// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdarg.h>
#include <vtss_api.h>
#include <mesa.h>

mesa_rc mesa_conv_vtss_symreg_data_t_to_mesa_symreg_data_t(const vtss_symreg_data_t *in,
                                                           mesa_symreg_data_t       *out)
{
#ifdef __cplusplus
    static_assert(sizeof(vtss_symreg_data_t) == sizeof(mesa_symreg_data_t), "Check size");
    static_assert(sizeof(vtss_symreg_target_t) == sizeof(mesa_symreg_target_t), "Check size");
#endif
    const mesa_symreg_data_t *d = (const mesa_symreg_data_t *)in;
    *out = *d;
    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_symreg_data_t_to_vtss_symreg_data_t(const mesa_symreg_data_t *in,
                                                           vtss_symreg_data_t       *out)
{
#ifdef __cplusplus
    static_assert(sizeof(vtss_symreg_data_t) == sizeof(mesa_symreg_data_t), "Check size");
    static_assert(sizeof(vtss_symreg_target_t) == sizeof(mesa_symreg_target_t), "Check size");
#endif
    const vtss_symreg_data_t *d = (const vtss_symreg_data_t *)in;
    *out = *d;
    return VTSS_RC_OK;
}

mesa_rc mesa_sgpio_read(const mesa_inst_t        inst,
                        const mesa_chip_no_t     chip_no,
                        const mesa_sgpio_group_t group,
                        mesa_sgpio_port_data_t   data[MESA_SGPIO_PORTS])
{
#if defined(VTSS_FEATURE_SERIAL_GPIO)
    mesa_rc                rc;
    vtss_sgpio_port_data_t vtss_data[VTSS_SGPIO_PORTS];
    uint32_t               port;

    if ((rc = vtss_sgpio_read((const vtss_inst_t)inst, chip_no, group, vtss_data)) == VTSS_RC_OK) {
        for (port = 0; port < VTSS_SGPIO_PORTS; port++) {
            mesa_conv_vtss_sgpio_port_data_t_to_mesa_sgpio_port_data_t(&vtss_data[port],
                                                                       &data[port]);
        }
    }
    return rc;
#else
    return VTSS_RC_OK;
#endif
}

mesa_rc mesa_fan_rotation_get(const mesa_inst_t inst, uint32_t *rotation_count)
{
#if defined(VTSS_FEATURE_FAN)
    vtss_fan_conf_t fan_conf = {}; // Dummy argument
    return vtss_fan_rotation_get((vtss_inst_t)inst, &fan_conf, rotation_count);
#else
    return VTSS_RC_ERROR;
#endif
}

void vtss_callout_trace_printf(const vtss_trace_layer_t layer,
                               const vtss_trace_group_t group,
                               const vtss_trace_level_t level,
                               const char              *file,
                               const int                line,
                               const char              *function,
                               const char              *format,
                               ...)
{
    va_list            args;
    mesa_trace_layer_t m_layer = 0;
    mesa_trace_group_t m_group = 0;
    mesa_trace_level_t m_level = 0;

    mesa_conv_vtss_trace_layer_t_to_mesa_trace_layer_t(&layer, &m_layer);
    mesa_conv_vtss_trace_group_t_to_mesa_trace_group_t(&group, &m_group);
    mesa_conv_vtss_trace_level_t_to_mesa_trace_level_t(&level, &m_level);
    va_start(args, format);
    mesa_callout_trace_printf(m_layer, m_group, m_level, file, line, function, format, args);
    va_end(args);
}

void vtss_callout_trace_hex_dump(const vtss_trace_layer_t layer,
                                 const vtss_trace_group_t group,
                                 const vtss_trace_level_t level,
                                 const char              *file,
                                 const int                line,
                                 const char              *function,
                                 const u8                *byte_p,
                                 const int                byte_cnt)
{
    mesa_trace_layer_t m_layer;
    mesa_trace_group_t m_group;
    mesa_trace_level_t m_level;

    mesa_conv_vtss_trace_layer_t_to_mesa_trace_layer_t(&layer, &m_layer);
    mesa_conv_vtss_trace_group_t_to_mesa_trace_group_t(&group, &m_group);
    mesa_conv_vtss_trace_level_t_to_mesa_trace_level_t(&level, &m_level);
    mesa_callout_trace_hex_dump(m_layer, m_group, m_level, file, line, function, byte_p, byte_cnt);
}

void vtss_callout_lock(const vtss_api_lock_t *const lock)
{
    mesa_callout_lock((const mesa_api_lock_t *)lock);
}

void vtss_callout_unlock(const vtss_api_lock_t *const lock)
{
    mesa_callout_unlock((const mesa_api_lock_t *)lock);
}
