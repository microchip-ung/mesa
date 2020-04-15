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

#include <linux/i2c.h>
#include <linux/i2c-mux.h>

#define MUX_PORT_START   100  // Port mux device offset

struct vcoreiii_mux_gpios {
    u8 gpio;
    u8 mode;
    bool output;
    u8 initial_value;
};

struct vcoreiii_mux_dd {
    struct vcoreiii_mux_priv *priv;

    u32    n_channels;
    const struct vcoreiii_mux_gpios *gpios;
    size_t n_gpios;
    // Callouts
    void (*select_channel)(struct i2c_adapter *, u32, bool);
    u32 (*channel2port)(u32);
};

int  meba_i2c_add(struct vcoreiii_mux_dd *mux, int i2c_parent);
void meba_i2c_del(struct vcoreiii_mux_dd *mux);

struct vcoreiii_i2c_device {
    unsigned short adp_no;
    unsigned short addr;
    const char *type;
};

int  meba_i2c_add_devices(const struct vcoreiii_i2c_device *devices, struct i2c_client **clients, size_t n_devices);
void meba_i2c_del_devices(struct i2c_client **clients, size_t n_devices);
