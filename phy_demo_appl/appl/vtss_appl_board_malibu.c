// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/*
 *****************************************************************************************
* Revision 0.1  2018/06/27 sunilp
* 0.1 is the first version for the Malibu family of products (VSC8254/57/58(-xx))
 *****************************************************************************************

*/
//***************************************************************************
//* This file contains board specific functions needed for running the PHY  *
//* API on a Malibu Char board. The Characterization board is equipped with *
//* a Rabbit CPU board, which do the communication with the PHY using a     *
//* socket connection. The actual API is running on the host computer. The  *
//* API has been tested with both Linux (Red Hat) and Cygwin.               *
//***************************************************************************
#include <netdb.h>  // For socket
#include <stdarg.h> // For va_list
#include "vtss_api.h"   // For BOOL and friends
#include "vtss_appl.h"  // For board types
#include <unistd.h>     // For TCP read/write
#include <sys/stat.h>// For /sys/class/mdio file status
#include <sys/types.h>// For /sys/class/mdio file status
#include <errno.h>// For System errors
#include <unistd.h>// For /sys/class/mdio
#include <stdio.h> // for FILE types
#include <stdlib.h> // for EXIT_SUCCESS
#include "vtss/api/options.h"

// // Fixed socket port for the CPU board used
// For Malibu Char Board - Rabbit 6000 series - port is 2310
// For Malibu EVAL Board - Rabbit 4200 series - port is 26

#undef MDIO_ENABLED
#undef SPI32_ENABLED
#define RBT_RCM6710
//#define RBT_RCM4210

//#undef RBT_RCM6710
#ifdef RBT_RCM6710

#define RBT_RCM6710_CPU_BOARD_PORT "2310"
#define SPI32_ENABLED

#elif defined RBT_RCM4210

#define RBT_RCM4210_CPU_BOARD_PORT "26"
#define SPI32_ENABLED
//#define MDIO_ENABLED

#endif


// Define which trace group to use for VTSS printout in this file
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

/* ================================================================= *
 *  Misc. functions
 * ================================================================= */

// Function defining the port interface.
static vtss_port_interface_t port_interface(vtss_port_no_t port_no)
{
return VTSS_PORT_INTERFACE_RGMII;
}

   /* ================================================================= *
 *  Board specific functions
 * ================================================================= */

int sockfd;
FILE *miim_read_fp;
FILE *miim_write_fp;
char miim_read_file[64];

// Function for doing read access from the Rabbit CPU via socket
// In :  Buffer - Pointer for the data read via the socket.
static void socket_read (char *buffer) {
    int n;

    n = read(sockfd, buffer, 255);
    if (n < 0)
        T_E("ERROR reading from socket");
    //printf("...\n%s...\n", buffer);
}

// Function for doing write access to the Rabbit CPU via socket
// In :  Buffer - Pointer to the text to send over the socket
static void socket_write (char *buffer) {
    int n;
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) {
        T_E("ERROR writing to socket");
    } else {
        T_N("TX: %s\n", buffer);
    }
}

// Function for initializing the socket connection to the Rabbit CPU.
// In : server_addr - IP address for the CPU board
//      port        - Port used for the socket connection
static void socket_init (const char *server_addr, const char *port) {
    struct hostent *server;
    struct sockaddr_in serv_addr;

    int portno = atoi(port);

    server = gethostbyname(server_addr);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        T_E("ERROR opening socket");

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        T_E("ERROR connecting");
}


#if defined(VTSS_CHIP_10G_PHY)

