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

#include <linux/gpio.h>
#include <linux/spi/spi_vcoreiii.h>

#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"

#define VCOREIII_SPI_BUS 0

static struct spi_board_info board_spi_add_info[] = {
    // sync
    {
        .modalias = "spidev",
        .max_speed_hz = 100000,
        .chip_select = SPI_VCOREIII_NUM_HW_CS + 10,    // GPIO 10 == nCS
        .mode = SPI_MODE_0,
    },
};

static struct spi_device *spi_devices[ARRAY_SIZE(board_spi_add_info)];

// -------------- I2C -------------

struct i2c_mux_vcoreiii_entry {
    u8 adp_no;
    u8 value;
};

static struct i2c_mux_vcoreiii_entry i2c_mux_entries[] = {
    /*               adp, value */
    { MUX_PORT_START + 8,     0  },  // SFP0
    { MUX_PORT_START + 9,     1  },  // SFP1
    {                201,     2  },  // PoE For Silicon Labs  - MUX value can be either 2 or 3, see schematic u64
    {                202,     3  },  // PoE For Texas Instruments  - MUX value can be either 2 or 3, see schematic u64
    {                203,     2  },  // PoE For MSCC PD69200  - MUX value can be either 2 or 3, see schematic u64
    {                204,     2  },  // PoE For MSCC PD69200 add-on board (PCA9537 chip) - MUX value can be either 2 or 3, see schematic u64
};

#define GPIO_SCL  5
#define GPIO_MUX 11
static struct vcoreiii_mux_gpios mux_gpios[] = {
    {GPIO_SCL, VCOREIII_GPIO_MODE_ALT1,   true, 1},
    {GPIO_MUX, VCOREIII_GPIO_MODE_NORMAL, true, 0},
};

static void i2c_mux_select_channel(struct i2c_adapter *adap, u32 chan, bool select)
{
    if (select) {
        const struct i2c_mux_vcoreiii_entry *entry = &i2c_mux_entries[chan];
        //printk(KERN_ERR "mux: Set GPIO %d = %d\n", GPIO_MUX, entry->value);
        vcoreiii_gpio_set_value(GPIO_MUX, entry->value);
#if 0
        printk(KERN_ERR "mux: Set GPIO %d, OE = 0x%08x OUT = 0x%08x\n",
               GPIO_MUX,
               readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OE),
               readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT));
#endif
    }
}

static u32 i2c_mux_channel2port(u32 chan)
{
    return i2c_mux_entries[chan].adp_no;
}

static struct vcoreiii_mux_dd mux_data = {
    .n_channels =  ARRAY_SIZE(i2c_mux_entries),
    .gpios = mux_gpios,
    .n_gpios = ARRAY_SIZE(mux_gpios),
    .select_channel = i2c_mux_select_channel,
    .channel2port = i2c_mux_channel2port,
};

static const struct vcoreiii_i2c_device i2c_devices[] = {
    { .adp_no =   0, I2C_BOARD_INFO("synce_cpld",   0x75), }, // On default bus segment
    { .adp_no =   0, I2C_BOARD_INFO("synce_silabs", 0x71), }, // On default bus segment
    { .adp_no =   0, I2C_BOARD_INFO("synce_dac",    0x0c), }, // On default bus segment
    { .adp_no = 201, I2C_BOARD_INFO("si3452_1",     0x21), },
    { .adp_no = 201, I2C_BOARD_INFO("si3452_2",     0x25), },
    { .adp_no = 201, I2C_BOARD_INFO("si3452_3",     0x29), },
    { .adp_no = 201, I2C_BOARD_INFO("si3452_4",     0x2B), },
    { .adp_no = 201, I2C_BOARD_INFO("si3452_5",     0x2D), },
    { .adp_no = 201, I2C_BOARD_INFO("si3452_6",     0x2F), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_1",    0x20), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_2",    0x21), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_3",    0x22), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_4",    0x23), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_5",    0x24), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_6",    0x25), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_7",    0x28), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_8",    0x29), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_10",   0x2B), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_11",   0x2C), },
    { .adp_no = 202, I2C_BOARD_INFO("slus787_12",   0x2D), },
    { .adp_no = 203, I2C_BOARD_INFO("pd69x00",      0x14), },
    { .adp_no = 203, I2C_BOARD_INFO("pd69x00bt",    0x20), },
    { .adp_no = 204, I2C_BOARD_INFO("pd69x00_io",   0x49), },  // I2C address is fixed to 0x49 - SEE PCA9537 datasheet section 6.1
};

static struct i2c_client *i2c_clients[ARRAY_SIZE(i2c_devices)];

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

    vcoreiii_gpio_set_mode(10, VCOREIII_GPIO_MODE_NORMAL);    // GPIO16 driven as CS

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
