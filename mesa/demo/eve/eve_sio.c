/*
 * eve_sio.c
 *
 *  Created on: Oct 30, 2012
 *      Author: jsa
 *
 * See: https://www.kernel.org/doc/Documentation/spi/
 */

#include <ctype.h>		// toupper, isspace
#include <errno.h>
#include <fcntl.h>		// open, close
#include <stdint.h>		// uint8_t, uint32_t
#include <stdio.h>		// popen
#include <stdlib.h>		// strtol
#include <string.h>		// memset, strcpy, strlen
#include <strings.h>	// strcasecmp
#include <unistd.h>		// open, close, read, write
#include <linux/i2c.h>	// i2c_msg
#include <linux/i2c-dev.h>	// I2C_RDWR
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <sys/ioctl.h>	// ioctl

#include "eve_sio.h"	// EVE serial IO: SPI, I2C
#include "eve_gpio.h"

// Globals
const char *i2c_device = "/dev/i2c-1";
const char *spi_device = "/dev/spidev1.0";
int  spi_handle = -1;	// SPI file system handle
int  spi_gpio_cs = 1;	// SPI uses GPIO for chip selects
int  spi_mm_gpio = 0;	// SPI enable use of memory mapped GPIOs for chip selects (faster)
uint8_t spi_mode = SPI_MODE_0;	// SPI operating mode (CPOL=0,CPHA=0,LOOP=0 etc.)
int  spi_cs[] = {P9_23, P9_25, P9_27};	// SPI default GPIOs used for Chip Selects
static int spi_debug = 0; // SPI enable debug output
//int  spi_channel = 0;	// SPI CS
//long spi_hz = 4000000;	// SPI frequency default. On beaglebone -> 3MHz
//int  spi_padding = 0;	// SPI # of padding bytes

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
//#define SPI_MAXCS (3)
#define SPI_MAXCS (ARRAY_SIZE(spi_cs))
#define ISHEXDIGIT(c) (toupper(c) >= 'A' && toupper(c) <= 'F')
/*
 * myhextobuf:
 *    convert input hex string str (base 16) to binary array
 *    Caller must ensure buf is long enough to hold result
 *    Return number of bytes in buffer
 */
int myhextobuf(const char *str, char *buf, int maxlen) {
	int i, len, odd, bytes;
	char hi, lo;

	if (*str == '0' && *(str + 1) == 'x') /* skip preceding 0x */
		str += 2;
	len = strlen(str);
	odd = len % 2; // = 1 if odd number of nibbles
	bytes = len / 2; // Number of complete bytes
	if (bytes + odd > maxlen)
		return 0; // string too long, abort
	if (odd) { // If odd no. of nibbles, convert first nibble
		lo = str[0];
		buf[0] = 0xf & (toupper(lo) - (ISHEXDIGIT(lo) ? ('A' - 10) : '0'));
	} // convert rest of nibbles
	for (i = 0; i < bytes; i++) {
		hi = str[2 * i + odd]; // offset 1 nibble if odd no. of nibbles
		lo = str[2 * i + 1 + odd];
		hi = 0xf & (toupper(hi) - (ISHEXDIGIT(hi) ? ('A' - 10) : '0'));
		lo = 0xf & (toupper(lo) - (ISHEXDIGIT(lo) ? ('A' - 10) : '0'));
		buf[i + odd] = (hi << 4) + lo;
	}
	return (bytes + odd);
}

#define TOHEXDIGIT(c) (((c) > 9) ? ((c) - 10 + 'a') : ((c) + '0'))
/*
 * mybuftohex:
 *    convert binary array to hex string str (base 16)
 *    Caller must ensure str is long enough to hold result
 *    Return number of bytes in str
 */
int mybuftohex(const char *buf, char *str, int len) {
	int i, hi, lo, rc = 0;

	if (len) {
		strcpy(str, "0x");
		str += 2; // point to end of string
		for (i = 0; i < len; i++) { // Convert 4 bytes of buffer to hex
			hi = (*buf & 0xf0) >> 4; // Most significant nibble
			lo = (*buf++ & 0x0f); // Least significant nibble
			*str++ = TOHEXDIGIT(hi);
			*str++ = TOHEXDIGIT(lo);
		}
		rc = 2 * len + 2;
	}
	*str = 0;
	return (rc);
}

