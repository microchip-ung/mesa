// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
/*
 * eve_miim.c
 *
 *  Ported from GENIE app_miim.c and str_lib.c plus Rabbit MIIM IO code on:
 *      October 1, 2014
 *      Author: jsa
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <sys/time.h>
//#include "genieio_lib.h"
//#include "socket_cli_conf.h"
//#include "socket_cli.h"
//#include "error.h"
//#include "vitgenio_adapter.h"
//#include "switch_app_adapter.h"

//#define DEBUG
//#include "debug.h"

#include "eve_gpio.h"
#include "eve_sio.h"	// EVE serial IO: SPI
#include "eve_miim.h"

static int miim_init_done = 0;
static int miim_debug = 0;

/////////////////////////////////////////////////////////////////////////////
// The following is taken from GENIE str_lib.c

#define DBUF_STARTSIZE 1024
#define DBUF_INCRSIZE  1024

typedef struct _dbuf {
    char *pbuf;
    int len,size;
}  dbuf;


typedef dbuf * dbuf_handle;


/* ------------ Private functions ------------ */

//#ifdef EPD_DEBUG
#ifdef DEBUG
// Variadic Macros see: https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
//#define dbg_printf(tracemessage,args) printf(tracemessage, ##args)
#define dbg_printf(tracemessage,args) log2stderr(tracemessage, ##args)
//#define dbg_printf(...) log2stderr(__VA_ARGS__)
#define dbg_assert(X) if (!(X)) {dbg_printf(("Assert in %s line %d\n", __FILE__, __LINE__)); }
#define dbg_dump(s) db_dump(s)
#else
#define dbg_printf(...)
#define dbg_assert(X)
#define dbg_dump(s)
#endif
#define paranoid_assert(X)
#define dbg_start()
#define dbg_end()

void MIIM_set_debug(int on) {
	miim_debug = on;
	log2stderr("MIIM debug %s", miim_debug ? "enabled" : "disabled");
}

#ifdef DEBUG
static void db_dump(dbuf_handle sh)
{
    dbg_printf("pbuf = %p\n", sh->pbuf);
    dbg_printf("len = %d\n", sh->len);
    dbg_printf("size = %d\n", sh->size);
    if (sh->pbuf && sh->size) {
        if (sh->pbuf[sh->len] == '\0') {
            dbg_printf("strlen = %d\n", strlen(sh->pbuf));
            dbg_printf("str = ");
            dbg_write(sh->pbuf, sh->len);
            dbg_printf("\n");
        }
        else
            dbg_printf("pbuf str not terminated by 0!\n");
    }
    //dbg_sleep(1);
}
#endif

static void db_resize(dbuf_handle sh, int newsize)
{
    dbg_printf("----- Resize -----\n");
    dbg_dump(sh);
    dbg_assert(sh->len < newsize);
    sh->pbuf = (char *) realloc(sh->pbuf, newsize);
    sh->size = newsize;
    dbg_dump(sh);
    dbg_printf("Resize done!\n");
}

void db_expand(dbuf_handle sh, int newlen)
{
    if (newlen >= sh->size) {
        int newsize = sh->size;
        while (newsize <= newlen) newsize += DBUF_INCRSIZE;
        db_resize(sh, newsize);
    }
}

void db_inflate(dbuf_handle sh)
{
    int newsize = sh->size + DBUF_INCRSIZE;
    db_resize(sh, newsize);
}

/* ------------ Public functions ------------ */

dbuf_handle dbuf_new()
{
    dbuf_handle sh = (dbuf_handle) malloc(sizeof(dbuf));

    sh->pbuf = NULL;
    sh->len = 0;
    db_resize(sh, DBUF_STARTSIZE);

    dbg_printf("------ dbuf_new ------\n");
    dbg_dump(sh);

    return sh;
}

void dbuf_free(dbuf_handle *sh)
{
    paranoid_assert(sh);
    free((*sh)->pbuf);
    free(*sh);
    *sh = NULL;
}

void dbuf_reset(dbuf_handle sh)
{
    paranoid_assert(sh);
    sh->len = 0;
    if (sh->size != DBUF_STARTSIZE) {
        if (sh->pbuf) {
            free(sh->pbuf);
            sh->pbuf = NULL;
        }
        db_resize(sh, DBUF_STARTSIZE);
    }
    sh->pbuf[0] = '\0';
    dbg_printf("------ dbuf_reset ------\n");
    dbg_dump(sh);
}

void dbuf_appendn(dbuf_handle sh, char *str, int len)
{
    int newlen = sh->len + len;
    paranoid_assert(sh);
    //int len = strlen(str);

    db_expand(sh, newlen);
    memcpy(sh->pbuf + sh->len, str, len);
    sh->len = newlen;
    dbg_printf("------ Appendn: len=%d ------\n", len);
    dbg_dump(sh);
}

void dbuf_appendstr(dbuf_handle sh, char *str)
{
    dbuf_appendn(sh, str, strlen(str));
    sh->pbuf[sh->len] = '\0';
}

//#define dbuf_len(x)  ((x)->len)
int dbuf_len(dbuf_handle sh)
{
    paranoid_assert(sh);
    return sh->len;
}

//#define dbuf_read(x) ((x)->pbuf)
char *dbuf_read(dbuf_handle sh)
{
    paranoid_assert(sh);
    return sh->pbuf;
}

void dbuf_drop(dbuf_handle sh, int len)
{
    int newlen = sh->len - len;
    paranoid_assert(sh);
    memmove(sh->pbuf, sh->pbuf + len, newlen +1); /* include terminating 0 */
    sh->len = newlen;
}

char *dbuf_makeroom(dbuf_handle sh, int len)
{
    paranoid_assert(sh);
    if (sh->size - sh->len <= len)
        db_expand(sh, sh->len + len +1);

    dbg_printf("------ dbuf_makeroom: len=%d ------\n", len);
    dbg_dump(sh);

    return sh->pbuf + sh->len; /* ready for writing */
}

