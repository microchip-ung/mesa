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

#include <linux/device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>
#include <linux/delay.h>

#define DEVICE_NAME "jaguar2"

#define PCIE_VENDOR_ID 0x101B
#define PCIE_DEVICE_JR2_ID 0xB003
#define PCIE_DEVICE_SERVALT_ID 0xB004

struct uio_jaguar2 {
    struct uio_info uio;
    /* Private data */
    spinlock_t lock;
    unsigned long flags;
    struct pci_dev *pdev;
};

static irqreturn_t jaguar2_handler(int irq, struct uio_info *dev_info)
{
    struct uio_jaguar2 *priv = dev_info->priv;

    //printk("Jaguar2: Got IRQ, disabling\n");

    if (!test_and_set_bit(0, &priv->flags))
        disable_irq_nosync(irq);

    return IRQ_HANDLED;
}

static int jaguar2_irqcontrol(struct uio_info *dev_info, s32 irq_on)
{
    struct uio_jaguar2 *priv = dev_info->priv;
    unsigned long flags;

    spin_lock_irqsave(&priv->lock, flags);
    if (irq_on) {
        if (test_and_clear_bit(0, &priv->flags)) {
            //printk("Jaguar2: Enable IRQ\n");
            enable_irq(dev_info->irq);
        }
    } else {
        if (!test_and_set_bit(0, &priv->flags)) {
            //printk("Jaguar2: Disable IRQ\n");
            disable_irq(dev_info->irq);
        }
    }
    spin_unlock_irqrestore(&priv->lock, flags);

    return 0;
}

static int jaguar2_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
    struct uio_jaguar2 *priv;
    struct uio_info *info;
    void __iomem *chipid_reg;

    priv = kzalloc(sizeof(struct uio_jaguar2), GFP_KERNEL);
    if (!priv)
        return -ENOMEM;
    info = &priv->uio;
    info->priv = priv;

    if (pci_enable_device(dev))
        goto out_free;

    if (pci_request_regions(dev, DEVICE_NAME))
        goto out_disable;

    /* BAR0 = registers, BAR1 = CONFIG, BAR2 = DDR (unused) */
    info->mem[0].addr = pci_resource_start(dev, 0);
    if (!info->mem[0].addr)
        goto out_release;
    info->mem[0].size = pci_resource_len(dev, 0);
    info->mem[0].memtype = UIO_MEM_PHYS;
    info->mem[0].internal_addr = ioremap(info->mem[0].addr, info->mem[0].size);

#if 1
    info->mem[1].addr = pci_resource_start(dev, 1);
    if (!info->mem[1].addr)
        goto out_release;
    info->mem[1].size = pci_resource_len(dev, 1);
    info->mem[1].memtype = UIO_MEM_PHYS;
#endif

    info->name = "Jaguar2 RefBoard";
    info->version = "1.0.0";
    info->irq = dev->irq;
    info->handler = jaguar2_handler;
    info->irqcontrol = jaguar2_irqcontrol;

    spin_lock_init(&priv->lock);
    priv->flags = 0; /* interrupt is enabled to begin with */
    priv->pdev = dev;

    if (uio_register_device(&dev->dev, info))
        goto out_unmap;

    pci_set_drvdata(dev, info);
    chipid_reg = info->mem[0].internal_addr + (0x01010000);
    dev_info(&dev->dev, "Found %s, UIO device - IRQ %ld, id 0x%08x.\n", info->name, info->irq, ioread32(chipid_reg));

    return 0;

out_unmap:
    iounmap(info->mem[0].internal_addr);
out_release:
    pci_release_regions(dev);
out_disable:
    pci_disable_device(dev);
out_free:
    kfree(info);
    return -ENODEV;
}


static void jaguar2_pci_remove(struct pci_dev *dev)
{
    struct uio_info *info = pci_get_drvdata(dev);

    uio_unregister_device(info);
    iounmap(info->mem[0].internal_addr);
    pci_release_regions(dev);
    pci_disable_device(dev);
    pci_set_drvdata(dev, NULL);

    kfree(info->priv);
}

static struct pci_device_id jaguar2_pci_ids[] = {
    {
        .vendor =    PCIE_VENDOR_ID,
        .device =    PCIE_DEVICE_JR2_ID,
        .subvendor = PCI_ANY_ID,
        .subdevice = PCI_ANY_ID,
    },
    {
        .vendor =    PCIE_VENDOR_ID,
        .device =    PCIE_DEVICE_SERVALT_ID,
        .subvendor = PCI_ANY_ID,
        .subdevice = PCI_ANY_ID,
    },
    { 0, }
};

static struct pci_driver jaguar2_pci_driver = {
    .name = DEVICE_NAME,
    .id_table = jaguar2_pci_ids,
    .probe = jaguar2_pci_probe,
    .remove = jaguar2_pci_remove,
};

static int __init jaguar2_init_module(void)
{
    return pci_register_driver(&jaguar2_pci_driver);
}

static void __exit jaguar2_exit_module(void)
{
    pci_unregister_driver(&jaguar2_pci_driver);
}

module_init(jaguar2_init_module);
module_exit(jaguar2_exit_module);

MODULE_DEVICE_TABLE(pci, jaguar2_pci_ids);
MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Lars Povlsen <lpovlsen@vitesse.com>");