////////////////////////////////////////////////////////////////////////////////
// MMD_Read and MMD_Write Code for Rabbit
// ---Unfinished because the rabbit code is optimized for neumonic values not straight port/mmd/addr hex values
////////////////////////////////////////////////////////////////////////////////
vtss_rc mmd_read_rbt(const vtss_inst_t    inst,
		     const vtss_port_no_t port_no,
                     const u8             mmd,
                           u16            addr,
                           u16            *const value)
{
  char buffer[255];
  int v;

//  sprintf(buffer, "mdio_rd %x %x %x ", port_no, mmd, addr);
  sprintf(buffer, "mdio_rd %x %x %x ", port_no, mmd, addr);
  printf ("MDIORD: %s\n", buffer);
  T_N("mmd_read_rbt: %s", buffer);
  socket_write(&buffer[0]);
  memset(buffer, 0, sizeof(buffer));
  socket_read(&buffer[0]);
  buffer[8] = '\0'; //NULL to strip off the CR/LF and prompt;
  v = (u32)strtol(buffer,NULL,16);  //TODO: put back the error checking that exists below.
  *value = v;
  printf ("MDIORD: value: 0x%x\n", v);
  //  if (sscanf(buffer, "%x", &v) == 1) {
  //    //  if (sprintf(num, "%x", &v) == 1) {
  //    *value = v;
  //  } else {
  //    T_E("missing value: buffer=%s, port 0x%X, mmd 0x%X, addr = 0x%X", buffer, port_no, mmd, addr);
  //  }
  //  T_N("mmd_read port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X", port_no, mmd, addr, *value);
  //printf("mmd_read port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X\n", port_no, mmd, addr, *value);
  return VTSS_RC_OK;
}

vtss_rc mmd_write_rbt(const vtss_inst_t    inst,
		      const vtss_port_no_t port_no,
                      const u8             mmd,
                            u16            addr,
                            u16            data)
{
  char buffer[255];

//  sprintf(buffer, "mdio_wr %x %x %x %x", port_no, mmd, addr, data);
  sprintf(buffer, " mdio_wr %x %x %x %x", port_no, mmd, addr, data);
  printf ("MDIOWR: %s\n", buffer);
  T_N("mmd_write_rbt: %s", buffer);
  socket_write(&buffer[0]);
  socket_read(&buffer[0]);
  return VTSS_RC_OK;
}

vtss_rc mmd_read_rbt_test( u8 port_no,
                           u8             mmd,
                           u16            addr,
                           u16            *value)
{
  char buffer[255];
  int v;

  //sprintf(buffer, "mmdrd %x %x %x ", port_no, mmd, addr);
  //sprintf(buffer, "mmd_rd %x %x %x ", port_no, mmd, addr);
  //sprintf(buffer, "mdio_rd %x %x %x ", port_no, mmd, addr);
  sprintf(buffer, "mdiord %x %x %x", port_no, mmd, addr);
  //sprintf(buffer, "spird %x %x %x\n", port_no, mmd, addr);
  printf ("%s\n", buffer);
  //  T_N("mmd_read_rbt: %s", buffer);
  socket_write(&buffer[0]);
  memset(buffer, 0, sizeof(buffer));
  socket_read(&buffer[0]);
  buffer[8] = '\0'; //NULL;
  printf ("%s\n", buffer);
  if (sscanf(buffer, "[%d]", &v) == 1) {
        *value = v;
  } else {
        T_E("missing value -buffer = %s, port %u, addr =%d", buffer, port_no, addr);
  }

  //u16 num = (u16)strtol(buffer,NULL,16);  // TODO: fix this function to work with mdio, has to do with Rabbit parameters in mdio mode
  //printf("%X\n", num);
  //*value = num;
  printf("tmp=%X\n", *value);
  //  if (sscanf(buffer, "%x", &v) == 1) {
  //    //  if (sprintf(num, "%x", &v) == 1) {
  //    *value = v;
  //  } else {
  //    T_E("missing value: buffer=%s, port 0x%X, mmd 0x%X, addr = 0x%X", buffer, port_no, mmd, addr);
  //  }
  //  value = num * 1;
  //  T_N("mmd_read port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X", port_no, mmd, addr, *value);
  printf("mmd_read port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X\n", port_no, mmd, addr, *value);
  return VTSS_RC_OK;
}