/* user has written directly into the buffer */
/* used only with makeroom */
void dbuf_makelen(dbuf_handle sh, int appendlen)
{
    paranoid_assert(sh);
    sh->len += appendlen;
    dbg_assert(sh->len < sh->size);
    dbg_printf("------ dbuf_makelen: appendlen=%d ------\n", appendlen);
    dbg_dump(sh);
}

void dbuf_printf(dbuf_handle sh, const char *fmt, ...)
{
    va_list ap;
    int rv, remain;

    remain = sh->size - sh->len;
    va_start(ap, fmt);
    /* rv excludes and remain includes trailing '\0' */
    rv = vsnprintf(sh->pbuf + sh->len, remain, fmt, ap);
    if (rv >= remain) {
        dbuf_makeroom(sh, rv);
        remain = sh->size - sh->len;
        rv = vsnprintf(sh->pbuf + sh->len, remain, fmt, ap);
        paranoid_assert(rv < remain);
    }
    va_end(ap);
    sh->len += rv;
}

// End of GENIE str_lib.c
/////////////////////////////////////////////////////////////////////////////
// The following is from GENIE genieio_lib.c

#define TOUPPER(ch) ((ch) & ~('a'-'A'))
#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISHEXDIGIT(ch) (TOUPPER(ch) >= 'A' && TOUPPER(ch) <= 'F')
#define ISHEX(ch) (ISDIGIT(ch) || ISHEXDIGIT(ch))
#define HEX(ch) (ISHEX(ch) ? (ISDIGIT(ch) ? (ch) - '0' : TOUPPER(ch) - 'A' + 10) : -1)

static const char *read_int(const char *str,unsigned long *val)
{
    int ch, base = 10, state = 0;

    assert(str);
    for (;;) {
        switch (state) {
        case 0:
            if (!(ISHEX(*str) || *str =='x'))
                return NULL;
            if (*str == '0') {
                str++;
            }
            state++;
            break;
        case 1:
            if  (*str == 'x') {
                base = 16;
                str++;
                if (!ISHEX(*str))
                    return NULL;
            }
            state++;
            *val = 0;
        case 2:
            if ((ch = HEX(*str)) < 0)
                return str;
            *val = *val * base + ch;
            str++;
            break;
        }
    }
    assert(0);
    return NULL;
}

int parse_ints(const char *str,unsigned long *res, int max)
{
    if (max <= 0)
        return 0;
    if (!str)
        return 0;
    for (; *str == ' '; str++);
    if ((str = read_int(str,res)))
        return parse_ints(str, ++res, --max) + 1;
    else
        return 0;
}

#define READHEX_OK             0
#define READHEX_ISNOTHEX      -1
#define READHEX_NOTEVENLENGTH -2

int read_hex_str(const char *instr, unsigned char *out)
{
    int i, bytelen;
    bytelen = strlen(instr);

    if (bytelen % 2) {
        return READHEX_NOTEVENLENGTH;
    }
    bytelen >>= 1;

    for(i=0; i<bytelen; i++) {
        if (!ISHEX(*instr))
            return READHEX_ISNOTHEX;
        out[i] = HEX(*instr) << 4;
        instr++;
        if (!ISHEX(*instr))
            return READHEX_ISNOTHEX;
        out[i] |= HEX(*instr);
        instr++;
    }

    return bytelen;
}

static const char bin2hex_table[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};

void bin2hexstr(const unsigned char *p, char *dst, int len)
{
    const unsigned char *endp = p+len;
    for (; p<endp; p++) {
        //cli_printf("bin2hexstr: p=%p, dst=%p, *p=0x%02x, ", p, dst, *p);
        *(dst++) = bin2hex_table[*p >> 4];
        //cli_printf("c1=%c, ", *(dst-1));
        *(dst++) = bin2hex_table[*p & 0x0f];
        //cli_printf("c2=%c\n", *(dst-1));
    }
}

// End of GENIE genieio_lib.c
/////////////////////////////////////////////////////////////////////////////
// The following is ported from rabbit MIIM IO

static unsigned int MDC  = P9_21;
static unsigned int MDIO = P9_22;

// Map Rabbit bit IO primitives to Beaglebone functions
// Note: MIIM is ALWAYS memory mapped IO, for speed
#define MDC_O(v)    gpio_mmdo_set(MDC,(v))
#define MDC_DIR(d)  gpio_mmdo_dir(MDC, (d))
#define MDIO_O(v)   gpio_mmdo_set(MDIO, (v))
#define MDIO_I      gpio_mm_get(MDIO)
#define MDIO_DIR(d) gpio_mmdo_dir(MDIO, (d))

/* --------------------- MIIM via direct GPIO --------------------- */

int miim_setgpio(int pin, int val)
{
    int rc = 0;
    if (pin) {
        MDC  = (val > 0) ? (unsigned int) val : P9_21;
        rc   = MDC;
    } else {
        MDIO = (val > 0) ? (unsigned int) val : P9_22;
        rc   = MDIO;
    }
    return rc;
}

void gpio_miim_preamble(void)
{
    auto int i;
    MDC_O(1);
    MDIO_O(0);
    MDC_DIR(1);
    MDIO_DIR(0);  // Set MDIO value to 0, but keep tristate = high
    // Send idle bit + PREAMBLE of 32 x 1
    for (i = 34; i > 0; i--) {
        MDC_O(0);
        MDC_O(1);
    }
}

void gpio_miim_wr16(unsigned int word)
{
    auto int i;
    for (i = 15; i >= 0; i--) {
        MDC_O(0);
        MDIO_DIR(!(word & (1 << i))); // Set Direction to 1 (output) to drive MDIO LOW
        MDC_O(1);
    }
}

void gpio_miim_idle_release(void)
{
    MDC_O(0);     // Send IDLE
    MDIO_DIR(0);
    MDC_O(1);
    MDC_DIR(0);   // Release bus
}

