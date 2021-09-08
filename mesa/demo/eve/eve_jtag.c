/*
 * eve_jtag.c
 *
 *  Ported from Rabbit code on: July 1, 2014
 *      Author: jsa
 *
 */

#include <errno.h>
#include <stdint.h>		// uint8_t, uint32_t
#include <stdio.h>		// sprintf
#include <string.h>		// memset, strcpy, strlen
#include <assert.h>		// assert

#include "eve_sio.h"	// myhextobuf, mybuftohex
#include "eve_gpio.h"
#include "eve_jtag.h"

static int jtag_debug = 0; // JTAG enable debug output

// Map JTAG signals to Beaglebone GPIOs
#if 1   // Standard mapping
static unsigned int JTAG_TCK = P9_11; // P9_11 = 30 = 0x1E
static unsigned int JTAG_TDO = P9_12; // P9_12 = 60 = 0x3C
static unsigned int JTAG_TMS = P9_13; // P9_13 = 31 = 0x1F
static unsigned int JTAG_RST = P9_14; // P9_14 = 50 = 0x32
static unsigned int JTAG_TDI = P9_15; // P9_15 = 48 = 0x30
#else // BeagleBone PRU mapping:
static unsigned int JTAG_TCK = P8_27; // P8_27 = PRU1_b8  = 86 = 0x56
static unsigned int JTAG_TDO = P8_28; // P8_28 = PRU1_b10 = 88 = 0x58
static unsigned int JTAG_TMS = P8_29; // P8_29 = PRU1_b9  = 87 = 0x57
static unsigned int JTAG_RST = P8_30; // P8_30 = PRU1_b11 = 89 = 0x59
static unsigned int JTAG_TDI = P8_40; // P8_40 = PRU1_b7  = 77 = 0x4D
#endif
static unsigned int JTAG_DBG = P9_16; // P9_16 = 51 = 0x33
static int          IDLE_CLKS = 0;

// Map Rabbit bit IO primitives to Beaglebone functions
// Note: JTAG is ALWAYS memory mapped IO, for speed
#define BitWr(b,v)    gpio_mmdo_set((b),(v))
#define BitRd(b)      gpio_mm_get(b)
#define BitDir(b,d)   gpio_mmdo_dir((b),(d))

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define EMPTYSTR "[]\r\n"
#define EMPTYSTRLEN 4

#define CMD_MAX_LINE  512
#define JTAG_MAXLEN   (CMD_MAX_LINE / 2 - 2)
#define TMS           2     // Bit flag for setting TMS
#define TDI           1     // Bit flag for setting TDI
#define JTAG_MAX_DR   2048  // maximum length of the DR/boundary scan register
#define JTAG_MAXBUF   ((JTAG_MAX_DR/8)+1) // MUST be > JTAG_MAXLEN !
#if (JTAG_MAXLEN > JTAG_MAXBUF)
#error "Inconsistent JTAG buffer definitions!"
#endif

// Internal functions used by jtag_MicroCmd
char jtag_clk(char data);
void jtag_clk_edge(char hi);
void jtag_Disable(void);
void jtag_Reset(char type);
void jtag_EnterShiftIR(void);
void jtag_EnterShiftDR(void);
int  jtag_ChainLen(unsigned int nbits);
void jtag_SendData(char* pb, unsigned int nbits, char last);
void jtag_ReadData(char* pb, unsigned int nbits, char last);

