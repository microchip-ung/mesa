/*


 Copyright (c) 2004-2020 Microsemi Corporation "Microsemi".

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

 *****************************************************************************************
* Revision 0.6  2018/10/23 sunilp
* Fixed issue related to vtss_phy_10g_init() and commented out the call to vtss_phy_10g_mode_get
* Revision 0.5  2018/10/03 sunilp
* Changed MALIBU_EVAL_BOARD to MALIBU_CHAR_BOARD
* Revision 0.4  2018/08/31 sunilp
* Added support for different data rates
* Revision 0.3  2018/07/19 sunilp
* Modified GPIO functionality to match datasheet documentation and added aggregate interrupt
* Added SCKOUT/CKOUT support, 10GBASE-KR support
* Revision 0.2  2018/06/29 sunilp
* Added GPIO functionality
* Revision 0.1  2018/06/27 sunilp
* 0.1 is the first version for the Malibu family of products (VSC8254/57/58(-xx))
 *****************************************************************************************

*/
#include "vtss_api.h"   // For board initialization
#include "vtss_appl.h"  // For vtsss_board_t
#include "vtss_port_api.h"
#include "vtss_appl_10g_phy_malibu.h" // For board init
#include "../base/ail/vtss_state.h" // For AIL dumping function
#include <netdb.h>  // For socket
#include <stdarg.h> // For va_list

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
FILE   *fp;
#endif

#ifdef VTSS_FEATURE_PHY_TIMESTAMP
#include "vtss_phy_ts_api.h"
#include "vtss_appl_ts_demo.h"
#define EVAL_BOARD_1588_CAPABLE

#else

#undef EVAL_BOARD_1588_CAPABLE
#endif

#ifdef VTSS_FEATURE_MACSEC
#include "vtss_macsec_api.h"
#include <openssl/aes.h>
#include "vtss_appl_macsec_demo.h"
#define EVAL_BOARD_MACSEC_CAPABLE

#else

#undef EVAL_BOARD_MACSEC_CAPABLE
#endif

/* ================================================================= *
 *  Board init.
 * ================================================================= */
#define SPI_WR  (0)
#define SPI_RD  (1)


#define PHY_MODE_10G_LAN     (0)
#define PHY_MODE_1G_LAN      (1)
#define PHY_MODE_10G_WAN     (2)

#define MAX_BOARD_INSTANCES    (2)
/* Board specifics */
static vtss_appl_board_t board_table[MAX_BOARD_INSTANCES];

#ifdef _INCLUDE_DEBUG_TERM_PRINT_
static BOOL live_debug_enable = TRUE;
#endif

// #define EXTENDED_LOOPBACK    // Enable SerDes Loopback
// #undef  CHANGE_PHY_BASE_PORT // Eval Board has the Base Port Addr set to something other than 0

// Function defining the board
//
// In : Pointer to the board definition
void vtss_board_phy_init(vtss_appl_board_t *board)
{
	memset (board, 0, sizeof(vtss_appl_board_t));
	// board->descr = "PHY"; // Description
	board->target = VTSS_TARGET_10G_PHY; // Target

	// Please select which EVAL board you are using.
	// The mmd_read, mmd_write,... fuctions are defined for the particular EVAL board you are using.
#if defined (MALIBU_CHAR_BOARD)
	board->board_init = malibu_board_init; // Pointer to function initializing the board
	//#define EVAL_BOARD_1588_CAPABLE
	//#define EVAL_BOARD_MACSEC_CAPABLE
#endif
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
    //.level[0] = VTSS_TRACE_LEVEL_ERROR
    //.level[0] = VTSS_TRACE_LEVEL_INFO
    .level[0] = VTSS_TRACE_LEVEL_DEBUG
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

vtss_rc vtss_phy_10g_malibu_dump_public (const vtss_inst_t inst,
                                          const vtss_debug_printf_t pr,
                                          const vtss_port_no_t port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        rc = VTSS_RC_COLD(vtss_phy_10g_debug_malibu_info_print(vtss_state, pr, port_no));
    }
    VTSS_EXIT();
    return rc;
}


