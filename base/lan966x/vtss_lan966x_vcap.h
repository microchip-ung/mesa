// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef VTSS_LAN966X_VCAP_H
#define VTSS_LAN966X_VCAP_H

#include "vtss_lan966x_cil.h"

void vtss_lan966x_vcap_key_set(struct vtss_lan966x_vcap_data *data,
                               u32                            offset,
                               u32                            width,
                               u32                            value,
                               u32                            mask);

void vtss_lan966x_vcap_key_bytes_set(struct vtss_lan966x_vcap_data *data,
                                     u32                            offset,
                                     const u8                      *val,
                                     const u8                      *msk,
                                     u32                            count);

void vtss_lan966x_vcap_key_bit_set(struct vtss_lan966x_vcap_data *data,
                                   u32                            offset,
                                   enum vtss_lan966x_vcap_bit     val);

void vtss_lan966x_vcap_action_set(struct vtss_lan966x_vcap_data *data,
                                  u32                            offset,
                                  u32                            width,
                                  u32                            value);

void vtss_lan966x_vcap_action_bit_set(struct vtss_lan966x_vcap_data *data, u32 offset, u32 value);

#endif /* VTSS_LAN966X_VCAP_H */
