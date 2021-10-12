// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MEBA_GENERIC_H_
#define _MEBA_GENERIC_H_

#include <microchip/ethernet/board/api.h>
#include <vtss_phy_api.h>

/** Phy instance constant */
#define PHY_INST NULL

/** Map instance to board state */
#define INST2BOARD(inst) ((meba_board_state_t*) (inst)->private_data)

// C++ compat
#define true 1
#define false 0

#define MEBA_MAX(x, y) ((x) > (y) ? (x) : (y))
#define MEBA_ARRSZ(x) (sizeof(x) / sizeof(x[0]))

/** Debug */
#define T_R(i, f, ...) i->iface.debug(MEBA_TRACE_LVL_RACKET, __FUNCTION__, __LINE__, f, ##__VA_ARGS__)
#define T_N(i, f, ...) i->iface.debug(MEBA_TRACE_LVL_NOISE, __FUNCTION__, __LINE__, f, ##__VA_ARGS__)
#define T_D(i, f, ...) i->iface.debug(MEBA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, f, ##__VA_ARGS__)
#define T_I(i, f, ...) i->iface.debug(MEBA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, f, ##__VA_ARGS__)
#define T_W(i, f, ...) i->iface.debug(MEBA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, f, ##__VA_ARGS__)
#define T_E(i, f, ...) i->iface.debug(MEBA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, f, ##__VA_ARGS__)

#define MEBA_RC(expr) { mesa_rc __rc__ = (expr); if (__rc__ < MESA_RC_OK) return __rc__; }

// Make sure assert() really asserts
// BEGIN
#if defined(NDEBUG)
#define NDEBUG_WAS_DEFINED
#undef NDEBUG
#endif
#include <assert.h>
#define MEBA_ASSERT(expr) assert(expr)
#if defined(NDEBUG_WAS_DEFINED)
#define NDEBUG
#undef NDEBUG_WAS_DEFINED
#endif
// END

mesa_ptp_event_type_t meba_generic_ptp_source_to_event(meba_inst_t inst,
                                                       meba_event_t event_id);

mepa_ts_event_t meba_generic_phy_ts_source_to_event(meba_inst_t inst, meba_event_t event_id);

mesa_rc meba_generic_ptp_handler(meba_inst_t inst,
                                 meba_event_signal_t interrupt_source_signal);

mesa_rc meba_generic_phy_timestamp_check(meba_inst_t inst,
                                         mesa_port_no_t port_no,
                                         meba_event_signal_t signal_notifier);

mesa_rc meba_generic_phy_event_check(meba_inst_t inst,
                                     mesa_port_no_t port_no,
                                     meba_event_signal_t signal_notifier);


uint32_t meba_get_phy_id(meba_inst_t inst, uint32_t port_no, meba_port_entry_t port_entry);
void meba_phy_driver_init(meba_inst_t inst);

static inline mesa_bool_t has_cap(meba_port_cap_t port_cap,
                                  meba_port_cap_t cap)
{
    return !!(port_cap & cap);
}

static inline mesa_bool_t has_all_cap(meba_port_cap_t port_cap,
                                      meba_port_cap_t cap)
{
    return (port_cap & cap) == cap;
}

static inline mesa_bool_t is_phy_port(meba_port_cap_t port_cap)
{
    return has_cap(port_cap, MEBA_PORT_CAP_COPPER | MEBA_PORT_CAP_DUAL_COPPER);
}

static inline mesa_bool_t is_ams_port(meba_port_cap_t port_cap)
{
    return has_all_cap(port_cap, (MEBA_PORT_CAP_DUAL_SFP_DETECT | MEBA_PORT_CAP_INT_PHY));
}

static inline mesa_bool_t is_phy_internal(meba_port_cap_t port_cap)
{
    return has_cap(port_cap, MEBA_PORT_CAP_INT_PHY);
}

static inline mesa_bool_t is_sfp_port(meba_port_cap_t port_cap)
{
    return has_cap(port_cap, (MEBA_PORT_CAP_SFP_DETECT | MEBA_PORT_CAP_DUAL_SFP_DETECT));
}

static inline mesa_bool_t is_10g_port(meba_port_cap_t port_cap)
{
    return has_cap(port_cap, MEBA_PORT_CAP_10G_FDX);
}

#endif /* _MEBA_GENERIC_H_ */
