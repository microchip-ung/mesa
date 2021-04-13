// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static int spi_fd = -1;
static int spi_freq = 400000;
static int spi_padding = 1;

/* MEBA callouts */
#define TO_SPI(_a_)     (_a_ & 0x00FFFFFF) /* 24 bit SPI address */
#define SPI_NR_BYTES     7                 /* Number of bytes to transmit or receive */
#define SPI_PADDING_MAX 15                 /* Maximum number of optional padding bytes */

int spi_reg_read(const uint32_t addr, uint32_t *const value)
{
    uint8_t tx[SPI_NR_BYTES + SPI_PADDING_MAX] = { 0 };
    uint8_t rx[sizeof(tx)] = { 0 };
    uint32_t siaddr = TO_SPI(addr);
    int ret;

    memset(tx, 0xff, sizeof(tx));
    tx[0] = (uint8_t)(siaddr >> 16);
    tx[1] = (uint8_t)(siaddr >> 8);
    tx[2] = (uint8_t)(siaddr >> 0);

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long) tx,
        .rx_buf = (unsigned long) rx,
        .len = SPI_NR_BYTES + spi_padding,
        .delay_usecs = 0,
        .speed_hz = spi_freq,
        .bits_per_word = 8,
    };

    ret = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1) {
        printf("ERROR:%d> spi_read: %s=n\n", __LINE__, strerror(errno));
        return -1;
    }

    uint32_t rxword =
            (rx[3 + spi_padding] << 24) |
            (rx[4 + spi_padding] << 16) |
            (rx[5 + spi_padding] << 8) |
            (rx[6 + spi_padding] << 0);

    *value = rxword;

    printf("RX: %02x %02x %02x-%02x %02x %02x %02x\n",
           tx[0], tx[1], tx[2],
           rx[3 + spi_padding],
           rx[4 + spi_padding],
           rx[5 + spi_padding],
           rx[6 + spi_padding]);

    return 0;
}

int spi_reg_write(const uint32_t addr, const uint32_t value)
{
    uint8_t tx[SPI_NR_BYTES] = { 0 };
    uint8_t rx[sizeof(tx)] = { 0 };
    uint32_t siaddr = TO_SPI(addr);
    uint32_t read_back;
    int ret;

    tx[0] = (uint8_t)(0x80 | (siaddr >> 16));
    tx[1] = (uint8_t)(siaddr >> 8);
    tx[2] = (uint8_t)(siaddr >> 0);
    tx[3] = (uint8_t)(value >> 24);
    tx[4] = (uint8_t)(value >> 16);
    tx[5] = (uint8_t)(value >> 8);
    tx[6] = (uint8_t)(value >> 0);

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long) tx,
        .rx_buf = (unsigned long) rx,
        .len = sizeof(tx),
        .delay_usecs = 0,
        .speed_hz = spi_freq,
        .bits_per_word = 8,
    };

    ret = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1) {
        printf("TX: %02x %02x %02x-%02x %02x %02x %02x -> ERROR\n", tx[0],
               tx[1], tx[2], tx[3], tx[4], tx[5], tx[6]);
        printf("ERROR:%d> spi_write: %s=n\n", __LINE__, strerror(errno));
        return -1;
    }

    printf("TX: %02x %02x %02x-%02x %02x %02x %02x -> OK\n", tx[0], tx[1],
           tx[2], tx[3], tx[4], tx[5], tx[6]);

    spi_reg_read(addr, &read_back);
    if (value != read_back) {
        printf("Read back error: expect: %08x actual: %08x\n", value, read_back);
    }

    return 0;
}

int spi_reg_io_init(char *spi_dev)
{
    int ret, mode = 0;
    printf("DEV: %s, Freq: %d, Padding: %d\n", spi_dev, spi_freq, spi_padding);

    if (spi_padding > SPI_PADDING_MAX) {
        printf("ERROR:%d> invalid padding length\n", __LINE__);
        return -1;
    }
    spi_fd = open(spi_dev, O_RDWR);
    if (spi_fd < 0) {
        printf("ERROR:%d> could not open device %s=n\n", __LINE__, strerror(errno));
        return -1;
    }

    ret = ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    if (ret < 0) {
        close(spi_fd);
        spi_fd = -1;
        printf("ERROR:%d> Error setting wr-mode\n", __LINE__);
        return -1;
    }

    ret = ioctl(spi_fd, SPI_IOC_RD_MODE, &mode);
    if (ret < 0) {
        close(spi_fd);
        spi_fd = -1;
        printf("ERROR:%d> Error setting rd-mode\n", __LINE__);
        return -1;
    }

    return 0;
}

static void help(void)
{
    printf("Usage: spi_reg_read spi_dev offset_hex\n");
    printf("options:\n");
    printf("  -h | --help              Show this help text\n");
    printf("commands:\n");
}

int main(int argc, char **argv)
{
    int res;
    uint32_t chip_id;
    uint32_t reg = 0;
    int f;

    static const struct option options[] =
    {
	{.name = "help",	.val = 'h'},
	{ 0 }
    };

    while (EOF != (f = getopt_long(argc, argv, "h", options, NULL))) {
	switch (f) {
	case 'h':
		help();
		return 0;
	}
    }

    if (argc < 3) {
	   help();
	   return 0;
    }

    reg = strtol(argv[2], NULL, 16);

    res = spi_reg_io_init(argv[1]);
    spi_reg_read(reg, &chip_id);

    return res;
}


