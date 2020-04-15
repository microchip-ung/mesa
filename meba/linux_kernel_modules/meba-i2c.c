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

#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <asm/vcoreiii.h>
#include <asm/vcoreiii-gpio.h>

#include "meba-i2c.h"

typedef struct vcoreiii_mux_priv {
    struct device *dev;
    struct i2c_adapter *parent;    // Grandpa
    struct i2c_mux_core *muxc;
    struct vcoreiii_mux_dd dd;
} vcoreiii_mux_priv_t;

static int i2c_mux_init(vcoreiii_mux_priv_t *vc3mux)
{
    int i;
    for (i = 0; i < vc3mux->dd.n_gpios; i++) {
        const struct vcoreiii_mux_gpios *ent = &vc3mux->dd.gpios[i];
        vcoreiii_gpio_set_mode(ent->gpio, ent->mode);
        gpio_request(ent->gpio, NULL);
        if(ent->output) {
            vcoreiii_gpio_direction_output(ent->gpio, ent->initial_value);
        } else {
            vcoreiii_gpio_set_value(ent->gpio, ent->initial_value);
        }
    }
    return 0;
}

static int i2c_mux_vcoreiii_select(struct i2c_mux_core *muxc, u32 chan)
{
    vcoreiii_mux_priv_t *vc3mux = i2c_mux_priv(muxc);
    vc3mux->dd.select_channel(vc3mux->parent, chan, true);
    return 0;
}

static int i2c_mux_vcoreiii_deselect(struct i2c_mux_core *muxc, u32 chan)
{
    vcoreiii_mux_priv_t *vc3mux = i2c_mux_priv(muxc);
    vc3mux->dd.select_channel(vc3mux->parent, chan, false);
    return 0;
}

int meba_i2c_add(struct vcoreiii_mux_dd *mux, int i2c_parent)
{
    struct i2c_adapter *parent;
    struct i2c_mux_core *muxc;
    vcoreiii_mux_priv_t *priv;
    int i, err;

    parent = i2c_get_adapter(i2c_parent);
    if (!parent) {
        printk("Parent adapter (%d) not found\n", i2c_parent);
        return -EPROBE_DEFER;
    }

    muxc = i2c_mux_alloc(parent, &parent->dev,
                         mux->n_channels,
                         sizeof(vcoreiii_mux_priv_t), 0,
                         i2c_mux_vcoreiii_select, i2c_mux_vcoreiii_deselect);
    if (!muxc) {
        printk("Cannot allocate i2c_adapter structure");
        err = -ENOMEM;
        goto mux_dd_err_put;
    }

    priv = i2c_mux_priv(muxc);
    priv->parent = parent;
    priv->muxc = muxc;
    priv->dd = *mux;

    for (i = 0; i < mux->n_channels; i++) {
        err = i2c_mux_add_adapter(muxc, mux->channel2port(i), i, 0);
        if (err) {
            dev_err(muxc->dev, "Failed to add adapter %d\n", i);
            printk("Failed to add adapter %d\n", i);
            goto add_adapter_failed;
        }
    }

    // Initialize state
    i2c_mux_init(priv);

    // Backpatch
    mux->priv = priv;

    return 0;

add_adapter_failed:    
    i2c_mux_del_adapters(muxc);

mux_dd_err_put:
    i2c_put_adapter(parent);

    return err;
}

void meba_i2c_del(struct vcoreiii_mux_dd *mux)
{
    vcoreiii_mux_priv_t *priv = mux->priv;
    struct i2c_mux_core *muxc = priv->muxc;
    i2c_mux_del_adapters(muxc);
    i2c_put_adapter(muxc->parent);
}

int  meba_i2c_add_devices(const struct vcoreiii_i2c_device *devices, struct i2c_client **clients, size_t n_devices)
{
    int i, added;
    struct i2c_board_info i2c_info = { };

    for (i = 0; i < n_devices; i++) {
        struct i2c_adapter *i2c_adap;
        strncpy(i2c_info.type, devices[i].type, sizeof(i2c_info.type));
        i2c_info.addr = devices[i].addr;
        if ((i2c_adap = i2c_get_adapter(devices[i].adp_no))) {
            if ((clients[i] = i2c_new_device(i2c_adap, &i2c_info))) {
                added++;
            } else {
                printk(KERN_ERR "Unable to add i2c-%d device(\"%s\",0x%x)\n", 
                       devices[i].adp_no, devices[i].type, devices[i].addr);
            }
            i2c_put_adapter(i2c_adap);
        } else {
            printk(KERN_ERR "Unable to find i2c bus: i2c-%d\n", devices[i].adp_no);
        }
    }
    return added;
}

void meba_i2c_del_devices(struct i2c_client **clients, size_t n_devices)
{
    int i;
    for (i = 0; i < n_devices; i++) {
        if (clients[i]) {
            i2c_unregister_device(clients[i]);
        }
    }
}