unsigned int gpio_miim_read(int phynum, int regnum)
{
    int i, ctrl;
    unsigned int data;

    // Build ST OP PHYAD REGAD TA, MSB first
    // ST (start) is 01 for clause 22
    // OP (opcode) is 10 for read, 01 for write
    // TA (turnaround) is two bits for bus turnaround time. Usually tristate.
    ctrl =  (1 << 14) + (1 << 13) + (phynum << 7) + (regnum << 2) + 2;
//  ctrl =  (1 << 14) + (1 << 13) + (phynum << 7) + (regnum << 2) + 3; // original value was 2 at the end. This is the change we wanted to incorperate.
    gpio_miim_preamble();
    // Send ST OP PHYAD REGAD TA, MSB first
    gpio_miim_wr16(ctrl);
    // Get DATA, MSB first
    MDIO_DIR(0);  // Change MDIO direction (tristate)
    data = 0;
    for (i = 15; i >= 0; i--) {
        MDC_O(0);
        if (MDIO_I) data |= (1 << i);
        MDC_O(1);
    }
    // Send IDLE & Release bus
    gpio_miim_idle_release();
    //DBG_PRINTF(("MIIMRD %d %d 0x%04x\n", phynum, regnum, data));
    return data;
}

int gpio_miim_write(int phynum, int regnum, unsigned int value)
{
	unsigned int ctrl;

    // Build ST OP PHYAD REGAD TA, MSB first (see gpio_miim_read)
    ctrl =  (1 << 14) + (1 << 12) + (phynum << 7) + (regnum << 2) + 2;
    gpio_miim_preamble();
    // Send ST OP PHYAD REGAD TA, MSB first
    gpio_miim_wr16(ctrl);
    // Send DATA, MSB first
    gpio_miim_wr16(value);
    // Send IDLE & Release bus
    gpio_miim_idle_release();
    return 0;
}

/* --------------------- MIIM controller in CPLD --------------------- */
// MIIM via MIIM controller in CPLD
// Currently no working CPLD implementation
#define CPLD_CTRL_REG   3           // Control register contains MIIM status
#define CPLD_MIIM_MASK  (1 << 10)   // Which bit shows MIIM command is running
#define CPLD_MIIM_REG   13          // MIIM control register
#if 0
int cpld_miim_write(int phynum, int regnum, unsigned int value)
{
    int rc, old_channel;
    unsigned long ctrl, sdata;
    old_channel = set_spi_select(1);
    // Build ST OP PHYAD REGAD TA, MSB first
    ctrl =  0x5000L + (phynum << 7) + (regnum << 2) + 2L;
    // Then add data in lower 16 bits
    sdata = ctrl << 16 + (unsigned long) value;
    spi_write(0, 0, CPLD_MIIM_REG, sdata);
#ifdef MIIM_POLL
    rc = -1;
    do {  // poll for MIIM completion. Give up after 100 tries
        sdata = spi_read(0, 0, CPLD_CTRL_REG);
        rc = (sdata & CPLD_MIIM_MASK) ? (rc-1) : 0;
    } while (-10 < rc && rc < 0);
#else
    rc = 0;
#endif
    set_spi_select(old_channel);
    return rc;
}

long cpld_miim_read(int phynum, int regnum)
{
    int rc, old_channel;
    unsigned long sdata;
    old_channel = set_spi_select(1);
    // Build ST OP PHYAD REGAD TA, MSB in top 16 bits
    sdata =  0x6000L + (phynum << 7) + (regnum << 2) + 2L;
    sdata = sdata << 16;
    spi_write(0, 0, CPLD_MIIM_REG, sdata);
#ifdef MIIM_POLL
    rc = -1;
    do {  // poll for MIIM completion. Give up after 100 tries
        sdata = spi_read(0, 0, CPLD_CTRL_REG);
        rc = (sdata & CPLD_MIIM_MASK) ? (rc-1) : 0;
    } while (-10 < rc && rc < 0);
#else
    rc = 0;
#endif
    sdata = (rc == 0) ? spi_read(0, 0, CPLD_MIIM_REG) : 0xffffffff;
    set_spi_select(old_channel);
    return (long) sdata;
}
#endif
/* --------------------- MIIM in switch --------------------- */
// MIIM via MIIM controller in Luton switch
#define LUTON_MIIM_BLOCK  3
#define LUTON_MIIM_STATUS 0
#define LUTON_MIIM_CMD    1
#define LUTON_MIIM_DATA   2

#define LUTON_MIIM_CMD_SCAN_BIT       27
#define LUTON_MIIM_CMD_OPER_BIT       26
#define LUTON_MIIM_CMD_PHY_ADDR_BIT   21
#define LUTON_MIIM_CMD_PHY_REG_BIT    16
#define LUTON_MIIM_CMD_WRITE_DATA_BIT 0

#define LUTON_MIIM_CMD_OPER_READ  (1L << LUTON_MIIM_CMD_OPER_BIT)
#define LUTON_MIIM_CMD_OPER_WRITE (0L << LUTON_MIIM_CMD_OPER_BIT)
#define LUTON_MIIM_CMD_BUSY       (1L << 3)

#if 0
long epdsi_miim_read(int bus, int phynum, int regnum)
{
    int rc, old_channel;
    unsigned long sdata;
    old_channel = set_spi_select(0);
    sdata = LUTON_MIIM_CMD_OPER_READ |
        ((phynum & 0x1fL) << LUTON_MIIM_CMD_PHY_ADDR_BIT) |
        ((regnum & 0x1fL) << LUTON_MIIM_CMD_PHY_REG_BIT);
    spi_write(LUTON_MIIM_BLOCK, bus, LUTON_MIIM_CMD, sdata);
//DBG_PRINTF(("EPDSI W: %d %d %d = 0x%08lx\n", bus, phynum, regnum, sdata));
    rc = -1;
    do {  // poll for MIIM completion. Give up after 100 tries
        sdata = spi_read(LUTON_MIIM_BLOCK, bus, LUTON_MIIM_STATUS);
        rc = (sdata & LUTON_MIIM_CMD_BUSY) ? (rc-1) : 0;
//DBG_PRINTF(("EPDSI R(%d): 0x%08lx\n", rc, sdata));
    } while (-100 < rc && rc < 0);
    sdata = (rc == 0) ? spi_read(LUTON_MIIM_BLOCK, bus, LUTON_MIIM_DATA) : 0x1ffff;
//DBG_PRINTF(("EPDSI R(%d): 0x%08lx\n", rc, sdata));
    if (sdata & 0x10000)  // bit 16 is FAILURE
        sdata = 0xffffffff;
    set_spi_select(old_channel);
    return (long) sdata;
}