/* ********************************************************** */
/* ********************************************************** */
/* ******    Test SPI I/O                 ******************* */
/* ********************************************************** */
BOOL  vtss_appl_malibu_spi_io_test(const vtss_inst_t   inst, const vtss_port_no_t   port_no)
{
    u32 val32 = 0;
    u32 val32B = 0;
    u16 addr;
    u8 dev;

    dev = 0x1E; addr = 0x0;
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
    printf("0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

    dev = 0x1E; addr = 0x0;
    inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
    printf("1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

    dev = 0x1E; addr = 0x0;
    inst->init_conf.spi_32bit_read_write(inst, 2, SPI_RD, dev, addr, &val32);
    printf("2x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

    // dev = 0x1E; addr = 0x9002;
    // inst->init_conf.spi_32bit_read_write(NULL, 0, SPI_RD, dev, addr, &val32);
    // printf("0x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);
    // *val32 = 0x4;
    // inst->init_conf.spi_32bit_read_write(NULL, 0, SPI_WR, dev, addr, &val32);
    // inst->init_conf.spi_32bit_read_write(NULL, 0, SPI_RD, dev, addr, &val32);
    // printf("0x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);
    //
    // dev = 0x1E; addr = 0x9002;
    // inst->init_conf.spi_32bit_read_write(NULL, 2, SPI_RD, dev, addr, &val32);
    // printf("2x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);
    // *val32 = 0x4;
    // inst->init_conf.spi_32bit_read_write(NULL, 2, SPI_WR, dev, addr, &val32);
    // inst->init_conf.spi_32bit_read_write(NULL, 2, SPI_RD, dev, addr, &val32);
    // printf("2x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);
    //
    // dev = 0x1E; addr = 0x9202;
    // inst->init_conf.spi_32bit_read_write(NULL, 0, SPI_RD, dev, addr, &val32);
    // printf("0x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);
    // *val32 = 0x4;
    // inst->init_conf.spi_32bit_read_write(NULL, 0, SPI_WR, dev, addr, &val32);
    // inst->init_conf.spi_32bit_read_write(NULL, 0, SPI_RD, dev, addr, &val32);
    // printf("0x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);
    //
    // dev = 0x1E; addr = 0x9202;
    // inst->init_conf.spi_32bit_read_write(NULL, 2, SPI_RD, dev, addr, &val32);
    // printf("2x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);
    // *val32 = 0x4;
    // inst->init_conf.spi_32bit_read_write(NULL, 2, SPI_WR, dev, addr, &val32);
    // inst->init_conf.spi_32bit_read_write(NULL, 2, SPI_RD, dev, addr, &val32);
    // printf("2x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

    dev = 0x1; addr = 0xF112;
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
    printf("0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    val32 = 0x003DF828;
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_WR, dev, addr, &val32);
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
    printf("0x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

    dev = 0x1; addr = 0xF112;
    inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
    printf("1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    val32 = 0x004DF828;
    inst->init_conf.spi_32bit_read_write(inst, 1, SPI_WR, dev, addr, &val32);
    inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
    printf("1x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

    dev = 0x1; addr = 0xF112;
    inst->init_conf.spi_32bit_read_write(inst, 2, SPI_RD, dev, addr, &val32);
    printf("2x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    val32 = 0x005DF828;
    inst->init_conf.spi_32bit_read_write(inst, 2, SPI_WR, dev, addr, &val32);
    inst->init_conf.spi_32bit_read_write(inst, 2, SPI_RD, dev, addr, &val32);
    printf("2x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    val32 = 0x007DF820;
    inst->init_conf.spi_32bit_read_write(inst, 2, SPI_WR, dev, addr, &val32);
    inst->init_conf.spi_32bit_read_write(inst, 2, SPI_RD, dev, addr, &val32);
    printf("2x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

    dev = 0x1; addr = 0xF112;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    val32 = 0x006DF828;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_WR, dev, addr, &val32);
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    val32 = 0x007DF820;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_WR, dev, addr, &val32);
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("3x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

    dev = 0x1; addr = 0xF120;
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
    printf("0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
    printf("1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    inst->init_conf.spi_32bit_read_write(inst, 2, SPI_RD, dev, addr, &val32);
    printf("2x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("3x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

    dev = 0x1; addr = 0xF121;
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
    printf("0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    val32B = 0x48888924;
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_WR, dev, addr, &val32B);
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32B);
    printf("0x%Xx%04X = 0x%X\n", dev, addr, val32B); fflush(stdout);

    // *val32 = 0x88888924;
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_WR, dev, addr, &val32);
    inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
    printf("0x%Xx%04X = 0x%X\n\n\n", dev, addr, val32); fflush(stdout);

}

    /* ********************************************************** */
    /* ********************************************************** */
    /* ******    SYNC-E                       ******************* */
    /* ********************************************************** */
    // SYNC-E: SREFCLK function to configure the input SyncE clock
    //
    // srefclk_enable:
    // --> TRUE (to configure SREFCLK input macro),
    // --> FALSE (to disable SREFCLK input macro)
    //
    // srefclk_freq:
    // --> VTSS_PHY_10G_SREFCLK_156_25 (156.25MHz)
    // --> VTSS_PHY_10G_SREFCLK_125_00 (125.00MHz)
    // --> VTSS_PHY_10G_SREFCLK_155_52 (155.52MHz)
    //
    // Note:
    // Users must add a call to the "lane sync" function after calling the SREFCLK function.
    // The following 10G Tx Macros are available as destination for synchronization to SREFCLK:
    // --> Line Ch0/Ch1/Ch2/Ch3,
    // --> Host Ch0/Ch1/Ch2/Ch3 or
    // --> SCKOUT

BOOL  vtss_appl_malibu_synce_cntrl(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
    if (port_no == VTSS_PORT_NO_START) {
      vtss_phy_10g_srefclk_mode_t     srefclk;

      memset(&srefclk, 0, sizeof(vtss_phy_10g_srefclk_mode_t));

      printf("SREFCLK configuration: \n");
      if (vtss_phy_10g_srefclk_conf_get(inst, port_no, &srefclk) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_srefclk_conf_get, port %d\n", port_no);
	printf("%% Error getting SREFCLK configuration for port %d \n", port_no);
      }

      srefclk.enable = TRUE;
      srefclk.freq = VTSS_PHY_10G_SREFCLK_156_25;

      if (vtss_phy_10g_srefclk_conf_set(inst, port_no, &srefclk) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_srefclk_conf_set, port %d\n", port_no);
	printf("Malibu Error getting SREFCLK configuration for port %d \n", port_no);
      }
      printf("Done!\n");

      // Lane Sync: To synchronize a Tx macro to an Rx source.
      // This code syncs Ch3 10G Line Tx macro to SREFCLK
      vtss_phy_10g_lane_sync_conf_t lane_sync;

      memset(&lane_sync, 0, sizeof(vtss_phy_10g_lane_sync_conf_t));

      printf("Lane Sync configuration --> Rx (Source): SREFCLK, Tx (Destination): Line Ch0 \n");
      lane_sync.enable = TRUE;
      lane_sync.rx_macro = VTSS_PHY_10G_RX_MACRO_SREFCLK;
      lane_sync.tx_macro = VTSS_PHY_10G_TX_MACRO_LINE;
      lane_sync.rx_ch = 0;
      lane_sync.tx_ch = 0;

      if (vtss_phy_10g_lane_sync_set(inst, port_no, &lane_sync) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_lane_sync_set, port %d\n", port_no);
	printf("Malibu Error setting lane sync configuration for port %d \n", port_no);
      }
      printf("Done!\n\n");
    }

    // SYNC-E: SCKOUT function to configure the input SyncE clock
    //
    // sckout_enable:
    // --> TRUE (to configure SCKOUT input macro),
    // --> FALSE (to disable SCKOUT input macro)
    //
    // sckout_freq:
    // --> VTSS_PHY_10G_SCKOUT_156_25 (156.25MHz)
    // --> VTSS_PHY_10G_SCKOUT_125_00 (125.00MHz)
    //
    //
    // Note:
    // Users must add a call to the "lane sync" function after calling the SCKOUT function.
    // The following 10G Rx Macros are available as destination for synchronization to SCKOUT:
    // --> Line Ch0/Ch1/Ch2/Ch3,
    // --> Host Ch0/Ch1/Ch2/Ch3 or
    // --> SREFCLK

    if (port_no == VTSS_PORT_NO_START) {
      vtss_phy_10g_sckout_conf_t sckout;

      memset(&sckout, 0, sizeof(vtss_phy_10g_sckout_conf_t));

      printf("SCKOUT configuration: \n");
      sckout.mode = VTSS_PHY_10G_SYNC_DISABLE;
      sckout.src = VTSS_CKOUT_NO_SQUELCH;
      sckout.freq = VTSS_PHY_10G_SCKOUT_156_25;
      sckout.squelch_inv = FALSE;
      sckout.enable = TRUE;

      if(vtss_phy_10g_sckout_conf_set(inst, port_no, &sckout) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_sckout_set, port %d", port_no);
	printf("Malibu Error setting SCKOUT configuration \n");
      }
      printf("Done!\n");

      // Lane Sync: To synchronize a Tx macro to an Rx source.
      // This code synchronizes SCKOUT to SREFCLK
      vtss_phy_10g_lane_sync_conf_t lane_sync;

      memset(&lane_sync, 0, sizeof(vtss_phy_10g_lane_sync_conf_t));

      printf("Lane Sync configuration --> Rx (Source): SREFCLK, Tx (Destination): SCKOUT \n");
      lane_sync.enable = TRUE;
      lane_sync.rx_macro = VTSS_PHY_10G_RX_MACRO_SREFCLK;
      lane_sync.tx_macro = VTSS_PHY_10G_TX_MACRO_SCKOUT;
      lane_sync.rx_ch = 0;
      lane_sync.tx_ch = 0;

      if (vtss_phy_10g_lane_sync_set(inst, port_no, &lane_sync) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_lane_sync_set, port %d", port_no);
	printf("Malibu Error setting lane sync configuration for port %d \n", port_no);
      }
      printf("Done!\n\n");
    }

    // SYNC-E: CKOUT function to configure the input SyncE clock
    //
    // Note:
    // 1) At 10G LAN data rate, Line/Host Tx/Rx clock is 161.1328125MHz +/- ppm delta (10.3125G/64)
    // 2) At 10G WAN data rate, Line/Host Tx/Rx clock is 155.52MHz +/- ppm delta (9.95328G/64)
    // 3) At 1G LAN data rate, Line/Host Tx/Rx clock is 62.5MHz +/- ppm delta (1.25G/20)

    if (port_no == VTSS_PORT_NO_START) {
      vtss_phy_10g_ckout_conf_t ckout;

      memset(&ckout, 0, sizeof(vtss_phy_10g_ckout_conf_t));

      ckout.mode = VTSS_CKOUT_LINE0_RECVRD_CLOCK;
      ckout.src = VTSS_CKOUT_NO_SQUELCH;
      ckout.freq = VTSS_PHY_10G_CLK_DIVIDE_BY_2;
      ckout.squelch_inv = FALSE;
      ckout.ckout_sel = CKOUT0;
      ckout.enable = TRUE;

      if(vtss_phy_10g_ckout_conf_set(inst, port_no, &ckout) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_ckout_set, port %d", port_no);
	printf("Malibu Error setting CKOUT configuration for port %d \n", port_no);
      }
    }
#endif
}

  /* ********************************************************** */
  /* **********   10G Output Buffer (OB) Control    *********** */
  /* ********************************************************** */
  /* HH:  moved to before any link-related functionality e.g. ANEG or PRBS are tested, in order to apply included settings for those tests */
  // 10G Output Buffer (OB) or "d_filter" or KR driver Control
  //
  // Notes:
  // 1) abs(c0)+abs(c1)+abs(cm2) should be less than 31
  // 2) "ampl" should be less than 1275 (mV) (OB_ampl < 1275)
  // 3) "slewrate" (or rise time) settings: 0 = 25ps (10G LAN recommendation), 1 = 35ps, 2 = 55ps, 3 = 70ps, 4 = 120ps
BOOL  vtss_appl_malibu_ob_cntrl(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
  //for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++)
  {
    vtss_phy_10g_base_kr_conf_t kr_conf;

    memset(&kr_conf, 0, sizeof(vtss_phy_10g_base_kr_conf_t));

    // Line side Output Buffer control
    printf("\nMalibu 10G Output Buffer configuration on Line side of Port %d \n", port_no);

    memset(&kr_conf, 0, sizeof(vtss_phy_10g_base_kr_conf_t));

    if(vtss_phy_10g_base_kr_conf_get(inst, port_no, &kr_conf) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_base_kr_conf_init, port %d", port_no);
      printf("Malibu Error getting 10G Output Buffer (KR driver) configuration for Port %d (Line) \n", port_no);
    }

	/* HH:  D_FILTER 0x45f876 corresponding to tap values cm1=-4,c0=23,c1=-11 for -9dB (w.c.) channel in char report */
	/* but D_FILTER 0x45f876 is not programmable through API due to sum<=31 rule.  That value has to programmed directly*/
	/* HH:  Per Sunil, positive/amplifying cm1/C1 values should never be used as potentially introduces non-linearities in signal */
    kr_conf.cm1 = 0;
    kr_conf.c0 = 25;
    kr_conf.c1 = -6;
    kr_conf.ampl = 1000;

    kr_conf.slewrate = 0;
    kr_conf.en_ob = TRUE;
    kr_conf.ser_inv = FALSE;

    printf("\ncml = %d\n", kr_conf.cm1);
    printf("c0 = %d\n", kr_conf.c0);
    printf("c1 = %d\n", kr_conf.c1);
    printf("ampl = %d\n", kr_conf.ampl);

    printf("slewrate = %d\n", kr_conf.slewrate);
    printf("en_ob = %d\n", kr_conf.en_ob);
    printf("ser_inv = %d\n", kr_conf.ser_inv);

    if (vtss_phy_10g_base_kr_conf_set(inst, port_no, &kr_conf) != VTSS_RC_OK) {
      printf("Malibu Error setting 10G Output Buffer (KR driver) configuration for Line-side of Port %d \n", port_no);
    }

    // Host side Output Buffer control
    printf("\nMalibu 10G Output Buffer configuration on Host side of Port %d \n", port_no);
    if(vtss_phy_10g_base_kr_conf_get(inst, port_no, &kr_conf) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_base_kr_conf_init, port %d", port_no);
      printf("Malibu Error getting 10G Output Buffer (KR driver) configuration for Port %d (Host) \n", port_no);
    }
    kr_conf.cm1 = 0;
    kr_conf.c0 = 29;
    kr_conf.c1 = -2;
    kr_conf.ampl = 1000;

    kr_conf.slewrate = 0;
    kr_conf.en_ob = TRUE;
    kr_conf.ser_inv = FALSE;

    printf("\ncml = %d\n", kr_conf.cm1);
    printf("c0 = %d\n", kr_conf.c0);
    printf("c1 = %d\n", kr_conf.c1);
    printf("ampl = %d\n", kr_conf.ampl);

    printf("slewrate = %d\n", kr_conf.slewrate);
    printf("en_ob = %d\n", kr_conf.en_ob);
    printf("ser_inv = %d\n", kr_conf.ser_inv);

    if (vtss_phy_10g_base_kr_host_conf_set(inst, port_no, &kr_conf) != VTSS_RC_OK) {
      printf("Malibu Error setting 10G Output Buffer (KR driver) configuration for Host-side of Port %d \n", port_no);
    }
  }
#endif
}


  /* ********************************************************** */
  /* ********   10GBASE-KR Auto-Neg and Training     ********** */
  /* ********************************************************** */
BOOL  vtss_appl_malibu_10g_base_kr_cntrl(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
  // KR enabled only on Ch0 and Ch1 per connections on the test board
  //for (port_no = VTSS_PORT_NO_START; port_no < (VTSS_PORTS/2); port_no++)
  {
    // Perform 10GBASE-KR on the HOST/LINE Interface
    vtss_phy_10g_base_kr_train_aneg_t aneg;

    printf("\nMalibu 10GBASE-KR AN/Tr configuration on Line side of Port %d \n", port_no);
    memset(&aneg, 0, sizeof(vtss_phy_10g_base_kr_train_aneg_t));

    aneg.line_kr = TRUE;
    aneg.host_kr = FALSE;
    aneg.training.enable = TRUE;
    aneg.training.trmthd_c0 = 0;
    aneg.training.trmthd_cm = 0;
    aneg.training.trmthd_cp = 0;
    aneg.training.ld_pre_init = 0;
    aneg.autoneg.an_restart = TRUE;
    aneg.autoneg.an_enable = TRUE;
    aneg.autoneg.an_reset = FALSE;
    aneg.ld_abil.adv_1g = 0;    // not supported!
    aneg.ld_abil.adv_10g = 1;   // default option
    aneg.ld_abil.fec_abil = 1;  // by default chosen by api
    aneg.ld_abil.fec_req = 0;   // set FEC request, configurable yes or no (1 or 0)

    // Enable line side 10GBASE-KR Auto-Neg and Training
    if (vtss_phy_10g_base_kr_train_aneg_set(inst, port_no, &aneg) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_base_kr_train_aneg_set, port %d\n", port_no);
      printf("Malibu Error setting 10GBASE-KR AN/Tr configuration on Line side of Port %d \n", port_no);
      return (FALSE);
    }
    // Enable host side 10GBASE-KR Auto-Neg and Training
    // if (vtss_phy_10g_base_host_kr_train_aneg_set(board->inst, port_no, &aneg) != VTSS_RC_OK) {
    //   T_E("vtss_phy_10g_base_kr_train_aneg_set, port %d, gpio %d, mode: INPUT\n", port_no, gpio_no);
    //   printf("Malibu Error setting 10GBASE-KR AN/Tr configuration on Host side of Port %d \n", port_no);
    //   return ERROR;
    // }
  }

  // Enable 10GBASE-KR AN/Tr between port 0 and port 1 of VSC825x on the line side
  //for (port_no = VTSS_PORT_NO_START; port_no < (VTSS_PORTS/2); port_no++)
  {
    u8 loop_count=0;
    vtss_phy_10g_base_kr_status_t kr_status;
    memset(&kr_status, 0, sizeof(vtss_phy_10g_base_kr_status_t));

    do {
      if (vtss_phy_10g_kr_status_get(inst, port_no, TRUE, &kr_status) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_base_kr_status_get, port %d\n", port_no);
	printf("Malibu Error getting 10GBASE-KR AN/Tr configuration on Line side of Port %d \n", port_no);
      }
      printf("loop_count = %d\n", loop_count);
      printf("aneg complete - %s \n", kr_status.aneg.complete ? "TRUE" : "FALSE");
      printf("training complete - %s \n", kr_status.train.complete ? "TRUE" : "FALSE");
      uint msec = 500;
      struct timespec ts;					  \
      ts.tv_sec = msec / 1000;					  \
      ts.tv_nsec = (msec % 1000) * 1000000;                       \
      while(nanosleep(&ts, &ts) == -1 && errno == EINTR) {        \
      }
      loop_count++;
    } while ((!kr_status.aneg.complete || !kr_status.train.complete) && (loop_count < 10) );

    printf("KR training and aneg status on port %u HOST\n", port_no);

    printf(" aneg complete - %s \n", kr_status.aneg.complete ? "TRUE" : "FALSE");
    printf(" aneg active - %s \n", kr_status.aneg.active ? "TRUE" : "FALSE");
    printf(" aneg lp request_10g - %s \n", kr_status.aneg.request_10g ? "TRUE" : "FALSE");
    printf(" aneg lp request_1g - %s \n", kr_status.aneg.request_1g ? "TRUE" : "FALSE");
    printf(" aneg request_fec_change - %s \n", kr_status.aneg.request_fec_change ? "TRUE" : "FALSE");
    printf(" aneg fec_enable - %s \n", kr_status.aneg.fec_enable ? "TRUE" : "FALSE");
    printf(" aneg sm - %u \n", kr_status.aneg.sm );
    printf(" aneg lp_aneg_able - %s \n", kr_status.aneg.lp_aneg_able ? "TRUE" : "FALSE");
    printf(" pcs block_lock - %s \n", kr_status.aneg.block_lock ? "TRUE" : "FALSE");
    printf(" training complete - %s \n", kr_status.train.complete ? "TRUE" : "FALSE");
    printf(" training cm_ob_tap_result - %d \n", (kr_status.train.cm_ob_tap_result==0) ? 0:(kr_status.train.cm_ob_tap_result-128) );
    printf(" training cp_ob_tap_result - %d \n", (kr_status.train.cp_ob_tap_result==0) ? 0:(kr_status.train.cp_ob_tap_result-128) );
    printf(" training c0_ob_tap_result - %d \n", kr_status.train.c0_ob_tap_result );

    printf(" fec enable - %s \n", kr_status.fec.enable ? "TRUE" : "FALSE");
    printf(" fec corrected_block_cnt - %u \n", kr_status.fec.corrected_block_cnt);
    printf(" fec uncorrected_block_cnt - %u \n", kr_status.fec.uncorrected_block_cnt);
  }

#endif

  return(TRUE);
}


  /* ********************************************************** */
  /* *******************    PRBS      ************************* */
  /* ********************************************************** */
  /* HH:  multiple build issues cleaned up in this area */
BOOL  vtss_appl_malibu_prbs_cntrl(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 0
  // Analog PRBS gen/mon config with status
  // Note: This code does not work with Mesa v5.4.0
  #ifdef HOST
	#error "preprocessor macro conflict - HOST"
  #else
	#define HOST 0
  #endif
  #ifdef LINE
	#error "preprocessor macro conflict - LINE"
  #else
	#define LINE 1
  #endif

    oper_mode_t data_rate;
    u8 prbs_num = 0;
    // prbs_pattern: 0 = PRBS7,  1 = PRBS15,  2 = PRBS23,  3 = PRBS11,  4 = PRBS31,  5 = PRBS9
    u8 prbs_pattern = 4;
    BOOL prbs_line_host = HOST;  /* <select the line side or host side, 1 for line side */
    BOOL prbs_enable = TRUE;

    // Configure the generator
    vtss_phy_10g_prbs_gen_conf_t prbs_gen_conf;
    vtss_phy_10g_prbs_mon_conf_t prbs_mon_conf;

  //for (port_no = VTSS_PORT_NO_START; port_no < (VTSS_PORTS/2); port_no++)
  {

    // Get the PRBS pattern number
    switch (prbs_pattern)
      {
      case 0:
	prbs_num = 7;
	break;
      case 1:
	prbs_num = 15;
	break;
      case 2:
	prbs_num = 23;
	break;
      case 3:
	prbs_num = 11;
	break;
      case 4:
	prbs_num = 31;
	break;
      case 5:
	prbs_num = 9;
	break;
      default:
	prbs_num = 0;
	printf("Malibu Error getting PRBS pattern info for port %d  prbs_pattern: %d,  prbs_num:%d\n", port_no, prbs_pattern, prbs_num);
	break;
      }

    memset(&prbs_gen_conf, 0, sizeof(vtss_phy_10g_prbs_gen_conf_t));

    prbs_gen_conf.enable = TRUE; // Enable the generator
    //prbs_gen_conf.prbsn_tx_sel = prbs_pattern; // Select the PRBS pattern to be generated
    prbs_gen_conf.line = prbs_line_host; // Select between LINE and HOST interfaces to run this test on
    //prbs_gen_conf.prbsn_tx_io = TRUE; // Enable inversion (internal usage)
    //prbs_gen_conf.prbsn_tx_iw = 4; /* PCS->PMA interface width for DFT control register (internal usage) --> */
                                   /* NOTE: if data_rate == VTSS_PHY_1G_MODE), then set to 1  */

    if(vtss_phy_10g_prbs_gen_conf(inst, port_no, &prbs_gen_conf) != VTSS_RC_OK) {
      printf("Malibu Error setting PRBS GEN configuration for port %d \n", port_no);
      return (FALSE);
    }
  }

  //for (port_no = VTSS_PORT_NO_START; port_no < (VTSS_PORTS/2); port_no++)
  {

    memset(&prbs_mon_conf, 0, sizeof(vtss_phy_10g_prbs_mon_conf_t));

    prbs_mon_conf.enable = prbs_enable; // Enable the monitor
    prbs_mon_conf.line = prbs_line_host; // Select between LINE and HOST interfaces to run this test on
    prbs_mon_conf.max_bist_frames = 1000; // BIST threshold (internal usage)
    prbs_mon_conf.error_states = 2; // BIST state for counting errors (internal usage)
    prbs_mon_conf.des_interface_width = 4; // same def as tx_iw.  Interface width (internal usage)  --> NOTE: if data_rate == VTSS_PHY_1G_MODE), then set to 1
    prbs_mon_conf.prbsn_sel = prbs_pattern; // Select the PRBS pattern to be checked against
    prbs_mon_conf.prbs_check_input_invert = TRUE; // Enable inversion (internal usage)
    prbs_mon_conf.no_of_errors = 7; // BIST state transition number (internal usage)
    prbs_mon_conf.bist_mode = 3; // BIST mode (internal usage)

    if(vtss_phy_10g_prbs_mon_conf(inst, port_no, &prbs_mon_conf) != VTSS_RC_OK) {
      printf("Malibu Error setting PRBS MON configuration for port %d \n", port_no);
      return (FALSE);
    }
  }

  sleep(1);  /* HH: was 100seconds.  PRBS algo running on 10Gbps clock so this can be changed to 1 second ( 2^31/10^10  seconds for PRBS31 gives 4 complete LFSR rollovers ). */

  //for (port_no = VTSS_PORT_NO_START; port_no < (VTSS_PORTS/2); port_no++)
  {
    // Needs the following additional arguments:
    // -- line: TRUE = Line side, FALSE = Host side,
    // -- reset: TRUE = reset the error counter, FALSE = do not reset the error counter
    if(vtss_phy_10g_prbs_mon_status_get(inst, port_no, &prbs_mon_conf, prbs_line_host, TRUE) != VTSS_RC_OK) {
      printf("Malibu Error setting PRBS MON STATUS GET configuration for port %d \n", port_no);
    } else {
      printf("Port %d: PRBS monitor status on %s side\n", port_no, prbs_line_host ? "LINE" : "HOST");
      printf("Error Counter for PRBS%d: %u\n", prbs_num, prbs_mon_conf.error_status);
      printf("PRBS Status (PRBS data related to 1st sync lost event): %u\n", prbs_mon_conf.PRBS_status);
      printf("Main Status register for PRBS:%u\n", prbs_mon_conf.main_status);
      printf("Stuck at par: %s\nstuck at 0/1: %s\n", prbs_mon_conf.stuck_at_par? "true":"false", prbs_mon_conf.stuck_at_01? "true":"false");
      printf("No Sync: %s\nUnstable:%s\n", prbs_mon_conf.no_sync? "true":"false", prbs_mon_conf.instable? "true":"false");
      printf("Incomplete: %s\nActive: %s\n", prbs_mon_conf.incomplete? "true":"false", prbs_mon_conf.active? "true":"false");
    }
	/* added code to gracefully deactivate generator */
   prbs_gen_conf.enable = FALSE;
    if(vtss_phy_10g_prbs_gen_conf(inst, port_no, &prbs_gen_conf) != VTSS_RC_OK) {
      printf("Malibu Error turning off PRBS GEN configuration for port %d \n", port_no);
      return (FALSE);
    }
    else {
        printf("Malibu turning off PRBS GEN configuration for port %d \n", port_no);
    }
  }
  /* added code to gracefully deactivate monitor */
  //for (port_no = VTSS_PORT_NO_START; port_no < (VTSS_PORTS/2); port_no++)
  {
      prbs_mon_conf.enable = FALSE;
      if(vtss_phy_10g_prbs_mon_conf(inst, port_no, &prbs_mon_conf) != VTSS_RC_OK) {
          printf("Malibu Error turning off PRBS MON configuration for port %d \n", port_no);
          return (FALSE);
      }
      else
          printf("Malibu turning off PRBS MON configuration for port %d \n", port_no);
  }
#endif

  return(TRUE);

}


  /* ********************************************************** */
  /* **********   10G Serdes Vscope Control    **************** */
  /* ********************************************************** */
  // 10G Serdes Vscope Control
  //

BOOL  vtss_appl_malibu_vscope_cntrl(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
    vtss_rc    rc = 0;
    int i=0;
    int j=0;
    char value_str[255] = {0};
    vtss_phy_10g_vscope_conf_t vscope_conf;  // FAST SCAN
    vtss_phy_10g_vscope_scan_conf_t vscope_scan_conf; // FULL SCAN parameters -- does not apply to FAST SCAN
    vtss_phy_10g_vscope_scan_status_t  scan_status;

    // Initialize all structs to 0
    memset(&vscope_conf, 0, sizeof(vtss_phy_10g_vscope_conf_t));
    memset(&vscope_scan_conf, 0, sizeof(vtss_phy_10g_vscope_scan_conf_t));
    memset(&scan_status, 0, sizeof(vtss_phy_10g_vscope_scan_status_t));

    // There are 2 options:
    // -- Fast Scan --> VTSS_PHY_10G_FAST_SCAN
    // -- Full Vscope --> VTSS_PHY_10G_FULL_SCAN
    printf ("Configure VSCOPE:  0=FULL SCAN   1=FAST SCAN  \n");
    memset (&value_str[0], 0, sizeof(value_str));
    scanf("%s", &value_str[0]);

    if (value_str [0] == '1') {
        vscope_conf.scan_type = VTSS_PHY_10G_FAST_SCAN;
    } else {
        vscope_conf.scan_type = VTSS_PHY_10G_FULL_SCAN;
    }

    vscope_conf.line = TRUE;
    vscope_conf.enable = TRUE;
    vscope_conf.error_thres = 3;

    if (vscope_conf.scan_type == VTSS_PHY_10G_FAST_SCAN) {
        printf ("VSCOPE Config:  VTSS_PHY_10G_FAST_SCAN !\n");
    } else if (vscope_conf.scan_type == VTSS_PHY_10G_FULL_SCAN) {
        printf ("VSCOPE Config:  VTSS_PHY_10G_FULL_SCAN !\n");
    } else {
        printf ("VSCOPE Config:  ERROR VSCOPE MISCONFIGURED !\n");
    }

/* x_start can be anything from 0 (LHS of the sampling window) to 127, but do not recommend than greater than 20% of U.I.  Generally no
reason to use x_start other than 0.
 */
/* y_axis has a center point at count 31-32 (it's 6 bit counter).  Generally +/-12 is sufficient for a typical eye visulation (efficient run time)
 */
/* x_incr and y_incr = 0 is to collect all points.  Increment by n to skip every nth point.
 */
/* ber is TBD for definition - unclear whether e.g. value 5 means 10^-5 i.e. an undefined confidence for the BER value input.
note the GDC sample count is unknown how implemented in the digital HW.
*/
/* note overall:  the vscope_scan_conf arguments are all directly written to SD10G registers.  I.e. digitial PMA performs this processing
 */
/* notes about results:  the error_free_y returned from FAST_SCAN is "inner bounds".  the amp_range returned from FAST_SCAN is "outer bound" i.e. the
maximum  amplitude swing observed at receiver.  However the statistical confidence of the reported "inner_bound" depends on the GDC sampling/count
for the ber parameter passed in [a relationship which is unknown at this time w/o GDC help].
*/

    vscope_scan_conf.x_start = 0;
    vscope_scan_conf.y_start = 20;
    vscope_scan_conf.x_count = 127;
    vscope_scan_conf.y_count = 25;
    vscope_scan_conf.x_incr = 0;
    vscope_scan_conf.y_incr = 0;
    vscope_scan_conf.ber = 5;

    scan_status.scan_conf = vscope_scan_conf;

    if (vtss_phy_10g_vscope_conf_set(inst, port_no, &vscope_conf) != VTSS_RC_OK) {
      printf("Malibu Error setting 10G Serdes VScope configuration on Port %d \n", port_no);
    } else {

      // Get the results
      printf("\nMalibu VSCOPE successfully configured\n");
      if((rc = vtss_phy_10g_vscope_scan_status_get(inst, port_no, &scan_status)) != VTSS_RC_OK){
          printf("Malibu Error Fetching VSCOPE data\n");
      }
      else {
          if (vscope_conf.scan_type == VTSS_PHY_10G_FAST_SCAN) {
              printf("FAST SCAN error free x points: %d\n", scan_status.error_free_x);
              printf("FAST SCAN error free y points: %d\n", scan_status.error_free_y);
              printf("FAST SCAN amplitude range: %d\n", scan_status.amp_range);
          } else if (vscope_conf.scan_type == VTSS_PHY_10G_FULL_SCAN) {
              // Create a data eye on a screen --> "X" for no errors, "." for errors
              printf("VScope FULL SCAN for Port %d are as follows:\n", port_no);
              for(j=vscope_scan_conf.y_start; j < (vscope_scan_conf.y_start + vscope_scan_conf.y_count); j = j + vscope_scan_conf.y_incr + 1){
                  if (scan_status.errors[0][j] == 0)
                      j++;
                  printf("\n");
                  for(i=vscope_scan_conf.x_start; i < (vscope_scan_conf.x_start + vscope_scan_conf.x_count) ;i = i + vscope_scan_conf.x_incr + 1){
                      if(scan_status.errors[i][j] == 0)
                          printf("X");
                      else
                          printf(".");
                  }
              }
          }
          else{
              printf("Scan Type not supported\n");
          }
      }
    }
#endif
    return(TRUE);
}


BOOL  vtss_appl_malibu_status_get(vtss_inst_t   inst, vtss_port_no_t   port_no, vtss_phy_10g_mode_t  *oper_mode)
{
# if 1
  // Port Status
  vtss_phy_10g_status_t status;
  vtss_phy_10g_cnt_t    cnt;

    printf("%-12s %-12s %-16s %-12s %-12s\n", "", "Link", "Link-down-event", "Rx-Fault-Sticky", "Tx-Fault-Sticky");

    if (vtss_phy_10g_status_get(inst, port_no, &status) != VTSS_RC_OK) {
        T_E("vtss_phy_10g_status_get failed, port %d", port_no);
        printf ("vtss_phy_10g_status_get failed, port %d", port_no);
        return (FALSE);
    }

    printf ("Port %u:\n", port_no);
    printf ("--------\n");
    printf ("%-12s %-12s %-16s %-12s %-12s\n", "Line PMA:", status.pma.rx_link?"Yes":"No",
              status.pma.link_down ? "Yes" : "No", status.pma.rx_fault ? "Yes" : "No", status.pma.tx_fault ? "Yes" : "No");
    printf ("%-12s %-12s %-16s %-12s %-12s\n", "Host PMA:", status.hpma.rx_link?"Yes":"No",
            status.hpma.link_down ? "Yes" : "No", status.hpma.rx_fault ? "Yes" : "No", status.hpma.tx_fault ? "Yes" : "No");
    printf ("%-12s %-12s %-16s %-12s %-12s\n", "WIS:", oper_mode->oper_mode == VTSS_PHY_WAN_MODE ? status.wis.rx_link ? "Yes" : "No" : "-",
            oper_mode->oper_mode == VTSS_PHY_WAN_MODE ? status.wis.link_down ? "Yes" : "No" : "-",
            oper_mode->oper_mode == VTSS_PHY_WAN_MODE ? status.wis.rx_fault ? "Yes" : "No" : "-",
            oper_mode->oper_mode == VTSS_PHY_WAN_MODE ? status.wis.tx_fault ? "Yes" : "No" : "-");
    printf ("%-12s %-12s %-16s %-12s %-12s\n", "Line PCS:", status.pcs.rx_link ? "Yes" : "No",
            status.pcs.link_down ? "Yes" : "No", status.pcs.rx_fault ? "Yes" : "No", status.pcs.tx_fault ? "Yes" : "No");
    printf ("%-12s %-12s %-16s %-12s %-12s\n", "Host PCS:", status.hpcs.rx_link ? "Yes" : "No",
            status.hpcs.link_down ? "Yes" : "No", status.hpcs.rx_fault ? "Yes" : "No", status.hpcs.tx_fault ? "Yes" : "No");
    printf ("%-12s %-12s %-16s %-12s %-12s\n", "XAUI Status:", status.xs.rx_link ? "Yes" : "No",
            status.xs.link_down ? "Yes" : "No", status.xs.rx_fault ? "Yes" : "No", status.xs.tx_fault ? "Yes" : "No");
    printf ("%-12s %-12s \n", "Line 1G PCS:", status.lpcs_1g ? "Yes" : "No");
    printf ("%-12s %-12s \n", "Host 1G PCS:", status.hpcs_1g ? "Yes" : "No");
    printf ("%-12s %-12s \n", "Link UP:", status.status ? "Yes" : "No");
    printf ("%-12s %-12s \n", "Block lock:", status.block_lock ? "Yes" : "No");
    printf ("%-12s %-12s \n", "LOPC status:", status.lopc_stat ? "Yes" : "No");

    if (vtss_phy_10g_cnt_get(inst, port_no, &cnt) != VTSS_RC_OK) {
        T_E("vtss_phy_10g_cnt_get failed, port %d", port_no);
        printf ("vtss_phy_10g_cnt_get failed, port %d", port_no);
        return (FALSE);
    }
    printf ("\n");
    printf ("PCS counters:\n");
    printf ("%-20s %-12s\n", "  Block_lacthed:", cnt.pcs.block_lock_latched ? "Yes" : "No");
    printf ("%-20s %-12s\n", "  High_ber_latched:", cnt.pcs.high_ber_latched ? "Yes" : "No");
    printf ("%-20s %-12d\n", "  Ber_cnt:", cnt.pcs.ber_cnt);
    printf ("%-20s %-12d\n", "  Err_blk_cnt:", cnt.pcs.err_blk_cnt);
    printf ("\n");

    fflush(stdout);
#endif

    return(TRUE);
}

    ///////////////////////////////////////////////////////////////////////////////
    // 1588 interrupts, using Line 10G PCS status, driving Aggregate Interrupt
    // output -- Channel dependent GPIOs
    // GPIO used for Aggregate Interrupt: #34
    ///////////////////////////////////////////////////////////////////////////////

BOOL  vtss_appl_malibu_ts_gpio_int_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#ifdef  EVAL_BOARD_1588_CAPABLE
#if 1
    char value_str[255] = {0};
    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    vtss_phy_ts_event_t ts_ev;
    u16 gpio_no;

    // Per channel 1588 Interrupts

    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));

    gpio_no = 35;

    // Note: NONE of the AGG_INT are working properly, Not 0, 1, 2, or 3.  They are not implementd correctly in the API
    // 1) Only available interrupts are as follows (AGG_INT_0 should not be used as of API 4.67.04)
    //    <This is because API routes all other INTs thru VTSS_10G_PHY_GPIO_AGG_INT_0, which is a bug>
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_1
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_2
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_3

    printf ("VTSS_PHY_TS_INGR_ENGINE_ERR            0x01\n");  /**< More than one engine find match */
    printf ("VTSS_PHY_TS_INGR_RW_PREAM_ERR          0x02\n");  /**< Preamble too short to append timestamp */
    printf ("VTSS_PHY_TS_INGR_RW_FCS_ERR            0x04\n");  /**< FCS error in ingress */
    printf ("VTSS_PHY_TS_EGR_ENGINE_ERR             0x08\n");  /**< More than one engine find match */
    printf ("VTSS_PHY_TS_EGR_RW_FCS_ERR             0x10\n");  /**< FCS error in egress */
    printf ("VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20\n");  /**< Timestamp captured in Tx TSFIFO */
    printf ("VTSS_PHY_TS_EGR_FIFO_OVERFLOW          0x40\n");  /**< Tx TSFIFO overflow */
    printf ("VTSS_PHY_TS_DATA_IN_RSRVD_FIELD        0x80\n");  /**< Data in reserved Field */
    printf ("VTSS_PHY_TS_LTC_NEW_PPS_INTRPT         0x100\n"); /**< New PPS pushed onto external PPS pin*/
    printf ("VTSS_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200\n"); /**< New LTC value either loaded in to HW or saved into registers*/

    // Enable 1588 TSFIFO overflow event
    if (vtss_phy_ts_event_enable_get(inst, port_no, &ts_ev) != VTSS_RC_OK) {
      T_E("vtss_phy_ts_event_enable_get, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO 1588 Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    printf("Current Malibu GPIO 1588 Event Enable configuration for port %d, gpio %d, Events: 0x%04x \n", port_no, gpio_no, ts_ev);

    printf ("Routing GPIO_NO: %d,  Enter 1588 Event Enable:  ", gpio_no);
    memset (&value_str[0], 0, sizeof(value_str));
    scanf("%s", &value_str[0]);
    ts_ev = strtol(value_str, NULL, 10);

    // Example of FIFO_OVERFLOW and TS_CAPTURED:
    ts_ev = VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED | VTSS_PHY_TS_EGR_ENGINE_ERR | VTSS_PHY_TS_EGR_FIFO_OVERFLOW | VTSS_PHY_TS_INGR_ENGINE_ERR | VTSS_PHY_TS_INGR_RW_FCS_ERR | VTSS_PHY_TS_EGR_RW_FCS_ERR;

    printf("\nUpdating/Setting Malibu GPIO 1588 Event Enable configuration for port %d, gpio %d, Events: 0x%04x \n", port_no, gpio_no, ts_ev);

    // Enable 1588 TSFIFO overflow event
    if (vtss_phy_ts_event_enable_set(inst, port_no, TRUE, ts_ev) != VTSS_RC_OK) {
      T_E("vtss_phy_ts_event_enable_set, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO 1588 Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    // Now configure the GPIO for Agg Int function
    //memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    //gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_1;
    //gpio_mode.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR3_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR2_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR1_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR0_EN);

    // Now configure the GPIO for 1588 Int function
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_1588_INT;
    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: 1588_INT\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO AGG_INT configuration for port %d, gpio %d, 1588 Int1 \n", port_no, gpio_no);
    }
#endif
#endif
}

    ///////////////////////////////////////////////////////////////////////////////
    // Per Channel interrupt, using Line 10G PCS status, driving Aggregate Interrupt
    // Note: for each of the 4 ports, the LOPC has Default config for:
    // Port 0: GPIO34; Port 1: GPIO35; Port 2: GPIO36; Port 3: GPIO37
    //
    // For Malibu, ALL Interrupts are considered Extended Interrupts and the following
    // Private functions are called by vtss_phy_10g_extended_event_enable_set() to configure these blocks
    // PMA: vtss_phy_10g_pma_event_enable_private
    //      - Enable the PMA Line side block interrupts
    //               Note: Block Interrupts Pending bits are STICKY, To clear, must write a '1' back.  API takes care of this action.
    //      - Enable the LPMA interrupts on INTR[1] for LPMA_INTR_EN: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR: There is INTR[0-1]: API uses INTR[1]
    //      - Enable INTR_SRC_EN: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN – LPMA_INTR.
    //               There is INTR[0-1]: API hard-codes and uses INTR[1] and also hard-codes and uses aggr_intr[0] for all channels
    //      - Enable the LPMA interrupts on INTR[1] for LPMA_INTR_EN
    //      - Enable INTR_SRC_EN (GPIO_CTRL (Dev 0x1E):INTR_CFG_STAT:INTR_SRC_EN[0-3].CH0_INTR1_EN) PMA block interrupts at aggr_intr[0], all chan
    //               So, by default: API is using: VTSS_10G_PHY_GPIO_AGG_INT_0
    //               NOTE: User's should avoid using Agg_INT_0 or CHx_INTR1
    //    - vtss_phy_10g_gpio_mode_set:
    //        - Configure the GPIO for Agg Int and connect to the GPIO output pin (GPIO_No = 34)
    //        - Connect up VTSS_10G_PHY_GPIO_AGG_INT_0 via VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR1_EN,
    //        - Trigger on Input Signal VTSS_10G_GPIO_INTR_SGNL_LINE_PMA_INT
    //
    // PCS: vtss_phy_10g_pcs_event_enable_private
    //      - Enable the PCS Line side block interrupts by setting Mask
    //               Note: Block Interrupts Pending bits are STICKY, To clear, must write a '1' back.  API takes care of this action.
    //      - Enable the PCS10g interrupts on INTR[1] for LPCS10G_INTR_EN: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR: There is INTR[0-1]: API uses INTR[1]
    //      - Enable INTR_SRC_EN: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN – LPCS10G_INTR.
    //               There is INTR[0-1]: API hard-codes and uses INTR[1] and also hard-codes and uses aggr_intr[0] for all channels
    //      - Enable the PCS10g interrupts on INTR[1] for LPCS10G_INTR_EN
    //      - Enable INTR_SRC_EN (GPIO_CTRL (Dev 0x1E):INTR_CFG_STAT:INTR_SRC_EN[0-3].CH0_INTR1_EN) in PCS block interrupts at aggr_intr[0], all chan
    //               So, by default: API is using: VTSS_10G_PHY_GPIO_AGG_INT_0, User's should avoid using Agg_INT_0 or CHx_INTR1
    //               NOTE: User's should avoid using Agg_INT_0 or CHx_INTR1
    //    - vtss_phy_10g_gpio_mode_set:
    //        - Configure the GPIO for Agg Int and connect to the GPIO output pin (GPIO_No = 34)
    //        - Connect up VTSS_10G_PHY_GPIO_AGG_INT_0 via VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR1_EN,
    //        - Trigger on Input Signal VTSS_10G_GPIO_INTR_SGNL_LPCS_INTR
    // MAC: vtss_phy_10g_mac_event_enable_private
    //      - Enable the HMAC and LMAC Interrupts to catch Errors
    //               Note: Block Interrupts Pending bits are STICKY, To clear, must write a '1' back.  API takes care of this action.
    //      - Enable the HMAC and LMAC interrupts on INTR[1] for HMAC_INTR_EN and LMAC_INTR_EN: VTSS_GPIO_INTR_CTRL_GPIO_INTR_INTR:
    //               There is INTR[0-1]: API uses INTR[1]
    //      - Enable INTR_SRC_EN: VTSS_GPIO_CTRL_INTR_CFG_STAT_INTR_SRC_EN – HMAC_INTR and LMAC_INTR
    //               There is INTR[0-1]: API hard-codes and uses INTR[1] and also hard-codes and uses aggr_intr[0] for all channels
    //      - Enable the PCS10g interrupts on INTR[1] for HMAC_INTR_EN and LMAC_INTR_EN
    //      - Enable INTR_SRC_EN (GPIO_CTRL (Dev 0x1E):INTR_CFG_STAT:INTR_SRC_EN[0-3].CH0_INTR1_EN) HMAC/LMAC Block ints at aggr_intr[0], all chan
    //               So, by default: API is using: VTSS_10G_PHY_GPIO_AGG_INT_0
    //               NOTE: User's should avoid using Agg_INT_0 or CHx_INTR1 as they are already taken and used by the PHY API
    //
    // output -- Channel dependent GPIOs
    // GPIO used for Aggregate Interrupt: #34
    //
    // Note: for each of the 4 ports, the LOPC has Default config for:
    // Port 0: GPIO34; Port 1: GPIO35; Port 2: GPIO36; Port 3: GPIO37
    //
    ///////////////////////////////////////////////////////////////////////////////
BOOL  vtss_appl_malibu_ex_gpio_int_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
    char value_str[255] = {0};
    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    vtss_phy_10g_extnd_event_t ex_ev;
    u16 gpio_no;
    u16 addr = 0;
    u16 dev = 0;
    u32 val32 = 0;

    // This is the GPIO Pin that will be driven
    /* Note: for each of the 4 ports, the LOPC has Default config for: */
    /* Port 0: GPIO34; Port 1: GPIO35; Port 2: GPIO36; Port 3: GPIO37 */
    gpio_no = 34;

    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));

    // Note:
    // 1) The function "vtss_phy_10g_extended_event_enable_set" can be called with the last argument set to FALSE to disable this interrupt
    // 2) Only available interrupts are as follows (AGG_INT_0 should not be used as of API 4.67.05):
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_1
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_2
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_3
    // 3) This function only supports Line 10G PCS event, Host 10G PCS event is not supported
    // 4) To set multiple extended events, it is required to make multiple calls to the functions below

    /*--Events changed in Malibu */
    printf("<<<<--  PMA block interupts -->>>>\n");
    printf("VTSS_PHY_10G_RX_LOS_EV                  0x00000001 \n");/**< PHY RX LOS interrupt - 8256 specific */
    printf("VTSS_PHY_10G_RX_LOL_EV                  0x00000002 \n");/**< PHY RX LOL interrupt - 8256 specific*/
    printf("VTSS_PHY_10G_TX_LOL_EV                  0x00000004 \n");/**< PHY TX LOL interrupt - 8256 specific */
    printf("<<<<--  PCS block interrupts -->>>>\n");
    printf("VTSS_PHY_10G_RX_CHAR_DEC_CNT_THRESH_EV  0x00000010 \n");/**< PHY RX character decode error - 8256 specific */
    printf("VTSS_PHY_10G_TX_CHAR_ENC_CNT_THRESH_EV  0x00000020 \n");/**< PHY TX character encode error count  - 8256 specific */
    printf("VTSS_PHY_10G_RX_BLK_DEC_CNT_THRESH_EV   0x00000040 \n");/**< PHY RX block decode error count  - 8256 specific */
    printf("VTSS_PHY_10G_TX_BLK_ENC_CNT_THRESH_EV   0x00000080 \n");/**< PHY TX block encode error count- 8256 specific */
    printf("VTSS_PHY_10G_RX_SEQ_CNT_THRESH_EV       0x00000100 \n");/**< PHY RX sequencing error count - 8256 specific */
    printf("VTSS_PHY_10G_TX_SEQ_CNT_THRESH_EV       0x00000200 \n");/**< PHY TX sequencing error count - 8256 specific */
    printf("VTSS_PHY_10G_FEC_UNFIXED_CNT_THRESH_EV  0x00000400 \n");/**< PHY KR-FEC uncorrectable block count interrupt - 8256 specific */
    printf("VTSS_PHY_10G_FEC_FIXED_CNT_THRESH_EV    0x00000800 \n");/**< PHY KR-FEC corrected threshold - 8256 specific */
    printf("VTSS_PHY_10G_HIGHBER_EV                 0x00001000 \n");/**< PHY high bit Error - 8256 specific */
    printf("VTSS_PHY_10G_RX_LINK_STAT_EV            0x00002000 \n");/**< PHY Link status up/down interrupt - 8256 specific */
    printf("VTSS_PHY_10G_RX_LINK_STAT_EV            0x00002000 \n");/**< PHY Link status up/down interrupt - 8256 specific */
    printf("VTSS_PHY_10G_GPIO_INT_AGG0_EV           0x00004000 \n");/**< PHY GPIO interrupt on Aggregator0  - 8256 specific */
    printf("VTSS_PHY_10G_GPIO_INT_AGG1_EV           0x00008000 \n");/**< PHY GPIO interrupt on Aggregator1  - 8256 specific */
    printf("VTSS_PHY_10G_GPIO_INT_AGG2_EV           0x00010000 \n");/**< PHY GPIO interrupt on Aggregator2  - 8256 specific */
    printf("VTSS_PHY_10G_GPIO_INT_AGG3_EV           0x00020000 \n");/**< PHY GPIO interrupt on Aggregator3  - 8256 specific */
    printf("VTSS_PHY_1G_LINE_AUTONEG_RESTART_EV     0x00040000 \n");/**< PHY 1G Line side Autoneg restart event */
    printf("VTSS_PHY_1G_HOST_AUTONEG_RESTART_EV     0x00080000 \n");/**< PHY 1G Host side Autoneg restart event  - 8256 specific */
    printf("<<<<--   MAC Block interrupts -->>>> \n");
    printf("VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV    0x00100000 \n");/**< PHY 10G LINE MAC local fault event */
    printf("VTSS_PHY_10G_HOST_MAC_LOCAL_FAULT_EV    0x00400000 \n");/**< PHY 10G HOST MAC local fault event */
    printf("VTSS_PHY_10G_LINE_MAC_REMOTE_FAULT_EV   0x00800000 \n");/**< PHY 10G LINE MAC remote fault event */
    printf("VTSS_PHY_10G_HOST_MAC_REMOTE_FAULT_EV   0x01000000 \n");/**< PHY 10G HOST MAC remote fault event */

#if 1
    /* ***************************************************** */
    /* Now Port 0-3 have LOPC Default config                 */
    /* Note: for each of the 4 ports, the LOPC has Default config for: */
    /* Port 0: GPIO34; Port 1: GPIO35; Port 2: GPIO36; Port 3: GPIO37 */
    /* This is changing the GPIO34 characteristics and re-assigning LOPC for Port 0 */
    /* Configure the GPIO, Switching Enabling the MASK Bit and Clearing the Sticky Bit for the Interrupt */
    /* ***************************************************** */
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_OUT;
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_LINE_LINK;
    gpio_mode.p_gpio = 4;
    gpio_mode.invert_output = 1;       // Since this is Aggr. Int, Determine if Signal is inverted or not

    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: AGG_INT\n", port_no, gpio_no);
      printf("Malibu Error setting AGG_INT Work-around: Set GPIO OUT for AGG_INT configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
    /* ***************************************************** */
#endif

    // ===========================================================================
    // Configure for PMA INTR - This would be for Removal of the SFP.
    // Get the Extended Events
    // ===========================================================================

#define EXAMPE_LINE_PMA_INT
#ifdef EXAMPE_LINE_PMA_INT
    // Get the Extended Events
    if (vtss_phy_10g_extended_event_enable_get(inst, port_no, &ex_ev) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_event_enable_get, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Extended Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
    printf("Current Malibu GPIO Extended Event Enable configuration for port %d, gpio %d, Events: 0x%08x \n", port_no, gpio_no, ex_ev);

    // Example:
    // Enable 10G PCS event
    //ex_ev = VTSS_PHY_10G_RX_LINK_STAT_EV | VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV;
    // Enable 10G PMA event
    // PMA INTR - Seen if the SFP Module is Removed
    ex_ev |= VTSS_PHY_10G_RX_LOS_EV | VTSS_PHY_10G_RX_LOL_EV;

//    For user Selectable Inputs -
//    printf ("Routing GPIO_NO: %d,  Enter Extended Event Enable:  ", gpio_no);
//    memset (&value_str[0], 0, sizeof(value_str));
//    scanf("%s", &value_str[0]);
//    ex_ev = strtol(value_str, NULL, 16);

    printf("\nUpdating/Setting PMA:VTSS_PHY_10G_RX_LOS_EV | VTSS_PHY_10G_RX_LOL_EV for port %d \n", port_no);
    printf("\nMalibu GPIO Extended Event Enable configuration for port %d, gpio %d, Events: 0x%08x \n", port_no, gpio_no, ex_ev);

    if (vtss_phy_10g_extended_event_enable_set(inst, port_no, ex_ev, TRUE) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_extended_event_enable_set, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

#undef PMA_INT_DEBUG
#ifdef PMA_INT_DEBUG
    dev = 0x1;
    //addr = 0xa204;
    //inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    //printf("Read PMA INTR Sticky Status 1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    //addr = 0xa203;
    //inst->init_conf.spi_32bit_read_write(inst, 3, SPI_WR, dev, addr, &val32);
    //printf("Write PMA INTR Sticky Mask 1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    //addr = 0xa204;
    //inst->init_conf.spi_32bit_read_write(inst, 3, SPI_WR, dev, addr, &val32);
    //printf("Write PMA INTR Sticky Status 1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    addr = 0xa203;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("Read PMA INTR Sticky Mask 1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    addr = 0xa204;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("Read PMA INTR Sticky Status 1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
#endif

    // Now configure the GPIO for Agg Int and connect to the GPIO output pin
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    //gpio_mode.mode = VTSS_10G_PHY_GPIO_OUT;
    gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;                    // API hard-Codes Agg_Int0
    gpio_mode.aggr_intrpt = VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR1_EN;  // API hard-codes Agg_Int Ch0, INTR1

    // PMA Block
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_LINE_PMA_INT;  // This has to match the Block for whichever event is programmed
                                                              // VTSS_PHY_10G_RX_LOS_EV | VTSS_PHY_10G_RX_LOL_EV
    // PCS Block
    //gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_LPCS_INTR;  // This has to match the Block for whichever event is programmed ie.:
                                                             // VTSS_PHY_10G_RX_LOS_EV | VTSS_PHY_10G_RX_LOL_EV;
    gpio_mode.p_gpio = 0;  // Valid for Channel INTR (VTSS_10G_PHY_GPIO_OUT), but Meaningless or not used for Agg Intr
    //gpio_mode.invert_output = 1;       // Since this is Aggr. Int, Determine if Signal is inverted or not

    // This is configuruing for PMA INTR - ie. if someone removes the SFP Module
    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: AGG_INT\n", port_no, gpio_no);
      printf("Malibu Error setting AGG_INT Work-around: Set GPIO OUT for AGG_INT configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
#endif  //  End of EXAMPE_LINE_PMA_INT

    // ===========================================================================
    // Now Configure for PCS INTR - This would be for Removal of the Fiber Cable.
    // Get the Extended Events
    // ===========================================================================

#define EXAMPE_LINE_PCS10G_INT
#ifdef EXAMPE_LINE_PCS10G_INT
    if (vtss_phy_10g_extended_event_enable_get(inst, port_no, &ex_ev) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_event_enable_get, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Extended Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    printf("Current Malibu GPIO Extended Event Enable configuration for port %d, gpio %d, Events: 0x%08x \n", port_no, gpio_no, ex_ev);

    // Example:
    // Enable 10G PCS event
    // Note: VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV Event being added
    //ex_ev |= VTSS_PHY_10G_RX_LINK_STAT_EV | VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV;
    ex_ev |= VTSS_PHY_10G_RX_LINK_STAT_EV;

    // Enable 10G PMA event
    //ex_ev = VTSS_PHY_10G_RX_LOS_EV | VTSS_PHY_10G_RX_LOL_EV;

//    printf ("Routing GPIO_NO: %d,  Enter Extended Event Enable:  ", gpio_no);
//    memset (&value_str[0], 0, sizeof(value_str));
//    scanf("%s", &value_str[0]);
//    ex_ev = strtol(value_str, NULL, 10);

    printf("\nUpdating/Setting PCS:VTSS_PHY_10G_RX_LINK_STAT_EV | VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV for port_no %d \n", port_no);
    printf("\nMalibu GPIO Extended Event Enable configuration for port %d, gpio %d, Events: 0x%08x \n", port_no, gpio_no, ex_ev);

    if (vtss_phy_10g_extended_event_enable_set(inst, port_no, ex_ev, TRUE) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_extended_event_enable_set, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

#define PCS10G_INT_DEBUG
#ifdef PCS10G_INT_DEBUG
    dev = 0x3;
    //addr = 0x8e00;
    //inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    //printf("Read PCS INTR Pend 3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    //addr = 0x8e01;
    //inst->init_conf.spi_32bit_read_write(inst, 3, SPI_WR, dev, addr, &val32);
    //printf("Write PCS INTR Mask 3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    //addr = 0x8e00;
    //inst->init_conf.spi_32bit_read_write(inst, 3, SPI_WR, dev, addr, &val32);
    //printf("Write PCS INTR Pend 3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    addr = 0x8e00;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("Read PCS INTR Pend 3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    addr = 0x8e01;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("Read PCS INTR Mask 3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
    addr = 0x8e03;
    inst->init_conf.spi_32bit_read_write(inst, 3, SPI_RD, dev, addr, &val32);
    printf("Read PCS INTR Curr 3x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);
#endif

    // Now configure the GPIO for Agg Int Work-Around, Enabling the MASK Bit and Clearing the Sticky Bit for the Interrupt
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    //gpio_mode.mode = VTSS_10G_PHY_GPIO_OUT;
    gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_0;                    // API hard-Codes Agg_Int0
    gpio_mode.aggr_intrpt = VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR1_EN;  // API hard-codes Agg_Int Ch0, INTR1
    // PMA Block
    //gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_LINE_PMA_INT;  // This has to match the Block for whichever event is programmed
                                                                // VTSS_PHY_10G_RX_LOS_EV | VTSS_PHY_10G_RX_LOL_EV
    // PCS Block
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_LPCS_INTR;  // This has to match the Block for whichever event is programmed ie.:
                                                           // VTSS_PHY_10G_RX_LOS_EV | VTSS_PHY_10G_RX_LOL_EV;
    gpio_mode.p_gpio = 0;  // Valid for Channel INTR, Meaningless for Agg Intr
    //gpio_mode.invert_output = 1;       // Since this is Aggr. Int, Determine if Signal is inverted or not

    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: AGG_INT\n", port_no, gpio_no);
      printf("Malibu Error setting AGG_INT Work-around: Set GPIO OUT for AGG_INT configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
#endif  // EXAMPE_LINE_PCS10G_INT

#if 0
    // Now configure the GPIO for Agg Int function
    // Remember that API already uses: VTSS_10G_PHY_GPIO_AGG_INT_0, VTSS_10G_GPIO_AGGR_INTRPT_CHx_INTR1_EN where x=0,1,2,3 so it is taken
    // This means VTSS_10G_PHY_GPIO_AGG_INT_1, VTSS_10G_PHY_GPIO_AGG_INT_2, VTSS_10G_PHY_GPIO_AGG_INT_3 are available
    // VTSS_10G_GPIO_AGGR_INTRPT_CHx_INTR0_EN where x=0,1,2,3 so it is also available
    // Now configure the GPIO for Agg Int function
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_1;
    gpio_mode.aggr_intrpt = VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR0_EN;
    gpio_mode.invert_output = 0;


    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: AGG_INT\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO AGG_INT configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
#endif

#endif
}

    ///////////////////////////////////////////////////////////////////////////////
    // Per Channel interrupt, using Line 10G PCS status, driving Aggregate Interrupt
    // output -- Channel dependent GPIOs
    // GPIO used for Aggregate Interrupt: #34
    ///////////////////////////////////////////////////////////////////////////////
BOOL  vtss_appl_malibu_gpio_int_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
    char value_str[255] = {0};
    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    vtss_phy_10g_event_t       ev;
    u16 gpio_no;

    gpio_no = 34;

    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));

    // Note:
    // 1) The function "vtss_phy_10g_extended_event_enable_set" can be called with the last argument set to FALSE to disable this interrupt
    // 2) Only available interrupts are as follows (AGG_INT_0 should not be used as of API 4.67.05):
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_1
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_2
    //    -- gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_3
    // 3) This function only supports Line 10G PCS event, Host 10G PCS event is not supported
    // 4) To set multiple extended events, it is required to make multiple calls to the functions below

    /** \brief Event source identification mask values */
    printf("VTSS_PHY_10G_LINK_LOS_EV            0x00000001 \n"); /**< PHY Link Los interrupt - only on 8486 */
    printf("VTSS_PHY_10G_RX_LOL_EV              0x00000002 \n"); /**< PHY RXLOL interrupt - only on 8488 */
    printf("VTSS_PHY_10G_TX_LOL_EV              0x00000004 \n"); /**< PHY TXLOL interrupt - only on 8488 */
    printf("VTSS_PHY_10G_LOPC_EV                0x00000008 \n"); /**< PHY LOPC interrupt - only on 8488 */
    printf("VTSS_PHY_10G_HIGH_BER_EV            0x00000010 \n"); /**< PHY HIGH_BER interrupt - only on 8488 */
    printf("VTSS_PHY_10G_MODULE_STAT_EV         0x00000020 \n"); /**< PHY MODULE_STAT interrupt - only on 8488 */
    printf("VTSS_PHY_10G_PCS_RECEIVE_FAULT_EV   0x00000040 \n"); /**< PHY PCS_RECEIVE_FAULT interrupt - only on 8488 */
#ifdef VTSS_FEATURE_WIS
    printf("VTSS_PHY_EWIS_SEF_EV                0x00000080 \n"); /**< SEF has changed state - only for 8488 */
    printf("VTSS_PHY_EWIS_FPLM_EV               0x00000100 \n"); /**< far-end (PLM-P) / (LCDP) - only for 8488 */
    printf("VTSS_PHY_EWIS_FAIS_EV               0x00000200 \n"); /**< far-end (AIS-P) / (LOP) - only for 8488 */
    printf("VTSS_PHY_EWIS_LOF_EV                0x00000400 \n"); /**< Loss of Frame (LOF) - only for 8488 */
    printf("VTSS_PHY_EWIS_RDIL_EV               0x00000800 \n"); /**< Line Remote Defect Indication (RDI-L) - only for 8488 */
    printf("VTSS_PHY_EWIS_AISL_EV               0x00001000 \n"); /**< Line Alarm Indication Signal (AIS-L) - only for 8488 */
    printf("VTSS_PHY_EWIS_LCDP_EV               0x00002000 \n"); /**< Loss of Code-group Delineation (LCD-P) - only for 8488 */
    printf("VTSS_PHY_EWIS_PLMP_EV               0x00004000 \n"); /**< Path Label Mismatch (PLMP) - only for 8488 */
    printf("VTSS_PHY_EWIS_AISP_EV               0x00008000 \n"); /**< Path Alarm Indication Signal (AIS-P) - only for 8488 */
    printf("VTSS_PHY_EWIS_LOPP_EV               0x00010000 \n"); /**< Path Loss of Pointer (LOP-P) - only for 8488 */
    printf("VTSS_PHY_EWIS_UNEQP_EV              0x00020000 \n"); /**< Unequiped Path (UNEQ-P) - only for 8488 */
    printf("VTSS_PHY_EWIS_FEUNEQP_EV            0x00040000 \n"); /**< Far-end Unequiped Path (UNEQ-P) - only for 8488 */
    printf("VTSS_PHY_EWIS_FERDIP_EV             0x00080000 \n"); /**< Far-end Path Remote Defect Identifier (RDI-P) - only for 8488 */
    printf("VTSS_PHY_EWIS_REIL_EV               0x00100000 \n"); /**< Line Remote Error Indication (REI-L) - only for 8488 */
    printf("VTSS_PHY_EWIS_REIP_EV               0x00200000 \n"); /**< Path Remote Error Indication (REI-P) - only for 8488 */
    printf("VTSS_PHY_EWIS_B1_NZ_EV              0x00400000 \n"); /**< PMTICK B1 BIP (B1_ERR_CNT) not zero - only for 8488 */
    printf("VTSS_PHY_EWIS_B2_NZ_EV              0x00800000 \n"); /**< PMTICK B2 BIP (B1_ERR_CNT) not zero - only for 8488 */
    printf("VTSS_PHY_EWIS_B3_NZ_EV              0x01000000 \n"); /**< PMTICK B3 BIP (B1_ERR_CNT) not zero - only for 8488 */
    printf("VTSS_PHY_EWIS_REIL_NZ_EV            0x02000000 \n"); /**< PMTICK REI-L (REIL_ERR_CNT) not zero - only for 8488 */
    printf("VTSS_PHY_EWIS_REIP_NZ_EV            0x04000000 \n"); /**< PMTICK REI-P (REIP_ERR_CNT) not zero - only for 8488 */
    printf("VTSS_PHY_EWIS_B1_THRESH_EV          0x08000000 \n"); /**< B1_THRESH_ERR - only for 8488 */
    printf("VTSS_PHY_EWIS_B2_THRESH_EV          0x10000000 \n"); /**< B2_THRESH_ERR - only for 8488 */
    printf("VTSS_PHY_EWIS_B3_THRESH_EV          0x20000000 \n"); /**< B3_THRESH_ERR - only for 8488 */
    printf("VTSS_PHY_EWIS_REIL_THRESH_EV        0x40000000 \n"); /**< REIL_THRESH_ERR - only for 8488 */
    printf("VTSS_PHY_EWIS_REIP_THRESH_EV        0x80000000 \n"); /**< REIp_THRESH_ERR - only for 8488 */
#endif /* VTSS_FEATURE_WIS */

    // Get the Events
    if (vtss_phy_10g_event_enable_get(inst, port_no, &ev) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_event_enable_get, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    printf("Current Malibu GPIO Event Enable configuration for port %d, gpio %d, Events: 0x%04x \n", port_no, gpio_no, ev);

    printf ("Routing GPIO_NO: %d,  Enter Event Enable:  ", gpio_no);
    memset (&value_str[0], 0, sizeof(value_str));
    scanf("%s", &value_str[0]);
    ev = strtol(value_str, NULL, 10);

    ev = VTSS_PHY_10G_LINK_LOS_EV;
    printf("\nOVER-RIDE, VTSS_PHY_10G_LINK_LOS_EV port %d, gpio %d, Events: 0x%04x \n", port_no, gpio_no, ev);

    // Example:
    //ex_ev = VTSS_PHY_10G_RX_LINK_STAT_EV | VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV;

    printf("\nUpdating/Setting Malibu GPIO Event Enable configuration for port %d, gpio %d, Events: 0x%04x \n", port_no, gpio_no, ev);

    // Enable 10G PCS event
    //ex_ev = VTSS_PHY_10G_RX_LINK_STAT_EV;

    if (vtss_phy_10g_event_enable_set(inst, port_no, ev, TRUE) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_event_enable_set, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    // Now configure the GPIO for Agg Int function
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_1;
    gpio_mode.aggr_intrpt = VTSS_10G_GPIO_AGGR_INTRPT_CH0_INTR0_EN;
    gpio_mode.use_as_intrpt = 0;
    //gpio_mode.p_gpio = 34; // 34 = rx_pcs_pause_o  GPIO_INTR_CTRL, Dev:0x1, chreg;GPIO_INTR:GPIO0_OUT.SEL0
    gpio_mode.p_gpio = 22;   // 22 = lpcs10g_intr    GPIO_INTR_CTRL, Dev:0x1, chreg;GPIO_INTR:GPIO0_OUT.SEL0
  //gpio_mode.p_gpio = 24;   // 24 = line_pcs1g_intr GPIO_INTR_CTRL, Dev:0x1, chreg;GPIO_INTR:GPIO0_OUT.SEL0
    gpio_mode.invert_output = 0;


    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: AGG_INT\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO AGG_INT configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
#endif
}

BOOL  vtss_appl_malibu_gpio_i2c_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    u16 gpio_no;
    BOOL value;
    // GPIO as I2C Master Interface for SFP+ I2C register readout
    // GPIO used: #2/#3 (Ch0_SCL and CH0_SDA resp), #10/#11 (Ch1_SCL and CH1_SDA resp) and so on
    //
    // Notes:
    // 1) This GPIO allocation is per channel (A Data/Clk pair per channel),
    // 2) Based on this allocation, the I2C read/write functions send the commands
    //    out on those GPIOs assigned to that particular channel.
    // 3) Slave_ID is fixed at 0x50 (as per the SFP+ Standard, SFF-8472).
    // 4) The two-wire serial master does not support read-increment instructions.

    // First, assign GPIOs as I2C Master for a particular channel
    printf("\nMalibu Reading SFP+ I2C registers port %d, gpio %d \n", port_no, gpio_no);

    /* ********************************************************** */
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_OUT;
    gpio_mode.p_gpio = 0; // GPIO_INTR_CTRL (Dev:1 ch_reg):GPIO_INTR:GPIO0_OUT.SEL0
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_I2C_MSTR_DATA_OUT;
    /* Note: For Port_no=3, this GPIO conflicts with CHAR_BOARD LED config  */
    gpio_no = 2 + (port_no*8);

    printf("\nMalibu GPIO Output: I2C Master DATA configuration for port %d, gpio %d \n", port_no, gpio_no);
    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: I2C_MSTR_DATA_OUT\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Output configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_OUT;
    gpio_mode.p_gpio = 1; // GPIO_INTR_CTRL (Dev:1 ch_reg):GPIO_INTR:GPIO0_OUT.SEL0
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_I2C_MSTR_CLK_OUT;
    /* Note: For Port_no=3, this GPIO conflicts with CHAR_BOARD LED config  */
    gpio_no = 3 + (port_no*8);

    printf("\nMalibu GPIO Output: I2C Master CLK configuration for port %d, gpio %d \n", port_no, gpio_no);
    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: I2C_MSTR_CLK_OUT\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Output configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    /* ********************************************************** */

    // Now call the read or write function with the relevant address and data
    u16 address = 0x0;
    u16 data;

    for (address = 0; address < 16; address++) {
      if (vtss_phy_10g_i2c_read(inst, port_no, address, &data) != VTSS_RC_OK) {
	T_E("vtss_phy_10g_i2c_read, port %d, gpio %d, address = 0x%X\n", port_no, gpio_no, address);
	printf("Malibu Error reading I2C register on SFP+ module for port %d, gpio %d \n", port_no, gpio_no);
      } else {
	printf("Malibu reading I2C register @ addr = %d: value = 0x%X \n", address, data);
      }
    }

    address = 0x3E;
    if (vtss_phy_10g_i2c_read(inst, port_no, address, &data) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_i2c_read, port %d, gpio %d, address = 0x%X\n", port_no, gpio_no, address);
      printf("Malibu Error reading I2C register on SFP+ module for port %d, gpio %d \n", port_no, gpio_no);
    } else {
      printf("Malibu reading I2C register @ addr = %d: value = 0x%X \n", address, data);
    }

    data = 0x100;
    if (vtss_phy_10g_i2c_write(inst, port_no, address, &data) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_i2c_write, port %d, gpio %d, address = 0x%X, data = 0x%X\n", port_no, gpio_no, address, data);
      printf("Malibu Error writing I2C register on SFP+ module for port %d, gpio %d \n", port_no, gpio_no);
    }

    if (vtss_phy_10g_i2c_read(inst, port_no, address, &data) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_i2c_read, port %d, gpio %d, address = 0x%X\n", port_no, gpio_no, address);
      printf("Malibu Error reading I2C register on SFP+ module for port %d, gpio %d \n", port_no, gpio_no);
    } else {
      printf("Malibu reading I2C register @ addr = %d: value = 0x%X \n", address, data);
    }

    /* ********************************************************** */

#endif
}


BOOL  vtss_appl_malibu_gpio_out_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
    /* ********************************************************** */
    /* *******************    GPIO      ************************* */
    /* ********************************************************** */

    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    u32 val32 = 0;
    u16 gpio_no;
    BOOL value;

    /* ********************************************************** */
    // GPIO Output functionality
    // GPIO_0 -> GPIO_7  This repeats for each of the 4 ports.
    // In this Example:
    // 0 = GPIO output 0 from channel 0   - CH0_RS0
    // 1 = GPIO output 1 from channel 0   - N/A
    // 2 = GPIO output 2 from channel 0   - CH0_SCL - I2C Master for SFP+
    // 3 = GPIO output 3 from channel 0   - CH0_SDA - I2C Master for SFP+
    // 4 = GPIO output 4 from channel 0   - CH0_TX_DIS
    // 5 = GPIO output 5 from channel 0   - N/A
    // 6 = GPIO output 6 from channel 0   - N/A
    // 7 = GPIO output 7 from channel 0   - CH0_LINK_UP
    //
    // 8 = GPIO output 0 from channel 1   - CH1_RS0
    // 9 = GPIO output 1 from channel 1   - N/A
    // 10 = GPIO output 2 from channel 1  - CH1_SCL - I2C Master for SFP+
    // 11 = GPIO output 3 from channel 1  - CH1_SDA - I2C Master for SFP+
    // 12 = GPIO output 4 from channel 1  - CH1_TX_DIS
    // 13 = GPIO output 5 from channel 1  - N/A
    // 14 = GPIO output 6 from channel 1  - N/A
    // 15 = GPIO output 7 from channel 1  - CH1_LINK_UP
    // .....
    /* ********************************************************** */

#if 1

    // GPIO output driving High/Low signals (can be used for TX_DISABLE, RS0)

    /* ********************************************************** */
    // GPIO used: #0 for Ch0 (CH0_RS0), #8 for Ch1 and so on
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_DRIVE_HIGH;
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_NONE;
    gpio_no = 0 + (port_no*8);

    printf("\nMalibu GPIO Output: Driving HIGH configuration for port %d, gpio %d \n", port_no, gpio_no);
    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: DRIVE_HIGH/LOW (RS0)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Output configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    /* ********************************************************** */

    // GPIO used: #4 for Ch0 (CH0_TX_DIS), #12 for Ch1 and so on
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_DRIVE_LOW;
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_NONE;

    /* Note: For Port_no=3, this GPIO conflicts with CHAR_BOARD LED config */
    gpio_no = 4 + (port_no*8);

    printf("\nMalibu GPIO Output: Driving LOW configuration for port %d, gpio %d \n", port_no, gpio_no);
    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: DRIVE_HIGH/LOW (TX_DISABLE)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Output configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    /* ********************************************************** */

#endif

#if 0
    /* ********************************************************** */
    // GPIO output driving 1G/10G link status
    // GPIO used: #7 (CH0_LINK_UP), #15 (CH1_LINK_UP) and so on
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_OUT;
    gpio_mode.p_gpio = 2;
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_LINE_LINK;
    gpio_no = 7 + (port_no*8);

    printf("\nMalibu GPIO Output: 1G/10G link status configuration for port %d, gpio %d \n", port_no, gpio_no);
    if (vtss_phy_10g_gpio_mode_set(board->inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: DRIVE_HIGH/LOW\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Output configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
    /* ********************************************************** */
#endif

#if 1
    // GPIO output driving Activity LEDs
    // GPIO used: #36(CH0_ACTIVITY), #37 (CH1_ACTIVITY) and so on
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_OUT;
    gpio_mode.p_gpio = 3; /* HH:  virtual GPIO reference applies to output mode only - will be numbered 0-7 corresponding to registers */
    gpio_mode.in_sig = VTSS_10G_GPIO_INTR_SGNL_LED_TX; /* HH:  this commands corresponding GPIO_INTR_CTRL register[p_gpio index] to route a particular
														GPIO function.  see GPIO_INTR_CTRL register in VML/CML for the code values. */
														/*HH:  note w/r/t the vtss_gpio_10g_gpio_mode_t struct, that in_sig is for an *internal* signal (not
														an input), and in_sig only applies to GPIO_OUT (output) mode.  in_sig n/a GPIO_IN mode. */
#if defined (MALIBU_CHAR_BOARD)
    // Note: The Malibu Device has Dedicated Pins for PPS_0 -> PPS_3.  GPIO's are not used for PPS_x signals.
    // Malibu Char board has an issue in this area and these GPIO's are used instead of GPIO's 36->39 to drive LED's
    // 25 = GPIO output 1 from channel 3
    // 26 = GPIO output 2 from channel 3
    // 27 = GPIO output 3 from channel 3
    // 28 = GPIO output 4 from channel 3
    gpio_no = 25 + (port_no); // Only for CHAR Board
#else
    // Note: The Malibu Device has Dedicated Pins for PPS_0 -> PPS_3.  GPIO's are not used for PPS_x signals.
    // While it is possible, it is not necessary.  For this Example, GPIO's 36->39 will be used to drive LED's
    // 36 = PPS_0 from ip1588
    // 37 = PPS_1 from ip1588
    // 38 = PPS_2 from ip1588
    // 39 = PPS_3 from ip1588
    gpio_no = 36 + (port_no); // Per Datasheet
#endif

    // Tx/Rx LED mode setup -- needs direct register access

    // VTSS_F_LINE_PMA_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_MODE:
    // 0: Tx Link Status, 2(DEFAULT): Tx link + Tx data activity, 3: Tx Link + (Tx+Rx) data activity

    // VTSS_F_LINE_PMA_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_RX_LED_MODE:
    // 0: Rx Link Status, 2(DEFAULT): Rx link + Rx data activity, 3: Rx Link + (Tx+Rx) data activity

    // VTSS_F_LINE_PMA_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_BLINK_TIME:
    // 0: 50ms interval, 1(DEFAULT): 100 ms interval

    // VTSS_F_LINE_PMA_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_RX_LED_BLINK_TIME:
    // 0: 50ms interval, 1(DEFAULT): 100 ms interval

    inst->init_conf.spi_32bit_read_write(inst, port_no, SPI_RD, 0x1, 0xA100, &val32);
    val32 |= (3 << 5);
    inst->init_conf.spi_32bit_read_write(inst, port_no, SPI_WR, 0x1, 0xA100, &val32);
    // CSR_COLD_WRM(port_no, VTSS_LINE_PMA_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2,
    // 		 VTSS_F_LINE_PMA_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_MODE(3),
    // 		 VTSS_M_LINE_PMA_Vendor_Specific_PMA_Control_2_Vendor_Specific_PMA_Control_2_TX_LED_MODE);

    printf("\nMalibu GPIO Output: Activity LED configuration for port %d, gpio %d \n", port_no, gpio_no);
    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: Activity LED mode\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Output configuration for port %d, gpio %d \n", port_no, gpio_no);
    }
#endif
}

BOOL  vtss_appl_malibu_gpio_in_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
    /* ********************************************************** */
    /* *******************    GPIO      ************************* */
    /* ********************************************************** */

    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    u16 gpio_no;
    BOOL value;

    /* ********************************************************** */
    // GPIO Input functionality
    /* ********************************************************** */


#if 1
    // GPIO as Input to be used for Line LOPC or RxLOS

    // GPIO used: #6 (CH0_RXLOS), #14 (CH1_RXLOS) and so on
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));

    gpio_mode.mode = VTSS_10G_PHY_GPIO_IN;
    gpio_mode.input = VTSS_10G_GPIO_INPUT_LINE_LOPC;
    gpio_no = 6 + (port_no*8);

    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: INPUT (LINE_LOPC)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Input configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    if (vtss_phy_10g_gpio_read(inst, port_no, gpio_no, &value) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_read, port %d, gpio %d, mode: INPUT (LINE_LOPC)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Read for port %d, gpio %d \n", port_no, gpio_no);
    }
    printf("GPIO %d value = %d\n", gpio_no, value);
#endif

#if 1
    // GPIO used: #1 (Ch0_MOD_ABS), #9 (Ch1_MOD_ABS) and so on
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));

    gpio_mode.mode = VTSS_10G_PHY_GPIO_IN;
    gpio_mode.input = VTSS_10G_GPIO_INPUT_NONE;
    /* Note: For Port_no=3, this GPIO conflicts with CHAR_BOARD LED config  */
    gpio_no = 1 + (port_no*8);

    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: INPUT (MOD_ABS)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Input configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    if (vtss_phy_10g_gpio_read(inst, port_no, gpio_no, &value) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_read, port %d, gpio %d, mode: INPUT (MOD_ABS)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Read for port %d, gpio %d \n", port_no, gpio_no);
    }
    printf("GPIO %d value = %d\n", gpio_no, value);

    // GPIO used: #5 (Ch0_TX_FAULT), #13 (Ch1_TX_FAULT) and so on
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));

    gpio_mode.mode = VTSS_10G_PHY_GPIO_IN;
    gpio_mode.input = VTSS_10G_GPIO_INPUT_NONE;
    gpio_no = 5 + (port_no*8);

    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: INPUT (TX_FAULT)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Input configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    if (vtss_phy_10g_gpio_read(inst, port_no, gpio_no, &value) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_read, port %d, gpio %d, mode: INPUT (TX_FAULT)\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Read for port %d, gpio %d \n", port_no, gpio_no);
    }
    printf("GPIO %d value = %d\n", gpio_no, value);
#endif
}


/* ================================================================= *
 *  START_OF_MAIN
 * ================================================================= */
int main(int argc, const char **argv) {
  vtss_rc                 rc;
  int                     phy_mode = 0;
  vtss_appl_board_t       *board;
  vtss_inst_create_t      create;
  vtss_port_no_t          port_no=0;
  vtss_port_no_t          phy_base_port=0;
  vtss_init_conf_t        init_conf;
  vtss_port_interface_t   mac_if;
  char value_str[255] = {0};
  char command[255] = {0};
  char port_no_str[255] = {0};
  BOOL enable_1588 = FALSE;
#ifdef EVAL_BOARD_1588_CAPABLE
  vtss_phy_ts_eng_init_conf_t     ts_init_conf;
#endif
  vtss_port_no_t ing_port_no = 0;
  vtss_port_no_t egr_port_no = 0;
  u32 val32 = 0;
  u16 value = 0;

  // Setup trace level for PHY group -- in increasing order of logging messages
  // VTSS_TRACE_LEVEL_NONE
  // VTSS_TRACE_LEVEL_ERROR
  // VTSS_TRACE_LEVEL_INFO
  // VTSS_TRACE_LEVEL_DEBUG
  // VTSS_TRACE_LEVEL_NOISE
  vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_ERROR;
  vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_ERROR;
  printf ("//Default AIL TRACE Level : VTSS_TRACE_LEVEL_ERROR\n" );
  printf ("//Default CIL TRACE Level : VTSS_TRACE_LEVEL_ERROR\n" );
  //vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_DEBUG;
  //printf ("//Default AIL TRACE Level : VTSS_TRACE_LEVEL_DEBUG\n" );

  // Setup trace level for PHY group - vtss_appl_trace_conf is a global
  vtss_trace_conf_set(VTSS_TRACE_GROUP_PHY, &vtss_appl_trace_conf);


#ifdef _INCLUDE_DEBUG_FILE_PRINT_
  fp = fopen("phychar.log", "w");
#endif

  // In this case we only have one board. Assign point to the board definition
  board = &board_table[0];

  memset (&board_table[0], 0, (sizeof(vtss_appl_board_t) * MAX_BOARD_INSTANCES));

  printf ("//Default Setup Assumptions: \n" );
  printf ("//Board has Power Applied prior to Demo start \n" );
  // printf ("//The PHY Initialization Timing delays have been satisfied \n" );
  printf ("//Pwr Supply/Voltages Stable, Ref Clk Stable, Ref & PLL Stable \n\n" );

// #ifdef _INCLUDE_DEBUG_TERM_PRINT_
//   printf ("Enable Live Debug TERM Output? (Y/N)  \n");
//   memset (&value_str[0], 0, sizeof(value_str));
//   scanf("%s", &value_str[0]);
//
//   if (value_str [0] == 'y' || value_str [0] == 'Y' ) {
//     live_debug_enable = TRUE;
//   }
// #endif

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
    printf ("//Comment: Board being initialized\n");
  }

  if (vtss_init_conf_set(board->inst, &init_conf) == VTSS_RC_ERROR) {
        T_E("Could not initialize");
        return 1;
  }

  if (board->inst->init_conf.spi_32bit_read_write) {
      vtss_appl_malibu_spi_io_test(board->inst, port_no);
  }

#ifdef  MALIBU_CHAR_BOARD
  printf ("Setup of VSC825x - MALIBU Char Board \n");
  mac_if = VTSS_PORT_INTERFACE_SFI; // vtss_api/include/vtss/api/types.h used in 10G?

#endif

  /* ****************************************************** */
  /* USER CONFIGURATION                                     */
  /* ****************************************************** */

#if defined(VTSS_CHIP_10G_PHY)
  vtss_phy_10g_init_parm_t  init_parm;
  vtss_phy_10g_mode_t     oper_mode;

  printf("VTSS_PORT_NO_START = %d\n", VTSS_PORT_NO_START);
  printf("VTSS_PORTS = %d\n", VTSS_PORTS);
  fflush(stdout);

  printf("\nBoard Info --> \n");
  printf("Board name: %s\n", board->descr);
  printf("port_no = %d\n", port_no); fflush(stdout);
  printf("Board Target: 0x%X\n", board->target); fflush(stdout);

  printf("Board Inst: %p\n\n", board->inst); fflush(stdout);

  /* ********************************************************** */
  /* ***************    Basic Bring-up      ******************* */
  /* ********************************************************** */


  printf ("Configuring Operating MODE for ALL Ports; 0=MODE_10GLAN;  1=MODE_1GLAN;  2=MODE_10GWAN, Enter Oper_MODE (0/1/2): ");
  memset (&value_str[0], 0, sizeof(value_str));
  scanf("%s", &value_str[0]);
  phy_mode = atoi(value_str);

  printf ("\n");

  switch (phy_mode) {
  case PHY_MODE_10G_LAN:
      printf ("Operating MODE for ALL Ports: 0=MODE_10GLAN\n");
      break;
  case PHY_MODE_1G_LAN:
      printf ("Operating MODE for ALL Ports: 1=MODE_1GLAN\n");
      break;
  case PHY_MODE_10G_WAN:
      printf ("Operating MODE for ALL Ports: 2=MODE_10GWAN\n");
      break;
  default:
      printf ("Operating MODE ALL Ports INVALID, Setting 10G_LAN Mode \n");
      phy_mode = 0;
  }

  // Undefine modes for each port
#undef MODE_10GLAN
#undef MODE_1GLAN
#undef MODE_10GWAN

#define MODE_10GLAN

  // This loop should always start from the physical Ch0 of the device
  for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {
    printf("\nConfiguring port %d\n", port_no);


    // define modes for each port
    // Notes:
    // 1) If the data rate mode is the same for all channels then there is no need
    //    to define the MODE_* flag again,
    // 2) In case, the any channel is operating in a different mode, then the MODE_*
    //    flag used by the previous channel would have to be undefined first, before
    //    defining the MODE_* variable required by the current channel

    // All ports in 10G LAN mode
    if (port_no == VTSS_PORT_NO_START) {
      // #define MODE_1GLAN
    } else if (port_no == (VTSS_PORT_NO_START+1)) {
      // #define MODE_10GLAN
      // #define MODE_1GLAN
    } else if (port_no == (VTSS_PORT_NO_START+2)) {
      // #define MODE_10GLAN
      // #define MODE_1GLAN
    } else if (port_no == (VTSS_PORT_NO_START+3)) {
      // #define MODE_10GLAN
      // #define MODE_1GLAN
    }

    // Ports 0 and 2 in 10G LAN, while ports 1 and 3 are in 1G LAN mode
    // if (port_no == VTSS_PORT_NO_START) {
    //   #define MODE_10GLAN
    // } else if (port_no == (VTSS_PORT_NO_START+1)) {
    //   #undef MODE_10GLAN
    //   #define MODE_1GLAN
    // } else if (port_no == (VTSS_PORT_NO_START+2)) {
    //   #undef MODE_1GLAN
    //   #define MODE_10GLAN
    // } else if (port_no == (VTSS_PORT_NO_START+3)) {
    //   #undef MODE_10GLAN
    //   #define MODE_1GLAN
    // }

    memset(&oper_mode, 0, sizeof(vtss_phy_10g_mode_t));

    init_parm.channel_conf = VTSS_CHANNEL_AUTO;
    if(vtss_phy_10g_init(board->inst, port_no, &init_parm) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_init failed, port %d\n", port_no);
      printf("vtss_phy_10g_init failed, port %d\n", port_no);
    }

    // if (vtss_phy_10g_mode_get(board->inst, port_no, &oper_mode) != VTSS_RC_OK) {
    //   T_E("vtss_phy_10g_mode_get failed, port %d\n", port_no);
    //   printf("vtss_phy_10g_mode_get failed, port %d\n", port_no);
    // }

    switch (phy_mode) {
    case PHY_MODE_10G_LAN:   /* 0=MODE_10GLAN */
        oper_mode.oper_mode = VTSS_PHY_LAN_MODE;
        oper_mode.interface = VTSS_PHY_SFI_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // h_media/l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)

        // Assuming SR/LR limiting module on the line side and long traces (> 10 in)
        // or backplane on the host side
        oper_mode.h_media = VTSS_MEDIA_TYPE_KR_SC;
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;
        // oper_mode.l_media = VTSS_MEDIA_TYPE_KR_SC;

        break;

    case PHY_MODE_1G_LAN: /* 1=MODE_1GLAN */
        oper_mode.oper_mode = VTSS_PHY_1G_MODE;
        oper_mode.interface = VTSS_PHY_SFI_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // h_media/l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)

        // Always use these media settings for 1G LAN data rates
        oper_mode.h_media = VTSS_MEDIA_TYPE_SR2_SC;
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;
        // oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;

        break;

    case PHY_MODE_10G_WAN: /* 2=MODE_10GWAN */
        oper_mode.oper_mode = VTSS_PHY_WAN_MODE;
        oper_mode.interface = VTSS_PHY_SFI_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // h_media/l_media options:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)

        // Assuming SR/LR limiting module on the line side and long traces (> 10 in)
        // or backplane on the host side
        oper_mode.h_media = VTSS_MEDIA_TYPE_KR_SC;
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;
        // oper_mode.l_media = VTSS_MEDIA_TYPE_KR_SC;

        break;

    default:
        // Error
        T_E("vtss_phy_10g_mode_set config, port %d\n", port_no);
        printf("vtss_phy_10g_mode_set config failed, port %d -- Improper Mode Selection!\n", port_no);
    }

    // Invert Polarity of Line/Host Tx/Rx
    oper_mode.polarity.line_rx = FALSE;
    oper_mode.polarity.line_tx = FALSE;
    oper_mode.polarity.host_rx = FALSE;
    oper_mode.polarity.host_tx = FALSE;
    // H/LREFCLK is_high_amp :
    // --> TRUE (1100mV to 2400mV diff swing)
    // --> FALSE (200mV to 1200mV diff swing)
    oper_mode.h_clk_src.is_high_amp = TRUE;
    oper_mode.l_clk_src.is_high_amp = TRUE;

    /* Setup Port */
    printf("vtss_phy_10g_mode_set: port %d, oper_mode = %d\n", port_no, oper_mode.oper_mode);

    if (vtss_phy_10g_mode_set(board->inst, port_no, &oper_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_mode_set failed, port %d\n", port_no);
      printf("vtss_phy_10g_mode_set failed, port %d\n", port_no);
    }

    /* MODE_1GLAN */
    if (phy_mode == PHY_MODE_1G_LAN) {
        // 1G Auto Negotiation
        printf("\nConfiguring 1G Auto Negotiation, port %d:\n", port_no);

        vtss_phy_10g_clause_37_control_t ctrl;
        memset(&ctrl, 0, sizeof(vtss_phy_10g_clause_37_control_t));
        ctrl.enable = TRUE;
        ctrl.line = TRUE;
        ctrl.host = FALSE;
        ctrl.l_h = FALSE;
        ctrl.advertisement.fdx = TRUE;
        ctrl.advertisement.hdx = FALSE;
        ctrl.advertisement.symmetric_pause = FALSE; /* Enable or Disable Flowcontrol */
        ctrl.advertisement.asymmetric_pause = FALSE; /* Enable or Disable Flowcontrol */
        ctrl.advertisement.remote_fault =  FALSE;
        ctrl.advertisement.acknowledge =  FALSE;
        ctrl.advertisement.next_page =  FALSE;
        if (vtss_phy_10g_clause_37_control_set(board->inst, port_no, &ctrl) != VTSS_RC_OK) {
          T_E("vtss_phy_10g_clause_37_control_set failed, port %d\n", port_no);
          printf("vtss_phy_10g_clause_37_control_set failed, port %d\n", port_no);
        }
    }
  }  // End of For loop looping through channels for basic configuration

  // Wait for the chip to stablize -- about 1 sec
  uint msec = 1000;
  struct timespec ts;						  \
  ts.tv_sec = msec / 1000;					  \
  ts.tv_nsec = (msec % 1000) * 1000000;				  \
  while(nanosleep(&ts, &ts) == -1 && errno == EINTR) {		  \
  }

  /* ********************************************************** */
  /* **************   Additional Features      **************** */
  /* ********************************************************** */

  for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {

#if 1
    /* ********************************************************** */
    /* ******    DEBUG REG PRINT OUT          ******************* */
    /* ********************************************************** */

    vtss_debug_printf_t pr = (vtss_debug_printf_t) printf;
    printf("\n==========================================================\n");
    printf("Debug Reg Dump for Port %d\n", port_no);
    if (vtss_phy_10g_debug_register_dump(board->inst, pr, FALSE, port_no) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
      printf("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
    }
    printf("==========================================================\n");
#endif

    /* ********************************************************** */
    /* *******************    GPIO      ************************* */
    /* ********************************************************** */

    /* ********************************************************** */
    // GPIO Output functionality
    /* ********************************************************** */

    vtss_appl_malibu_gpio_out_set(board->inst, port_no);

    /* ********************************************************** */
    // GPIO I2C Output functionality
    /* ********************************************************** */

    //vtss_appl_malibu_gpio_i2c_set(board->inst, port_no);

    /* ********************************************************** */
    // GPIO Input functionality
    /* ********************************************************** */

    //vtss_appl_malibu_gpio_in_set(board->inst, port_no);

  } // End of For loop looping through channels

  fflush(stdout);

    while (1) {
        {
            printf (" *************************************\n");
            printf (" The following commands are supported:\n");
#ifdef _INCLUDE_DEBUG_TERM_PRINT_
            printf (" debug  <port_no>  - Sets PHY API to output Debug \n");
#endif
            printf (" dump <port_no> - Dump Reg 0-31 Pages:std/ext1/ext2/ext3/gpio/1588/macsec/1588_reg/macsec_rng/ext_rng for Port \n");
            printf (" rdext <port_no> <page> <addr> - Read Extended Page - where page=1,2,3,4,0x10,0x1588,0x2A30,0x52B5 - <addr> 0-31 \n");
            printf (" wrext <port_no> <page> <addr> <value> - Write Ext Page - page=1,2,3,4,0x10,0x1588,0x2A30,0x52B5 - <addr> 0-31 - Value MUST be in hex \n");
            printf (" ----------------------------------------  |  ------------------------------------------------------- \n");
            printf (" spird    <port_no> <dev> <addr>           |  spiwr       <port_no> <dev> <addr> <value> - Value MUST be in hex\n");
            printf (" getmedia <port_no> - Get Media i/f        |  setmedia    <port_no> - Set Media I/F for port \n");
            printf (" getmac   <port_no> - Get MAC i/f          |  setmac      <port_no> - Set MAC I/F for port \n");
            printf (" ----------------------------------------  |  ------------------------------------------------------- \n");
            printf (" 10g_kr   <port_no> - 10G Base KR          |  synce       <port_no> - Sync-E Config   \n");
            printf (" prbs     <port_no> - PRBS                 |  obuf        <port_no> - Output Buf Control  \n");
            printf (" status   <port_no> - Rtn PHY Link status  |  vscope      <port_no> - Config for VSCOPE FAST/FULL SCAN \n");
            printf (" lpback   <port_no> - Set PHY Loopback     |                                                           \n");
            printf (" int10g   <port_no> - Set 10g Interuppts   |  poll10g     <port_no>                                    \n");
            printf (" ex_int   <port_no> - Set Ext Interuppts   |  ex_poll     <port_no>                                    \n");
            printf (" ts_int   <port_no> - Set TS Interuppts    |  ts_poll     <port_no>                                    \n");
            printf (" macsec   <port_no> - MACSEC Block config  |  1588        <port_no> - 1588 Block Config   \n");
            printf (" dbgdump  <port_no> - Reg Dump             |                                                \n");

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
            printf (" status <port_no>  - Return PHY API status \n");
            printf (" stats  <port_no>  - Return PHY API Statistics \n");
            printf ("\n");
            printf ("> ");
            continue;

        } else if (strcmp(command, "spird")  == 0) {
            u32   val32 = 0;
            u16   dev = 0;
            u16   addr = 0;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }
            printf ("Enter Dev (in HEX, ie. 0x ): ");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            dev = strtol(value_str, NULL, 16);

            printf ("Enter Dev (in HEX, ie. 0x ): ");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            addr = strtol(value_str, NULL, 16);

            board->inst->init_conf.spi_32bit_read_write(board->inst, port_no, SPI_RD, dev, addr, &val32);

            continue;

        } else if (strcmp(command, "spiwr")  == 0) {
            u32   val32 = 0;
            u16   dev = 0;
            u16   addr = 0;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Enter Dev (in HEX, ie. 0x ): ");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            dev = strtol(value_str, NULL, 16);

            printf ("Enter Dev (in HEX, ie. 0x ): ");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            addr = strtol(value_str, NULL, 16);

            printf ("Enter Value (in HEX, ie. 0x ): ");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            val32 = strtol(value_str, NULL, 16);

            board->inst->init_conf.spi_32bit_read_write(board->inst, port_no, SPI_WR, dev, addr, &val32);

            continue;

        } else if (strcmp(command, "dump")  == 0) {
            BOOL     print_hdr = TRUE;
            u32      page_no = 0;
            vtss_debug_info_t  dbg_info;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            /* ********************************************************** */
            /* ******  FULL REG PRINT OUT          ******************* */
            /* ****** CHANNEL 0 ONLY implemented below!!!!   ******************* */
            /* ********************************************************** */

            vtss_debug_printf_t pr2 = (vtss_debug_printf_t) printf;
            printf("\n==========================================================\n");
            if (port_no == VTSS_PORT_NO_START) {
                printf("Full Reg Dump for Port %d\n", port_no);
                if (vtss_phy_10g_malibu_dump_public(board->inst, pr2, port_no) != VTSS_RC_OK) {
                    T_E("vtss_phy_malibu_register_dump, port %d\n", port_no);
                    printf("vtss_phy_malibu_register_dump, port %d\n", port_no);
                }
            } else {
                printf("Skipping full reg dump for port %d\n", port_no);
            }
            printf("==========================================================\n");

            continue;

        } else if (strcmp(command, "dbgdump")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

           /* ********************************************************** */
           /* ******    DEBUG REG PRINT OUT          ******************* */
           /* ********************************************************** */

            vtss_debug_printf_t pr = (vtss_debug_printf_t) printf;
            printf("\n==========================================================\n");
            printf("Debug Reg Dump for Port %d\n", port_no);
            if (vtss_phy_10g_debug_register_dump(board->inst, pr, FALSE, port_no) != VTSS_RC_OK) {
              T_E("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
              printf("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
            }
            printf("==========================================================\n");
            continue;

        } else if (strcmp(command, "status")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            vtss_appl_malibu_status_get(board->inst, port_no, &oper_mode);

            continue;

        } else if (strcmp(command, "synce")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            vtss_appl_malibu_synce_cntrl(board->inst, port_no);

            continue;


        } else if (strcmp(command, "10g_kr")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            vtss_appl_malibu_10g_base_kr_cntrl(board->inst, port_no);

            continue;

        } else if (strcmp(command, "obuf")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            vtss_appl_malibu_ob_cntrl(board->inst, port_no);

            continue;


        } else if (strcmp(command, "prbs")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            printf ("Please confirm OBUF is configured via Output Buffer Control prior to running PRBS on Port: %d", port_no);
            printf ("Configure OBUF ? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str [0] == 'y' || value_str [0] == 'Y' ) {
                vtss_appl_malibu_ob_cntrl(board->inst, port_no);
            }

            vtss_appl_malibu_prbs_cntrl(board->inst, port_no);

            continue;

        } else if (strcmp(command, "vscope")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            vtss_appl_malibu_vscope_cntrl(board->inst, port_no);

            continue;

        } else if (strcmp(command, "lpback")  == 0) {
            vtss_phy_10g_loopback_t    lpback;
            vtss_lb_type_t             lpback_type = VTSS_LB_NONE;
            char                       lpback_descr[6];
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            memset (&lpback_descr[0], 0, sizeof(lpback_descr));
            vtss_phy_10g_loopback_set(board->inst, port_no, &lpback);

            switch (lpback.lb_type) {
            case VTSS_LB_NONE: lpback_descr[0] = 'N'; lpback_descr[1] = 'O'; lpback_descr[2] = 'N'; lpback_descr[3] = 'E'; break;
            case VTSS_LB_H2: lpback_descr[0] = 'H'; lpback_descr[1] = '2'; break;
            case VTSS_LB_H3: lpback_descr[0] = 'H'; lpback_descr[1] = '3'; break;
            case VTSS_LB_H4: lpback_descr[0] = 'H'; lpback_descr[1] = '4'; break;
            case VTSS_LB_H5: lpback_descr[0] = 'H'; lpback_descr[1] = '5'; break;
            case VTSS_LB_H6: lpback_descr[0] = 'H'; lpback_descr[1] = '6'; break;
            case VTSS_LB_L0: lpback_descr[0] = 'L'; lpback_descr[1] = '0'; break;
            case VTSS_LB_L1: lpback_descr[0] = 'L'; lpback_descr[1] = '1'; break;
            case VTSS_LB_L2: lpback_descr[0] = 'L'; lpback_descr[1] = '2'; break;
            case VTSS_LB_L3: lpback_descr[0] = 'L'; lpback_descr[1] = '3'; break;
            case VTSS_LB_L2C: lpback_descr[0] = 'L'; lpback_descr[1] = '2'; lpback_descr[2] = 'C'; break;
            default:
                printf ("Current Loopback Description INVALID,  Port_no: %d \n",  port_no);
                memset (&lpback_descr[0], 0, sizeof(lpback_descr));
            }
            printf ("Current Loopback is: %s  Type: %s \n\n",  (lpback.enable ? "Enabled" : "Disabled"), lpback_descr);

            printf ("Loopback Options for Port: %d \n", port_no);
            printf ("  H2: Host Loopback 2, 40-bit XAUI-PHY interface Mirror XAUI data\n");
            printf ("  H3: Host Loopback 3, 64-bit PCS after the gearbox FF00 repeating IEEE PCS system loopback \n");
            printf ("  H4: Host Loopback 4, 64-bit WIS FF00 repeating IEEE WIS system loopback \n");
            printf ("  H5: Host Loopback 5, 1-bit SFP+ after SerDes Mirror XAUI data IEEE PMA system loopback \n");
            printf ("  H6: Host Loopback 6, 32-bit XAUI-PHY interface Mirror XAUI data  \n\n");
            printf ("  L0: Line Loopback 0, 4-bit XAUI before SerDes Mirror SFP+ data \n");
            printf ("  L1: Line Loopback 1, 4-bit XAUI after SerDes Mirror SFP+ data IEEE PHY-XS network loopback \n");
            printf ("  L2: Line Loopback 2, 64-bit XGMII after FIFO Mirror SFP+ data  \n");
            printf ("  L3: Line Loopback 3, 64-bit PMA interface Mirror SFP+ data \n");
            printf ("  L2C: Line Line loopback 4 after cross connect    \n\n");
            printf ("Enter Loopback Type: H2/H3/H4/H5/H6/L0/L1/L2/L3/L2C \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str [0] == 'h' || value_str [0] == 'H' ) {
                switch (value_str [1]) {
                case '2':
                    lpback_type = VTSS_LB_H2;
                    break;
                case '3':
                    lpback_type = VTSS_LB_H3;
                    break;
                case '4':
                    lpback_type = VTSS_LB_H4;
                    break;
                case '5':
                    lpback_type = VTSS_LB_H5;
                    break;
                case '6':
                    lpback_type = VTSS_LB_H6;
                    break;
                default:
                    break;
                }
            } else if (value_str [0] == 'l' || value_str [0] == 'L' ) {
                switch (value_str [1]) {
                case '0':
                    lpback_type = VTSS_LB_L0;
                    break;
                case '1':
                    lpback_type = VTSS_LB_L1;
                    break;
                case '2':
                    if (value_str [2] == 'c' || value_str [2] == 'C') {
                        lpback_type = VTSS_LB_L2C;
                    } else {
                        lpback_type = VTSS_LB_L2;
                    }
                    break;
                case '3':
                    lpback_type = VTSS_LB_L3;
                    break;
                default:
                    break;
                }

            } else {
                lpback_type = VTSS_LB_NONE;
            }

            lpback.lb_type = lpback_type;
            switch (lpback.lb_type) {
            case VTSS_LB_NONE: lpback_descr[0] = 'N'; lpback_descr[1] = 'O'; lpback_descr[2] = 'N'; lpback_descr[3] = 'E'; break;
            case VTSS_LB_H2: lpback_descr[0] = 'H'; lpback_descr[1] = '2'; break;
            case VTSS_LB_H3: lpback_descr[0] = 'H'; lpback_descr[1] = '3'; break;
            case VTSS_LB_H4: lpback_descr[0] = 'H'; lpback_descr[1] = '4'; break;
            case VTSS_LB_H5: lpback_descr[0] = 'H'; lpback_descr[1] = '5'; break;
            case VTSS_LB_H6: lpback_descr[0] = 'H'; lpback_descr[1] = '6'; break;
            case VTSS_LB_L0: lpback_descr[0] = 'L'; lpback_descr[1] = '0'; break;
            case VTSS_LB_L1: lpback_descr[0] = 'L'; lpback_descr[1] = '1'; break;
            case VTSS_LB_L2: lpback_descr[0] = 'L'; lpback_descr[1] = '2'; break;
            case VTSS_LB_L3: lpback_descr[0] = 'L'; lpback_descr[1] = '3'; break;
            case VTSS_LB_L2C: lpback_descr[0] = 'L'; lpback_descr[1] = '2'; lpback_descr[2] = 'C'; break;
            default:
                printf ("Current Loopback Description INVALID,  Port_no: %d \n",  port_no);
                memset (&lpback_descr[0], 0, sizeof(lpback_descr));
            }
            printf ("Selected Loopback Type: %s \n",  lpback_descr);
            printf ("E=Enable or D=Disable Loopback? \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str [0] == 'e' || value_str [0] == 'E') {
                lpback.enable = 1;
            } else {
                lpback.enable = 0;
            }

            printf ("Port %d, Setting Loopback Type: %s  to  %s  \n",  port_no, lpback_descr, (lpback.enable ? "Enabled" : "Disabled"));
            vtss_phy_10g_loopback_set(board->inst, port_no, &lpback);

            continue;

        } else if (strcmp(command, "int10g")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Setting 10G INT's for Port %d", port_no);
#if 1
            vtss_appl_malibu_gpio_int_set(board->inst, port_no);
#endif
            continue;

       } else if (strcmp(command, "poll10g")  == 0) {
            vtss_phy_10g_event_t    ev_status = 0;
            int i;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            /** \brief Event source identification mask values */
            printf("VTSS_PHY_10G_LINK_LOS_EV            0x00000001 \n"); /**< PHY Link Los interrupt - only on 8486 */
            printf("VTSS_PHY_10G_RX_LOL_EV              0x00000002 \n"); /**< PHY RXLOL interrupt - only on 8488 */
            printf("VTSS_PHY_10G_TX_LOL_EV              0x00000004 \n"); /**< PHY TXLOL interrupt - only on 8488 */
            printf("VTSS_PHY_10G_LOPC_EV                0x00000008 \n"); /**< PHY LOPC interrupt - only on 8488 */
            printf("VTSS_PHY_10G_HIGH_BER_EV            0x00000010 \n"); /**< PHY HIGH_BER interrupt - only on 8488 */
            printf("VTSS_PHY_10G_MODULE_STAT_EV         0x00000020 \n"); /**< PHY MODULE_STAT interrupt - only on 8488 */
            printf("VTSS_PHY_10G_PCS_RECEIVE_FAULT_EV   0x00000040 \n"); /**< PHY PCS_RECEIVE_FAULT interrupt - only on 8488 */
#ifdef VTSS_FEATURE_WIS
            printf("VTSS_PHY_EWIS_SEF_EV                0x00000080 \n"); /**< SEF has changed state - only for 8488 */
            printf("VTSS_PHY_EWIS_FPLM_EV               0x00000100 \n"); /**< far-end (PLM-P) / (LCDP) - only for 8488 */
            printf("VTSS_PHY_EWIS_FAIS_EV               0x00000200 \n"); /**< far-end (AIS-P) / (LOP) - only for 8488 */
            printf("VTSS_PHY_EWIS_LOF_EV                0x00000400 \n"); /**< Loss of Frame (LOF) - only for 8488 */
            printf("VTSS_PHY_EWIS_RDIL_EV               0x00000800 \n"); /**< Line Remote Defect Indication (RDI-L) - only for 8488 */
            printf("VTSS_PHY_EWIS_AISL_EV               0x00001000 \n"); /**< Line Alarm Indication Signal (AIS-L) - only for 8488 */
            printf("VTSS_PHY_EWIS_LCDP_EV               0x00002000 \n"); /**< Loss of Code-group Delineation (LCD-P) - only for 8488 */
            printf("VTSS_PHY_EWIS_PLMP_EV               0x00004000 \n"); /**< Path Label Mismatch (PLMP) - only for 8488 */
            printf("VTSS_PHY_EWIS_AISP_EV               0x00008000 \n"); /**< Path Alarm Indication Signal (AIS-P) - only for 8488 */
            printf("VTSS_PHY_EWIS_LOPP_EV               0x00010000 \n"); /**< Path Loss of Pointer (LOP-P) - only for 8488 */
            printf("VTSS_PHY_EWIS_UNEQP_EV              0x00020000 \n"); /**< Unequiped Path (UNEQ-P) - only for 8488 */
            printf("VTSS_PHY_EWIS_FEUNEQP_EV            0x00040000 \n"); /**< Far-end Unequiped Path (UNEQ-P) - only for 8488 */
            printf("VTSS_PHY_EWIS_FERDIP_EV             0x00080000 \n"); /**< Far-end Path Remote Defect Identifier (RDI-P) - only for 8488 */
            printf("VTSS_PHY_EWIS_REIL_EV               0x00100000 \n"); /**< Line Remote Error Indication (REI-L) - only for 8488 */
            printf("VTSS_PHY_EWIS_REIP_EV               0x00200000 \n"); /**< Path Remote Error Indication (REI-P) - only for 8488 */
            printf("VTSS_PHY_EWIS_B1_NZ_EV              0x00400000 \n"); /**< PMTICK B1 BIP (B1_ERR_CNT) not zero - only for 8488 */
            printf("VTSS_PHY_EWIS_B2_NZ_EV              0x00800000 \n"); /**< PMTICK B2 BIP (B1_ERR_CNT) not zero - only for 8488 */
            printf("VTSS_PHY_EWIS_B3_NZ_EV              0x01000000 \n"); /**< PMTICK B3 BIP (B1_ERR_CNT) not zero - only for 8488 */
            printf("VTSS_PHY_EWIS_REIL_NZ_EV            0x02000000 \n"); /**< PMTICK REI-L (REIL_ERR_CNT) not zero - only for 8488 */
            printf("VTSS_PHY_EWIS_REIP_NZ_EV            0x04000000 \n"); /**< PMTICK REI-P (REIP_ERR_CNT) not zero - only for 8488 */
            printf("VTSS_PHY_EWIS_B1_THRESH_EV          0x08000000 \n"); /**< B1_THRESH_ERR - only for 8488 */
            printf("VTSS_PHY_EWIS_B2_THRESH_EV          0x10000000 \n"); /**< B2_THRESH_ERR - only for 8488 */
            printf("VTSS_PHY_EWIS_B3_THRESH_EV          0x20000000 \n"); /**< B3_THRESH_ERR - only for 8488 */
            printf("VTSS_PHY_EWIS_REIL_THRESH_EV        0x40000000 \n"); /**< REIL_THRESH_ERR - only for 8488 */
            printf("VTSS_PHY_EWIS_REIP_THRESH_EV        0x80000000 \n"); /**< REIp_THRESH_ERR - only for 8488 */
#endif /* VTSS_FEATURE_WIS */

            for (i = 0; i < 3; i++) {
#if 1
                vtss_phy_10g_event_poll(board->inst, port_no, &ev_status);
#endif
                printf ("\n\nPolling Extended INT's for Port %d,   10g_ev_status: 0x%x \n", port_no, ev_status);
            }

            continue;


        } else if (strcmp(command, "ex_int")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Setting Extended INT's for Port %d", port_no);
#if 1
            vtss_appl_malibu_ex_gpio_int_set(board->inst, port_no);
#endif
            continue;

       } else if (strcmp(command, "ex_poll")  == 0) {
            vtss_phy_10g_extnd_event_t    ex_ev_status = 0;
            int i;

            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            /*--Events changed in Malibu */
            printf("<<<<--  PMA block interupts -->>>>\n");
            printf("VTSS_PHY_10G_RX_LOS_EV                  0x00000001 \n");/**< PHY RX LOS interrupt - 8256 specific */
            printf("VTSS_PHY_10G_RX_LOL_EV                  0x00000002 \n");/**< PHY RX LOL interrupt - 8256 specific*/
            printf("VTSS_PHY_10G_TX_LOL_EV                  0x00000004 \n");/**< PHY TX LOL interrupt - 8256 specific */
            printf("<<<<--  PCS block interrupts -->>>>\n");
            printf("VTSS_PHY_10G_RX_CHAR_DEC_CNT_THRESH_EV  0x00000010 \n");/**< PHY RX character decode error - 8256 specific */
            printf("VTSS_PHY_10G_TX_CHAR_ENC_CNT_THRESH_EV  0x00000020 \n");/**< PHY TX character encode error count  - 8256 specific */
            printf("VTSS_PHY_10G_RX_BLK_DEC_CNT_THRESH_EV   0x00000040 \n");/**< PHY RX block decode error count  - 8256 specific */
            printf("VTSS_PHY_10G_TX_BLK_ENC_CNT_THRESH_EV   0x00000080 \n");/**< PHY TX block encode error count- 8256 specific */
            printf("VTSS_PHY_10G_RX_SEQ_CNT_THRESH_EV       0x00000100 \n");/**< PHY RX sequencing error count - 8256 specific */
            printf("VTSS_PHY_10G_TX_SEQ_CNT_THRESH_EV       0x00000200 \n");/**< PHY TX sequencing error count - 8256 specific */
            printf("VTSS_PHY_10G_FEC_UNFIXED_CNT_THRESH_EV  0x00000400 \n");/**< PHY KR-FEC uncorrectable block count interrupt - 8256 specific */
            printf("VTSS_PHY_10G_FEC_FIXED_CNT_THRESH_EV    0x00000800 \n");/**< PHY KR-FEC corrected threshold - 8256 specific */
            printf("VTSS_PHY_10G_HIGHBER_EV                 0x00001000 \n");/**< PHY high bit Error - 8256 specific */
            printf("VTSS_PHY_10G_RX_LINK_STAT_EV            0x00002000 \n");/**< PHY Link status up/down interrupt - 8256 specific */
            printf("VTSS_PHY_10G_RX_LINK_STAT_EV            0x00002000 \n");/**< PHY Link status up/down interrupt - 8256 specific */
            printf("VTSS_PHY_10G_GPIO_INT_AGG0_EV           0x00004000 \n");/**< PHY GPIO interrupt on Aggregator0  - 8256 specific */
            printf("VTSS_PHY_10G_GPIO_INT_AGG1_EV           0x00008000 \n");/**< PHY GPIO interrupt on Aggregator1  - 8256 specific */
            printf("VTSS_PHY_10G_GPIO_INT_AGG2_EV           0x00010000 \n");/**< PHY GPIO interrupt on Aggregator2  - 8256 specific */
            printf("VTSS_PHY_10G_GPIO_INT_AGG3_EV           0x00020000 \n");/**< PHY GPIO interrupt on Aggregator3  - 8256 specific */
            printf("VTSS_PHY_1G_LINE_AUTONEG_RESTART_EV     0x00040000 \n");/**< PHY 1G Line side Autoneg restart event */
            printf("VTSS_PHY_1G_HOST_AUTONEG_RESTART_EV     0x00080000 \n");/**< PHY 1G Host side Autoneg restart event  - 8256 specific */
            printf("<<<<--   MAC Block interrupts -->>>> \n");
            printf("VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV    0x00100000 \n");/**< PHY 10G LINE MAC local fault event */
            printf("VTSS_PHY_10G_HOST_MAC_LOCAL_FAULT_EV    0x00400000 \n");/**< PHY 10G HOST MAC local fault event */
            printf("VTSS_PHY_10G_LINE_MAC_REMOTE_FAULT_EV   0x00800000 \n");/**< PHY 10G LINE MAC remote fault event */
            printf("VTSS_PHY_10G_HOST_MAC_REMOTE_FAULT_EV   0x01000000 \n");/**< PHY 10G HOST MAC remote fault event */

            for (i = 0; i < 3; i++) {
#if 1
                vtss_phy_10g_extended_event_poll(board->inst, port_no, &ex_ev_status);
#endif
                printf ("\n\nPolling Extended INT's for Port %d,   ex_ev_status: 0x%x \n", port_no, ex_ev_status);
            }

            continue;

#ifdef VTSS_FEATURE_PHY_TIMESTAMP

        } else if (strcmp(command, "ts_int")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Setting 1588 INT's for Port %d", port_no);
#if 1
#ifdef  EVAL_BOARD_1588_CAPABLE    // 1588 get #ifdef'd because they are completely seperate Modules
            vtss_appl_malibu_ts_gpio_int_set(board->inst, port_no);
#endif  // End of MACSEC
#endif
            continue;

       } else if (strcmp(command, "ts_poll")  == 0) {
            vtss_phy_ts_event_t    ev_status = 0;
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("VTSS_PHY_TS_INGR_ENGINE_ERR            0x01\n");  /**< More than one engine find match */
            printf ("VTSS_PHY_TS_INGR_RW_PREAM_ERR          0x02\n");  /**< Preamble too short to append timestamp */
            printf ("VTSS_PHY_TS_INGR_RW_FCS_ERR            0x04\n");  /**< FCS error in ingress */
            printf ("VTSS_PHY_TS_EGR_ENGINE_ERR             0x08\n");  /**< More than one engine find match */
            printf ("VTSS_PHY_TS_EGR_RW_FCS_ERR             0x10\n");  /**< FCS error in egress */
            printf ("VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20\n");  /**< Timestamp captured in Tx TSFIFO */
            printf ("VTSS_PHY_TS_EGR_FIFO_OVERFLOW          0x40\n");  /**< Tx TSFIFO overflow */
            printf ("VTSS_PHY_TS_DATA_IN_RSRVD_FIELD        0x80\n");  /**< Data in reserved Field */
            printf ("VTSS_PHY_TS_LTC_NEW_PPS_INTRPT         0x100\n"); /**< New PPS pushed onto external PPS pin*/
            printf ("VTSS_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200\n\n"); /**< New LTC value either loaded in to HW or saved into registers*/

#if 1
#ifdef  EVAL_BOARD_1588_CAPABLE    // 1588 get #ifdef'd because they are completely seperate Modules
            vtss_phy_ts_event_poll(board->inst, port_no, &ev_status);
#endif  // End of MACSEC
#endif
            printf ("\n\nPolling 1588 INT's for Port %d,   ev_status: 0x%x \n", port_no, ev_status);

            continue;

#endif // #VTSS_FEATURE_PHY_TIMESTAMP

#ifdef VTSS_FEATURE_MACSEC
        } else if (strcmp(command, "macsec")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
#if 1
#ifdef EVAL_BOARD_MACSEC_CAPABLE  // 1588 and MACSec get #ifdef'd because they are completely seperate Modules
            printf ("Configure MACSEC Block? (Y/N)  \n");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);

            if (value_str [0] == 'y' || value_str [0] == 'Y' ) {
                vtss_appl_macsec_demo_menu(board->inst, port_no);
            }
#endif  // End of MACSEC
#endif
            continue;

#endif // VTSS_FEATURE_MACSEC

#ifdef VTSS_FEATURE_PHY_TIMESTAMP

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
#endif

#endif // VTSS_FEATURE_PHY_TIMESTAMP
            continue;

        } else if (strcmp(command, "exit")  == 0) {
            break;
        }
    } /* End of While (1) */

#endif /* VTSS_CHIP_10G_PHY */


#ifdef _INCLUDE_DEBUG_FILE_PRINT_
  fclose(fp);
#endif
  return 0; // All done

} // end of main