int SPI_set_device(const char *device) {
	int rc = -1;
	int rc_access = 1;
	if (device) {
		//rc_access = access(device, X_OK);	// Test for execute access. This fails !?!
		//rc_access = access(device, R_OK|W_OK);	// Test for R/W access
		rc_access = access(device, F_OK);	// Test for existence
		if (rc_access == 0) {
			spi_device = device;
			rc = 0;
		}
	}
	if (spi_debug) log2stderr("SPI device '%s' access: %d (%s)", spi_device, rc_access, strerror(errno));
	return rc;
}

const char * SPI_get_device(void) {
	return spi_device;
}

int SPI_open(const char *spi_name) {
	int fd, rc;

	if (!spi_name)
		spi_name = spi_device;
	fd = open(spi_name, O_RDWR);
	if (-1 == fd) {
		perror("SPI unable to open userspace control file");
		exit(2);
	}
	// Set SPI operating mode
	rc = ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
	if (-1 == rc)
		perror("SPI unable to set mode");
	if (spi_debug) log2stderr("SPI opened device '%s'", spi_device);
	return fd;
}

int SPI_close(int handle) {
	if ( (handle >= 0) && (-1 == close(handle)) ) {
		perror("SPI failed to close filehandle");
	}
	return -1;
}
static int spi_padding = 1;
/*
 * SPI_brw:	SPI Binary Read/Write
 *    Handles both Write-then-Read (duplex=0) and simultaneous R/W.
 *    Caller must ensure rxbuf is long enough to hold result, i.e. sum of txlen, rxlen and padding.
 *    Return number of bytes read.
 */
unsigned char * SPI_brw(SPI_STATE *spi, const unsigned char *txbuf, int txlen, unsigned char *rxbuf, int rxlen, int duplex) {
	int status;
	struct spi_ioc_transfer xfer;
	uint32_t xferlen;
	uint8_t  bpw = 8;

	if (spi_handle < 0)	// SPI file not opened!
		return NULL;
	if (duplex)
		xferlen = (txlen > rxlen) ? txlen : rxlen;
	else {	// Sequential Write then Read
		txlen += rxlen ? spi->padding[spi->channel] : 0;  // add padding for reads. NB data sent during padding is undefined!
		xferlen = txlen + rxlen;
	}
	if (xferlen > SPI_MAX_BYTES) {
		return NULL;
	} else if (0 == (xferlen % 4)) {
		// bpw = 32;
		// Data are interpreted as arrays of words (not bytes), so to
		// use this speedup (which is not large, 2-3us/byte), bytes must be
		// shuffled within words as architecture seems to be little-endian.
	} else if (0 == (xferlen % 2)) {
		// bpw = 16;
	}
	xfer.tx_buf = (unsigned long) txbuf;	// _u64
	xfer.rx_buf = (unsigned long) rxbuf;	// _u64
	xfer.len = xferlen;			// _u32 Length of tx and rx buffers, in bytes.
    // _u32 Temporary override of the device's bitrate.
	xfer.speed_hz = spi->freq[spi->channel] ? spi->freq[spi->channel] : spi->freq[0];
	xfer.bits_per_word = bpw;	// _u8  Temporary override of the device's wordsize. There is a 1us pause between each word.
	xfer.cs_change = 1;			// _u8  True to deselect device before starting the next transfer
	xfer.delay_usecs = 0;		// _u16 If nonzero, how long to delay after the last bit transfer
								//      before optionally deselecting the device before the next transfer.
	if (spi_gpio_cs) SPI_set_cs(spi, 0);
	status = ioctl(spi_handle, SPI_IOC_MESSAGE(1), &xfer);
	if (spi_gpio_cs) SPI_set_cs(spi, 1);


    printf("tr.len:%d tr.speed_hz:%d, tr.bits_per_word:%d\n",xfer.len, xfer.speed_hz, xfer.bits_per_word);
    printf("RX: %02x %02x %02x-%02x %02x %02x %02x\n",
           txbuf[0], txbuf[1], txbuf[2],
           rxbuf[3 + spi_padding],
           rxbuf[4 + spi_padding],
           rxbuf[5 + spi_padding],
           rxbuf[6 + spi_padding]);

	if (status < 0) {
		perror("SPI failed to send");
        log2stderr("SPI_BRW unable to send data to CS:%d", spi->channel);
		return NULL;
	}

	return (rxbuf + (duplex ? 0 : txlen));
}

