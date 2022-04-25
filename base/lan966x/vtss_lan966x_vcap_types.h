// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAN966X_VCAP_TYPES_H_
#define _VTSS_LAN966X_VCAP_TYPES_H_

#include "vtss/api/types.h"
#include "vtss_api.h"

enum vtss_lan966x_vcap_instance {
    VTSS_LAN966X_VCAP_INSTANCE_ES0,
    VTSS_LAN966X_VCAP_INSTANCE_IS1,
    VTSS_LAN966X_VCAP_INSTANCE_IS2
};

enum vtss_lan966x_vcap_version {
    VTSS_LAN966X_VCAP_VERSION_1,
    VTSS_LAN966X_VCAP_VERSION_2
};

#define vtss_lan966x_vcap_bit vtss_vcap_bit
#define VTSS_LAN966X_VCAP_BIT_ANY VTSS_VCAP_BIT_ANY
#define VTSS_LAN966X_VCAP_BIT_0 VTSS_VCAP_BIT_0
#define VTSS_LAN966X_VCAP_BIT_1 VTSS_VCAP_BIT_1

struct vtss_lan966x_vcap_u8 {
    u8 value;
    u8 mask;
};

struct vtss_lan966x_vcap_u16 {
    u16 value;
    u16 mask;
};

struct vtss_lan966x_vcap_u32 {
    u32 value;
    u32 mask;
};

struct vtss_lan966x_vcap_u48 {
    u8 value[6];
    u8 mask[6];
};

struct vtss_lan966x_vcap_u56 {
    u8 value[7];
    u8 mask[7];
};

struct vtss_lan966x_vcap_u64 {
    u8 value[8];
    u8 mask[8];
};

struct vtss_lan966x_vcap_u112 {
    u8 value[14];
    u8 mask[14];
};

struct vtss_lan966x_vcap_u128 {
    u8 value[16];
    u8 mask[16];
};

#define LAN966X_VCAP_MAX_ENTRY_WIDTH 12 /* Max entry width (32bit words) */
#define LAN966X_VCAP_MAX_ACTION_WIDTH 12 /* Max action width (32bit words) */
#define LAN966X_VCAP_MAX_COUNTER_WIDTH 4 /* Max counter width (32bit words) */

struct vtss_lan966x_vcap_data {
    u32 entry[LAN966X_VCAP_MAX_ENTRY_WIDTH]; /* ENTRY_DAT */
    u32 mask[LAN966X_VCAP_MAX_ENTRY_WIDTH]; /* MASK_DAT */
    u32 action[LAN966X_VCAP_MAX_ACTION_WIDTH]; /* ACTION_DAT */
    u32 counter[LAN966X_VCAP_MAX_COUNTER_WIDTH]; /* CNT_DAT */
    u32 tg; /* TG_DAT */
    u32 action_type; /* Current action type */
    u32 key_offset; /* Current entry offset */
    u32 action_offset; /* Current action offset */
    u32 counter_offset; /* Current counter offset */
    u32 tg_value; /* Current type-group value */
    u32 tg_mask; /* Current type-group mask */
};

#endif /* _VTSS_LAN966X_VCAP_TYPES_H_ */