int epdsi_miim_write(int bus, int phynum, int regnum, unsigned int value)
{
    int rc, old_channel;
    unsigned long sdata;
    old_channel = set_spi_select(0);
    sdata = LUTON_MIIM_CMD_OPER_WRITE |
        ((phynum & 0x1fL) << LUTON_MIIM_CMD_PHY_ADDR_BIT) |
        ((regnum & 0x1fL) << LUTON_MIIM_CMD_PHY_REG_BIT)  |
        (value & 0xffffL);
//DBG_PRINTF(("EPDSI W: %d %d %d = 0x%08lx\n", bus, phynum, regnum, sdata));
    spi_write(LUTON_MIIM_BLOCK, bus, LUTON_MIIM_CMD, sdata);
    rc = -1;
    do {  // poll for MIIM completion. Give up after 100 tries
        sdata = spi_read(LUTON_MIIM_BLOCK, bus, LUTON_MIIM_STATUS);
//DBG_PRINTF(("EPDSI R(%d): 0x%08lx\n", rc, sdata));
        rc = (sdata & LUTON_MIIM_CMD_BUSY) ? (rc-1) : 0;
    } while (-10 < rc && rc < 0);
    set_spi_select(old_channel);
    return rc;
}
#endif

/* --------------------- MIIM in switch --------------------- */
// MIIM via MIIM controller in Luton switch, Freeflight format
#define LUTON_CS 0
#define SIFF_WR  1
#define SIFF_RD  0
#define LUTONFF_MIIM_TGT    0x01  // DEVCPU_GCB
#define LUTONFF_MIIM_STATUS 0x31
#define LUTONFF_MIIM_CMD    0x33
#define LUTONFF_MIIM_DATA   0x34

#define LUTONFF_MIIM_INST_OFFS  0x9

#define LUTONFF_MIIM_CMD_SCAN_BIT       0
#define LUTONFF_MIIM_CMD_OPER_BIT       1
#define LUTONFF_MIIM_CMD_VLD_BIT        31
#define LUTONFF_MIIM_CMD_PHY_ADDR_BIT   25
#define LUTONFF_MIIM_CMD_PHY_REG_BIT    20
#define LUTONFF_MIIM_CMD_WRITE_DATA_BIT 4

#define LUTONFF_MIIM_CMD_OPER_READ  (2L << LUTONFF_MIIM_CMD_OPER_BIT)
#define LUTONFF_MIIM_CMD_OPER_WRITE (1L << LUTONFF_MIIM_CMD_OPER_BIT)

#define LUTONFF_MIIM_CMD_BUSY       (1L << 3)

static int miim_poll = 0;

unsigned long spi_rw(SPI_STATE *spi, int cs, int write, int tgt, int addr, unsigned long data)
{
    int tgtaddr, old_select;
    unsigned long rxdata = 0xffffffff;
    unsigned char txbuf[8], rxbuf[10], *rx; // rxbuf len = TX + padding + RX

    old_select   = spi->channel; // Save CS
    spi->channel = cs;
    tgtaddr = (tgt << 14) + addr;
    txbuf[0] = (unsigned char)((tgtaddr>>16)&0xFF);
    txbuf[1] = (unsigned char)((tgtaddr>>8) &0xff);
    txbuf[2] = (unsigned char) (tgtaddr     &0xff);
    if (write) {
        txbuf[0] |= 0x80;
        txbuf[3] = (unsigned char) (data>>24);
        txbuf[4] = (unsigned char) (data>>16)&0xff;
        txbuf[5] = (unsigned char) (data>>8) &0xff;
        txbuf[6] = (unsigned char) (data)    &0xff;
        SPI_brw(spi, (unsigned char*)txbuf, 7, NULL, 0, 0);
    } else {
        rx = SPI_brw(spi, (unsigned char*)txbuf, 3, (unsigned char*)rxbuf, 4, 0);
        rxdata =   (unsigned long) rx[3];
        rxdata |= ((unsigned long) rx[2]) << 8;
        rxdata |= ((unsigned long) rx[1]) << 16;
        rxdata |= ((unsigned long) rx[0]) << 24;
    }
    if (miim_debug) log2stderr("MIIM_SPI_RW: %c A:0x%02X%02X%02X D:0x%08X",
                               write?'W':'R', txbuf[0], txbuf[1], txbuf[2], write?data:rxdata);
    spi->channel = old_select; // Restore CS
    return rxdata;
}

long epdsiff_miim_read(SPI_STATE *spi, int bus, int phynum, int regnum)
{
    int rc, regbase;
    unsigned long sdata;

    regbase = LUTONFF_MIIM_INST_OFFS * bus;
    sdata = (1L << LUTONFF_MIIM_CMD_VLD_BIT) | LUTONFF_MIIM_CMD_OPER_READ |
        ((phynum & 0x1fL) << LUTONFF_MIIM_CMD_PHY_ADDR_BIT) |
        ((regnum & 0x1fL) << LUTONFF_MIIM_CMD_PHY_REG_BIT);
    spi_rw(spi, LUTON_CS, SIFF_WR, LUTONFF_MIIM_TGT, LUTONFF_MIIM_CMD+regbase, sdata);
	if (miim_debug) log2stderr("EPDSIFF R: %d %d %d = 0x%08lx", bus, phynum, regnum, sdata);
    rc = miim_poll ? -1 : 0;
    if (miim_poll) do { // poll for MIIM completion. Give up after 100 tries
            sdata = spi_rw(spi, LUTON_CS, SIFF_RD, LUTONFF_MIIM_TGT, LUTONFF_MIIM_STATUS+regbase, 0L);
            if (miim_debug) log2stderr("EPDSIFF R: %d %d %d = 0x%08lx", bus, phynum, regnum, sdata);
            rc = (sdata & LUTONFF_MIIM_CMD_BUSY) ? (rc-1) : 0;
            if (miim_debug) log2stderr("EPDSIFF R BUSY: %d", rc);
        } while (-100 < rc && rc < 0);
    sdata = (rc == 0) ? spi_rw(spi, LUTON_CS, SIFF_RD, LUTONFF_MIIM_TGT, LUTONFF_MIIM_DATA+regbase, 0L) : 0x1ffff;
	if (miim_debug) log2stderr("EPDSIFF R RC(%d): 0x%08lx", rc, sdata);
    if (sdata & 0x10000)  // bit 16 is FAILURE
        sdata = 0x1ffff;  // Not 0xffffffff, this was sign extended to -1 (quit request)
    return (long) sdata;
}

