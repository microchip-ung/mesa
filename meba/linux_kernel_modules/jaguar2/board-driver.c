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

#include <linux/spi/spi.h>
#include <linux/gpio.h>

#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"

#define VCOREIII_SPI_BUS 0

static DEFINE_MUTEX(mux_mutex);

static inline void do_lock(const char *who)
{
    mutex_lock(&mux_mutex);
    //printk("Lock(%s)\n", who);
}

static inline void do_unlock(const char *who)
{
    //printk("UN-Lock(%s)\n", who);
    mutex_unlock(&mux_mutex);
}

// This should have been exposed in a header file...!
struct dw_spi_chip {
    u8 poll_mode;   /* 1 for controller polling mode */
    u8 type;        /* SPI/SSP/MicroWire */
    void (*cs_control)(u32 command);
};

// Note - the current implementation only allow one specific spi
// device under the MUX. Luckily, it presently seems its all we need.
static void cs_control_cpld0(u32 enable)
{
    if (enable) {
        do_lock("spi");
        vcoreiii_gpio_set_value(51, 0);
        vcoreiii_gpio_set_value(52, 0);
        vcoreiii_gpio_set_value(53, 0);
    } else {
        vcoreiii_gpio_set_value(51, 1);
        vcoreiii_gpio_set_value(52, 1);
        vcoreiii_gpio_set_value(53, 1);
        do_unlock("spi");
    }
}

struct dw_spi_chip spi_cd_muxed_cpld = {
    .cs_control = cs_control_cpld0,
};

static struct spi_board_info board_spi_add_info[] = {
    // sync
    {
        .modalias = "spidev",
        .max_speed_hz = 8000000,
        .chip_select = 1,                             // GPIO 16 == SI_nCS1
        .mode = SPI_MODE_0,
    },
    // CPLD for Synce CPLD
    {
        .modalias = "spidev",
        .max_speed_hz = 8000000,
        .chip_select = 13,                            // GPIO 49 == SI_nCS13
        .mode = SPI_MODE_0,
        .controller_data = &spi_cd_muxed_cpld,        // Use MUX selector
     },
};

static struct spi_device *spi_devices[ARRAY_SIZE(board_spi_add_info)];
// -------------- I2C -------------
struct i2c_mux_vcoreiii_entry {
    u8 port_no;
    u32 gpiomask;
};

#define IMUX_(x)  (1 << x)    // Bits 0-3
#define EMUX(x)   (x << 4)    // Bits 4-6
#define EMUX2_nCS (1 << 7)    // Bits 7-8
#define EMUX1_nCS (2 << 7)    // Bits 7-8
#define X2TYPE    (1 << 9)    // Bit 9
#define EMUX1(x)  (EMUX1_nCS | EMUX(x))
#define EMUX2(x)  (EMUX2_nCS | EMUX(x))
#define IMUX(x)   (EMUX1_nCS | EMUX2_nCS | IMUX_(x))
#define X2MUX     (X2TYPE | EMUX1_nCS | EMUX2_nCS)

static struct i2c_mux_vcoreiii_entry i2c_mux_entries[] = {
    /* port,   gpio mask */
    {     8,   EMUX1(0) },
    {     9,   EMUX1(1) },
    {     10,  EMUX1(2) },
    {     11,  EMUX1(3) },
    {     12,  EMUX1(4) },
    {     13,  EMUX1(5) },
    {     14,  EMUX1(6) },
    {     15,  EMUX1(7) },
    {     16,  EMUX2(0) },
    {     17,  EMUX2(1) },
    {     18,  EMUX2(2) },
    {     19,  EMUX2(3) },
    {     20,  EMUX2(4) },
    {     21,  EMUX2(5) },
    {     22,  EMUX2(6) },
    {     23,  EMUX2(7) },
    // X2 handled specially
    {     24,  X2MUX },
    {     25,  X2MUX },
    {     26,  X2MUX },
    {     27,  X2MUX },
    {     28,  X2MUX },
    {     29,  X2MUX },
    {     30,  X2MUX },
    {     31,  X2MUX },
    // 10G SFP are internal mux. See Table 15 in UG1053
    {     49,  IMUX(0) },
    {     50,  IMUX(1) },
    {     51,  IMUX(2) },
    {     52,  IMUX(3) },
};

