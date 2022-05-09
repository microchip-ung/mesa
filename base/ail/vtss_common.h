// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_COMMON_H_
#define _VTSS_COMMON_H_

#include "vtss_api.h"
#include <vtss_os.h>            /* This defines the *runtime* OS environment */

u32 vtss_cmn_pcp2qos(u32 pcp);
vtss_rc vtss_port_no_check(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_port_no_none_check(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_cmn_restart_update(vtss_state_t *vtss_state, u32 value);
u32 vtss_cmn_restart_value_get(vtss_state_t *vtss_state);

#if defined(VTSS_FEATURE_PORT_CONTROL)  ||  defined(VTSS_FEATURE_VOP)
typedef enum {
    VTSS_COUNTER_CMD_UPDATE, // Update accumulated counter
    VTSS_COUNTER_CMD_CLEAR,  // Clear accumulated counter
    VTSS_COUNTER_CMD_REBASE, // Store latest counter read
} vtss_counter_cmd_t;

void vtss_cmn_counter_8_rebase(u8 new_base_value, vtss_chip_counter_t *counter);
void vtss_cmn_counter_8_update(u8 value, vtss_chip_counter_t *counter, BOOL clear);
void vtss_cmn_counter_16_rebase(u16 new_base_value, vtss_chip_counter_t *counter);
void vtss_cmn_counter_16_update(u16 value, vtss_chip_counter_t *counter, BOOL clear);
void vtss_cmn_counter_32_rebase(u32 new_base_value, vtss_chip_counter_t *counter);
void vtss_cmn_counter_32_update(u32 value, vtss_chip_counter_t *counter, BOOL clear);
void vtss_cmn_counter_32_cmd(u32 value, vtss_chip_counter_t *counter, vtss_counter_cmd_t cmd);
void vtss_cmn_counter_40_rebase(u32 new_lsb, u32 new_msb, vtss_chip_counter_t *counter);
void vtss_cmn_counter_40_update(u32 lsb, u32 msb, vtss_chip_counter_t *counter, BOOL clear);
const char *vtss_serdes_mode_txt(vtss_serdes_mode_t mode);
#endif

const char *vtss_bool_txt(BOOL enabled);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_cmn_debug_info_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
void vtss_debug_print_header_underlined(const vtss_debug_printf_t pr,
                                        const char                *header,
                                        BOOL                      layer);
void vtss_debug_print_header(const vtss_debug_printf_t pr,
                             const char                *header);
void vtss_debug_print_port_header(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const char *txt, u32 count, BOOL nl);
void vtss_debug_print_ports(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u8 *member, BOOL nl);
void vtss_debug_print_port_members(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   BOOL port_member[VTSS_PORT_ARRAY_SIZE],
                                   BOOL nl);
BOOL vtss_debug_group_enabled(const vtss_debug_printf_t pr,
                              const vtss_debug_info_t *const info,
                              const vtss_debug_group_t group);
vtss_rc vtss_debug_print_group(const vtss_debug_group_t group,
                               vtss_rc (* dbg)(vtss_state_t *vtss_state,
                                               const vtss_debug_printf_t pr, 
                                               const vtss_debug_info_t   *const info),
                               vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t *const info);
void vtss_debug_print_sticky(const vtss_debug_printf_t pr, 
                             const char *name, u32 value, u32 offset);
void vtss_debug_print_value(const vtss_debug_printf_t pr, const char *name, u32 value);
void vtss_debug_print_reg_header(const vtss_debug_printf_t pr, const char *name);
void vtss_debug_print_reg(const vtss_debug_printf_t pr, const char *name, u32 value);
#endif // VTSS_OPT_DEBUG_PRINT

vtss_rc vtss_cmn_bit_from_one_hot_mask64(u64 mask, u32 *bit_pos);

vtss_rc srvl_pll5g_read(vtss_state_t *vtss_state, u32 lcpll_mask);
vtss_rc srvl_pll5g_write(vtss_state_t *vtss_state, u32 lcpll_mask, u32 nsec);

#endif /* _VTSS_COMMON_H_ */

