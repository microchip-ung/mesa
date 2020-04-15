/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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


//***************************************************************************
//* This file contains board specific functions needed for running the PHY  *
//* API at a Atom12 evaluation board. The evaluation board is equipped with *
//* a Rabbit CPU board, which do the communication with the PHY using a     *
//* socket connection. The actual API is running on the host computer. The  *
//* API has been tested with both Linux (Red Hat) and Cygwin.               *
//***************************************************************************

#include <netdb.h>  // For socket
#include <stdarg.h> // For va_list
#include "vtss_api.h"   // For BOOL and friends
#include "vtss_appl.h"  // For board types
#include <unistd.h>     // For TCP read/write

// Fixed socket port for the CPU board used 
#define CPU_BOARD_PORT "23" 

// Define which trace group to use for VTSS printout in this file
#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

/* ================================================================= *
 *  Misc. functions 
 * ================================================================= */

// Function defining the port interface.
static vtss_port_interface_t port_interface(vtss_port_no_t port_no)
{
    return VTSS_PORT_INTERFACE_SGMII;
}

/* ================================================================= *
 *  Board specific functions
 * ================================================================= */
int sockfd;

// Function for doing write access to the board CPU board via socket
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


// Function for do read access from the board CPU board via socket
// In :  Buffer - Pointer for the data read via the socket.
static void socket_read (char *buffer) {
    
    int n;
    VTSS_MSLEEP(100);
    n = read(sockfd, buffer, 255);
    if (n < 0) 
        T_E("ERROR reading from socket");
}

// Function for initializing the socket connection to the CPU board.
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




// Each board can have it own way of communicating with the chip. The miim read and write function are called by the API 
// when the API needs to do register access.


// Miim read access specific for this board.
// In : port_no - The port to access.
//      addr    - The address to access
//
// In/Out:  value   - Pointer to the value to be returned
vtss_rc atom12_miim_read(const vtss_inst_t    inst,
                         const vtss_port_no_t port_no,
                         const u8             addr,
                         u16                  *const value)
{
    char * pch;
    char *endptr;
    char buffer[255];
    
    sprintf(buffer, "MIIM READ %d %d \n", port_no, addr);
    socket_write(&buffer[0]);

    strcpy(&buffer[0], "");
    socket_read(&buffer[0]);
    

    const char *ptr = buffer;
    char field [255];
    int n;

    while ( sscanf(ptr, "%255[^0x]%n", field, &n) == 1 )
    {
        ptr += n; /* advance the pointer by the number of characters read */
        ++ptr; /* skip the delimiter */
    }
    ptr--;
    sscanf(ptr, "%s", field);

    pch = strtok (buffer, "\n"); // Skip the miim read 
    pch = strtok (NULL, "\n"); 
    *value = strtol(field, &endptr, 16);
    
    return VTSS_RC_OK;
}

vtss_rc miim_read(const vtss_inst_t    inst,
                  const vtss_port_no_t port_no,
                  const u8             addr,
                  u16                  *const value)
{
    return (atom12_miim_read(inst, port_no, addr, value));
}

// Miim write access specific for this board.
// In : port_no - The port to access.
//      addr    - The address to access
///     value   - The value to written 
vtss_rc atom12_miim_write(const vtss_inst_t    inst,
                          const vtss_port_no_t port_no,
                          const u8             addr,
                          const u16            value)
{


    char buffer[255];
    sprintf(buffer, "MIIM WRITE %d %d %d\r", port_no, addr, value);
    T_I("miim_write port_no = %d, addr = %d, value = 0x%X", port_no, addr ,value);
    T_I("Buffer = %s", &buffer[0]);
    socket_write(&buffer[0]);
    socket_read(&buffer[0]);
    return VTSS_RC_OK;
}

vtss_rc miim_write(const vtss_inst_t    inst,
                   const vtss_port_no_t port_no,
                   const u8             addr,
                   const u16            value)
{
    return (atom12_miim_write(inst, port_no, addr, value));
}

#if defined(VTSS_CHIP_10G_PHY)
vtss_rc mmd_read(const vtss_inst_t     inst,
                 const vtss_port_no_t  port_no,
                 const u8              mmd,
                 const u16             addr,
                 u16                   *const value)
{
    /* Must be filled out by the user */
    T_I("mmd_read port_no = %d, mmd = %d addr = %d, value = 0x%X", port_no, mmd, addr, value);
    return VTSS_RC_OK;
}

vtss_rc mmd_write(const vtss_inst_t     inst,
                  const vtss_port_no_t  port_no,
                  const u8              mmd,
                  const u16             addr,
                  const u16             value)

{
    /* Must be filled out by the user */
    T_I("mmd_write port_no = %d, mmd = %d addr = %d, value = 0x%X", port_no, mmd, addr, value);
    return VTSS_RC_OK;
}

vtss_rc mmd_read_inc(const vtss_inst_t     inst,
                     const vtss_port_no_t  port_no,
                     const u8              mmd,
                     const u16             addr,
                     u16                   *buf,
                     u8                    count)
{
    /* Must be filled out by the user */
    T_I("mmd_read_inc port_no = %d, mmd = %d addr = %d", port_no, mmd, addr);
    return VTSS_RC_OK;
}
#endif /* VTSS_CHIP_10G_PHY */

// The Vitesse eval board has a CPLD that needs to be initialized. This is done with the CPLD function.

// Function for writing the CPLD.
// In : data - The data to be written to the CPLD
static void cpld_write(char * data) {
    char buffer[255];
    socket_write("spi select 1 \n\r");
    socket_write("spi gw ");
    socket_write(data);
    socket_write("\n");
    socket_read(&buffer[0]);
}

// Function for reading the CPLD.
static void cpld_read(char * addr) {
    char buffer[255];
    socket_write("spi select 1 \n \r");
    socket_write("spi grw ");
    socket_write(addr);
    socket_write("\n");
    socket_read(&buffer[0]);
}



// Function for initializing the hardware board.
int atom12_board_init(int argc, const char **argv, vtss_appl_board_t *board)
{
    char buffer[255];
    board->port_count = VTSS_PORTS; //Setup the number of port used 

    board->port_interface = port_interface; // Define the port interface

    board->init.init_conf->miim_read =  atom12_miim_read; // Set pointer to the MIIM read function for this board.
    board->init.init_conf->miim_write = atom12_miim_write; // Set pointer to the MIIM write function for this board.
#if defined(VTSS_CHIP_10G_PHY)
    board->init.init_conf->mmd_read =  mmd_read; // Set pointer to the MIIM read function for this board.
    board->init.init_conf->mmd_read_inc =  mmd_read_inc; // Set pointer to the MIIM read function for this board.
    board->init.init_conf->mmd_write = mmd_write; // Set pointer to the MIIM write function for this board.
#endif /* VTSS_CHIP_10G_PHY */


    if (board->init.init_conf->warm_start_enable != TRUE) {
        if (argc != 2) {
            printf("Usage  : %s <Rabbit IP Address> \n"  , argv[0]);
            printf("Example: %s 10.10.132.59 \n"  , argv[0]);
            exit(EXIT_SUCCESS);
        }

        socket_init(argv[1], CPU_BOARD_PORT); // Connect to the CPU board
        socket_read(&buffer[0]); // Clear the welcome message
    
        // Do the CPLD initialization
        cpld_write("80000200000141");
        cpld_write("80000200000140");
        cpld_write("80000300000000");
        cpld_write("80000300000001");
        cpld_read("000003 4");
    }

    return 0;
}