/*-----------------------------------------------------------------------------
cmd : jtag_MicroCmd
-------------------------------------------------------------------------------
Synopsis:
    jtag <hex data>
Description:
Parameters:
  There are 5 basic JTAG commands
  0x00         : Exit JTAG, reset TAP, then tristates JTAG signals
  0x01         : Enable JTAG pins, and do JTAG Hard Reset
  0x02         : Enable JTAG pins, and do JTAG Soft Reset
  0x03         : Enable JTAG pins, and do JTAG Hard and Soft Reset
  0x11         : Enter Shift IR
  0x12         : Enter Shift DR
  0x13bbbbdd.. : Send Data
                 bbbb is 16 bits of how many bits to send (max 2048),
                 dd.. is the data to send
  0x14bbbbdd.. : Send and Read Data
                 bbbb is 16 bits of how many bits to send (max 2048),
                 dd.. is the data to send, which will be overwritten with
  0x15bbbb     : Read Data
                 bbbb is 16 bits of how many bits to read (max 2048)
  0x16bbbb     : Determine chain length
                 bbbb is 16 bits of how many bits to scan
  0x23bbbbdd.. : Send Data
                 Same as 0x13, except TAP controller stays in ShiftDR,
                 so additional data can be sent
  0x24bbbbdd.. : Send and Read Data
                 Same as 0x14, except TAP controller stays in ShiftDR,
                 so additional data can be sent and read
  0x25bbbb     : Read Data
                 Same as 0x15, except TAP controller stays in ShiftDR,
                 so additional data can be read
  Configuration commands:
  0x80         : Start/stop TCK low. Shift clock Hi->Lo.
  0x81         : Start/stop TCK high. Shift clock Lo->Hi.
  0x90         : Set pins to default. All pin configurations must be preceded
                 by JTAG exit (0x00), and followed by JTAG reset (0x01-0x03).
  0x91bb       : Set TCK pin to bb.
  0x92bb       : Set TDO pin to bb.
  0x93bb       : Set TMS pin to bb.
  0x94bb       : Set TRST pin to bb.
  0x95bb       : Set TDI pin to bb.
  0xAn         : Set number of extra clocks after entering idle state.

  All data are Little-Endian, ie:
    for bbbb, 0x1234 -> 3412
    for dd.., 0x12345678 -> 78563412
  This makes it easy to manage binary data as arrays of binary bytes.
  Data are sent in the order they appear in a command, so the first
  data byte to be sent is 0x78, the next is 0x56, and so on. Each byte
  is sent LSB first. 0x78 will result in the bitstream: 0001 1110.
  Data are received in the same order, LSB first.

  Commands can be chained, ie:
  0x011116 is JTAG reset, Enter Shift IR, Determine chain length
  0x011113180078563412 is:
    JTAG reset, Enter Shift IR, Send 24 (0x18) bits of data (0x12345678)

  Maximum command string length is 510 chars
*/
//int jtag_MicroCmd(tcp_Socket *s, const char *cmd_line, char *resbuf, int maxlen)
int jtag_MicroCmd(const char *cmd_line, char *resbuf, int maxlen)
{
  int l, bytelen, rc, outlen;
  unsigned int bitlen, pin;
  char lastchunk;
  char cmd, *endp, *cmdp, jtagbuf[JTAG_MAXLEN];
  const char *p;

  p = cmd_line;
  while(*p == ' ') p++;

  if ((strlen(p) / 2) >= JTAG_MAXLEN)
	  return(sprintf(resbuf, "[0:errno -1 cmd too long (%ld)]\r\n", strlen(p)));

  // jtagbuf is used both for input and output data.
  // Therefore 0x14/0x15/0x24/0x25 (Read Data) MUST be last command in command sequence!
  bytelen = myhextobuf(p, jtagbuf, JTAG_MAXLEN);
  if (bytelen < 1) {
    //miim_cmd_microcmd_syntaxerror();
    return -1;  //return CLI_USER_ERROR_INFO;
  }
  /* Interpret bytes */
  cmdp = jtagbuf;
  endp = cmdp + bytelen;
	strcpy(resbuf, EMPTYSTR);
  rc = EMPTYSTRLEN;  // Default response: length of "[]", excluding terminating nul
  while (cmdp < endp) {
    lastchunk = 0;
    cmd  = *cmdp++; // First byte is command, save it
    switch (cmd) {
      case 0x00:
        jtag_Disable();
        break;
      case 0x01:  // Init JTAG, Reset, move to IDLE
      case 0x02:
      case 0x03:
        jtag_Reset(cmd);
        break;
      case 0x11:
	jtag_EnterShiftIR();
	break;
      case 0x12:
	jtag_EnterShiftDR();
	break;
      case 0x13:  // Send Data (last chunk, exit ShiftDR)
        lastchunk = 1;
        // fall thru to send data
      case 0x23:  // Send Data (continue, stay in ShiftDR)
        bitlen = *cmdp++;
        bitlen += ((int) *cmdp++) << 8;
        jtag_SendData(cmdp, bitlen, lastchunk);
        l = (bitlen+7)/8;  // # of bytes
	    cmdp += l;         // skip past data bytes to next command
	break;
      case 0x14:  // Send and Read data (last chunk, exit ShiftDR)
      case 0x15:  // Read Data          (last chunk, exit ShiftDR)
        lastchunk = 1;
        // fall thru to send/rcv data
      case 0x24:  // Send and Read data (continue, stay in ShiftDR)
      case 0x25:  // Read Data          (continue, stay in ShiftDR)
        bitlen = *cmdp++;
        bitlen += ((int) *cmdp++) << 8;
        if ((cmd==0x15) || (cmd==0x25)) jtag_ReadData(jtagbuf, bitlen, lastchunk);
        else                            jtag_SendData(cmdp,    bitlen, lastchunk);
	*resbuf = '[';
        outlen = (MIN(bitlen,JTAG_MAX_DR) + 7) / 8;
	rc = mybuftohex((cmd==0x15 || cmd==0x25) ? jtagbuf : cmdp, resbuf+1, outlen);
        strcpy(resbuf + rc+1, "]\r\n");
        rc += 4;
        return rc;// Always abort after a command which returns data
	break;
      case 0x16:  // Read chain length
        if (cmdp < endp) {
          bitlen = *cmdp++;
          bitlen += ((int) *cmdp++) << 8;
        } else
          bitlen = 2*JTAG_MAX_DR;
        rc = sprintf(resbuf, "[%u]\r\n", jtag_ChainLen(bitlen));
        break;
      case 0x80:  // Config: Start/stop TCK low. Shift clock Hi->Lo.
        jtag_clk_edge(0);
        break;
      case 0x81:  // Config: Start/stop TCK high. Shift clock Lo->Hi.
        jtag_clk_edge(1);
        break;
      case 0x90:  // Config: JTAG pins back to default
        jtag_SetConfig(P_JTAG_TCK, -1);
        jtag_SetConfig(P_JTAG_TDO, -1);
        jtag_SetConfig(P_JTAG_TMS, -1);
        jtag_SetConfig(P_JTAG_RST, -1);
        jtag_SetConfig(P_JTAG_TDI, -1);
        jtag_SetConfig(P_JTAG_DBG, -1);
        break;
      case 0x91:  // Config: TCK pin
        pin = *cmdp++;
        jtag_SetConfig(P_JTAG_TCK, (int) pin);
        break;
      case 0x92:  // Config: TDO pin
        pin = *cmdp++;
        jtag_SetConfig(P_JTAG_TDO, (int) pin);
        break;
      case 0x93:  // Config: TMS pin
        pin = *cmdp++;
        jtag_SetConfig(P_JTAG_TMS, (int) pin);
        break;
      case 0x94:  // Config: TRST pin
        pin = *cmdp++;
        jtag_SetConfig(P_JTAG_RST, (int) pin);
        break;
      case 0x95:  // Config: TDI pin
        pin = *cmdp++;
        jtag_SetConfig(P_JTAG_TDI, (int) pin);
        break;
      case 0x96:  // Config: DBG pin
        pin = *cmdp++;
        jtag_SetConfig(P_JTAG_DBG, (int) pin);
        break;
        // Config: Set extra clocks when entering TAP idle state.
      case 0xA0: IDLE_CLKS = 0; break;
      case 0xA1: IDLE_CLKS = 1; break;
      case 0xA2: IDLE_CLKS = 2; break;
      case 0xA3: IDLE_CLKS = 3; break;
      default:
        //DBG_PRINTF(("JTAG Unknown command 0x%02x\n", cmd));
        rc = sprintf(resbuf, "[0:errno -1 unknown cmd 0x%02x]\r\n", cmd);
        break;
    }
  }
  return rc;
}