int epdsiff_miim_write(SPI_STATE *spi, int bus, int phynum, int regnum, unsigned int value)
{
    int rc, regbase;
    unsigned long sdata;

    regbase = LUTONFF_MIIM_INST_OFFS * bus;
    sdata = (1L << LUTONFF_MIIM_CMD_VLD_BIT) | LUTONFF_MIIM_CMD_OPER_WRITE |
        ((phynum & 0x1fL) << LUTONFF_MIIM_CMD_PHY_ADDR_BIT) |
        ((regnum & 0x1fL) << LUTONFF_MIIM_CMD_PHY_REG_BIT)  |
        ((value & 0xffffL)<< LUTONFF_MIIM_CMD_WRITE_DATA_BIT);
	if (miim_debug) log2stderr("EPDSIFF W: %d %d %d = 0x%08lx", bus, phynum, regnum, sdata);
    spi_rw(spi, LUTON_CS, SIFF_WR, LUTONFF_MIIM_TGT, LUTONFF_MIIM_CMD+regbase, sdata);
	if (miim_debug) log2stderr("EPDSIFF W: %d %d %d = 0x%08lx", bus, phynum, regnum, sdata);
    rc = miim_poll ? -1 : 0;
    if (miim_poll) do { // poll for MIIM completion. Give up after 10 tries
            sdata = spi_rw(spi, LUTON_CS, SIFF_RD, LUTONFF_MIIM_TGT, LUTONFF_MIIM_STATUS+regbase, 0L);
            rc = (sdata & LUTONFF_MIIM_CMD_BUSY) ? (rc-1) : 0;
            if (miim_debug) log2stderr("EPDSIFF W POLL(%d): 0x%08lx", rc, sdata);
        } while (-10 < rc && rc < 0);

    return rc;
}

// End of rabbit MIIM IO
/////////////////////////////////////////////////////////////////////////////
// The following is taken from GENIE app_miim.c

dbuf_handle ocharbuf;
dbuf_handle obinbuf;

void *miim_init(int gpio)
{
    if (miim_init_done) return NULL;

    dbg_start();
    ocharbuf = dbuf_new();
    obinbuf = dbuf_new();
    /*err_msg("Miim app: Init done!");*/
    // Init GPIOs for direct miim_busover GPIO
    if (gpio && gpio_export(MDC))  log2stderr("MIIM MDC enable failed");
    if (gpio && gpio_export(MDIO)) log2stderr("MIIM MDIO enable failed");

    miim_init_done = 1;
    return NULL;
}

void miim_destroy(void *entity_handle)
{
    if (!miim_init_done) return;

    dbuf_free(&obinbuf);
    dbuf_free(&ocharbuf);
    dbg_end();
    /*err_msg("Miim app: Shutting down!");*/
    // Release GPIOs. TODO: add conditional on direct MIIM...
    MDC_DIR(0);
    MDIO_DIR(0);
    gpio_unexport(MDC);
    gpio_unexport(MDIO);

    miim_init_done = 0;
}

// int miim_cmd_read(void *entity_handle, const char *cmd_line)
// {
//     long long rv;
//     unsigned long miim_parms[2];
//     const char *ptr;
//     dbg_printf("Miim app: invoked cmdline:'%s'\n",cmd_line);
//     if (!(ptr = skip_cmd(cmd_line)))
// 	return CLI_USER_ERROR_INFO;
//
//     if (parse_ints(ptr, miim_parms, 2) != 2) {
// 	return CLI_USER_ERROR_INFO;
//     }
//
//     rv = miim_read(entity_handle, miim_parms[0], miim_parms[1]);
//
//     if (rv == -1)
// 	cli_printf("[Error: miim_read %s]\n", strerror(errno));
//     else
// 	cli_printf("[0x%04x]\n", (ulong) rv);
//
//     return CLI_OK;
// }

// int miim_cmd_write(void *entity_handle, const char *cmd_line)
// {
//     int rv;
//     unsigned long miim_parms[3];
//     const char *ptr;
//     dbg_printf("Miim app: invoked cmdline:'%s'\n",cmd_line);
//     if (!(ptr = skip_cmd(cmd_line)))
// 	return CLI_USER_ERROR_INFO;
//
//     if (parse_ints(ptr, miim_parms, 3) != 3) {
// 	return CLI_USER_ERROR_INFO;
//     }
//
//     rv = miim_write(entity_handle, miim_parms[0], miim_parms[1], miim_parms[2]);
//
//     if (rv == -1)
// 	cli_printf("[Error: miim_write %s]\n", strerror(errno));
//     else
// 	cli_printf("[]\n");
//
//     return CLI_OK;
// }

void miim_cmd_microcmd_syntaxerror()
{
    //cli_printf("Syntax: microcmd <hexstring>\n- e.g.:\nmicrocmd d503d2ff\n");
    dbg_printf("Syntax: microcmd <hexstring>\n- e.g.:\nmicrocmd d503d2ff\n");
}

/* --------------------- IO interface --------------------- */

typedef enum {
    MIIMMODE_SMO_UNMAPPED,
    MIIMMODE_DIRECT,
    MIIMMODE_CPLD,
    MIIMMODE_SMO_PORT,
    MIIMMODE_EPDSI,
    MIIMMODE_EPDSIFF
} miim_mode_t;

static miim_mode_t  miim_mode = MIIMMODE_DIRECT;
static unsigned int miim_bus = 0;

