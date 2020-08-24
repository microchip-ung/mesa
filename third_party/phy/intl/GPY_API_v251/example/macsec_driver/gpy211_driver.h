/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPY211_DRIVER_H_
#define _GPY211_DRIVER_H_

#include <linux/skbuff.h>
#include <linux/module.h>
#include <net/genetlink.h>
#include <net/sock.h>

#define DRIVER_NAME "gpy2xx"

struct gpy2xx_priv {
	u32 initialized;
	struct platform_device *pdev[1];
	//struct gpy2xx_priv_data *gpdev[1];
};

void gpy211_macsec_postdoit(const struct genl_ops *ops,
			    struct sk_buff *skb,
			    struct genl_info *info);
int gpy211_macsec_changelink(struct net_device *dev,
			     struct nlattr *tb[],
			     struct nlattr *data[]);
int macsec_init(struct net_device *dev, u32 mac_idx);
int macsec_exit(u32 mac_idx);

#endif /* _GPY211_DRIVER_H_ */