int jtag_SetConfig(jtagConfig_t param, int val) {
  int rc = 0;
  switch (param) {
    case P_JTAG_TCK:
      JTAG_TCK = (val > 0) ? (unsigned int) val : P9_11;
      rc = JTAG_TCK;
      break;
    case P_JTAG_TDO:
      JTAG_TDO = (val > 0) ? (unsigned int) val : P9_12;
      rc = JTAG_TDO;
      break;
    case P_JTAG_TMS:
      JTAG_TMS = (val > 0) ? (unsigned int) val : P9_13;
      rc = JTAG_TMS;
      break;
    case P_JTAG_RST:
      JTAG_RST = (val > 0) ? (unsigned int) val : P9_14;
      rc = JTAG_RST;
      break;
    case P_JTAG_TDI:
      JTAG_TDI = (val > 0) ? (unsigned int) val : P9_15;
      rc = JTAG_TDI;
      break;
    case P_JTAG_DBG:
      JTAG_DBG = (val > 0) ? (unsigned int) val : P9_16;
      rc = JTAG_DBG;
      break;
    default: break;
  }
  return rc;
}

char jtag_clk(char data)
{
  char b;
  //if (tck_starthi) BitWr(JTAG_TCK, 0);
  BitWr(JTAG_TCK, 0);
  BitWr(JTAG_TMS, data & TMS);
  BitWr(JTAG_TDI, data & TDI);
  BitWr(JTAG_TCK, 1);
  b = BitRd(JTAG_TDO);
  //if (!tck_starthi) BitWr(JTAG_TCK, 0);
  return b;
}