//long long miim_read(void *handle, int phynum, int regnum)
long miim_read(void *handle, int phynum, int regnum)
{
    unsigned long val = -1;

    switch (miim_mode) {
    case MIIMMODE_DIRECT :
        miim_init(1); // And enable GPIOs
        val = (unsigned long) gpio_miim_read(phynum, regnum);
        val &= 0xffff;  // prevent sign extension for 0xffff result
        break;
    case MIIMMODE_CPLD :
        //val = cpld_miim_read(handle, phynum, regnum);
        break;
    case MIIMMODE_SMO_UNMAPPED :
        //rs = smo_phy_unmapped_read(handle, miim_bus, phynum, regnum, &val);
        break;
    case MIIMMODE_SMO_PORT :
        dbg_assert(0); /* todo : implement */
        break;
    case MIIMMODE_EPDSI :
        //val = epdsi_miim_read(miim_bus, phynum, regnum);
        break;
    case MIIMMODE_EPDSIFF : // Freeflight SI format
        val = epdsiff_miim_read((SPI_STATE *)handle, miim_bus, phynum, regnum);
        break;
    default :
        dbg_assert(0);
    }
    return val;
}

//int miim_write(void *handle, int phynum, int regnum, unsigned long value);
int miim_write(void *handle, int phynum, int regnum, unsigned long value)
{
    int rc = 0;

    switch (miim_mode) {
    case MIIMMODE_DIRECT :
        miim_init(1); // And enable GPIOs
        rc = gpio_miim_write(phynum, regnum, value);
        break;
    case MIIMMODE_CPLD :
        //rc = cpld_miim_write(handle, phynum, regnum, value);
        break;
    case MIIMMODE_SMO_UNMAPPED :
        //rs = smo_phy_unmapped_write(handle, miim_bus, phynum, regnum, value);
        break;
    case MIIMMODE_SMO_PORT :
        dbg_assert(0); /* todo : implement */
        break;
    case MIIMMODE_EPDSI :
        //rc = epdsi_miim_write(miim_bus, phynum, regnum, value);
        break;
    case MIIMMODE_EPDSIFF : // Freeflight SI format
        rc = epdsiff_miim_write((SPI_STATE *)handle, miim_bus, phynum, regnum, value);
        break;
    default :
        dbg_assert(0);
    }
    return rc;
}

/* --------------------- MIIM MicroCmds --------------------- */
/* Byte Codes:
   Smiwrite
   sync,0x04,upper,lower,phy,reg,chksum
   Return code: 0xf0

   Smiread
   sync,0x05,phy,reg,chksum
   Return code: 0xf0,upper,lower

   Trwrite
   sync,0x47,up,mid,low,addU,addL,phy#,chksum
   Return code: 0xf0

   Trread
   sync,0x48,addU,addL,phy#,chksum
   Return code: 0xf0,lower,middle,upper

   Subroutine
   sync,0x44,#bytes,[cmd,data...],chksum
   Return code: 0xf0

   Loop
   0x52 - This goes inside the subroutine array

   Repeat
   sync,0x46,upper,lower,chksum
   Return code: 0xf0,[data from subroutine],time[0],time[1],time[2],time[3]
   time[0] is MSB of uint32 timediff in millisecs
*/

#define MICROCMD_BYTE_SYNC       0xd5
#define MICROCMD_BYTE_SMIWRITE   0x04
#define MICROCMD_BYTE_SMIREAD    0x05
#define MICROCMD_BYTE_TRWRITE    0x47
#define MICROCMD_BYTE_TRREAD     0x48
#define MICROCMD_BYTE_SUBROUTINE 0x44
#define MICROCMD_BYTE_LOOP       0x52
#define MICROCMD_BYTE_REPEAT     0x46

static unsigned char       *micro_subroutine_buf        = NULL;
static int                  micro_subroutine_len        = 0;
static const unsigned char *micro_subroutine_loopoffset = NULL;
static void                *micro_driverhandle          = NULL;
static unsigned int         micro_phyoffset             = 0;
static int                  micro_command_socket_out    = 0;