vtss_rc spi_read_rbt_test( u8 port_no,
                           u8             mmd,
                           u16            addr,
                           u16            *value)
{
  char buffer[255];
  u16 v;

  sprintf(buffer, "spird %x %x %x\n", port_no, mmd, addr);
  //printf ("%s\n", buffer);
  T_N("spi_read_rbt_test: %s", buffer);
  socket_write(&buffer[0]);
  memset(buffer, 0, sizeof(buffer));
  socket_read(&buffer[0]);
  buffer[8] = '\0'; //NULL to strip off the CR/LF and prompt;
  v = (u32)strtol(buffer,NULL,16);  //TODO: put back the error checking that exists below.
  *value = v;
  //  if (sscanf(buffer, "%x", &v) == 1) {
  //    //  if (sprintf(num, "%x", &v) == 1) {
  //    *value = v;
  //  } else {
  //    T_E("missing value: buffer=%s, port 0x%X, mmd 0x%X, addr = 0x%X", buffer, port_no, mmd, addr);
  //  }
  //  T_N("mmd_read port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X", port_no, mmd, addr, *value);
  printf("mmd_read port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X\n", port_no, mmd, addr, *value);
  return VTSS_RC_OK;
}


////////////////////////////////////////////////////////////////////////////////
// SPI_Read_Write Code for Rabbit
////////////////////////////////////////////////////////////////////////////////
vtss_rc spi_32bit_read_write_rbt(vtss_inst_t    inst,
		                 vtss_port_no_t port_no,
				 BOOL           rd, // (1=rd, 0=wr)
                                 u8             mmd,
                                 u16            addr,
                                 u32            *value)
{
  char buffer[255];
  u32 v;
  int i;

  errno = 0;


  if(rd){
    sprintf(buffer, "spird %x %x %x\n", port_no, mmd, addr);
    if ((mmd == 0x1e) && (addr == 0x9002 || addr == 0x9202)) {
      printf ("RD buffer = %s", buffer);
    }
    T_N("spi32_read_rbt: %s", buffer);
    socket_write(&buffer[0]);
    memset(buffer, 0, sizeof(buffer));
    socket_read(&buffer[0]);
    //    fprintf(stderr, "%s\n", buffer);
    buffer[8] = '\0'; //NULL to strip off the CR/LF and prompt;
    v = strtoul(buffer,NULL,16);
    if(buffer[0] == 'V' && buffer[1] == 'a' && buffer[2] == 'l'){ //TODO: put in better error checking to ensure valid response
      //    if(NULL == buffer){
      //    fprintf(stderr, "%s: not a decimal number\n", buffer);
      //    } else if ((ULONG_MIN == v || ULONG_MAX == v) && errno == ERANGE) {
      //      fprintf(stderr, "%s: out of range\n", buffer);
      //    } else if (v > INT_MAX) {
      //      fprintf(stderr, "%X: > INT_MAX\n", v);
      //    } else if (v < INT_MIN) {
      //      fprintf(stderr, "%X: < INT_MIN\n", v);
      T_E("missing value: buffer=%s, port 0x%X, mmd 0x%X, addr = 0x%X", buffer, port_no, mmd, addr);
      printf("ERROR: missing value: buffer=%s, port 0x%X, mmd 0x%X, addr = 0x%X\n", buffer, port_no, mmd, addr);
      fflush(stdout);
      return VTSS_RC_ERROR;
    } else{
      *value = (u32)v;
    }
    T_N("spi32_rd port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X", port_no, mmd, addr, *value);
    if ((mmd == 0x1e) && (addr == 0x9002 || addr == 0x9202)) {
      printf("spi32_rd port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X\n", port_no, mmd, addr, *value);
    }
  } else {
    sprintf(buffer, "spiwr %x %x %x %x\n", port_no, mmd, addr, *value);
    if ((mmd == 0x1e) && (addr == 0x9002 || addr == 0x9202)) {
      printf ("WR buffer = %s", buffer);
    }
    T_N("spi_write_rbt: %s", buffer);
    socket_write(&buffer[0]);
    socket_read(&buffer[0]);
    T_N("spi32_wr port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X", port_no, mmd, addr, *value);
    if ((mmd == 0x1e) && (addr == 0x9002 || addr == 0x9202)) {
      printf("spi32_wr port_no = 0x%X, mmd = 0x%X, addr = 0x%X, value = 0x%X\n", port_no, mmd, addr, *value);
    }
  }
  return VTSS_RC_OK;
}