void jtag_clk_edge(char hi)
{
  //tck_starthi = hi;
  //BitWr(JTAG_TCK, hi);
}

void jtag_Disable(void)
{
	char i;
	// TAP Hard reset
  BitWr(JTAG_RST, 0); // Set RST low
  jtag_clk(TDI | TMS);
  BitWr(JTAG_RST, 1); // Set RST high
  // TAP Soft Reset
  for(i=0; i<5; i++){ // Send soft reset sequence
    jtag_clk(TMS);
  }
  // Disable JTAG: Tri-state signals (set to input), and release.
  // Setting to input will throw an error if pins are already released.
  BitDir(JTAG_TCK, 0);
  BitDir(JTAG_TMS, 0);
  BitDir(JTAG_RST, 0);
  BitDir(JTAG_TDI, 0);
  BitDir(JTAG_TDO, 0);
  if (jtag_debug) BitDir(JTAG_DBG, 0);
  gpio_unexport(JTAG_TCK);
  gpio_unexport(JTAG_TMS);
  gpio_unexport(JTAG_RST);
  gpio_unexport(JTAG_TDI);
  gpio_unexport(JTAG_TDO);
  if (jtag_debug) gpio_unexport(JTAG_DBG);
}

void jtag_Reset(char type)
{
	char i;

  if (gpio_export(JTAG_TCK)) log2stderr("JTAG TCK enable failed");
  if (gpio_export(JTAG_TDI)) log2stderr("JTAG TDI enable failed");
  if (gpio_export(JTAG_TMS)) log2stderr("JTAG TMS enable failed");
  if (gpio_export(JTAG_RST)) log2stderr("JTAG TRST enable failed");
  if (gpio_export(JTAG_TDO)) log2stderr("JTAG TDO enable failed");
  if (jtag_debug) {
    if (gpio_export(JTAG_DBG)) log2stderr("JTAG DBG enable failed");
    else log2stderr("JTAG DBG pin enabled");
  }

  BitWr( JTAG_TCK, 1);
  //BitWr( JTAG_TCK, tck_starthi ? 1 : 0);
  BitDir(JTAG_TCK, 1);  // Set CLK to output
  BitWr( JTAG_TMS, 1);
  BitDir(JTAG_TMS, 1);  // Set TMS to output
  BitWr( JTAG_RST, 1);
  BitDir(JTAG_RST, 1);  // Set RST to output
  BitWr( JTAG_TDI, 1);
  BitDir(JTAG_TDI, 1);  // Set TDI to output
  if (jtag_debug) {
    BitWr( JTAG_DBG, 1);
    BitDir(JTAG_DBG, 1);// Set DBG to output
  }
  BitDir(JTAG_TDO, 0);  // Set TDO to input
  if (type & 1) {
    BitWr(JTAG_RST, 0); // Set RST low
    jtag_clk(TDI | TMS);
    BitWr(JTAG_RST, 1); // Set RST high
  }
  if (type & 2) {
    for(i=0; i<5; i++){ // Send soft reset sequence
      jtag_clk(TMS);
    }
  }
  //jtag_clk(0);    // end in IDLE
  for (i = 0; i <= IDLE_CLKS; i++) jtag_clk(0); // end in IDLE
}

