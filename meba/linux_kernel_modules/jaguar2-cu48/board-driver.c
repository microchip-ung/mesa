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

#include <linux/platform_device.h>
#include <linux/module.h>

#include <linux/spi/spi.h>
#include <linux/gpio.h>

#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"

#define VCOREIII_SPI_BUS 0

static struct spi_board_info board_spi_add_info[] = {
    // sync
    {
        .modalias = "spidev",
        .max_speed_hz = 8000000,
        .chip_select = 1,                             // GPIO 16 == SI_nCS1
        .mode = SPI_MODE_0,
    },
    // cpld register interface
    {
        .modalias = "spidev",
        .max_speed_hz = 8000000,
        .chip_select = 14,                             // GPIO 50 == SI_nCS14
        .mode = SPI_MODE_0,
    },
    // cpld FIFO interface
    {
        .modalias = "spidev",
        .max_speed_hz = 8000000,
        .chip_select = 15,                             // GPIO 51 == SI_nCS15
        .mode = SPI_MODE_0,
    },
};

static struct spi_device *spi_devices[ARRAY_SIZE(board_spi_add_info)];

// -------------- I2C -------------

struct i2c_mux_vcoreiii_entry {
    u8 port_no;
    u8 gpiomask;
};

#define IMUX(x)  (1 << x)    // Bits 0-3

static struct i2c_mux_vcoreiii_entry i2c_mux_entries[] = {
        /* port, gpio */
    // 10G SFP are internal mux. See Table 15 in UG1053
    {     49,  IMUX(0) },
    {     50,  IMUX(1) },
    {     51,  IMUX(2) },
    {     52,  IMUX(3) },
    {    101,  0  },  // PoE For Silicon Labs
    {    102,  0  },  // PoE For Texas Instruments
    {    103,  0  },  // PoE For PD69200
};

static struct vcoreiii_mux_gpios mux_gpios[] = {
    { 17, VCOREIII_GPIO_MODE_ALT2, true, 1 },
    { 18, VCOREIII_GPIO_MODE_ALT2, true, 0 },
    { 20, VCOREIII_GPIO_MODE_ALT2, true, 0 },
    { 21, VCOREIII_GPIO_MODE_ALT2, true, 0 },
};

static void i2c_mux_select_channel(struct i2c_adapter *adap, u32 chan, bool select)
{
    int i;
    if (select) {
        u32 value = i2c_mux_entries[chan].gpiomask;
        for (i = 0; i < ARRAY_SIZE(mux_gpios); i++, value >>= 1) {
            bool enb = (value & 1);
            vcoreiii_gpio_set_value(mux_gpios[i].gpio, enb);
            //pr_err("GPIO %d: %s (value 0x%02x)\n", mux_gpios[i].gpio, enb ? "ON " : "OFF", value);
        }
    }
}

static u32 i2c_mux_channel2port(u32 chan)
{
    return MUX_PORT_START + i2c_mux_entries[chan].port_no;
}

static struct vcoreiii_mux_dd mux_data = {
    .n_channels =  ARRAY_SIZE(i2c_mux_entries),
    .gpios = mux_gpios,
    .n_gpios = ARRAY_SIZE(mux_gpios),
    .select_channel = i2c_mux_select_channel,
    .channel2port = i2c_mux_channel2port,
    };

    static const struct vcoreiii_i2c_device i2c_devices[] = {
        { .adp_no = 0, I2C_BOARD_INFO("synce_cpld",   0x75), }, // On main bus segment
        { .adp_no = 0, I2C_BOARD_INFO("synce_silabs", 0x71), }, // On main bus segment
        { .adp_no = 0, I2C_BOARD_INFO("synce_dac",    0x0c), }, // On main bus segment
        { .adp_no = 0, I2C_BOARD_INFO("ptp_dac",      0x0f), }, // On main bus segment
        { .adp_no = 0, I2C_BOARD_INFO("malibu_silabs",0x70), }, // On main bus segment
        { .adp_no = 201, I2C_BOARD_INFO("si3452_1",   0x21), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_2",   0x25), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_3",   0x29), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_4",   0x2B), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_5",   0x2D), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_6",   0x2F), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_7",   0x20), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_8",   0x24), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_9",   0x28), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_10",  0x2A), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_11",  0x2C), },
        { .adp_no = 201, I2C_BOARD_INFO("si3452_12",  0x2E), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_1",  0x20), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_2",  0x21), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_3",  0x22), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_4",  0x23), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_5",  0x24), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_6",  0x25), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_7",  0x28), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_8",  0x29), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_9",  0x2A), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_10", 0x2B), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_11", 0x2C), },
        { .adp_no = 202, I2C_BOARD_INFO("slus787_12", 0x2D), },
        { .adp_no = 203, I2C_BOARD_INFO("pd69x00",    0x14), },
        { .adp_no = 203, I2C_BOARD_INFO("pd69x00-2",  0x28), },
    };

    static struct i2c_client *i2c_clients[ARRAY_SIZE(i2c_devices)];

