// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/*
 *****************************************************************************************
* Revision 0.2  2018/10/04 sunilp
* 0.2 Added support for different data rates
* Revision 0.1  2018/08/02 sunilp
* 0.1 is the first version for the Venice family of products (VSC8489/90/91(-xx))
 *****************************************************************************************

*/
#include "vtss_api.h"   // For board initialization
#include "vtss_appl.h"  // For vtsss_board_t
#include "vtss_port_api.h"
#include "vtss_phy_10g_api.h"   // For board initialization
#include "vtss_appl_10g_phy_venice.h" // For board init
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

#define PHY_MODE_10G_LAN_XAUI     (0)
#define PHY_MODE_10G_LAN_RXAUI    (1)
#define PHY_MODE_1G_LAN_LANE0     (2)
#define PHY_MODE_1G_LAN_LANE3     (3)
#define PHY_MODE_10G_WAN_XAUI     (4)
#define PHY_MODE_10G_WAN_RXAUI    (5)


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
#if defined (VENICE_CHAR_BOARD)
	board->board_init = venice_board_init; // Pointer to function initializing the board
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



  /* ********************************************************** */
  /* **** Peform some Read / Write functions to Validate SPI ** */
  /* ********************************************************** */
  // Read and write to registers to test out the register interface
  //
  // Note:
  // 1) This section consists of some simple read/write comamnds to
  //    test out the register access interface,
  // 2) The different register access listed here test out various
  //    combinations of 16-bit/32-bit registers, channel access as
  //    well as read/write functions,
  // 3) We recommend testing this section out before proceeding to
  //    initialize the chip.