void jtag_EnterShiftIR(void)
{ // Start from IDLE
  jtag_clk(TMS);
  jtag_clk(TMS);
  jtag_clk(0);
  jtag_clk(0);
}

void jtag_EnterShiftDR(void)
{ // Start from IDLE
  jtag_clk(TMS);
  jtag_clk(0);
  jtag_clk(0);
}

int jtag_ChainLen(unsigned int nbits)
{
	unsigned int u, rc;
	char b;
	// empty the chain (fill it with 0's)
	for(u=0; u < nbits; u++) {
    jtag_clk(0);
  }
  rc = 0xffff;
	// feed the chain with 1's
	for(u=0; u < nbits; u++) {
    b = jtag_clk(TDI);
    if (b) {
      rc = u;
      break;
    }
  }
  jtag_clk(TMS);
  jtag_clk(TMS);
  //jtag_clk(0);  // end in IDLE
  for (b = 0; b <= IDLE_CLKS; b++) jtag_clk(0);  // end in IDLE
  return rc;
}

void jtag_SendData(char* pb, unsigned int nbits, char last)
{ // note: call this function only when in shift-IR or shift-DR state
  int nbytes;
  char b, bi, bitc, outbyte, inbyte;
  assert(nbits);  // make sure there is at least one bit to send (we can't send zero if we're already there)
  nbytes = (nbits+7)/8;
  while (nbytes--) {
    outbyte = *pb;
    inbyte  = 0;
    bitc    = (char) MIN(8, nbits);
    for (bi = 0; bi < bitc; bi++) {
      b = (outbyte & (1 << bi)) ? TDI : 0;
      --nbits;
      if (last && (0 == nbits)) b |= TMS; // last bit of last chunk with TMS asserted
	//DBG_PRINTF(("JTAG SendData nbits=%d, outbyte=%02x, mask=%02x, b=%d\n", nbits,outbyte,1<<bi,b));
		b = jtag_clk(b);        // send bit,
		if (b) inbyte |= (1 << bi);
    }
    //DBG_PRINTF(("JTAG SendData bits=%2u,bytes=%2d,out=%02x,in=%02x,last=%d\n", nbits,nbytes,outbyte,inbyte,last));
    *pb++ = inbyte; // return read byte, and select next byte
  }
  if (last) {
    jtag_clk(TMS);
    //jtag_clk(0);  // end in IDLE
    for (bi = 0; bi <= IDLE_CLKS; bi++) jtag_clk(0); // end in IDLE
  }
}

void jtag_ReadData(char* pb, unsigned int nbits, char last)
{ // note: call this function only when in shift-IR or shift-DR state
  int bitofs;
  char b;
  assert(nbits);  // make sure there is at least one bit to read (we can't send zero if we're already there)
  bitofs = 0;
  memset(pb, 0, (nbits+7)/8); // Clear buffer
  nbits--;
  //DBG_PRINTF(("JTAG ReadData l=%d\n", l));
	while(nbits--) {
		b = jtag_clk(TDI);	   // read all bits but the last one, assert TDI
		pb[bitofs>>3] |= (b << (bitofs & 7));
		bitofs++;
	}
	b = jtag_clk(TDI | (last ? TMS : 0)); // read the last bit, with TMS (& TDI) asserted
	pb[bitofs>>3] |= (b << (bitofs & 7));
	if (last) {
    jtag_clk(TMS);
    //jtag_clk(0);  // end in IDLE
    for (b = 0; b <= IDLE_CLKS; b++) jtag_clk(0); // end in IDLE
  }
}

