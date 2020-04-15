/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

static int spi_fd = -1;
static int spi_freq = 400000;
static int spi_padding = 1;
static const char *spi_dev = "/dev/spidev1.1";

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

    printf("RX: %02x %02x %02x-%02x %02x %02x %02x",
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

int spi_reg_io_init()
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

int main(int argc, char **argv)
{
    int res;
    uint32_t chip_id;

    res = spi_reg_io_init();
    spi_reg_read(0x404000, &chip_id);
    printf("fa chip id: %08x\n", chip_id);

    return res;
}