static struct vcoreiii_mux_gpios mux_gpios[] = {
    // Internal MUX
    { 17, VCOREIII_GPIO_MODE_ALT2, false, 1 },
    { 18, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 20, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    { 21, VCOREIII_GPIO_MODE_ALT2, false, 0 },
    // I2C For the 16 front SFP ports goes through external multiplexers (gpios 51,52,53,58 and 59). See Table 10 in UG1053
    { 51, VCOREIII_GPIO_MODE_NORMAL, true, 0 },
    { 52, VCOREIII_GPIO_MODE_NORMAL, true, 0 },
    { 53, VCOREIII_GPIO_MODE_NORMAL, true, 0 },
    // eMUX nCS 1+2
    { 58, VCOREIII_GPIO_MODE_NORMAL, true, 0 },
    { 59, VCOREIII_GPIO_MODE_NORMAL, true, 1 },
};

static void i2c_mux_select_channel(struct i2c_adapter *adap, u32 chan, bool select)
{
    if (select) {
        do_lock("i2c");
    }
    if (select) {
        int i;
        u32 value = i2c_mux_entries[chan].gpiomask;
        for (i = 0; i < ARRAY_SIZE(mux_gpios); i++, value >>= 1) {
            bool enb = (value & 1);
            vcoreiii_gpio_set_value(mux_gpios[i].gpio, enb);
            //pr_err("GPIO %d: %s (value 0x%02x)\n", mux_gpios[i].gpio, enb ? "ON " : "OFF", value);
        }
#if 0
        pr_err("mux: MASK = 0x%08x\n", VTSS_BIT(59-32)|VTSS_BIT(58-32)|VTSS_BIT(53-32)|VTSS_BIT(52-32)|VTSS_BIT(51-32));
        pr_err("mux: OE1  = 0x%08x\n", readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OE1));
        pr_err("mux: OUT1 = 0x%08x\n", readl(VTSS_DEVCPU_GCB_GPIO_GPIO_OUT1));
        pr_err("mux: ALT1(0) = 0x%08x\n", readl(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT1(0)));
        pr_err("mux: ALT1(1) = 0x%08x\n", readl(VTSS_DEVCPU_GCB_GPIO_GPIO_ALT1(1)));
#endif
    }
    // NOTE: Runs for both select and deselect!
    if (i2c_mux_entries[chan].gpiomask & X2TYPE) {
        int port = i2c_mux_entries[chan].port_no;
        u8 addr, val;
        struct i2c_msg msg;
        char buf[1];
        addr = 0x70 + ((port - 24) / 4);    // 0x70 or 0x71
        val =  select ? 1 << ((port - 24) % 4) : 0; // 1 << (0,1,2,3) or zero (deselected)
        //pr_err("mux: X2 %02x data %02x\n", addr, val);
        // Now write to the PCA954x
        msg.addr = addr;
        msg.flags = 0;
        msg.len = 1;
        buf[0] = val;
        msg.buf = buf;
        (void) __i2c_transfer(adap, &msg, 1);
    }
    if (!select) {
        do_unlock("i2c");
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
    { .adp_no = 152, I2C_BOARD_INFO("malibu_silabs",0x70), }, // On external PHY
    { .adp_no = 0, I2C_BOARD_INFO("ZL30251",0x6e), }, // On main bus segment
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
    int rc = 0, i;

    // Reserve CS1 (SyncE feature connector)
    vcoreiii_gpio_set_mode(16, VCOREIII_GPIO_MODE_ALT1);
    // CS > 3 are actually controlled as GPIO's - setup on the fly

    // Extended SPI chip selects - GPIO 51,52,53
    for (i = 51; i <= 53; i++) {
        vcoreiii_gpio_set_mode(i, VCOREIII_GPIO_MODE_NORMAL);
        vcoreiii_gpio_direction_output(i, 0);
    }

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
