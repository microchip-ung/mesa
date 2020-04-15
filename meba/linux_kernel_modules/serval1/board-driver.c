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

#include <linux/platform_device.h>
#include <linux/module.h>

#include <linux/gpio.h>
#include <linux/spi/spi_vcoreiii.h>
#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"

#define VCOREIII_SPI_BUS 0

static struct spi_vcoreiii_controller_data spi_cd = {
    .cs_delay = 1000,    // CS delay = 1000 nsec = 1 usec
};

static struct spi_board_info board_spi_add_info[] = {
    // sync
    {
        .modalias = "spidev",
        .max_speed_hz = 100000,
        .chip_select = SPI_VCOREIII_NUM_HW_CS + 6,    // GPIO 6 == CS
        .mode = SPI_MODE_0,                           // CS low (nCS)
        .controller_data = &spi_cd,                   // Use delay
    },
    // t1e1j1
    {
        .modalias = "spidev",
        .max_speed_hz = 100000,
        .chip_select = SPI_VCOREIII_NUM_HW_CS + 17,   // GPIO 17 == CS
        .mode = SPI_MODE_0,                           // CS low (nCS)
        .controller_data = &spi_cd,                   // Use delay
    },
};

static struct spi_device *spi_devices[ARRAY_SIZE(board_spi_add_info)];

// -------------- I2C -------------

struct i2c_mux_vcoreiii_entry {
    u8 adp_no;
    u8 gpio;
};

static const struct i2c_mux_vcoreiii_entry i2c_mux_entries[] = {
    /* adapter, gpio */
    {     4 + MUX_PORT_START,   11 },
    {     5 + MUX_PORT_START,   12 },
    {     6 + MUX_PORT_START,   18 },
    {     7 + MUX_PORT_START,   19 },
    {     8 + MUX_PORT_START,   20 },
    {     9 + MUX_PORT_START,   21 },
};

static const struct vcoreiii_mux_gpios mux_gpios[] = {
    { 11, VCOREIII_GPIO_MODE_ALT3, false, 1 },
    { 12, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 18, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 19, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 20, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 21, VCOREIII_GPIO_MODE_ALT3, false, 0 },
};

static void i2c_mux_select_channel(struct i2c_adapter *adap, u32 chan, bool select)
{
    const struct i2c_mux_vcoreiii_entry *entry = &i2c_mux_entries[chan];
    //printk(KERN_ERR "mux: Set GPIO %d = %d\n", entry->gpio, select);
    vcoreiii_gpio_set_value(entry->gpio, select);
#if 0
    printk(KERN_ERR "mux: Set GPIO %d, OE = 0x%08x OUT = 0x%08x\n",
           entry->gpio,
           readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OE),
           readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT));
#endif
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
    { .adp_no = 4 + MUX_PORT_START, I2C_BOARD_INFO("synce_cpld",   0x75), }, // On GPIO 11 bus segment
    { .adp_no = 4 + MUX_PORT_START, I2C_BOARD_INFO("synce_silabs", 0x71), }, // On GPIO 11 bus segment
    { .adp_no = 4 + MUX_PORT_START, I2C_BOARD_INFO("synce_dac",    0x0c), }, // On GPIO 11 bus segment
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
    } else if (&spi_devices[1]->dev == dev) {
        return sprintf(buf, "%s\n", "t1e1j1");
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

    vcoreiii_gpio_set_mode(6, VCOREIII_GPIO_MODE_NORMAL);    // synce nCS
    vcoreiii_gpio_set_mode(17, VCOREIII_GPIO_MODE_NORMAL);   // t1e1j1 nCS

    master = spi_busnum_to_master(VCOREIII_SPI_BUS);
    if (master) {
        int i;
        for (i = 0; i < ARRAY_SIZE(spi_devices); i++) {
            if ((spi_devices[i] = spi_new_device(master, &board_spi_add_info[i])) == NULL) {
                printk("Error: Unable to register '%s', CS %d\n",
                       board_spi_add_info[i].modalias, board_spi_add_info[i].chip_select);
                rc = -EINVAL;
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
        rc = -EINVAL;
    }

    // Add i2c mux ports
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
    // Unreg i2c mux ports
    meba_i2c_del(&mux_data);
}

module_init(meba_init_module);
module_exit(meba_cleanup_module);

MODULE_AUTHOR("Lars Povlsen <lars.povlsen@microsemi.com>");
MODULE_DESCRIPTION("VCoreIII Board drivers");
MODULE_LICENSE("Dual MIT/GPL");