int SPI_hrw(SPI_STATE *spi, const char *txstr, int rxlen, char *rxstr, int duplex) {
	int txlen;
	unsigned char *rx, txbuf[SPI_MAX_BYTES], rxbuf[SPI_MAX_BYTES];

	if (spi_handle < 0)	// SPI file not opened!
		return -1;
	if (spi->padding[spi->channel]) memset(txbuf, 0xff, SPI_MAX_BYTES);	// padding bytes set to 0xff
	txlen =  myhextobuf(txstr, (char *)txbuf, SPI_MAX_BYTES);
	rx = SPI_brw(spi, (unsigned char *) &txbuf, txlen, (unsigned char *) &rxbuf, rxlen, duplex);
	return mybuftohex((char *) rx, rxstr, rxlen);
}

int SPI_set_delay(SPI_STATE *spi, long period) {
	long delay, freq;
	int bits;
	// Beaglebone max. is 48MHz ~ 21ns, and steps down by factors of 2.
	// 48000000/1024=46875
	// Calculation of actual period/frequency
	delay = (period % 20) ? (period / 20) + 1 : (period / 20);
	for (bits= 0; delay > 0; bits++) {
		delay = delay >> 1;
	}
	delay = 20 * (1 << bits); // only keep most significant bit
	freq  = delay ? (1000000000L / delay) : 1000000;

    if (spi->channel_state_enabled) {
        spi->freq[spi->channel] = freq;
        if (spi_debug) log2stderr("SPI delay for channel %d requested %ld, actual %ld, SPI Hz actual %ld",
                                  spi->channel, period, delay, freq);
    } else {
        for (int i = 0; i < SPI_MAX_CHANNELS; i++) {
            spi->freq[i] = freq;
        }
        if (spi_debug) log2stderr("SPI delay (ch %d) requested %ld, actual %ld, SPI Hz actual %ld",
                                  spi->channel, period, delay, spi->freq[spi->channel]);
    }
	return (int) delay;
}

int SPI_set_channel(SPI_STATE *spi, int channel) {
	int max_cs, old_channel;

	max_cs = ARRAY_SIZE(spi_cs);			// GPIO CS: number of elements in array
    old_channel = spi->channel;
	if (!spi_gpio_cs) max_cs = 1 << max_cs;	// GPIO select: number of combinations
	if (spi_debug) log2stderr("SPI CS max %d, current %d, new %d", max_cs, spi->channel, channel);
    if (old_channel == channel) return old_channel; // Nothing to do...
	if (0 <= channel && channel < max_cs) {
		spi->channel = channel;
		// Open correct SPI device. Currently only have spidev1.0,
		// which is device 1, chip select 0.
		// Therefore additional CS are implemented with GPIOs.
        // TODO: Close previous SPI device if switching devices.
		//if (0 <= spi_handle) spi_handle = SPI_close(spi_handle);
		if (spi_handle < 0) // use default device. TBD support for configurable device!
            spi_handle = SPI_open(spi_device);
		//pinMode(P9_27, OUTPUT, 7, PULLUP);
		//pinMode(P9_25, OUTPUT, 7, PULLUP);
		//pinMode(P9_23, OUTPUT, 7, PULLUP);
		for (int i = 0; i < SPI_MAXCS; i++) {
			gpio_export(spi_cs[i]);
            if (spi_mm_gpio) gpio_mm_dir( spi_cs[i], 1);
			else             gpio_set_dir(spi_cs[i], 1);

		}
		if (spi_gpio_cs) {	// Always set all CS pins to inactive: CS0=P9_27, CS1=P9_25, CS2=P9_23
			for (int i = 0; i < SPI_MAXCS; i++) {
				if (spi_mm_gpio) gpio_mm_set(   spi_cs[i], 1);
				else             gpio_set_value(spi_cs[i], 1);
			}
			//digitalWrite(P9_27, HIGH);
			//digitalWrite(P9_25, HIGH);
			//digitalWrite(P9_23, HIGH);
		} else {			// Set SPI CS multiplexer select
			for (int i = 0; i < SPI_MAXCS; i++) {
				if (spi_mm_gpio) gpio_mm_set(spi_cs[i],    channel & 1<<i);
				else             gpio_set_value(spi_cs[i], channel & 1<<i);
			}
		}
		if (spi_debug) log2stderr("SPI opened '%s'%s", spi_device, spi_gpio_cs ? " using GPIO CS" : " using GPIO select");
	} else if (-1 == channel) {
		// Close SPI file handle
		spi_handle = SPI_close(spi_handle);
		if (spi_gpio_cs) {	// Disable GPIOs: set to inputs, then disable
			for (int i = 0; i < SPI_MAXCS; i++) {
                if (spi_mm_gpio) gpio_mm_dir( spi_cs[i], 1);
                else             gpio_set_dir(spi_cs[i], 1);
				gpio_unexport(spi_cs[i]);
			}
			//pinMode(P9_27, INPUT, 7, PULLUP);
			//pinMode(P9_25, INPUT, 7, PULLUP);
			//pinMode(P9_23, INPUT, 7, PULLUP);
		}
		if (spi_debug) log2stderr("SPI closed (channel %d)", channel);
	}
	return old_channel;
}

