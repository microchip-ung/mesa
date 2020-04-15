/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

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

#include <unistd.h>

#include "main.h"
#include "uio.h"
#include "spi.h"

/*

   |   | 13| 12| 11| 10| 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
   |   |SWM|SCK|COE|SDO|SOE|       CS      |     CS_OE     |SDI|
---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

SWM = 0x2000
SCK = 0x1000
COE = 0x0800
SDO = 0x0400
SOE = 0x0200
SDI = 0x0001

*/

static void delay(int msecs)
{
    usleep(msecs * 1000);
}

static void udelay(int usecs)
{
    //usleep(usecs);
    //(void) reg_read(regoff(spimst_swmode));
}

static void cs_on(int cs)
{
    uint32_t value;

    /* Enable bitbang, SCK_OE, SDO_OE */
    value = (VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE| /* SW Bitbang */
             VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK_OE|    /* SCK_OE */
             VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO_OE);   /* SDO OE */

    reg_write(regoff(spimst_swmode), value);
    delay(1);

    /* Add CS */
    value |= (VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE(VTSS_BIT(cs)) |
              VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS(VTSS_BIT(cs)));

    reg_write(regoff(spimst_swmode), value);

    NOISE("CS_%d ON\n", cs);

    delay(1);
}

static void cs_off(int cs)
{
    reg_write_masked_clear(regoff(spimst_swmode), VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS(VTSS_BIT(cs)));
    reg_write_masked_clear(regoff(spimst_swmode), VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_CS_OE(VTSS_BIT(cs)));
    reg_write_masked_clear(regoff(spimst_swmode), VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_PIN_CTRL_MODE);
}

int do_transfer(const uint8_t *tx, uint8_t *rx, size_t len)
{
    int i, ret = 0;
    uint32_t svalue = reg_read(regoff(spimst_swmode));

    NOISE("Transfer %zd bytes\n", len);

    // Be sure we start with clock low, DO low
    svalue &= ~(VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK|
                VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO);

    for (i = 0; i < len; i++, ret++) {
        uint32_t rx_byte = 0, mask = 0x80, value;
        //printf("data[%d] = %02x\n", i, tx[i]);
        while (mask) {
            // Initial condition: CLK is low.
            value = svalue;
            if (tx && tx[i] & mask) {
                value |= VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDO;
            }
            // Drive data while taking CLK low. The device we're accessing will
            // sample on the following rising edge and will output data on this edge for us
            // to be sampled at the end of this loop.
            reg_write(regoff(spimst_swmode), value);
            // Wait for t_setup.
            udelay(1);
            // Drive the clock high.
            reg_write(regoff(spimst_swmode), value | VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SCK);
            // Wait for t_hold. We actually don't do that when we are
            // doing a posted PCI read, which has enough latency built
            // right in...
            if (rx) {
                value = reg_read(regoff(spimst_swmode));
                if (value & VTSS_F_ICPU_CFG_SPI_MST_SW_MODE_SW_SPI_SDI) {
                    rx_byte |= mask;
                }
            } else {
                udelay(1);
            }
            mask >>= 1;
        }
        if (rx) {
            rx[i] = (uint8_t)rx_byte;
        }
    }
    return ret;
}

int spi_transfer(int cs, const uint8_t *tx, uint8_t *rx, size_t len)
{
    int ret;
    cs_on(cs);
    ret = do_transfer(tx, rx, len);
    cs_off(cs);
    return ret;
}

int spi_cmd(int cs, const uint8_t *cmd, int cmdlen, uint8_t *buf, size_t buflen, int mode)
{
    int ret;
    cs_on(cs);
    do_transfer(cmd, NULL, cmdlen);
    if (mode == SPI_TX) {
        ret = do_transfer(buf, NULL, buflen);
    } else {
        ret = do_transfer(NULL, buf, buflen);
    }
    cs_off(cs);
    return ret;
}
