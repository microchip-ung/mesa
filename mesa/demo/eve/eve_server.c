/*
 * eve_server.c
 *  C telnet socket server,
 *  handles multiple clients using fork()
 *  Created on: Sep 17, 2012
 *      Author: jsa
 */

#define SWREVISION  "$Revision: 1.8 $"	// Do not touch: Auto-incremented by CVS

#define _XOPEN_SOURCE 500	// allow posix functions, even though we are C99
#ifndef no_argument			// Suppress Eclipse warnings, these are already in getopt.h
# define no_argument		0
# define required_argument	1
# define optional_argument	2
#endif

#include <ctype.h>		// isspace
#include <getopt.h>		// getopt_long
#include <pthread.h>	// pthread_mutex_lock
#include <stdio.h>		// popen
#include <stdlib.h>		// strtol
#include <string.h>		// strlen
#include <strings.h>	// strcasecmp
#include <unistd.h>		// fork, close
#include <sys/socket.h>
#include <arpa/inet.h>	// inet_addr
#include <errno.h>

#include "eve_sio.h"	// EVE serial IO: SPI_*, I2C_*
#include "eve_jtag.h"	// EVE JTAG
#include "eve_miim.h"	// EVE MIIM
#include "eve_gpio.h"

#define EVE_DEBUG_SOCKET 0x02
#define EVE_DEBUG_GPIO   0x04
#define EVE_DEBUG_SPI    0x08
#define EVE_DEBUG_MIIM   0x10
#define EVE_DEBUG_JTAG   0x20
// Globals
static int  eve_debug = 0;
static int  spi_stateful = 0;
static char spi_device[32];
static char i2c_device[32];

typedef struct s_EVE_STATE {
    int socket;
    enum {NORMAL, RECORDING, REPLAYING} state;
    FILE *fd_record;
    SPI_STATE spi;
    void *portmon;
} EVE_STATE;

// Prototypes
void *connection_handler(int);	// forked process
int epd_tcp_asciicmd(EVE_STATE *state, char *cmdbuf, char *resbuf);
int stats_cmd(const char *cmd_line, char *resbuf, int maxlen, void **portmon_state, SPI_STATE *spi);

