// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_API_INTERNAL_H_
#define _VTSS_API_INTERNAL_H_

#include "vtss_api.h"

/* PHY Interrupt status/control - should we share this ? */
#define PHY_INTERRUPT_MASK_REG        25
#define PHY_INTERRUPT_PENDING_REG     26

#define PHY_INT_MASK              0x8000
#define PHY_LINK_MASK             0x2000
#define PHY_FAST_LINK_MASK        0x0080
#define PHY_AMS_MASK              0x0010

#endif /* _VTSS_API_INTERNAL_H_ */
