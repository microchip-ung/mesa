// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <vtss_api.h>
#include <mesa.h>

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv2_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(
    const vtss_phy_ts_eth_flow_conf_t *in,
    mesa_phy_ts_eth_flow_conf_t       *out)
{
    out->outer_tag.value.val = in->outer_tag.value.val;
    out->outer_tag.value.mask = in->outer_tag.value.mask;
    out->inner_tag.i_tag.val = in->inner_tag.i_tag.val;
    out->inner_tag.i_tag.mask = in->inner_tag.i_tag.mask;
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(
    const mesa_phy_ts_eth_flow_conf_t *in,
    vtss_phy_ts_eth_flow_conf_t       *out)
{
    out->outer_tag.value.val = in->outer_tag.value.val;
    out->outer_tag.value.mask = in->outer_tag.value.mask;
    out->inner_tag.i_tag.val = in->inner_tag.i_tag.val;
    out->inner_tag.i_tag.mask = in->inner_tag.i_tag.mask;
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(
    const vtss_phy_ts_ip_flow_conf_t *in,
    mesa_phy_ts_ip_flow_conf_t       *out)
{
    for (int i = 0; i < 4; i++) {
        out->ip_addr.ipv6.addr[i] = in->ip_addr.ipv6.addr[i];
        out->ip_addr.ipv6.mask[i] = in->ip_addr.ipv6.mask[i];
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(
    const mesa_phy_ts_ip_flow_conf_t *in,
    vtss_phy_ts_ip_flow_conf_t       *out)
{
    for (int i = 0; i < 4; i++) {
        out->ip_addr.ipv6.addr[i] = in->ip_addr.ipv6.addr[i];
        out->ip_addr.ipv6.mask[i] = in->ip_addr.ipv6.mask[i];
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(
    const vtss_phy_ts_mpls_flow_conf_t *in,
    mesa_phy_ts_mpls_flow_conf_t       *out)
{
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.top,
                                                                       &out->stack_level.top_down
                                                                            .top);
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down
                                                                            .frst_lvl_after_top,
                                                                       &out->stack_level.top_down
                                                                            .frst_lvl_after_top);
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down
                                                                            .snd_lvl_after_top,
                                                                       &out->stack_level.top_down
                                                                            .snd_lvl_after_top);
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down
                                                                            .thrd_lvl_after_top,
                                                                       &out->stack_level.top_down
                                                                            .thrd_lvl_after_top);
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(
    const mesa_phy_ts_mpls_flow_conf_t *in,
    vtss_phy_ts_mpls_flow_conf_t       *out)
{
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.top,
                                                                       &out->stack_level.top_down
                                                                            .top);
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down
                                                                            .frst_lvl_after_top,
                                                                       &out->stack_level.top_down
                                                                            .frst_lvl_after_top);
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down
                                                                            .snd_lvl_after_top,
                                                                       &out->stack_level.top_down
                                                                            .snd_lvl_after_top);
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down
                                                                            .thrd_lvl_after_top,
                                                                       &out->stack_level.top_down
                                                                            .thrd_lvl_after_top);
    return VTSS_RC_OK;
}
#endif // defined(VTSS_OPT_PHY_TIMESTAMP)