//
int main(int argc, char *argv[]) {
    int socket_desc, client_sock, c, i, port = 26;
    struct sockaddr_in server, client;
    pid_t pid;

    // Parse command line switches using getopt_long().
    // http://www.gnu.org/software/libc/manual/html_node/Getopt.html
    // TBD: If command line options are not sufficient, add config file
    //      parsing using libconfuse: http://www.nongnu.org/confuse/
    static struct option long_options[] = {
        /* These options set a flag. */
        //{"debug",    no_argument, &eve_debug, 1},
        {"spistate", no_argument, &spi_stateful, 1},
        /* These options don't set a flag. We distinguish them by their indices. */
        {"debug",    optional_argument, 0, 'D'},    // set debug level
        {"help",     no_argument,       0, 'h'},		// print help
        {"gpiocs",   no_argument,       0, 'g'},		// Use GPIOs for chip selects
        {"gpiomm",   no_argument,       0, 'm'},		// Use memory mapped GPIO
        {"port",     required_argument, 0, 'p'},		// Alternate socket port than 26
        {"i2cfile",  required_argument, 0, 'i'},		// Alternate I2C userspace control file
        {"spifile",  required_argument, 0, 's'},		// Alternate SPI userspace control file
        {"jtagtck",  required_argument, 0, 'C'},		// JTAG: TCK GPIO pin
        {"jtagtms",  required_argument, 0, 'M'},		// JTAG: TMS GPIO pin
        {"jtagtdi",  required_argument, 0, 'I'},		// JTAG: TDI GPIO pin
        {"jtagtdo",  required_argument, 0, 'O'},		// JTAG: TDO GPIO pin
        {"jtagtrst", required_argument, 0, 'R'},		// JTAG: TRST GPIO pin
        {"mdc",      required_argument, 0, 'A'},		// MIIM: MDC GPIO pin
        {"mdio",     required_argument, 0, 'B'},		// MIIM: MDIO GPIO pin
        {0, 0, 0, 0}
    };
    log2stderr("Starting Beaglebone EVE server %s", SWREVISION + 1);
    while (1) {
        int option_index = 0;	// getopt_long stores the option index here.
        c = getopt_long(argc, argv, "gmp:i:s:C:M:I:O:R:A:B:D::", long_options, &option_index);
        if (c == -1) break;		// Detect the end of the options.
        switch (c) {
        case 0: /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0) break;
            printf("option %s", long_options[option_index].name);
            if (optarg) printf (" with arg %s", optarg);
            printf("\n");
            break;
        case 'D':	// DEBUG level. No level specified enables all levels
            eve_debug = optarg ? strtol(optarg, (char **)NULL, 0) : 0xffff;
            log2stderr("Debug level set to 0x%04X", eve_debug);
            break;
        case 'g':	// GPIOCS: Use GPIOs for chip selects (slower)
            SPI_set_gpio_cs(1);
            break;
        case 'm':	// GPIOMM: Use memory mapped GPIO (faster)
            //SPI_set_mm_gpio(1); // This is now default, and cannot be turned off.
            break;
        case 'p':	// PORT: alternate socket port
            port = strtol(optarg, (char **)NULL, 0);
            if (port < 20) port = 26;
            log2stderr("Using port = %d", port);
            break;
        case 'i':	// I2CFILE: Alternate I2C userspace control file
            strncpy(i2c_device, optarg, sizeof(i2c_device)-1);
            log2stderr("Use I2C device: `%s'", i2c_device);
            if (i2c_set_device(i2c_device)) {
                log2stderr("Cannot access device `%s'", optarg);
                abort();
            }
            break;
        case 's': 	// SPIFILE: Alternate SPI userspace control file
            strncpy(spi_device, optarg, sizeof(spi_device)-1);
            log2stderr("Use SPI device: `%s'", spi_device);
            if (SPI_set_device(spi_device)) {
                log2stderr("Cannot access device `%s'", optarg);
                abort();
            }
            break;
        case 'C':	// JTAGTCK: alternate TCK pin
            i = strtol(optarg, (char **)NULL, 0);
            jtag_SetConfig(P_JTAG_TCK, i);
            log2stderr("JTAG TCK set to pin %d", i);
            break;
        case 'M':	// JTAGTMS: alternate TMS pin
            i = strtol(optarg, (char **)NULL, 0);
            jtag_SetConfig(P_JTAG_TMS, i);
            log2stderr("JTAG TMS set to pin %d", i);
            break;
        case 'I':	// JTAGTDI: alternate TDI pin
            i = strtol(optarg, (char **)NULL, 0);
            jtag_SetConfig(P_JTAG_TDI, i);
            log2stderr("JTAG TDI set to pin %d", i);
            break;
        case 'O':	// JTAGTDO: alternate TDO pin
            i = strtol(optarg, (char **)NULL, 0);
            jtag_SetConfig(P_JTAG_TDO, i);
            log2stderr("JTAG TDO set to pin %d", i);
            break;
        case 'R':	// JTAGTRST: alternate TRST pin
            i = strtol(optarg, (char **)NULL, 0);
            jtag_SetConfig(P_JTAG_RST, i);
            log2stderr("JTAG TRST set to pin %d", i);
            break;
        case 'A':	// MDC: alternate MDC pin
            i = strtol(optarg, (char **)NULL, 0);
            i = miim_setgpio(1, i);
            log2stderr("MDC set to pin %d", i);
            break;
        case 'B':	// MDIO: alternate MDIO pin
            i = strtol(optarg, (char **)NULL, 0);
            i = miim_setgpio(0, i);
            log2stderr("MDIO set to pin %d", i);
            break;
        case '?':	// getopt_long already printed an error message.
        case 'h':	// HELP                                                           78 chars |
            puts("Usage:");
            puts("  -p --port PORT     Use other port than 26.");
            puts("  -g --gpiocs        Enable GPIO SPI chip selects.");
            //puts("  -m --gpiomm        Enable memory mapped GPIO.");
            puts("  -i --i2cfile FILE  Use this I2C control file instead of '/dev/i2c-1'.");
            puts("  -s --spifile FILE  Use this SPI control file instead of '/dev/spidev1.0'.");
            puts("     --spistate      Separate SPI state for each CS.");
            puts("  -C --jtagtck PIN   GPIO pin to use as JTAG TCK.");
            puts("  -M --jtagtms PIN   GPIO pin to use as JTAG TMS.");
            puts("  -I --jtagtdi PIN   GPIO pin to use as JTAG TDI.");
            puts("  -O --jtagtdo PIN   GPIO pin to use as JTAG TDO.");
            puts("  -R --jtagtrst PIN  GPIO pin to use as JTAG TRST.");
            puts("  -A --mdc PIN       GPIO pin to use as MDC.");
            puts("  -B --mdio PIN      GPIO pin to use as MDIO.");
            puts("  -D --debug=LEVEL   Enable debug output. Limit to only 1 socket connection!");
            return 0;
            break;
        default:
            abort();
            break;
        }
    }
    log2stderr("EVE server starting %s", eve_debug ? "in debug mode. Only ONE connection supported!" : "...");
    if (eve_debug) {
        if (eve_debug & EVE_DEBUG_GPIO) { GPIO_set_debug(1); }
        if (eve_debug & EVE_DEBUG_SPI)  { SPI_set_debug(1);  }
        if (eve_debug & EVE_DEBUG_MIIM) { MIIM_set_debug(1); }
        if (eve_debug & EVE_DEBUG_JTAG) { JTAG_set_debug(1); }
    }

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        perror("Socket create failed");
    }
    int enable = 1;
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
    }
    log2stderr("SOCKet created.");

    // Prepare the sockaddr_in structure. INADDR_ANY binds to all interfaces (also localhost)
    memset((char *) &server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    // Bind.
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Exiting - Socket bind failed");
        return 1;
    }
    log2stderr("SOCKet bind done.");

    // Listen: server socket
    if (listen(socket_desc, 3) < 0) {
        perror("Socket listen failed");
        return 1;
    }
    // Accept incoming connections
    log2stderr("SOCK waiting for incoming connections on port %d ...", ntohs(server.sin_port));
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c))) {
        log2stderr("SOCK connection accepted from %s", inet_ntoa(client.sin_addr));
        if (eve_debug)	// Restrict to single instance for debugging
            connection_handler(client_sock);
        else {
            /* FORK: Create child process */
            pid = fork();
            if (pid < 0) {
                perror("Fork process failed");
                exit(1);
            } else if (pid == 0) {
                /* This is the client process */
                close(socket_desc);
                connection_handler(client_sock);
                exit(0);
            } else {
                // Host process, close no longer needed socket
                close(client_sock);
            }
        }
    }

    if (client_sock < 0) {
        perror("Socket accept failed");
        return 1;
    }

    log2stderr("Stopping EVE server...");
    return 0;
}

