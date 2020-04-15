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
#include <linux/delay.h>

#include <linux/reboot.h>
#include <linux/spi/spi.h>
#include <linux/gpio.h>
#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"

#ifdef DEBUG
#define MEBA_D(fmt, arg...) do {if (debug) printk(KERN_DEBUG "DEBUG %s#%d: "fmt"\n", __FUNCTION__, __LINE__, ##arg);} while(0)
#else
#define MEBA_D(fmt, arg...) do {if (debug) printk(KERN_INFO "DEBUG %s#%d: "fmt"\n", __FUNCTION__, __LINE__, ##arg);} while(0)
#endif
#define MEBA_I(fmt, arg...) do {if (debug) printk(KERN_INFO "INFO %s#%d: "fmt"\n", __FUNCTION__, __LINE__, ##arg);} while(0)
#define MEBA_W(fmt, arg...) do {if (debug) printk(KERN_WARNING "WARN %s#%d: "fmt"\n", __FUNCTION__, __LINE__, ##arg);} while(0)
#define MEBA_E(fmt, arg...) do {if (debug) printk(KERN_ERR "ERR %s#%d: "fmt"\n", __FUNCTION__, __LINE__, ##arg);} while(0)

// Same defines as in port_custom_api.h
#define VTSS_BOARD_JAGUAR2_AQ_REF 17
static int board_type = VTSS_BOARD_JAGUAR2_AQ_REF;

static int debug = 0;
module_param(board_type, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
// The parameter to used for invoking printk
module_param(debug, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
MODULE_PARM_DESC(board_type, "The board type which must be equal to value in 'Board Type Active' field of 'debug board' debug command");

#define GPIO_SCL_SFP_1   17
#define GPIO_SCL_SFP_2   16

#define VCOREIII_SPI_BUS 0

static struct spi_board_info board_spi_add_info[] = {
    // sync
    {
        .modalias = "spidev",
        .max_speed_hz = 8000000,
        .chip_select = 3,                             // GPIO 18 == SI_nCS3
        .mode = SPI_MODE_0,
    },
};

static struct spi_device *spi_devices[ARRAY_SIZE(board_spi_add_info)];


struct i2c_mux_vcoreiii_entry {
    u8 adp_no;
    u8 value; // It isn't used at this moment, because the i2c devices use different i2c scl.
};

static struct i2c_mux_vcoreiii_entry i2c_mux_entries[] = {
    /*  adp_no,   value */
    {   51,     0  },    // SFP-1
    {   52,     1  },    // SFP-2
};

// Configuration of the GPIOs used in this context
static struct vcoreiii_mux_gpios mux_gpios[] = {
  { GPIO_SCL_SFP_1,   VCOREIII_GPIO_MODE_ALT2, false, 1},
  { GPIO_SCL_SFP_2,   VCOREIII_GPIO_MODE_ALT2, false, 0},
};

// Mapping from channel number to adapter no.
//
static u32 i2c_mux_channel2port(u32 chan)
{
  return MUX_PORT_START + i2c_mux_entries[chan].adp_no;
}

// Function to enable/disable (depending on 'select') the I2C
// channel given by 'chan'.
//
static void i2c_mux_select_channel(struct i2c_adapter *adap, u32 chan, bool select)
{
  static const int chan2gpio[]={
				  GPIO_SCL_SFP_1,
				  GPIO_SCL_SFP_2    };
  MEBA_D("enter");
  if ( !(chan<ARRAY_SIZE(chan2gpio)) ) { /* Error */ return; }
  MEBA_D("%sSELECT chan %d(GPIO-%d)", select ? "" : "DE-", chan, chan2gpio[chan]);
  vcoreiii_gpio_set_value(chan2gpio[chan], select ? 1 : 0);
  udelay(8000); /* Wait for SGPIO to settle */
}

static struct vcoreiii_mux_dd mux_data = {
    .n_channels =  ARRAY_SIZE(i2c_mux_entries),
    .gpios = mux_gpios,
    .n_gpios = ARRAY_SIZE(mux_gpios),
    .select_channel = i2c_mux_select_channel,
    .channel2port = i2c_mux_channel2port,
};

static int vcoreiii_notify_reboot(struct notifier_block *this,
                                  unsigned long code,
                                  void *x)
{
#define SOFT_RESET_GPIO 27
    printk(KERN_ERR "Asserting soft reset\n");
    mdelay(1000);
    vcoreiii_gpio_direction_output(SOFT_RESET_GPIO, true);
    vcoreiii_gpio_set_value(SOFT_RESET_GPIO, false);
    mdelay(200);
    printk(KERN_ERR "Asserting soft reset - done\n");
    return NOTIFY_DONE;
}

static struct notifier_block vcoreiii_notifier = {
    .notifier_call  = vcoreiii_notify_reboot,
    .priority       = 0,
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
  struct spi_master *master; //detect SPI device for DPLL device
  int rc = 0;

  switch (board_type) {
  case VTSS_BOARD_JAGUAR2_AQ_REF:
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
    break;

  default:
    return -EINVAL;
  }

  printk("Register reboot notifier\n");
  register_reboot_notifier(&vcoreiii_notifier);

  return 0;
}

static void meba_cleanup_module(void)
{
  switch (board_type) {
  case VTSS_BOARD_JAGUAR2_AQ_REF:
    meba_i2c_del(&mux_data);
    break;
  }
  printk("Un-register reboot notifier\n");
  unregister_reboot_notifier(&vcoreiii_notifier);
}

module_init(meba_init_module);
module_exit(meba_cleanup_module);

MODULE_AUTHOR("Sgetz Peng <sgetz.peng@microsemi.com>");
MODULE_DESCRIPTION("VCoreIII Board drivers");
MODULE_LICENSE("Dual MIT/GPL");