#endif /* VTSS_CHIP_10G_PHY */



// Function for initializing the Rabbit Char board.
int malibu_char_board_init(int argc, const char **argv, vtss_appl_board_t *board)
{
  printf("In malibu_char_board_init\n"); fflush(stdout);
  board->descr = "Malibu_Char";
  board->target = VTSS_TARGET_10G_PHY;  // 10G PHY
  board->port_count = VTSS_PORTS; //Setup the number of port used

  board->port_interface = port_interface; // Define the port interface

  // board->init.init_conf->miim_read =  miim_read; // Set pointer to the MIIM read function for this board.
  // board->init.init_conf->miim_write = miim_write; // Set pointer to the MIIM write function for this board.
  //#if defined(VTSS_CHIP_10G_PHY)
#ifdef MDIO_ENABLED
  printf("API being configured for MDIO Accessor Functions (mmd_read/mmd_write) \n" );
  board->init.init_conf->mmd_read =  mmd_read_rbt; // Set pointer to the MMD read function for this board.
  //board->init.init_conf->mmd_read_inc =  *mmd_read_inc_rbt; // Set pointer to the MMD read function for this board.
  board->init.init_conf->mmd_write = mmd_write_rbt; // Set pointer to the MMD write function for this board.
#ifndef SPI32_ENABLED
  board->init.init_conf->spi_32bit_read_write = NULL; // Set pointer to the SPI read function for this board.
#endif
#endif

#ifdef SPI32_ENABLED
  printf("API being configured for MDIO Accessor Functions (mmd_read/mmd_write) \n" );
  board->init.init_conf->spi_32bit_read_write = *spi_32bit_read_write_rbt; // Set pointer to the SPI read function for this board.
#endif

  //#endif /* VTSS_CHIP_10G_PHY */

  //board->init.init_conf->warm_start_enable = FALSE; // Rob R. 1/17/17
  //if (board->init.init_conf->warm_start_enable != TRUE) {
  if (argc != 2) {
    printf("Usage  : %s <Rabbit IP Address> \n"  , argv[0]);
    printf("Example: %s 10.10.132.59 \n"  , argv[0]);
    exit(EXIT_SUCCESS);
  }

  //socket_init(argv[1], "2310"); // Connect to the CPU board

#ifdef RBT_RCM6710
  socket_init(argv[1], RBT_RCM6710_CPU_BOARD_PORT); // Connect to the CPU board via socket 2310
  printf("Init Socket on 2310,  Malibu Char Board is: 2310 \n" );
#elif defined RBT_RCM4210
  socket_init(argv[1], RBT_RCM4210_CPU_BOARD_PORT); // Connect to the CPU board via socket 26
  printf("Init Socket on 26,  Malibu Char Board is: 2310 \n" );
#else
  printf("<<<< ERROR >>>> RABBIT SOCKET NOT DEFINED \n" );
#endif
  //}

  //TEST CODE
  u16 *val = (u16 *)malloc(sizeof(u16));
#ifdef MDIO_ENABLED
  mmd_read_rbt_test(0x0, 0x1e, 0x0, val);
#endif
#ifdef SPI32_ENABLED
  spi_read_rbt_test(0x0, 0x1e, 0x0, val);
#endif
  printf("Dev ID = 0x%x\n",*val); fflush(stdout);

  //    u32 *val = (u32 *)malloc(sizeof(u32));
  //
  printf("Out malibu_char_board_init\n"); fflush(stdout);
  return 0;
}

// Function for initializing the hardware board.
int malibu_board_init(int argc, const char **argv, vtss_appl_board_t *board)
{
#if defined(RPI_MIIM)
  rpi_malibu_board_init(argc, argv, board); // Use init function for Raspberry PI MIIM.
#else
  malibu_char_board_init(argc, argv, board); // Use init function for Rabbit MIIM.
#endif /* RPI_MIIM */

  return 0;
}
