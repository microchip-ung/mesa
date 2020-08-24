/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#define DEBUG

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/reset.h>
//#include <net/gpy211/gpy211_ops.h>

#include "gpy211_common.h"
#include "gpy211_macsec.h"
#include "gpy211_driver.h"
#include "gpy211_gennl.h"

struct gpy2xx_priv gpy212_data;

void gpy211_macsec_register(struct genl_family *fam)
{
	pr_debug("Entering %s %d\n", __func__, __LINE__);

	/* Make Sure all doit commands have a control here */
	fam->post_doit = gpy211_macsec_postdoit;

	pr_debug("Exiting %s %d\n", __func__, __LINE__);
	return;
}
EXPORT_SYMBOL(gpy211_macsec_register);

#if defined(SUPPORT_GPY2XX_OPS) && SUPPORT_GPY2XX_OPS
/* API to get MACSec operations */
struct gpy211_gphy_ops *gpy211_get_gphy_ops(u32 idx)
{
	if (gpy212_data.pdev[0])
		return platform_get_drvdata(gpy212_data.pdev[0]);

	return NULL;
}
EXPORT_SYMBOL(gpy211_get_gphy_ops);
#endif

/* Data structure for the platform data of "gpy2xx" */
struct gpy2xx_plat_data {
	int (*macsec_init_ing_dev)(struct gpy211_device *ppdata);
	int (*macsec_init_egr_dev)(struct gpy211_device *ppdata);
};

/* "my device" platform gpy2xx_plat_data */
static struct gpy2xx_plat_data gpy2xx_pdata = {
	.macsec_init_ing_dev          = gpy2xx_msec_init_ing_dev,
	.macsec_init_egr_dev          = gpy2xx_msec_init_egr_dev,
};

static struct platform_device gpy2xx_device = {
	.name           = DRIVER_NAME,
	.id             = PLATFORM_DEVID_NONE,
	.dev.platform_data    = &gpy2xx_pdata,
};

static int gpy2xx_driver_probe(struct platform_device *pdev)
{
	int ret;
	struct gpy2xx_plat_data *gpy2xx_pdata = NULL;
	struct gpy2xx_priv_data *driver_data = NULL;
	pr_debug("Entering %s\n", __FUNCTION__);

	memset(&gpy212_data, 0, sizeof(gpy212_data));

	/* Create the driver data here */
	//driver_data = kzalloc(sizeof(struct gpy2xx_priv_data), GFP_KERNEL);
	driver_data = devm_kzalloc(&pdev->dev, sizeof(*driver_data), GFP_KERNEL);

	if (!driver_data)
		return -ENOMEM;

#ifdef DEBUG_PRINT
	//pr_debug("The struct gpy2xx_priv_data resoruce = %pr", driver_data);
	pr_debug("The top allocated gpy2xx_priv_data = %px", driver_data);
	pr_debug("The int allocated gpy211_device = %px", &driver_data->gdev);
#endif
	driver_data->gdev.macsec_data = kzalloc(sizeof(struct gpy211_macsec_data), GFP_KERNEL);

	if (!driver_data->gdev.macsec_data)
		return -ENOMEM;

#ifdef DEBUG_PRINT
	pr_debug("The msec top allocated gpy211_macsec_dev = %px", driver_data->gdev.macsec_data);
#endif
	/* Set this driver data in platform device structure */
	platform_set_drvdata(pdev, driver_data);

	gpy2xx_pdata = dev_get_platdata(&pdev->dev);

	/* Call the class specific register driver here */
	ret = gpy2xx_pdata->macsec_init_ing_dev(&driver_data->gdev);

	if (ret < 0)
		pr_err("MACSec ingress dev init failed\n", __FUNCTION__);

	ret = gpy2xx_pdata->macsec_init_egr_dev(&driver_data->gdev);

	if (ret < 0)
		pr_err("MACSec egress dev init failed\n", __FUNCTION__);

	/* Store it */
	gpy212_data.pdev[0] = pdev;
	//gpy212_data.gpdev[0] = driver_data;

	pr_debug("Exiting %s\n", __FUNCTION__);
	return 0;
}

static int gpy2xx_driver_remove(struct platform_device *pdev)
{
	//struct gpy2xx_priv_data *driver_data;
	pr_debug("Entering %s\n", __FUNCTION__);

	//driver_data =  platform_get_drvdata(pdev);
	//free_netdev(driver_data);

	pr_debug("Exiting %s\n", __FUNCTION__);
	return 0;
}

static struct of_device_id of_gpy2xx_platform_device_match[] = {
	{ .compatible = "gpy2xx", },
	{},
};

MODULE_DEVICE_TABLE(of, of_gpy2xx_platform_device_match);

static struct platform_driver gpy2xx_driver = {
	.probe = gpy2xx_driver_probe,
	.remove = gpy2xx_driver_remove,
	.driver = {
		.name = DRIVER_NAME,
		.of_match_table = of_gpy2xx_platform_device_match,
		.owner = THIS_MODULE,
	},
};

int gpy2xx_module_init(void)
{
	int rc;

	pr_info("Welcome to GPY2XX platform driver.... \n");

	rc = platform_device_register(&gpy2xx_device);

	if (rc < 0)
		pr_err("GPY2XX platform device register failed\n");

	/* Registering with Kernel */
	rc = platform_driver_register(&gpy2xx_driver);

	if (rc < 0)
		pr_err("GPY2XX platform driver register failed\n");

	//platform_driver_probe(&gpy2xx_driver, gpy2xx_driver_probe);

	return 0;
}
module_init(gpy2xx_module_init);

void gpy2xx_module_uninit(void)
{
	pr_info("Thanks....Exiting GPY2XX platform driver... \n");

	/* Unregistering from Kernel */
	platform_driver_unregister(&gpy2xx_driver);

	//gpy2xx_driver_remove(NULL);
	platform_device_unregister(&gpy2xx_device);

	//return 0;
}
module_exit(gpy2xx_module_uninit);

//module_platform_driver(gpy2xx_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Govindaiah Mudepalli");
MODULE_DESCRIPTION("Intel GPY211 PHY driver.");
MODULE_VERSION("0.01");