/*
 * 300us transaction for file system GPIO & 1GHz CPU
 * 630us transaction for file system GPIO & 300MHz CPU
 * 120us transaction for memory mapped GPIO & 1GHz CPU
 * 240us transaction for memory mapped GPIO & 300MHz CPU
 */
void SPI_set_cs(SPI_STATE *spi, int level) {

	if (!spi_gpio_cs)
		return;	// Do nothing if not using GPIO chip selects
	if (spi_mm_gpio) gpio_mm_set(spi_cs[spi->channel], level);
	else gpio_set_value(spi_cs[spi->channel], level);
}

int SPI_set_gpio_cs(int on) {
	spi_gpio_cs = on ? 1:0;;
	// ensure all chip selects are enabled and inactive
	for (int i = 0; i < SPI_MAXCS; i++) {
		gpio_export(spi_cs[i]);
		if (spi_mm_gpio) {
            gpio_mm_dir(spi_cs[i], 1);
            gpio_mm_set(spi_cs[i], 1);
        }	else {
            gpio_set_dir(spi_cs[i], 1);
            gpio_set_value(spi_cs[i], 1);
        }
	}
	log2stderr("SPI GPIOs as chip selects %s", spi_gpio_cs ? "enabled" : "disabled");
	return spi_gpio_cs;
}

int SPI_set_padding(SPI_STATE *spi, int padding) {
	if (padding >= 0) {
        if (spi->channel_state_enabled) {
            spi->padding[spi->channel] = padding;
            if (spi_debug) log2stderr("SPI padding for channel %d set to %d bytes",
                                      spi->channel, spi->padding[spi->channel]);
        } else {
            for (int i = 0; i < SPI_MAX_CHANNELS; i++) {
                spi->padding[i] = padding;
            }
            if (spi_debug) log2stderr("SPI padding set to %d bytes", spi->padding[spi->channel]);
        }
	}
	return spi->padding[spi->channel];
}

int SPI_set_mm_gpio(int on) {
	spi_mm_gpio = on ? 1:0;
	log2stderr("SPI memory mapped GPIO %s", spi_mm_gpio ? "enabled" : "disabled");
	return spi_mm_gpio;
}

void SPI_set_debug(int on) {
	spi_debug = on;
	log2stderr("SPI debug %s", spi_debug ? "enabled" : "disabled");
}

int i2c_set_device(const char *device) {
	int rc = -1;
//	if (device && (access(device, X_OK) == 0) ) { 	    // Test for execute access
//	if (device && (access(device, R_OK|W_OK) == 0) ) {  // Test for R/W access
	if (device && (access(device, F_OK) == 0) ) {       // Test for existence
		i2c_device = device;
		rc = 0;
	}
	return rc;
}

