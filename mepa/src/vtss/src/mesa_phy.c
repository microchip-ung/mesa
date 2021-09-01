// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "mesa_phy.h"

#define __RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wformat-security"
mesa_rc mesa_conv_vtss_phy_power_mode_t_to_mesa_phy_power_mode_t(const vtss_phy_power_mode_t *in, mesa_phy_power_mode_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        case VTSS_PHY_POWER_NOMINAL:
            *out = MESA_PHY_POWER_NOMINAL;
            return VTSS_RC_OK;
        case VTSS_PHY_POWER_ACTIPHY:
            *out = MESA_PHY_POWER_ACTIPHY;
            return VTSS_RC_OK;
        case VTSS_PHY_POWER_DYNAMIC:
            *out = MESA_PHY_POWER_DYNAMIC;
            return VTSS_RC_OK;
        case VTSS_PHY_POWER_ENABLED:
            *out = MESA_PHY_POWER_ENABLED;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_phy_power_mode_t_to_vtss_phy_power_mode_t(const mesa_phy_power_mode_t *in, vtss_phy_power_mode_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        case MESA_PHY_POWER_NOMINAL:
            *out = VTSS_PHY_POWER_NOMINAL;
            return VTSS_RC_OK;
        case MESA_PHY_POWER_ACTIPHY:
            *out = VTSS_PHY_POWER_ACTIPHY;
            return VTSS_RC_OK;
        case MESA_PHY_POWER_DYNAMIC:
            *out = VTSS_PHY_POWER_DYNAMIC;
            return VTSS_RC_OK;
        case MESA_PHY_POWER_ENABLED:
            *out = VTSS_PHY_POWER_ENABLED;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_vtss_port_interface_t_to_mesa_port_interface_t(const vtss_port_interface_t *in, mesa_port_interface_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        // skipped: VTSS_PORT_INTERFACE_CPU
        case VTSS_PORT_INTERFACE_NO_CONNECTION:
            *out = MESA_PORT_INTERFACE_NO_CONNECTION;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_LOOPBACK:
            *out = MESA_PORT_INTERFACE_LOOPBACK;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_INTERNAL:
            *out = MESA_PORT_INTERFACE_INTERNAL;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_MII:
            *out = MESA_PORT_INTERFACE_MII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_GMII:
            *out = MESA_PORT_INTERFACE_GMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_RGMII:
            *out = MESA_PORT_INTERFACE_RGMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_TBI:
            *out = MESA_PORT_INTERFACE_TBI;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_RTBI:
            *out = MESA_PORT_INTERFACE_RTBI;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_SGMII:
            *out = MESA_PORT_INTERFACE_SGMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_SGMII_2G5:
            *out = MESA_PORT_INTERFACE_SGMII_2G5;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_SGMII_CISCO:
            *out = MESA_PORT_INTERFACE_SGMII_CISCO;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_SERDES:
            *out = MESA_PORT_INTERFACE_SERDES;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_VAUI:
            *out = MESA_PORT_INTERFACE_VAUI;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_100FX:
            *out = MESA_PORT_INTERFACE_100FX;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_XAUI:
            *out = MESA_PORT_INTERFACE_XAUI;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_RXAUI:
            *out = MESA_PORT_INTERFACE_RXAUI;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_XGMII:
            *out = MESA_PORT_INTERFACE_XGMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_SPI4:
            *out = MESA_PORT_INTERFACE_SPI4;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_QSGMII:
            *out = MESA_PORT_INTERFACE_QSGMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_SFI:
            *out = MESA_PORT_INTERFACE_SFI;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_SXGMII:
            *out = MESA_PORT_INTERFACE_SXGMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_USGMII:
            *out = MESA_PORT_INTERFACE_USGMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_QXGMII:
            *out = MESA_PORT_INTERFACE_QXGMII;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_DXGMII_5G:
            *out = MESA_PORT_INTERFACE_DXGMII_5G;
            return VTSS_RC_OK;
        case VTSS_PORT_INTERFACE_DXGMII_10G:
            *out = MESA_PORT_INTERFACE_DXGMII_10G;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_port_interface_t_to_vtss_port_interface_t(const mesa_port_interface_t *in, vtss_port_interface_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        // skipped: VTSS_PORT_INTERFACE_CPU
        case MESA_PORT_INTERFACE_NO_CONNECTION:
            *out = VTSS_PORT_INTERFACE_NO_CONNECTION;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_LOOPBACK:
            *out = VTSS_PORT_INTERFACE_LOOPBACK;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_INTERNAL:
            *out = VTSS_PORT_INTERFACE_INTERNAL;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_MII:
            *out = VTSS_PORT_INTERFACE_MII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_GMII:
            *out = VTSS_PORT_INTERFACE_GMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_RGMII:
            *out = VTSS_PORT_INTERFACE_RGMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_TBI:
            *out = VTSS_PORT_INTERFACE_TBI;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_RTBI:
            *out = VTSS_PORT_INTERFACE_RTBI;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_SGMII:
            *out = VTSS_PORT_INTERFACE_SGMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_SGMII_2G5:
            *out = VTSS_PORT_INTERFACE_SGMII_2G5;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_SGMII_CISCO:
            *out = VTSS_PORT_INTERFACE_SGMII_CISCO;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_SERDES:
            *out = VTSS_PORT_INTERFACE_SERDES;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_VAUI:
            *out = VTSS_PORT_INTERFACE_VAUI;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_100FX:
            *out = VTSS_PORT_INTERFACE_100FX;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_XAUI:
            *out = VTSS_PORT_INTERFACE_XAUI;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_RXAUI:
            *out = VTSS_PORT_INTERFACE_RXAUI;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_XGMII:
            *out = VTSS_PORT_INTERFACE_XGMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_SPI4:
            *out = VTSS_PORT_INTERFACE_SPI4;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_QSGMII:
            *out = VTSS_PORT_INTERFACE_QSGMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_SFI:
            *out = VTSS_PORT_INTERFACE_SFI;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_SXGMII:
            *out = VTSS_PORT_INTERFACE_SXGMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_USGMII:
            *out = VTSS_PORT_INTERFACE_USGMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_QXGMII:
            *out = VTSS_PORT_INTERFACE_QXGMII;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_DXGMII_5G:
            *out = VTSS_PORT_INTERFACE_DXGMII_5G;
            return VTSS_RC_OK;
        case MESA_PORT_INTERFACE_DXGMII_10G:
            *out = VTSS_PORT_INTERFACE_DXGMII_10G;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_reset_conf_t_to_mesa_phy_reset_conf_t(const vtss_phy_reset_conf_t *in, mesa_phy_reset_conf_t *out) /* ag.rb:1656 */
{
    __RC(mesa_conv_vtss_port_interface_t_to_mesa_port_interface_t(&in->mac_if, &out->mac_if)); /* ag.rb:1432 */
    {
        const mesa_phy_media_interface_t *tmp = (const mesa_phy_media_interface_t *)&in->media_if;
#ifdef __cplusplus
        static_assert(sizeof(out.media_if) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->media_if = *tmp;
    }
    {
        const mesa_phy_rgmii_conf_t *tmp = (const mesa_phy_rgmii_conf_t *)&in->rgmii;
#ifdef __cplusplus
        static_assert(sizeof(out.rgmii) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rgmii = *tmp;
    }
    {
        const mesa_phy_tbi_conf_t *tmp = (const mesa_phy_tbi_conf_t *)&in->tbi;
#ifdef __cplusplus
        static_assert(sizeof(out.tbi) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tbi = *tmp;
    }
    {
        const mesa_phy_forced_reset_t *tmp = (const mesa_phy_forced_reset_t *)&in->force;
#ifdef __cplusplus
        static_assert(sizeof(out.force) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->force = *tmp;
    }
    {
        const mesa_phy_pkt_mode_t *tmp = (const mesa_phy_pkt_mode_t *)&in->pkt_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.pkt_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->pkt_mode = *tmp;
    }
    out->i_cpu_en = in->i_cpu_en;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_reset_conf_t_to_vtss_phy_reset_conf_t(const mesa_phy_reset_conf_t *in, vtss_phy_reset_conf_t *out) /* ag.rb:1664 */
{
    __RC(mesa_conv_mesa_port_interface_t_to_vtss_port_interface_t(&in->mac_if, &out->mac_if)); /* ag.rb:1432 */
    {
        const vtss_phy_media_interface_t *tmp = (const vtss_phy_media_interface_t *)&in->media_if;
#ifdef __cplusplus
        static_assert(sizeof(out.media_if) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->media_if = *tmp;
    }
    {
        const vtss_phy_rgmii_conf_t *tmp = (const vtss_phy_rgmii_conf_t *)&in->rgmii;
#ifdef __cplusplus
        static_assert(sizeof(out.rgmii) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rgmii = *tmp;
    }
    {
        const vtss_phy_tbi_conf_t *tmp = (const vtss_phy_tbi_conf_t *)&in->tbi;
#ifdef __cplusplus
        static_assert(sizeof(out.tbi) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tbi = *tmp;
    }
    {
        const vtss_phy_forced_reset_t *tmp = (const vtss_phy_forced_reset_t *)&in->force;
#ifdef __cplusplus
        static_assert(sizeof(out.force) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->force = *tmp;
    }
    {
        const vtss_phy_pkt_mode_t *tmp = (const vtss_phy_pkt_mode_t *)&in->pkt_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.pkt_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->pkt_mode = *tmp;
    }
    out->i_cpu_en = in->i_cpu_en;

    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_conv_vtss_macsec_mac_counters_t_to_mesa_macsec_mac_counters_t(const vtss_macsec_mac_counters_t *in, mesa_macsec_mac_counters_t *out) /* ag.rb:1656 */
{
    // skipped: if_rx_pause_pkts@vtss_macsec_mac_counters_t
    // skipped: if_tx_pause_pkts@vtss_macsec_mac_counters_t
    out->if_rx_octets = in->if_rx_octets;
    out->if_rx_in_bytes = in->if_rx_in_bytes;
    out->if_rx_ucast_pkts = in->if_rx_ucast_pkts;
    out->if_rx_multicast_pkts = in->if_rx_multicast_pkts;
    out->if_rx_broadcast_pkts = in->if_rx_broadcast_pkts;
    out->if_rx_discards = in->if_rx_discards;
    out->if_rx_errors = in->if_rx_errors;
    out->if_rx_StatsPkts = in->if_rx_StatsPkts;
    out->if_rx_CRCAlignErrors = in->if_rx_CRCAlignErrors;
    out->if_rx_UndersizePkts = in->if_rx_UndersizePkts;
    out->if_rx_OversizePkts = in->if_rx_OversizePkts;
    out->if_rx_Fragments = in->if_rx_Fragments;
    out->if_rx_Jabbers = in->if_rx_Jabbers;
    out->if_rx_Pkts64Octets = in->if_rx_Pkts64Octets;
    out->if_rx_Pkts65to127Octets = in->if_rx_Pkts65to127Octets;
    out->if_rx_Pkts128to255Octets = in->if_rx_Pkts128to255Octets;
    out->if_rx_Pkts256to511Octets = in->if_rx_Pkts256to511Octets;
    out->if_rx_Pkts512to1023Octets = in->if_rx_Pkts512to1023Octets;
    out->if_rx_Pkts1024to1518Octets = in->if_rx_Pkts1024to1518Octets;
    out->if_rx_Pkts1519toMaxOctets = in->if_rx_Pkts1519toMaxOctets;
    out->if_tx_octets = in->if_tx_octets;
    out->if_tx_ucast_pkts = in->if_tx_ucast_pkts;
    out->if_tx_multicast_pkts = in->if_tx_multicast_pkts;
    out->if_tx_broadcast_pkts = in->if_tx_broadcast_pkts;
    out->if_tx_errors = in->if_tx_errors;
    out->if_tx_DropEvents = in->if_tx_DropEvents;
    out->if_tx_StatsPkts = in->if_tx_StatsPkts;
    out->if_tx_Collisions = in->if_tx_Collisions;
    out->if_tx_Pkts64Octets = in->if_tx_Pkts64Octets;
    out->if_tx_Pkts65to127Octets = in->if_tx_Pkts65to127Octets;
    out->if_tx_Pkts128to255Octets = in->if_tx_Pkts128to255Octets;
    out->if_tx_Pkts256to511Octets = in->if_tx_Pkts256to511Octets;
    out->if_tx_Pkts512to1023Octets = in->if_tx_Pkts512to1023Octets;
    out->if_tx_Pkts1024to1518Octets = in->if_tx_Pkts1024to1518Octets;
    out->if_tx_Pkts1519toMaxOctets = in->if_tx_Pkts1519toMaxOctets;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_macsec_mac_counters_t_to_vtss_macsec_mac_counters_t(const mesa_macsec_mac_counters_t *in, vtss_macsec_mac_counters_t *out) /* ag.rb:1664 */
{
    // skipped: if_rx_pause_pkts@vtss_macsec_mac_counters_t
    // skipped: if_tx_pause_pkts@vtss_macsec_mac_counters_t
    out->if_rx_octets = in->if_rx_octets;
    out->if_rx_in_bytes = in->if_rx_in_bytes;
    out->if_rx_ucast_pkts = in->if_rx_ucast_pkts;
    out->if_rx_multicast_pkts = in->if_rx_multicast_pkts;
    out->if_rx_broadcast_pkts = in->if_rx_broadcast_pkts;
    out->if_rx_discards = in->if_rx_discards;
    out->if_rx_errors = in->if_rx_errors;
    out->if_rx_StatsPkts = in->if_rx_StatsPkts;
    out->if_rx_CRCAlignErrors = in->if_rx_CRCAlignErrors;
    out->if_rx_UndersizePkts = in->if_rx_UndersizePkts;
    out->if_rx_OversizePkts = in->if_rx_OversizePkts;
    out->if_rx_Fragments = in->if_rx_Fragments;
    out->if_rx_Jabbers = in->if_rx_Jabbers;
    out->if_rx_Pkts64Octets = in->if_rx_Pkts64Octets;
    out->if_rx_Pkts65to127Octets = in->if_rx_Pkts65to127Octets;
    out->if_rx_Pkts128to255Octets = in->if_rx_Pkts128to255Octets;
    out->if_rx_Pkts256to511Octets = in->if_rx_Pkts256to511Octets;
    out->if_rx_Pkts512to1023Octets = in->if_rx_Pkts512to1023Octets;
    out->if_rx_Pkts1024to1518Octets = in->if_rx_Pkts1024to1518Octets;
    out->if_rx_Pkts1519toMaxOctets = in->if_rx_Pkts1519toMaxOctets;
    out->if_tx_octets = in->if_tx_octets;
    out->if_tx_ucast_pkts = in->if_tx_ucast_pkts;
    out->if_tx_multicast_pkts = in->if_tx_multicast_pkts;
    out->if_tx_broadcast_pkts = in->if_tx_broadcast_pkts;
    out->if_tx_errors = in->if_tx_errors;
    out->if_tx_DropEvents = in->if_tx_DropEvents;
    out->if_tx_StatsPkts = in->if_tx_StatsPkts;
    out->if_tx_Collisions = in->if_tx_Collisions;
    out->if_tx_Pkts64Octets = in->if_tx_Pkts64Octets;
    out->if_tx_Pkts65to127Octets = in->if_tx_Pkts65to127Octets;
    out->if_tx_Pkts128to255Octets = in->if_tx_Pkts128to255Octets;
    out->if_tx_Pkts256to511Octets = in->if_tx_Pkts256to511Octets;
    out->if_tx_Pkts512to1023Octets = in->if_tx_Pkts512to1023Octets;
    out->if_tx_Pkts1024to1518Octets = in->if_tx_Pkts1024to1518Octets;
    out->if_tx_Pkts1519toMaxOctets = in->if_tx_Pkts1519toMaxOctets;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)

#if 0
mesa_rc mesa_conv_vtss_debug_info_t_to_mesa_debug_info_t(const vtss_debug_info_t *in, mesa_debug_info_t *out) /* ag.rb:1656 */
{
    // skipped: prm@vtss_debug_info_t
    {
        const mesa_debug_layer_t *tmp = (const mesa_debug_layer_t *)&in->layer;
#ifdef __cplusplus
        static_assert(sizeof(out.layer) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->layer = *tmp;
    }
    {
        const mesa_debug_group_t *tmp = (const mesa_debug_group_t *)&in->group;
#ifdef __cplusplus
        static_assert(sizeof(out.group) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->group = *tmp;
    }
    out->chip_no = in->chip_no;
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1432 */
    out->full = in->full;
    out->clear = in->clear;
    out->vml_format = in->vml_format;
    out->has_action = in->has_action;
    out->action = in->action;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_debug_info_t_to_vtss_debug_info_t(const mesa_debug_info_t *in, vtss_debug_info_t *out) /* ag.rb:1664 */
{
    // skipped: prm@vtss_debug_info_t
    {
        const vtss_debug_layer_t *tmp = (const vtss_debug_layer_t *)&in->layer;
#ifdef __cplusplus
        static_assert(sizeof(out.layer) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->layer = *tmp;
    }
    {
        const vtss_debug_group_t *tmp = (const vtss_debug_group_t *)&in->group;
#ifdef __cplusplus
        static_assert(sizeof(out.group) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->group = *tmp;
    }
    out->chip_no = in->chip_no;
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1432 */
    out->full = in->full;
    out->clear = in->clear;
    out->vml_format = in->vml_format;
    out->has_action = in->has_action;
    out->action = in->action;

    return VTSS_RC_OK;
}
#endif // 0

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_oper_mode_t_to_mesa_oper_mode_t(const vtss_oper_mode_t *in, mesa_oper_mode_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        case VTSS_PHY_LAN_MODE:
            *out = MESA_PHY_LAN_MODE;
            return VTSS_RC_OK;
        case VTSS_PHY_WAN_MODE:
            *out = MESA_PHY_WAN_MODE;
            return VTSS_RC_OK;
        case VTSS_PHY_1G_MODE:
            *out = MESA_PHY_1G_MODE;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_SYNCE_10G)
        case VTSS_PHY_LAN_SYNCE_MODE:
            *out = MESA_PHY_LAN_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
        case VTSS_PHY_WAN_SYNCE_MODE:
            *out = MESA_PHY_WAN_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
        case VTSS_PHY_LAN_MIXED_SYNCE_MODE:
            *out = MESA_PHY_LAN_MIXED_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
        case VTSS_PHY_WAN_MIXED_SYNCE_MODE:
            *out = MESA_PHY_WAN_MIXED_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
        case VTSS_PHY_REPEATER_MODE:
            *out = MESA_PHY_REPEATER_MODE;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_oper_mode_t_to_vtss_oper_mode_t(const mesa_oper_mode_t *in, vtss_oper_mode_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        case MESA_PHY_LAN_MODE:
            *out = VTSS_PHY_LAN_MODE;
            return VTSS_RC_OK;
        case MESA_PHY_WAN_MODE:
            *out = VTSS_PHY_WAN_MODE;
            return VTSS_RC_OK;
        case MESA_PHY_1G_MODE:
            *out = VTSS_PHY_1G_MODE;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_SYNCE_10G)
        case MESA_PHY_LAN_SYNCE_MODE:
            *out = VTSS_PHY_LAN_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
        case MESA_PHY_WAN_SYNCE_MODE:
            *out = VTSS_PHY_WAN_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
        case MESA_PHY_LAN_MIXED_SYNCE_MODE:
            *out = VTSS_PHY_LAN_MIXED_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
        case MESA_PHY_WAN_MIXED_SYNCE_MODE:
            *out = VTSS_PHY_WAN_MIXED_SYNCE_MODE;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
        case MESA_PHY_REPEATER_MODE:
            *out = VTSS_PHY_REPEATER_MODE;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // VTSS_CHIP_10G_PHY

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_phy_10g_mode_t_to_mesa_phy_10g_mode_t(const vtss_phy_10g_mode_t *in, mesa_phy_10g_mode_t *out) /* ag.rb:1656 */
{
    __RC(mesa_conv_vtss_oper_mode_t_to_mesa_oper_mode_t(&in->oper_mode, &out->oper_mode)); /* ag.rb:1432 */
    {
        const mesa_phy_interface_mode *tmp = (const mesa_phy_interface_mode *)&in->interface;
#ifdef __cplusplus
        static_assert(sizeof(out.interface) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->interface = *tmp;
    }
    {
        const mesa_wrefclk_t *tmp = (const mesa_wrefclk_t *)&in->wrefclk;
#ifdef __cplusplus
        static_assert(sizeof(out.wrefclk) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->wrefclk = *tmp;
    }
    out->high_input_gain = in->high_input_gain;
    out->xfi_pol_invert = in->xfi_pol_invert;
    out->xaui_lane_flip = in->xaui_lane_flip;
    {
        const mesa_channel_t *tmp = (const mesa_channel_t *)&in->channel_id;
#ifdef __cplusplus
        static_assert(sizeof(out.channel_id) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->channel_id = *tmp;
    }
#if defined(VTSS_FEATURE_SYNCE_10G)
    out->hl_clk_synth = in->hl_clk_synth;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const mesa_recvrd_t *tmp = (const mesa_recvrd_t *)&in->rcvrd_clk;
#ifdef __cplusplus
        static_assert(sizeof(out.rcvrd_clk) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rcvrd_clk = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const mesa_recvrdclk_cdr_div_t *tmp = (const mesa_recvrdclk_cdr_div_t *)&in->rcvrd_clk_div;
#ifdef __cplusplus
        static_assert(sizeof(out.rcvrd_clk_div) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rcvrd_clk_div = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const mesa_srefclk_div_t *tmp = (const mesa_srefclk_div_t *)&in->sref_clk_div;
#ifdef __cplusplus
        static_assert(sizeof(out.sref_clk_div) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sref_clk_div = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const mesa_wref_clk_div_t *tmp = (const mesa_wref_clk_div_t *)&in->wref_clk_div;
#ifdef __cplusplus
        static_assert(sizeof(out.wref_clk_div) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->wref_clk_div = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_EDC_FW_LOAD)
    {
        const mesa_edc_fw_load_t *tmp = (const mesa_edc_fw_load_t *)&in->edc_fw_load;
#ifdef __cplusplus
        static_assert(sizeof(out.edc_fw_load) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->edc_fw_load = *tmp;
    }
#endif  // defined(VTSS_FEATURE_EDC_FW_LOAD)
    out->serdes_conf.use_conf = in->serdes_conf.use_conf;
    out->serdes_conf.ob_conf = in->serdes_conf.ob_conf;
    out->serdes_conf.ib_conf = in->serdes_conf.ib_conf;
    out->serdes_conf.dig_offset_reg = in->serdes_conf.dig_offset_reg;
    out->serdes_conf.apc_offs_ctrl = in->serdes_conf.apc_offs_ctrl;
    out->serdes_conf.apc_line_ld_ctrl = in->serdes_conf.apc_line_ld_ctrl;
    out->serdes_conf.apc_host_ld_ctrl = in->serdes_conf.apc_host_ld_ctrl;
    out->serdes_conf.d_filter = in->serdes_conf.d_filter;
    out->serdes_conf.cfg0 = in->serdes_conf.cfg0;
    out->serdes_conf.ib_ini_lp = in->serdes_conf.ib_ini_lp;
    out->serdes_conf.ib_min_lp = in->serdes_conf.ib_min_lp;
    out->serdes_conf.ib_max_lp = in->serdes_conf.ib_max_lp;
    out->serdes_conf.apc_eqz_offs_par_cfg = in->serdes_conf.apc_eqz_offs_par_cfg;
    out->serdes_conf.apc_line_eqz_ld_ctrl = in->serdes_conf.apc_line_eqz_ld_ctrl;
    out->serdes_conf.apc_host_eqz_ld_ctrl = in->serdes_conf.apc_host_eqz_ld_ctrl;
    out->serdes_conf.l_offset_guard = in->serdes_conf.l_offset_guard;
    out->serdes_conf.h_offset_guard = in->serdes_conf.h_offset_guard;
    {
        const mesa_apc_ib_regulator_t *tmp = (const mesa_apc_ib_regulator_t *)&in->apc_ib_regulator;
#ifdef __cplusplus
        static_assert(sizeof(out.apc_ib_regulator) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->apc_ib_regulator = *tmp;
    }
    out->pma_txratecontrol = in->pma_txratecontrol;
    out->venice_rev_a_los_detection_workaround = in->venice_rev_a_los_detection_workaround;
    {
        const mesa_ddr_mode_t *tmp = (const mesa_ddr_mode_t *)&in->ddr_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.ddr_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ddr_mode = *tmp;
    }
    {
        const mesa_clk_mstr_t *tmp = (const mesa_clk_mstr_t *)&in->master;
#ifdef __cplusplus
        static_assert(sizeof(out.master) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->master = *tmp;
    }
    {
        const mesa_rptr_rate_t *tmp = (const mesa_rptr_rate_t *)&in->rate;
#ifdef __cplusplus
        static_assert(sizeof(out.rate) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rate = *tmp;
    }
    {
        const mesa_phy_10g_polarity_inv_t *tmp = (const mesa_phy_10g_polarity_inv_t *)&in->polarity;
#ifdef __cplusplus
        static_assert(sizeof(out.polarity) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->polarity = *tmp;
    }
    out->is_host_wan = in->is_host_wan;
    {
        const mesa_phy_10g_clk_src_t *tmp = (const mesa_phy_10g_clk_src_t *)&in->h_clk_src;
#ifdef __cplusplus
        static_assert(sizeof(out.h_clk_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_clk_src = *tmp;
    }
    {
        const mesa_phy_10g_clk_src_t *tmp = (const mesa_phy_10g_clk_src_t *)&in->l_clk_src;
#ifdef __cplusplus
        static_assert(sizeof(out.l_clk_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_clk_src = *tmp;
    }
    out->lref_for_host = in->lref_for_host;
    {
        const mesa_phy_6g_link_partner_distance_t *tmp = (const mesa_phy_6g_link_partner_distance_t *)&in->link_6g_distance;
#ifdef __cplusplus
        static_assert(sizeof(out.link_6g_distance) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->link_6g_distance = *tmp;
    }
    {
        const mesa_phy_10g_media_t *tmp = (const mesa_phy_10g_media_t *)&in->h_media;
#ifdef __cplusplus
        static_assert(sizeof(out.h_media) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_media = *tmp;
    }
    {
        const mesa_phy_10g_media_t *tmp = (const mesa_phy_10g_media_t *)&in->l_media;
#ifdef __cplusplus
        static_assert(sizeof(out.l_media) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_media = *tmp;
    }
    {
        const mesa_phy_10g_ib_conf_t *tmp = (const mesa_phy_10g_ib_conf_t *)&in->h_ib_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.h_ib_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_ib_conf = *tmp;
    }
    {
        const mesa_phy_10g_ib_conf_t *tmp = (const mesa_phy_10g_ib_conf_t *)&in->l_ib_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.l_ib_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_ib_conf = *tmp;
    }
    {
        const mesa_phy_10g_apc_conf_t *tmp = (const mesa_phy_10g_apc_conf_t *)&in->h_apc_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.h_apc_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_apc_conf = *tmp;
    }
    {
        const mesa_phy_10g_apc_conf_t *tmp = (const mesa_phy_10g_apc_conf_t *)&in->l_apc_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.l_apc_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_apc_conf = *tmp;
    }
    out->enable_pass_thru = in->enable_pass_thru;
    out->is_init = in->is_init;
    out->sd6g_calib_done = in->sd6g_calib_done;
    out->alternate_port_ena = in->alternate_port_ena;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_10g_mode_t_to_vtss_phy_10g_mode_t(const mesa_phy_10g_mode_t *in, vtss_phy_10g_mode_t *out) /* ag.rb:1664 */
{
    __RC(mesa_conv_mesa_oper_mode_t_to_vtss_oper_mode_t(&in->oper_mode, &out->oper_mode)); /* ag.rb:1432 */
    {
        const vtss_phy_interface_mode *tmp = (const vtss_phy_interface_mode *)&in->interface;
#ifdef __cplusplus
        static_assert(sizeof(out.interface) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->interface = *tmp;
    }
    {
        const vtss_wrefclk_t *tmp = (const vtss_wrefclk_t *)&in->wrefclk;
#ifdef __cplusplus
        static_assert(sizeof(out.wrefclk) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->wrefclk = *tmp;
    }
    out->high_input_gain = in->high_input_gain;
    out->xfi_pol_invert = in->xfi_pol_invert;
    out->xaui_lane_flip = in->xaui_lane_flip;
    {
        const vtss_channel_t *tmp = (const vtss_channel_t *)&in->channel_id;
#ifdef __cplusplus
        static_assert(sizeof(out.channel_id) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->channel_id = *tmp;
    }
#if defined(VTSS_FEATURE_SYNCE_10G)
    out->hl_clk_synth = in->hl_clk_synth;
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const vtss_recvrd_t *tmp = (const vtss_recvrd_t *)&in->rcvrd_clk;
#ifdef __cplusplus
        static_assert(sizeof(out.rcvrd_clk) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rcvrd_clk = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const vtss_recvrdclk_cdr_div_t *tmp = (const vtss_recvrdclk_cdr_div_t *)&in->rcvrd_clk_div;
#ifdef __cplusplus
        static_assert(sizeof(out.rcvrd_clk_div) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rcvrd_clk_div = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const vtss_srefclk_div_t *tmp = (const vtss_srefclk_div_t *)&in->sref_clk_div;
#ifdef __cplusplus
        static_assert(sizeof(out.sref_clk_div) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sref_clk_div = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_SYNCE_10G)
    {
        const vtss_wref_clk_div_t *tmp = (const vtss_wref_clk_div_t *)&in->wref_clk_div;
#ifdef __cplusplus
        static_assert(sizeof(out.wref_clk_div) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->wref_clk_div = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#if defined(VTSS_FEATURE_EDC_FW_LOAD)
    {
        const vtss_edc_fw_load_t *tmp = (const vtss_edc_fw_load_t *)&in->edc_fw_load;
#ifdef __cplusplus
        static_assert(sizeof(out.edc_fw_load) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->edc_fw_load = *tmp;
    }
#endif  // defined(VTSS_FEATURE_EDC_FW_LOAD)
    out->serdes_conf.use_conf = in->serdes_conf.use_conf;
    out->serdes_conf.ob_conf = in->serdes_conf.ob_conf;
    out->serdes_conf.ib_conf = in->serdes_conf.ib_conf;
    out->serdes_conf.dig_offset_reg = in->serdes_conf.dig_offset_reg;
    out->serdes_conf.apc_offs_ctrl = in->serdes_conf.apc_offs_ctrl;
    out->serdes_conf.apc_line_ld_ctrl = in->serdes_conf.apc_line_ld_ctrl;
    out->serdes_conf.apc_host_ld_ctrl = in->serdes_conf.apc_host_ld_ctrl;
    out->serdes_conf.d_filter = in->serdes_conf.d_filter;
    out->serdes_conf.cfg0 = in->serdes_conf.cfg0;
    out->serdes_conf.ib_ini_lp = in->serdes_conf.ib_ini_lp;
    out->serdes_conf.ib_min_lp = in->serdes_conf.ib_min_lp;
    out->serdes_conf.ib_max_lp = in->serdes_conf.ib_max_lp;
    out->serdes_conf.apc_eqz_offs_par_cfg = in->serdes_conf.apc_eqz_offs_par_cfg;
    out->serdes_conf.apc_line_eqz_ld_ctrl = in->serdes_conf.apc_line_eqz_ld_ctrl;
    out->serdes_conf.apc_host_eqz_ld_ctrl = in->serdes_conf.apc_host_eqz_ld_ctrl;
    out->serdes_conf.l_offset_guard = in->serdes_conf.l_offset_guard;
    out->serdes_conf.h_offset_guard = in->serdes_conf.h_offset_guard;
    {
        const vtss_apc_ib_regulator_t *tmp = (const vtss_apc_ib_regulator_t *)&in->apc_ib_regulator;
#ifdef __cplusplus
        static_assert(sizeof(out.apc_ib_regulator) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->apc_ib_regulator = *tmp;
    }
    out->pma_txratecontrol = in->pma_txratecontrol;
    out->venice_rev_a_los_detection_workaround = in->venice_rev_a_los_detection_workaround;
    {
        const vtss_ddr_mode_t *tmp = (const vtss_ddr_mode_t *)&in->ddr_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.ddr_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ddr_mode = *tmp;
    }
    {
        const vtss_clk_mstr_t *tmp = (const vtss_clk_mstr_t *)&in->master;
#ifdef __cplusplus
        static_assert(sizeof(out.master) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->master = *tmp;
    }
    {
        const vtss_rptr_rate_t *tmp = (const vtss_rptr_rate_t *)&in->rate;
#ifdef __cplusplus
        static_assert(sizeof(out.rate) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rate = *tmp;
    }
    {
        const vtss_phy_10g_polarity_inv_t *tmp = (const vtss_phy_10g_polarity_inv_t *)&in->polarity;
#ifdef __cplusplus
        static_assert(sizeof(out.polarity) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->polarity = *tmp;
    }
    out->is_host_wan = in->is_host_wan;
    {
        const vtss_phy_10g_clk_src_t *tmp = (const vtss_phy_10g_clk_src_t *)&in->h_clk_src;
#ifdef __cplusplus
        static_assert(sizeof(out.h_clk_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_clk_src = *tmp;
    }
    {
        const vtss_phy_10g_clk_src_t *tmp = (const vtss_phy_10g_clk_src_t *)&in->l_clk_src;
#ifdef __cplusplus
        static_assert(sizeof(out.l_clk_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_clk_src = *tmp;
    }
    out->lref_for_host = in->lref_for_host;
    {
        const vtss_phy_6g_link_partner_distance_t *tmp = (const vtss_phy_6g_link_partner_distance_t *)&in->link_6g_distance;
#ifdef __cplusplus
        static_assert(sizeof(out.link_6g_distance) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->link_6g_distance = *tmp;
    }
    {
        const vtss_phy_10g_media_t *tmp = (const vtss_phy_10g_media_t *)&in->h_media;
#ifdef __cplusplus
        static_assert(sizeof(out.h_media) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_media = *tmp;
    }
    {
        const vtss_phy_10g_media_t *tmp = (const vtss_phy_10g_media_t *)&in->l_media;
#ifdef __cplusplus
        static_assert(sizeof(out.l_media) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_media = *tmp;
    }
    {
        const vtss_phy_10g_ib_conf_t *tmp = (const vtss_phy_10g_ib_conf_t *)&in->h_ib_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.h_ib_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_ib_conf = *tmp;
    }
    {
        const vtss_phy_10g_ib_conf_t *tmp = (const vtss_phy_10g_ib_conf_t *)&in->l_ib_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.l_ib_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_ib_conf = *tmp;
    }
    {
        const vtss_phy_10g_apc_conf_t *tmp = (const vtss_phy_10g_apc_conf_t *)&in->h_apc_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.h_apc_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->h_apc_conf = *tmp;
    }
    {
        const vtss_phy_10g_apc_conf_t *tmp = (const vtss_phy_10g_apc_conf_t *)&in->l_apc_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.l_apc_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->l_apc_conf = *tmp;
    }
    out->enable_pass_thru = in->enable_pass_thru;
    out->is_init = in->is_init;
    out->sd6g_calib_done = in->sd6g_calib_done;
    out->alternate_port_ena = in->alternate_port_ena;

    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_gpio_10g_input_t_to_mesa_gpio_10g_input_t(const vtss_gpio_10g_input_t *in, mesa_gpio_10g_input_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        // skipped: MESA_10G_GPIO_INPUT_SFP_MOD_DET
        case VTSS_10G_GPIO_INPUT_NONE:
            *out = MESA_10G_GPIO_INPUT_NONE;
            return VTSS_RC_OK;
        case VTSS_10G_GPIO_INPUT_LINE_LOPC:
            *out = MESA_10G_GPIO_INPUT_LINE_LOPC;
            return VTSS_RC_OK;
        case VTSS_10G_GPIO_INPUT_HOST_LOPC:
            *out = MESA_10G_GPIO_INPUT_HOST_LOPC;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_gpio_10g_input_t_to_vtss_gpio_10g_input_t(const mesa_gpio_10g_input_t *in, vtss_gpio_10g_input_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        // skipped: MESA_10G_GPIO_INPUT_SFP_MOD_DET
        case MESA_10G_GPIO_INPUT_NONE:
            *out = VTSS_10G_GPIO_INPUT_NONE;
            return VTSS_RC_OK;
        case MESA_10G_GPIO_INPUT_LINE_LOPC:
            *out = VTSS_10G_GPIO_INPUT_LINE_LOPC;
            return VTSS_RC_OK;
        case MESA_10G_GPIO_INPUT_HOST_LOPC:
            *out = VTSS_10G_GPIO_INPUT_HOST_LOPC;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // VTSS_CHIP_10G_PHY

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_gpio_10g_gpio_mode_t_to_mesa_gpio_10g_gpio_mode_t(const vtss_gpio_10g_gpio_mode_t *in, mesa_gpio_10g_gpio_mode_t *out) /* ag.rb:1656 */
{
    // skipped: invert_output@vtss_gpio_10g_gpio_mode_t
    {
        const mesa_10g_phy_gpio_t *tmp = (const mesa_10g_phy_gpio_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
    out->port = in->port;
    __RC(mesa_conv_vtss_gpio_10g_input_t_to_mesa_gpio_10g_input_t(&in->input, &out->input)); /* ag.rb:1432 */
    {
        const mesa_gpio_10g_gpio_intr_sgnl_t *tmp = (const mesa_gpio_10g_gpio_intr_sgnl_t *)&in->in_sig;
#ifdef __cplusplus
        static_assert(sizeof(out.in_sig) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->in_sig = *tmp;
    }
    out->p_gpio = in->p_gpio;
    {
        const mesa_gpio_10g_chan_intrpt_t *tmp = (const mesa_gpio_10g_chan_intrpt_t *)&in->c_intrpt;
#ifdef __cplusplus
        static_assert(sizeof(out.c_intrpt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->c_intrpt = *tmp;
    }
    out->source = in->source;
    out->aggr_intrpt = in->aggr_intrpt;
    out->use_as_intrpt = in->use_as_intrpt;
    out->p_gpio_intrpt = in->p_gpio_intrpt;
    {
        const mesa_gpio_10g_led_conf_t *tmp = (const mesa_gpio_10g_led_conf_t *)&in->led_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.led_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->led_conf = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_gpio_10g_gpio_mode_t_to_vtss_gpio_10g_gpio_mode_t(const mesa_gpio_10g_gpio_mode_t *in, vtss_gpio_10g_gpio_mode_t *out) /* ag.rb:1664 */
{
    // skipped: invert_output@vtss_gpio_10g_gpio_mode_t
    {
        const vtss_10g_phy_gpio_t *tmp = (const vtss_10g_phy_gpio_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
    out->port = in->port;
    __RC(mesa_conv_mesa_gpio_10g_input_t_to_vtss_gpio_10g_input_t(&in->input, &out->input)); /* ag.rb:1432 */
    {
        const vtss_gpio_10g_gpio_intr_sgnl_t *tmp = (const vtss_gpio_10g_gpio_intr_sgnl_t *)&in->in_sig;
#ifdef __cplusplus
        static_assert(sizeof(out.in_sig) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->in_sig = *tmp;
    }
    out->p_gpio = in->p_gpio;
    {
        const vtss_gpio_10g_chan_intrpt_t *tmp = (const vtss_gpio_10g_chan_intrpt_t *)&in->c_intrpt;
#ifdef __cplusplus
        static_assert(sizeof(out.c_intrpt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->c_intrpt = *tmp;
    }
    out->source = in->source;
    out->aggr_intrpt = in->aggr_intrpt;
    out->use_as_intrpt = in->use_as_intrpt;
    out->p_gpio_intrpt = in->p_gpio_intrpt;
    {
        const vtss_gpio_10g_led_conf_t *tmp = (const vtss_gpio_10g_led_conf_t *)&in->led_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.led_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->led_conf = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_conf_t_to_mesa_phy_conf_t(const vtss_phy_conf_t *in, mesa_phy_conf_t *out) /* ag.rb:1656 */
{
    // skipped: skip_coma@vtss_phy_conf_t
    {
        const mesa_phy_mode_t *tmp = (const mesa_phy_mode_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
    {
        const mesa_phy_forced_t *tmp = (const mesa_phy_forced_t *)&in->forced;
#ifdef __cplusplus
        static_assert(sizeof(out.forced) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->forced = *tmp;
    }
    {
        const mesa_phy_aneg_t *tmp = (const mesa_phy_aneg_t *)&in->aneg;
#ifdef __cplusplus
        static_assert(sizeof(out.aneg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->aneg = *tmp;
    }
    {
        const mesa_phy_mdi_t *tmp = (const mesa_phy_mdi_t *)&in->mdi;
#ifdef __cplusplus
        static_assert(sizeof(out.mdi) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mdi = *tmp;
    }
    {
        const mesa_phy_fast_link_fail_t *tmp = (const mesa_phy_fast_link_fail_t *)&in->flf;
#ifdef __cplusplus
        static_assert(sizeof(out.flf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->flf = *tmp;
    }
    {
        const mesa_phy_sigdet_polarity_t *tmp = (const mesa_phy_sigdet_polarity_t *)&in->sigdet;
#ifdef __cplusplus
        static_assert(sizeof(out.sigdet) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sigdet = *tmp;
    }
    {
        const mesa_phy_unidirectional_t *tmp = (const mesa_phy_unidirectional_t *)&in->unidir;
#ifdef __cplusplus
        static_assert(sizeof(out.unidir) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->unidir = *tmp;
    }
    {
        const mesa_phy_mac_serd_pcs_cntl_t *tmp = (const mesa_phy_mac_serd_pcs_cntl_t *)&in->mac_if_pcs;
#ifdef __cplusplus
        static_assert(sizeof(out.mac_if_pcs) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mac_if_pcs = *tmp;
    }
    {
        const mesa_phy_media_serd_pcs_cntl_t *tmp = (const mesa_phy_media_serd_pcs_cntl_t *)&in->media_if_pcs;
#ifdef __cplusplus
        static_assert(sizeof(out.media_if_pcs) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->media_if_pcs = *tmp;
    }
    {
        const mesa_phy_media_force_ams_sel_t *tmp = (const mesa_phy_media_force_ams_sel_t *)&in->force_ams_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.force_ams_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->force_ams_sel = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(const mesa_phy_conf_t *in, vtss_phy_conf_t *out) /* ag.rb:1664 */
{
    // skipped: skip_coma@vtss_phy_conf_t
    {
        const vtss_phy_mode_t *tmp = (const vtss_phy_mode_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
    {
        const vtss_phy_forced_t *tmp = (const vtss_phy_forced_t *)&in->forced;
#ifdef __cplusplus
        static_assert(sizeof(out.forced) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->forced = *tmp;
    }
    {
        const vtss_phy_aneg_t *tmp = (const vtss_phy_aneg_t *)&in->aneg;
#ifdef __cplusplus
        static_assert(sizeof(out.aneg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->aneg = *tmp;
    }
    {
        const vtss_phy_mdi_t *tmp = (const vtss_phy_mdi_t *)&in->mdi;
#ifdef __cplusplus
        static_assert(sizeof(out.mdi) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mdi = *tmp;
    }
    {
        const vtss_phy_fast_link_fail_t *tmp = (const vtss_phy_fast_link_fail_t *)&in->flf;
#ifdef __cplusplus
        static_assert(sizeof(out.flf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->flf = *tmp;
    }
    {
        const vtss_phy_sigdet_polarity_t *tmp = (const vtss_phy_sigdet_polarity_t *)&in->sigdet;
#ifdef __cplusplus
        static_assert(sizeof(out.sigdet) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sigdet = *tmp;
    }
    {
        const vtss_phy_unidirectional_t *tmp = (const vtss_phy_unidirectional_t *)&in->unidir;
#ifdef __cplusplus
        static_assert(sizeof(out.unidir) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->unidir = *tmp;
    }
    {
        const vtss_phy_mac_serd_pcs_cntl_t *tmp = (const vtss_phy_mac_serd_pcs_cntl_t *)&in->mac_if_pcs;
#ifdef __cplusplus
        static_assert(sizeof(out.mac_if_pcs) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mac_if_pcs = *tmp;
    }
    {
        const vtss_phy_media_serd_pcs_cntl_t *tmp = (const vtss_phy_media_serd_pcs_cntl_t *)&in->media_if_pcs;
#ifdef __cplusplus
        static_assert(sizeof(out.media_if_pcs) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->media_if_pcs = *tmp;
    }
    {
        const vtss_phy_media_force_ams_sel_t *tmp = (const vtss_phy_media_force_ams_sel_t *)&in->force_ams_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.force_ams_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->force_ams_sel = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_power_conf_t_to_mesa_phy_power_conf_t(const vtss_phy_power_conf_t *in, mesa_phy_power_conf_t *out) /* ag.rb:1656 */
{
    __RC(mesa_conv_vtss_phy_power_mode_t_to_mesa_phy_power_mode_t(&in->mode, &out->mode)); /* ag.rb:1432 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_power_conf_t_to_vtss_phy_power_conf_t(const mesa_phy_power_conf_t *in, vtss_phy_power_conf_t *out) /* ag.rb:1664 */
{
    __RC(mesa_conv_mesa_phy_power_mode_t_to_vtss_phy_power_mode_t(&in->mode, &out->mode)); /* ag.rb:1432 */

    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_encap_t_to_mesa_phy_ts_encap_t(const vtss_phy_ts_encap_t *in, mesa_phy_ts_encap_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        case VTSS_PHY_TS_ENCAP_ETH_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_IP_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_IP_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_IP_IP_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_ETH_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_ETH_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_ETH_IP_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_MPLS_IP_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP:
            *out = MESA_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_OAM:
            *out = MESA_PHY_TS_ENCAP_ETH_OAM;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_ETH_OAM:
            *out = MESA_PHY_TS_ENCAP_ETH_ETH_OAM;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM:
            *out = MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM:
            *out = MESA_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ANY:
            *out = MESA_PHY_TS_ENCAP_ANY;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_ENCAP_ETH_GEN:
            *out = MESA_PHY_TS_ENCAP_ETH_GEN;
            return VTSS_RC_OK;
#if defined VTSS_FEATURE_WARM_START
        case VTSS_PHY_TS_ENCAP_NONE:
            *out = MESA_PHY_TS_ENCAP_NONE;
            return VTSS_RC_OK;
#endif  // defined VTSS_FEATURE_WARM_START
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(const mesa_phy_ts_encap_t *in, vtss_phy_ts_encap_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        case MESA_PHY_TS_ENCAP_ETH_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_IP_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_IP_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_IP_IP_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_ETH_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_ETH_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_ETH_IP_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_MPLS_IP_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP:
            *out = VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_OAM:
            *out = VTSS_PHY_TS_ENCAP_ETH_OAM;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_ETH_OAM:
            *out = VTSS_PHY_TS_ENCAP_ETH_ETH_OAM;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM:
            *out = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM:
            *out = VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ANY:
            *out = VTSS_PHY_TS_ENCAP_ANY;
            return VTSS_RC_OK;
        case MESA_PHY_TS_ENCAP_ETH_GEN:
            *out = VTSS_PHY_TS_ENCAP_ETH_GEN;
            return VTSS_RC_OK;
#if defined VTSS_FEATURE_WARM_START
        case MESA_PHY_TS_ENCAP_NONE:
            *out = VTSS_PHY_TS_ENCAP_NONE;
            return VTSS_RC_OK;
#endif  // defined VTSS_FEATURE_WARM_START
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_eng_init_conf_t_to_mesa_phy_ts_eng_init_conf_t(const vtss_phy_ts_eng_init_conf_t *in, mesa_phy_ts_eng_init_conf_t *out) /* ag.rb:1656 */
{
    out->eng_used = in->eng_used;
    __RC(mesa_conv_vtss_phy_ts_encap_t_to_mesa_phy_ts_encap_t(&in->encap_type, &out->encap_type)); /* ag.rb:1432 */
    {
        const mesa_phy_ts_engine_flow_match_t *tmp = (const mesa_phy_ts_engine_flow_match_t *)&in->flow_match_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.flow_match_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->flow_match_mode = *tmp;
    }
    out->flow_st_index = in->flow_st_index;
    out->flow_end_index = in->flow_end_index;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_eng_init_conf_t_to_vtss_phy_ts_eng_init_conf_t(const mesa_phy_ts_eng_init_conf_t *in, vtss_phy_ts_eng_init_conf_t *out) /* ag.rb:1664 */
{
    out->eng_used = in->eng_used;
    __RC(mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(&in->encap_type, &out->encap_type)); /* ag.rb:1432 */
    {
        const vtss_phy_ts_engine_flow_match_t *tmp = (const vtss_phy_ts_engine_flow_match_t *)&in->flow_match_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.flow_match_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->flow_match_mode = *tmp;
    }
    out->flow_st_index = in->flow_st_index;
    out->flow_end_index = in->flow_end_index;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv2_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(const vtss_phy_ts_eth_flow_conf_t *in, mesa_phy_ts_eth_flow_conf_t *out)
{
    out->outer_tag.value.val = in->outer_tag.value.val;
    out->outer_tag.value.mask = in->outer_tag.value.mask;
    out->inner_tag.i_tag.val = in->inner_tag.i_tag.val;
    out->inner_tag.i_tag.mask = in->inner_tag.i_tag.mask;
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(const mesa_phy_ts_eth_flow_conf_t *in, vtss_phy_ts_eth_flow_conf_t *out)
{
    out->outer_tag.value.val = in->outer_tag.value.val;
    out->outer_tag.value.mask = in->outer_tag.value.mask;
    out->inner_tag.i_tag.val = in->inner_tag.i_tag.val;
    out->inner_tag.i_tag.mask = in->inner_tag.i_tag.mask;
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(const vtss_phy_ts_ip_flow_conf_t *in, mesa_phy_ts_ip_flow_conf_t *out)
{
    for (int i = 0; i < 4; i++) {
        out->ip_addr.ipv6.addr[i] = in->ip_addr.ipv6.addr[i];
        out->ip_addr.ipv6.mask[i] = in->ip_addr.ipv6.mask[i];
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(const mesa_phy_ts_ip_flow_conf_t *in, vtss_phy_ts_ip_flow_conf_t *out)
{
    for (int i = 0; i < 4; i++) {
        out->ip_addr.ipv6.addr[i] = in->ip_addr.ipv6.addr[i];
        out->ip_addr.ipv6.mask[i] = in->ip_addr.ipv6.mask[i];
    }
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(const vtss_phy_ts_mpls_flow_conf_t *in, mesa_phy_ts_mpls_flow_conf_t *out)
{
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.top, &out->stack_level.top_down.top);
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.frst_lvl_after_top, &out->stack_level.top_down.frst_lvl_after_top);
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.snd_lvl_after_top, &out->stack_level.top_down.snd_lvl_after_top);
    mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.thrd_lvl_after_top, &out->stack_level.top_down.thrd_lvl_after_top);
    return VTSS_RC_OK;
}

mesa_rc mesa_conv2_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(const mesa_phy_ts_mpls_flow_conf_t *in, vtss_phy_ts_mpls_flow_conf_t *out)
{
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.top, &out->stack_level.top_down.top);
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.frst_lvl_after_top, &out->stack_level.top_down.frst_lvl_after_top);
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.snd_lvl_after_top, &out->stack_level.top_down.snd_lvl_after_top);
    mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(&in->stack_level.top_down.thrd_lvl_after_top, &out->stack_level.top_down.thrd_lvl_after_top);
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(const vtss_phy_ts_eth_flow_conf_t *in, mesa_phy_ts_eth_flow_conf_t *out) /* ag.rb:1656 */
{
    out->flow_en = in->flow_en;
    out->addr_match_mode = in->addr_match_mode;
    out->addr_match_select = in->addr_match_select;
    for (size_t i = 0; i < 6; ++i) {
        out->mac_addr[i] = in->mac_addr[i];
    }
    out->vlan_check = in->vlan_check;
    out->num_tag = in->num_tag;
    out->outer_tag_type = in->outer_tag_type;
    out->inner_tag_type = in->inner_tag_type;
    out->tag_range_mode = in->tag_range_mode;

    return mesa_conv2_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(in, out); /* ag.rb:1477 */
}

mesa_rc mesa_conv_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(const mesa_phy_ts_eth_flow_conf_t *in, vtss_phy_ts_eth_flow_conf_t *out) /* ag.rb:1664 */
{
    out->flow_en = in->flow_en;
    out->addr_match_mode = in->addr_match_mode;
    out->addr_match_select = in->addr_match_select;
    for (size_t i = 0; i < 6; ++i) {
        out->mac_addr[i] = in->mac_addr[i];
    }
    out->vlan_check = in->vlan_check;
    out->num_tag = in->num_tag;
    out->outer_tag_type = in->outer_tag_type;
    out->inner_tag_type = in->inner_tag_type;
    out->tag_range_mode = in->tag_range_mode;

    return mesa_conv2_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(in, out); /* ag.rb:1477 */
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(const vtss_phy_ts_eth_conf_t *in, mesa_phy_ts_eth_conf_t *out) /* ag.rb:1656 */
{
    out->comm_opt.pbb_en = in->comm_opt.pbb_en;
    out->comm_opt.etype = in->comm_opt.etype;
    out->comm_opt.tpid = in->comm_opt.tpid;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1432 */
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(const mesa_phy_ts_eth_conf_t *in, vtss_phy_ts_eth_conf_t *out) /* ag.rb:1664 */
{
    out->comm_opt.pbb_en = in->comm_opt.pbb_en;
    out->comm_opt.etype = in->comm_opt.etype;
    out->comm_opt.tpid = in->comm_opt.tpid;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1432 */
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(const vtss_phy_ts_ip_flow_conf_t *in, mesa_phy_ts_ip_flow_conf_t *out) /* ag.rb:1656 */
{
    out->flow_en = in->flow_en;
    out->match_mode = in->match_mode;

    return mesa_conv2_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(in, out); /* ag.rb:1477 */
}

mesa_rc mesa_conv_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(const mesa_phy_ts_ip_flow_conf_t *in, vtss_phy_ts_ip_flow_conf_t *out) /* ag.rb:1664 */
{
    out->flow_en = in->flow_en;
    out->match_mode = in->match_mode;

    return mesa_conv2_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(in, out); /* ag.rb:1477 */
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ip_conf_t_to_mesa_phy_ts_ip_conf_t(const vtss_phy_ts_ip_conf_t *in, mesa_phy_ts_ip_conf_t *out) /* ag.rb:1656 */
{
    out->comm_opt.ip_mode = in->comm_opt.ip_mode;
    out->comm_opt.sport_val = in->comm_opt.sport_val;
    out->comm_opt.sport_mask = in->comm_opt.sport_mask;
    out->comm_opt.dport_val = in->comm_opt.dport_val;
    out->comm_opt.dport_mask = in->comm_opt.dport_mask;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1432 */
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_ip_conf_t_to_vtss_phy_ts_ip_conf_t(const mesa_phy_ts_ip_conf_t *in, vtss_phy_ts_ip_conf_t *out) /* ag.rb:1664 */
{
    out->comm_opt.ip_mode = in->comm_opt.ip_mode;
    out->comm_opt.sport_val = in->comm_opt.sport_val;
    out->comm_opt.sport_mask = in->comm_opt.sport_mask;
    out->comm_opt.dport_val = in->comm_opt.dport_val;
    out->comm_opt.dport_mask = in->comm_opt.dport_mask;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1432 */
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(const vtss_phy_ts_mpls_flow_conf_t *in, mesa_phy_ts_mpls_flow_conf_t *out) /* ag.rb:1656 */
{
    out->flow_en = in->flow_en;
    out->stack_depth = in->stack_depth;
    out->stack_ref_point = in->stack_ref_point;

    return mesa_conv2_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(in, out); /* ag.rb:1477 */
}

mesa_rc mesa_conv_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(const mesa_phy_ts_mpls_flow_conf_t *in, vtss_phy_ts_mpls_flow_conf_t *out) /* ag.rb:1664 */
{
    out->flow_en = in->flow_en;
    out->stack_depth = in->stack_depth;
    out->stack_ref_point = in->stack_ref_point;

    return mesa_conv2_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(in, out); /* ag.rb:1477 */
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_mpls_conf_t_to_mesa_phy_ts_mpls_conf_t(const vtss_phy_ts_mpls_conf_t *in, mesa_phy_ts_mpls_conf_t *out) /* ag.rb:1656 */
{
    out->comm_opt.cw_en = in->comm_opt.cw_en;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1432 */
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_mpls_conf_t_to_vtss_phy_ts_mpls_conf_t(const mesa_phy_ts_mpls_conf_t *in, vtss_phy_ts_mpls_conf_t *out) /* ag.rb:1664 */
{
    out->comm_opt.cw_en = in->comm_opt.cw_en;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1432 */
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ptp_engine_flow_conf_t_to_mesa_phy_ts_ptp_engine_flow_conf_t(const vtss_phy_ts_ptp_engine_flow_conf_t *in, mesa_phy_ts_ptp_engine_flow_conf_t *out) /* ag.rb:1656 */
{
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_vtss_phy_ts_ip_conf_t_to_mesa_phy_ts_ip_conf_t(&in->ip1_opt, &out->ip1_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_vtss_phy_ts_ip_conf_t_to_mesa_phy_ts_ip_conf_t(&in->ip2_opt, &out->ip2_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_vtss_phy_ts_mpls_conf_t_to_mesa_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1432 */
    {
        const mesa_phy_ts_ach_conf_t *tmp = (const mesa_phy_ts_ach_conf_t *)&in->ach_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.ach_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ach_opt = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_ptp_engine_flow_conf_t_to_vtss_phy_ts_ptp_engine_flow_conf_t(const mesa_phy_ts_ptp_engine_flow_conf_t *in, vtss_phy_ts_ptp_engine_flow_conf_t *out) /* ag.rb:1664 */
{
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_mesa_phy_ts_ip_conf_t_to_vtss_phy_ts_ip_conf_t(&in->ip1_opt, &out->ip1_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_mesa_phy_ts_ip_conf_t_to_vtss_phy_ts_ip_conf_t(&in->ip2_opt, &out->ip2_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_mesa_phy_ts_mpls_conf_t_to_vtss_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1432 */
    {
        const vtss_phy_ts_ach_conf_t *tmp = (const vtss_phy_ts_ach_conf_t *)&in->ach_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.ach_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ach_opt = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_oam_engine_flow_conf_t_to_mesa_phy_ts_oam_engine_flow_conf_t(const vtss_phy_ts_oam_engine_flow_conf_t *in, mesa_phy_ts_oam_engine_flow_conf_t *out) /* ag.rb:1656 */
{
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_vtss_phy_ts_mpls_conf_t_to_mesa_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1432 */
    {
        const mesa_phy_ts_ach_conf_t *tmp = (const mesa_phy_ts_ach_conf_t *)&in->ach_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.ach_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ach_opt = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_oam_engine_flow_conf_t_to_vtss_phy_ts_oam_engine_flow_conf_t(const mesa_phy_ts_oam_engine_flow_conf_t *in, vtss_phy_ts_oam_engine_flow_conf_t *out) /* ag.rb:1664 */
{
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1432 */
    __RC(mesa_conv_mesa_phy_ts_mpls_conf_t_to_vtss_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1432 */
    {
        const vtss_phy_ts_ach_conf_t *tmp = (const vtss_phy_ts_ach_conf_t *)&in->ach_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.ach_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ach_opt = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_generic_flow_conf_t_to_mesa_phy_ts_generic_flow_conf_t(const vtss_phy_ts_generic_flow_conf_t *in, mesa_phy_ts_generic_flow_conf_t *out) /* ag.rb:1656 */
{
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1432 */
    {
        const mesa_phy_ts_gen_conf_t *tmp = (const mesa_phy_ts_gen_conf_t *)&in->gen_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.gen_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->gen_opt = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_generic_flow_conf_t_to_vtss_phy_ts_generic_flow_conf_t(const mesa_phy_ts_generic_flow_conf_t *in, vtss_phy_ts_generic_flow_conf_t *out) /* ag.rb:1664 */
{
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1432 */
    {
        const vtss_phy_ts_gen_conf_t *tmp = (const vtss_phy_ts_gen_conf_t *)&in->gen_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.gen_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->gen_opt = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_init_conf_t_to_mesa_phy_ts_init_conf_t(const vtss_phy_ts_init_conf_t *in, mesa_phy_ts_init_conf_t *out) /* ag.rb:1656 */
{
    // skipped: remote_phy@vtss_phy_ts_init_conf_t
    {
        const mesa_phy_ts_clockfreq_t *tmp = (const mesa_phy_ts_clockfreq_t *)&in->clk_freq;
#ifdef __cplusplus
        static_assert(sizeof(out.clk_freq) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->clk_freq = *tmp;
    }
    {
        const mesa_phy_ts_clock_src_t *tmp = (const mesa_phy_ts_clock_src_t *)&in->clk_src;
#ifdef __cplusplus
        static_assert(sizeof(out.clk_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->clk_src = *tmp;
    }
    {
        const mesa_phy_ts_rxtimestamp_pos_t *tmp = (const mesa_phy_ts_rxtimestamp_pos_t *)&in->rx_ts_pos;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_ts_pos) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_ts_pos = *tmp;
    }
    {
        const mesa_phy_ts_rxtimestamp_len_t *tmp = (const mesa_phy_ts_rxtimestamp_len_t *)&in->rx_ts_len;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_ts_len) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_ts_len = *tmp;
    }
    {
        const mesa_phy_ts_fifo_mode_t *tmp = (const mesa_phy_ts_fifo_mode_t *)&in->tx_fifo_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.tx_fifo_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tx_fifo_mode = *tmp;
    }
    {
        const mesa_phy_ts_fifo_timestamp_len_t *tmp = (const mesa_phy_ts_fifo_timestamp_len_t *)&in->tx_ts_len;
#ifdef __cplusplus
        static_assert(sizeof(out.tx_ts_len) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tx_ts_len = *tmp;
    }
    out->tx_fifo_spi_conf = in->tx_fifo_spi_conf;
    out->tx_fifo_hi_clk_cycs = in->tx_fifo_hi_clk_cycs;
    out->tx_fifo_lo_clk_cycs = in->tx_fifo_lo_clk_cycs;
#ifdef VTSS_CHIP_10G_PHY
    out->xaui_sel_8487 = in->xaui_sel_8487;
#endif  // VTSS_CHIP_10G_PHY
    {
        const mesa_phy_ts_tc_op_mode_t *tmp = (const mesa_phy_ts_tc_op_mode_t *)&in->tc_op_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.tc_op_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tc_op_mode = *tmp;
    }
    out->auto_clear_ls = in->auto_clear_ls;
    out->macsec_ena = in->macsec_ena;
    out->chk_ing_modified = in->chk_ing_modified;
    out->one_step_txfifo = in->one_step_txfifo;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_init_conf_t_to_vtss_phy_ts_init_conf_t(const mesa_phy_ts_init_conf_t *in, vtss_phy_ts_init_conf_t *out) /* ag.rb:1664 */
{
    // skipped: remote_phy@vtss_phy_ts_init_conf_t
    {
        const vtss_phy_ts_clockfreq_t *tmp = (const vtss_phy_ts_clockfreq_t *)&in->clk_freq;
#ifdef __cplusplus
        static_assert(sizeof(out.clk_freq) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->clk_freq = *tmp;
    }
    {
        const vtss_phy_ts_clock_src_t *tmp = (const vtss_phy_ts_clock_src_t *)&in->clk_src;
#ifdef __cplusplus
        static_assert(sizeof(out.clk_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->clk_src = *tmp;
    }
    {
        const vtss_phy_ts_rxtimestamp_pos_t *tmp = (const vtss_phy_ts_rxtimestamp_pos_t *)&in->rx_ts_pos;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_ts_pos) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_ts_pos = *tmp;
    }
    {
        const vtss_phy_ts_rxtimestamp_len_t *tmp = (const vtss_phy_ts_rxtimestamp_len_t *)&in->rx_ts_len;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_ts_len) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_ts_len = *tmp;
    }
    {
        const vtss_phy_ts_fifo_mode_t *tmp = (const vtss_phy_ts_fifo_mode_t *)&in->tx_fifo_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.tx_fifo_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tx_fifo_mode = *tmp;
    }
    {
        const vtss_phy_ts_fifo_timestamp_len_t *tmp = (const vtss_phy_ts_fifo_timestamp_len_t *)&in->tx_ts_len;
#ifdef __cplusplus
        static_assert(sizeof(out.tx_ts_len) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tx_ts_len = *tmp;
    }
    out->tx_fifo_spi_conf = in->tx_fifo_spi_conf;
    out->tx_fifo_hi_clk_cycs = in->tx_fifo_hi_clk_cycs;
    out->tx_fifo_lo_clk_cycs = in->tx_fifo_lo_clk_cycs;
#ifdef VTSS_CHIP_10G_PHY
    out->xaui_sel_8487 = in->xaui_sel_8487;
#endif  // VTSS_CHIP_10G_PHY
    {
        const vtss_phy_ts_tc_op_mode_t *tmp = (const vtss_phy_ts_tc_op_mode_t *)&in->tc_op_mode;
#ifdef __cplusplus
        static_assert(sizeof(out.tc_op_mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tc_op_mode = *tmp;
    }
    out->auto_clear_ls = in->auto_clear_ls;
    out->macsec_ena = in->macsec_ena;
    out->chk_ing_modified = in->chk_ing_modified;
    out->one_step_txfifo = in->one_step_txfifo;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ptp_message_type_t_to_mesa_phy_ts_ptp_message_type_t(const vtss_phy_ts_ptp_message_type_t *in, mesa_phy_ts_ptp_message_type_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        // skipped: VTSS_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_REQ_MSG
        // skipped: VTSS_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_RESP_MSG
        // skipped: MESA_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_REQ
        // skipped: MESA_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_RESP
        case VTSS_PHY_TS_PTP_MESSAGE_TYPE_SYNC:
            *out = MESA_PHY_TS_PTP_MESSAGE_TYPE_SYNC;
            return VTSS_RC_OK;
        case VTSS_PHY_TS_PTP_MESSAGE_TYPE_DELAY_REQ:
            *out = MESA_PHY_TS_PTP_MESSAGE_TYPE_DELAY_REQ;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_phy_ts_ptp_message_type_t_to_vtss_phy_ts_ptp_message_type_t(const mesa_phy_ts_ptp_message_type_t *in, vtss_phy_ts_ptp_message_type_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        // skipped: MESA_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_REQ
        // skipped: MESA_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_RESP
        // skipped: VTSS_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_REQ_MSG
        // skipped: VTSS_PHY_TS_PTP_MESSAGE_TYPE_PDELAY_RESP_MSG
        case MESA_PHY_TS_PTP_MESSAGE_TYPE_SYNC:
            *out = VTSS_PHY_TS_PTP_MESSAGE_TYPE_SYNC;
            return VTSS_RC_OK;
        case MESA_PHY_TS_PTP_MESSAGE_TYPE_DELAY_REQ:
            *out = VTSS_PHY_TS_PTP_MESSAGE_TYPE_DELAY_REQ;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

mesa_rc mesa_conv_vtss_serdes_mode_t_to_mesa_serdes_mode_t(const vtss_serdes_mode_t *in, mesa_serdes_mode_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        // skipped: VTSS_SERDES_MODE_SFI_KR
        // skipped: VTSS_SERDES_MODE_USXGMII
        // skipped: MESA_SERDES_MODE_SXGMII
        case VTSS_SERDES_MODE_DISABLE:
            *out = MESA_SERDES_MODE_DISABLE;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_XAUI_12G:
            *out = MESA_SERDES_MODE_XAUI_12G;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_XAUI:
            *out = MESA_SERDES_MODE_XAUI;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_RXAUI:
            *out = MESA_SERDES_MODE_RXAUI;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_RXAUI_12G:
            *out = MESA_SERDES_MODE_RXAUI_12G;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_2G5:
            *out = MESA_SERDES_MODE_2G5;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_QSGMII:
            *out = MESA_SERDES_MODE_QSGMII;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SGMII:
            *out = MESA_SERDES_MODE_SGMII;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_100FX:
            *out = MESA_SERDES_MODE_100FX;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_1000BaseX:
            *out = MESA_SERDES_MODE_1000BaseX;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SFI:
            *out = MESA_SERDES_MODE_SFI;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SFI_DAC:
            *out = MESA_SERDES_MODE_SFI_DAC;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SFI_SR:
            *out = MESA_SERDES_MODE_SFI_SR;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SFI_ZR:
            *out = MESA_SERDES_MODE_SFI_ZR;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SFI_BP:
            *out = MESA_SERDES_MODE_SFI_BP;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SFI_B2B:
            *out = MESA_SERDES_MODE_SFI_B2B;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_SFI_PR_NONE:
            *out = MESA_SERDES_MODE_SFI_PR_NONE;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_IDLE:
            *out = MESA_SERDES_MODE_IDLE;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_TEST_MODE:
            *out = MESA_SERDES_MODE_TEST_MODE;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_USGMII:
            *out = MESA_SERDES_MODE_USGMII;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_QXGMII:
            *out = MESA_SERDES_MODE_QXGMII;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_DXGMII_10G:
            *out = MESA_SERDES_MODE_DXGMII_10G;
            return VTSS_RC_OK;
        case VTSS_SERDES_MODE_DXGMII_5G:
            *out = MESA_SERDES_MODE_DXGMII_5G;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_serdes_mode_t_to_vtss_serdes_mode_t(const mesa_serdes_mode_t *in, vtss_serdes_mode_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        // skipped: MESA_SERDES_MODE_SXGMII
        // skipped: VTSS_SERDES_MODE_SFI_KR
        // skipped: VTSS_SERDES_MODE_USXGMII
        case MESA_SERDES_MODE_DISABLE:
            *out = VTSS_SERDES_MODE_DISABLE;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_XAUI_12G:
            *out = VTSS_SERDES_MODE_XAUI_12G;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_XAUI:
            *out = VTSS_SERDES_MODE_XAUI;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_RXAUI:
            *out = VTSS_SERDES_MODE_RXAUI;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_RXAUI_12G:
            *out = VTSS_SERDES_MODE_RXAUI_12G;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_2G5:
            *out = VTSS_SERDES_MODE_2G5;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_QSGMII:
            *out = VTSS_SERDES_MODE_QSGMII;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SGMII:
            *out = VTSS_SERDES_MODE_SGMII;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_100FX:
            *out = VTSS_SERDES_MODE_100FX;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_1000BaseX:
            *out = VTSS_SERDES_MODE_1000BaseX;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SFI:
            *out = VTSS_SERDES_MODE_SFI;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SFI_DAC:
            *out = VTSS_SERDES_MODE_SFI_DAC;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SFI_SR:
            *out = VTSS_SERDES_MODE_SFI_SR;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SFI_ZR:
            *out = VTSS_SERDES_MODE_SFI_ZR;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SFI_BP:
            *out = VTSS_SERDES_MODE_SFI_BP;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SFI_B2B:
            *out = VTSS_SERDES_MODE_SFI_B2B;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_SFI_PR_NONE:
            *out = VTSS_SERDES_MODE_SFI_PR_NONE;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_IDLE:
            *out = VTSS_SERDES_MODE_IDLE;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_TEST_MODE:
            *out = VTSS_SERDES_MODE_TEST_MODE;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_USGMII:
            *out = VTSS_SERDES_MODE_USGMII;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_QXGMII:
            *out = VTSS_SERDES_MODE_QXGMII;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_DXGMII_10G:
            *out = VTSS_SERDES_MODE_DXGMII_10G;
            return VTSS_RC_OK;
        case MESA_SERDES_MODE_DXGMII_5G:
            *out = VTSS_SERDES_MODE_DXGMII_5G;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_vtss_ewis_tti_mode_t_to_mesa_ewis_tti_mode_t(const vtss_ewis_tti_mode_t *in, mesa_ewis_tti_mode_t *out) /* ag.rb:1656 */
{
    switch (*in) {
        // skipped: VTSS_EWIS_TTI_MODE_MAX
        // skipped: MESA_WEIS_TTI_MODE_MAX
        case VTSS_EWIS_TTI_MODE_1:
            *out = MESA_EWIS_TTI_MODE_1;
            return VTSS_RC_OK;
        case VTSS_EWIS_TTI_MODE_16:
            *out = MESA_EWIS_TTI_MODE_16;
            return VTSS_RC_OK;
        case VTSS_EWIS_TTI_MODE_64:
            *out = MESA_EWIS_TTI_MODE_64;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_ewis_tti_mode_t_to_vtss_ewis_tti_mode_t(const mesa_ewis_tti_mode_t *in, vtss_ewis_tti_mode_t *out) /* ag.rb:1664 */
{
    switch (*in) {
        // skipped: MESA_WEIS_TTI_MODE_MAX
        // skipped: VTSS_EWIS_TTI_MODE_MAX
        case MESA_EWIS_TTI_MODE_1:
            *out = VTSS_EWIS_TTI_MODE_1;
            return VTSS_RC_OK;
        case MESA_EWIS_TTI_MODE_16:
            *out = VTSS_EWIS_TTI_MODE_16;
            return VTSS_RC_OK;
        case MESA_EWIS_TTI_MODE_64:
            *out = VTSS_EWIS_TTI_MODE_64;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_WIS)

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(const vtss_ewis_tti_t *in, mesa_ewis_tti_t *out) /* ag.rb:1656 */
{
    __RC(mesa_conv_vtss_ewis_tti_mode_t_to_mesa_ewis_tti_mode_t(&in->mode, &out->mode)); /* ag.rb:1432 */
    for (size_t i = 0; i < 64; ++i) {
        out->tti[i] = in->tti[i];
    }
    out->valid = in->valid;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_ewis_tti_t_to_vtss_ewis_tti_t(const mesa_ewis_tti_t *in, vtss_ewis_tti_t *out) /* ag.rb:1664 */
{
    __RC(mesa_conv_mesa_ewis_tti_mode_t_to_vtss_ewis_tti_mode_t(&in->mode, &out->mode)); /* ag.rb:1432 */
    for (size_t i = 0; i < 64; ++i) {
        out->tti[i] = in->tti[i];
    }
    out->valid = in->valid;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_init_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_init_t *const init)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_init_t) == sizeof(mesa_macsec_init_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_init_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_macsec_init_t *)init /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_init_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_init_t *const init)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_init_t *const init)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_init_t) == sizeof(mesa_macsec_init_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_init_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_init_t *)init /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_init_t *const init)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_secy_conf_t) == sizeof(mesa_macsec_secy_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_add((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_secy_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_conf_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_secy_conf_t) == sizeof(mesa_macsec_secy_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_update((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_secy_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_conf_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_secy_conf_t) == sizeof(mesa_macsec_secy_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_secy_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_conf_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_del((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_conf_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_controlled_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_controlled_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_controlled_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_controlled_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_bool_t *const enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_controlled_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_controlled_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_bool_t *const enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_port_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_secy_port_status_t) == sizeof(mesa_macsec_secy_port_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_port_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_secy_port_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_port_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_port_get_next(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_port_t *const search_macsec_port, mesa_macsec_port_t *const found_macsec_port)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_port_get_next((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_macsec_port_t *)search_macsec_port /* ag.rb:1844 */, (vtss_macsec_port_t *)found_macsec_port /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_port_get_next(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_port_t *const search_macsec_port, mesa_macsec_port_t *const found_macsec_port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_add((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sc_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const mesa_macsec_rx_sc_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_rx_sc_conf_t) == sizeof(mesa_macsec_rx_sc_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_update((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, (const vtss_macsec_rx_sc_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const mesa_macsec_rx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_rx_sc_conf_t) == sizeof(mesa_macsec_rx_sc_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_get_conf((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, (vtss_macsec_rx_sc_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_get_next(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const search_sci, mesa_macsec_sci_t *const found_sci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_get_next((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)search_sci /* ag.rb:1844 */, (vtss_macsec_sci_t *)found_sci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sc_get_next(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const search_sci, mesa_macsec_sci_t *const found_sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_del((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_rx_sc_status_t) == sizeof(mesa_macsec_rx_sc_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, (vtss_macsec_rx_sc_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_set(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sc_set(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tx_sc_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tx_sc_conf_t) == sizeof(mesa_macsec_tx_sc_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_update((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_tx_sc_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tx_sc_conf_t) == sizeof(mesa_macsec_tx_sc_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_get_conf((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_tx_sc_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_del((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tx_sc_status_t) == sizeof(mesa_macsec_tx_sc_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_tx_sc_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn, const mesa_macsec_sak_t *const sak)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, lowest_pn, (const vtss_macsec_sak_t *)sak /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn, const mesa_macsec_sak_t *const sak)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, uint32_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, lowest_pn, (vtss_macsec_sak_t *)sak /* ag.rb:1844 */, active); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, uint32_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_activate((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_disable((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_del((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_lowest_pn_update((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, lowest_pn); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_rx_sa_status_t) == sizeof(mesa_macsec_rx_sa_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, (vtss_macsec_rx_sa_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_seca_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, *((const vtss_macsec_pkt_num_t *)&lowest_pn) /* ag.rb:1849 */, (const vtss_macsec_sak_t *)sak /* ag.rb:1844 */, (const vtss_macsec_ssci_t *)ssci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_pkt_num_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_seca_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, (vtss_macsec_pkt_num_t *)lowest_pn /* ag.rb:1844 */, (vtss_macsec_sak_t *)sak /* ag.rb:1844 */, active, (vtss_macsec_ssci_t *)ssci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_pkt_num_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_seca_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_seca_lowest_pn_update((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, *((const vtss_macsec_pkt_num_t *)&lowest_pn) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_seca_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const uint32_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an, next_pn, confidentiality, (const vtss_macsec_sak_t *)sak /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const uint32_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, uint32_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an, next_pn, confidentiality, (vtss_macsec_sak_t *)sak /* ag.rb:1844 */, active); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, uint32_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_activate((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_disable((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_del((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tx_sa_status_t) == sizeof(mesa_macsec_tx_sa_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an, (vtss_macsec_tx_sa_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const mesa_macsec_pkt_num_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_seca_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an, *((const vtss_macsec_pkt_num_t *)&next_pn) /* ag.rb:1849 */, confidentiality, (const vtss_macsec_sak_t *)sak /* ag.rb:1844 */, (const vtss_macsec_ssci_t *)ssci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const mesa_macsec_pkt_num_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_pkt_num_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_seca_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an, (vtss_macsec_pkt_num_t *)next_pn /* ag.rb:1844 */, confidentiality, (vtss_macsec_sak_t *)sak /* ag.rb:1844 */, active, (vtss_macsec_ssci_t *)ssci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_pkt_num_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_controlled_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_secy_port_counters_t) == sizeof(mesa_macsec_secy_port_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_controlled_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_secy_port_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_controlled_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_uncontrolled_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_uncontrolled_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_uncontrolled_counters_t) == sizeof(mesa_macsec_uncontrolled_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_uncontrolled_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_uncontrolled_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_uncontrolled_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_uncontrolled_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_common_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_common_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_common_counters_t) == sizeof(mesa_macsec_common_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_common_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_common_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_common_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_common_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_cap_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_secy_cap_t *const cap)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_secy_cap_t) == sizeof(mesa_macsec_secy_cap_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_cap_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_secy_cap_t *)cap /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_cap_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_secy_cap_t *const cap)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_secy_counters_t) == sizeof(mesa_macsec_secy_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_secy_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_counters_update(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_counters_update((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_counters_update(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_rx_sc_counters_t) == sizeof(mesa_macsec_rx_sc_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, (vtss_macsec_rx_sc_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tx_sc_counters_t) == sizeof(mesa_macsec_tx_sc_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_tx_sc_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tx_sa_counters_t) == sizeof(mesa_macsec_tx_sa_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an, (vtss_macsec_tx_sa_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_tx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_rx_sa_counters_t) == sizeof(mesa_macsec_rx_sa_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, (vtss_macsec_rx_sa_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_control_frame_match_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_control_frame_match_conf_t *const conf, uint32_t *const rule_id)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_control_frame_match_conf_t) == sizeof(mesa_macsec_control_frame_match_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_control_frame_match_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_macsec_control_frame_match_conf_t *)conf /* ag.rb:1844 */, rule_id); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_control_frame_match_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_control_frame_match_conf_t *const conf, uint32_t *const rule_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_control_frame_match_conf_del(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t rule_id)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_control_frame_match_conf_del((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, rule_id); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_control_frame_match_conf_del(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t rule_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_control_frame_match_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_control_frame_match_conf_t *const conf, uint32_t rule_id)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_control_frame_match_conf_t) == sizeof(mesa_macsec_control_frame_match_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_control_frame_match_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_control_frame_match_conf_t *)conf /* ag.rb:1844 */, rule_id); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_control_frame_match_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_control_frame_match_conf_t *const conf, uint32_t rule_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_pattern_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, const mesa_macsec_match_pattern_t *const pattern)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_direction_t) == sizeof(mesa_macsec_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_match_action_t) == sizeof(mesa_macsec_match_action_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_match_pattern_t) == sizeof(mesa_macsec_match_pattern_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_pattern_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, *((const vtss_macsec_direction_t *)&direction) /* ag.rb:1849 */, *((const vtss_macsec_match_action_t *)&action) /* ag.rb:1849 */, (const vtss_macsec_match_pattern_t *)pattern /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_pattern_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, const mesa_macsec_match_pattern_t *const pattern)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_pattern_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_direction_t) == sizeof(mesa_macsec_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_match_action_t) == sizeof(mesa_macsec_match_action_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_pattern_del((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, *((const vtss_macsec_direction_t *)&direction) /* ag.rb:1849 */, *((const vtss_macsec_match_action_t *)&action) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_pattern_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_pattern_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, mesa_macsec_match_pattern_t *const pattern)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_direction_t) == sizeof(mesa_macsec_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_match_action_t) == sizeof(mesa_macsec_match_action_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_match_pattern_t) == sizeof(mesa_macsec_match_pattern_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_pattern_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, *((const vtss_macsec_direction_t *)&direction) /* ag.rb:1849 */, *((const vtss_macsec_match_action_t *)&action) /* ag.rb:1849 */, (vtss_macsec_match_pattern_t *)pattern /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_pattern_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, mesa_macsec_match_pattern_t *const pattern)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_default_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_default_action_policy_t *const policy)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_default_action_policy_t) == sizeof(mesa_macsec_default_action_policy_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_default_action_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_macsec_default_action_policy_t *)policy /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_default_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_default_action_policy_t *const policy)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_default_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_default_action_policy_t *const policy)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_default_action_policy_t) == sizeof(mesa_macsec_default_action_policy_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_default_action_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_default_action_policy_t *)policy /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_default_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_default_action_policy_t *const policy)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_bypass_mode_t *const bypass)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_bypass_mode_t) == sizeof(mesa_macsec_bypass_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_bypass_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_macsec_bypass_mode_t *)bypass /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_bypass_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_bypass_mode_t *const bypass)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_bypass_mode_t *const bypass)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_bypass_mode_t) == sizeof(mesa_macsec_bypass_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_bypass_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_bypass_mode_t *)bypass /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_bypass_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_bypass_mode_t *const bypass)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_tag_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tag_bypass_t tag)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tag_bypass_t) == sizeof(mesa_macsec_tag_bypass_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_bypass_tag_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, *((const vtss_macsec_tag_bypass_t *)&tag) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_bypass_tag_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tag_bypass_t tag)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_tag_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tag_bypass_t *const tag)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_tag_bypass_t) == sizeof(mesa_macsec_tag_bypass_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_bypass_tag_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (vtss_macsec_tag_bypass_t *)tag /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_bypass_tag_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tag_bypass_t *const tag)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_mtu_t *const mtu_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_mtu_t) == sizeof(mesa_macsec_mtu_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_mtu_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_macsec_mtu_t *)mtu_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_mtu_t *const mtu_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mtu_t * mtu_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_mtu_t) == sizeof(mesa_macsec_mtu_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_mtu_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_mtu_t *)mtu_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mtu_t * mtu_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_frame_capture_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_frame_capture_t capture)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_frame_capture_t) == sizeof(mesa_macsec_frame_capture_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_frame_capture_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_macsec_frame_capture_t *)&capture) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_frame_capture_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_frame_capture_t capture)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_frame_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t buf_length, uint32_t *const return_length, uint8_t *const frame)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_frame_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, buf_length, return_length, frame); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_frame_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t buf_length, uint32_t *const return_length, uint8_t *const frame)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_event_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_event_t) == sizeof(mesa_macsec_event_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_event_enable_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_macsec_event_t *)&ev_mask) /* ag.rb:1849 */, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_event_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_event_t) == sizeof(mesa_macsec_event_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_event_enable_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_event_t *)ev_mask /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_event_t) == sizeof(mesa_macsec_event_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_event_poll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_event_t *)ev_mask /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_seq_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t threshold)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_event_seq_threshold_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, threshold); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_event_seq_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_seq_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const threshold)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_event_seq_threshold_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, threshold); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_event_seq_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mmd, const uint32_t addr, uint32_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_csr_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, mmd, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mmd, const uint32_t addr, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t mmd, const uint32_t addr, const uint32_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_csr_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, mmd, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t mmd, const uint32_t addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_rc_dbg_counters_t *const counters)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_rc_dbg_counters_t) == sizeof(mesa_macsec_rc_dbg_counters_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_dbg_counter_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_rc_dbg_counters_t *)counters /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_dbg_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_rc_dbg_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_hmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{ /* ag.rb:1822 */
    vtss_macsec_mac_counters_t __counters;
    memset(&__counters, 0, sizeof(__counters));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_macsec_hmac_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__counters, clear); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_macsec_mac_counters_t_to_mesa_macsec_mac_counters_t(&__counters, counters)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_macsec_hmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_lmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{ /* ag.rb:1822 */
    vtss_macsec_mac_counters_t __counters;
    memset(&__counters, 0, sizeof(__counters));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_macsec_lmac_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__counters, clear); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_macsec_mac_counters_t_to_mesa_macsec_mac_counters_t(&__counters, counters)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_macsec_lmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_is_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * capable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_is_capable((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, capable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_is_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * capable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_dbg_reg_dump((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, pr); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_dbg_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_lmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_lmac_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_lmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_hmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_hmac_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_hmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_debug_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_debug_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_debug_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_common_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_common_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_common_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_uncontrolled_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_uncontrolled_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_uncontrolled_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_controlled_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_controlled_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_controlled_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rxsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rxsa_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rxsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rxsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rxsc_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rxsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_txsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_txsa_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_txsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_txsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_txsc_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_txsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_secy_counters_clear((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_secy_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_port_enable_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_port_enable_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, status); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_port_enable_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rxsa_an_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_bool_t * status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_rxsa_an_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, status); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_rxsa_an_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_bool_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_mac_block_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const mtu_value, mesa_bool_t *const mtu_tag_check)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_mac_block_mtu_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, mtu_value, mtu_tag_check); /* ag.rb:1952*/
}
#else
mesa_rc mesa_mac_block_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const mtu_value, mesa_bool_t *const mtu_tag_check)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_mac_block_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mtu_value, const mesa_bool_t mtu_tag_check)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_mac_block_mtu_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, mtu_value, mtu_tag_check); /* ag.rb:1952*/
}
#else
mesa_rc mesa_mac_block_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mtu_value, const mesa_bool_t mtu_tag_check)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_fcbuf_frame_gap_comp_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t frm_gap)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_fcbuf_frame_gap_comp_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, frm_gap); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_fcbuf_frame_gap_comp_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t frm_gap)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_fcb_block_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_dbg_fcb_block_reg_dump((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, pr); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_dbg_fcb_block_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_frm_match_handling_ctrl_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, pr); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_dbg_frm_match_handling_ctrl_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_update_seq_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, uint16_t an, mesa_bool_t egr, const mesa_bool_t disable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_dbg_update_seq_set((const vtss_inst_t)inst /* ag.rb:1847 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1849 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1844 */, an, egr, disable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_dbg_update_seq_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, uint16_t an, mesa_bool_t egr, const mesa_bool_t disable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_egr_intr_sa_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_port_t *const port, uint16_t *const an)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_macsec_egr_intr_sa_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_macsec_port_t *)port /* ag.rb:1844 */, an); /* ag.rb:1952*/
}
#else
mesa_rc mesa_macsec_egr_intr_sa_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_port_t *const port, uint16_t *const an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_init_parm_t *const init_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_init_parm_t) == sizeof(mesa_phy_10g_init_parm_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_init((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_init_parm_t *)init_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_init_parm_t *const init_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_mode_t *const mode)
{ /* ag.rb:1822 */
    vtss_phy_10g_mode_t __mode;
    memset(&__mode, 0, sizeof(__mode));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_10g_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__mode); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_phy_10g_mode_t_to_mesa_phy_10g_mode_t(&__mode, mode)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_10g_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_mode_t *const mode)
{ /* ag.rb:1822 */
    vtss_phy_10g_mode_t __mode;
    memset(&__mode, 0, sizeof(__mode));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_phy_10g_mode_t_to_vtss_phy_10g_mode_t(mode, &__mode)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_phy_10g_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__mode); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ib_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ib_conf_t *const ib_conf, mesa_bool_t is_host)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_ib_conf_t) == sizeof(mesa_phy_10g_ib_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_ib_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_ib_conf_t *)ib_conf /* ag.rb:1844 */, is_host); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_ib_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ib_conf_t *const ib_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ib_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_ib_conf_t *const ib_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_ib_conf_t) == sizeof(mesa_phy_10g_ib_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_ib_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, is_host, (vtss_phy_10g_ib_conf_t *)ib_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_ib_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_ib_conf_t *const ib_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ib_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ib_status_t *const ib_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_ib_status_t) == sizeof(mesa_phy_10g_ib_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_ib_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_ib_status_t *)ib_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_ib_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ib_status_t *const ib_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_apc_conf_t *const apc_conf, const mesa_bool_t is_host)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_apc_conf_t) == sizeof(mesa_phy_10g_apc_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_apc_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_apc_conf_t *)apc_conf /* ag.rb:1844 */, is_host); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_apc_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_apc_conf_t *const apc_conf, const mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_conf_t *const apc_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_apc_conf_t) == sizeof(mesa_phy_10g_apc_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_apc_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, is_host, (vtss_phy_10g_apc_conf_t *)apc_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_apc_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_conf_t *const apc_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_status_t *const apc_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_apc_status_t) == sizeof(mesa_phy_10g_apc_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_apc_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, is_host, (vtss_phy_10g_apc_status_t *)apc_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_apc_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_status_t *const apc_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_restart(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_apc_restart((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, is_host); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_apc_restart(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_jitter_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_jitter_conf_t) == sizeof(mesa_phy_10g_jitter_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_jitter_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_jitter_conf_t *)jitter_conf /* ag.rb:1844 */, is_host); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_jitter_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_jitter_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t * jitter_conf, mesa_bool_t is_host)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_jitter_conf_t) == sizeof(mesa_phy_10g_jitter_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_jitter_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_jitter_conf_t *)jitter_conf /* ag.rb:1844 */, is_host); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_jitter_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t * jitter_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_jitter_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_jitter_conf_t) == sizeof(mesa_phy_10g_jitter_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_jitter_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_jitter_conf_t *)jitter_conf /* ag.rb:1844 */, is_host); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_jitter_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_fc_buffer_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_fc_buffer_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_fc_buffer_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_synce_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const synce_clkout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_synce_clkout_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, synce_clkout); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_synce_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_synce_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_synce_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t synce_clkout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_synce_clkout_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, synce_clkout); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_synce_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_synce_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_xfp_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const xfp_clkout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_xfp_clkout_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, xfp_clkout); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_xfp_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_xfp_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_xfp_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t xfp_clkout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_xfp_clkout_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, xfp_clkout); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_xfp_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_xfp_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_rxckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_rxckout_conf_t *const rxckout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_rxckout_conf_t) == sizeof(mesa_phy_10g_rxckout_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_rxckout_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_rxckout_conf_t *)rxckout /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_rxckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_rxckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_rxckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_rxckout_conf_t *const rxckout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_rxckout_conf_t) == sizeof(mesa_phy_10g_rxckout_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_rxckout_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_rxckout_conf_t *)rxckout /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_rxckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_rxckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_txckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_txckout_conf_t *const txckout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_txckout_conf_t) == sizeof(mesa_phy_10g_txckout_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_txckout_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_txckout_conf_t *)txckout /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_txckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_txckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_txckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_txckout_conf_t *const txckout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_txckout_conf_t) == sizeof(mesa_phy_10g_txckout_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_txckout_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_txckout_conf_t *)txckout /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_txckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_txckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_srefclk_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_srefclk_mode_t *const srefclk)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_srefclk_mode_t) == sizeof(mesa_phy_10g_srefclk_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_srefclk_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_srefclk_mode_t *)srefclk /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_srefclk_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_srefclk_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_srefclk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_srefclk_mode_t *const srefclk)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_srefclk_mode_t) == sizeof(mesa_phy_10g_srefclk_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_srefclk_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_srefclk_mode_t *)srefclk /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_srefclk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_srefclk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_sckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_sckout_conf_t *const sckout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_sckout_conf_t) == sizeof(mesa_phy_10g_sckout_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_sckout_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_sckout_conf_t *)sckout /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_sckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_sckout_conf_t *const sckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_sckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_sckout_conf_t *const sckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_ckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ckout_conf_t *const ckout)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_ckout_conf_t) == sizeof(mesa_phy_10g_ckout_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_ckout_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_ckout_conf_t *)ckout /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_ckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ckout_conf_t *const ckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_ckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ckout_conf_t *const ckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_line_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_line_clk_conf_t) == sizeof(mesa_phy_10g_line_clk_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_line_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_line_clk_conf_t *)line_clk /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_line_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_line_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_host_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_host_clk_conf_t) == sizeof(mesa_phy_10g_host_clk_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_host_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_host_clk_conf_t *)host_clk /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_host_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_host_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_line_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_line_clk_conf_t) == sizeof(mesa_phy_10g_line_clk_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_line_recvrd_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_line_clk_conf_t *)line_clk /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_line_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_line_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_host_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_host_clk_conf_t) == sizeof(mesa_phy_10g_host_clk_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_host_recvrd_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_host_clk_conf_t *)host_clk /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_host_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_host_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_lane_sync_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_lane_sync_conf_t *const lane_sync)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_lane_sync_conf_t) == sizeof(mesa_phy_10g_lane_sync_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_lane_sync_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_lane_sync_conf_t *)lane_sync /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_lane_sync_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_lane_sync_conf_t *const lane_sync)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_debug_register_dump((const vtss_inst_t)inst /* ag.rb:1847 */, pr, clear, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_base_kr_train_aneg_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_train_aneg_t) == sizeof(mesa_phy_10g_base_kr_train_aneg_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_train_aneg_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_base_kr_train_aneg_t *)kr_tr_aneg /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_base_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_train_aneg_t) == sizeof(mesa_phy_10g_base_kr_train_aneg_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_train_aneg_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_base_kr_train_aneg_t *)kr_tr_aneg /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_base_host_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_train_aneg_t) == sizeof(mesa_phy_10g_base_kr_train_aneg_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_base_host_kr_train_aneg_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_base_kr_train_aneg_t *)kr_tr_aneg /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_base_host_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_base_host_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t direction, mesa_phy_10g_base_kr_status_t *const kr_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_status_t) == sizeof(mesa_phy_10g_base_kr_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_kr_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, direction, (vtss_phy_10g_base_kr_status_t *)kr_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t direction, mesa_phy_10g_base_kr_status_t *const kr_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1965 */
#else
mesa_rc mesa_phy_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t direction, mesa_phy_10g_base_kr_status_t *const kr_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_base_kr_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_base_kr_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_host_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_host_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_base_kr_host_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_host_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_host_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_base_kr_host_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ob_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ob_status_t *const ob_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_ob_status_t) == sizeof(mesa_phy_10g_ob_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_ob_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_ob_status_t *)ob_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_ob_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ob_status_t *const ob_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_status_t) == sizeof(mesa_phy_10g_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_serdes_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_serdes_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_serdes_status_t) == sizeof(mesa_phy_10g_serdes_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_serdes_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_serdes_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_serdes_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_serdes_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_clause_37_status_get(const mesa_inst_t inst, mesa_port_no_t port_no, mesa_phy_10g_clause_37_cmn_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_clause_37_cmn_status_t) == sizeof(mesa_phy_10g_clause_37_cmn_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_clause_37_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_clause_37_cmn_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_clause_37_status_get(const mesa_inst_t inst, mesa_port_no_t port_no, mesa_phy_10g_clause_37_cmn_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_clause_37_control_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_clause_37_control_t *const control)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_clause_37_control_t) == sizeof(mesa_phy_10g_clause_37_control_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_clause_37_control_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_clause_37_control_t *)control /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_clause_37_control_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_clause_37_control_t *const control)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_clause_37_control_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_clause_37_control_t *const control)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_clause_37_control_t) == sizeof(mesa_phy_10g_clause_37_control_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_clause_37_control_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_clause_37_control_t *)control /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_clause_37_control_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_clause_37_control_t *const control)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_loopback_t *const loopback)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_loopback_t) == sizeof(mesa_phy_10g_loopback_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_loopback_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_loopback_t *)loopback /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_loopback_t *const loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_loopback_t *const loopback)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_loopback_t) == sizeof(mesa_phy_10g_loopback_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_loopback_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_loopback_t *)loopback /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_loopback_t *const loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_cnt_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_cnt_t *const cnt)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_cnt_t) == sizeof(mesa_phy_10g_cnt_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_cnt_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_cnt_t *)cnt /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_cnt_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_cnt_t *const cnt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_power_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_power_t *const power)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_power_t) == sizeof(mesa_phy_10g_power_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_power_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_power_t *)power /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_power_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_power_t *const power)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_power_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_power_t *const power)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_power_t) == sizeof(mesa_phy_10g_power_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_power_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_power_t *)power /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_power_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_power_t *const power)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_bool_t mesa_phy_10G_is_valid(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10G_is_valid((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_failover_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_failover_mode_t) == sizeof(mesa_phy_10g_failover_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_failover_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_failover_mode_t *)mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_failover_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_failover_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_failover_mode_t) == sizeof(mesa_phy_10g_failover_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_failover_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_failover_mode_t *)mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_failover_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_auto_failover_set(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_auto_failover_conf_t) == sizeof(mesa_phy_10g_auto_failover_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_auto_failover_set((const vtss_inst_t)inst /* ag.rb:1847 */, (vtss_phy_10g_auto_failover_conf_t *)mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_auto_failover_set(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_auto_failover_get(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_auto_failover_conf_t) == sizeof(mesa_phy_10g_auto_failover_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_auto_failover_get((const vtss_inst_t)inst /* ag.rb:1847 */, (vtss_phy_10g_auto_failover_conf_t *)mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_auto_failover_get(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_vscope_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_vscope_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_vscope_conf_t) == sizeof(mesa_phy_10g_vscope_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_vscope_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_10g_vscope_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_vscope_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_vscope_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_vscope_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_vscope_conf_t) == sizeof(mesa_phy_10g_vscope_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_vscope_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_vscope_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_vscope_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_vscope_scan_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_scan_status_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_vscope_scan_status_t) == sizeof(mesa_phy_10g_vscope_scan_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_vscope_scan_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_vscope_scan_status_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_vscope_scan_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_scan_status_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_generator_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_generator_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_generator_conf_t) == sizeof(mesa_phy_10g_prbs_generator_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_generator_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1849 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1849 */, (vtss_phy_10g_prbs_generator_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_generator_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_generator_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_generator_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_generator_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_generator_conf_t) == sizeof(mesa_phy_10g_prbs_generator_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_generator_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1849 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1849 */, (const vtss_phy_10g_prbs_generator_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_generator_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_generator_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_monitor_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_monitor_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_monitor_conf_t) == sizeof(mesa_phy_10g_prbs_monitor_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_monitor_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1849 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1849 */, (vtss_phy_10g_prbs_monitor_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_monitor_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_monitor_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_monitor_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_monitor_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_monitor_conf_t) == sizeof(mesa_phy_10g_prbs_monitor_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_monitor_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1849 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1849 */, (const vtss_phy_10g_prbs_monitor_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_monitor_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_monitor_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_monitor_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_bool_t reset, mesa_phy_10g_prbs_monitor_status_t *const mon_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_monitor_status_t) == sizeof(mesa_phy_10g_prbs_monitor_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_monitor_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1849 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1849 */, reset, (vtss_phy_10g_prbs_monitor_status_t *)mon_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_monitor_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_bool_t reset, mesa_phy_10g_prbs_monitor_status_t *const mon_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_gen_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_gen_conf_t) == sizeof(mesa_phy_10g_prbs_gen_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_gen_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_prbs_gen_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_gen_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_gen_conf_t) == sizeof(mesa_phy_10g_prbs_gen_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_gen_conf((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_prbs_gen_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_mon_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_mon_conf_t) == sizeof(mesa_phy_10g_prbs_mon_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_mon_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_prbs_mon_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_mon_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_prbs_mon_conf_t) == sizeof(mesa_phy_10g_prbs_mon_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_mon_conf((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_prbs_mon_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_prbs_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pkt_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_gen_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_pkt_gen_conf_t) == sizeof(mesa_phy_10g_pkt_gen_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_pkt_gen_conf((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_pkt_gen_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_pkt_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_gen_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pkt_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ts_rd, mesa_phy_10g_pkt_mon_conf_t *const conf, mesa_phy_10g_timestamp_val_t *const conf_ts)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_pkt_mon_conf_t) == sizeof(mesa_phy_10g_pkt_mon_conf_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_timestamp_val_t) == sizeof(mesa_phy_10g_timestamp_val_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_pkt_mon_conf((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ts_rd, (vtss_phy_10g_pkt_mon_conf_t *)conf /* ag.rb:1844 */, (vtss_phy_10g_timestamp_val_t *)conf_ts /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_pkt_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ts_rd, mesa_phy_10g_pkt_mon_conf_t *const conf, mesa_phy_10g_timestamp_val_t *const conf_ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pkt_mon_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_mon_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_pkt_mon_conf_t) == sizeof(mesa_phy_10g_pkt_mon_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_pkt_mon_counters_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_pkt_mon_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_pkt_mon_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_mon_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_id_t *const phy_id)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_id_t) == sizeof(mesa_phy_10g_id_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_id_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_id_t *)phy_id /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_id_t *const phy_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_gpio_10g_gpio_mode_t *const mode)
{ /* ag.rb:1822 */
    vtss_gpio_10g_gpio_mode_t __mode;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    vtss_phy_10g_gpio_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, &__mode);  /* ag.rb:1938 */ // get-before-set
    __RC(mesa_conv_mesa_gpio_10g_gpio_mode_t_to_vtss_gpio_10g_gpio_mode_t(mode, &__mode)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_phy_10g_gpio_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, &__mode); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_gpio_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_gpio_10g_gpio_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_gpio_10g_gpio_mode_t *const mode)
{ /* ag.rb:1822 */
    vtss_gpio_10g_gpio_mode_t __mode;
    memset(&__mode, 0, sizeof(__mode));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_10g_gpio_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, &__mode); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_gpio_10g_gpio_mode_t_to_mesa_gpio_10g_gpio_mode_t(&__mode, mode)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_10g_gpio_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_gpio_10g_gpio_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_bool_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_gpio_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_gpio_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_bool_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_bool_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_gpio_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_gpio_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_bool_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_event_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_event_enable_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_event_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_event_enable_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_extended_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_extended_event_enable_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ex_ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_extended_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_event_poll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pcs_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_pcs_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ex_events); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_pcs_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_extended_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_extended_event_poll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ex_events); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_extended_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_extended_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_extnd_event_t ex_ev_mask, const mesa_bool_t extnd_enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_extended_event_enable_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ex_ev_mask, extnd_enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_extended_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_extnd_event_t ex_ev_mask, const mesa_bool_t extnd_enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_poll_1sec(const mesa_inst_t inst)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_poll_1sec((const vtss_inst_t)inst /* ag.rb:1847 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_poll_1sec(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_edc_fw_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_fw_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_fw_status_t) == sizeof(mesa_phy_10g_fw_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_edc_fw_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_fw_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_edc_fw_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_fw_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, uint32_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_csr_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, dev, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, const uint32_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_csr_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, dev, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_warm_start_10g_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_warm_start_10g_failed_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_warm_start_10g_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_sgmii_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_sgmii_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_sgmii_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, uint16_t * value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_i2c_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, uint16_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, const uint16_t * value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_i2c_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, const uint16_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_slave_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t *const i2c_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_i2c_slave_conf_t) == sizeof(mesa_phy_10g_i2c_slave_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_i2c_slave_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_i2c_slave_conf_t *)i2c_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_i2c_slave_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t *const i2c_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_slave_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t * i2c_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_10g_i2c_slave_conf_t) == sizeof(mesa_phy_10g_i2c_slave_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_10g_i2c_slave_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_10g_i2c_slave_conf_t *)i2c_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_i2c_slave_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t * i2c_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_get_user_data(const mesa_inst_t inst, const mesa_port_no_t port_no, void ** user_data)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_10g_get_user_data((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, user_data); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_10g_get_user_data(const mesa_inst_t inst, const mesa_port_no_t port_no, void ** user_data)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_pre_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_pre_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_pre_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_post_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_post_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_post_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_pre_system_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_pre_system_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_pre_system_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_reset_conf_t *const conf)
{ /* ag.rb:1822 */
    vtss_phy_reset_conf_t __conf;
    memset(&__conf, 0, sizeof(__conf));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_phy_reset_conf_t_to_vtss_phy_reset_conf_t(conf, &__conf)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_phy_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_reset_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_reset_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_reset_conf_t * conf)
{ /* ag.rb:1822 */
    vtss_phy_reset_conf_t __conf;
    memset(&__conf, 0, sizeof(__conf));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_reset_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_phy_reset_conf_t_to_mesa_phy_reset_conf_t(&__conf, conf)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_reset_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_reset_conf_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_chip_temp_get(const mesa_inst_t inst, const mesa_port_no_t port_no, int16_t *const temp)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_chip_temp_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, temp); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_chip_temp_get(const mesa_inst_t inst, const mesa_port_no_t port_no, int16_t *const temp)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_chip_temp_init(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_chip_temp_init((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_chip_temp_init(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_t *const conf)
{ /* ag.rb:1822 */
    vtss_phy_conf_t __conf;
    memset(&__conf, 0, sizeof(__conf));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_phy_conf_t_to_mesa_phy_conf_t(&__conf, conf)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_t *const conf)
{ /* ag.rb:1822 */
    vtss_phy_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    vtss_phy_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf);  /* ag.rb:1938 */ // get-before-set
    __RC(mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(conf, &__conf)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_phy_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_port_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_cl37_lp_abil_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_cl37_lp_abil_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_port_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_cl37_lp_abil_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_type_t * phy_id)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_type_t) == sizeof(mesa_phy_type_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_id_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_type_t *)phy_id /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_type_t * phy_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ring_resiliency_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ring_resiliency_conf_t) == sizeof(mesa_phy_ring_resiliency_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ring_resiliency_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_ring_resiliency_conf_t *)ring_rslnt_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ring_resiliency_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ring_resiliency_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ring_resiliency_conf_t) == sizeof(mesa_phy_ring_resiliency_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ring_resiliency_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_ring_resiliency_conf_t *)ring_rslnt_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ring_resiliency_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_1g_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_conf_1g_t) == sizeof(mesa_phy_conf_1g_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_conf_1g_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_conf_1g_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_conf_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_1g_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_1g_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_1g_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_conf_1g_t) == sizeof(mesa_phy_conf_1g_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_conf_1g_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_conf_1g_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_conf_1g_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_1g_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_status_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_status_1g_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_status_1g_t) == sizeof(mesa_phy_status_1g_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_status_1g_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_status_1g_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_status_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_status_1g_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_power_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_conf_t *const conf)
{ /* ag.rb:1822 */
    vtss_phy_power_conf_t __conf;
    memset(&__conf, 0, sizeof(__conf));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_power_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_phy_power_conf_t_to_mesa_phy_power_conf_t(&__conf, conf)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_power_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_power_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_power_conf_t *const conf)
{ /* ag.rb:1822 */
    vtss_phy_power_conf_t __conf;
    memset(&__conf, 0, sizeof(__conf));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_phy_power_conf_t_to_vtss_phy_power_conf_t(conf, &__conf)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_phy_power_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_power_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_power_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_power_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_power_status_t) == sizeof(mesa_phy_power_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_power_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_power_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_power_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_clock_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, const mesa_phy_clock_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_clock_conf_t) == sizeof(mesa_phy_clock_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_clock_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, clock_port, (const vtss_phy_clock_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_clock_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, const mesa_phy_clock_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_clock_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, mesa_phy_clock_conf_t *const conf, mesa_port_no_t *const clock_source)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_clock_conf_t) == sizeof(mesa_phy_clock_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_clock_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, clock_port, (vtss_phy_clock_conf_t *)conf /* ag.rb:1844 */, clock_source); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_clock_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, mesa_phy_clock_conf_t *const conf, mesa_port_no_t *const clock_source)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t *const value, uint8_t cnt, mesa_bool_t word_access)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_i2c_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, i2c_mux, i2c_reg_addr, i2c_device_addr, value, cnt, word_access); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t *const value, uint8_t cnt, mesa_bool_t word_access)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t * value, uint8_t cnt, mesa_bool_t word_access)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_i2c_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, i2c_mux, i2c_reg_addr, i2c_device_addr, value, cnt, word_access); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t * value, uint8_t cnt, mesa_bool_t word_access)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, uint16_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, uint16_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_read_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t page, const uint32_t addr, uint16_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_read_page((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, page, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_read_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t page, const uint32_t addr, uint16_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mmd_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_mmd_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, devad, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_mmd_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mmd_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_mmd_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, devad, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_mmd_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_write_masked(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value, const uint16_t mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_write_masked((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, addr, value, mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_write_masked(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value, const uint16_t mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_write_masked_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t page, const uint16_t addr, const uint16_t value, const uint16_t mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_write_masked_page((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, page, addr, value, mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_write_masked_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t page, const uint16_t addr, const uint16_t value, const uint16_t mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_gpio_mode(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, const mesa_phy_gpio_mode_t mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_gpio_mode_t) == sizeof(mesa_phy_gpio_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_gpio_mode((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, *((const vtss_phy_gpio_mode_t *)&mode) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_gpio_mode(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, const mesa_phy_gpio_mode_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_gpio_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t * value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_gpio_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_gpio_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_gpio_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_gpio_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, gpio_no, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_gpio_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
#if VTSS_PHY_OPT_VERIPHY
mesa_rc mesa_phy_veriphy_start(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_veriphy_start((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, mode); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_veriphy_start(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_PHY_OPT_VERIPHY /* ag.rb:1965 */
#else
mesa_rc mesa_phy_veriphy_start(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
#if VTSS_PHY_OPT_VERIPHY
mesa_rc mesa_phy_veriphy_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_veriphy_result_t *const result)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_veriphy_result_t) == sizeof(mesa_phy_veriphy_result_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_veriphy_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_veriphy_result_t *)result /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_veriphy_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_veriphy_result_t *const result)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_PHY_OPT_VERIPHY /* ag.rb:1965 */
#else
mesa_rc mesa_phy_veriphy_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_veriphy_result_t *const result)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_led_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_mode_select_t led_mode_select)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_led_mode_select_t) == sizeof(mesa_phy_led_mode_select_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_led_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_led_mode_select_t *)&led_mode_select) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_led_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_mode_select_t led_mode_select)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_led_intensity_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_intensity intensity)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_led_intensity_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, intensity); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_led_intensity_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_intensity intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_led_intensity_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_intensity intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_led_intensity_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_led_intensity * intensity)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_led_intensity_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, intensity); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_led_intensity_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_led_intensity * intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_led_intensity_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_led_intensity * intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_enhanced_led_control_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_enhanced_led_control_t conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_enhanced_led_control_t) == sizeof(mesa_phy_enhanced_led_control_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_enhanced_led_control_init((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_enhanced_led_control_t *)&conf) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_enhanced_led_control_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_enhanced_led_control_t conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_enhanced_led_control_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_enhanced_led_control_t conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_enhanced_led_control_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_enhanced_led_control_t * conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_enhanced_led_control_t) == sizeof(mesa_phy_enhanced_led_control_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_enhanced_led_control_init_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_enhanced_led_control_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_enhanced_led_control_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_enhanced_led_control_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_enhanced_led_control_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_enhanced_led_control_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_coma_mode_disable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_coma_mode_disable((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_coma_mode_disable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_coma_mode_enable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_coma_mode_enable((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_coma_mode_enable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_port_eee_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * eee_capable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_port_eee_capable((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, eee_capable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_port_eee_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * eee_capable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_ena(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_eee_ena((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_eee_ena(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_eee_conf_t * conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_eee_conf_t) == sizeof(mesa_phy_eee_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_eee_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_eee_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_eee_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_eee_conf_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_eee_conf_t conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_eee_conf_t) == sizeof(mesa_phy_eee_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_eee_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_eee_conf_t *)&conf) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_eee_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_eee_conf_t conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_power_save_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * rx_in_power_save_state, mesa_bool_t * tx_in_power_save_state)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_eee_power_save_state_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, rx_in_power_save_state, tx_in_power_save_state); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_eee_power_save_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * rx_in_power_save_state, mesa_bool_t * tx_in_power_save_state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_link_partner_advertisements_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * advertisement)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_eee_link_partner_advertisements_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, advertisement); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_eee_link_partner_advertisements_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * advertisement)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_event_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_event_enable_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_event_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t * ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_event_enable_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t * ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_event_poll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_squelch_workaround(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_squelch_workaround((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_squelch_workaround(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_csr_wr(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, const uint32_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_csr_wr((const vtss_inst_t)inst /* ag.rb:1847 */, page, port_no, target, csr_reg_addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_csr_wr(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_csr_rd(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_csr_rd((const vtss_inst_t)inst /* ag.rb:1847 */, page, port_no, target, csr_reg_addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_csr_rd(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_statistic_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_statistic_t * statistics)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_statistic_t) == sizeof(mesa_phy_statistic_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_statistic_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_statistic_t *)statistics /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_statistic_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_statistic_t * statistics)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_do_page_chk_set(const mesa_inst_t inst, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_do_page_chk_set((const vtss_inst_t)inst /* ag.rb:1847 */, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_do_page_chk_set(const mesa_inst_t inst, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_do_page_chk_get(const mesa_inst_t inst, mesa_bool_t * enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_do_page_chk_get((const vtss_inst_t)inst /* ag.rb:1847 */, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_do_page_chk_get(const mesa_inst_t inst, mesa_bool_t * enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t loopback)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_loopback_t) == sizeof(mesa_phy_loopback_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_loopback_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((vtss_phy_loopback_t *)&loopback) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t * loopback)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_loopback_t) == sizeof(mesa_phy_loopback_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_loopback_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_loopback_t *)loopback /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t * loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_is_8051_crc_ok(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t code_length, uint16_t expected_crc)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_is_8051_crc_ok((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, code_length, expected_crc); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_is_8051_crc_ok(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t code_length, uint16_t expected_crc)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_cfg_ob_post0(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_cfg_ob_post0((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_cfg_ob_post0(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_cfg_ib_cterm(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ib_cterm_ena, const uint8_t ib_eq_mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_cfg_ib_cterm((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ib_cterm_ena, ib_eq_mode); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_cfg_ib_cterm(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ib_cterm_ena, const uint8_t ib_eq_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes6g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_rcpll_status_t) == sizeof(mesa_rcpll_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_serdes6g_rcpll_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_rcpll_status_t *)rcpll_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_serdes6g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes1g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_rcpll_status_t) == sizeof(mesa_rcpll_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_serdes1g_rcpll_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_rcpll_status_t *)rcpll_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_serdes1g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_lcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_lcpll_status_t * lcpll_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_lcpll_status_t) == sizeof(mesa_lcpll_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_lcpll_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_lcpll_status_t *)lcpll_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_lcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_lcpll_status_t * lcpll_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
void mesa_phy_reg_decode_status(mesa_port_no_t port_no, uint16_t lp_auto_neg_advertisment_reg, uint16_t lp_1000base_t_status_reg, uint16_t mii_status_reg, const mesa_phy_conf_t phy_setup, mesa_port_status_t *const status)
{ /* ag.rb:1822 */
    vtss_phy_conf_t __phy_setup;
    memset(&__phy_setup, 0, sizeof(__phy_setup));
#ifdef __cplusplus
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(&phy_setup, &__phy_setup) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_phy_reg_decode_status(port_no, lp_auto_neg_advertisment_reg, lp_1000base_t_status_reg, mii_status_reg, __phy_setup, (vtss_port_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_flowcontrol_decode_status(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t lp_auto_neg_advertisment_reg, const mesa_phy_conf_t phy_setup, mesa_port_status_t *const status)
{ /* ag.rb:1822 */
    vtss_phy_conf_t __phy_setup;

    memset(&__phy_setup, 0, sizeof(__phy_setup));

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(&phy_setup, &__phy_setup)) /* ag.rb:1893 */; /* ag.rb:1941 */

    return vtss_phy_flowcontrol_decode_status((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, lp_auto_neg_advertisment_reg, __phy_setup, (vtss_port_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_flowcontrol_decode_status(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t lp_auto_neg_advertisment_reg, const mesa_phy_conf_t phy_setup, mesa_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_stat_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_debug_stat_print((const vtss_inst_t)inst /* ag.rb:1847 */, pr, port_no, print_hdr); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_debug_stat_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_warm_start_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_warm_start_failed_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_warm_start_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_phyinfo_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_debug_phyinfo_print((const vtss_inst_t)inst /* ag.rb:1847 */, pr, port_no, print_hdr); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_debug_phyinfo_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_debug_register_dump((const vtss_inst_t)inst /* ag.rb:1847 */, pr, clear, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_detect_base_ports(const mesa_inst_t inst)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_detect_base_ports((const vtss_inst_t)inst /* ag.rb:1847 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_detect_base_ports(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ext_connector_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t lpback)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ext_connector_loopback((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, lpback); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ext_connector_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t lpback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes_sgmii_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_serdes_sgmii_loopback((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, mode); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_serdes_sgmii_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes_fmedia_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_serdes_fmedia_loopback((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, mode); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_serdes_fmedia_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_regdump_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_port_no_t page_no, const mesa_bool_t print_hdr)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_debug_regdump_print((const vtss_inst_t)inst /* ag.rb:1847 */, pr, port_no, page_no, print_hdr); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_debug_regdump_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_port_no_t page_no, const mesa_bool_t print_hdr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_wol_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_wol_enable((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_wol_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_wol_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_wol_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_wol_conf_t) == sizeof(mesa_phy_wol_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_wol_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_wol_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_wol_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_wol_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_wol_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_wol_conf_t *const conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_wol_conf_t) == sizeof(mesa_phy_wol_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_wol_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_wol_conf_t *)conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_wol_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_wol_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_reset_lcpll(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_reset_lcpll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_reset_lcpll(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_post_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_post0, uint8_t * ob_post1)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_post_rd((vtss_inst_t)inst /* ag.rb:1847 */, port_no, ob_post0, ob_post1); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_sd6g_ob_post_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_post0, uint8_t * ob_post1)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_post_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_post0, const uint8_t ob_post1)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_post_wr((vtss_inst_t)inst /* ag.rb:1847 */, port_no, ob_post0, ob_post1); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_sd6g_ob_post_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_post0, const uint8_t ob_post1)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_lev_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_level)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_lev_rd((vtss_inst_t)inst /* ag.rb:1847 */, port_no, ob_level); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_sd6g_ob_lev_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_level)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_lev_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_level)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_lev_wr((vtss_inst_t)inst /* ag.rb:1847 */, port_no, ob_level); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_sd6g_ob_lev_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_level)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mac_media_inhibit_odd_start(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t mac_inhibit, const mesa_bool_t media_inhibit)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_mac_media_inhibit_odd_start((vtss_inst_t)inst /* ag.rb:1847 */, port_no, mac_inhibit, media_inhibit); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_mac_media_inhibit_odd_start(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t mac_inhibit, const mesa_bool_t media_inhibit)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_fefi_get(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_fefi_mode_t * fefi)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_fefi_mode_t) == sizeof(mesa_fefi_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_fefi_get((vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_fefi_mode_t *)fefi /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_fefi_get(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_fefi_mode_t * fefi)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_fefi_set(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_fefi_mode_t fefi)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_fefi_mode_t) == sizeof(mesa_fefi_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_fefi_set((vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_fefi_mode_t *)&fefi) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_fefi_set(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_fefi_mode_t fefi)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_fefi_detect(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * fefi_detect)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_fefi_detect((vtss_inst_t)inst /* ag.rb:1847 */, port_no, fefi_detect); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_fefi_detect(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * fefi_detect)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mse_100m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mse)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_mse_100m_get((vtss_inst_t)inst /* ag.rb:1847 */, port_no, mse); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_mse_100m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mse)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mse_1000m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mseA, uint32_t * mseB, uint32_t * mseC, uint32_t * mseD)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_mse_1000m_get((vtss_inst_t)inst /* ag.rb:1847 */, port_no, mseA, mseB, mseC, mseD); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_mse_1000m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mseA, uint32_t * mseB, uint32_t * mseC, uint32_t * mseD)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_read_tr_addr(mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t tr_addr, uint16_t * tr_lower, uint16_t * tr_upper)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_read_tr_addr((vtss_inst_t)inst /* ag.rb:1847 */, port_no, tr_addr, tr_lower, tr_upper); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_read_tr_addr(mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t tr_addr, uint16_t * tr_lower, uint16_t * tr_upper)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_is_viper_revB(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * is_viper_revB)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_is_viper_revB((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, is_viper_revB); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_is_viper_revB(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * is_viper_revB)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ext_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ext_event_poll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ext_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_firmware_update(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t *const fw, uint32_t *const len)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_firmware_update((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, fw, len); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_firmware_update(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t *const fw, uint32_t *const len)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_macsec_csr_sd6g_rd(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_macsec_csr_sd6g_rd((vtss_inst_t)inst /* ag.rb:1847 */, port_no, target, csr_reg_addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_macsec_csr_sd6g_rd(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_macsec_csr_sd6g_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_macsec_csr_sd6g_wr((vtss_inst_t)inst /* ag.rb:1847 */, port_no, target, csr_reg_addr, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_macsec_csr_sd6g_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_alt_clock_saved_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const saved)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_alt_clock_saved_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, saved); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_alt_clock_saved_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const saved)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_alt_clock_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_alt_clock_mode_t) == sizeof(mesa_phy_ts_alt_clock_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_alt_clock_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_ts_alt_clock_mode_t *)phy_alt_clock_mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_alt_clock_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_alt_clock_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_alt_clock_mode_t) == sizeof(mesa_phy_ts_alt_clock_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_alt_clock_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_ts_alt_clock_mode_t *)phy_alt_clock_mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_alt_clock_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_pps_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_pps_conf_t) == sizeof(mesa_phy_ts_pps_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_pps_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_ts_pps_conf_t *)phy_pps_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_pps_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_pps_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_pps_conf_t) == sizeof(mesa_phy_ts_pps_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_pps_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_ts_pps_conf_t *)phy_pps_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_pps_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_ingress_latency_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, latency); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_ingress_latency_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, latency); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_egress_latency_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, latency); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_egress_latency_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, latency); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_path_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const path_delay)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_path_delay_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, path_delay); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_path_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const path_delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_path_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const path_delay)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_path_delay_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, path_delay); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_path_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const path_delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_delay_asymmetry_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const delay_asym)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_delay_asymmetry_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, delay_asym); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_delay_asymmetry_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const delay_asym)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_delay_asymmetry_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const delay_asym)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_delay_asymmetry_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, delay_asym); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_delay_asymmetry_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const delay_asym)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_timestamp_t *const ts)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_timestamp_t) == sizeof(mesa_phy_timestamp_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ptptime_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_timestamp_t *)ts /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ptptime_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_set_done(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_ptptime_set_done((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ptptime_set_done(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_arm(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_ptptime_arm((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ptptime_arm(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_timestamp_t) == sizeof(mesa_phy_timestamp_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ptptime_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_timestamp_t *)ts /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_load_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_timestamp_t) == sizeof(mesa_phy_timestamp_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_load_ptptime_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_timestamp_t *)ts /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_load_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_sertod_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_sertod_conf_t *const sertod_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_sertod_conf_t) == sizeof(mesa_phy_ts_sertod_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_sertod_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_ts_sertod_conf_t *)sertod_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_sertod_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_sertod_conf_t *const sertod_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_sertod_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_sertod_conf_t *const sertod_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_sertod_conf_t) == sizeof(mesa_phy_ts_sertod_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_sertod_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_ts_sertod_conf_t *)sertod_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_sertod_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_sertod_conf_t *const sertod_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_loadpulse_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t *const delay)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_loadpulse_delay_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, delay); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_loadpulse_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t *const delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_loadpulse_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const delay)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_loadpulse_delay_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, delay); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_loadpulse_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_clock_rateadj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_scaled_ppb_t *const adj)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_clock_rateadj_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, adj); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_clock_rateadj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_scaled_ppb_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_clock_rateadj_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_scaled_ppb_t *const adj)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_clock_rateadj_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, adj); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_clock_rateadj_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_scaled_ppb_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_adj1ns(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t incr)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_ptptime_adj1ns((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, incr); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ptptime_adj1ns(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t incr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_timeofday_offset_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const int32_t offset)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_timeofday_offset_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, offset); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_timeofday_offset_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const int32_t offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ongoing_adjustment(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_todadj_status_t *const ongoing_adjustment)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_todadj_status_t) == sizeof(mesa_phy_ts_todadj_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ongoing_adjustment((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_ts_todadj_status_t *)ongoing_adjustment /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ongoing_adjustment(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_todadj_status_t *const ongoing_adjustment)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ltc_freq_synth_t) == sizeof(mesa_phy_ltc_freq_synth_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ltc_freq_synth_pulse_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_ltc_freq_synth_t *)ltc_freq_synthesis /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ltc_freq_synth_t) == sizeof(mesa_phy_ltc_freq_synth_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ltc_freq_synth_pulse_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_ltc_freq_synth_t *)ltc_freq_synthesis /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_daisy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_daisy_chain_conf_t *const daisy_chain)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_daisy_chain_conf_t) == sizeof(mesa_phy_daisy_chain_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_daisy_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_daisy_chain_conf_t *)daisy_chain /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_daisy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */
#else
mesa_rc mesa_phy_daisy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_daisy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_daisy_chain_conf_t *const daisy_chain)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_daisy_chain_conf_t) == sizeof(mesa_phy_daisy_chain_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_daisy_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_daisy_chain_conf_t *)daisy_chain /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_daisy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1965 */
#else
mesa_rc mesa_phy_daisy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_sig_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_sig_mask_t sig_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_fifo_sig_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, sig_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_fifo_sig_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_sig_mask_t sig_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_sig_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_fifo_sig_mask_t *const sig_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_fifo_sig_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, sig_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_fifo_sig_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_fifo_sig_mask_t *const sig_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_empty(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_fifo_empty((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_fifo_empty(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_read_install(const mesa_inst_t inst, mesa_phy_ts_fifo_read rd_cb, void * cntxt)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_fifo_read) == sizeof(mesa_phy_ts_fifo_read), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_fifo_read_install((const vtss_inst_t)inst /* ag.rb:1847 */, *((vtss_phy_ts_fifo_read *)&rd_cb) /* ag.rb:1849 */, cntxt); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_fifo_read_install(const mesa_inst_t inst, mesa_phy_ts_fifo_read rd_cb, void * cntxt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_read_cb_get(const mesa_inst_t inst, mesa_phy_ts_fifo_read * rd_cb, void ** cntxt)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_fifo_read) == sizeof(mesa_phy_ts_fifo_read), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_fifo_read_cb_get((const vtss_inst_t)inst /* ag.rb:1847 */, (vtss_phy_ts_fifo_read *)rd_cb /* ag.rb:1844 */, cntxt); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_fifo_read_cb_get(const mesa_inst_t inst, mesa_phy_ts_fifo_read * rd_cb, void ** cntxt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{ /* ag.rb:1822 */
    vtss_phy_ts_encap_t __encap_type;

    memset(&__encap_type, 0, sizeof(__encap_type));

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_match_t) == sizeof(mesa_phy_ts_engine_flow_match_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(&encap_type, &__encap_type)) /* ag.rb:1893 */; /* ag.rb:1941 */

    return vtss_phy_ts_ingress_engine_init((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, __encap_type, flow_st_index, flow_end_index, *((const vtss_phy_ts_engine_flow_match_t *)&flow_match_mode) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{ /* ag.rb:1822 */
    vtss_phy_ts_eng_init_conf_t __init_conf;

    memset(&__init_conf, 0, sizeof(__init_conf));

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    mesa_rc rc = vtss_phy_ts_ingress_engine_init_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, &__init_conf); /* ag.rb:1946 */

    __RC(mesa_conv_vtss_phy_ts_eng_init_conf_t_to_mesa_phy_ts_eng_init_conf_t(&__init_conf, init_conf)) /* ag.rb:1893 */; /* ag.rb:1948 */

    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_ts_ingress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{ /* ag.rb:1822 */
    vtss_phy_ts_encap_t __encap_type;

    memset(&__encap_type, 0, sizeof(__encap_type));

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_match_t) == sizeof(mesa_phy_ts_engine_flow_match_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(&encap_type, &__encap_type)) /* ag.rb:1893 */; /* ag.rb:1941 */

    return vtss_phy_ts_egress_engine_init((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, __encap_type, flow_st_index, flow_end_index, *((const vtss_phy_ts_engine_flow_match_t *)&flow_match_mode) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{ /* ag.rb:1822 */
    vtss_phy_ts_eng_init_conf_t __init_conf;

    memset(&__init_conf, 0, sizeof(__init_conf));

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    mesa_rc rc = vtss_phy_ts_egress_engine_init_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, &__init_conf); /* ag.rb:1946 */

    __RC(mesa_conv_vtss_phy_ts_eng_init_conf_t_to_mesa_phy_ts_eng_init_conf_t(&__init_conf, init_conf)) /* ag.rb:1893 */; /* ag.rb:1948 */

    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_ts_egress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_clear((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (const vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (const vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_action_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (const vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_action_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_ingress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_action_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (const vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_action_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, (vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_egress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_phy_ts_event_t ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_event_enable_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_phy_ts_event_t ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_event_enable_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_event_poll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, status); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_stats_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_stats_t *const statistics)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_stats_t) == sizeof(mesa_phy_ts_stats_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_stats_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_phy_ts_stats_t *)statistics /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_stats_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_stats_t *const statistics)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_correction_overflow_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const ingr_overflow, mesa_bool_t *const egr_overflow)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_correction_overflow_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ingr_overflow, egr_overflow); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_correction_overflow_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const ingr_overflow, mesa_bool_t *const egr_overflow)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const enable)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_init_conf_t *const conf)
{ /* ag.rb:1822 */
    vtss_phy_ts_init_conf_t __conf;
    memset(&__conf, 0, sizeof(__conf));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_phy_ts_init_conf_t_to_vtss_phy_ts_init_conf_t(conf, &__conf)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_phy_ts_init((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__conf); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_init_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const init_done, mesa_phy_ts_init_conf_t *const conf)
{ /* ag.rb:1822 */
    vtss_phy_ts_init_conf_t __conf;
    memset(&__conf, 0, sizeof(__conf));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_ts_init_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, init_done, &__conf); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_phy_ts_init_conf_t_to_mesa_phy_ts_init_conf_t(&__conf, conf)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_phy_ts_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const init_done, mesa_phy_ts_init_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_nphase_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_nphase_sampler_t sampler, mesa_phy_ts_nphase_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_nphase_sampler_t) == sizeof(mesa_phy_ts_nphase_sampler_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_nphase_status_t) == sizeof(mesa_phy_ts_nphase_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_nphase_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, *((vtss_phy_ts_nphase_sampler_t *)&sampler) /* ag.rb:1849 */, (vtss_phy_ts_nphase_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_nphase_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_nphase_sampler_t sampler, mesa_phy_ts_nphase_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_CHIP_10G_PHY)
mesa_rc mesa_phy_ts_phy_oper_mode_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_ts_phy_oper_mode_change((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_phy_oper_mode_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_CHIP_10G_PHY) /* ag.rb:1965 */
#else
mesa_rc mesa_phy_ts_phy_oper_mode_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_1588_csr_reg_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, const uint32_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_1588_csr_reg_write((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, blk_id, csr_address, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_1588_csr_reg_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, const uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_1588_csr_reg_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, uint32_t *const value)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_phy_1588_csr_reg_read((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, blk_id, csr_address, value); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_1588_csr_reg_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_viper_fifo_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_conf_t * fifo_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_fifo_conf_t) == sizeof(mesa_phy_ts_fifo_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_phy_ts_viper_fifo_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_phy_ts_fifo_conf_t *)fifo_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_viper_fifo_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_conf_t * fifo_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_flow_clear_cf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ingress, const mesa_phy_ts_engine_t eng_id, uint8_t act_id, const mesa_phy_ts_ptp_message_type_t msgtype)
{ /* ag.rb:1822 */
    vtss_phy_ts_ptp_message_type_t __msgtype;

    memset(&__msgtype, 0, sizeof(__msgtype));

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_phy_ts_ptp_message_type_t_to_vtss_phy_ts_ptp_message_type_t(&msgtype, &__msgtype)) /* ag.rb:1893 */; /* ag.rb:1941 */

    return vtss_phy_ts_flow_clear_cf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, ingress, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1849 */, act_id, __msgtype); /* ag.rb:1952*/
}
#else
mesa_rc mesa_phy_ts_flow_clear_cf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ingress, const mesa_phy_ts_engine_t eng_id, uint8_t act_id, const mesa_phy_ts_ptp_message_type_t msgtype)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_event_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_mask)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_ewis_event_enable((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable, ev_mask); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_event_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_event_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_ewis_event_poll((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, status); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_event_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_event_force(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_force)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_ewis_event_force((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, enable, ev_force); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_event_force(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_force)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_static_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_static_conf_t *const stat_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_static_conf_t) == sizeof(mesa_ewis_static_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_static_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_static_conf_t *)stat_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_static_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_static_conf_t *const stat_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_force_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_force_mode_t *const force_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_force_mode_t) == sizeof(mesa_ewis_force_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_force_conf_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_force_mode_t *)force_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_force_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_force_mode_t *const force_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_force_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_force_mode_t *const force_conf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_force_mode_t) == sizeof(mesa_ewis_force_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_force_conf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_force_mode_t *)force_conf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_force_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_force_mode_t *const force_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_t *const tx_oh)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_tx_oh_t) == sizeof(mesa_ewis_tx_oh_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_tx_oh_t *)tx_oh /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_tx_oh_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_t *const tx_oh)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_t *const tx_oh)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_tx_oh_t) == sizeof(mesa_ewis_tx_oh_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_tx_oh_t *)tx_oh /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_tx_oh_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_t *const tx_oh)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_passthru_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_tx_oh_passthru_t) == sizeof(mesa_ewis_tx_oh_passthru_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_passthru_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_tx_oh_passthru_t *)tx_oh_passthru /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_tx_oh_passthru_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_passthru_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_tx_oh_passthru_t) == sizeof(mesa_ewis_tx_oh_passthru_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_passthru_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_tx_oh_passthru_t *)tx_oh_passthru /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_tx_oh_passthru_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_mode_t *const mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_mode_t) == sizeof(mesa_ewis_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_mode_t *)mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_mode_t *const mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_mode_t) == sizeof(mesa_ewis_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_mode_t *)mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    return vtss_ewis_reset((const vtss_inst_t)inst /* ag.rb:1847 */, port_no); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_cons_act_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_cons_act_t *const cons_act)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_cons_act_t) == sizeof(mesa_ewis_cons_act_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_cons_act_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_cons_act_t *)cons_act /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_cons_act_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_cons_act_t *const cons_act)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_cons_act_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_cons_act_t *const cons_act)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_cons_act_t) == sizeof(mesa_ewis_cons_act_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_cons_act_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_cons_act_t *)cons_act /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_cons_act_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_cons_act_t *const cons_act)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_section_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{ /* ag.rb:1822 */
    vtss_ewis_tti_t __txti;
    memset(&__txti, 0, sizeof(__txti));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_ewis_tti_t_to_vtss_ewis_tti_t(txti, &__txti)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_ewis_section_txti_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__txti); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_section_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_section_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{ /* ag.rb:1822 */
    vtss_ewis_tti_t __txti;
    memset(&__txti, 0, sizeof(__txti));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_section_txti_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__txti); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__txti, txti)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_ewis_section_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_exp_sl_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_sl_conf_t *const sl)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_sl_conf_t) == sizeof(mesa_ewis_sl_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_exp_sl_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_sl_conf_t *)sl /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_exp_sl_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_sl_conf_t *const sl)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_path_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{ /* ag.rb:1822 */
    vtss_ewis_tti_t __txti;
    memset(&__txti, 0, sizeof(__txti));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_ewis_tti_t_to_vtss_ewis_tti_t(txti, &__txti)) /* ag.rb:1893 */; /* ag.rb:1941 */
    return vtss_ewis_path_txti_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__txti); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_path_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_path_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{ /* ag.rb:1822 */
    vtss_ewis_tti_t __txti;
    memset(&__txti, 0, sizeof(__txti));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_path_txti_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__txti); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__txti, txti)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_ewis_path_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_test_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_test_conf_t *const test_mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_test_conf_t) == sizeof(mesa_ewis_test_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_test_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_test_conf_t *)test_mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_test_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_test_conf_t *const test_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_test_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_conf_t *const test_mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_test_conf_t) == sizeof(mesa_ewis_test_conf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_test_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_test_conf_t *)test_mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_test_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_conf_t *const test_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_prbs31_err_inj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_prbs31_err_inj_t *const inj)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_prbs31_err_inj_t) == sizeof(mesa_ewis_prbs31_err_inj_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_prbs31_err_inj_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_prbs31_err_inj_t *)inj /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_prbs31_err_inj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_prbs31_err_inj_t *const inj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_test_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_status_t *const test_status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_test_status_t) == sizeof(mesa_ewis_test_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_test_counter_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_test_status_t *)test_status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_test_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_status_t *const test_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_defects_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_defects_t *const def)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_defects_t) == sizeof(mesa_ewis_defects_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_defects_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_defects_t *)def /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_defects_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_defects_t *const def)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_status_t *const status)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_status_t) == sizeof(mesa_ewis_status_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_status_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_status_t *)status /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_section_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{ /* ag.rb:1822 */
    vtss_ewis_tti_t __acti;
    memset(&__acti, 0, sizeof(__acti));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_section_acti_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__acti); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__acti, acti)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_ewis_section_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_path_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{ /* ag.rb:1822 */
    vtss_ewis_tti_t __acti;
    memset(&__acti, 0, sizeof(__acti));
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_path_acti_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, &__acti); /* ag.rb:1946 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__acti, acti)) /* ag.rb:1893 */; /* ag.rb:1948 */
    return rc; /* ag.rb:1950 */
}
#else
mesa_rc mesa_ewis_path_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_t *const counter)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_counter_t) == sizeof(mesa_ewis_counter_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_counter_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_counter_t *)counter /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_t *const counter)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_perf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_t *const perf)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_perf_t) == sizeof(mesa_ewis_perf_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_perf_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_perf_t *)perf /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_perf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_t *const perf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_counter_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_counter_threshold_t *const threshold)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_counter_threshold_t) == sizeof(mesa_ewis_counter_threshold_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_counter_threshold_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_counter_threshold_t *)threshold /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_counter_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_counter_threshold_t *const threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_counter_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_threshold_t *const threshold)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_counter_threshold_t) == sizeof(mesa_ewis_counter_threshold_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_counter_threshold_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_counter_threshold_t *)threshold /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_counter_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_threshold_t *const threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_perf_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_perf_mode_t *const perf_mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_perf_mode_t) == sizeof(mesa_ewis_perf_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_perf_mode_set((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (const vtss_ewis_perf_mode_t *)perf_mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_perf_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_perf_mode_t *const perf_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_perf_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_mode_t *const perf_mode)
{ /* ag.rb:1822 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1932 */
    static_assert(sizeof(vtss_ewis_perf_mode_t) == sizeof(mesa_ewis_perf_mode_t), "Check size"); /* ag.rb:1932 */
#endif // __cplusplus

    return vtss_ewis_perf_mode_get((const vtss_inst_t)inst /* ag.rb:1847 */, port_no, (vtss_ewis_perf_mode_t *)perf_mode /* ag.rb:1844 */); /* ag.rb:1952*/
}
#else
mesa_rc mesa_ewis_perf_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_mode_t *const perf_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1965 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_patch_settings_get(const mesa_inst_t    inst,
                                    const mesa_port_no_t port_no,
                                    const uint8_t        mcb_bus,
                                    uint8_t              *mcb_res,
                                    uint8_t              *cfg_buf,
                                    uint8_t              *stat_buf)
{
    *mcb_res = mcb_bus; // INOUT in VTSS API
    return vtss_phy_patch_settings_get((const vtss_inst_t)inst, port_no, mcb_res, cfg_buf, stat_buf);
}
#endif // VTSS_CHIP_CU_PHY

#pragma GCC diagnostic pop