// -------------- BSP-----------

/*
 * Note: The function_show function is being referred to by the structure instantiation just below it.
 * The macro __ATTR_RO(function) among other things makes a reference to a function called function_show (the argument
 * function with _show appended to it). This is how the function_show function comes into play.
 *
 */
static ssize_t function_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    if (&spi_devices[0]->dev == dev) {
        return sprintf(buf, "%s\n", "synce_dpll");
    } else if (&spi_devices[1]->dev == dev) {
        return sprintf(buf, "%s\n", "cpld");
    } else if (&spi_devices[2]->dev == dev) {
        return sprintf(buf, "%s\n", "cpld_fifo");
    } else {
        return sprintf(buf, "%s\n", "Unknown");
    }
}

static struct device_attribute foo_attribute = __ATTR_RO(function);

static struct attribute *attrs[] = {
    &foo_attribute.attr,
    NULL
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static int meba_init_module(void)
{
    struct spi_master *master;
    int rc = 0;

    // Reserve CS1 (SyncE feature connector)
    vcoreiii_gpio_set_mode(16, VCOREIII_GPIO_MODE_ALT1);
    // CS > 3 are actually controlled as GPIO's - setup on the fly

    master = spi_busnum_to_master(VCOREIII_SPI_BUS);
    if (master) {
        int i;
        for (i = 0; i < ARRAY_SIZE(spi_devices); i++) {
            if ((spi_devices[i] = spi_new_device(master, &board_spi_add_info[i])) == NULL) {
                printk("Error: Unable to register '%s', CS %d\n",
                       board_spi_add_info[i].modalias, board_spi_add_info[i].chip_select);
                rc = EINVAL;
            } else {
                // Add an attribute to SPI devices sysfs directory to indicate if this SPI device is the SyncE DPLL, CPLD or t1e1j1 device (or something else).
                if ((sysfs_create_group(&spi_devices[i]->dev.kobj, &attr_group)) != 0) {
                    printk("Error: Unable to create sysfs file\n");
                    rc = -EINVAL;
                };
            }
        }
    } else {
        printk("Error: Bus %d unknown\n", VCOREIII_SPI_BUS);
        rc = EINVAL;
    }
    meba_i2c_add(&mux_data, 0);
    // Add i2c devices
    meba_i2c_add_devices(i2c_devices, i2c_clients, ARRAY_SIZE(i2c_devices));

    return rc;
}

static void meba_cleanup_module(void)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(spi_devices); i++) {
        if (spi_devices[i]) {
            spi_unregister_device(spi_devices[i]);
            spi_devices[i] = NULL;
        }
    }
    // Unreg i2c devices
    meba_i2c_del_devices(i2c_clients, ARRAY_SIZE(i2c_devices));
    meba_i2c_del(&mux_data);
}

module_init(meba_init_module);
module_exit(meba_cleanup_module);

MODULE_AUTHOR("Lars Povlsen <lars.povlsen@microsemi.com>");
MODULE_DESCRIPTION("VCoreIII Board drivers");
MODULE_LICENSE("Dual MIT/GPL");