void JTAG_set_debug(int on) {
	jtag_debug = on;
	log2stderr("JTAG debug %s", jtag_debug ? "enabled" : "disabled");
}

/*-----------------------------------------------------------------------------
cmd : jtag_Vector
-------------------------------------------------------------------------------
Synopsis:
    jtag_Vector <?>
Description:
# Function arguments:
# jtag_vector <vector> <repeat> <vector number>
#
# The <vector> pin order is: JTAG_TCK JTAG_NTRST JTAG_TMS JTAG_TDI JTAG_TDO
# Argument <repeat>: Repeat current vector <repeat> times
# Argument <vector number>: Current vector number. Used to report the number of a failing vector
#
# Vector symbols: 0: drive 0, 1: drive 1, L: expect 0, H: expect 1, P: Clock pulse 0110
#
# Each vectors must to be applied to the DUT in 1 tester cycle (TC).
# The TC duration should be the same for all vectors
# Drive inputs at 0% of the TC time
# Drive JTAG_TCK 1 at 25% of TC and 0 at 75% of the TC
# Check outputs at 0% of the TC time
#
# jtag_vector 0000X 1 0
# jtag_vector 0000X 10 1
# jtag_vector 0100X 1 11
# jtag_vector P000X 1 12
# …
# jtag_vector P100H 1 20

Parameters:
*/
int jtag_Vector(const char *vector, int rpt, int num)
{
  int rc = -1;  // Default to matching expect
  // Parse vector JTAG_TCK JTAG_NTRST JTAG_TMS JTAG_TDI JTAG_TDO
  char vector_tck  =  vector[0];                    // Valid values 0, 1, P
  char vector_trst = (vector[1] == '1') ? 1 : 0;    // Valid values 0, 1
  char vector_tms  = (vector[2] == '1') ? 1 : 0;    // Valid values 0, 1
  char vector_tdi  = (vector[3] == '1') ? 1 : 0;    // Valid values 0, 1
  char vector_tdo  = (vector[4] == 'H') ? 1 :
                     (vector[4] == 'L') ? 0 : 255;  // Valid values L=0, H=1, X=-1

  for (int i=0; i<rpt; i++) {
    char b = BitRd(JTAG_TDO); // Read at 0% of vector time
    if (jtag_debug && (vector_tdo != 255) && (vector_tdo != b)) {
      BitWr(JTAG_DBG, 0);
      BitWr(JTAG_DBG, 1);
      BitWr(JTAG_DBG, 0);
    }
    switch (vector_tck) {
      case '0':
        BitWr(JTAG_TCK, 0); // 0%
        BitWr(JTAG_RST, vector_trst);
        BitWr(JTAG_TMS, vector_tms);
        BitWr(JTAG_TDI, vector_tdi);
        break;              // 100%
      case '1':
        BitWr(JTAG_TCK, 1); // 0%
        BitWr(JTAG_RST, vector_trst);
        BitWr(JTAG_TMS, vector_tms);
        BitWr(JTAG_TDI, vector_tdi);
        break;              // 100%
      case 'P':
        BitWr(JTAG_TCK, 0); // 0%
        BitWr(JTAG_RST, vector_trst);
        BitWr(JTAG_TMS, vector_tms);
        BitWr(JTAG_TDI, vector_tdi);
        BitWr(JTAG_TCK, 0);
        BitWr(JTAG_TCK, 1); // 25%
        BitWr(JTAG_TCK, 1); // 50%
        BitWr(JTAG_TCK, 0); // 75%
        break;              // 100%
      default: break;
    }
    if ((rc < 0) && (vector_tdo != 255)) {  // Return first mismatch
      rc = (vector_tdo != b) ? num : -1;
    }
    if (jtag_debug) {
      //log2stderr("JTAG Vector %s,rpt=%d,num=%d,in=%d,expect=%d,return=%d", vector,rpt,num,b,vector_tdo,rc);
    }
    ++num;
  }

  return rc;
}
