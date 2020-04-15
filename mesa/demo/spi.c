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
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "mscc/ethernet/switch/api.h"
#include "mscc/ethernet/board/api.h"
#include "main.h"
#include "trace.h"

static int spi_fd = -1;
static int spi_freq = 500000;
static int spi_padding = 1;

static mscc_appl_trace_module_t trace_module = {
    .name = "spi"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

/* MEBA callouts */
#define TO_SPI(_a_)     (_a_ & 0x003FFFFF) /* 22 bit SPI address */
#define SPI_NR_BYTES     7                 /* Number of bytes to transmit or receive */
#define SPI_PADDING_MAX 15                 /* Maximum number of optional padding bytes */

mesa_rc spi_reg_read(const mesa_chip_no_t chip_no,
                     const uint32_t       addr,
                     uint32_t             *const value)
{
    uint8_t tx[SPI_NR_BYTES + SPI_PADDING_MAX] = { 0 };
    uint8_t rx[sizeof(tx)] = { 0 };
    uint32_t siaddr = TO_SPI(addr);
    int ret;

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
        T_E("spi_read: %s", strerror(errno));
        return MESA_RC_ERROR;
    }

    uint32_t rxword =
            (rx[3 + spi_padding] << 24) |
            (rx[4 + spi_padding] << 16) |
            (rx[5 + spi_padding] << 8) |
            (rx[6 + spi_padding] << 0);

    *value = rxword;

    T_D("RX: %02x %02x %02x-%02x %02x %02x %02x",
        tx[0], tx[1], tx[2],
        rx[3 + spi_padding],
        rx[4 + spi_padding],
        rx[5 + spi_padding],
        rx[6 + spi_padding]);

    return MESA_RC_OK;
}

mesa_rc spi_reg_write(const mesa_chip_no_t chip_no,
                      const uint32_t       addr,
                      const uint32_t       value)
{
    uint8_t tx[SPI_NR_BYTES] = { 0 };
    uint8_t rx[sizeof(tx)] = { 0 };
    uint32_t siaddr = TO_SPI(addr);
    int ret;

    tx[0] = (uint8_t)(0x80 | (siaddr >> 16));
    tx[1] = (uint8_t)(siaddr >> 8);
    tx[2] = (uint8_t)(siaddr >> 0);
    tx[3] = (uint8_t)(value >> 24);
    tx[4] = (uint8_t)(value >> 16);
    tx[5] = (uint8_t)(value >> 8);
    tx[6] = (uint8_t)(value >> 0);

    T_D("TX: %02x %02x %02x-%02x %02x %02x %02x",
        tx[0], tx[1], tx[2], tx[3], tx[4], tx[5], tx[6]);

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
        T_E("spi_write: %s", strerror(errno));
        return MESA_RC_ERROR;
    }

    return MESA_RC_OK;
}

mesa_rc spi_reg_io_init(const char *device, int freq, int padding)
{
    mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
    spi_freq = freq;
    spi_padding = padding;
    if (spi_padding > SPI_PADDING_MAX) {
        T_E("Invalid spi_padding %d, Range is 0..%d",
            spi_padding, SPI_PADDING_MAX);
        exit(1);
    }
    spi_fd = open(device, O_RDWR);
    if (spi_fd < 0) {
        T_E("%s: %s", device, strerror(errno));
        exit(1);
    }

    T_D("spi: %s opened", device);

    return MESA_RC_OK;
}

