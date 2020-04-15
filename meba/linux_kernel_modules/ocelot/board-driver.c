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
#include <linux/delay.h>

#include <linux/gpio.h>
#include <linux/spi/spi_vcoreiii.h>
#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"

#define VCOREIII_SPI_BUS 0

static struct spi_board_info board_spi_add_info[] = {
    // sync (used if external DPLL is mounted)
    {
        .modalias = "spidev",
        .max_speed_hz = 8000000,
        .chip_select = 2,                             // GPIO 09 == SI_nCS2
        .mode = SPI_MODE_0,                           // CS low (nCS)
    },
};

static struct spi_device *spi_devices[ARRAY_SIZE(board_spi_add_info)];

// Same defines as in board_if.h
#define VTSS_BOARD_OCELOT_PCB120 28
#define VTSS_BOARD_OCELOT_PCB123 29

static int board_type = VTSS_BOARD_OCELOT_PCB123; // Default PCB123
module_param(board_type, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
MODULE_PARM_DESC(board_type, "The number X in PCB-X, where X=120,121,123");

// --- --- This is for PCB120
#define GPIO_SCL_PD69200 17
#define GPIO_SCL_SFP_1   20
#define GPIO_SCL_SFP_2   21

struct i2c_mux_vcoreiii_entry {
    u8 adp_no;
    u8 value;
};

static struct i2c_mux_vcoreiii_entry i2c_mux_entries[3] = {
    /*  adp,                 value */
    {   201,                    0  },    // PoE
    {   MUX_PORT_START + 8,     1  },    // SFP-1
    {   MUX_PORT_START + 9,     2  },    // SFP-2
};

// Configuration of the GPIOs used in this context
//
static struct vcoreiii_mux_gpios mux_gpios[] = {
  { GPIO_SCL_PD69200, VCOREIII_GPIO_MODE_ALT2, false, 0},
  { GPIO_SCL_SFP_1,   VCOREIII_GPIO_MODE_ALT3, false, 0},
  { GPIO_SCL_SFP_2,   VCOREIII_GPIO_MODE_ALT3, false, 0},
};

// Mapping from channel number to adapter no.
//
static u32 i2c_mux_channel2port(u32 chan)
{
  return i2c_mux_entries[chan].adp_no;
}

// Function to enable/disable (depending on 'select') the I2C
// channel given by 'chan'.
//
static void i2c_mux_select_channel(struct i2c_adapter *adap, u32 chan, bool select)
{
  static const int chan2gpio[3]={ GPIO_SCL_PD69200,
				  GPIO_SCL_SFP_1,
				  GPIO_SCL_SFP_2    };

  if ( !(chan<ARRAY_SIZE(chan2gpio)) ) { /* Error */ return; }
  vcoreiii_gpio_set_value(chan2gpio[chan], select ? 1 : 0);
  msleep(8); /* Wait for SGPIO to settle */
}

static struct vcoreiii_mux_dd mux_data_pcb120 = {
    .n_channels =  ARRAY_SIZE(i2c_mux_entries),
    .gpios = mux_gpios,
    .n_gpios = ARRAY_SIZE(mux_gpios),
    .select_channel = i2c_mux_select_channel,
    .channel2port = i2c_mux_channel2port,
};

static const struct vcoreiii_i2c_device i2c_devices_pcb120[] = {
    { .adp_no = 201, I2C_BOARD_INFO("pd69x00", 0x20) },  // On 1st I2C bus segment
};

static struct i2c_client *i2c_clients_pcb120[ARRAY_SIZE(i2c_devices_pcb120)];

// --- --- This is for PCB123
#define NUM_SFP_PORTS_PCB123   8 /* Number of SFP ports */
#define SFP_PORT_OFFSET_PCB123 4 /* Port number of the first SFP port */

static void i2c_mux_select_channel_pcb123(struct i2c_adapter *adap, u32 chan, bool select)
{
    if (select) {
        vcoreiii_sgpio_set_value(13, 0, chan & VTSS_BIT(0) ? 1 : 0);
        vcoreiii_sgpio_set_value(13, 1, chan & VTSS_BIT(1) ? 1 : 0);
        vcoreiii_sgpio_set_value(14, 0, chan & VTSS_BIT(2) ? 1 : 0);
        msleep(8); /* Wait for SGPIO to settle */
    }
}

static u32 i2c_mux_channel2port_pcb123(u32 chan)
{
    return MUX_PORT_START + SFP_PORT_OFFSET_PCB123 + chan;
}

static struct vcoreiii_mux_dd mux_data_pcb123 = {
    .n_channels = NUM_SFP_PORTS_PCB123,
    .gpios = NULL,
    .n_gpios = 0,
    .select_channel = i2c_mux_select_channel_pcb123,
    .channel2port = i2c_mux_channel2port_pcb123,
};

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

    switch (board_type) {
        case VTSS_BOARD_OCELOT_PCB120:
            meba_i2c_add(&mux_data_pcb120, 0);
            meba_i2c_add_devices(i2c_devices_pcb120, i2c_clients_pcb120, ARRAY_SIZE(i2c_devices_pcb120));
            break;
      
        case VTSS_BOARD_OCELOT_PCB123:
            // Reserve CS2 GPIO pin (GPIO09 on Ocelot)
            vcoreiii_gpio_set_mode(9, VCOREIII_GPIO_MODE_ALT1);

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

            meba_i2c_add(&mux_data_pcb123, 0);
            break;
      
        default:
            return -EINVAL;
    }

    return rc;
}

static void meba_cleanup_module(void)
{
    int i;

    switch (board_type) {
        case VTSS_BOARD_OCELOT_PCB120:
            meba_i2c_del_devices(i2c_clients_pcb120, ARRAY_SIZE(i2c_devices_pcb120));
            meba_i2c_del(&mux_data_pcb120);
            break;
  
        case VTSS_BOARD_OCELOT_PCB123:
            for (i = 0; i < ARRAY_SIZE(spi_devices); i++) {
                if (spi_devices[i]) {
                    spi_unregister_device(spi_devices[i]);
                    spi_devices[i] = NULL;
                }
            }
        
            meba_i2c_del(&mux_data_pcb123);
            break;
    }
}

module_init(meba_init_module);
module_exit(meba_cleanup_module);

MODULE_AUTHOR("Lars Povlsen <lars.povlsen@microsemi.com>");
MODULE_DESCRIPTION("VCoreIII Board drivers");
MODULE_LICENSE("Dual MIT/GPL");
