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
#include <linux/spi/spi_vcoreiii.h>
#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"


// -------------- I2C -------------

struct i2c_mux_vcoreiii_entry {
    u8 port_no;    // Chip port
    u32 gpio_mask; // GPIO mux to enable I2C for that port
};

#define IMUX(x)  (1 << x)              // Internal mux index 0-11
#define EMUX_CS  (1 << 15)             // External Mux Enable
#define EMUX(x)  ((x << 12) | EMUX_CS) // External 3 x mux-sel @ index 12 -> 8 SPFs

struct i2c_mux_vcoreiii_entry i2c_mux_entries[] = {
//chip_port gpio_mask
    // Internal
    { 12,  IMUX(0) },
    { 13,  IMUX(1) },
    { 14,  IMUX(2) },
    { 15,  IMUX(3) },
    { 16,  IMUX(4) },
    { 17,  IMUX(5) },
    { 18,  IMUX(6) },
    { 19,  IMUX(7) },
    { 20,  IMUX(8) },
    { 21,  IMUX(9) },
    { 22,  IMUX(10) },
    { 23,  IMUX(11) },
    // External mux
    { 56,  EMUX(0) },
    { 57,  EMUX(1) },
    { 58,  EMUX(2) },
    { 59,  EMUX(3) },
    { 60,  EMUX(4) },
    { 61,  EMUX(5) },
    { 62,  EMUX(6) },
    { 63,  EMUX(7) },
};

static struct vcoreiii_mux_gpios mux_gpios[] = {
    // 10G ports D12-D23 use internal MUX
    { 16, VCOREIII_GPIO_MODE_ALT2, false, 1 },
    { 17, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 18, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 19, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 20, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 22, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 35, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 36, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 50, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 51, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 52, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    { 53, VCOREIII_GPIO_MODE_ALT3, false, 0 },
    // 25G ports D56-D63 use external MUX
    { 55, VCOREIII_GPIO_MODE_NORMAL, false, 0 },
    { 60, VCOREIII_GPIO_MODE_NORMAL, false, 0 },
    { 61, VCOREIII_GPIO_MODE_NORMAL, false, 0 },
    // External MUX enable 
    { 54, VCOREIII_GPIO_MODE_NORMAL, false, 0 },

};

static void i2c_mux_select_channel(struct i2c_adapter *adap, u32 chan, bool select)
{
    if (select) {
        int i;
        u32 value = i2c_mux_entries[chan].gpio_mask;
        u32 port = i2c_mux_entries[chan].port_no;
        for (i = 0; i < ARRAY_SIZE(mux_gpios); i++, value >>= 1) {
            bool enb = (value & 1);
//            vcoreiii_gpio_set_value(mux_gpios[i].gpio, enb);
            printk(KERN_INFO "Chip port:%d: GPIO %d: %s (value 0x%02x)\n",port, mux_gpios[i].gpio, enb ? "ON " : "OFF", value);
        }
    }
    
#if 0
    printk(KERN_ERR "mux: Set GPIO %d, OE = 0x%08x OUT = 0x%08x, OE1 = 0x%08x OUT1 = 0x%08x\n",
           entry->gpio,
           readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OE),
           readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT),
           readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OE1),
           readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT1));
#endif
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

// -------------- BSP-----------

static int meba_init_module(void)
{
    meba_i2c_add(&mux_data, 0);
    return 0;
}

static void meba_cleanup_module(void)
{
    meba_i2c_del(&mux_data);
}

module_init(meba_init_module);
module_exit(meba_cleanup_module);

MODULE_AUTHOR("Bjarni Jonasson <bjarni.jonasson@microchip.com>");
MODULE_DESCRIPTION("VCoreXXX Board drivers");
MODULE_LICENSE("Dual MIT/GPL");