// ----------------------------------------------------------------------------
// trim leading & trailing spaces from string s (return modified string s)
// alg:
// - skip leading spaces, via cp1
// - shift remaining *cp1's to the left, via cp2
// - mark a new end of string
// - replace trailing spaces with '\0', via cp2
// - return the trimmed s
//
char *str_trim(char *s) {
    char *cp1;                              // for parsing the whole s
    char *cp2;                              // for shifting & padding
    // skip leading spaces, shift remaining chars
    for (cp1=s; isspace(*cp1); cp1++ )      // skip leading spaces, via cp1
        ;
    for (cp2=s; *cp1; cp1++, cp2++)         // shift left remaining chars, via cp2
        *cp2 = *cp1;
    *cp2-- = 0;                             // mark new end of string for s
    // replace trailing spaces with '\0'
    while ( cp2 > s && isspace(*cp2) )
        *cp2-- = 0;                         // pad with '\0's
    return s;
}

#define MAX_MSG_LEN 1023
/*
 * This will handle the connection for each client
 */
void *connection_handler(int socket_desc) {
    // Get the socket descriptor
    int sock = socket_desc;
    int read_size, write_sz_actual, write_size = 0;
    socklen_t raddrlen;
    struct sockaddr_in client;
    char client_message[MAX_MSG_LEN+1], host_message[MAX_MSG_LEN+1];
    EVE_STATE eve_state;

    memset(&eve_state, 0, sizeof(eve_state));
    eve_state.state = NORMAL;         // Record/replay initial state

    raddrlen = sizeof(client); // Must pass length of buffer to getpeername()
    getpeername(sock, (struct sockaddr *) &client, &raddrlen);
    log2stderr("SOCKet %d connected to %s:%d",
               sock, inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    eve_state.socket = sock;
    SPI_set_channel(&eve_state.spi, 1);	  // Init SPI (CS!=0 ensures SPI handle is retrieved)
    SPI_set_delay(&eve_state.spi, 1000);  // Default SPI frequency 1MHz = clock period 1000us
    eve_state.spi.channel_state_enabled = spi_stateful;
    log2stderr("SPI device '%s', I2C device '%s'", SPI_get_device(), i2c_get_device());
    if (eve_debug) {	// Send a message to the client
#if 0               // No, don't, it confuses EVE...
        sprintf(host_message, "Connection %d: [Beaglebone EVE server %s]\n", sock, SWREVISION + 1);
        write_sz_actual = write(sock, host_message, strlen(host_message));
#endif
    }
    // Receive a message from the client
    while ((read_size = recv(sock, client_message, MAX_MSG_LEN, 0)) > 0) {
        client_message[read_size] = '\0'; // NUL terminate input!
        str_trim(client_message);
        if (eve_debug & EVE_DEBUG_SOCKET)
            log2stderr("SOCK RX: '%s'", client_message);
        if (strlen(client_message) > 0) {	// skip empty lines
            if ((eve_state.state == RECORDING) && eve_state.fd_record) {	// record commands.
                fputs(client_message, eve_state.fd_record);					// Move to epd_tcp_asciicmd?
                fputs("\n", eve_state.fd_record);
            }
            write_size = epd_tcp_asciicmd(&eve_state, client_message, host_message);
            if (write_size < 0) {
                close(sock); // Client requested quit, close the socket
                break;
            }
            // Send the reply message back to the client
            write_sz_actual = write(sock, host_message, write_size);
            if (eve_debug & EVE_DEBUG_SOCKET)
                log2stderr("SOCK TX(%d): %s", write_size, str_trim(host_message));
            if (write_sz_actual != write_size)
                log2stderr("SOCKet write truncated, %d of %d bytes written", write_sz_actual, write_size);
        }
    }

    if (read_size == 0 || write_size < 0) {
        log2stderr("SOCKet %d closed by %s:%d", sock, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        fflush(stdout);
    } else if (read_size == -1) {
        perror("Socket receive failed");
    }

    return 0;
}

/*
 * Implements semaphores (See GENIE implementation)
 * Synopsis:
 *     semaphore <action> <name>
 * Parameters:
 *     <action> is either init, wait, try, release or destroy
 *         init    creates the semaphore and sets the value to 1
 *         wait    decreases the value by one.
 *                 Suspends process while value is less than 0
 *         try     decreases value by one.
 *                 Fails if value is less or equal to 0
 *         release increases value by 1
 *         destroy deallocates semaphore. All suspended processes will fail
 *     <name>   is a global (for the cpu system) string identifier
 * Return:
 *     If a command succeeds it will return 1
 *     otherwise 0
 */


/*
 * System call with output to a pipe: run external Linux shell command
 * Limitations & bugs:
 *     Doesn't handle large amounts of output well
 * Return (planned, not currently implemented):
 *     Returns everything the command writes to stdout and substitutes
 *     newlines with spaces
 */
int mySystem(const char *cmd, char *retstr, int maxlen) {
    char *rc;
    FILE *fpipe;

    if (0 == (fpipe = (FILE*) popen(cmd, "r"))) {
        perror("popen() failed");
        exit(1);
    }
    *retstr = '\0';	// Clear return
    // Only save last line of multi-line output!
    while (NULL != (rc = fgets(retstr, maxlen, fpipe))) {
        str_trim(retstr);
    }
    pclose(fpipe);
    return strlen(retstr);
}

/*-----------------------------------------------------------------------------
  EVE TCP Command handler
  -------------------------------------------------------------------------------
  Handles TCP (telnet) commands. All numeric field may be decimal or hex.
  Command format:
  SPI_SELECT <channel>, SELECT CPLD_GPIO<n>
  SPI_DELAY <ns>, DELAY <ns>
  SPI_PADDING <bytes>, DUMMY <bytes>
  GRW <hex data to write> <# bytes to read>
  I2C_RD <addr> <# bytes>
  I2C_WR <addr> <# bytes> <hex data>
  I2C_RD_RAND <addr> <reg> <# bytes>
  I2C_WR_RAND <addr> <reg> <# bytes> <hex data>
  JTAG <JTAG microcommands>
  JTAG_VECTOR <vector> <repeat> <vector number>
  PORTMON
  RECORD <ON|OFF> <filename>
  REPLAY <filename>
  RUN <system command>
  VERSION
  QUIT
  Return length of string in result buffer (resbuf), including terminating nul

  Obsolete Commands (only on available on Rabbit):
  W, R, LED/RELAY, GP*, SEMAPHORE, GSRW, GMW, GMW4, WP, RP, WPRP,
  P_I2C_WR, P_I2C_RD, P_I2C_RD_RAND, PCI9030_TEST, RESET_VAL_BOARD, STATS
  MIIMWRITE, MIIMREAD, MICROSETUP, MICROCMD

  Current timing on various platforms:
  RCM3720:    R: 2.30ms, W: 2.60ms (measured with scope)
  R: 4.75ms, W: 5.15ms (TCL) TCP overhead ~ 2.5ms
  RCM4010:    R: 2.07ms, W: ?.??ms (TCL)
  RCM4310:    R: 1.48ms, W: 1.66ms (TCL)
  Genie:      R: 1 ms,   W: 1 ms   (TCL)
  Beaglebone: R: 0.55ms, W: 0.55ms (TCL,275MHz)(500MHz:0.40ms)(600MHz:0.37ms)(720MHz:0.34ms)
*/
#define WPRP_MAX_BYTES  67
#define ERRSTR "[0:errno %d]\r\n"
#define EMPTYSTR "[]\r\n"
#define EMPTYSTRLEN 4

int epd_tcp_asciicmd(EVE_STATE *state, char *cmdbuf, char *resbuf) {
    int  l, rc;
    unsigned udata;
    char address, reg, rxlen, txlen;
    char *cmd, *txstr, *tok, *pres;
    char txbuf[WPRP_MAX_BYTES], rxbuf[WPRP_MAX_BYTES];

    cmd = strtok(cmdbuf, " \r\n");
    if (!cmd)
        return 0; // This should never happen...
    strcpy(resbuf, "[0:errno 0]\r\n"); // Is this the correct error response?
    rc = sizeof("[0:errno 0]\r\n") - 1;
    // Parse other commands. Command token already ready

    ////////////////////////////////////////////////////////////////////////////
    // GRW : Generic SPI R/W
    // GRW <hex data to write> <# bytes to read>
    if (0 == strcasecmp(cmd, "grw")) {
        txstr = strtok(NULL, " ");
        if (txstr) {
            tok = strtok(NULL, " ");
            rxlen = tok ? (((char) strtol(tok, (char **) NULL, 0)) & 0xf) : 0;
            *resbuf = '[';
            rc = 1;
            //log2stderr("DEBUG GRW1: rc=%d '%s'", rc, resbuf);
            rc += SPI_hrw(&state->spi, txstr, rxlen, resbuf + 1, 0);
            //log2stderr("DEBUG GRW2: rc=%d '%s'", rc, resbuf);
            strcpy(resbuf + rc, "]\r\n");
            rc += 3;
            //log2stderr("DEBUG GRW3: rc=%d '%s'", rc, resbuf);
        }
        //////////////////////////////////////////////////////////////////////////
        // GSRW : Generic Simultaneous SPI R/W
        // GSRW <hex data to write> <# bytes to read>
    } else if (0 == strcasecmp(cmd, "gsrw")) {
        txstr = strtok(NULL, " ");
        if (txstr) {
            tok = strtok(NULL, " ");
            rxlen = tok ? (((char) strtol(tok, (char **) NULL, 0)) & 0xf) : 0;
            *resbuf = '[';
            rc = 1;
            rc += SPI_hrw(&state->spi, txstr, rxlen, resbuf + 1, 1);
            strcpy(resbuf + rc, "]\r\n");
            rc += 3;
        }
        //////////////////////////////////////////////////////////////////////////
        // SPI_SELECT : SPI select active chip select (GLOBAL)
        // SPI_SELECT <channel>, SELECT CPLD_GPIO<n>,
    } else if (0 == strcasecmp(cmd, "select") ||
               0 == strcasecmp(cmd, "spi_select")) {
        tok = strtok(NULL, " ");
        if (tok) {
            if (0 == strncmp(tok, "CPLD_GPIO", 9)) // Genie spi_select support
                tok += 9;
            rc = sprintf(resbuf, "[%d]\r\n", SPI_set_channel(&state->spi, (int) strtol(tok, (char **) NULL, 0) ) );
        }
        //////////////////////////////////////////////////////////////////////////
        // SPI_GPIOCS : SPI uses GPIOs as chip selects (GLOBAL)
    } else if (0 == strcasecmp(cmd, "spi_gpiocs")) {
        tok = strtok(NULL, " ");
        if (tok) {	// NB: sets active chip select to 0 as side effect!
            rc = sprintf(resbuf, "[%d]\r\n", SPI_set_gpio_cs(strtol(tok, (char **) NULL, 0)));
        }
        //////////////////////////////////////////////////////////////////////////
        // SPI_GPIOMM : SPI uses memory mapped GPIO (GLOBAL)
    } else if (0 == strcasecmp(cmd, "spi_gpiomm")) {
        tok = strtok(NULL, " ");
        if (tok) {
            rc = sprintf(resbuf, "[%d]\r\n", SPI_set_mm_gpio(strtol(tok, (char **) NULL, 0)));
        }
        //////////////////////////////////////////////////////////////////////////
        // SPI_DEVICE : SPI select active SPI device file (GLOBAL)
    } else if (0 == strcasecmp(cmd, "spi_device")) {
        tok = strtok(NULL, " ");
        if (tok) {
            int cs;
            rc = SPI_set_device(tok);
            if (rc) // Error
                rc = sprintf(resbuf, "[0:errno %d]\r\n", rc);
            else {	// OK
                cs = SPI_set_channel(&state->spi, -1);	// close current device
                cs = SPI_set_channel(&state->spi, cs);	// open new device, same channel select
                rc = sprintf(resbuf, "[%s %d]\r\n", tok, cs);
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // SPI_DELAY : SPI bit time in ns (GLOBAL)
        // SPI_DELAY <ns>, DELAY <ns>
    } else if (0 == strcasecmp(cmd, "spi_delay") ||
               0 == strcasecmp(cmd, "delay")) {
        tok = strtok(NULL, " ");
        if (tok) {
            rc = sprintf(resbuf, "[%d]\r\n", SPI_set_delay(&state->spi, strtol(tok, (char **) NULL, 0)));
        }
        //////////////////////////////////////////////////////////////////////////
        // SPI_PADDING : SPI # of padding bytes. Max 15. (GLOBAL)
        // SPI_PADDING <bytes>, DUMMY <bytes>
    } else if (0 == strcasecmp(cmd, "spi_padding") ||
               0 == strcasecmp(cmd, "dummy")) {
        tok = strtok(NULL, " ");
        if (tok) {
            rc = sprintf(resbuf, "[%d]\r\n", SPI_set_padding(&state->spi, ((int) strtol(tok, (char **) NULL, 0)) & 0xf) );
        } else {
            rc = sprintf(resbuf, "[%d]\r\n", SPI_set_padding(&state->spi, -1));
        }
        //////////////////////////////////////////////////////////////////////////
        // I2C_RD : I2C read
        // I2C_RD <addr> <# bytes>
    } else if (0 == strcasecmp(cmd, "i2c_rd")) { // I2C read
        tok   = strtok(NULL, " ");
        if (tok) {
            address = ((char) strtol(tok, (char **)NULL, 0)) & 0x7f;
            tok   = strtok(NULL, " ");
            rxlen = ((char) strtol(tok, (char **)NULL, 0)) & 0xf;
            if ((0 < rxlen) && (rxlen <= SPI_MAX_BYTES)) {
                int i2c_handle = i2c_open(NULL);
                if (i2c_read_bytes(i2c_handle, address, rxlen, (unsigned char *)rxbuf) > 0) {
                    rc = sprintf(resbuf, "[%d", rxlen);
                    pres = resbuf + rc; // save positions so we can replace '0x' with ': '
                    rc += mybuftohex(rxbuf, resbuf+rc, rxlen);
                    *pres++ = ':';
                    *pres = ' '; // replace '0x' with ': '
                    strcpy(resbuf+rc, "]\r\n");
                    rc += 3;
                }
                i2c_close(i2c_handle);
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // I2C_WR : I2C write
        // I2C_WR <addr> <# bytes> <hex data>
    } else if (0 == strcasecmp(cmd, "i2c_wr")) { // I2C write
        tok   = strtok(NULL, " ");
        if (tok) {
            address = ((char) strtol(tok, (char **)NULL, 0)) & 0x7f;
            tok   = strtok(NULL, " ");
            // Ignore length field, this is only needed in GENIE
            // txlen = ((char) strtol(tok, (char **)NULL, 0)) & 0x7f;
            tok   = strtok(NULL, " ");
            txlen = myhextobuf(tok, txbuf, SPI_MAX_BYTES);
            if ((0 < txlen) && (txlen <= SPI_MAX_BYTES)) {
                int i2c_handle = i2c_open(NULL);
                l = i2c_write(i2c_handle, address, txlen, (unsigned char *)txbuf);
                i2c_close(i2c_handle);
                if (l > 0) rc = sprintf(resbuf, "[%d]\r\n", l);
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // I2C_RD_RAND : I2C read random access
        // I2C_RD_RAND <addr> <reg> <# bytes>
    } else if (0 == strcasecmp(cmd, "i2c_rd_rand")) { // I2C random read
        tok   = strtok(NULL, " ");
        if (tok) {
            address = ((char) strtol(tok, (char **)NULL, 0)) & 0x7f;
            tok   = strtok(NULL, " ");
            reg   = tok ? (((char) strtol(tok, (char **)NULL, 0)) & 0xff) : 0;
            tok   = strtok(NULL, " ");
            rxlen = tok ? (((char) strtol(tok, (char **)NULL, 0)) & 0xf) : 0;
            if ((0 < rxlen) && (rxlen <= SPI_MAX_BYTES)) {
                int i2c_handle = i2c_open(NULL);
                if (i2c_read_rand(i2c_handle, address, reg, rxlen, (unsigned char *)rxbuf) > 0) {
                    rc = sprintf(resbuf, "[%d", rxlen);
                    pres = resbuf + rc; // save positions so we can replace '0x' with ': '
                    rc += mybuftohex(rxbuf, resbuf+rc, rxlen);
                    *pres++ = ':';
                    *pres = ' '; // replace '0x' with ': '
                    strcpy(resbuf+rc, "]\r\n");
                    rc += 3;
                }
                i2c_close(i2c_handle);
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // I2C_WR_RAND : I2C write random access
        // I2C_WR_RAND <addr> <reg> <# bytes> <hex data>
    } else if (0 == strcasecmp(cmd, "i2c_wr_rand")) { // I2C random write
        tok   = strtok(NULL, " ");
        if (tok) {
            address = ((char) strtol(tok, (char **)NULL, 0)) & 0x7f;
            tok   = strtok(NULL, " ");
            if (tok) {
                reg   = ((char) strtol(tok, (char **)NULL, 0)) & 0xff;
                tok   = strtok(NULL, " ");
                // Ignore length field, this is only needed in GENIE
                // txlen = ((char) strtol(tok, (char **)NULL, 0)) & 0x7f;
                tok   = strtok(NULL, " ");
                txlen = myhextobuf(tok, txbuf, SPI_MAX_BYTES);
                if ((0 < txlen) && (txlen <= SPI_MAX_BYTES)) {
                    int i2c_handle = i2c_open(NULL);
                    l = i2c_write_rand(i2c_handle, address, reg, txlen, (unsigned char *)txbuf);
                    i2c_close(i2c_handle);
                    if (l >= 0) rc = sprintf(resbuf, "[%d]\r\n", txlen);
                }
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // MIIMWRITE
    } else if (0 == strcasecmp(cmd, "miimwrite")) {
        if (!(tok = strtok(NULL, " "))) return rc; // Default error code
        address   = ((char) strtol(tok, (char **)NULL, 0)) & 0x1f;  // 5 bits
        if (!(tok = strtok(NULL, " "))) return rc;
        reg       = ((char) strtol(tok, (char **)NULL, 0)) & 0x1f;  // 5 bits
        if (!(tok = strtok(NULL, " "))) return rc;
        udata     = (unsigned int) strtol(tok, (char **)NULL, 0);
        rc        = miim_write((void *)&state->spi, address, reg, udata);
        strcpy(resbuf, EMPTYSTR);
        return EMPTYSTRLEN;  // length of "[]", excluding terminating nul
        //////////////////////////////////////////////////////////////////////////
        // MIIMREAD
    } else if (0 == strcasecmp(cmd, "miimread")) {
        tok     = strtok(NULL, " ");
        address = ((char) strtol(tok, (char **)NULL, 0)) & 0x1f;  // 5 bits
        tok     = strtok(NULL, " ");
        reg     = ((char) strtol(tok, (char **)NULL, 0)) & 0x1f;  // 5 bits
        udata   = (unsigned int) miim_read((void *)&state->spi, address, reg);
        rc      = sprintf(resbuf, "[%u]\r\n", udata);
        //////////////////////////////////////////////////////////////////////////
        // MICROSETUP : MIIM microsetup
    } else if (0 == strcasecmp(cmd, "microsetup")) {
        cmd     = strtok(NULL, " ");
        tok     = strtok(NULL, " ");
        if (cmd && tok)
            rc = miim_cmd_microsetup(NULL, cmd, tok, resbuf);
        //////////////////////////////////////////////////////////////////////////
        // MICROCMD : MIIM microcommand
        //            Not implemented yet.
//   } else if (0 == strcasecmp(cmd, "microcmd")) {
//     tok     = strtok(NULL, " ");
//     if (tok)
//       rc = miim_cmd_microcmd(NULL, tok, resbuf, MAX_MSG_LEN);
        //////////////////////////////////////////////////////////////////////////
        // JTAG : JTAG microcommands
        // JTAG <microcommands>
    } else if (0 == strcasecmp(cmd, "jtag")) {
        tok  = strtok(NULL, " ");
        if (tok)
            rc = jtag_MicroCmd(tok, resbuf, MAX_MSG_LEN);
        //////////////////////////////////////////////////////////////////////////
        // JTAG_VECTOR : WGL vector support
        // jtag_vector <vector> <repeat> <vector number>
    } else if (0 == strcasecmp(cmd, "jtag_vector")) {
        tok   = strtok(NULL, " ");
        if (tok) {
            char *vector = tok;
            tok     = strtok(NULL, " ");
            int rpt = tok ? ((int) strtol(tok, (char **)NULL, 0)) : -1;
            tok   = strtok(NULL, " ");
            int num = tok ? ((int) strtol(tok, (char **)NULL, 0)) : -1;
            if ((0 < rpt) && (0 <= num)) {
                num = jtag_Vector(vector, rpt, num);
                if (num < 0) {
                    strcpy(resbuf, EMPTYSTR);
                    rc = EMPTYSTRLEN;  // length of "[]", excluding terminating nul
                } else {
                    rc = sprintf(resbuf, "[%i]\r\n", num);
                }
            }
        }
        ////////////////////////////////////////////////////////////////////////
        // RUN : Unix commands.
    } else if (0 == strcasecmp(cmd, "run")) {
        log2stderr("System command: '%s %s'", cmd, cmdbuf+4);
        *resbuf = '[';
        rc = 1 + mySystem(cmdbuf+4, resbuf+1, 255);
        strcpy(resbuf + rc, "]\r\n");
        rc += 3;
        //////////////////////////////////////////////////////////////////////////
        // VERSION: Version string looks like "$Revision: 1.8 $"
    } else if (0 == strcasecmp(cmd, "version")) {
        rc = sprintf(resbuf, "[Beaglebone EVE server %s]\r\n", SWREVISION + 1);
        //////////////////////////////////////////////////////////////////////////
        // SEMAPHORE: What to do here? TBD see GENIE
    } else if (0 == strcasecmp(cmd, "semaphore")) {
        rc = sprintf(resbuf, "[1:]\r\n");
        //////////////////////////////////////////////////////////////////////////
        // RECORD <ON|OFF> <filename>:
    } else if (0 == strcasecmp(cmd, "record")) {
        tok = strtok(NULL, " ");
        if (tok) {
            if (0 != strcasecmp(tok, "ON")) {
                // stop recording
                if (state->state == RECORDING && state->fd_record) {
                    fclose(state->fd_record);
                    state->fd_record = NULL;
                }
                if (state->state == RECORDING) log2stderr("RECORD stopped", tok);
                state->state = NORMAL;
                rc = sprintf(resbuf, "[0]\r\n");
            } else {
                // start recording
                tok = strtok(NULL, " ");
                if (tok) {
                    state->fd_record = fopen(tok, "w+");
                    if (state->fd_record) {
                        state->state = RECORDING;
                        log2stderr("RECORD to: '%s'", tok);
                        rc = sprintf(resbuf, "[%s]\r\n", tok);
                    } else {
                        rc = sprintf(resbuf, ERRSTR, errno);
                    }
                }
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // REPLAY <filename>:
    } else if (0 == strcasecmp(cmd, "replay")) {
        tok = strtok(NULL, " ");
        if (tok && (state->state == NORMAL) && !state->fd_record) {
            state->fd_record = fopen(tok, "r");
            if (state->fd_record) {
                int i = 0;
                state->state = REPLAYING;
                log2stderr("REPLAY from: '%s'", tok);
                while (NULL != fgets(txbuf, sizeof(txbuf), state->fd_record)) {
                    str_trim(txbuf);	// Why is this necessary???
                    if (eve_debug) log2stderr("REPLAY(%d) '%s'", i, txbuf);
                    txlen = epd_tcp_asciicmd(state, txbuf, rxbuf);
                    ++i;
                }
                fclose(state->fd_record);	// Close file when read
                state->fd_record = NULL;
                log2stderr("REPLAYed %d commands", i);
                state->state = NORMAL;
                rc = sprintf(resbuf, "[%s]\r\n", tok);
            } else {
                rc = sprintf(resbuf, ERRSTR, errno);
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // GPIOTEST: <gpio> <toggle count> [mode]
    } else if (0 == strcasecmp(cmd, "gpiotest")) {
        unsigned int i, gpio, tcnt;
        char *sgpio, *stcnt, *smode;
        sgpio = strtok(NULL, " ");
        stcnt = strtok(NULL, " ");
        smode = strtok(NULL, " ");
        if (sgpio && stcnt) {
            gpio = (unsigned int) strtoul(sgpio, (char **) NULL, 0);
            tcnt = (unsigned int) strtoul(stcnt, (char **) NULL, 0);
            i = gpio_export(gpio);
            if (eve_debug & EVE_DEBUG_GPIO) log2stderr("GPIO_export(%d): %d", gpio, i);
            i = gpio_set_dir(gpio, 1);
            if (eve_debug & EVE_DEBUG_GPIO) log2stderr("GPIO_set_dir(%d): %d", gpio, i);
            if (eve_debug & EVE_DEBUG_GPIO) log2stderr("GPIO toggle %d, mode: %s", tcnt, (smode) ? "gpio_mmdo_set" : "gpio_mm_set" );
            for (i=0; i<tcnt; i++)
                (smode) ? gpio_mmdo_set(gpio, i%2) : gpio_mm_set(gpio, i%2);
            i = gpio_set_dir(gpio, 0);
            if (eve_debug & EVE_DEBUG_GPIO) log2stderr("GPIO_set_dir(%d): %d", gpio, i);
            i = gpio_unexport(gpio);
            if (eve_debug & EVE_DEBUG_GPIO) log2stderr("GPIO_unexport(%d): %d", gpio, i);
            rc = sprintf(resbuf, EMPTYSTR);
        }
        //////////////////////////////////////////////////////////////////////////
        // SPITEST: <address> <tx data> [rx data]
    } else if (0 == strcasecmp(cmd, "spitest")) {
        long int aval, tval, rval;
        char tx[20], rx[20];
        char *addr, *tdata, *rdata;
        addr  = strtok(NULL, " ");
        tdata = strtok(NULL, " ");
        if (addr && tdata) {
            aval = strtoul(addr,  (char **) NULL, 0);
            tval = strtoul(tdata, (char **) NULL, 0);
            sprintf(tx, "0x%6.6lx%8.8lx", 0x800000 | aval, tval);	// set write bit in address field
            SPI_hrw(&state->spi, tx, 0, rx, 0);						// write
            sprintf(tx, "0x%6.6lx", aval);
            SPI_hrw(&state->spi, tx, 4, rx, 0);						// read
            rval = strtoul(rx, (char **) NULL, 16);
            rdata = strtok(NULL, " ");
            if (rdata) tval = strtoul(rdata, (char **) NULL, 0);	// check against this value instead
            if (tval != rval) log2stderr("SPITEST failed: TX:0x%08lx != RX:0x%08lx", tval, rval);
            rc = sprintf(resbuf, "[0x%08lx]\r\n", rval);
        }
        //////////////////////////////////////////////////////////////////////////
        // RepReadES <ADDR> <WordCnt>
        //    ADDR must be A[22:0], ie. byte addressing
        //    FAST_REGS::CFG_STATUS_2 and FAST_REGS::SLOWDATA_MSB/LSB are hardcoded
        //    Assumes Chip seelsct etc are already set correctly
        // TODO: Make FATS_REGS register addresses configurable?
    } else if (0 == strcasecmp(cmd, "RepReadES")) {
        long int aval, cval;
        char txa[20], rx[20];
        unsigned char txb[10], rxb[10];
        char *addr, *count;
        addr  = strtok(NULL, " ");
        count = strtok(NULL, " ");
        if (addr && count) {
            aval = strtoul(addr,  (char **) NULL, 0);
            cval = strtoul(count, (char **) NULL, 0);
            if (cval < (MAX_MSG_LEN-4)/(2+2*4+1)) { // Ensure buffer does not overflow
                sprintf(txa, "0x%6.6lx", aval+1);  // Odd address results in aborted read
                // FAST_REGS:CSR_REGS:CFG_STATUS_2 register (Leda & OHFPGA)
                txb[0] = 0x3f; txb[1] = 0x00; txb[2] = 0x07;
                *resbuf = '[';
                rc = 1;
                for (int i = cval; i >= 1; i--) {
                    int polls = 16; // give up after 16 polls
                    // Initiate indirect read
                    SPI_hrw(&state->spi, txa, 4, rx, 0);       // TX 3 bytes, RX 4 bytes
                    do {
                        SPI_brw(&state->spi, txb, 3, rxb, 4, 0); // TX 3 bytes, RX 4 bytes
                    } while (--polls && (0x8000 & rxb[3]));    // Test for CFG_STATUS_2::RD_IN_PROGRESS(15)
                    // read 4 bytes from FAST_REGS:CSR_REGS:SLOWDATA_MSB + LSB registers
                    rc += SPI_hrw(&state->spi, "0x3f0000", 4, resbuf + rc, 0);
                    if (i > 1) *(resbuf + rc++) = ' ';
                }
                strcpy(resbuf + rc, "]\r\n");
                rc += 3;
            }
        }
        //////////////////////////////////////////////////////////////////////////
        // DEBUG : Set debug level. Return level if no parameter (GLOBAL)
    } else if (0 == strcasecmp(cmd, "eve_debug")) {
        tok = strtok(NULL, " ");
        if (tok)
            eve_debug = (int) strtol(tok, (char **) NULL, 0);
        rc = sprintf(resbuf, "[%d]\r\n", eve_debug);
        //////////////////////////////////////////////////////////////////////////
        // PORTMON : Return portmon change set
    } else if (0 == strcasecmp(cmd, "stats")) {
        rc = stats_cmd(cmd+6, resbuf, MAX_MSG_LEN, &state->portmon, &state->spi);
        //////////////////////////////////////////////////////////////////////////
        // QUIT
    } else if (0 == strcasecmp(cmd, "quit")) {
        rc = -1; // close socket!
        //////////////////////////////////////////////////////////////////////////
        // Unknown command
    } else {
        rc = sprintf(resbuf, "[0:unknown command: %s]\r\n", cmd);
        log2stderr("Unknown command: '%s'", cmd);
    }
    return rc;
}
