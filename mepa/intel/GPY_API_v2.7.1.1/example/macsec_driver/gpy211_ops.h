/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPY211_OPS_H_
#define _GPY211_OPS_H_

#ifdef __KERNEL__
//#include <linux/rtnetlink.h>
#include <linux/netlink.h>
//#include <linux/etherdevice.h>
#include <net/net_namespace.h>
#include <net/genetlink.h>
//#include <net/sock.h>
#endif

enum {
	MACSEC_INIT_ING_DEV,
	MACSEC_INIT_EGR_DEV,
};

struct gpy211_gphy_ops {
	/* Initialize Macsec Ingress device
	 */
	int(*macsec_init_ing_dev)(void *);
	/* Initialize Macsec Egress device
	 */
	int(*(*macsec_init_egr_dev))(void *);
};

struct gpy211_gphy_ops *gpy211_get_gphy_ops(u32 idx);

#ifdef __KERNEL__
void gpy211_macsec_register(struct genl_family *fam);
#endif

#endif /* _GPY211_OPS_H_ */
