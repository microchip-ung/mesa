// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
/*
 * eve_sio.h
 *
 *  Created on: Oct 30, 2012
 *      Author: jsa
 */

#ifndef _EVE_SIO_H_
#define _EVE_SIO_H_

#define SPI_MAX_BYTES     32
#define SPI_MAX_CHANNELS  8

int myhextobuf(const char *str, char *buf, int maxlen);
//int myhextobuf(const char *str, uint8_t *buf, int maxlen);
int mybuftohex(const char *buf, char *str, int len);
//int mybuftohex(uint8_t *buf, char *str, int len);

typedef struct s_SPI_STATE {
	int  channel;	                   // SPI CS
  int  channel_state_enabled;
	long freq[SPI_MAX_CHANNELS];     // SPI frequency default. On beaglebone -> 3MHz
	int  padding[SPI_MAX_CHANNELS];  // SPI # of padding bytes, 8 channels supported
} SPI_STATE;

int SPI_set_device(const char *device);
const char * SPI_get_device(void);
int SPI_open(const char *spi_name);
int SPI_close(int handle);
int SPI_grw(SPI_STATE *spi, const char *txstr, int rxlen, char *rxstr);
int SPI_gsrw(SPI_STATE *spi, const char *txstr, int rxlen, char *rxstr);
unsigned char * SPI_brw(SPI_STATE *spi, const unsigned char *txbuf, int txlen, unsigned char *rxbuf, int rxlen, int duplex);
int SPI_hrw(SPI_STATE *spi, const char *txstr, int rxlen, char *rxstr, int duplex);
void SPI_set_cs(SPI_STATE *spi, int level);
int SPI_set_gpio_cs(int on);
int SPI_set_delay(SPI_STATE *spi, long period);
int SPI_set_channel(SPI_STATE *spi, int channel);
int SPI_set_padding(SPI_STATE *spi, int padding);
int SPI_set_mm_gpio(int on);
void SPI_set_debug(int on);

int i2c_set_device(const char *device);
const char * i2c_get_device(void);
int i2c_open(const char *i2c_file_name);
void i2c_close(int i2c_file);
int i2c_read_bytes(int file, unsigned char addr, int rxlen, unsigned char *rxbuf);
int i2c_write(int file, unsigned char addr, int txlen, unsigned char *txbuf);
int i2c_read_rand(int file, unsigned char addr, unsigned char reg, int rxlen, unsigned char *rxbuf);
int i2c_write_rand(int file, unsigned char addr, unsigned char reg, int txlen, unsigned char *txbuf);

#endif /* _EVE_SIO_H_ */