BOOL  vtss_appl_venice_spi_io_test(const vtss_inst_t   inst, const vtss_port_no_t   port_no)
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
  printf("1x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

  dev = 0x1; addr = 0x2;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV1, Addr02: Dev_ID1: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x1; addr = 0x3;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV1, Addr03: Dev_ID2:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x1; addr = 0x0;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV1, Addr00: PMA_CTRL1:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x2; addr = 0x2;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV2, Addr02: WIS_ID1: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x2; addr = 0x3;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV2, Addr03: WIS_ID2:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x2; addr = 0x0;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV2, Addr00: WIS_CTRL1:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x3; addr = 0x2;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV3, Addr02: PCS_ID1: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x3; addr = 0x3;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV3, Addr03: PCS_ID2:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x3; addr = 0x0;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV3, Addr00: PCS_CTRL1:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x4; addr = 0x2;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV4, Addr02: XS_ID1: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x4; addr = 0x3;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV4, Addr03: XS_ID2:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x4; addr = 0x0;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("DEV4, Addr00: XS_CTRL1:: 0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  dev = 0x1; addr = 0xF112;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  val32 = 0x003DF828;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_WR, dev, addr, &val32);
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  val32 = 0x007DF820;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_WR, dev, addr, &val32);
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("0x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

  dev = 0x1; addr = 0xF112;
  inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
  printf("1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  val32 = 0x004DF828;
  inst->init_conf.spi_32bit_read_write(inst, 1, SPI_WR, dev, addr, &val32);
  inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
  printf("1x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  val32 = 0x007DF820;
  inst->init_conf.spi_32bit_read_write(inst, 1, SPI_WR, dev, addr, &val32);
  inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
  printf("1x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

  dev = 0x1; addr = 0xF120;
  inst->init_conf.spi_32bit_read_write(inst, 0, SPI_RD, dev, addr, &val32);
  printf("0x%Xx%04X = 0x%X\n", dev, addr, val32); fflush(stdout);

  inst->init_conf.spi_32bit_read_write(inst, 1, SPI_RD, dev, addr, &val32);
  printf("1x%Xx%04X = 0x%X\n\n", dev, addr, val32); fflush(stdout);

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
    /* ******    SYNC-E                       ******************* */
    /* ********************************************************** */
    // SYNC-E: SREFCLK function to configure the input SyncE clock
    //
    /* The modes: VTSS_PHY_LAN_SYNCE_MODE and VTSS_PHY_WAN_SYNCE_MODE assume the SREFCLK is connected */
    /* Generally speaking, SYNC_E Mode will be Ext. Master which does not use SREFCLK */
    /* Therefore, Only use the mode_set API code if SREFCLK is the SYNCE Ref */

BOOL  vtss_appl_venice_synce_cntrl(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
    vtss_phy_10g_rxckout_conf_t  rx_ckout_conf;


    if (vtss_phy_10g_rxckout_get(inst, port_no, &rx_ckout_conf) != VTSS_RC_OK) {
        printf("RECOV CLK configuration: vtss_phy_10g_rxckout_get FAILED: %d\n", port_no);
    }

    // VTSS_RECVRD_CLKOUT_DISABLE=0,             /**< recovered clock output is disabled */
    // VTSS_RECVRD_CLKOUT_LINE_SIDE_RX_CLOCK=1,  /**< recovered clock output is derived from Lineside Rx clock */
    // VTSS_RECVRD_CLKOUT_LINE_SIDE_TX_CLOCK=2,  /**< recovered clock output is derived from Lineside Tx clock */

    rx_ckout_conf.mode = VTSS_RECVRD_CLKOUT_LINE_SIDE_RX_CLOCK;
    rx_ckout_conf.squelch_on_pcs_fault = TRUE;
    rx_ckout_conf.squelch_on_lopc = TRUE;

    if (vtss_phy_10g_rxckout_set(inst, port_no, &rx_ckout_conf) != VTSS_RC_OK) {
        printf("RECOV CLK configuration: vtss_phy_10g_rxckout_set FAILED: %d\n", port_no);
    }

#undef SREFCLK_IS_SYNCE_REF
#ifdef SREFCLK_IS_SYNCE_REF
    vtss_phy_10g_mode_t       oper_mode;

    if (vtss_phy_10g_mode_get(inst, port_no, &oper_mode) != VTSS_RC_OK) {
        printf("RECOV CLK configuration: vtss_phy_10g_mode_get FAILED: %d\n", port_no);
    }

    /* The modes: VTSS_PHY_LAN_SYNCE_MODE and VTSS_PHY_WAN_SYNCE_MODE assume the SREFCLK is connected */
    /* Generally speaking, SYNC_E Mode will be Ext. Master which does not use SREFCLK */
    /* Therefore, Only use this code if SREFCLK is the SYNCE Ref */
    if (oper_mode.oper_mode == VTSS_PHY_LAN_MODE) {
        oper_mode.oper_mode = VTSS_PHY_LAN_SYNCE_MODE;
        printf("RECOV CLK configuration: updating oper_mode to: VTSS_PHY_LAN_SYNCE_MODE: %d\n", port_no);
    } else if (oper_mode.oper_mode == VTSS_PHY_WAN_MODE) {
        oper_mode.oper_mode = VTSS_PHY_WAN_SYNCE_MODE;
        printf("RECOV CLK configuration: updating oper_mode to: VTSS_PHY_WAN_SYNCE_MODE: %d\n", port_no);
    } else if (oper_mode.oper_mode == VTSS_PHY_1G_MODE) {
        oper_mode.oper_mode = VTSS_PHY_LAN_SYNCE_MODE;
        printf("RECOV CLK configuration: updating oper_mode to: VTSS_PHY_LAN_SYNCE_MODE: %d\n", port_no);
    } else {
        printf("RECOV CLK configuration: INVALID OPTION, port_no: %d;  oper_mode.oper_mode = %d \n", port_no, oper_mode.oper_mode );
    }

    printf("RECOV CLK configuration: oper_mode.oper_mode: %d\n", oper_mode.oper_mode);

    if (vtss_phy_10g_mode_set(inst, port_no, &oper_mode) != VTSS_RC_OK) {
        printf("RECOV CLK configuration: vtss_phy_10g_mode_set FAILED: %d\n", port_no);
    }

#endif
    printf("RECOV CLK configuration:  Done!\n");
}

BOOL  vtss_appl_venice_status_get(vtss_inst_t   inst, vtss_port_no_t   port_no, vtss_phy_10g_mode_t  *oper_mode)
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
    // Per Channel interrupt, using Line 10G PCS status, driving WIS INT blocks
    // output -- Channel dependent GPIOs
    // GPIO on Venice char board used for Aggregate Interrupt: GPIO_6
    ///////////////////////////////////////////////////////////////////////////////

BOOL  vtss_appl_venice_gpio_int_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#if 1
    char value_str[255] = {0};
    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    vtss_phy_10g_event_t       ev;
    u16 gpio_no;

    gpio_no = 8; /* available on char board GPIO header */

    memset(&ev, 0, sizeof(vtss_phy_10g_event_t));
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

    // Example:
    //ex_ev = VTSS_PHY_10G_RX_LINK_STAT_EV | VTSS_PHY_10G_LINE_MAC_LOCAL_FAULT_EV;
    // Note:
    // 1) The function "vtss_phy_10g_event_enable_set" can be called with the last argument set to FALSE to disable this interrupt
    // 2) To set multiple extended events, it is required to make multiple calls to the functions below

    // Enable 10G PCS event
    //ev = VTSS_PHY_10G_PCS_RECEIVE_FAULT_EV | VTSS_PHY_10G_RX_LINK_STAT_EV;
    printf("\nVenice GPIO Event Enable config port_no: %d; gpio %d, EventMask: 0x%04x \n", port_no, gpio_no, ev);

    // Enable 10G PCS event

    if (vtss_phy_10g_event_enable_set(inst, port_no, ev, TRUE) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_event_enable_set, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

    printf("\nSet Venice GPIO Event Enable config port_no: %d; mode=VTSS_10G_PHY_GPIO_WIS_INT, gpio %d, Events: 0x%04x \n", port_no, gpio_no, ev);
#if 1
   // Now configure the GPIO for WIS Int function
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_WIS_INT;
    gpio_mode.port = port_no;

    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: AGG_INT\n", port_no, gpio_no);
      printf("Venice Error setting GPIO WIS_INT configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

#endif

#endif
}

    ///////////////////////////////////////////////////////////////////////////////
    // 1588 interrupts, using Line 10G PCS status, driving Aggregate Interrupt
    // output -- Channel dependent GPIOs
    // GPIO used for Aggregate Interrupt: #34
    ///////////////////////////////////////////////////////////////////////////////

BOOL  vtss_appl_venice_ts_gpio_int_set(vtss_inst_t   inst, vtss_port_no_t   port_no)
{
#ifdef  EVAL_BOARD_1588_CAPABLE
#if 1
    char value_str[255] = {0};
    vtss_gpio_10g_gpio_mode_t  gpio_mode;
    vtss_phy_ts_event_t ts_ev;
    u16 gpio_no;

    // Per channel 1588 Interrupts

    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));

    gpio_no = 34;

    // Note:
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
    //ts_ev = VTSS_PHY_TS_EGR_FIFO_OVERFLOW | VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED;

    printf("\nUpdating/Setting Malibu GPIO 1588 Event Enable configuration for port %d, gpio %d, Events: 0x%04x \n", port_no, gpio_no, ts_ev);

    // Enable 1588 TSFIFO overflow event
    if (vtss_phy_ts_event_enable_set(inst, port_no, TRUE, ts_ev) != VTSS_RC_OK) {
      T_E("vtss_phy_ts_event_enable_set, port %d, gpio %d\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO 1588 Event Enable configuration for port %d, gpio %d \n", port_no, gpio_no);
    }

#if 0

    // Enable 1588 channel 3 interrupt
    // Available options (1 interrupt per channel):
    // --> VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR0_EN
    // --> VTSS_10G_GPIO_AGGR_INTRPT_IP1588_1_INTR0_EN
    // --> VTSS_10G_GPIO_AGGR_INTRPT_IP1588_2_INTR0_EN
    // --> VTSS_10G_GPIO_AGGR_INTRPT_IP1588_3_INTR0_EN

    // Now configure the GPIO for Agg Int function
    memset(&gpio_mode, 0, sizeof(vtss_gpio_10g_gpio_mode_t));
    gpio_mode.mode = VTSS_10G_PHY_GPIO_AGG_INT_1;
    gpio_mode.aggr_intrpt = (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR3_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR2_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR1_EN) | (1<<VTSS_10G_GPIO_AGGR_INTRPT_IP1588_0_INTR0_EN);

    if (vtss_phy_10g_gpio_mode_set(inst, port_no, gpio_no, &gpio_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_gpio_mode_set, port %d, gpio %d, mode: AGG_INT\n", port_no, gpio_no);
      printf("Malibu Error setting GPIO AGG_INT configuration for port %d, gpio %d, 1588 Int1 \n", port_no, gpio_no);
    }
#endif

#endif
#endif
}




/* ================================================================= *
 *  START_OF_MAIN
 * ================================================================= */
int main(int argc, const char **argv) {
  vtss_rc                 rc;
  u16 value;
  int                     phy_mode = 0;
  vtss_appl_board_t       *board;
  vtss_inst_create_t      create;
  vtss_port_no_t          port_no=0;
  vtss_port_no_t          phy_base_port=0;
  vtss_init_conf_t        init_conf;
  vtss_port_interface_t   mac_if;
  vtss_phy_10g_mode_t       oper_mode;
  vtss_phy_10g_init_parm_t  init_parm;
  vtss_phy_10g_rxckout_conf_t  rx_ckout_conf;
  char value_str[255] = {0};
  char command[255] = {0};
  char port_no_str[255] = {0};
  BOOL enable_1588 = FALSE;
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
  memset(&vtss_appl_trace_conf, 0, sizeof(vtss_appl_trace_conf));
  vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_AIL] = VTSS_TRACE_LEVEL_ERROR;
  vtss_appl_trace_conf.level[VTSS_TRACE_LAYER_CIL] = VTSS_TRACE_LEVEL_ERROR;
  printf ("//Default AIL TRACE Level : VTSS_TRACE_LEVEL_ERROR\n" );
  printf ("//Default CIL TRACE Level : VTSS_TRACE_LEVEL_ERROR\n" );

  // Setup trace level for PHY group - vtss_appl_trace_conf is a global
  vtss_trace_conf_set(VTSS_TRACE_GROUP_PHY, &vtss_appl_trace_conf);


#ifdef _INCLUDE_DEBUG_FILE_PRINT_
  fp = fopen("phyeval.log", "w");
#endif

  // In this case we only have one board. Assign point to the board definition
  board = &board_table[0];

  memset (&board_table[0], 0, (sizeof(vtss_appl_board_t) * MAX_BOARD_INSTANCES));

  printf ("//Default Setup Assumptions: \n" );
  printf ("//Eval Board has Power Applied prior to Demo start \n" );
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

  /* ********************************************************** */
  /* ***************    Get the Board Definitiions ************ */
  /* *************** Define Board Accessor Functions ********** */
  /* ********************************************************** */
  // Initialize
  vtss_board_phy_init(board);

  /* ********************************************************** */
  /* ***************    Create the PHY INST for API************ */
  /* ********************************************************** */
  // "Create" the board
  vtss_inst_get(board->target, &create);
  vtss_inst_create(&create, &board->inst);
  vtss_init_conf_get(board->inst, &init_conf);

  /* ********************************************************** */
  /* ****     Save Board init_conf in board struct        ***** */
  /* ********************************************************** */
  board->init.init_conf = &init_conf;

  if (board->board_init(argc, argv, board)) {
    T_E("Could not initialize board");
    return 1;
  } else {
    printf ("//Comment: Board being initialized\n");
  }

  /* ********************************************************** */
  /* **** Assign the Board Accessor Functions in PHY INST ***** */
  /* ********************************************************** */
  if (vtss_init_conf_set(board->inst, &init_conf) == VTSS_RC_ERROR) {
        T_E("Could not initialize");
        return 1;
  }

/* ********************************************************** */
/* ******    Test SPI I/O                 ******************* */
/* ********************************************************** */

  printf("%s \n", board->descr);
  vtss_appl_venice_spi_io_test(board->inst, port_no);

#ifdef  VENICE_CHAR_BOARD
  printf ("Setup of VSC849x - VENICE Char/Eval Board \n");
  mac_if = VTSS_PORT_INTERFACE_SFI; // vtss_api/include/vtss/api/types.h used in 10G?

#endif

  /* ****************************************************** */
  /* USER CONFIGURATION                                     */
  /* ****************************************************** */
  printf("VTSS_PORT_NO_START = %d\n", VTSS_PORT_NO_START);
  printf("VTSS_PORTS = %d\n", VTSS_PORTS);
  fflush(stdout);

  printf("\nBoard Info --> \n");
  printf("Board name: %s\n", board->descr);
  printf("port_no = %d\n", port_no); fflush(stdout);
  printf("Board Target: %d\n", board->target); fflush(stdout);
  printf("Board Intf: %p\n", board->port_interface); fflush(stdout);

  printf("Board Inst: %p\n\n", board->inst); fflush(stdout);

  // Undefine modes for each port
#undef MODE_10GLAN_XAUI
#undef MODE_10GLAN_RXAUI
#undef MODE_1GLAN_LANE0
#undef MODE_1GLAN_LANE3
#undef MODE_10GWAN_XAUI
#undef MODE_10GWAN_RXAUI
#define MODE_10GLAN_XAUI

  /* ********************************************************** */
  /* ***************    Basic Bring-up      ******************* */
  /* ********************************************************** */

  printf ("Configuring Operating MODE for ALL Ports:  \n");
  printf ("0=MODE_10GLAN_XAUI;  1=MODE_10GLAN_RXAUI;  \n");
  printf ("2=MODE_1GLAN_LANE0;  3=MODE_1GLAN_LANE3;   \n");
  printf ("4=MODE_10GWAN_XAUI;  5=MODE_10GWAN_RXAUI;  \n");
  printf ("Enter Oper_MODE (0/1/2/3/4/5): ");
  memset (&value_str[0], 0, sizeof(value_str));
  scanf("%s", &value_str[0]);
  phy_mode = atoi(value_str);

  printf ("\n");

  switch (phy_mode) {
  case PHY_MODE_10G_LAN_XAUI:
      printf ("Operating MODE for ALL Ports: 0=PHY_MODE_10G_LAN_XAUI\n");
      break;
  case PHY_MODE_10G_LAN_RXAUI:
      printf ("Operating MODE for ALL Ports: 1=PHY_MODE_10G_LAN_RXAUI\n");
      break;
  case PHY_MODE_1G_LAN_LANE0:
      printf ("Operating MODE for ALL Ports: 2=PHY_MODE_1G_LAN_LANE0\n");
      break;
  case PHY_MODE_1G_LAN_LANE3:
      printf ("Operating MODE for ALL Ports: 3=PHY_MODE_1G_LAN_LANE3\n");
      break;
  case PHY_MODE_10G_WAN_XAUI:
      printf ("Operating MODE for ALL Ports: 4=PHY_MODE_10G_WAN_XAUI\n");
      break;
  case PHY_MODE_10G_WAN_RXAUI:
      printf ("Operating MODE for ALL Ports: 5=PHY_MODE_10G_WAN_RXAUI\n");
      break;
  default:
      printf ("Operating MODE ALL Ports INVALID, Setting 10G_LAN Mode \n");
      phy_mode = 0;
  }

  // Note: This loop should always start from the physical Ch0 of the device
  for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {

    printf("\nConfiguring port %d\n", port_no);

    /* Use Memset(0) only for the very first Reset of the Board    */
    /* If vtss_phy_10g_mode_set() is called again, first           */
    /* call vtss_phy_10g_mode_get, then vtss_phy_10g_mode_set      */
    memset(&oper_mode, 0, sizeof(vtss_phy_10g_mode_t));
    init_parm.channel_conf = VTSS_CHANNEL_AUTO;
    if(vtss_phy_10g_init(board->inst, port_no, &init_parm)!= VTSS_RC_OK) {
      T_E("vtss_phy_10g_init failed, port %d\n", port_no);
      printf("vtss_phy_10g_init failed, port %d\n", port_no);
    }

    // if (vtss_phy_10g_mode_get(board->inst, port_no, &oper_mode) != VTSS_RC_OK) {
    //   T_E("vtss_phy_10g_mode_get failed, port %d\n", port_no);
    //   printf("vtss_phy_10g_mode_get failed, port %d\n", port_no);
    // }

    // LREFCLK is_high_amp :
    // --> TRUE (1100mV to 1500mV diff swing)
    // --> FASLE (200mV to 1200mV diff swing)
    oper_mode.l_clk_src.is_high_amp = TRUE;

    switch (phy_mode) {
    case PHY_MODE_10G_LAN_XAUI:
        // Line side: 10G LAN
        // Host side: XAUI
        printf("Configuring 10GLAN_XAUI mode, port %d!\n", port_no);

        oper_mode.oper_mode = VTSS_PHY_LAN_MODE;
        oper_mode.interface = VTSS_PHY_XAUI_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;

        break;

    case PHY_MODE_10G_LAN_RXAUI:
        // Line side: 10G LAN
        // Host side: RXAUI
        printf("Configuring 10GLAN_RXAUI mode, port %d!\n", port_no);

        oper_mode.oper_mode = VTSS_PHY_LAN_MODE;
        oper_mode.interface = VTSS_PHY_RXAUI_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;

        break;

    case PHY_MODE_1G_LAN_LANE0:
        // Line side: 1000BASE-X LAN
        // Host side: 1000BASE-X LAN (Lane0 used with Auto Neg disabled)
        // SGMII Auto Neg is not supported, chip works only @ 1G data rate
        printf("Configuring 1GLAN_LANE0 mode, port %d!\n", port_no);

        oper_mode.oper_mode = VTSS_PHY_1G_MODE;
        oper_mode.interface = VTSS_PHY_SGMII_LANE_0_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;

        break;

    case PHY_MODE_1G_LAN_LANE3:
        // Line side: 1000BASE-X LAN
        // Host side: 1000BASE-X LAN (Lane3 used with Auto Neg disabled)
        // SGMII Auto Neg is not supported, chip works only @ 1G data rate
        printf("Configuring 1GLAN_LANE3 mode, port %d!\n", port_no);

        oper_mode.oper_mode = VTSS_PHY_1G_MODE;
        oper_mode.interface = VTSS_PHY_SGMII_LANE_3_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;

        break;

    case PHY_MODE_10G_WAN_XAUI:
        // Line side: 10G WAN
        // Host side: XAUI
        printf("Configuring 10GWAN_XAUI mode, port %d!\n", port_no);

        oper_mode.oper_mode = VTSS_PHY_WAN_MODE;
        oper_mode.interface = VTSS_PHY_XAUI_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;

        break;

    case PHY_MODE_10G_WAN_RXAUI:
        // Line side: 10G WAN
        // Host side: RXAUI
        printf("Configuring 10GWAN_RXAUI mode, port %d!\n", port_no);

        oper_mode.oper_mode = VTSS_PHY_WAN_MODE;
        oper_mode.interface = VTSS_PHY_RXAUI_XFI;
        oper_mode.channel_id = VTSS_CHANNEL_AUTO;

        // l_media:
        // --> VTSS_MEDIA_TYPE_SR2_SC (limiting SR/LR/ER/ZR limiting modules)
        // --> VTSS_MEDIA_TYPE_DAC_SC (Direct Attach Cu Cable)
        // --> VTSS_MEDIA_TYPE_KR_SC  (10GBASE-KR backplane)
        // --> VTSS_MEDIA_TYPE_ZR_SC  (linear ZR modules)
        oper_mode.l_media = VTSS_MEDIA_TYPE_SR2_SC;

        break;

    default:
        // Error
        T_E("vtss_phy_10g_mode_set config, port %d\n", port_no);
        printf("vtss_phy_10g_mode_set config failed, port %d -- Improper Mode Selection!\n", port_no);
    }

    /* Setup Port */
    printf("vtss_phy_10g_mode_set: port %d\n", port_no);

    if (vtss_phy_10g_mode_set(board->inst, port_no, &oper_mode) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_mode_set failed, port %d\n", port_no);
      printf("vtss_phy_10g_mode_set failed, port %d\n", port_no);
    }

    if ((phy_mode == PHY_MODE_1G_LAN_LANE0) ||
        (phy_mode == PHY_MODE_1G_LAN_LANE3)) {
        // 1G Auto Negotiation
        printf("\nConfiguring 1G Auto Negotiation, port %d:\n", port_no);

        vtss_phy_10g_clause_37_control_t ctrl;
        memset(&ctrl, 0, sizeof(vtss_phy_10g_clause_37_control_t));
        if (vtss_phy_10g_clause_37_control_get(board->inst, port_no, &ctrl) != VTSS_RC_OK) {
          T_E("vtss_phy_10g_clause_37_control_get failed, port %d\n", port_no);
          printf("vtss_phy_10g_clause_37_control_get failed, port %d\n", port_no);
        }

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
  } // End Of FOR Loop configuring all the ports

  for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORTS; port_no++) {

#if 1
    /* ********************************************************** */
    /* ******    DEBUG REG PRINT OUT          ******************* */
    /* ********************************************************** */

    vtss_debug_printf_t pr = (vtss_debug_printf_t) printf;
    printf("\n==========================================================\n");
    printf("Debug Reg Dump for Port %d\n", port_no);
    if (vtss_phy_10g_debug_register_dump(board->inst, (vtss_debug_printf_t) printf, FALSE, port_no) != VTSS_RC_OK) {
      T_E("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
      printf("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
    }
    printf("==========================================================\n");
#endif

   } // End Of FOR Loop configuring all the ports

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
            printf (" rd       <port_no> <addr>                 |  wr          <port_no> <addr> <value> - Value MUST be in hex\n");
            printf (" getmedia <port_no> - Get Media i/f        |  setmedia    <port_no> - Set Media I/F for port \n");
            printf (" getmac   <port_no> - Get MAC i/f          |  setmac      <port_no> - Set MAC I/F for port \n");
            printf (" ----------------------------------------  |  ------------------------------------------------------- \n");
            printf (" status   <port_no> - Rtn PHY Link status  |  synce       <port_no> - Sync-E Config   \n");
            printf (" lpback   <port_no> - Set PHY Loopback     |                                                           \n");
            printf (" int10g   <port_no> - Set 10g Interuppts   |  poll10g     <port_no>                                    \n");
            printf (" ts_int   <port_no> - Set TS Interuppts    |  ts_poll     <port_no>                                    \n");
            printf (" macsec   <port_no> - MACSEC Block config  |                                                           \n");
            printf (" 1588     <port_no> - 1588 Block Config    |                                                           \n");
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
                if (vtss_phy_10g_debug_register_dump(board->inst, pr2, FALSE, port_no) != VTSS_RC_OK) {
                    T_E("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
                    printf("vtss_phy_10g_debug_register_dump, port %d\n", port_no);
                }
            } else {
                printf("Skipping full reg dump for port %d\n", port_no);
            }
            printf("==========================================================\n");

            continue;

        } else if (strcmp(command, "status")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            vtss_appl_venice_status_get(board->inst, port_no, &oper_mode);

            continue;

        } else if (strcmp(command, "synce")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Port %d", port_no);
            vtss_appl_venice_synce_cntrl(board->inst, port_no);

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
            vtss_appl_venice_gpio_int_set(board->inst, port_no);
#endif
            continue;

       } else if (strcmp(command, "poll10g")  == 0) {
            vtss_phy_10g_event_t    ev_status = 0;
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
            printf("VTSS_PHY_EWIS_B3_THRESH_EV          0x20000000 \n"); /**< B3_THRESH_ERR - only for 8488 */
            printf("VTSS_PHY_EWIS_REIL_THRESH_EV        0x40000000 \n"); /**< REIL_THRESH_ERR - only for 8488 */
            printf("VTSS_PHY_EWIS_REIP_THRESH_EV        0x80000000 \n"); /**< REIp_THRESH_ERR - only for 8488 */
#endif /* VTSS_FEATURE_WIS */

#if 1
            vtss_phy_10g_event_poll(board->inst, port_no, &ev_status);
#endif
            printf ("\n\nPolling Extended INT's for Port %d,   10g_ev_status: 0x%x \n", port_no, ev_status);

            continue;

        } else if (strcmp(command, "ts_int")  == 0) {
            if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                continue;
            }

            printf ("Setting 1588 INT's for Port %d", port_no);
#if 1
#ifdef  EVAL_BOARD_1588_CAPABLE    // 1588 get #ifdef'd because they are completely seperate Modules
            vtss_appl_venice_ts_gpio_int_set(board->inst, port_no);
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
            continue;

        } else if (strcmp(command, "exit")  == 0) {
            break;
        }
   } /* End of While (1) */

  fflush(stdout);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
  fclose(fp);
#endif

  return 0; // All done

} // end of main
