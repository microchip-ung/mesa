// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_phy_api.h"
#include <microchip/ethernet/phy/api.h>
#ifndef __MESA_H__
#define __MESA_H__
#ifdef __cplusplus
extern "C" {
#endif
inline static mesa_rc mesa_conv_vtss_inst_t_to_mesa_inst_t(const vtss_inst_t *in, mesa_inst_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_inst_t *tmp = (const mesa_inst_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_mesa_inst_t_to_vtss_inst_t(const mesa_inst_t *in, vtss_inst_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_inst_t *tmp = (const vtss_inst_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_vtss_port_speed_t_to_mesa_port_speed_t(const vtss_port_speed_t *in, mesa_port_speed_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_port_speed_t *tmp = (const mesa_port_speed_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_mesa_port_speed_t_to_vtss_port_speed_t(const mesa_port_speed_t *in, vtss_port_speed_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_port_speed_t *tmp = (const vtss_port_speed_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_media_interface_t_to_mesa_phy_media_interface_t(const vtss_phy_media_interface_t *in, mesa_phy_media_interface_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_media_interface_t *tmp = (const mesa_phy_media_interface_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_media_interface_t_to_vtss_phy_media_interface_t(const mesa_phy_media_interface_t *in, vtss_phy_media_interface_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_media_interface_t *tmp = (const vtss_phy_media_interface_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_mdi_t_to_mesa_phy_mdi_t(const vtss_phy_mdi_t *in, mesa_phy_mdi_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_mdi_t *tmp = (const mesa_phy_mdi_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_mdi_t_to_vtss_phy_mdi_t(const mesa_phy_mdi_t *in, vtss_phy_mdi_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_mdi_t *tmp = (const vtss_phy_mdi_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_power_mode_t_to_mesa_phy_power_mode_t(const vtss_phy_power_mode_t *in, mesa_phy_power_mode_t *out); /* ag.rb:1595 */
mesa_rc mesa_conv_mesa_phy_power_mode_t_to_vtss_phy_power_mode_t(const mesa_phy_power_mode_t *in, vtss_phy_power_mode_t *out); /* ag.rb:1595 */
inline static mesa_rc mesa_conv_vtss_phy_veriphy_status_t_to_mesa_phy_veriphy_status_t(const vtss_phy_veriphy_status_t *in, mesa_phy_veriphy_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_veriphy_status_t *tmp = (const mesa_phy_veriphy_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_mesa_phy_veriphy_status_t_to_vtss_phy_veriphy_status_t(const mesa_phy_veriphy_status_t *in, vtss_phy_veriphy_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_veriphy_status_t *tmp = (const vtss_phy_veriphy_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#ifdef VTSS_CHIP_CU_PHY
#if VTSS_PHY_OPT_VERIPHY
inline static mesa_rc mesa_conv_vtss_phy_veriphy_result_t_to_mesa_phy_veriphy_result_t(const vtss_phy_veriphy_result_t *in, mesa_phy_veriphy_result_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_veriphy_result_t *tmp = (const mesa_phy_veriphy_result_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_PHY_OPT_VERIPHY
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
#if VTSS_PHY_OPT_VERIPHY
inline static mesa_rc mesa_conv_mesa_phy_veriphy_result_t_to_vtss_phy_veriphy_result_t(const mesa_phy_veriphy_result_t *in, vtss_phy_veriphy_result_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_veriphy_result_t *tmp = (const vtss_phy_veriphy_result_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_PHY_OPT_VERIPHY
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_status_1g_t_to_mesa_phy_status_1g_t(const vtss_phy_status_1g_t *in, mesa_phy_status_1g_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_status_1g_t *tmp = (const mesa_phy_status_1g_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_status_1g_t_to_vtss_phy_status_1g_t(const mesa_phy_status_1g_t *in, vtss_phy_status_1g_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_status_1g_t *tmp = (const vtss_phy_status_1g_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_rgmii_conf_t_to_mesa_phy_rgmii_conf_t(const vtss_phy_rgmii_conf_t *in, mesa_phy_rgmii_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_rgmii_conf_t *tmp = (const mesa_phy_rgmii_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_rgmii_conf_t_to_vtss_phy_rgmii_conf_t(const mesa_phy_rgmii_conf_t *in, vtss_phy_rgmii_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_rgmii_conf_t *tmp = (const vtss_phy_rgmii_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_tbi_conf_t_to_mesa_phy_tbi_conf_t(const vtss_phy_tbi_conf_t *in, mesa_phy_tbi_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_tbi_conf_t *tmp = (const mesa_phy_tbi_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_tbi_conf_t_to_vtss_phy_tbi_conf_t(const mesa_phy_tbi_conf_t *in, vtss_phy_tbi_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_tbi_conf_t *tmp = (const vtss_phy_tbi_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_forced_reset_t_to_mesa_phy_forced_reset_t(const vtss_phy_forced_reset_t *in, mesa_phy_forced_reset_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_forced_reset_t *tmp = (const mesa_phy_forced_reset_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_forced_reset_t_to_vtss_phy_forced_reset_t(const mesa_phy_forced_reset_t *in, vtss_phy_forced_reset_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_forced_reset_t *tmp = (const vtss_phy_forced_reset_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_pkt_mode_t_to_mesa_phy_pkt_mode_t(const vtss_phy_pkt_mode_t *in, mesa_phy_pkt_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_pkt_mode_t *tmp = (const mesa_phy_pkt_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_pkt_mode_t_to_vtss_phy_pkt_mode_t(const mesa_phy_pkt_mode_t *in, vtss_phy_pkt_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_pkt_mode_t *tmp = (const vtss_phy_pkt_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_port_interface_t_to_mesa_port_interface_t(const vtss_port_interface_t *in, mesa_port_interface_t *out); /* ag.rb:1595 */
mesa_rc mesa_conv_mesa_port_interface_t_to_vtss_port_interface_t(const mesa_port_interface_t *in, vtss_port_interface_t *out); /* ag.rb:1595 */
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_reset_conf_t_to_mesa_phy_reset_conf_t(const vtss_phy_reset_conf_t *in, mesa_phy_reset_conf_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_mesa_phy_reset_conf_t_to_vtss_phy_reset_conf_t(const mesa_phy_reset_conf_t *in, vtss_phy_reset_conf_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_aneg_t_to_mesa_aneg_t(const vtss_aneg_t *in, mesa_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_aneg_t *tmp = (const mesa_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_mesa_aneg_t_to_vtss_aneg_t(const mesa_aneg_t *in, vtss_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_aneg_t *tmp = (const vtss_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_ciphersuite_t_to_mesa_macsec_ciphersuite_t(const vtss_macsec_ciphersuite_t *in, mesa_macsec_ciphersuite_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_ciphersuite_t *tmp = (const mesa_macsec_ciphersuite_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_ciphersuite_t_to_vtss_macsec_ciphersuite_t(const mesa_macsec_ciphersuite_t *in, vtss_macsec_ciphersuite_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_ciphersuite_t *tmp = (const vtss_macsec_ciphersuite_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_validate_frames_t_to_mesa_validate_frames_t(const vtss_validate_frames_t *in, mesa_validate_frames_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_validate_frames_t *tmp = (const mesa_validate_frames_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_validate_frames_t_to_vtss_validate_frames_t(const mesa_validate_frames_t *in, vtss_validate_frames_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_validate_frames_t *tmp = (const vtss_validate_frames_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_pkt_num_t_to_mesa_macsec_pkt_num_t(const vtss_macsec_pkt_num_t *in, mesa_macsec_pkt_num_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_pkt_num_t *tmp = (const mesa_macsec_pkt_num_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_pkt_num_t_to_vtss_macsec_pkt_num_t(const mesa_macsec_pkt_num_t *in, vtss_macsec_pkt_num_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_pkt_num_t *tmp = (const vtss_macsec_pkt_num_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_salt_t_to_mesa_macsec_salt_t(const vtss_macsec_salt_t *in, mesa_macsec_salt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_salt_t *tmp = (const mesa_macsec_salt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_salt_t_to_vtss_macsec_salt_t(const mesa_macsec_salt_t *in, vtss_macsec_salt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_salt_t *tmp = (const vtss_macsec_salt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_sak_t_to_mesa_macsec_sak_t(const vtss_macsec_sak_t *in, mesa_macsec_sak_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_sak_t *tmp = (const mesa_macsec_sak_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_sak_t_to_vtss_macsec_sak_t(const mesa_macsec_sak_t *in, vtss_macsec_sak_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_sak_t *tmp = (const vtss_macsec_sak_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_sci_t_to_mesa_macsec_sci_t(const vtss_macsec_sci_t *in, mesa_macsec_sci_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_sci_t *tmp = (const mesa_macsec_sci_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_sci_t_to_vtss_macsec_sci_t(const mesa_macsec_sci_t *in, vtss_macsec_sci_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_sci_t *tmp = (const vtss_macsec_sci_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_ssci_t_to_mesa_macsec_ssci_t(const vtss_macsec_ssci_t *in, mesa_macsec_ssci_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_ssci_t *tmp = (const mesa_macsec_ssci_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_ssci_t_to_vtss_macsec_ssci_t(const mesa_macsec_ssci_t *in, vtss_macsec_ssci_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_ssci_t *tmp = (const vtss_macsec_ssci_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_port_t_to_mesa_macsec_port_t(const vtss_macsec_port_t *in, mesa_macsec_port_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_port_t *tmp = (const mesa_macsec_port_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_port_t_to_vtss_macsec_port_t(const mesa_macsec_port_t *in, vtss_macsec_port_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_port_t *tmp = (const vtss_macsec_port_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_secy_conf_t_to_mesa_macsec_secy_conf_t(const vtss_macsec_secy_conf_t *in, mesa_macsec_secy_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_secy_conf_t *tmp = (const mesa_macsec_secy_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_secy_conf_t_to_vtss_macsec_secy_conf_t(const mesa_macsec_secy_conf_t *in, vtss_macsec_secy_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_secy_conf_t *tmp = (const vtss_macsec_secy_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_port_status_t_to_mesa_macsec_port_status_t(const vtss_macsec_port_status_t *in, mesa_macsec_port_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_port_status_t *tmp = (const mesa_macsec_port_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_port_status_t_to_vtss_macsec_port_status_t(const mesa_macsec_port_status_t *in, vtss_macsec_port_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_port_status_t *tmp = (const vtss_macsec_port_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_secy_port_status_t_to_mesa_macsec_secy_port_status_t(const vtss_macsec_secy_port_status_t *in, mesa_macsec_secy_port_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_secy_port_status_t *tmp = (const mesa_macsec_secy_port_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_secy_port_status_t_to_vtss_macsec_secy_port_status_t(const mesa_macsec_secy_port_status_t *in, vtss_macsec_secy_port_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_secy_port_status_t *tmp = (const vtss_macsec_secy_port_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_tx_sc_status_t_to_mesa_macsec_tx_sc_status_t(const vtss_macsec_tx_sc_status_t *in, mesa_macsec_tx_sc_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_tx_sc_status_t *tmp = (const mesa_macsec_tx_sc_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_tx_sc_status_t_to_vtss_macsec_tx_sc_status_t(const mesa_macsec_tx_sc_status_t *in, vtss_macsec_tx_sc_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_tx_sc_status_t *tmp = (const vtss_macsec_tx_sc_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_rx_sc_status_t_to_mesa_macsec_rx_sc_status_t(const vtss_macsec_rx_sc_status_t *in, mesa_macsec_rx_sc_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_rx_sc_status_t *tmp = (const mesa_macsec_rx_sc_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_rx_sc_status_t_to_vtss_macsec_rx_sc_status_t(const mesa_macsec_rx_sc_status_t *in, vtss_macsec_rx_sc_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_rx_sc_status_t *tmp = (const vtss_macsec_rx_sc_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_tx_sa_pn_status_t_to_mesa_macsec_tx_sa_pn_status_t(const vtss_macsec_tx_sa_pn_status_t *in, mesa_macsec_tx_sa_pn_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_tx_sa_pn_status_t *tmp = (const mesa_macsec_tx_sa_pn_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_tx_sa_pn_status_t_to_vtss_macsec_tx_sa_pn_status_t(const mesa_macsec_tx_sa_pn_status_t *in, vtss_macsec_tx_sa_pn_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_tx_sa_pn_status_t *tmp = (const vtss_macsec_tx_sa_pn_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_tx_sa_status_t_to_mesa_macsec_tx_sa_status_t(const vtss_macsec_tx_sa_status_t *in, mesa_macsec_tx_sa_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_tx_sa_status_t *tmp = (const mesa_macsec_tx_sa_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_tx_sa_status_t_to_vtss_macsec_tx_sa_status_t(const mesa_macsec_tx_sa_status_t *in, vtss_macsec_tx_sa_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_tx_sa_status_t *tmp = (const vtss_macsec_tx_sa_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_rx_sa_pn_status_t_to_mesa_macsec_rx_sa_pn_status_t(const vtss_macsec_rx_sa_pn_status_t *in, mesa_macsec_rx_sa_pn_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_rx_sa_pn_status_t *tmp = (const mesa_macsec_rx_sa_pn_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_rx_sa_pn_status_t_to_vtss_macsec_rx_sa_pn_status_t(const mesa_macsec_rx_sa_pn_status_t *in, vtss_macsec_rx_sa_pn_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_rx_sa_pn_status_t *tmp = (const vtss_macsec_rx_sa_pn_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_rx_sa_status_t_to_mesa_macsec_rx_sa_status_t(const vtss_macsec_rx_sa_status_t *in, mesa_macsec_rx_sa_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_rx_sa_status_t *tmp = (const mesa_macsec_rx_sa_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_rx_sa_status_t_to_vtss_macsec_rx_sa_status_t(const mesa_macsec_rx_sa_status_t *in, vtss_macsec_rx_sa_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_rx_sa_status_t *tmp = (const vtss_macsec_rx_sa_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_rx_sc_conf_t_to_mesa_macsec_rx_sc_conf_t(const vtss_macsec_rx_sc_conf_t *in, mesa_macsec_rx_sc_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_rx_sc_conf_t *tmp = (const mesa_macsec_rx_sc_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_rx_sc_conf_t_to_vtss_macsec_rx_sc_conf_t(const mesa_macsec_rx_sc_conf_t *in, vtss_macsec_rx_sc_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_rx_sc_conf_t *tmp = (const vtss_macsec_rx_sc_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_tx_sc_conf_t_to_mesa_macsec_tx_sc_conf_t(const vtss_macsec_tx_sc_conf_t *in, mesa_macsec_tx_sc_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_tx_sc_conf_t *tmp = (const mesa_macsec_tx_sc_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_tx_sc_conf_t_to_vtss_macsec_tx_sc_conf_t(const mesa_macsec_tx_sc_conf_t *in, vtss_macsec_tx_sc_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_tx_sc_conf_t *tmp = (const vtss_macsec_tx_sc_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_lmac_conf_t_to_mesa_macsec_lmac_conf_t(const vtss_macsec_lmac_conf_t *in, mesa_macsec_lmac_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_lmac_conf_t *tmp = (const mesa_macsec_lmac_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_lmac_conf_t_to_vtss_macsec_lmac_conf_t(const mesa_macsec_lmac_conf_t *in, vtss_macsec_lmac_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_lmac_conf_t *tmp = (const vtss_macsec_lmac_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_hmac_conf_t_to_mesa_macsec_hmac_conf_t(const vtss_macsec_hmac_conf_t *in, mesa_macsec_hmac_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_hmac_conf_t *tmp = (const mesa_macsec_hmac_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_hmac_conf_t_to_vtss_macsec_hmac_conf_t(const mesa_macsec_hmac_conf_t *in, vtss_macsec_hmac_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_hmac_conf_t *tmp = (const vtss_macsec_hmac_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_mac_conf_t_to_mesa_macsec_mac_conf_t(const vtss_macsec_mac_conf_t *in, mesa_macsec_mac_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_mac_conf_t *tmp = (const mesa_macsec_mac_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_mac_conf_t_to_vtss_macsec_mac_conf_t(const mesa_macsec_mac_conf_t *in, vtss_macsec_mac_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_mac_conf_t *tmp = (const vtss_macsec_mac_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_init_bypass_t_to_mesa_macsec_init_bypass_t(const vtss_macsec_init_bypass_t *in, mesa_macsec_init_bypass_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_init_bypass_t *tmp = (const mesa_macsec_init_bypass_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_init_bypass_t_to_vtss_macsec_init_bypass_t(const mesa_macsec_init_bypass_t *in, vtss_macsec_init_bypass_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_init_bypass_t *tmp = (const vtss_macsec_init_bypass_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_init_t_to_mesa_macsec_init_t(const vtss_macsec_init_t *in, mesa_macsec_init_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_init_t *tmp = (const mesa_macsec_init_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_init_t_to_vtss_macsec_init_t(const mesa_macsec_init_t *in, vtss_macsec_init_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_init_t *tmp = (const vtss_macsec_init_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_mtu_t_to_mesa_macsec_mtu_t(const vtss_macsec_mtu_t *in, mesa_macsec_mtu_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_mtu_t *tmp = (const mesa_macsec_mtu_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_mtu_t_to_vtss_macsec_mtu_t(const mesa_macsec_mtu_t *in, vtss_macsec_mtu_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_mtu_t *tmp = (const vtss_macsec_mtu_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_common_counters_t_to_mesa_macsec_common_counters_t(const vtss_macsec_common_counters_t *in, mesa_macsec_common_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_common_counters_t *tmp = (const mesa_macsec_common_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_common_counters_t_to_vtss_macsec_common_counters_t(const mesa_macsec_common_counters_t *in, vtss_macsec_common_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_common_counters_t *tmp = (const vtss_macsec_common_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_uncontrolled_counters_t_to_mesa_macsec_uncontrolled_counters_t(const vtss_macsec_uncontrolled_counters_t *in, mesa_macsec_uncontrolled_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_uncontrolled_counters_t *tmp = (const mesa_macsec_uncontrolled_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_uncontrolled_counters_t_to_vtss_macsec_uncontrolled_counters_t(const mesa_macsec_uncontrolled_counters_t *in, vtss_macsec_uncontrolled_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_uncontrolled_counters_t *tmp = (const vtss_macsec_uncontrolled_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_secy_port_counters_t_to_mesa_macsec_secy_port_counters_t(const vtss_macsec_secy_port_counters_t *in, mesa_macsec_secy_port_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_secy_port_counters_t *tmp = (const mesa_macsec_secy_port_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_secy_port_counters_t_to_vtss_macsec_secy_port_counters_t(const mesa_macsec_secy_port_counters_t *in, vtss_macsec_secy_port_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_secy_port_counters_t *tmp = (const vtss_macsec_secy_port_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_secy_counters_t_to_mesa_macsec_secy_counters_t(const vtss_macsec_secy_counters_t *in, mesa_macsec_secy_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_secy_counters_t *tmp = (const mesa_macsec_secy_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_secy_counters_t_to_vtss_macsec_secy_counters_t(const mesa_macsec_secy_counters_t *in, vtss_macsec_secy_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_secy_counters_t *tmp = (const vtss_macsec_secy_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_secy_cap_t_to_mesa_macsec_secy_cap_t(const vtss_macsec_secy_cap_t *in, mesa_macsec_secy_cap_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_secy_cap_t *tmp = (const mesa_macsec_secy_cap_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_secy_cap_t_to_vtss_macsec_secy_cap_t(const mesa_macsec_secy_cap_t *in, vtss_macsec_secy_cap_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_secy_cap_t *tmp = (const vtss_macsec_secy_cap_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_rx_sc_counters_t_to_mesa_macsec_rx_sc_counters_t(const vtss_macsec_rx_sc_counters_t *in, mesa_macsec_rx_sc_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_rx_sc_counters_t *tmp = (const mesa_macsec_rx_sc_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_rx_sc_counters_t_to_vtss_macsec_rx_sc_counters_t(const mesa_macsec_rx_sc_counters_t *in, vtss_macsec_rx_sc_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_rx_sc_counters_t *tmp = (const vtss_macsec_rx_sc_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_tx_sc_counters_t_to_mesa_macsec_tx_sc_counters_t(const vtss_macsec_tx_sc_counters_t *in, mesa_macsec_tx_sc_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_tx_sc_counters_t *tmp = (const mesa_macsec_tx_sc_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_tx_sc_counters_t_to_vtss_macsec_tx_sc_counters_t(const mesa_macsec_tx_sc_counters_t *in, vtss_macsec_tx_sc_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_tx_sc_counters_t *tmp = (const vtss_macsec_tx_sc_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_tx_sa_counters_t_to_mesa_macsec_tx_sa_counters_t(const vtss_macsec_tx_sa_counters_t *in, mesa_macsec_tx_sa_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_tx_sa_counters_t *tmp = (const mesa_macsec_tx_sa_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_tx_sa_counters_t_to_vtss_macsec_tx_sa_counters_t(const mesa_macsec_tx_sa_counters_t *in, vtss_macsec_tx_sa_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_tx_sa_counters_t *tmp = (const vtss_macsec_tx_sa_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_rx_sa_counters_t_to_mesa_macsec_rx_sa_counters_t(const vtss_macsec_rx_sa_counters_t *in, mesa_macsec_rx_sa_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_rx_sa_counters_t *tmp = (const mesa_macsec_rx_sa_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_rx_sa_counters_t_to_vtss_macsec_rx_sa_counters_t(const mesa_macsec_rx_sa_counters_t *in, vtss_macsec_rx_sa_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_rx_sa_counters_t *tmp = (const vtss_macsec_rx_sa_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_control_frame_match_conf_t_to_mesa_macsec_control_frame_match_conf_t(const vtss_macsec_control_frame_match_conf_t *in, mesa_macsec_control_frame_match_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_control_frame_match_conf_t *tmp = (const mesa_macsec_control_frame_match_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_control_frame_match_conf_t_to_vtss_macsec_control_frame_match_conf_t(const mesa_macsec_control_frame_match_conf_t *in, vtss_macsec_control_frame_match_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_control_frame_match_conf_t *tmp = (const vtss_macsec_control_frame_match_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_match_pattern_t_to_mesa_macsec_match_pattern_t(const vtss_macsec_match_pattern_t *in, mesa_macsec_match_pattern_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_match_pattern_t *tmp = (const mesa_macsec_match_pattern_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_match_pattern_t_to_vtss_macsec_match_pattern_t(const mesa_macsec_match_pattern_t *in, vtss_macsec_match_pattern_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_match_pattern_t *tmp = (const vtss_macsec_match_pattern_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_match_action_t_to_mesa_macsec_match_action_t(const vtss_macsec_match_action_t *in, mesa_macsec_match_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_match_action_t *tmp = (const mesa_macsec_match_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_match_action_t_to_vtss_macsec_match_action_t(const mesa_macsec_match_action_t *in, vtss_macsec_match_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_match_action_t *tmp = (const vtss_macsec_match_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_direction_t_to_mesa_macsec_direction_t(const vtss_macsec_direction_t *in, mesa_macsec_direction_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_direction_t *tmp = (const mesa_macsec_direction_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_direction_t_to_vtss_macsec_direction_t(const mesa_macsec_direction_t *in, vtss_macsec_direction_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_direction_t *tmp = (const vtss_macsec_direction_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_default_action_t_to_mesa_macsec_default_action_t(const vtss_macsec_default_action_t *in, mesa_macsec_default_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_default_action_t *tmp = (const mesa_macsec_default_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_default_action_t_to_vtss_macsec_default_action_t(const mesa_macsec_default_action_t *in, vtss_macsec_default_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_default_action_t *tmp = (const vtss_macsec_default_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_default_action_policy_t_to_mesa_macsec_default_action_policy_t(const vtss_macsec_default_action_policy_t *in, mesa_macsec_default_action_policy_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_default_action_policy_t *tmp = (const mesa_macsec_default_action_policy_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_default_action_policy_t_to_vtss_macsec_default_action_policy_t(const mesa_macsec_default_action_policy_t *in, vtss_macsec_default_action_policy_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_default_action_policy_t *tmp = (const vtss_macsec_default_action_policy_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_bypass_t_to_mesa_macsec_bypass_t(const vtss_macsec_bypass_t *in, mesa_macsec_bypass_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_bypass_t *tmp = (const mesa_macsec_bypass_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_bypass_t_to_vtss_macsec_bypass_t(const mesa_macsec_bypass_t *in, vtss_macsec_bypass_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_bypass_t *tmp = (const vtss_macsec_bypass_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_bypass_mode_t_to_mesa_macsec_bypass_mode_t(const vtss_macsec_bypass_mode_t *in, mesa_macsec_bypass_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_bypass_mode_t *tmp = (const mesa_macsec_bypass_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_bypass_mode_t_to_vtss_macsec_bypass_mode_t(const mesa_macsec_bypass_mode_t *in, vtss_macsec_bypass_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_bypass_mode_t *tmp = (const vtss_macsec_bypass_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_tag_bypass_t_to_mesa_macsec_tag_bypass_t(const vtss_macsec_tag_bypass_t *in, mesa_macsec_tag_bypass_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_tag_bypass_t *tmp = (const mesa_macsec_tag_bypass_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_tag_bypass_t_to_vtss_macsec_tag_bypass_t(const mesa_macsec_tag_bypass_t *in, vtss_macsec_tag_bypass_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_tag_bypass_t *tmp = (const vtss_macsec_tag_bypass_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_frame_capture_t_to_mesa_macsec_frame_capture_t(const vtss_macsec_frame_capture_t *in, mesa_macsec_frame_capture_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_frame_capture_t *tmp = (const mesa_macsec_frame_capture_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_frame_capture_t_to_vtss_macsec_frame_capture_t(const mesa_macsec_frame_capture_t *in, vtss_macsec_frame_capture_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_frame_capture_t *tmp = (const vtss_macsec_frame_capture_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_event_t_to_mesa_macsec_event_t(const vtss_macsec_event_t *in, mesa_macsec_event_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_event_t *tmp = (const mesa_macsec_event_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_event_t_to_vtss_macsec_event_t(const mesa_macsec_event_t *in, vtss_macsec_event_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_event_t *tmp = (const vtss_macsec_event_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_macsec_rc_dbg_counters_t_to_mesa_macsec_rc_dbg_counters_t(const vtss_macsec_rc_dbg_counters_t *in, mesa_macsec_rc_dbg_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_macsec_rc_dbg_counters_t *tmp = (const mesa_macsec_rc_dbg_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_macsec_rc_dbg_counters_t_to_vtss_macsec_rc_dbg_counters_t(const mesa_macsec_rc_dbg_counters_t *in, vtss_macsec_rc_dbg_counters_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_macsec_rc_dbg_counters_t *tmp = (const vtss_macsec_rc_dbg_counters_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_conv_vtss_macsec_mac_counters_t_to_mesa_macsec_mac_counters_t(const vtss_macsec_mac_counters_t *in, mesa_macsec_mac_counters_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_conv_mesa_macsec_mac_counters_t_to_vtss_macsec_mac_counters_t(const mesa_macsec_mac_counters_t *in, vtss_macsec_mac_counters_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_vtss_sc_inst_count_t_to_mesa_sc_inst_count_t(const vtss_sc_inst_count_t *in, mesa_sc_inst_count_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_sc_inst_count_t *tmp = (const mesa_sc_inst_count_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if defined(VTSS_FEATURE_MACSEC)
inline static mesa_rc mesa_conv_mesa_sc_inst_count_t_to_vtss_sc_inst_count_t(const mesa_sc_inst_count_t *in, vtss_sc_inst_count_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_sc_inst_count_t *tmp = (const vtss_sc_inst_count_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_MACSEC)
#if 0
mesa_rc mesa_conv_vtss_debug_info_t_to_mesa_debug_info_t(const vtss_debug_info_t *in, mesa_debug_info_t *out); /* ag.rb:1595 */
mesa_rc mesa_conv_mesa_debug_info_t_to_vtss_debug_info_t(const mesa_debug_info_t *in, vtss_debug_info_t *out); /* ag.rb:1595 */
#endif
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_oper_mode_t_to_mesa_oper_mode_t(const vtss_oper_mode_t *in, mesa_oper_mode_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_mesa_oper_mode_t_to_vtss_oper_mode_t(const mesa_oper_mode_t *in, vtss_oper_mode_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_wrefclk_t_to_mesa_wrefclk_t(const vtss_wrefclk_t *in, mesa_wrefclk_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_wrefclk_t *tmp = (const mesa_wrefclk_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_wrefclk_t_to_vtss_wrefclk_t(const mesa_wrefclk_t *in, vtss_wrefclk_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_wrefclk_t *tmp = (const vtss_wrefclk_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_sublayer_status_t_to_mesa_sublayer_status_t(const vtss_sublayer_status_t *in, mesa_sublayer_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_sublayer_status_t *tmp = (const mesa_sublayer_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_sublayer_status_t_to_vtss_sublayer_status_t(const mesa_sublayer_status_t *in, vtss_sublayer_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_sublayer_status_t *tmp = (const vtss_sublayer_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_interface_mode_to_mesa_phy_interface_mode(const vtss_phy_interface_mode *in, mesa_phy_interface_mode *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_interface_mode *tmp = (const mesa_phy_interface_mode *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_interface_mode_to_vtss_phy_interface_mode(const mesa_phy_interface_mode *in, vtss_phy_interface_mode *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_interface_mode *tmp = (const vtss_phy_interface_mode *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_recvrd_t_to_mesa_recvrd_t(const vtss_recvrd_t *in, mesa_recvrd_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_recvrd_t *tmp = (const mesa_recvrd_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_recvrd_t_to_vtss_recvrd_t(const mesa_recvrd_t *in, vtss_recvrd_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_recvrd_t *tmp = (const vtss_recvrd_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_recvrdclk_cdr_div_t_to_mesa_recvrdclk_cdr_div_t(const vtss_recvrdclk_cdr_div_t *in, mesa_recvrdclk_cdr_div_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_recvrdclk_cdr_div_t *tmp = (const mesa_recvrdclk_cdr_div_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_recvrdclk_cdr_div_t_to_vtss_recvrdclk_cdr_div_t(const mesa_recvrdclk_cdr_div_t *in, vtss_recvrdclk_cdr_div_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_recvrdclk_cdr_div_t *tmp = (const vtss_recvrdclk_cdr_div_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_srefclk_div_t_to_mesa_srefclk_div_t(const vtss_srefclk_div_t *in, mesa_srefclk_div_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_srefclk_div_t *tmp = (const mesa_srefclk_div_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_srefclk_div_t_to_vtss_srefclk_div_t(const mesa_srefclk_div_t *in, vtss_srefclk_div_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_srefclk_div_t *tmp = (const vtss_srefclk_div_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_wref_clk_div_t_to_mesa_wref_clk_div_t(const vtss_wref_clk_div_t *in, mesa_wref_clk_div_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_wref_clk_div_t *tmp = (const mesa_wref_clk_div_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_wref_clk_div_t_to_vtss_wref_clk_div_t(const mesa_wref_clk_div_t *in, vtss_wref_clk_div_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_wref_clk_div_t *tmp = (const vtss_wref_clk_div_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_apc_ib_regulator_t_to_mesa_apc_ib_regulator_t(const vtss_apc_ib_regulator_t *in, mesa_apc_ib_regulator_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_apc_ib_regulator_t *tmp = (const mesa_apc_ib_regulator_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_apc_ib_regulator_t_to_vtss_apc_ib_regulator_t(const mesa_apc_ib_regulator_t *in, vtss_apc_ib_regulator_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_apc_ib_regulator_t *tmp = (const vtss_apc_ib_regulator_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_ddr_mode_t_to_mesa_ddr_mode_t(const vtss_ddr_mode_t *in, mesa_ddr_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ddr_mode_t *tmp = (const mesa_ddr_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_ddr_mode_t_to_vtss_ddr_mode_t(const mesa_ddr_mode_t *in, vtss_ddr_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ddr_mode_t *tmp = (const vtss_ddr_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_clk_mstr_t_to_mesa_clk_mstr_t(const vtss_clk_mstr_t *in, mesa_clk_mstr_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_clk_mstr_t *tmp = (const mesa_clk_mstr_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_clk_mstr_t_to_vtss_clk_mstr_t(const mesa_clk_mstr_t *in, vtss_clk_mstr_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_clk_mstr_t *tmp = (const vtss_clk_mstr_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_rptr_rate_t_to_mesa_rptr_rate_t(const vtss_rptr_rate_t *in, mesa_rptr_rate_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_rptr_rate_t *tmp = (const mesa_rptr_rate_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_rptr_rate_t_to_vtss_rptr_rate_t(const mesa_rptr_rate_t *in, vtss_rptr_rate_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_rptr_rate_t *tmp = (const vtss_rptr_rate_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_polarity_inv_t_to_mesa_phy_10g_polarity_inv_t(const vtss_phy_10g_polarity_inv_t *in, mesa_phy_10g_polarity_inv_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_polarity_inv_t *tmp = (const mesa_phy_10g_polarity_inv_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_polarity_inv_t_to_vtss_phy_10g_polarity_inv_t(const mesa_phy_10g_polarity_inv_t *in, vtss_phy_10g_polarity_inv_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_polarity_inv_t *tmp = (const vtss_phy_10g_polarity_inv_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_media_t_to_mesa_phy_10g_media_t(const vtss_phy_10g_media_t *in, mesa_phy_10g_media_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_media_t *tmp = (const mesa_phy_10g_media_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_media_t_to_vtss_phy_10g_media_t(const mesa_phy_10g_media_t *in, vtss_phy_10g_media_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_media_t *tmp = (const vtss_phy_10g_media_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_6g_link_partner_distance_t_to_mesa_phy_6g_link_partner_distance_t(const vtss_phy_6g_link_partner_distance_t *in, mesa_phy_6g_link_partner_distance_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_6g_link_partner_distance_t *tmp = (const mesa_phy_6g_link_partner_distance_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_6g_link_partner_distance_t_to_vtss_phy_6g_link_partner_distance_t(const mesa_phy_6g_link_partner_distance_t *in, vtss_phy_6g_link_partner_distance_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_6g_link_partner_distance_t *tmp = (const vtss_phy_6g_link_partner_distance_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_clk_src_t_to_mesa_phy_10g_clk_src_t(const vtss_phy_10g_clk_src_t *in, mesa_phy_10g_clk_src_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_clk_src_t *tmp = (const mesa_phy_10g_clk_src_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_clk_src_t_to_vtss_phy_10g_clk_src_t(const mesa_phy_10g_clk_src_t *in, vtss_phy_10g_clk_src_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_clk_src_t *tmp = (const vtss_phy_10g_clk_src_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_ib_apc_op_mode_t_to_mesa_phy_10g_ib_apc_op_mode_t(const vtss_phy_10g_ib_apc_op_mode_t *in, mesa_phy_10g_ib_apc_op_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_ib_apc_op_mode_t *tmp = (const mesa_phy_10g_ib_apc_op_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_ib_apc_op_mode_t_to_vtss_phy_10g_ib_apc_op_mode_t(const mesa_phy_10g_ib_apc_op_mode_t *in, vtss_phy_10g_ib_apc_op_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_ib_apc_op_mode_t *tmp = (const vtss_phy_10g_ib_apc_op_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_ib_par_cfg_t_to_mesa_ib_par_cfg_t(const vtss_ib_par_cfg_t *in, mesa_ib_par_cfg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ib_par_cfg_t *tmp = (const mesa_ib_par_cfg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_ib_par_cfg_t_to_vtss_ib_par_cfg_t(const mesa_ib_par_cfg_t *in, vtss_ib_par_cfg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ib_par_cfg_t *tmp = (const vtss_ib_par_cfg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_ib_conf_t_to_mesa_phy_10g_ib_conf_t(const vtss_phy_10g_ib_conf_t *in, mesa_phy_10g_ib_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_ib_conf_t *tmp = (const mesa_phy_10g_ib_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_ib_conf_t_to_vtss_phy_10g_ib_conf_t(const mesa_phy_10g_ib_conf_t *in, vtss_phy_10g_ib_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_ib_conf_t *tmp = (const vtss_phy_10g_ib_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_ib_status_t_to_mesa_phy_10g_ib_status_t(const vtss_phy_10g_ib_status_t *in, mesa_phy_10g_ib_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_ib_status_t *tmp = (const mesa_phy_10g_ib_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_ib_status_t_to_vtss_phy_10g_ib_status_t(const mesa_phy_10g_ib_status_t *in, vtss_phy_10g_ib_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_ib_status_t *tmp = (const vtss_phy_10g_ib_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_apc_conf_t_to_mesa_phy_10g_apc_conf_t(const vtss_phy_10g_apc_conf_t *in, mesa_phy_10g_apc_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_apc_conf_t *tmp = (const mesa_phy_10g_apc_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_apc_conf_t_to_vtss_phy_10g_apc_conf_t(const mesa_phy_10g_apc_conf_t *in, vtss_phy_10g_apc_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_apc_conf_t *tmp = (const vtss_phy_10g_apc_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_apc_status_t_to_mesa_phy_10g_apc_status_t(const vtss_phy_10g_apc_status_t *in, mesa_phy_10g_apc_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_apc_status_t *tmp = (const mesa_phy_10g_apc_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_apc_status_t_to_vtss_phy_10g_apc_status_t(const mesa_phy_10g_apc_status_t *in, vtss_phy_10g_apc_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_apc_status_t *tmp = (const vtss_phy_10g_apc_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_serdes_status_t_to_mesa_phy_10g_serdes_status_t(const vtss_phy_10g_serdes_status_t *in, mesa_phy_10g_serdes_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_serdes_status_t *tmp = (const mesa_phy_10g_serdes_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_serdes_status_t_to_vtss_phy_10g_serdes_status_t(const mesa_phy_10g_serdes_status_t *in, vtss_phy_10g_serdes_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_serdes_status_t *tmp = (const vtss_phy_10g_serdes_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_jitter_conf_t_to_mesa_phy_10g_jitter_conf_t(const vtss_phy_10g_jitter_conf_t *in, mesa_phy_10g_jitter_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_jitter_conf_t *tmp = (const mesa_phy_10g_jitter_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_jitter_conf_t_to_vtss_phy_10g_jitter_conf_t(const mesa_phy_10g_jitter_conf_t *in, vtss_phy_10g_jitter_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_jitter_conf_t *tmp = (const vtss_phy_10g_jitter_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_channel_t_to_mesa_channel_t(const vtss_channel_t *in, mesa_channel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_channel_t *tmp = (const mesa_channel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_channel_t_to_vtss_channel_t(const mesa_channel_t *in, vtss_channel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_channel_t *tmp = (const vtss_channel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_EDC_FW_LOAD)
inline static mesa_rc mesa_conv_vtss_edc_fw_load_t_to_mesa_edc_fw_load_t(const vtss_edc_fw_load_t *in, mesa_edc_fw_load_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_edc_fw_load_t *tmp = (const mesa_edc_fw_load_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_EDC_FW_LOAD)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_EDC_FW_LOAD)
inline static mesa_rc mesa_conv_mesa_edc_fw_load_t_to_vtss_edc_fw_load_t(const mesa_edc_fw_load_t *in, vtss_edc_fw_load_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_edc_fw_load_t *tmp = (const vtss_edc_fw_load_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_EDC_FW_LOAD)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_phy_10g_mode_t_to_mesa_phy_10g_mode_t(const vtss_phy_10g_mode_t *in, mesa_phy_10g_mode_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_mesa_phy_10g_mode_t_to_vtss_phy_10g_mode_t(const mesa_phy_10g_mode_t *in, vtss_phy_10g_mode_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_init_parm_t_to_mesa_phy_10g_init_parm_t(const vtss_phy_10g_init_parm_t *in, mesa_phy_10g_init_parm_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_init_parm_t *tmp = (const mesa_phy_10g_init_parm_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_init_parm_t_to_vtss_phy_10g_init_parm_t(const mesa_phy_10g_init_parm_t *in, vtss_phy_10g_init_parm_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_init_parm_t *tmp = (const vtss_phy_10g_init_parm_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_recvrd_clkout_t_to_mesa_recvrd_clkout_t(const vtss_recvrd_clkout_t *in, mesa_recvrd_clkout_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_recvrd_clkout_t *tmp = (const mesa_recvrd_clkout_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_recvrd_clkout_t_to_vtss_recvrd_clkout_t(const mesa_recvrd_clkout_t *in, vtss_recvrd_clkout_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_recvrd_clkout_t *tmp = (const vtss_recvrd_clkout_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_rxckout_conf_t_to_mesa_phy_10g_rxckout_conf_t(const vtss_phy_10g_rxckout_conf_t *in, mesa_phy_10g_rxckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_rxckout_conf_t *tmp = (const mesa_phy_10g_rxckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_rxckout_conf_t_to_vtss_phy_10g_rxckout_conf_t(const mesa_phy_10g_rxckout_conf_t *in, vtss_phy_10g_rxckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_rxckout_conf_t *tmp = (const vtss_phy_10g_rxckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_txckout_conf_t_to_mesa_phy_10g_txckout_conf_t(const vtss_phy_10g_txckout_conf_t *in, mesa_phy_10g_txckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_txckout_conf_t *tmp = (const mesa_phy_10g_txckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_txckout_conf_t_to_vtss_phy_10g_txckout_conf_t(const mesa_phy_10g_txckout_conf_t *in, vtss_phy_10g_txckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_txckout_conf_t *tmp = (const vtss_phy_10g_txckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_srefclk_freq_t_to_mesa_phy_10g_srefclk_freq_t(const vtss_phy_10g_srefclk_freq_t *in, mesa_phy_10g_srefclk_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_srefclk_freq_t *tmp = (const mesa_phy_10g_srefclk_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_srefclk_freq_t_to_vtss_phy_10g_srefclk_freq_t(const mesa_phy_10g_srefclk_freq_t *in, vtss_phy_10g_srefclk_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_srefclk_freq_t *tmp = (const vtss_phy_10g_srefclk_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_srefclk_mode_t_to_mesa_phy_10g_srefclk_mode_t(const vtss_phy_10g_srefclk_mode_t *in, mesa_phy_10g_srefclk_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_srefclk_mode_t *tmp = (const mesa_phy_10g_srefclk_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_srefclk_mode_t_to_vtss_phy_10g_srefclk_mode_t(const mesa_phy_10g_srefclk_mode_t *in, vtss_phy_10g_srefclk_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_srefclk_mode_t *tmp = (const vtss_phy_10g_srefclk_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_ckout_freq_t_to_mesa_phy_10g_ckout_freq_t(const vtss_phy_10g_ckout_freq_t *in, mesa_phy_10g_ckout_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_ckout_freq_t *tmp = (const mesa_phy_10g_ckout_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_ckout_freq_t_to_vtss_phy_10g_ckout_freq_t(const mesa_phy_10g_ckout_freq_t *in, vtss_phy_10g_ckout_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_ckout_freq_t *tmp = (const vtss_phy_10g_ckout_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_ckout_data_sel_t_to_mesa_ckout_data_sel_t(const vtss_ckout_data_sel_t *in, mesa_ckout_data_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ckout_data_sel_t *tmp = (const mesa_ckout_data_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_ckout_data_sel_t_to_vtss_ckout_data_sel_t(const mesa_ckout_data_sel_t *in, vtss_ckout_data_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ckout_data_sel_t *tmp = (const vtss_ckout_data_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_squelch_src_t_to_mesa_phy_10g_squelch_src_t(const vtss_phy_10g_squelch_src_t *in, mesa_phy_10g_squelch_src_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_squelch_src_t *tmp = (const mesa_phy_10g_squelch_src_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_squelch_src_t_to_vtss_phy_10g_squelch_src_t(const mesa_phy_10g_squelch_src_t *in, vtss_phy_10g_squelch_src_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_squelch_src_t *tmp = (const vtss_phy_10g_squelch_src_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_clk_sel_t_to_mesa_phy_10g_clk_sel_t(const vtss_phy_10g_clk_sel_t *in, mesa_phy_10g_clk_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_clk_sel_t *tmp = (const mesa_phy_10g_clk_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_clk_sel_t_to_vtss_phy_10g_clk_sel_t(const mesa_phy_10g_clk_sel_t *in, vtss_phy_10g_clk_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_clk_sel_t *tmp = (const vtss_phy_10g_clk_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_recvrd_clk_sel_t_to_mesa_phy_10g_recvrd_clk_sel_t(const vtss_phy_10g_recvrd_clk_sel_t *in, mesa_phy_10g_recvrd_clk_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_recvrd_clk_sel_t *tmp = (const mesa_phy_10g_recvrd_clk_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_recvrd_clk_sel_t_to_vtss_phy_10g_recvrd_clk_sel_t(const mesa_phy_10g_recvrd_clk_sel_t *in, vtss_phy_10g_recvrd_clk_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_recvrd_clk_sel_t *tmp = (const vtss_phy_10g_recvrd_clk_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_ckout_sel_t_to_mesa_ckout_sel_t(const vtss_ckout_sel_t *in, mesa_ckout_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ckout_sel_t *tmp = (const mesa_ckout_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_ckout_sel_t_to_vtss_ckout_sel_t(const mesa_ckout_sel_t *in, vtss_ckout_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ckout_sel_t *tmp = (const vtss_ckout_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_ckout_conf_t_to_mesa_phy_10g_ckout_conf_t(const vtss_phy_10g_ckout_conf_t *in, mesa_phy_10g_ckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_ckout_conf_t *tmp = (const mesa_phy_10g_ckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_ckout_conf_t_to_vtss_phy_10g_ckout_conf_t(const mesa_phy_10g_ckout_conf_t *in, vtss_phy_10g_ckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_ckout_conf_t *tmp = (const vtss_phy_10g_ckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_sckout_freq_t_to_mesa_phy_10g_sckout_freq_t(const vtss_phy_10g_sckout_freq_t *in, mesa_phy_10g_sckout_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_sckout_freq_t *tmp = (const mesa_phy_10g_sckout_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_sckout_freq_t_to_vtss_phy_10g_sckout_freq_t(const mesa_phy_10g_sckout_freq_t *in, vtss_phy_10g_sckout_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_sckout_freq_t *tmp = (const vtss_phy_10g_sckout_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_sckout_conf_t_to_mesa_phy_10g_sckout_conf_t(const vtss_phy_10g_sckout_conf_t *in, mesa_phy_10g_sckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_sckout_conf_t *tmp = (const mesa_phy_10g_sckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_sckout_conf_t_to_vtss_phy_10g_sckout_conf_t(const mesa_phy_10g_sckout_conf_t *in, vtss_phy_10g_sckout_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_sckout_conf_t *tmp = (const vtss_phy_10g_sckout_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_line_clk_conf_t_to_mesa_phy_10g_line_clk_conf_t(const vtss_phy_10g_line_clk_conf_t *in, mesa_phy_10g_line_clk_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_line_clk_conf_t *tmp = (const mesa_phy_10g_line_clk_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_line_clk_conf_t_to_vtss_phy_10g_line_clk_conf_t(const mesa_phy_10g_line_clk_conf_t *in, vtss_phy_10g_line_clk_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_line_clk_conf_t *tmp = (const vtss_phy_10g_line_clk_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_vtss_phy_10g_host_clk_conf_t_to_mesa_phy_10g_host_clk_conf_t(const vtss_phy_10g_host_clk_conf_t *in, mesa_phy_10g_host_clk_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_host_clk_conf_t *tmp = (const mesa_phy_10g_host_clk_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
inline static mesa_rc mesa_conv_mesa_phy_10g_host_clk_conf_t_to_vtss_phy_10g_host_clk_conf_t(const mesa_phy_10g_host_clk_conf_t *in, vtss_phy_10g_host_clk_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_host_clk_conf_t *tmp = (const vtss_phy_10g_host_clk_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G)
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_rx_macro_t_to_mesa_phy_10g_rx_macro_t(const vtss_phy_10g_rx_macro_t *in, mesa_phy_10g_rx_macro_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_rx_macro_t *tmp = (const mesa_phy_10g_rx_macro_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_rx_macro_t_to_vtss_phy_10g_rx_macro_t(const mesa_phy_10g_rx_macro_t *in, vtss_phy_10g_rx_macro_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_rx_macro_t *tmp = (const vtss_phy_10g_rx_macro_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_tx_macro_t_to_mesa_phy_10g_tx_macro_t(const vtss_phy_10g_tx_macro_t *in, mesa_phy_10g_tx_macro_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_tx_macro_t *tmp = (const mesa_phy_10g_tx_macro_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_tx_macro_t_to_vtss_phy_10g_tx_macro_t(const mesa_phy_10g_tx_macro_t *in, vtss_phy_10g_tx_macro_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_tx_macro_t *tmp = (const vtss_phy_10g_tx_macro_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_lane_sync_conf_t_to_mesa_phy_10g_lane_sync_conf_t(const vtss_phy_10g_lane_sync_conf_t *in, mesa_phy_10g_lane_sync_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_lane_sync_conf_t *tmp = (const mesa_phy_10g_lane_sync_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_lane_sync_conf_t_to_vtss_phy_10g_lane_sync_conf_t(const mesa_phy_10g_lane_sync_conf_t *in, vtss_phy_10g_lane_sync_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_lane_sync_conf_t *tmp = (const vtss_phy_10g_lane_sync_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_ob_status_t_to_mesa_phy_10g_ob_status_t(const vtss_phy_10g_ob_status_t *in, mesa_phy_10g_ob_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_ob_status_t *tmp = (const mesa_phy_10g_ob_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_ob_status_t_to_vtss_phy_10g_ob_status_t(const mesa_phy_10g_ob_status_t *in, vtss_phy_10g_ob_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_ob_status_t *tmp = (const vtss_phy_10g_ob_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_base_kr_conf_t_to_mesa_phy_10g_base_kr_conf_t(const vtss_phy_10g_base_kr_conf_t *in, mesa_phy_10g_base_kr_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_base_kr_conf_t *tmp = (const mesa_phy_10g_base_kr_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_base_kr_conf_t_to_vtss_phy_10g_base_kr_conf_t(const mesa_phy_10g_base_kr_conf_t *in, vtss_phy_10g_base_kr_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_base_kr_conf_t *tmp = (const vtss_phy_10g_base_kr_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_base_kr_autoneg_t_to_mesa_phy_10g_base_kr_autoneg_t(const vtss_phy_10g_base_kr_autoneg_t *in, mesa_phy_10g_base_kr_autoneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_base_kr_autoneg_t *tmp = (const mesa_phy_10g_base_kr_autoneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_base_kr_autoneg_t_to_vtss_phy_10g_base_kr_autoneg_t(const mesa_phy_10g_base_kr_autoneg_t *in, vtss_phy_10g_base_kr_autoneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_base_kr_autoneg_t *tmp = (const vtss_phy_10g_base_kr_autoneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_base_kr_training_t_to_mesa_phy_10g_base_kr_training_t(const vtss_phy_10g_base_kr_training_t *in, mesa_phy_10g_base_kr_training_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_base_kr_training_t *tmp = (const mesa_phy_10g_base_kr_training_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_base_kr_training_t_to_vtss_phy_10g_base_kr_training_t(const mesa_phy_10g_base_kr_training_t *in, vtss_phy_10g_base_kr_training_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_base_kr_training_t *tmp = (const vtss_phy_10g_base_kr_training_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_base_kr_ld_adv_abil_t_to_mesa_phy_10g_base_kr_ld_adv_abil_t(const vtss_phy_10g_base_kr_ld_adv_abil_t *in, mesa_phy_10g_base_kr_ld_adv_abil_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_base_kr_ld_adv_abil_t *tmp = (const mesa_phy_10g_base_kr_ld_adv_abil_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_base_kr_ld_adv_abil_t_to_vtss_phy_10g_base_kr_ld_adv_abil_t(const mesa_phy_10g_base_kr_ld_adv_abil_t *in, vtss_phy_10g_base_kr_ld_adv_abil_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_base_kr_ld_adv_abil_t *tmp = (const vtss_phy_10g_base_kr_ld_adv_abil_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_base_kr_train_aneg_t_to_mesa_phy_10g_base_kr_train_aneg_t(const vtss_phy_10g_base_kr_train_aneg_t *in, mesa_phy_10g_base_kr_train_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_base_kr_train_aneg_t *tmp = (const mesa_phy_10g_base_kr_train_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_base_kr_train_aneg_t_to_vtss_phy_10g_base_kr_train_aneg_t(const mesa_phy_10g_base_kr_train_aneg_t *in, vtss_phy_10g_base_kr_train_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_base_kr_train_aneg_t *tmp = (const vtss_phy_10g_base_kr_train_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_kr_status_aneg_t_to_mesa_phy_10g_kr_status_aneg_t(const vtss_phy_10g_kr_status_aneg_t *in, mesa_phy_10g_kr_status_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_kr_status_aneg_t *tmp = (const mesa_phy_10g_kr_status_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_kr_status_aneg_t_to_vtss_phy_10g_kr_status_aneg_t(const mesa_phy_10g_kr_status_aneg_t *in, vtss_phy_10g_kr_status_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_kr_status_aneg_t *tmp = (const vtss_phy_10g_kr_status_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_kr_status_train_t_to_mesa_phy_10g_kr_status_train_t(const vtss_phy_10g_kr_status_train_t *in, mesa_phy_10g_kr_status_train_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_kr_status_train_t *tmp = (const mesa_phy_10g_kr_status_train_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_kr_status_train_t_to_vtss_phy_10g_kr_status_train_t(const mesa_phy_10g_kr_status_train_t *in, vtss_phy_10g_kr_status_train_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_kr_status_train_t *tmp = (const vtss_phy_10g_kr_status_train_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_kr_status_fec_t_to_mesa_phy_10g_kr_status_fec_t(const vtss_phy_10g_kr_status_fec_t *in, mesa_phy_10g_kr_status_fec_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_kr_status_fec_t *tmp = (const mesa_phy_10g_kr_status_fec_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_kr_status_fec_t_to_vtss_phy_10g_kr_status_fec_t(const mesa_phy_10g_kr_status_fec_t *in, vtss_phy_10g_kr_status_fec_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_kr_status_fec_t *tmp = (const vtss_phy_10g_kr_status_fec_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_vtss_phy_10g_base_kr_status_t_to_mesa_phy_10g_base_kr_status_t(const vtss_phy_10g_base_kr_status_t *in, mesa_phy_10g_base_kr_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_base_kr_status_t *tmp = (const mesa_phy_10g_base_kr_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
inline static mesa_rc mesa_conv_mesa_phy_10g_base_kr_status_t_to_vtss_phy_10g_base_kr_status_t(const mesa_phy_10g_base_kr_status_t *in, vtss_phy_10g_base_kr_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_base_kr_status_t *tmp = (const vtss_phy_10g_base_kr_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_FEATURE_10GBASE_KR
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_status_t_to_mesa_phy_10g_status_t(const vtss_phy_10g_status_t *in, mesa_phy_10g_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_status_t *tmp = (const mesa_phy_10g_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_status_t_to_vtss_phy_10g_status_t(const mesa_phy_10g_status_t *in, vtss_phy_10g_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_status_t *tmp = (const vtss_phy_10g_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_clause_37_remote_fault_t_to_mesa_phy_10g_clause_37_remote_fault_t(const vtss_phy_10g_clause_37_remote_fault_t *in, mesa_phy_10g_clause_37_remote_fault_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_clause_37_remote_fault_t *tmp = (const mesa_phy_10g_clause_37_remote_fault_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_clause_37_remote_fault_t_to_vtss_phy_10g_clause_37_remote_fault_t(const mesa_phy_10g_clause_37_remote_fault_t *in, vtss_phy_10g_clause_37_remote_fault_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_clause_37_remote_fault_t *tmp = (const vtss_phy_10g_clause_37_remote_fault_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_clause_37_adv_t_to_mesa_phy_10g_clause_37_adv_t(const vtss_phy_10g_clause_37_adv_t *in, mesa_phy_10g_clause_37_adv_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_clause_37_adv_t *tmp = (const mesa_phy_10g_clause_37_adv_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_clause_37_adv_t_to_vtss_phy_10g_clause_37_adv_t(const mesa_phy_10g_clause_37_adv_t *in, vtss_phy_10g_clause_37_adv_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_clause_37_adv_t *tmp = (const vtss_phy_10g_clause_37_adv_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_clause_37_status_t_to_mesa_phy_10g_clause_37_status_t(const vtss_phy_10g_clause_37_status_t *in, mesa_phy_10g_clause_37_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_clause_37_status_t *tmp = (const mesa_phy_10g_clause_37_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_clause_37_status_t_to_vtss_phy_10g_clause_37_status_t(const mesa_phy_10g_clause_37_status_t *in, vtss_phy_10g_clause_37_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_clause_37_status_t *tmp = (const vtss_phy_10g_clause_37_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_clause_37_cmn_status_t_to_mesa_phy_10g_clause_37_cmn_status_t(const vtss_phy_10g_clause_37_cmn_status_t *in, mesa_phy_10g_clause_37_cmn_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_clause_37_cmn_status_t *tmp = (const mesa_phy_10g_clause_37_cmn_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_clause_37_cmn_status_t_to_vtss_phy_10g_clause_37_cmn_status_t(const mesa_phy_10g_clause_37_cmn_status_t *in, vtss_phy_10g_clause_37_cmn_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_clause_37_cmn_status_t *tmp = (const vtss_phy_10g_clause_37_cmn_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_clause_37_control_t_to_mesa_phy_10g_clause_37_control_t(const vtss_phy_10g_clause_37_control_t *in, mesa_phy_10g_clause_37_control_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_clause_37_control_t *tmp = (const mesa_phy_10g_clause_37_control_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_clause_37_control_t_to_vtss_phy_10g_clause_37_control_t(const mesa_phy_10g_clause_37_control_t *in, vtss_phy_10g_clause_37_control_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_clause_37_control_t *tmp = (const vtss_phy_10g_clause_37_control_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_lb_type_t_to_mesa_lb_type_t(const vtss_lb_type_t *in, mesa_lb_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_lb_type_t *tmp = (const mesa_lb_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_lb_type_t_to_vtss_lb_type_t(const mesa_lb_type_t *in, vtss_lb_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_lb_type_t *tmp = (const vtss_lb_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_loopback_t_to_mesa_phy_10g_loopback_t(const vtss_phy_10g_loopback_t *in, mesa_phy_10g_loopback_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_loopback_t *tmp = (const mesa_phy_10g_loopback_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_loopback_t_to_vtss_phy_10g_loopback_t(const mesa_phy_10g_loopback_t *in, vtss_phy_10g_loopback_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_loopback_t *tmp = (const vtss_phy_10g_loopback_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_pcs_cnt_t_to_mesa_phy_pcs_cnt_t(const vtss_phy_pcs_cnt_t *in, mesa_phy_pcs_cnt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_pcs_cnt_t *tmp = (const mesa_phy_pcs_cnt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_pcs_cnt_t_to_vtss_phy_pcs_cnt_t(const mesa_phy_pcs_cnt_t *in, vtss_phy_pcs_cnt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_pcs_cnt_t *tmp = (const vtss_phy_pcs_cnt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_cnt_t_to_mesa_phy_10g_cnt_t(const vtss_phy_10g_cnt_t *in, mesa_phy_10g_cnt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_cnt_t *tmp = (const mesa_phy_10g_cnt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_cnt_t_to_vtss_phy_10g_cnt_t(const mesa_phy_10g_cnt_t *in, vtss_phy_10g_cnt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_cnt_t *tmp = (const vtss_phy_10g_cnt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_power_t_to_mesa_phy_10g_power_t(const vtss_phy_10g_power_t *in, mesa_phy_10g_power_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_power_t *tmp = (const mesa_phy_10g_power_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_power_t_to_vtss_phy_10g_power_t(const mesa_phy_10g_power_t *in, vtss_phy_10g_power_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_power_t *tmp = (const vtss_phy_10g_power_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_failover_mode_t_to_mesa_phy_10g_failover_mode_t(const vtss_phy_10g_failover_mode_t *in, mesa_phy_10g_failover_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_failover_mode_t *tmp = (const mesa_phy_10g_failover_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_failover_mode_t_to_vtss_phy_10g_failover_mode_t(const mesa_phy_10g_failover_mode_t *in, vtss_phy_10g_failover_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_failover_mode_t *tmp = (const vtss_phy_10g_failover_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_auto_failover_event_t_to_mesa_phy_10g_auto_failover_event_t(const vtss_phy_10g_auto_failover_event_t *in, mesa_phy_10g_auto_failover_event_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_auto_failover_event_t *tmp = (const mesa_phy_10g_auto_failover_event_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_auto_failover_event_t_to_vtss_phy_10g_auto_failover_event_t(const mesa_phy_10g_auto_failover_event_t *in, vtss_phy_10g_auto_failover_event_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_auto_failover_event_t *tmp = (const vtss_phy_10g_auto_failover_event_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_auto_failover_filter_t_to_mesa_phy_10g_auto_failover_filter_t(const vtss_phy_10g_auto_failover_filter_t *in, mesa_phy_10g_auto_failover_filter_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_auto_failover_filter_t *tmp = (const mesa_phy_10g_auto_failover_filter_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_auto_failover_filter_t_to_vtss_phy_10g_auto_failover_filter_t(const mesa_phy_10g_auto_failover_filter_t *in, vtss_phy_10g_auto_failover_filter_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_auto_failover_filter_t *tmp = (const vtss_phy_10g_auto_failover_filter_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_auto_failover_conf_t_to_mesa_phy_10g_auto_failover_conf_t(const vtss_phy_10g_auto_failover_conf_t *in, mesa_phy_10g_auto_failover_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_auto_failover_conf_t *tmp = (const mesa_phy_10g_auto_failover_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_auto_failover_conf_t_to_vtss_phy_10g_auto_failover_conf_t(const mesa_phy_10g_auto_failover_conf_t *in, vtss_phy_10g_auto_failover_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_auto_failover_conf_t *tmp = (const vtss_phy_10g_auto_failover_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_vscope_scan_t_to_mesa_phy_10g_vscope_scan_t(const vtss_phy_10g_vscope_scan_t *in, mesa_phy_10g_vscope_scan_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_vscope_scan_t *tmp = (const mesa_phy_10g_vscope_scan_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_vscope_scan_t_to_vtss_phy_10g_vscope_scan_t(const mesa_phy_10g_vscope_scan_t *in, vtss_phy_10g_vscope_scan_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_vscope_scan_t *tmp = (const vtss_phy_10g_vscope_scan_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_vscope_conf_t_to_mesa_phy_10g_vscope_conf_t(const vtss_phy_10g_vscope_conf_t *in, mesa_phy_10g_vscope_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_vscope_conf_t *tmp = (const mesa_phy_10g_vscope_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_vscope_conf_t_to_vtss_phy_10g_vscope_conf_t(const mesa_phy_10g_vscope_conf_t *in, vtss_phy_10g_vscope_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_vscope_conf_t *tmp = (const vtss_phy_10g_vscope_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_ib_storage_t_to_mesa_phy_10g_ib_storage_t(const vtss_phy_10g_ib_storage_t *in, mesa_phy_10g_ib_storage_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_ib_storage_t *tmp = (const mesa_phy_10g_ib_storage_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_ib_storage_t_to_vtss_phy_10g_ib_storage_t(const mesa_phy_10g_ib_storage_t *in, vtss_phy_10g_ib_storage_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_ib_storage_t *tmp = (const vtss_phy_10g_ib_storage_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_vscope_scan_conf_t_to_mesa_phy_10g_vscope_scan_conf_t(const vtss_phy_10g_vscope_scan_conf_t *in, mesa_phy_10g_vscope_scan_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_vscope_scan_conf_t *tmp = (const mesa_phy_10g_vscope_scan_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_vscope_scan_conf_t_to_vtss_phy_10g_vscope_scan_conf_t(const mesa_phy_10g_vscope_scan_conf_t *in, vtss_phy_10g_vscope_scan_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_vscope_scan_conf_t *tmp = (const vtss_phy_10g_vscope_scan_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_vscope_scan_status_t_to_mesa_phy_10g_vscope_scan_status_t(const vtss_phy_10g_vscope_scan_status_t *in, mesa_phy_10g_vscope_scan_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_vscope_scan_status_t *tmp = (const mesa_phy_10g_vscope_scan_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_vscope_scan_status_t_to_vtss_phy_10g_vscope_scan_status_t(const mesa_phy_10g_vscope_scan_status_t *in, vtss_phy_10g_vscope_scan_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_vscope_scan_status_t *tmp = (const vtss_phy_10g_vscope_scan_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_direction_t_to_mesa_phy_10g_direction_t(const vtss_phy_10g_direction_t *in, mesa_phy_10g_direction_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_direction_t *tmp = (const mesa_phy_10g_direction_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_direction_t_to_vtss_phy_10g_direction_t(const mesa_phy_10g_direction_t *in, vtss_phy_10g_direction_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_direction_t *tmp = (const vtss_phy_10g_direction_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_prbs_type_t_to_mesa_phy_10g_prbs_type_t(const vtss_phy_10g_prbs_type_t *in, mesa_phy_10g_prbs_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_prbs_type_t *tmp = (const mesa_phy_10g_prbs_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_prbs_type_t_to_vtss_phy_10g_prbs_type_t(const mesa_phy_10g_prbs_type_t *in, vtss_phy_10g_prbs_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_prbs_type_t *tmp = (const vtss_phy_10g_prbs_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_prbs_generator_conf_t_to_mesa_phy_10g_prbs_generator_conf_t(const vtss_phy_10g_prbs_generator_conf_t *in, mesa_phy_10g_prbs_generator_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_prbs_generator_conf_t *tmp = (const mesa_phy_10g_prbs_generator_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_prbs_generator_conf_t_to_vtss_phy_10g_prbs_generator_conf_t(const mesa_phy_10g_prbs_generator_conf_t *in, vtss_phy_10g_prbs_generator_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_prbs_generator_conf_t *tmp = (const vtss_phy_10g_prbs_generator_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_prbs_monitor_conf_t_to_mesa_phy_10g_prbs_monitor_conf_t(const vtss_phy_10g_prbs_monitor_conf_t *in, mesa_phy_10g_prbs_monitor_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_prbs_monitor_conf_t *tmp = (const mesa_phy_10g_prbs_monitor_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_prbs_monitor_conf_t_to_vtss_phy_10g_prbs_monitor_conf_t(const mesa_phy_10g_prbs_monitor_conf_t *in, vtss_phy_10g_prbs_monitor_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_prbs_monitor_conf_t *tmp = (const vtss_phy_10g_prbs_monitor_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_prbs_monitor_status_t_to_mesa_phy_10g_prbs_monitor_status_t(const vtss_phy_10g_prbs_monitor_status_t *in, mesa_phy_10g_prbs_monitor_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_prbs_monitor_status_t *tmp = (const mesa_phy_10g_prbs_monitor_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_prbs_monitor_status_t_to_vtss_phy_10g_prbs_monitor_status_t(const mesa_phy_10g_prbs_monitor_status_t *in, vtss_phy_10g_prbs_monitor_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_prbs_monitor_status_t *tmp = (const vtss_phy_10g_prbs_monitor_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_prbs_gen_conf_t_to_mesa_phy_10g_prbs_gen_conf_t(const vtss_phy_10g_prbs_gen_conf_t *in, mesa_phy_10g_prbs_gen_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_prbs_gen_conf_t *tmp = (const mesa_phy_10g_prbs_gen_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_prbs_gen_conf_t_to_vtss_phy_10g_prbs_gen_conf_t(const mesa_phy_10g_prbs_gen_conf_t *in, vtss_phy_10g_prbs_gen_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_prbs_gen_conf_t *tmp = (const vtss_phy_10g_prbs_gen_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_prbs_mon_conf_t_to_mesa_phy_10g_prbs_mon_conf_t(const vtss_phy_10g_prbs_mon_conf_t *in, mesa_phy_10g_prbs_mon_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_prbs_mon_conf_t *tmp = (const mesa_phy_10g_prbs_mon_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_prbs_mon_conf_t_to_vtss_phy_10g_prbs_mon_conf_t(const mesa_phy_10g_prbs_mon_conf_t *in, vtss_phy_10g_prbs_mon_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_prbs_mon_conf_t *tmp = (const vtss_phy_10g_prbs_mon_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_sgmii_lane_select_t_to_mesa_phy_10g_sgmii_lane_select_t(const vtss_phy_10g_sgmii_lane_select_t *in, mesa_phy_10g_sgmii_lane_select_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_sgmii_lane_select_t *tmp = (const mesa_phy_10g_sgmii_lane_select_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_sgmii_lane_select_t_to_vtss_phy_10g_sgmii_lane_select_t(const mesa_phy_10g_sgmii_lane_select_t *in, vtss_phy_10g_sgmii_lane_select_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_sgmii_lane_select_t *tmp = (const vtss_phy_10g_sgmii_lane_select_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_pkt_gen_conf_t_to_mesa_phy_10g_pkt_gen_conf_t(const vtss_phy_10g_pkt_gen_conf_t *in, mesa_phy_10g_pkt_gen_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_pkt_gen_conf_t *tmp = (const mesa_phy_10g_pkt_gen_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_pkt_gen_conf_t_to_vtss_phy_10g_pkt_gen_conf_t(const mesa_phy_10g_pkt_gen_conf_t *in, vtss_phy_10g_pkt_gen_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_pkt_gen_conf_t *tmp = (const vtss_phy_10g_pkt_gen_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_pkt_mon_rst_t_to_mesa_phy_10g_pkt_mon_rst_t(const vtss_phy_10g_pkt_mon_rst_t *in, mesa_phy_10g_pkt_mon_rst_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_pkt_mon_rst_t *tmp = (const mesa_phy_10g_pkt_mon_rst_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_pkt_mon_rst_t_to_vtss_phy_10g_pkt_mon_rst_t(const mesa_phy_10g_pkt_mon_rst_t *in, vtss_phy_10g_pkt_mon_rst_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_pkt_mon_rst_t *tmp = (const vtss_phy_10g_pkt_mon_rst_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_pkt_mon_conf_t_to_mesa_phy_10g_pkt_mon_conf_t(const vtss_phy_10g_pkt_mon_conf_t *in, mesa_phy_10g_pkt_mon_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_pkt_mon_conf_t *tmp = (const mesa_phy_10g_pkt_mon_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_pkt_mon_conf_t_to_vtss_phy_10g_pkt_mon_conf_t(const mesa_phy_10g_pkt_mon_conf_t *in, vtss_phy_10g_pkt_mon_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_pkt_mon_conf_t *tmp = (const vtss_phy_10g_pkt_mon_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_timestamp_val_t_to_mesa_phy_10g_timestamp_val_t(const vtss_phy_10g_timestamp_val_t *in, mesa_phy_10g_timestamp_val_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_timestamp_val_t *tmp = (const mesa_phy_10g_timestamp_val_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_timestamp_val_t_to_vtss_phy_10g_timestamp_val_t(const mesa_phy_10g_timestamp_val_t *in, vtss_phy_10g_timestamp_val_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_timestamp_val_t *tmp = (const vtss_phy_10g_timestamp_val_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_type_t_to_mesa_phy_10g_type_t(const vtss_phy_10g_type_t *in, mesa_phy_10g_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_type_t *tmp = (const mesa_phy_10g_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_type_t_to_vtss_phy_10g_type_t(const mesa_phy_10g_type_t *in, vtss_phy_10g_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_type_t *tmp = (const vtss_phy_10g_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_family_t_to_mesa_phy_10g_family_t(const vtss_phy_10g_family_t *in, mesa_phy_10g_family_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_family_t *tmp = (const mesa_phy_10g_family_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_family_t_to_vtss_phy_10g_family_t(const mesa_phy_10g_family_t *in, vtss_phy_10g_family_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_family_t *tmp = (const vtss_phy_10g_family_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_id_t_to_mesa_phy_10g_id_t(const vtss_phy_10g_id_t *in, mesa_phy_10g_id_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_id_t *tmp = (const mesa_phy_10g_id_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_id_t_to_vtss_phy_10g_id_t(const mesa_phy_10g_id_t *in, vtss_phy_10g_id_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_id_t *tmp = (const vtss_phy_10g_id_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_10g_phy_gpio_t_to_mesa_10g_phy_gpio_t(const vtss_10g_phy_gpio_t *in, mesa_10g_phy_gpio_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_10g_phy_gpio_t *tmp = (const mesa_10g_phy_gpio_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_10g_phy_gpio_t_to_vtss_10g_phy_gpio_t(const mesa_10g_phy_gpio_t *in, vtss_10g_phy_gpio_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_10g_phy_gpio_t *tmp = (const vtss_10g_phy_gpio_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_gpio_10g_gpio_intr_sgnl_t_to_mesa_gpio_10g_gpio_intr_sgnl_t(const vtss_gpio_10g_gpio_intr_sgnl_t *in, mesa_gpio_10g_gpio_intr_sgnl_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_gpio_10g_gpio_intr_sgnl_t *tmp = (const mesa_gpio_10g_gpio_intr_sgnl_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_gpio_10g_gpio_intr_sgnl_t_to_vtss_gpio_10g_gpio_intr_sgnl_t(const mesa_gpio_10g_gpio_intr_sgnl_t *in, vtss_gpio_10g_gpio_intr_sgnl_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_gpio_10g_gpio_intr_sgnl_t *tmp = (const vtss_gpio_10g_gpio_intr_sgnl_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_gpio_10g_chan_intrpt_t_to_mesa_gpio_10g_chan_intrpt_t(const vtss_gpio_10g_chan_intrpt_t *in, mesa_gpio_10g_chan_intrpt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_gpio_10g_chan_intrpt_t *tmp = (const mesa_gpio_10g_chan_intrpt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_gpio_10g_chan_intrpt_t_to_vtss_gpio_10g_chan_intrpt_t(const mesa_gpio_10g_chan_intrpt_t *in, vtss_gpio_10g_chan_intrpt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_gpio_10g_chan_intrpt_t *tmp = (const vtss_gpio_10g_chan_intrpt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_gpio_10g_aggr_intrpt_t_to_mesa_gpio_10g_aggr_intrpt_t(const vtss_gpio_10g_aggr_intrpt_t *in, mesa_gpio_10g_aggr_intrpt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_gpio_10g_aggr_intrpt_t *tmp = (const mesa_gpio_10g_aggr_intrpt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_gpio_10g_aggr_intrpt_t_to_vtss_gpio_10g_aggr_intrpt_t(const mesa_gpio_10g_aggr_intrpt_t *in, vtss_gpio_10g_aggr_intrpt_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_gpio_10g_aggr_intrpt_t *tmp = (const vtss_gpio_10g_aggr_intrpt_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_gpio_10g_input_t_to_mesa_gpio_10g_input_t(const vtss_gpio_10g_input_t *in, mesa_gpio_10g_input_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_mesa_gpio_10g_input_t_to_vtss_gpio_10g_input_t(const mesa_gpio_10g_input_t *in, vtss_gpio_10g_input_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_gpio_10g_led_mode_t_to_mesa_gpio_10g_led_mode_t(const vtss_gpio_10g_led_mode_t *in, mesa_gpio_10g_led_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_gpio_10g_led_mode_t *tmp = (const mesa_gpio_10g_led_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_gpio_10g_led_mode_t_to_vtss_gpio_10g_led_mode_t(const mesa_gpio_10g_led_mode_t *in, vtss_gpio_10g_led_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_gpio_10g_led_mode_t *tmp = (const vtss_gpio_10g_led_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_gpio_10g_led_blink_t_to_mesa_gpio_10g_led_blink_t(const vtss_gpio_10g_led_blink_t *in, mesa_gpio_10g_led_blink_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_gpio_10g_led_blink_t *tmp = (const mesa_gpio_10g_led_blink_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_gpio_10g_led_blink_t_to_vtss_gpio_10g_led_blink_t(const mesa_gpio_10g_led_blink_t *in, vtss_gpio_10g_led_blink_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_gpio_10g_led_blink_t *tmp = (const vtss_gpio_10g_led_blink_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_gpio_10g_led_conf_t_to_mesa_gpio_10g_led_conf_t(const vtss_gpio_10g_led_conf_t *in, mesa_gpio_10g_led_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_gpio_10g_led_conf_t *tmp = (const mesa_gpio_10g_led_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_gpio_10g_led_conf_t_to_vtss_gpio_10g_led_conf_t(const mesa_gpio_10g_led_conf_t *in, vtss_gpio_10g_led_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_gpio_10g_led_conf_t *tmp = (const vtss_gpio_10g_led_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_gpio_10g_gpio_mode_t_to_mesa_gpio_10g_gpio_mode_t(const vtss_gpio_10g_gpio_mode_t *in, mesa_gpio_10g_gpio_mode_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_mesa_gpio_10g_gpio_mode_t_to_vtss_gpio_10g_gpio_mode_t(const mesa_gpio_10g_gpio_mode_t *in, vtss_gpio_10g_gpio_mode_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_fw_status_t_to_mesa_phy_10g_fw_status_t(const vtss_phy_10g_fw_status_t *in, mesa_phy_10g_fw_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_fw_status_t *tmp = (const mesa_phy_10g_fw_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_fw_status_t_to_vtss_phy_10g_fw_status_t(const mesa_phy_10g_fw_status_t *in, vtss_phy_10g_fw_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_fw_status_t *tmp = (const vtss_phy_10g_fw_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_vtss_phy_10g_i2c_slave_conf_t_to_mesa_phy_10g_i2c_slave_conf_t(const vtss_phy_10g_i2c_slave_conf_t *in, mesa_phy_10g_i2c_slave_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_10g_i2c_slave_conf_t *tmp = (const mesa_phy_10g_i2c_slave_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_10G_PHY
inline static mesa_rc mesa_conv_mesa_phy_10g_i2c_slave_conf_t_to_vtss_phy_10g_i2c_slave_conf_t(const mesa_phy_10g_i2c_slave_conf_t *in, vtss_phy_10g_i2c_slave_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_10g_i2c_slave_conf_t *tmp = (const vtss_phy_10g_i2c_slave_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_10G_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_part_number_t_to_mesa_phy_part_number_t(const vtss_phy_part_number_t *in, mesa_phy_part_number_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_part_number_t *tmp = (const mesa_phy_part_number_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_part_number_t_to_vtss_phy_part_number_t(const mesa_phy_part_number_t *in, vtss_phy_part_number_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_part_number_t *tmp = (const vtss_phy_part_number_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_led_mode_t_to_mesa_phy_led_mode_t(const vtss_phy_led_mode_t *in, mesa_phy_led_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_led_mode_t *tmp = (const mesa_phy_led_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_led_mode_t_to_vtss_phy_led_mode_t(const mesa_phy_led_mode_t *in, vtss_phy_led_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_led_mode_t *tmp = (const vtss_phy_led_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_led_number_t_to_mesa_phy_led_number_t(const vtss_phy_led_number_t *in, mesa_phy_led_number_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_led_number_t *tmp = (const mesa_phy_led_number_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_led_number_t_to_vtss_phy_led_number_t(const mesa_phy_led_number_t *in, vtss_phy_led_number_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_led_number_t *tmp = (const vtss_phy_led_number_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_led_mode_select_t_to_mesa_phy_led_mode_select_t(const vtss_phy_led_mode_select_t *in, mesa_phy_led_mode_select_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_led_mode_select_t *tmp = (const mesa_phy_led_mode_select_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_led_mode_select_t_to_vtss_phy_led_mode_select_t(const mesa_phy_led_mode_select_t *in, vtss_phy_led_mode_select_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_led_mode_select_t *tmp = (const vtss_phy_led_mode_select_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_type_t_to_mesa_phy_type_t(const vtss_phy_type_t *in, mesa_phy_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_type_t *tmp = (const mesa_phy_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_type_t_to_vtss_phy_type_t(const mesa_phy_type_t *in, vtss_phy_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_type_t *tmp = (const vtss_phy_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_rgmii_skew_delay_psec_t_to_mesa_rgmii_skew_delay_psec_t(const vtss_rgmii_skew_delay_psec_t *in, mesa_rgmii_skew_delay_psec_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_rgmii_skew_delay_psec_t *tmp = (const mesa_rgmii_skew_delay_psec_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_rgmii_skew_delay_psec_t_to_vtss_rgmii_skew_delay_psec_t(const mesa_rgmii_skew_delay_psec_t *in, vtss_rgmii_skew_delay_psec_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_rgmii_skew_delay_psec_t *tmp = (const vtss_rgmii_skew_delay_psec_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_mode_t_to_mesa_phy_mode_t(const vtss_phy_mode_t *in, mesa_phy_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_mode_t *tmp = (const mesa_phy_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_mode_t_to_vtss_phy_mode_t(const mesa_phy_mode_t *in, vtss_phy_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_mode_t *tmp = (const vtss_phy_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_forced_t_to_mesa_phy_forced_t(const vtss_phy_forced_t *in, mesa_phy_forced_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_forced_t *tmp = (const mesa_phy_forced_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_forced_t_to_vtss_phy_forced_t(const mesa_phy_forced_t *in, vtss_phy_forced_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_forced_t *tmp = (const vtss_phy_forced_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_aneg_t_to_mesa_phy_aneg_t(const vtss_phy_aneg_t *in, mesa_phy_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_aneg_t *tmp = (const mesa_phy_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_aneg_t_to_vtss_phy_aneg_t(const mesa_phy_aneg_t *in, vtss_phy_aneg_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_aneg_t *tmp = (const vtss_phy_aneg_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_fast_link_fail_t_to_mesa_phy_fast_link_fail_t(const vtss_phy_fast_link_fail_t *in, mesa_phy_fast_link_fail_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_fast_link_fail_t *tmp = (const mesa_phy_fast_link_fail_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_fast_link_fail_t_to_vtss_phy_fast_link_fail_t(const mesa_phy_fast_link_fail_t *in, vtss_phy_fast_link_fail_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_fast_link_fail_t *tmp = (const vtss_phy_fast_link_fail_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_sigdet_polarity_t_to_mesa_phy_sigdet_polarity_t(const vtss_phy_sigdet_polarity_t *in, mesa_phy_sigdet_polarity_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_sigdet_polarity_t *tmp = (const mesa_phy_sigdet_polarity_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_sigdet_polarity_t_to_vtss_phy_sigdet_polarity_t(const mesa_phy_sigdet_polarity_t *in, vtss_phy_sigdet_polarity_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_sigdet_polarity_t *tmp = (const vtss_phy_sigdet_polarity_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_unidirectional_t_to_mesa_phy_unidirectional_t(const vtss_phy_unidirectional_t *in, mesa_phy_unidirectional_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_unidirectional_t *tmp = (const mesa_phy_unidirectional_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_unidirectional_t_to_vtss_phy_unidirectional_t(const mesa_phy_unidirectional_t *in, vtss_phy_unidirectional_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_unidirectional_t *tmp = (const vtss_phy_unidirectional_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_mac_serd_pcs_sgmii_pre_to_mesa_phy_mac_serd_pcs_sgmii_pre(const vtss_phy_mac_serd_pcs_sgmii_pre *in, mesa_phy_mac_serd_pcs_sgmii_pre *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_mac_serd_pcs_sgmii_pre *tmp = (const mesa_phy_mac_serd_pcs_sgmii_pre *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_mac_serd_pcs_sgmii_pre_to_vtss_phy_mac_serd_pcs_sgmii_pre(const mesa_phy_mac_serd_pcs_sgmii_pre *in, vtss_phy_mac_serd_pcs_sgmii_pre *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_mac_serd_pcs_sgmii_pre *tmp = (const vtss_phy_mac_serd_pcs_sgmii_pre *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_mac_serd_pcs_cntl_t_to_mesa_phy_mac_serd_pcs_cntl_t(const vtss_phy_mac_serd_pcs_cntl_t *in, mesa_phy_mac_serd_pcs_cntl_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_mac_serd_pcs_cntl_t *tmp = (const mesa_phy_mac_serd_pcs_cntl_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_mac_serd_pcs_cntl_t_to_vtss_phy_mac_serd_pcs_cntl_t(const mesa_phy_mac_serd_pcs_cntl_t *in, vtss_phy_mac_serd_pcs_cntl_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_mac_serd_pcs_cntl_t *tmp = (const vtss_phy_mac_serd_pcs_cntl_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_media_rem_fault_t_to_mesa_phy_media_rem_fault_t(const vtss_phy_media_rem_fault_t *in, mesa_phy_media_rem_fault_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_media_rem_fault_t *tmp = (const mesa_phy_media_rem_fault_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_media_rem_fault_t_to_vtss_phy_media_rem_fault_t(const mesa_phy_media_rem_fault_t *in, vtss_phy_media_rem_fault_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_media_rem_fault_t *tmp = (const vtss_phy_media_rem_fault_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_media_serd_pcs_cntl_t_to_mesa_phy_media_serd_pcs_cntl_t(const vtss_phy_media_serd_pcs_cntl_t *in, mesa_phy_media_serd_pcs_cntl_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_media_serd_pcs_cntl_t *tmp = (const mesa_phy_media_serd_pcs_cntl_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_media_serd_pcs_cntl_t_to_vtss_phy_media_serd_pcs_cntl_t(const mesa_phy_media_serd_pcs_cntl_t *in, vtss_phy_media_serd_pcs_cntl_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_media_serd_pcs_cntl_t *tmp = (const vtss_phy_media_serd_pcs_cntl_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_media_force_ams_sel_t_to_mesa_phy_media_force_ams_sel_t(const vtss_phy_media_force_ams_sel_t *in, mesa_phy_media_force_ams_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_media_force_ams_sel_t *tmp = (const mesa_phy_media_force_ams_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_media_force_ams_sel_t_to_vtss_phy_media_force_ams_sel_t(const mesa_phy_media_force_ams_sel_t *in, vtss_phy_media_force_ams_sel_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_media_force_ams_sel_t *tmp = (const vtss_phy_media_force_ams_sel_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_conf_t_to_mesa_phy_conf_t(const vtss_phy_conf_t *in, mesa_phy_conf_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(const mesa_phy_conf_t *in, vtss_phy_conf_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_ring_resiliency_status_t_to_mesa_phy_ring_resiliency_status_t(const vtss_phy_ring_resiliency_status_t *in, mesa_phy_ring_resiliency_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ring_resiliency_status_t *tmp = (const mesa_phy_ring_resiliency_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_ring_resiliency_status_t_to_vtss_phy_ring_resiliency_status_t(const mesa_phy_ring_resiliency_status_t *in, vtss_phy_ring_resiliency_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ring_resiliency_status_t *tmp = (const vtss_phy_ring_resiliency_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_ring_resiliency_conf_t_to_mesa_phy_ring_resiliency_conf_t(const vtss_phy_ring_resiliency_conf_t *in, mesa_phy_ring_resiliency_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ring_resiliency_conf_t *tmp = (const mesa_phy_ring_resiliency_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_ring_resiliency_conf_t_to_vtss_phy_ring_resiliency_conf_t(const mesa_phy_ring_resiliency_conf_t *in, vtss_phy_ring_resiliency_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ring_resiliency_conf_t *tmp = (const vtss_phy_ring_resiliency_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_conf_1g_t_to_mesa_phy_conf_1g_t(const vtss_phy_conf_1g_t *in, mesa_phy_conf_1g_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_conf_1g_t *tmp = (const mesa_phy_conf_1g_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_conf_1g_t_to_vtss_phy_conf_1g_t(const mesa_phy_conf_1g_t *in, vtss_phy_conf_1g_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_conf_1g_t *tmp = (const vtss_phy_conf_1g_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_power_conf_t_to_mesa_phy_power_conf_t(const vtss_phy_power_conf_t *in, mesa_phy_power_conf_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_mesa_phy_power_conf_t_to_vtss_phy_power_conf_t(const mesa_phy_power_conf_t *in, vtss_phy_power_conf_t *out); /* ag.rb:1595 */
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_power_status_t_to_mesa_phy_power_status_t(const vtss_phy_power_status_t *in, mesa_phy_power_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_power_status_t *tmp = (const mesa_phy_power_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_power_status_t_to_vtss_phy_power_status_t(const mesa_phy_power_status_t *in, vtss_phy_power_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_power_status_t *tmp = (const vtss_phy_power_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_clk_source_t_to_mesa_phy_clk_source_t(const vtss_phy_clk_source_t *in, mesa_phy_clk_source_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_clk_source_t *tmp = (const mesa_phy_clk_source_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_clk_source_t_to_vtss_phy_clk_source_t(const mesa_phy_clk_source_t *in, vtss_phy_clk_source_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_clk_source_t *tmp = (const vtss_phy_clk_source_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_freq_t_to_mesa_phy_freq_t(const vtss_phy_freq_t *in, mesa_phy_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_freq_t *tmp = (const mesa_phy_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_freq_t_to_vtss_phy_freq_t(const mesa_phy_freq_t *in, vtss_phy_freq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_freq_t *tmp = (const vtss_phy_freq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_clk_squelch_to_mesa_phy_clk_squelch(const vtss_phy_clk_squelch *in, mesa_phy_clk_squelch *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_clk_squelch *tmp = (const mesa_phy_clk_squelch *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_clk_squelch_to_vtss_phy_clk_squelch(const mesa_phy_clk_squelch *in, vtss_phy_clk_squelch *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_clk_squelch *tmp = (const vtss_phy_clk_squelch *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_clock_conf_t_to_mesa_phy_clock_conf_t(const vtss_phy_clock_conf_t *in, mesa_phy_clock_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_clock_conf_t *tmp = (const mesa_phy_clock_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_clock_conf_t_to_vtss_phy_clock_conf_t(const mesa_phy_clock_conf_t *in, vtss_phy_clock_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_clock_conf_t *tmp = (const vtss_phy_clock_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_gpio_mode_t_to_mesa_phy_gpio_mode_t(const vtss_phy_gpio_mode_t *in, mesa_phy_gpio_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_gpio_mode_t *tmp = (const mesa_phy_gpio_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_gpio_mode_t_to_vtss_phy_gpio_mode_t(const mesa_phy_gpio_mode_t *in, vtss_phy_gpio_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_gpio_mode_t *tmp = (const vtss_phy_gpio_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_eee_mode_t_to_mesa_eee_mode_t(const vtss_eee_mode_t *in, mesa_eee_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_eee_mode_t *tmp = (const mesa_eee_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_eee_mode_t_to_vtss_eee_mode_t(const mesa_eee_mode_t *in, vtss_eee_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_eee_mode_t *tmp = (const vtss_eee_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_eee_conf_t_to_mesa_phy_eee_conf_t(const vtss_phy_eee_conf_t *in, mesa_phy_eee_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_eee_conf_t *tmp = (const mesa_phy_eee_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_eee_conf_t_to_vtss_phy_eee_conf_t(const mesa_phy_eee_conf_t *in, vtss_phy_eee_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_eee_conf_t *tmp = (const vtss_phy_eee_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
inline static mesa_rc mesa_conv_vtss_phy_enhanced_led_control_t_to_mesa_phy_enhanced_led_control_t(const vtss_phy_enhanced_led_control_t *in, mesa_phy_enhanced_led_control_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_enhanced_led_control_t *tmp = (const mesa_phy_enhanced_led_control_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC)
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
inline static mesa_rc mesa_conv_mesa_phy_enhanced_led_control_t_to_vtss_phy_enhanced_led_control_t(const mesa_phy_enhanced_led_control_t *in, vtss_phy_enhanced_led_control_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_enhanced_led_control_t *tmp = (const vtss_phy_enhanced_led_control_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC)
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_statistic_t_to_mesa_phy_statistic_t(const vtss_phy_statistic_t *in, mesa_phy_statistic_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_statistic_t *tmp = (const mesa_phy_statistic_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_statistic_t_to_vtss_phy_statistic_t(const mesa_phy_statistic_t *in, vtss_phy_statistic_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_statistic_t *tmp = (const vtss_phy_statistic_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_loopback_t_to_mesa_phy_loopback_t(const vtss_phy_loopback_t *in, mesa_phy_loopback_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_loopback_t *tmp = (const mesa_phy_loopback_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_loopback_t_to_vtss_phy_loopback_t(const mesa_phy_loopback_t *in, vtss_phy_loopback_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_loopback_t *tmp = (const vtss_phy_loopback_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_rcpll_status_t_to_mesa_rcpll_status_t(const vtss_rcpll_status_t *in, mesa_rcpll_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_rcpll_status_t *tmp = (const mesa_rcpll_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_rcpll_status_t_to_vtss_rcpll_status_t(const mesa_rcpll_status_t *in, vtss_rcpll_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_rcpll_status_t *tmp = (const vtss_rcpll_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_lcpll_status_t_to_mesa_lcpll_status_t(const vtss_lcpll_status_t *in, mesa_lcpll_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_lcpll_status_t *tmp = (const mesa_lcpll_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_lcpll_status_t_to_vtss_lcpll_status_t(const mesa_lcpll_status_t *in, vtss_lcpll_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_lcpll_status_t *tmp = (const vtss_lcpll_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_wol_mac_addr_t_to_mesa_wol_mac_addr_t(const vtss_wol_mac_addr_t *in, mesa_wol_mac_addr_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_wol_mac_addr_t *tmp = (const mesa_wol_mac_addr_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_wol_mac_addr_t_to_vtss_wol_mac_addr_t(const mesa_wol_mac_addr_t *in, vtss_wol_mac_addr_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_wol_mac_addr_t *tmp = (const vtss_wol_mac_addr_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_secure_on_passwd_t_to_mesa_secure_on_passwd_t(const vtss_secure_on_passwd_t *in, mesa_secure_on_passwd_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_secure_on_passwd_t *tmp = (const mesa_secure_on_passwd_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_secure_on_passwd_t_to_vtss_secure_on_passwd_t(const mesa_secure_on_passwd_t *in, vtss_secure_on_passwd_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_secure_on_passwd_t *tmp = (const vtss_secure_on_passwd_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_wol_passwd_len_type_t_to_mesa_wol_passwd_len_type_t(const vtss_wol_passwd_len_type_t *in, mesa_wol_passwd_len_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_wol_passwd_len_type_t *tmp = (const mesa_wol_passwd_len_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_wol_passwd_len_type_t_to_vtss_wol_passwd_len_type_t(const mesa_wol_passwd_len_type_t *in, vtss_wol_passwd_len_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_wol_passwd_len_type_t *tmp = (const vtss_wol_passwd_len_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_wol_conf_t_to_mesa_phy_wol_conf_t(const vtss_phy_wol_conf_t *in, mesa_phy_wol_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_wol_conf_t *tmp = (const mesa_phy_wol_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_wol_conf_t_to_vtss_phy_wol_conf_t(const mesa_phy_wol_conf_t *in, vtss_phy_wol_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_wol_conf_t *tmp = (const vtss_phy_wol_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_fefi_mode_t_to_mesa_fefi_mode_t(const vtss_fefi_mode_t *in, mesa_fefi_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_fefi_mode_t *tmp = (const mesa_fefi_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_fefi_mode_t_to_vtss_fefi_mode_t(const mesa_fefi_mode_t *in, vtss_fefi_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_fefi_mode_t *tmp = (const vtss_fefi_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_alt_clock_mode_t_to_mesa_phy_ts_alt_clock_mode_t(const vtss_phy_ts_alt_clock_mode_t *in, mesa_phy_ts_alt_clock_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_alt_clock_mode_t *tmp = (const mesa_phy_ts_alt_clock_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_alt_clock_mode_t_to_vtss_phy_ts_alt_clock_mode_t(const mesa_phy_ts_alt_clock_mode_t *in, vtss_phy_ts_alt_clock_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_alt_clock_mode_t *tmp = (const vtss_phy_ts_alt_clock_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_pps_conf_t_to_mesa_phy_ts_pps_conf_t(const vtss_phy_ts_pps_conf_t *in, mesa_phy_ts_pps_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_pps_conf_t *tmp = (const mesa_phy_ts_pps_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_pps_conf_t_to_vtss_phy_ts_pps_conf_t(const mesa_phy_ts_pps_conf_t *in, vtss_phy_ts_pps_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_pps_conf_t *tmp = (const vtss_phy_ts_pps_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_timestamp_t_to_mesa_phy_timestamp_t(const vtss_phy_timestamp_t *in, mesa_phy_timestamp_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_timestamp_t *tmp = (const mesa_phy_timestamp_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_timestamp_t_to_vtss_phy_timestamp_t(const mesa_phy_timestamp_t *in, vtss_phy_timestamp_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_timestamp_t *tmp = (const vtss_phy_timestamp_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_sertod_conf_t_to_mesa_phy_ts_sertod_conf_t(const vtss_phy_ts_sertod_conf_t *in, mesa_phy_ts_sertod_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_sertod_conf_t *tmp = (const mesa_phy_ts_sertod_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_sertod_conf_t_to_vtss_phy_ts_sertod_conf_t(const mesa_phy_ts_sertod_conf_t *in, vtss_phy_ts_sertod_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_sertod_conf_t *tmp = (const vtss_phy_ts_sertod_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_todadj_status_t_to_mesa_phy_ts_todadj_status_t(const vtss_phy_ts_todadj_status_t *in, mesa_phy_ts_todadj_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_todadj_status_t *tmp = (const mesa_phy_ts_todadj_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_todadj_status_t_to_vtss_phy_ts_todadj_status_t(const mesa_phy_ts_todadj_status_t *in, vtss_phy_ts_todadj_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_todadj_status_t *tmp = (const vtss_phy_ts_todadj_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ltc_freq_synth_t_to_mesa_phy_ltc_freq_synth_t(const vtss_phy_ltc_freq_synth_t *in, mesa_phy_ltc_freq_synth_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ltc_freq_synth_t *tmp = (const mesa_phy_ltc_freq_synth_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ltc_freq_synth_t_to_vtss_phy_ltc_freq_synth_t(const mesa_phy_ltc_freq_synth_t *in, vtss_phy_ltc_freq_synth_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ltc_freq_synth_t *tmp = (const vtss_phy_ltc_freq_synth_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_vtss_phy_daisy_chain_conf_t_to_mesa_phy_daisy_chain_conf_t(const vtss_phy_daisy_chain_conf_t *in, mesa_phy_daisy_chain_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_daisy_chain_conf_t *tmp = (const mesa_phy_daisy_chain_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
#ifdef VTSS_CHIP_CU_PHY
inline static mesa_rc mesa_conv_mesa_phy_daisy_chain_conf_t_to_vtss_phy_daisy_chain_conf_t(const mesa_phy_daisy_chain_conf_t *in, vtss_phy_daisy_chain_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_daisy_chain_conf_t *tmp = (const vtss_phy_daisy_chain_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_fifo_status_t_to_mesa_phy_ts_fifo_status_t(const vtss_phy_ts_fifo_status_t *in, mesa_phy_ts_fifo_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_fifo_status_t *tmp = (const mesa_phy_ts_fifo_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_fifo_status_t_to_vtss_phy_ts_fifo_status_t(const mesa_phy_ts_fifo_status_t *in, vtss_phy_ts_fifo_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_fifo_status_t *tmp = (const vtss_phy_ts_fifo_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_fifo_sig_t_to_mesa_phy_ts_fifo_sig_t(const vtss_phy_ts_fifo_sig_t *in, mesa_phy_ts_fifo_sig_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_fifo_sig_t *tmp = (const mesa_phy_ts_fifo_sig_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_fifo_sig_t_to_vtss_phy_ts_fifo_sig_t(const mesa_phy_ts_fifo_sig_t *in, vtss_phy_ts_fifo_sig_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_fifo_sig_t *tmp = (const vtss_phy_ts_fifo_sig_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_fifo_read_to_mesa_phy_ts_fifo_read(const vtss_phy_ts_fifo_read *in, mesa_phy_ts_fifo_read *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_fifo_read *tmp = (const mesa_phy_ts_fifo_read *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_fifo_read_to_vtss_phy_ts_fifo_read(const mesa_phy_ts_fifo_read *in, vtss_phy_ts_fifo_read *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_fifo_read *tmp = (const vtss_phy_ts_fifo_read *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_encap_t_to_mesa_phy_ts_encap_t(const vtss_phy_ts_encap_t *in, mesa_phy_ts_encap_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(const mesa_phy_ts_encap_t *in, vtss_phy_ts_encap_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_engine_t_to_mesa_phy_ts_engine_t(const vtss_phy_ts_engine_t *in, mesa_phy_ts_engine_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_engine_t *tmp = (const mesa_phy_ts_engine_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_engine_t_to_vtss_phy_ts_engine_t(const mesa_phy_ts_engine_t *in, vtss_phy_ts_engine_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_engine_t *tmp = (const vtss_phy_ts_engine_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_engine_flow_match_t_to_mesa_phy_ts_engine_flow_match_t(const vtss_phy_ts_engine_flow_match_t *in, mesa_phy_ts_engine_flow_match_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_engine_flow_match_t *tmp = (const mesa_phy_ts_engine_flow_match_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_engine_flow_match_t_to_vtss_phy_ts_engine_flow_match_t(const mesa_phy_ts_engine_flow_match_t *in, vtss_phy_ts_engine_flow_match_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_engine_flow_match_t *tmp = (const vtss_phy_ts_engine_flow_match_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_eng_init_conf_t_to_mesa_phy_ts_eng_init_conf_t(const vtss_phy_ts_eng_init_conf_t *in, mesa_phy_ts_eng_init_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_eng_init_conf_t_to_vtss_phy_ts_eng_init_conf_t(const mesa_phy_ts_eng_init_conf_t *in, vtss_phy_ts_eng_init_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(const vtss_phy_ts_eth_flow_conf_t *in, mesa_phy_ts_eth_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(const mesa_phy_ts_eth_flow_conf_t *in, vtss_phy_ts_eth_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(const vtss_phy_ts_eth_conf_t *in, mesa_phy_ts_eth_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(const mesa_phy_ts_eth_conf_t *in, vtss_phy_ts_eth_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(const vtss_phy_ts_ip_flow_conf_t *in, mesa_phy_ts_ip_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(const mesa_phy_ts_ip_flow_conf_t *in, vtss_phy_ts_ip_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ip_conf_t_to_mesa_phy_ts_ip_conf_t(const vtss_phy_ts_ip_conf_t *in, mesa_phy_ts_ip_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_ip_conf_t_to_vtss_phy_ts_ip_conf_t(const mesa_phy_ts_ip_conf_t *in, vtss_phy_ts_ip_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_mpls_lvl_rng_t_to_mesa_phy_ts_mpls_lvl_rng_t(const vtss_phy_ts_mpls_lvl_rng_t *in, mesa_phy_ts_mpls_lvl_rng_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_mpls_lvl_rng_t *tmp = (const mesa_phy_ts_mpls_lvl_rng_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_mpls_lvl_rng_t_to_vtss_phy_ts_mpls_lvl_rng_t(const mesa_phy_ts_mpls_lvl_rng_t *in, vtss_phy_ts_mpls_lvl_rng_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_mpls_lvl_rng_t *tmp = (const vtss_phy_ts_mpls_lvl_rng_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(const vtss_phy_ts_mpls_flow_conf_t *in, mesa_phy_ts_mpls_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(const mesa_phy_ts_mpls_flow_conf_t *in, vtss_phy_ts_mpls_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_mpls_conf_t_to_mesa_phy_ts_mpls_conf_t(const vtss_phy_ts_mpls_conf_t *in, mesa_phy_ts_mpls_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_mpls_conf_t_to_vtss_phy_ts_mpls_conf_t(const mesa_phy_ts_mpls_conf_t *in, vtss_phy_ts_mpls_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ach_conf_t_to_mesa_phy_ts_ach_conf_t(const vtss_phy_ts_ach_conf_t *in, mesa_phy_ts_ach_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ach_conf_t *tmp = (const mesa_phy_ts_ach_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ach_conf_t_to_vtss_phy_ts_ach_conf_t(const mesa_phy_ts_ach_conf_t *in, vtss_phy_ts_ach_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ach_conf_t *tmp = (const vtss_phy_ts_ach_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_gen_conf_t_to_mesa_phy_ts_gen_conf_t(const vtss_phy_ts_gen_conf_t *in, mesa_phy_ts_gen_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_gen_conf_t *tmp = (const mesa_phy_ts_gen_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_gen_conf_t_to_vtss_phy_ts_gen_conf_t(const mesa_phy_ts_gen_conf_t *in, vtss_phy_ts_gen_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_gen_conf_t *tmp = (const vtss_phy_ts_gen_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ptp_engine_flow_conf_t_to_mesa_phy_ts_ptp_engine_flow_conf_t(const vtss_phy_ts_ptp_engine_flow_conf_t *in, mesa_phy_ts_ptp_engine_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_ptp_engine_flow_conf_t_to_vtss_phy_ts_ptp_engine_flow_conf_t(const mesa_phy_ts_ptp_engine_flow_conf_t *in, vtss_phy_ts_ptp_engine_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_oam_engine_flow_conf_t_to_mesa_phy_ts_oam_engine_flow_conf_t(const vtss_phy_ts_oam_engine_flow_conf_t *in, mesa_phy_ts_oam_engine_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_oam_engine_flow_conf_t_to_vtss_phy_ts_oam_engine_flow_conf_t(const mesa_phy_ts_oam_engine_flow_conf_t *in, vtss_phy_ts_oam_engine_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_generic_flow_conf_t_to_mesa_phy_ts_generic_flow_conf_t(const vtss_phy_ts_generic_flow_conf_t *in, mesa_phy_ts_generic_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_generic_flow_conf_t_to_vtss_phy_ts_generic_flow_conf_t(const mesa_phy_ts_generic_flow_conf_t *in, vtss_phy_ts_generic_flow_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_engine_flow_conf_t_to_mesa_phy_ts_engine_flow_conf_t(const vtss_phy_ts_engine_flow_conf_t *in, mesa_phy_ts_engine_flow_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_engine_flow_conf_t *tmp = (const mesa_phy_ts_engine_flow_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_engine_flow_conf_t_to_vtss_phy_ts_engine_flow_conf_t(const mesa_phy_ts_engine_flow_conf_t *in, vtss_phy_ts_engine_flow_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_engine_flow_conf_t *tmp = (const vtss_phy_ts_engine_flow_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ptp_conf_t_to_mesa_phy_ts_ptp_conf_t(const vtss_phy_ts_ptp_conf_t *in, mesa_phy_ts_ptp_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ptp_conf_t *tmp = (const mesa_phy_ts_ptp_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ptp_conf_t_to_vtss_phy_ts_ptp_conf_t(const mesa_phy_ts_ptp_conf_t *in, vtss_phy_ts_ptp_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ptp_conf_t *tmp = (const vtss_phy_ts_ptp_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ptp_clock_mode_t_to_mesa_phy_ts_ptp_clock_mode_t(const vtss_phy_ts_ptp_clock_mode_t *in, mesa_phy_ts_ptp_clock_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ptp_clock_mode_t *tmp = (const mesa_phy_ts_ptp_clock_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ptp_clock_mode_t_to_vtss_phy_ts_ptp_clock_mode_t(const mesa_phy_ts_ptp_clock_mode_t *in, vtss_phy_ts_ptp_clock_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ptp_clock_mode_t *tmp = (const vtss_phy_ts_ptp_clock_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ptp_delaym_type_t_to_mesa_phy_ts_ptp_delaym_type_t(const vtss_phy_ts_ptp_delaym_type_t *in, mesa_phy_ts_ptp_delaym_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ptp_delaym_type_t *tmp = (const mesa_phy_ts_ptp_delaym_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ptp_delaym_type_t_to_vtss_phy_ts_ptp_delaym_type_t(const mesa_phy_ts_ptp_delaym_type_t *in, vtss_phy_ts_ptp_delaym_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ptp_delaym_type_t *tmp = (const vtss_phy_ts_ptp_delaym_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ptp_engine_action_t_to_mesa_phy_ts_ptp_engine_action_t(const vtss_phy_ts_ptp_engine_action_t *in, mesa_phy_ts_ptp_engine_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ptp_engine_action_t *tmp = (const mesa_phy_ts_ptp_engine_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ptp_engine_action_t_to_vtss_phy_ts_ptp_engine_action_t(const mesa_phy_ts_ptp_engine_action_t *in, vtss_phy_ts_ptp_engine_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ptp_engine_action_t *tmp = (const vtss_phy_ts_ptp_engine_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_y1731_oam_delaym_type_t_to_mesa_phy_ts_y1731_oam_delaym_type_t(const vtss_phy_ts_y1731_oam_delaym_type_t *in, mesa_phy_ts_y1731_oam_delaym_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_y1731_oam_delaym_type_t *tmp = (const mesa_phy_ts_y1731_oam_delaym_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_y1731_oam_delaym_type_t_to_vtss_phy_ts_y1731_oam_delaym_type_t(const mesa_phy_ts_y1731_oam_delaym_type_t *in, vtss_phy_ts_y1731_oam_delaym_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_y1731_oam_delaym_type_t *tmp = (const vtss_phy_ts_y1731_oam_delaym_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t_to_mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t(const vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t *in, mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t *tmp = (const mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t_to_vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t(const mesa_phy_ts_ietf_mpls_ach_oam_delaym_type_t *in, vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t *tmp = (const vtss_phy_ts_ietf_mpls_ach_oam_delaym_type_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_y1731_oam_conf_t_to_mesa_phy_ts_y1731_oam_conf_t(const vtss_phy_ts_y1731_oam_conf_t *in, mesa_phy_ts_y1731_oam_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_y1731_oam_conf_t *tmp = (const mesa_phy_ts_y1731_oam_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_y1731_oam_conf_t_to_vtss_phy_ts_y1731_oam_conf_t(const mesa_phy_ts_y1731_oam_conf_t *in, vtss_phy_ts_y1731_oam_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_y1731_oam_conf_t *tmp = (const vtss_phy_ts_y1731_oam_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t_to_mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t(const vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t *in, mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t *tmp = (const mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t_to_vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t(const mesa_phy_ts_ietf_mpls_ach_oam_ts_format_t *in, vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t *tmp = (const vtss_phy_ts_ietf_mpls_ach_oam_ts_format_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_ietf_mpls_ach_oam_conf_t_to_mesa_phy_ts_ietf_mpls_ach_oam_conf_t(const vtss_phy_ts_ietf_mpls_ach_oam_conf_t *in, mesa_phy_ts_ietf_mpls_ach_oam_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_ietf_mpls_ach_oam_conf_t *tmp = (const mesa_phy_ts_ietf_mpls_ach_oam_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_ietf_mpls_ach_oam_conf_t_to_vtss_phy_ts_ietf_mpls_ach_oam_conf_t(const mesa_phy_ts_ietf_mpls_ach_oam_conf_t *in, vtss_phy_ts_ietf_mpls_ach_oam_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_ietf_mpls_ach_oam_conf_t *tmp = (const vtss_phy_ts_ietf_mpls_ach_oam_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_oam_engine_action_t_to_mesa_phy_ts_oam_engine_action_t(const vtss_phy_ts_oam_engine_action_t *in, mesa_phy_ts_oam_engine_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_oam_engine_action_t *tmp = (const mesa_phy_ts_oam_engine_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_oam_engine_action_t_to_vtss_phy_ts_oam_engine_action_t(const mesa_phy_ts_oam_engine_action_t *in, vtss_phy_ts_oam_engine_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_oam_engine_action_t *tmp = (const vtss_phy_ts_oam_engine_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_action_format_to_mesa_phy_ts_action_format(const vtss_phy_ts_action_format *in, mesa_phy_ts_action_format *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_action_format *tmp = (const mesa_phy_ts_action_format *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_action_format_to_vtss_phy_ts_action_format(const mesa_phy_ts_action_format *in, vtss_phy_ts_action_format *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_action_format *tmp = (const vtss_phy_ts_action_format *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_generic_action_t_to_mesa_phy_ts_generic_action_t(const vtss_phy_ts_generic_action_t *in, mesa_phy_ts_generic_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_generic_action_t *tmp = (const mesa_phy_ts_generic_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_generic_action_t_to_vtss_phy_ts_generic_action_t(const mesa_phy_ts_generic_action_t *in, vtss_phy_ts_generic_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_generic_action_t *tmp = (const vtss_phy_ts_generic_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_engine_action_t_to_mesa_phy_ts_engine_action_t(const vtss_phy_ts_engine_action_t *in, mesa_phy_ts_engine_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_engine_action_t *tmp = (const mesa_phy_ts_engine_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_engine_action_t_to_vtss_phy_ts_engine_action_t(const mesa_phy_ts_engine_action_t *in, vtss_phy_ts_engine_action_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_engine_action_t *tmp = (const vtss_phy_ts_engine_action_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_stats_t_to_mesa_phy_ts_stats_t(const vtss_phy_ts_stats_t *in, mesa_phy_ts_stats_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_stats_t *tmp = (const mesa_phy_ts_stats_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_stats_t_to_vtss_phy_ts_stats_t(const mesa_phy_ts_stats_t *in, vtss_phy_ts_stats_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_stats_t *tmp = (const vtss_phy_ts_stats_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_clockfreq_t_to_mesa_phy_ts_clockfreq_t(const vtss_phy_ts_clockfreq_t *in, mesa_phy_ts_clockfreq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_clockfreq_t *tmp = (const mesa_phy_ts_clockfreq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_clockfreq_t_to_vtss_phy_ts_clockfreq_t(const mesa_phy_ts_clockfreq_t *in, vtss_phy_ts_clockfreq_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_clockfreq_t *tmp = (const vtss_phy_ts_clockfreq_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_clock_src_t_to_mesa_phy_ts_clock_src_t(const vtss_phy_ts_clock_src_t *in, mesa_phy_ts_clock_src_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_clock_src_t *tmp = (const mesa_phy_ts_clock_src_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_clock_src_t_to_vtss_phy_ts_clock_src_t(const mesa_phy_ts_clock_src_t *in, vtss_phy_ts_clock_src_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_clock_src_t *tmp = (const vtss_phy_ts_clock_src_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_rxtimestamp_pos_t_to_mesa_phy_ts_rxtimestamp_pos_t(const vtss_phy_ts_rxtimestamp_pos_t *in, mesa_phy_ts_rxtimestamp_pos_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_rxtimestamp_pos_t *tmp = (const mesa_phy_ts_rxtimestamp_pos_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_rxtimestamp_pos_t_to_vtss_phy_ts_rxtimestamp_pos_t(const mesa_phy_ts_rxtimestamp_pos_t *in, vtss_phy_ts_rxtimestamp_pos_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_rxtimestamp_pos_t *tmp = (const vtss_phy_ts_rxtimestamp_pos_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_rxtimestamp_len_t_to_mesa_phy_ts_rxtimestamp_len_t(const vtss_phy_ts_rxtimestamp_len_t *in, mesa_phy_ts_rxtimestamp_len_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_rxtimestamp_len_t *tmp = (const mesa_phy_ts_rxtimestamp_len_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_rxtimestamp_len_t_to_vtss_phy_ts_rxtimestamp_len_t(const mesa_phy_ts_rxtimestamp_len_t *in, vtss_phy_ts_rxtimestamp_len_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_rxtimestamp_len_t *tmp = (const vtss_phy_ts_rxtimestamp_len_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_fifo_mode_t_to_mesa_phy_ts_fifo_mode_t(const vtss_phy_ts_fifo_mode_t *in, mesa_phy_ts_fifo_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_fifo_mode_t *tmp = (const mesa_phy_ts_fifo_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_fifo_mode_t_to_vtss_phy_ts_fifo_mode_t(const mesa_phy_ts_fifo_mode_t *in, vtss_phy_ts_fifo_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_fifo_mode_t *tmp = (const vtss_phy_ts_fifo_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_fifo_timestamp_len_t_to_mesa_phy_ts_fifo_timestamp_len_t(const vtss_phy_ts_fifo_timestamp_len_t *in, mesa_phy_ts_fifo_timestamp_len_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_fifo_timestamp_len_t *tmp = (const mesa_phy_ts_fifo_timestamp_len_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_fifo_timestamp_len_t_to_vtss_phy_ts_fifo_timestamp_len_t(const mesa_phy_ts_fifo_timestamp_len_t *in, vtss_phy_ts_fifo_timestamp_len_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_fifo_timestamp_len_t *tmp = (const vtss_phy_ts_fifo_timestamp_len_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_tc_op_mode_t_to_mesa_phy_ts_tc_op_mode_t(const vtss_phy_ts_tc_op_mode_t *in, mesa_phy_ts_tc_op_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_tc_op_mode_t *tmp = (const mesa_phy_ts_tc_op_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_tc_op_mode_t_to_vtss_phy_ts_tc_op_mode_t(const mesa_phy_ts_tc_op_mode_t *in, vtss_phy_ts_tc_op_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_tc_op_mode_t *tmp = (const vtss_phy_ts_tc_op_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_init_conf_t_to_mesa_phy_ts_init_conf_t(const vtss_phy_ts_init_conf_t *in, mesa_phy_ts_init_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_init_conf_t_to_vtss_phy_ts_init_conf_t(const mesa_phy_ts_init_conf_t *in, vtss_phy_ts_init_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_nphase_sampler_t_to_mesa_phy_ts_nphase_sampler_t(const vtss_phy_ts_nphase_sampler_t *in, mesa_phy_ts_nphase_sampler_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_nphase_sampler_t *tmp = (const mesa_phy_ts_nphase_sampler_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_nphase_sampler_t_to_vtss_phy_ts_nphase_sampler_t(const mesa_phy_ts_nphase_sampler_t *in, vtss_phy_ts_nphase_sampler_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_nphase_sampler_t *tmp = (const vtss_phy_ts_nphase_sampler_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_nphase_status_t_to_mesa_phy_ts_nphase_status_t(const vtss_phy_ts_nphase_status_t *in, mesa_phy_ts_nphase_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_nphase_status_t *tmp = (const mesa_phy_ts_nphase_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_nphase_status_t_to_vtss_phy_ts_nphase_status_t(const mesa_phy_ts_nphase_status_t *in, vtss_phy_ts_nphase_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_nphase_status_t *tmp = (const vtss_phy_ts_nphase_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_phy_ts_fifo_conf_t_to_mesa_phy_ts_fifo_conf_t(const vtss_phy_ts_fifo_conf_t *in, mesa_phy_ts_fifo_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_phy_ts_fifo_conf_t *tmp = (const mesa_phy_ts_fifo_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_mesa_phy_ts_fifo_conf_t_to_vtss_phy_ts_fifo_conf_t(const mesa_phy_ts_fifo_conf_t *in, vtss_phy_ts_fifo_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_phy_ts_fifo_conf_t *tmp = (const vtss_phy_ts_fifo_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ptp_message_type_t_to_mesa_phy_ts_ptp_message_type_t(const vtss_phy_ts_ptp_message_type_t *in, mesa_phy_ts_ptp_message_type_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_mesa_phy_ts_ptp_message_type_t_to_vtss_phy_ts_ptp_message_type_t(const mesa_phy_ts_ptp_message_type_t *in, vtss_phy_ts_ptp_message_type_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)
inline static mesa_rc mesa_conv_vtss_port_status_t_to_mesa_port_status_t(const vtss_port_status_t *in, mesa_port_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_port_status_t *tmp = (const mesa_port_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_mesa_port_status_t_to_vtss_port_status_t(const mesa_port_status_t *in, vtss_port_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_port_status_t *tmp = (const vtss_port_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
mesa_rc mesa_conv_vtss_serdes_mode_t_to_mesa_serdes_mode_t(const vtss_serdes_mode_t *in, mesa_serdes_mode_t *out); /* ag.rb:1595 */
mesa_rc mesa_conv_mesa_serdes_mode_t_to_vtss_serdes_mode_t(const mesa_serdes_mode_t *in, vtss_serdes_mode_t *out); /* ag.rb:1595 */
inline static mesa_rc mesa_conv_vtss_mac_t_to_mesa_mac_t(const vtss_mac_t *in, mesa_mac_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_mac_t *tmp = (const mesa_mac_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_mesa_mac_t_to_vtss_mac_t(const mesa_mac_t *in, vtss_mac_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_mac_t *tmp = (const vtss_mac_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_vtss_vdd_t_to_mesa_vdd_t(const vtss_vdd_t *in, mesa_vdd_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_vdd_t *tmp = (const mesa_vdd_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
inline static mesa_rc mesa_conv_mesa_vdd_t_to_vtss_vdd_t(const mesa_vdd_t *in, vtss_vdd_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_vdd_t *tmp = (const vtss_vdd_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_vtss_ewis_tti_mode_t_to_mesa_ewis_tti_mode_t(const vtss_ewis_tti_mode_t *in, mesa_ewis_tti_mode_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_mesa_ewis_tti_mode_t_to_vtss_ewis_tti_mode_t(const mesa_ewis_tti_mode_t *in, vtss_ewis_tti_mode_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(const vtss_ewis_tti_t *in, mesa_ewis_tti_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_mesa_ewis_tti_t_to_vtss_ewis_tti_t(const mesa_ewis_tti_t *in, vtss_ewis_tti_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_fault_cons_act_t_to_mesa_ewis_fault_cons_act_t(const vtss_ewis_fault_cons_act_t *in, mesa_ewis_fault_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_fault_cons_act_t *tmp = (const mesa_ewis_fault_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_fault_cons_act_t_to_vtss_ewis_fault_cons_act_t(const mesa_ewis_fault_cons_act_t *in, vtss_ewis_fault_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_fault_cons_act_t *tmp = (const vtss_ewis_fault_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_aisl_cons_act_t_to_mesa_ewis_aisl_cons_act_t(const vtss_ewis_aisl_cons_act_t *in, mesa_ewis_aisl_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_aisl_cons_act_t *tmp = (const mesa_ewis_aisl_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_aisl_cons_act_t_to_vtss_ewis_aisl_cons_act_t(const mesa_ewis_aisl_cons_act_t *in, vtss_ewis_aisl_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_aisl_cons_act_t *tmp = (const vtss_ewis_aisl_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_rdil_cons_act_t_to_mesa_ewis_rdil_cons_act_t(const vtss_ewis_rdil_cons_act_t *in, mesa_ewis_rdil_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_rdil_cons_act_t *tmp = (const mesa_ewis_rdil_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_rdil_cons_act_t_to_vtss_ewis_rdil_cons_act_t(const mesa_ewis_rdil_cons_act_t *in, vtss_ewis_rdil_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_rdil_cons_act_t *tmp = (const vtss_ewis_rdil_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_cons_act_t_to_mesa_ewis_cons_act_t(const vtss_ewis_cons_act_t *in, mesa_ewis_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_cons_act_t *tmp = (const mesa_ewis_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_cons_act_t_to_vtss_ewis_cons_act_t(const mesa_ewis_cons_act_t *in, vtss_ewis_cons_act_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_cons_act_t *tmp = (const vtss_ewis_cons_act_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_line_force_mode_t_to_mesa_ewis_line_force_mode_t(const vtss_ewis_line_force_mode_t *in, mesa_ewis_line_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_line_force_mode_t *tmp = (const mesa_ewis_line_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_line_force_mode_t_to_vtss_ewis_line_force_mode_t(const mesa_ewis_line_force_mode_t *in, vtss_ewis_line_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_line_force_mode_t *tmp = (const vtss_ewis_line_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_line_tx_force_mode_t_to_mesa_ewis_line_tx_force_mode_t(const vtss_ewis_line_tx_force_mode_t *in, mesa_ewis_line_tx_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_line_tx_force_mode_t *tmp = (const mesa_ewis_line_tx_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_line_tx_force_mode_t_to_vtss_ewis_line_tx_force_mode_t(const mesa_ewis_line_tx_force_mode_t *in, vtss_ewis_line_tx_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_line_tx_force_mode_t *tmp = (const vtss_ewis_line_tx_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_path_force_mode_t_to_mesa_ewis_path_force_mode_t(const vtss_ewis_path_force_mode_t *in, mesa_ewis_path_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_path_force_mode_t *tmp = (const mesa_ewis_path_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_path_force_mode_t_to_vtss_ewis_path_force_mode_t(const mesa_ewis_path_force_mode_t *in, vtss_ewis_path_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_path_force_mode_t *tmp = (const vtss_ewis_path_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_force_mode_t_to_mesa_ewis_force_mode_t(const vtss_ewis_force_mode_t *in, mesa_ewis_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_force_mode_t *tmp = (const mesa_ewis_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_force_mode_t_to_vtss_ewis_force_mode_t(const mesa_ewis_force_mode_t *in, vtss_ewis_force_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_force_mode_t *tmp = (const vtss_ewis_force_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_perf_cntr_mode_t_to_mesa_ewis_perf_cntr_mode_t(const vtss_ewis_perf_cntr_mode_t *in, mesa_ewis_perf_cntr_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_perf_cntr_mode_t *tmp = (const mesa_ewis_perf_cntr_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_perf_cntr_mode_t_to_vtss_ewis_perf_cntr_mode_t(const mesa_ewis_perf_cntr_mode_t *in, vtss_ewis_perf_cntr_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_perf_cntr_mode_t *tmp = (const vtss_ewis_perf_cntr_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_perf_mode_t_to_mesa_ewis_perf_mode_t(const vtss_ewis_perf_mode_t *in, mesa_ewis_perf_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_perf_mode_t *tmp = (const mesa_ewis_perf_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_perf_mode_t_to_vtss_ewis_perf_mode_t(const mesa_ewis_perf_mode_t *in, vtss_ewis_perf_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_perf_mode_t *tmp = (const vtss_ewis_perf_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_mode_t_to_mesa_ewis_mode_t(const vtss_ewis_mode_t *in, mesa_ewis_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_mode_t *tmp = (const mesa_ewis_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_mode_t_to_vtss_ewis_mode_t(const mesa_ewis_mode_t *in, vtss_ewis_mode_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_mode_t *tmp = (const vtss_ewis_mode_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_status_t_to_mesa_ewis_status_t(const vtss_ewis_status_t *in, mesa_ewis_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_status_t *tmp = (const mesa_ewis_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_status_t_to_vtss_ewis_status_t(const mesa_ewis_status_t *in, vtss_ewis_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_status_t *tmp = (const vtss_ewis_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_defects_t_to_mesa_ewis_defects_t(const vtss_ewis_defects_t *in, mesa_ewis_defects_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_defects_t *tmp = (const mesa_ewis_defects_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_defects_t_to_vtss_ewis_defects_t(const mesa_ewis_defects_t *in, vtss_ewis_defects_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_defects_t *tmp = (const vtss_ewis_defects_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_perf_t_to_mesa_ewis_perf_t(const vtss_ewis_perf_t *in, mesa_ewis_perf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_perf_t *tmp = (const mesa_ewis_perf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_perf_t_to_vtss_ewis_perf_t(const mesa_ewis_perf_t *in, vtss_ewis_perf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_perf_t *tmp = (const vtss_ewis_perf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_counter_t_to_mesa_ewis_counter_t(const vtss_ewis_counter_t *in, mesa_ewis_counter_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_counter_t *tmp = (const mesa_ewis_counter_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_counter_t_to_vtss_ewis_counter_t(const mesa_ewis_counter_t *in, vtss_ewis_counter_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_counter_t *tmp = (const vtss_ewis_counter_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_test_pattern_t_to_mesa_ewis_test_pattern_t(const vtss_ewis_test_pattern_t *in, mesa_ewis_test_pattern_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_test_pattern_t *tmp = (const mesa_ewis_test_pattern_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_test_pattern_t_to_vtss_ewis_test_pattern_t(const mesa_ewis_test_pattern_t *in, vtss_ewis_test_pattern_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_test_pattern_t *tmp = (const vtss_ewis_test_pattern_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_test_conf_t_to_mesa_ewis_test_conf_t(const vtss_ewis_test_conf_t *in, mesa_ewis_test_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_test_conf_t *tmp = (const mesa_ewis_test_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_test_conf_t_to_vtss_ewis_test_conf_t(const mesa_ewis_test_conf_t *in, vtss_ewis_test_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_test_conf_t *tmp = (const vtss_ewis_test_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_test_status_t_to_mesa_ewis_test_status_t(const vtss_ewis_test_status_t *in, mesa_ewis_test_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_test_status_t *tmp = (const mesa_ewis_test_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_test_status_t_to_vtss_ewis_test_status_t(const mesa_ewis_test_status_t *in, vtss_ewis_test_status_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_test_status_t *tmp = (const vtss_ewis_test_status_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_tx_oh_t_to_mesa_ewis_tx_oh_t(const vtss_ewis_tx_oh_t *in, mesa_ewis_tx_oh_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_tx_oh_t *tmp = (const mesa_ewis_tx_oh_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_tx_oh_t_to_vtss_ewis_tx_oh_t(const mesa_ewis_tx_oh_t *in, vtss_ewis_tx_oh_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_tx_oh_t *tmp = (const vtss_ewis_tx_oh_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_tx_oh_passthru_t_to_mesa_ewis_tx_oh_passthru_t(const vtss_ewis_tx_oh_passthru_t *in, mesa_ewis_tx_oh_passthru_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_tx_oh_passthru_t *tmp = (const mesa_ewis_tx_oh_passthru_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_tx_oh_passthru_t_to_vtss_ewis_tx_oh_passthru_t(const mesa_ewis_tx_oh_passthru_t *in, vtss_ewis_tx_oh_passthru_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_tx_oh_passthru_t *tmp = (const vtss_ewis_tx_oh_passthru_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_counter_threshold_t_to_mesa_ewis_counter_threshold_t(const vtss_ewis_counter_threshold_t *in, mesa_ewis_counter_threshold_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_counter_threshold_t *tmp = (const mesa_ewis_counter_threshold_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_counter_threshold_t_to_vtss_ewis_counter_threshold_t(const mesa_ewis_counter_threshold_t *in, vtss_ewis_counter_threshold_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_counter_threshold_t *tmp = (const vtss_ewis_counter_threshold_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_prbs31_err_inj_t_to_mesa_ewis_prbs31_err_inj_t(const vtss_ewis_prbs31_err_inj_t *in, mesa_ewis_prbs31_err_inj_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_prbs31_err_inj_t *tmp = (const mesa_ewis_prbs31_err_inj_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_prbs31_err_inj_t_to_vtss_ewis_prbs31_err_inj_t(const mesa_ewis_prbs31_err_inj_t *in, vtss_ewis_prbs31_err_inj_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_prbs31_err_inj_t *tmp = (const vtss_ewis_prbs31_err_inj_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_static_conf_t_to_mesa_ewis_static_conf_t(const vtss_ewis_static_conf_t *in, mesa_ewis_static_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_static_conf_t *tmp = (const mesa_ewis_static_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_static_conf_t_to_vtss_ewis_static_conf_t(const mesa_ewis_static_conf_t *in, vtss_ewis_static_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_static_conf_t *tmp = (const vtss_ewis_static_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_vtss_ewis_sl_conf_t_to_mesa_ewis_sl_conf_t(const vtss_ewis_sl_conf_t *in, mesa_ewis_sl_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const mesa_ewis_sl_conf_t *tmp = (const mesa_ewis_sl_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
inline static mesa_rc mesa_conv_mesa_ewis_sl_conf_t_to_vtss_ewis_sl_conf_t(const mesa_ewis_sl_conf_t *in, vtss_ewis_sl_conf_t *out) { /* ag.rb:1585 */
#ifdef __cplusplus
    static_assert(sizeof(out) == sizeof(in), "size check");
#endif // __cplusplus
    const vtss_ewis_sl_conf_t *tmp = (const vtss_ewis_sl_conf_t *)in;
    *out = *tmp;
    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_vtss_ewis_conf_t_to_mesa_ewis_conf_t(const vtss_ewis_conf_t *in, mesa_ewis_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_WIS)
#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_mesa_ewis_conf_t_to_vtss_ewis_conf_t(const mesa_ewis_conf_t *in, vtss_ewis_conf_t *out); /* ag.rb:1595 */
#endif  // defined(VTSS_FEATURE_WIS)
#if 0
mesa_rc mesa_conv_uint8_t_to_mesa_port_list_t(const BOOL in[VTSS_PORT_ARRAY_SIZE], mesa_port_list_t *out); /* ag.rb:1595 */
mesa_rc mesa_conv_mesa_port_list_t_to_uint8_t(const mesa_port_list_t *in, BOOL out[VTSS_PORT_ARRAY_SIZE]); /* ag.rb:1595 */
#endif
#ifdef __cplusplus
}
#endif
#endif // __MESA_H__