const char * i2c_get_device(void) {
	return i2c_device;
}

/*
 * i2c_open:
 *    open the file system I2C link
 *    Return file handle
 */
int i2c_open(const char *i2c_file_name) {
	int i2c_file;

	if (!i2c_file_name)
		i2c_file_name = i2c_device;	// use default device
    // Open a connection to the I2C userspace control file.
    if ((i2c_file = open(i2c_file_name, O_RDWR)) < 0) {
        perror("I2C unable to open userspace control file");
    }	// return error code...
	return i2c_file;
}

void i2c_close(int i2c_file) {
	if (i2c_file >= 0)
		close(i2c_file);
}

int i2c_read_bytes(int file, unsigned char addr, int rxlen, unsigned char *rxbuf) {

    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr  = addr;
    messages[0].flags = I2C_M_RD /* | I2C_M_NOSTART*/;
    messages[0].len   = rxlen;
    messages[0].buf   = rxbuf;
    /* Send the request to the kernel and get the result back */
    packets.msgs      = messages;
    packets.nmsgs     = 1;
    if(ioctl(file, I2C_RDWR, &packets) < 0) {
        perror("I2C_RD unable to send data");
        log2stderr("I2C_RD unable to send data to 0x%02X", addr);
        return 0;
    }
	return rxlen;
}

int i2c_write(int file, unsigned char addr, int txlen, unsigned char *txbuf) {

	unsigned char outbuf[20];
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    if (txlen < 1 || 16 < txlen)
	return -1;
    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = txlen;
    messages[0].buf   = outbuf;
    memcpy(outbuf, txbuf, txlen);
    /* Transfer the i2c packets to the kernel and verify it worked */
    packets.msgs  = messages;
    packets.nmsgs = 1;
    if(ioctl(file, I2C_RDWR, &packets) < 0) {
        perror("I2C_WR unable to send data");
        log2stderr("I2C_WR unable to send data to 0x%02X", addr);
        return 0;
    }
    return txlen;
}

int i2c_read_rand(int file, unsigned char addr, unsigned char reg, int rxlen, unsigned char *rxbuf) {

	unsigned char outbuf;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];
    /*
     * In order to read a register, we first do a "dummy write" by writing
     * 0 bytes to the register we want to read from.  This is similar to
     * the packet in i2c_write_rand, except it's 1 byte rather than 2+.
     */
    outbuf = reg;
    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = sizeof(outbuf);
    messages[0].buf   = &outbuf;
    /* The data will get returned in this structure */
    messages[1].addr  = addr;
    messages[1].flags = I2C_M_RD /* | I2C_M_NOSTART*/;
    messages[1].len   = rxlen;
    messages[1].buf   = rxbuf;
    /* Send the request to the kernel and get the result back */
    packets.msgs      = messages;
    packets.nmsgs     = 2;
    if(ioctl(file, I2C_RDWR, &packets) < 0) {
        perror("I2C_RD_RAND unable to send data");
        log2stderr("I2C_RD_RAND unable to send data to A:0x%02X R:0x%02X", addr, reg);
        return 0;
    }
	return rxlen;
}

int i2c_write_rand(int file, unsigned char addr, unsigned char reg, int txlen, unsigned char *txbuf) {

	unsigned char outbuf[20];
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    if (txlen < 1 || 16 < txlen)
	return -1;
    messages[0].addr  = addr;
    messages[0].flags = 0;
    messages[0].len   = txlen + 1;
    messages[0].buf   = outbuf;
    /* The first byte indicates which register we'll write */
    outbuf[0] = reg;
    /* The remaining bytes indicate the values to write. */
    memcpy(outbuf + 1, txbuf, txlen);
    /* Transfer the i2c packets to the kernel and verify it worked */
    packets.msgs  = messages;
    packets.nmsgs = 1;
    if(ioctl(file, I2C_RDWR, &packets) < 0) {
        perror("I2C_WR_RAND unable to send data");
        log2stderr("I2C_WR_RAND unable to send data to A:0x%02X R:0x%02X", addr, reg);
        return 0;
    }
    return txlen;
}