static int do_microcmd(const unsigned char **ppIn, dbuf_handle dh, int cmdlen)
{
    unsigned char tmpbuf[4];
    int tmpbufi = 0;
    const unsigned char *cmdbuf = *ppIn;
    const unsigned char *sub_end, *sub_p;
    unsigned int phy, reg, value;
    int rc, sub_loops, i;
    struct timeval tvstart, tvend;
    unsigned long tdiff;

    dbg_assert(cmdlen >= 1);

    /* todo: maybe test chksum */

    cmdlen -= 1;
    switch (*(cmdbuf++)) {
    case MICROCMD_BYTE_SMIWRITE :
        dbg_assert(cmdlen >= 4);
        cmdlen -= 4;
        /* NOTE: the protocol has changed!!!!!
           IT is now two seperate bytes for phy and reg
        */
        value = *(cmdbuf++) << 8;
        value += *(cmdbuf++);
        phy = *(cmdbuf++) + micro_phyoffset;
        reg = *(cmdbuf++);
        rc = miim_write(micro_driverhandle, phy, reg, value);
        if (rc == -1)
            return -1;
        break;

    case MICROCMD_BYTE_SMIREAD :
        dbg_assert(cmdlen >= 1);
        cmdlen--;
        /* NOTE: the protocol has changed!!!!!
           IT is now two seperate bytes for phy and reg
        */
        phy = *(cmdbuf++) + micro_phyoffset;
        reg = *(cmdbuf++);
        rc = miim_read(micro_driverhandle, phy, reg);
        if (rc == -1)
            return -1;
        tmpbuf[0] = (rc >> 8) & 0xff;
        tmpbuf[1] = rc & 0xff;
        tmpbufi = 2;
        break;

    case MICROCMD_BYTE_TRWRITE :
        dbg_assert(cmdlen >= 6);
        cmdlen -= 6;
        phy = cmdbuf[2] + micro_phyoffset;

        /* miim_write(phy, 18 , data[0] << 8) */
        value = cmdbuf[0] << 8;
        rc = miim_write(micro_driverhandle, phy, 18, value);
        if (rc == -1)
            return -1;

        /* miim_write(phy, 17 , (data[2] << 8) + data[1]) */
        value = (cmdbuf[2] << 8) + cmdbuf[1];
        rc = miim_write(micro_driverhandle, phy, 17, value);
        if (rc == -1)
            return -1;

        /* miim_write(phy, 16 , (data[4] << 8) + data[3]) */
        value = (cmdbuf[4] << 8) + cmdbuf[3];
        rc = miim_write(micro_driverhandle, phy, 16, value);
        if (rc == -1)
            return -1;

        cmdbuf += 6;
        break;

    case MICROCMD_BYTE_TRREAD :
        dbg_assert(cmdlen >= 3);
        cmdlen -= 3;
        phy = cmdbuf[5] + micro_phyoffset;

        /* miim_write(phy, 16 , (data[1] << 8) + data[0]) */
        value = (cmdbuf[1] << 8) + cmdbuf[0];
        rc = miim_write(micro_driverhandle, phy, 16, value);
        if (rc == -1)
            return -1;

        /* todo: is it ok to read reg 17 before reg 18? */
        /* val=miim_read(phy, 17) -> out[0]=val@hi -> out[1]=val@lo */
        rc = miim_read(micro_driverhandle, phy, 17);
        if (rc == -1)
            return -1;
        tmpbuf[0] = (rc >> 8) & 0xff;
        tmpbuf[1] = rc & 0xff;

        /* val=miim_read(phy, 18) -> out[2]=val@hi */
        rc = miim_read(micro_driverhandle, phy, 18);
        if (rc == -1)
            return -1;
        tmpbuf[2] = (rc >> 8) & 0xff;
        tmpbufi = 3;

        cmdbuf += 3;
        break;

    case MICROCMD_BYTE_SUBROUTINE :
        /* Note: A subroutine cmd within a subroutine is fatal! */
        if (micro_subroutine_buf) /* discard old subroutine */
            free(micro_subroutine_buf);
        micro_subroutine_len = *(cmdbuf++);
        cmdlen--;
        dbg_assert(cmdlen >= micro_subroutine_len);

        micro_subroutine_buf = (unsigned char *) malloc(micro_subroutine_len);
        memcpy(micro_subroutine_buf, cmdbuf, micro_subroutine_len);
        cmdbuf += micro_subroutine_len;
        cmdlen -= micro_subroutine_len;
        break;

    case MICROCMD_BYTE_REPEAT :
        dbg_assert(cmdlen >= 2);
        cmdlen -= 2;
        dbg_assert(micro_subroutine_buf);

        sub_end = micro_subroutine_buf + micro_subroutine_len;
        sub_loops = *(cmdbuf++) << 8;
        sub_loops += *(cmdbuf++);
        micro_subroutine_loopoffset = micro_subroutine_buf;
        /* timediff start */
        gettimeofday(&tvstart, 0);
        for (i=0; i<sub_loops; i++) {
            sub_p = micro_subroutine_loopoffset;
            while (sub_p < sub_end) {
                do_microcmd(&sub_p, dh, sub_end - sub_p);
            }
        }
        /* timediff end */
        gettimeofday(&tvend, 0);
        tdiff = (tvend.tv_sec - tvstart.tv_sec)*1000000 +
            (tvend.tv_usec - tvstart.tv_usec);
        tmpbuf[0] = (tdiff >> 24) & 0xff;
        tmpbuf[1] = (tdiff >> 16) & 0xff;
        tmpbuf[2] = (tdiff >> 8) & 0xff;
        tmpbuf[3] = (tdiff >> 0) & 0xff;
        tmpbufi = 4;
        break;

    case MICROCMD_BYTE_LOOP :
        micro_subroutine_loopoffset = cmdbuf;
        break;

    default :
        return -1;
        break;
    }

    /* All is well now update pointers */
    *ppIn = cmdbuf;
    dbuf_appendn(dh, (char *)tmpbuf, tmpbufi);

    return 0;
}


//#define MICROSUBROUTINE_MAXLEN   (CMD_MAX_LINE / 2 - 2)
#define MAX_INBYTES 10000

// TODO!!!
// MICROCOMMANDS not done, socket output is missing...

//int miim_cmd_microcmd(void *entity_handle, const char *cmd_line)
int  miim_cmd_microcmd(void *entity_handle, const char *cmd_line, char *resbuf, int maxlen)
{
    const char *ptr;
    int bytelen, outlen, rc;
    unsigned char cmdbuf[MAX_INBYTES];
    const unsigned char *cmdp = cmdbuf;

    //if (!(ptr = skip_cmd(cmd_line)))
    //    return CLI_USER_ERROR_INFO;

    ptr = cmd_line;
    while(*ptr == ' ') ptr++;

    dbg_assert((strlen(ptr) >> 1) < MAX_INBYTES);

    micro_driverhandle = entity_handle;

    //bytelen = read_hex_str(ptr, cmdbuf);
    bytelen = myhextobuf(ptr, (char *)cmdbuf, MAX_INBYTES);
    if (bytelen < 0) {
        miim_cmd_microcmd_syntaxerror();
        return -1; //CLI_USER_ERROR_INFO;
    }

    /* Interpret bytes */
    if (*cmdp != MICROCMD_BYTE_SYNC) {
        //cli_printf("'0x%02x' is not a valid microcmd start byte\n", *cmdp);
        //return CLI_USER_ERROR_INFO;
        rc = sprintf(resbuf, "[error: '0x%02x' invalid microcmd start byte]\r\n", *cmdp);
        return rc;
    }
    cmdp++;

    // No error checking with socket out!
    if (entity_handle && micro_command_socket_out) {
//        rc = sock_fastwrite(s, "[microcmd: f0", 13);
        dbg_printf("miimsocket start (%d)\n", rc);
    }

    rc = do_microcmd(&cmdp, obinbuf, bytelen-2); /* minus sync and chksum */

    // No error checking with socket out!
    if (entity_handle && micro_command_socket_out) {
        if (rc < 0) {
            //cli_printf("Exec of microcmd failed\n");
            //cli_printf("[error: 0f]\n");
            outlen = sprintf(resbuf, " error: %d]\r\n", rc);
//            rc = sock_fastwrite(s, resbuf, outlen);
            dbg_printf("miimsocket error %d\n", rc);
        } else {
            char *p;
            outlen = dbuf_len(obinbuf);
            dbuf_appendstr(ocharbuf, "[microcmd: f0");
            p = dbuf_makeroom(ocharbuf, outlen*2 + 3);
            bin2hexstr((unsigned char *)dbuf_read(obinbuf), p, outlen);
            dbuf_makelen(ocharbuf, outlen*2);
            dbuf_appendstr(ocharbuf, "]\n");
            //cli_write(dbuf_read(ocharbuf), dbuf_len(ocharbuf));
//            rc = sock_fastwrite(s, resbuf, outlen);
            dbuf_reset(ocharbuf);
            dbuf_reset(obinbuf);
        }
    } else if (rc < 0) {
        dbg_printf("Exec of microcmd failed\n");
        sprintf(resbuf, "[error: %d]\r\n", rc);
    } else {
        outlen = dbuf_len(obinbuf);
        rc = 2*outlen + 16;
        if (rc < maxlen) {
            strcpy(resbuf, "[microcmd: f0"); //dbuf_appendstr(ocharbuf, "[microcmd: f0");
            rc = strlen(resbuf);
            bin2hexstr((unsigned char *)dbuf_read(obinbuf), resbuf + rc, outlen);
            rc += 2*outlen;
            strcpy(resbuf + rc, "]\r\n");
            //dbuf_reset(ocharbuf);
            dbuf_reset(obinbuf);
        } else {
            dbg_printf("Output buffer overrun in microcmd\n");
            strcpy(resbuf, "[error: 0f Output buffer overrun in microcmd]\r\n");
        }
    }
    return strlen(resbuf); //return CLI_OK;
}

// This is from rabbit code, not app_miim.c
int miim_cmd_microsetup(void *handle, const char *cmd, const char *param, char *resbuf)
{
    int rc;

    //if (!(optr = skip_cmd(cmd_line)))
    //  return CLI_USER_ERROR_INFO;
    //while(*optr == ' ') optr++;
    rc = -1;
    if (0 == strcmp(cmd, "mdcpin")) {
        MDC = ((unsigned int) strtol(param, (char **)NULL, 0));
        rc = sprintf(resbuf, "[MDCpin: %d]\r\n", MDC);
    } else if (0 == strcmp(cmd, "mdiopin")) {
        MDIO = ((unsigned int) strtol(param, (char **)NULL, 0));
        rc = sprintf(resbuf, "[MDCpin: %d]\r\n", MDIO);
    } else if (0 == strcmp(cmd, "phyoffset")) {
        micro_phyoffset = ((unsigned int) strtol(param, (char **)NULL, 0));
        rc = sprintf(resbuf, "[phyoffset: %d]\r\n", micro_phyoffset);
    } else if (0 == strcmp(cmd, "miimpoll")) {
        miim_poll = ((unsigned int) strtol(param, (char **)NULL, 0));
        rc = sprintf(resbuf, "[miimpoll: %d]\r\n", miim_poll);
    } else if (0 == strcmp(cmd, "miimbus")) {
        miim_bus = ((unsigned int) strtol(param, (char **)NULL, 0));
        rc = sprintf(resbuf, "[miimbus: %d]\r\n", miim_bus);
    } else if (0 == strcmp(cmd, "miimpath")) {
        if (0 == strcmp(param, "direct")) {
            miim_mode       = MIIMMODE_DIRECT;
            rc = sprintf(resbuf, "[miimpath: direct]\r\n");
        } else if (0 == strcmp(param, "cpld")) {
            miim_mode = MIIMMODE_CPLD;
            rc = sprintf(resbuf, "[miimpath: cpld]\r\n");
#if 0
        } else if ((ptr = strstr(optr, "switch"))) {
            miim_mode = MIIMMODE_SMO_UNMAPPED;
            cli_printf("[miimpath: switch]");
        } else if ((ptr = strstr(optr, "port"))) {
            miim_mode = MIIMMODE_SMO_PORT;
            cli_printf("[miimpath: port]");
#endif
        } else if (0 == strcmp(param, "lutonpi")) {
            miim_mode = MIIMMODE_EPDSI;
            rc = sprintf(resbuf, "[miimpath: lutonpi]\r\n");
        } else if (0 == strcmp(param, "lutonffpi")) {
            miim_mode = MIIMMODE_EPDSIFF;
            rc = sprintf(resbuf, "[miimpath: lutonffpi]\r\n");
        } else {
            rc = sprintf(resbuf, "[Error: Unknown miimpath]\r\n");
        }
    } else if (0 == strcmp(cmd, "miimresult")) {
        if (0 == strcmp(param, "socket")) {
            dbg_printf("miimresult = socket\n");
            micro_command_socket_out = 1;
            rc = sprintf(resbuf, "[miimresult: socket]\r\n");
        } else {
            dbg_printf("miimresult = normal\n");
            micro_command_socket_out = 0;
            rc = sprintf(resbuf, "[miimresult: normal]\r\n");
        }
#if 0
    } else if ((ptr = strstr(optr, "switchapp"))) {
        optr = ptr;
        optr += strlen("switchapp");
        while(*optr == ' ') optr++;
        if ((ptr = strstr(optr, "suspend"))) {
            const char *rc = smo_suspend(entity_handle);
            if (rc)
                cli_printf("[error: %s]\n", rc);
            else
                cli_printf("[switchapp: suspended]\n");
        } else if ((ptr = strstr(optr, "resume"))) {
            const char *rc = smo_resume(entity_handle);
            if (rc)
                cli_printf("[error: %s]\n", rc);
            else
                cli_printf("[switchapp: resumed]\n");
        }	else {
            cli_printf("Error: Unknown switchapp parm %s\n", optr);
            return CLI_USER_ERROR_INFO;
        }
#endif
    } else {
        //cli_printf("Usage: microsetup phyoffset <offset>\n");
        //cli_printf("  adds \"offset\" to phynum in microcmds\n");
        //cli_printf("Or   : microsetup miimpath cpld/switch/port/lutonpi\n");
        //return -1; //CLI_USER_ERROR_INFO;
        rc = sprintf(resbuf, "[Error: Unknown command]\r\n");
    }
    return rc; //return CLI_OK;
}

// End of GENIE app_miim.c
/////////////////////////////////////////////////////////////////////////////
