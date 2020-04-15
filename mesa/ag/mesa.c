#include "mesa.h"

#define __RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wformat-security"
#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V1)
mesa_rc mesa_conv_vtss_afi_frm_dscr_t_to_mesa_afi_frm_dscr_t(const vtss_afi_frm_dscr_t *in, mesa_afi_frm_dscr_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: actual_fps@vtss_afi_frm_dscr_t
    out->fps = in->fps;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_afi_frm_dscr_t_to_vtss_afi_frm_dscr_t(const mesa_afi_frm_dscr_t *in, vtss_afi_frm_dscr_t *out) /* ag.rb:1687 */
{
    // skipped: actual_fps@vtss_afi_frm_dscr_t
    out->fps = in->fps;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_AFI_V1)
#endif  // defined(VTSS_FEATURE_AFI_SWC)

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_conv_vtss_afi_fast_inj_start_cfg_t_to_mesa_afi_fast_inj_start_cfg_t(const vtss_afi_fast_inj_start_cfg_t *in, mesa_afi_fast_inj_start_cfg_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: bps_actual@vtss_afi_fast_inj_start_cfg_t
    out->bps = in->bps;
    out->seq_cnt = in->seq_cnt;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_afi_fast_inj_start_cfg_t_to_vtss_afi_fast_inj_start_cfg_t(const mesa_afi_fast_inj_start_cfg_t *in, vtss_afi_fast_inj_start_cfg_t *out) /* ag.rb:1687 */
{
    // skipped: bps_actual@vtss_afi_fast_inj_start_cfg_t
    out->bps = in->bps;
    out->seq_cnt = in->seq_cnt;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_AFI_V2)
#endif  // defined(VTSS_FEATURE_AFI_SWC)

mesa_rc mesa_conv_vtss_target_type_t_to_mesa_target_type_t(const vtss_target_type_t *in, mesa_target_type_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        // skipped: VTSS_TARGET_SPARX_III_10_UM
        // skipped: VTSS_TARGET_SPARX_III_17_UM
        // skipped: VTSS_TARGET_SPARX_III_25_UM
        // skipped: VTSS_TARGET_SPARX_III_10_01
        case VTSS_TARGET_CU_PHY:
            *out = MESA_TARGET_CU_PHY;
            return VTSS_RC_OK;
        case VTSS_TARGET_10G_PHY:
            *out = MESA_TARGET_10G_PHY;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_III_11:
            *out = MESA_TARGET_SPARX_III_11;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_LITE:
            *out = MESA_TARGET_SERVAL_LITE;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL:
            *out = MESA_TARGET_SERVAL;
            return VTSS_RC_OK;
        case VTSS_TARGET_CARACAL_LITE:
            *out = MESA_TARGET_CARACAL_LITE;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_III_10:
            *out = MESA_TARGET_SPARX_III_10;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_III_18:
            *out = MESA_TARGET_SPARX_III_18;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_III_24:
            *out = MESA_TARGET_SPARX_III_24;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_III_26:
            *out = MESA_TARGET_SPARX_III_26;
            return VTSS_RC_OK;
        case VTSS_TARGET_CARACAL_1:
            *out = MESA_TARGET_CARACAL_1;
            return VTSS_RC_OK;
        case VTSS_TARGET_CARACAL_2:
            *out = MESA_TARGET_CARACAL_2;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_IV_52:
            *out = MESA_TARGET_SPARX_IV_52;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_IV_44:
            *out = MESA_TARGET_SPARX_IV_44;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_IV_80:
            *out = MESA_TARGET_SPARX_IV_80;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_IV_90:
            *out = MESA_TARGET_SPARX_IV_90;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_2:
            *out = MESA_TARGET_SERVAL_2;
            return VTSS_RC_OK;
        case VTSS_TARGET_LYNX_2:
            *out = MESA_TARGET_LYNX_2;
            return VTSS_RC_OK;
        case VTSS_TARGET_JAGUAR_2:
            *out = MESA_TARGET_JAGUAR_2;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_T:
            *out = MESA_TARGET_SERVAL_T;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_TP:
            *out = MESA_TARGET_SERVAL_TP;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_TE:
            *out = MESA_TARGET_SERVAL_TE;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_TEP:
            *out = MESA_TARGET_SERVAL_TEP;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_2_LITE:
            *out = MESA_TARGET_SERVAL_2_LITE;
            return VTSS_RC_OK;
        case VTSS_TARGET_SERVAL_TE10:
            *out = MESA_TARGET_SERVAL_TE10;
            return VTSS_RC_OK;
        case VTSS_TARGET_SPARX_IV_34:
            *out = MESA_TARGET_SPARX_IV_34;
            return VTSS_RC_OK;
        case VTSS_TARGET_7511:
            *out = MESA_TARGET_7511;
            return VTSS_RC_OK;
        case VTSS_TARGET_7512:
            *out = MESA_TARGET_7512;
            return VTSS_RC_OK;
        case VTSS_TARGET_7513:
            *out = MESA_TARGET_7513;
            return VTSS_RC_OK;
        case VTSS_TARGET_7514:
            *out = MESA_TARGET_7514;
            return VTSS_RC_OK;
        case VTSS_TARGET_7546:
            *out = MESA_TARGET_7546;
            return VTSS_RC_OK;
        case VTSS_TARGET_7549:
            *out = MESA_TARGET_7549;
            return VTSS_RC_OK;
        case VTSS_TARGET_7552:
            *out = MESA_TARGET_7552;
            return VTSS_RC_OK;
        case VTSS_TARGET_7556:
            *out = MESA_TARGET_7556;
            return VTSS_RC_OK;
        case VTSS_TARGET_7558:
            *out = MESA_TARGET_7558;
            return VTSS_RC_OK;
        case VTSS_TARGET_7546TSN:
            *out = MESA_TARGET_7546TSN;
            return VTSS_RC_OK;
        case VTSS_TARGET_7549TSN:
            *out = MESA_TARGET_7549TSN;
            return VTSS_RC_OK;
        case VTSS_TARGET_7552TSN:
            *out = MESA_TARGET_7552TSN;
            return VTSS_RC_OK;
        case VTSS_TARGET_7556TSN:
            *out = MESA_TARGET_7556TSN;
            return VTSS_RC_OK;
        case VTSS_TARGET_7558TSN:
            *out = MESA_TARGET_7558TSN;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_target_type_t_to_vtss_target_type_t(const mesa_target_type_t *in, vtss_target_type_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        // skipped: VTSS_TARGET_SPARX_III_10_UM
        // skipped: VTSS_TARGET_SPARX_III_17_UM
        // skipped: VTSS_TARGET_SPARX_III_25_UM
        // skipped: VTSS_TARGET_SPARX_III_10_01
        case MESA_TARGET_CU_PHY:
            *out = VTSS_TARGET_CU_PHY;
            return VTSS_RC_OK;
        case MESA_TARGET_10G_PHY:
            *out = VTSS_TARGET_10G_PHY;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_III_11:
            *out = VTSS_TARGET_SPARX_III_11;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_LITE:
            *out = VTSS_TARGET_SERVAL_LITE;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL:
            *out = VTSS_TARGET_SERVAL;
            return VTSS_RC_OK;
        case MESA_TARGET_CARACAL_LITE:
            *out = VTSS_TARGET_CARACAL_LITE;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_III_10:
            *out = VTSS_TARGET_SPARX_III_10;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_III_18:
            *out = VTSS_TARGET_SPARX_III_18;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_III_24:
            *out = VTSS_TARGET_SPARX_III_24;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_III_26:
            *out = VTSS_TARGET_SPARX_III_26;
            return VTSS_RC_OK;
        case MESA_TARGET_CARACAL_1:
            *out = VTSS_TARGET_CARACAL_1;
            return VTSS_RC_OK;
        case MESA_TARGET_CARACAL_2:
            *out = VTSS_TARGET_CARACAL_2;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_IV_52:
            *out = VTSS_TARGET_SPARX_IV_52;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_IV_44:
            *out = VTSS_TARGET_SPARX_IV_44;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_IV_80:
            *out = VTSS_TARGET_SPARX_IV_80;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_IV_90:
            *out = VTSS_TARGET_SPARX_IV_90;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_2:
            *out = VTSS_TARGET_SERVAL_2;
            return VTSS_RC_OK;
        case MESA_TARGET_LYNX_2:
            *out = VTSS_TARGET_LYNX_2;
            return VTSS_RC_OK;
        case MESA_TARGET_JAGUAR_2:
            *out = VTSS_TARGET_JAGUAR_2;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_T:
            *out = VTSS_TARGET_SERVAL_T;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_TP:
            *out = VTSS_TARGET_SERVAL_TP;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_TE:
            *out = VTSS_TARGET_SERVAL_TE;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_TEP:
            *out = VTSS_TARGET_SERVAL_TEP;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_2_LITE:
            *out = VTSS_TARGET_SERVAL_2_LITE;
            return VTSS_RC_OK;
        case MESA_TARGET_SERVAL_TE10:
            *out = VTSS_TARGET_SERVAL_TE10;
            return VTSS_RC_OK;
        case MESA_TARGET_SPARX_IV_34:
            *out = VTSS_TARGET_SPARX_IV_34;
            return VTSS_RC_OK;
        case MESA_TARGET_7511:
            *out = VTSS_TARGET_7511;
            return VTSS_RC_OK;
        case MESA_TARGET_7512:
            *out = VTSS_TARGET_7512;
            return VTSS_RC_OK;
        case MESA_TARGET_7513:
            *out = VTSS_TARGET_7513;
            return VTSS_RC_OK;
        case MESA_TARGET_7514:
            *out = VTSS_TARGET_7514;
            return VTSS_RC_OK;
        case MESA_TARGET_7546:
            *out = VTSS_TARGET_7546;
            return VTSS_RC_OK;
        case MESA_TARGET_7549:
            *out = VTSS_TARGET_7549;
            return VTSS_RC_OK;
        case MESA_TARGET_7552:
            *out = VTSS_TARGET_7552;
            return VTSS_RC_OK;
        case MESA_TARGET_7556:
            *out = VTSS_TARGET_7556;
            return VTSS_RC_OK;
        case MESA_TARGET_7558:
            *out = VTSS_TARGET_7558;
            return VTSS_RC_OK;
        case MESA_TARGET_7546TSN:
            *out = VTSS_TARGET_7546TSN;
            return VTSS_RC_OK;
        case MESA_TARGET_7549TSN:
            *out = VTSS_TARGET_7549TSN;
            return VTSS_RC_OK;
        case MESA_TARGET_7552TSN:
            *out = VTSS_TARGET_7552TSN;
            return VTSS_RC_OK;
        case MESA_TARGET_7556TSN:
            *out = VTSS_TARGET_7556TSN;
            return VTSS_RC_OK;
        case MESA_TARGET_7558TSN:
            *out = VTSS_TARGET_7558TSN;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_vtss_inst_create_t_to_mesa_inst_create_t(const vtss_inst_create_t *in, mesa_inst_create_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_target_type_t_to_mesa_target_type_t(&in->target, &out->target)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_inst_create_t_to_vtss_inst_create_t(const mesa_inst_create_t *in, vtss_inst_create_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_target_type_t_to_vtss_target_type_t(&in->target, &out->target)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_PORT_MUX)
mesa_rc mesa_conv_vtss_port_mux_mode_t_to_mesa_port_mux_mode_t(const vtss_port_mux_mode_t *in, mesa_port_mux_mode_t *out) /* ag.rb:1679 */
{
    switch (*in) {
#if defined(VTSS_ARCH_LUTON26)
        case VTSS_PORT_MUX_MODE_0:
            *out = MESA_PORT_MUX_MODE_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
#if defined(VTSS_ARCH_JAGUAR_2)
        case VTSS_PORT_MUX_MODE_0:
            *out = MESA_PORT_MUX_MODE_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_OCELOT)
        case VTSS_PORT_MUX_MODE_0:
            *out = MESA_PORT_MUX_MODE_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_LUTON26)
        case VTSS_PORT_MUX_MODE_1:
            *out = MESA_PORT_MUX_MODE_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
#if defined(VTSS_ARCH_JAGUAR_2)
        case VTSS_PORT_MUX_MODE_1:
            *out = MESA_PORT_MUX_MODE_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_OCELOT)
        case VTSS_PORT_MUX_MODE_1:
            *out = MESA_PORT_MUX_MODE_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_LUTON26)
        case VTSS_PORT_MUX_MODE_2:
            *out = MESA_PORT_MUX_MODE_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
#if defined(VTSS_ARCH_JAGUAR_2)
        case VTSS_PORT_MUX_MODE_2:
            *out = MESA_PORT_MUX_MODE_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_OCELOT)
        case VTSS_PORT_MUX_MODE_2:
            *out = MESA_PORT_MUX_MODE_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_JAGUAR_2)
        case VTSS_PORT_MUX_MODE_AUTO:
            *out = MESA_PORT_MUX_MODE_AUTO;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_OCELOT)
        case VTSS_PORT_MUX_MODE_3:
            *out = MESA_PORT_MUX_MODE_3;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_OCELOT)
        case VTSS_PORT_MUX_MODE_4:
            *out = MESA_PORT_MUX_MODE_4;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_OCELOT)
        case VTSS_PORT_MUX_MODE_5:
            *out = MESA_PORT_MUX_MODE_5;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_port_mux_mode_t_to_vtss_port_mux_mode_t(const mesa_port_mux_mode_t *in, vtss_port_mux_mode_t *out) /* ag.rb:1687 */
{
    switch (*in) {
#if defined(VTSS_ARCH_JAGUAR_2)
        case MESA_PORT_MUX_MODE_AUTO:
            *out = VTSS_PORT_MUX_MODE_AUTO;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_LUTON26)
        case MESA_PORT_MUX_MODE_0:
            *out = VTSS_PORT_MUX_MODE_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
#if defined(VTSS_ARCH_JAGUAR_2)
        case MESA_PORT_MUX_MODE_0:
            *out = VTSS_PORT_MUX_MODE_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_OCELOT)
        case MESA_PORT_MUX_MODE_0:
            *out = VTSS_PORT_MUX_MODE_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_LUTON26)
        case MESA_PORT_MUX_MODE_1:
            *out = VTSS_PORT_MUX_MODE_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
#if defined(VTSS_ARCH_JAGUAR_2)
        case MESA_PORT_MUX_MODE_1:
            *out = VTSS_PORT_MUX_MODE_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_OCELOT)
        case MESA_PORT_MUX_MODE_1:
            *out = VTSS_PORT_MUX_MODE_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_LUTON26)
        case MESA_PORT_MUX_MODE_2:
            *out = VTSS_PORT_MUX_MODE_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
#if defined(VTSS_ARCH_JAGUAR_2)
        case MESA_PORT_MUX_MODE_2:
            *out = VTSS_PORT_MUX_MODE_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_OCELOT)
        case MESA_PORT_MUX_MODE_2:
            *out = VTSS_PORT_MUX_MODE_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_OCELOT)
        case MESA_PORT_MUX_MODE_3:
            *out = VTSS_PORT_MUX_MODE_3;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_OCELOT)
        case MESA_PORT_MUX_MODE_4:
            *out = VTSS_PORT_MUX_MODE_4;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
#if defined(VTSS_ARCH_OCELOT)
        case MESA_PORT_MUX_MODE_5:
            *out = VTSS_PORT_MUX_MODE_5;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_OCELOT)
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_PORT_MUX)

mesa_rc mesa_conv_vtss_init_conf_t_to_mesa_init_conf_t(const vtss_init_conf_t *in, mesa_init_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: pi@vtss_init_conf_t
    out->reg_read = in->reg_read;
    out->reg_write = in->reg_write;
#if defined(VTSS_FEATURE_CLOCK)
    out->clock_read = in->clock_read;
#endif  // defined(VTSS_FEATURE_CLOCK)
#if defined(VTSS_FEATURE_CLOCK)
    out->clock_write = in->clock_write;
#endif  // defined(VTSS_FEATURE_CLOCK)
    {
        const mesa_miim_read_t *tmp = (const mesa_miim_read_t *)&in->miim_read;
#ifdef __cplusplus
        static_assert(sizeof(out.miim_read) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->miim_read = *tmp;
    }
    {
        const mesa_miim_write_t *tmp = (const mesa_miim_write_t *)&in->miim_write;
#ifdef __cplusplus
        static_assert(sizeof(out.miim_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->miim_write = *tmp;
    }
    {
        const mesa_mmd_read_t *tmp = (const mesa_mmd_read_t *)&in->mmd_read;
#ifdef __cplusplus
        static_assert(sizeof(out.mmd_read) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mmd_read = *tmp;
    }
    {
        const mesa_mmd_read_inc_t *tmp = (const mesa_mmd_read_inc_t *)&in->mmd_read_inc;
#ifdef __cplusplus
        static_assert(sizeof(out.mmd_read_inc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mmd_read_inc = *tmp;
    }
    {
        const mesa_mmd_write_t *tmp = (const mesa_mmd_write_t *)&in->mmd_write;
#ifdef __cplusplus
        static_assert(sizeof(out.mmd_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mmd_write = *tmp;
    }
    {
        const mesa_spi_read_write_t *tmp = (const mesa_spi_read_write_t *)&in->spi_read_write;
#ifdef __cplusplus
        static_assert(sizeof(out.spi_read_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->spi_read_write = *tmp;
    }
    {
        const mesa_spi_32bit_read_write_t *tmp = (const mesa_spi_32bit_read_write_t *)&in->spi_32bit_read_write;
#ifdef __cplusplus
        static_assert(sizeof(out.spi_32bit_read_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->spi_32bit_read_write = *tmp;
    }
    {
        const mesa_spi_64bit_read_write_t *tmp = (const mesa_spi_64bit_read_write_t *)&in->spi_64bit_read_write;
#ifdef __cplusplus
        static_assert(sizeof(out.spi_64bit_read_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->spi_64bit_read_write = *tmp;
    }
    out->skip_switch_reset = in->skip_switch_reset;
    out->spi_bus = in->spi_bus;
#if defined(VTSS_FEATURE_WARM_START)
    out->warm_start_enable = in->warm_start_enable;
#endif  // defined(VTSS_FEATURE_WARM_START)
#if defined(VTSS_FEATURE_WARM_START)
    {
        const mesa_restart_info_src_t *tmp = (const mesa_restart_info_src_t *)&in->restart_info_src;
#ifdef __cplusplus
        static_assert(sizeof(out.restart_info_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->restart_info_src = *tmp;
    }
#endif  // defined(VTSS_FEATURE_WARM_START)
#if defined(VTSS_FEATURE_WARM_START)
    out->restart_info_port = in->restart_info_port;
#endif  // defined(VTSS_FEATURE_WARM_START)
#if defined(VTSS_FEATURE_PORT_MUX)
    __RC(mesa_conv_vtss_port_mux_mode_t_to_mesa_port_mux_mode_t(&in->mux_mode, &out->mux_mode)); /* ag.rb:1455 */
#endif  // defined(VTSS_FEATURE_PORT_MUX)
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    {
        const mesa_serdes_macro_conf_t *tmp = (const mesa_serdes_macro_conf_t *)&in->serdes;
#ifdef __cplusplus
        static_assert(sizeof(out.serdes) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->serdes = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    out->using_ufdma = in->using_ufdma;
    out->loopback_bw_mbps = in->loopback_bw_mbps;
#if defined(VTSS_ARCH_JAGUAR_2_CE)
    {
        const mesa_qs_conf_t *tmp = (const mesa_qs_conf_t *)&in->qs_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.qs_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->qs_conf = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2_CE)
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    out->vlan_counters_disable = in->vlan_counters_disable;
#endif  // defined(VTSS_FEATURE_VLAN_COUNTERS)
#if defined(VTSS_FEATURE_PSFP)
    out->psfp_counters_enable = in->psfp_counters_enable;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_CORE_CLOCK)
    {
        const mesa_core_clock_conf_t *tmp = (const mesa_core_clock_conf_t *)&in->core_clock;
#ifdef __cplusplus
        static_assert(sizeof(out.core_clock) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->core_clock = *tmp;
    }
#endif  // defined(VTSS_FEATURE_CORE_CLOCK)
#if defined(VTSS_ARCH_LUTON26)
    out->packet_init_disable = in->packet_init_disable;
#endif  // defined(VTSS_ARCH_LUTON26)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_init_conf_t_to_vtss_init_conf_t(const mesa_init_conf_t *in, vtss_init_conf_t *out) /* ag.rb:1687 */
{
    // skipped: pi@vtss_init_conf_t
    out->reg_read = in->reg_read;
    out->reg_write = in->reg_write;
#if defined(VTSS_FEATURE_CLOCK)
    out->clock_read = in->clock_read;
#endif  // defined(VTSS_FEATURE_CLOCK)
#if defined(VTSS_FEATURE_CLOCK)
    out->clock_write = in->clock_write;
#endif  // defined(VTSS_FEATURE_CLOCK)
    {
        const vtss_miim_read_t *tmp = (const vtss_miim_read_t *)&in->miim_read;
#ifdef __cplusplus
        static_assert(sizeof(out.miim_read) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->miim_read = *tmp;
    }
    {
        const vtss_miim_write_t *tmp = (const vtss_miim_write_t *)&in->miim_write;
#ifdef __cplusplus
        static_assert(sizeof(out.miim_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->miim_write = *tmp;
    }
    {
        const vtss_mmd_read_t *tmp = (const vtss_mmd_read_t *)&in->mmd_read;
#ifdef __cplusplus
        static_assert(sizeof(out.mmd_read) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mmd_read = *tmp;
    }
    {
        const vtss_mmd_read_inc_t *tmp = (const vtss_mmd_read_inc_t *)&in->mmd_read_inc;
#ifdef __cplusplus
        static_assert(sizeof(out.mmd_read_inc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mmd_read_inc = *tmp;
    }
    {
        const vtss_mmd_write_t *tmp = (const vtss_mmd_write_t *)&in->mmd_write;
#ifdef __cplusplus
        static_assert(sizeof(out.mmd_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mmd_write = *tmp;
    }
    {
        const vtss_spi_read_write_t *tmp = (const vtss_spi_read_write_t *)&in->spi_read_write;
#ifdef __cplusplus
        static_assert(sizeof(out.spi_read_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->spi_read_write = *tmp;
    }
    {
        const vtss_spi_32bit_read_write_t *tmp = (const vtss_spi_32bit_read_write_t *)&in->spi_32bit_read_write;
#ifdef __cplusplus
        static_assert(sizeof(out.spi_32bit_read_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->spi_32bit_read_write = *tmp;
    }
    {
        const vtss_spi_64bit_read_write_t *tmp = (const vtss_spi_64bit_read_write_t *)&in->spi_64bit_read_write;
#ifdef __cplusplus
        static_assert(sizeof(out.spi_64bit_read_write) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->spi_64bit_read_write = *tmp;
    }
    out->skip_switch_reset = in->skip_switch_reset;
    out->spi_bus = in->spi_bus;
#if defined(VTSS_FEATURE_WARM_START)
    out->warm_start_enable = in->warm_start_enable;
#endif  // defined(VTSS_FEATURE_WARM_START)
#if defined(VTSS_FEATURE_WARM_START)
    {
        const vtss_restart_info_src_t *tmp = (const vtss_restart_info_src_t *)&in->restart_info_src;
#ifdef __cplusplus
        static_assert(sizeof(out.restart_info_src) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->restart_info_src = *tmp;
    }
#endif  // defined(VTSS_FEATURE_WARM_START)
#if defined(VTSS_FEATURE_WARM_START)
    out->restart_info_port = in->restart_info_port;
#endif  // defined(VTSS_FEATURE_WARM_START)
#if defined(VTSS_FEATURE_PORT_MUX)
    __RC(mesa_conv_mesa_port_mux_mode_t_to_vtss_port_mux_mode_t(&in->mux_mode, &out->mux_mode)); /* ag.rb:1455 */
#endif  // defined(VTSS_FEATURE_PORT_MUX)
#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    {
        const vtss_serdes_macro_conf_t *tmp = (const vtss_serdes_macro_conf_t *)&in->serdes;
#ifdef __cplusplus
        static_assert(sizeof(out.serdes) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->serdes = *tmp;
    }
#endif  // defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    out->using_ufdma = in->using_ufdma;
    out->loopback_bw_mbps = in->loopback_bw_mbps;
#if defined(VTSS_ARCH_JAGUAR_2_CE)
    {
        const vtss_qs_conf_t *tmp = (const vtss_qs_conf_t *)&in->qs_conf;
#ifdef __cplusplus
        static_assert(sizeof(out.qs_conf) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->qs_conf = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2_CE)
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    out->vlan_counters_disable = in->vlan_counters_disable;
#endif  // defined(VTSS_FEATURE_VLAN_COUNTERS)
#if defined(VTSS_FEATURE_PSFP)
    out->psfp_counters_enable = in->psfp_counters_enable;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_CORE_CLOCK)
    {
        const vtss_core_clock_conf_t *tmp = (const vtss_core_clock_conf_t *)&in->core_clock;
#ifdef __cplusplus
        static_assert(sizeof(out.core_clock) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->core_clock = *tmp;
    }
#endif  // defined(VTSS_FEATURE_CORE_CLOCK)
#if defined(VTSS_ARCH_LUTON26)
    out->packet_init_disable = in->packet_init_disable;
#endif  // defined(VTSS_ARCH_LUTON26)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_vtss_spi_slave_init_t_to_mesa_spi_slave_init_t(const vtss_spi_slave_init_t *in, mesa_spi_slave_init_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->reg_write = in->reg_write;
    out->reg_read = in->reg_read;
    {
        const mesa_spi_endian_t *tmp = (const mesa_spi_endian_t *)&in->endian;
#ifdef __cplusplus
        static_assert(sizeof(out.endian) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->endian = *tmp;
    }
    {
        const mesa_spi_bit_order_t *tmp = (const mesa_spi_bit_order_t *)&in->bit_order;
#ifdef __cplusplus
        static_assert(sizeof(out.bit_order) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->bit_order = *tmp;
    }
    out->padding = in->padding;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_spi_slave_init_t_to_vtss_spi_slave_init_t(const mesa_spi_slave_init_t *in, vtss_spi_slave_init_t *out) /* ag.rb:1687 */
{
    out->reg_write = in->reg_write;
    out->reg_read = in->reg_read;
    {
        const vtss_spi_endian_t *tmp = (const vtss_spi_endian_t *)&in->endian;
#ifdef __cplusplus
        static_assert(sizeof(out.endian) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->endian = *tmp;
    }
    {
        const vtss_spi_bit_order_t *tmp = (const vtss_spi_bit_order_t *)&in->bit_order;
#ifdef __cplusplus
        static_assert(sizeof(out.bit_order) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->bit_order = *tmp;
    }
    out->padding = in->padding;

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_mac_table_entry_t_to_mesa_mac_table_entry_t(const vtss_mac_table_entry_t *in, mesa_mac_table_entry_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_vid_mac_t *tmp = (const mesa_vid_mac_t *)&in->vid_mac;
#ifdef __cplusplus
        static_assert(sizeof(out.vid_mac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->vid_mac = *tmp;
    }
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->destination, &out->destination)); /* ag.rb:1455 */
    out->copy_to_cpu = in->copy_to_cpu;
    out->copy_to_cpu_smac = in->copy_to_cpu_smac;
    out->locked = in->locked;
    out->aged = in->aged;
    out->cpu_queue = in->cpu_queue;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_mac_table_entry_t_to_vtss_mac_table_entry_t(const mesa_mac_table_entry_t *in, vtss_mac_table_entry_t *out) /* ag.rb:1687 */
{
    {
        const vtss_vid_mac_t *tmp = (const vtss_vid_mac_t *)&in->vid_mac;
#ifdef __cplusplus
        static_assert(sizeof(out.vid_mac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->vid_mac = *tmp;
    }
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->destination, out->destination)); /* ag.rb:1455 */
    out->copy_to_cpu = in->copy_to_cpu;
    out->copy_to_cpu_smac = in->copy_to_cpu_smac;
    out->locked = in->locked;
    out->aged = in->aged;
    out->cpu_queue = in->cpu_queue;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vlan_port_conf_t_to_mesa_vlan_port_conf_t(const vtss_vlan_port_conf_t *in, mesa_vlan_port_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: s_etype@vtss_vlan_port_conf_t
    {
        const mesa_vlan_port_type_t *tmp = (const mesa_vlan_port_type_t *)&in->port_type;
#ifdef __cplusplus
        static_assert(sizeof(out.port_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->port_type = *tmp;
    }
    out->pvid = in->pvid;
    out->untagged_vid = in->untagged_vid;
    {
        const mesa_vlan_frame_t *tmp = (const mesa_vlan_frame_t *)&in->frame_type;
#ifdef __cplusplus
        static_assert(sizeof(out.frame_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->frame_type = *tmp;
    }
    out->ingress_filter = in->ingress_filter;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vlan_port_conf_t_to_vtss_vlan_port_conf_t(const mesa_vlan_port_conf_t *in, vtss_vlan_port_conf_t *out) /* ag.rb:1687 */
{
    // skipped: s_etype@vtss_vlan_port_conf_t
    {
        const vtss_vlan_port_type_t *tmp = (const vtss_vlan_port_type_t *)&in->port_type;
#ifdef __cplusplus
        static_assert(sizeof(out.port_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->port_type = *tmp;
    }
    out->pvid = in->pvid;
    out->untagged_vid = in->untagged_vid;
    {
        const vtss_vlan_frame_t *tmp = (const vtss_vlan_frame_t *)&in->frame_type;
#ifdef __cplusplus
        static_assert(sizeof(out.frame_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->frame_type = *tmp;
    }
    out->ingress_filter = in->ingress_filter;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vlan_vid_conf_t_to_mesa_vlan_vid_conf_t(const vtss_vlan_vid_conf_t *in, mesa_vlan_vid_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->learning = in->learning;
    out->flooding = in->flooding;
    out->mirror = in->mirror;
#if defined(VTSS_FEATURE_VLAN_SVL)
    out->fid = in->fid;
#endif  // defined(VTSS_FEATURE_VLAN_SVL)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vlan_vid_conf_t_to_vtss_vlan_vid_conf_t(const mesa_vlan_vid_conf_t *in, vtss_vlan_vid_conf_t *out) /* ag.rb:1687 */
{
    out->learning = in->learning;
    out->flooding = in->flooding;
    out->mirror = in->mirror;
#if defined(VTSS_FEATURE_VLAN_SVL)
    out->fid = in->fid;
#endif  // defined(VTSS_FEATURE_VLAN_SVL)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vce_mac_t_to_mesa_vce_mac_t(const vtss_vce_mac_t *in, mesa_vce_mac_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_vcap_bit_t *tmp = (const mesa_vcap_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const mesa_vcap_bit_t *tmp = (const mesa_vcap_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
#if defined(VTSS_FEATURE_VCL_KEY_DMAC)
    {
        const mesa_vcap_u48_t *tmp = (const mesa_vcap_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_VCL_KEY_DMAC)
    {
        const mesa_vcap_u48_t *tmp = (const mesa_vcap_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vce_mac_t_to_vtss_vce_mac_t(const mesa_vce_mac_t *in, vtss_vce_mac_t *out) /* ag.rb:1687 */
{
    {
        const vtss_vcap_bit_t *tmp = (const vtss_vcap_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const vtss_vcap_bit_t *tmp = (const vtss_vcap_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
#if defined(VTSS_FEATURE_VCL_KEY_DMAC)
    {
        const vtss_vcap_u48_t *tmp = (const vtss_vcap_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_VCL_KEY_DMAC)
    {
        const vtss_vcap_u48_t *tmp = (const vtss_vcap_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vce_frame_ipv4_t_to_mesa_vce_frame_ipv4_t(const vtss_vce_frame_ipv4_t *in, mesa_vce_frame_ipv4_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_vcap_bit_t *tmp = (const mesa_vcap_bit_t *)&in->fragment;
#ifdef __cplusplus
        static_assert(sizeof(out.fragment) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->fragment = *tmp;
    }
    {
        const mesa_vcap_bit_t *tmp = (const mesa_vcap_bit_t *)&in->options;
#ifdef __cplusplus
        static_assert(sizeof(out.options) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->options = *tmp;
    }
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const mesa_vcap_u8_t *tmp = (const mesa_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const mesa_vcap_ip_t *tmp = (const mesa_vcap_ip_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const mesa_vcap_ip_t *tmp = (const mesa_vcap_ip_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vce_frame_ipv4_t_to_vtss_vce_frame_ipv4_t(const mesa_vce_frame_ipv4_t *in, vtss_vce_frame_ipv4_t *out) /* ag.rb:1687 */
{
    {
        const vtss_vcap_bit_t *tmp = (const vtss_vcap_bit_t *)&in->fragment;
#ifdef __cplusplus
        static_assert(sizeof(out.fragment) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->fragment = *tmp;
    }
    {
        const vtss_vcap_bit_t *tmp = (const vtss_vcap_bit_t *)&in->options;
#ifdef __cplusplus
        static_assert(sizeof(out.options) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->options = *tmp;
    }
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const vtss_vcap_u8_t *tmp = (const vtss_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const vtss_vcap_ip_t *tmp = (const vtss_vcap_ip_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const vtss_vcap_ip_t *tmp = (const vtss_vcap_ip_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vce_frame_ipv6_t_to_mesa_vce_frame_ipv6_t(const vtss_vce_frame_ipv6_t *in, mesa_vce_frame_ipv6_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const mesa_vcap_u8_t *tmp = (const mesa_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const mesa_vcap_u128_t *tmp = (const mesa_vcap_u128_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const mesa_vcap_u128_t *tmp = (const mesa_vcap_u128_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vce_frame_ipv6_t_to_vtss_vce_frame_ipv6_t(const mesa_vce_frame_ipv6_t *in, vtss_vce_frame_ipv6_t *out) /* ag.rb:1687 */
{
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const vtss_vcap_u8_t *tmp = (const vtss_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const vtss_vcap_u128_t *tmp = (const vtss_vcap_u128_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const vtss_vcap_u128_t *tmp = (const vtss_vcap_u128_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_VCL_KEY_DIP)
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vce_key_t_to_mesa_vce_key_t(const vtss_vce_key_t *in, mesa_vce_key_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_vce_mac_t_to_mesa_vce_mac_t(&in->mac, &out->mac)); /* ag.rb:1455 */
    {
        const mesa_vce_tag_t *tmp = (const mesa_vce_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const mesa_vce_tag_t *tmp = (const mesa_vce_tag_t *)&in->inner_tag;
#ifdef __cplusplus
        static_assert(sizeof(out.inner_tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->inner_tag = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const mesa_vce_type_t *tmp = (const mesa_vce_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }

    return mesa_conv2_vtss_vce_key_t_to_mesa_vce_key_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_vce_key_t_to_vtss_vce_key_t(const mesa_vce_key_t *in, vtss_vce_key_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_vce_mac_t_to_vtss_vce_mac_t(&in->mac, &out->mac)); /* ag.rb:1455 */
    {
        const vtss_vce_tag_t *tmp = (const vtss_vce_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const vtss_vce_tag_t *tmp = (const vtss_vce_tag_t *)&in->inner_tag;
#ifdef __cplusplus
        static_assert(sizeof(out.inner_tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->inner_tag = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const vtss_vce_type_t *tmp = (const vtss_vce_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }

    return mesa_conv2_mesa_vce_key_t_to_vtss_vce_key_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vce_action_t_to_mesa_vce_action_t(const vtss_vce_action_t *in, mesa_vce_action_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->vid = in->vid;
    out->policy_no = in->policy_no;
    out->pop_enable = in->pop_enable;
    out->pop_cnt = in->pop_cnt;
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    {
        const mesa_imap_sel_t *tmp = (const mesa_imap_sel_t *)&in->map_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.map_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->map_sel = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP)
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    out->map_id = in->map_id;
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP)
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_id = in->flow_id;
#endif  // defined(VTSS_FEATURE_XFLOW)
#if defined(VTSS_FEATURE_XFLOW)
    {
        const mesa_oam_detect_t *tmp = (const mesa_oam_detect_t *)&in->oam_detect;
#ifdef __cplusplus
        static_assert(sizeof(out.oam_detect) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->oam_detect = *tmp;
    }
#endif  // defined(VTSS_FEATURE_XFLOW)
    out->prio_enable = in->prio_enable;
    out->prio = in->prio;
    out->dp_enable = in->dp_enable;
    out->dp = in->dp;
    out->dscp_enable = in->dscp_enable;
    out->dscp = in->dscp;
    out->pcp_enable = in->pcp_enable;
    out->pcp = in->pcp;
    out->dei_enable = in->dei_enable;
    out->dei = in->dei;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vce_action_t_to_vtss_vce_action_t(const mesa_vce_action_t *in, vtss_vce_action_t *out) /* ag.rb:1687 */
{
    out->vid = in->vid;
    out->policy_no = in->policy_no;
    out->pop_enable = in->pop_enable;
    out->pop_cnt = in->pop_cnt;
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    {
        const vtss_imap_sel_t *tmp = (const vtss_imap_sel_t *)&in->map_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.map_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->map_sel = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP)
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    out->map_id = in->map_id;
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP)
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_id = in->flow_id;
#endif  // defined(VTSS_FEATURE_XFLOW)
#if defined(VTSS_FEATURE_XFLOW)
    {
        const vtss_oam_detect_t *tmp = (const vtss_oam_detect_t *)&in->oam_detect;
#ifdef __cplusplus
        static_assert(sizeof(out.oam_detect) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->oam_detect = *tmp;
    }
#endif  // defined(VTSS_FEATURE_XFLOW)
    out->prio_enable = in->prio_enable;
    out->prio = in->prio;
    out->dp_enable = in->dp_enable;
    out->dp = in->dp;
    out->dscp_enable = in->dscp_enable;
    out->dscp = in->dscp;
    out->pcp_enable = in->pcp_enable;
    out->pcp = in->pcp;
    out->dei_enable = in->dei_enable;
    out->dei = in->dei;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vce_t_to_mesa_vce_t(const vtss_vce_t *in, mesa_vce_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->id = in->id;
    __RC(mesa_conv_vtss_vce_key_t_to_mesa_vce_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_vce_action_t_to_mesa_vce_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vce_t_to_vtss_vce_t(const mesa_vce_t *in, vtss_vce_t *out) /* ag.rb:1687 */
{
    out->id = in->id;
    __RC(mesa_conv_mesa_vce_key_t_to_vtss_vce_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_vce_action_t_to_vtss_vce_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_conv_vtss_ingress_counters_t_to_mesa_ingress_counters_t(const vtss_ingress_counters_t *in, mesa_ingress_counters_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_counter_pair_t *tmp = (const mesa_counter_pair_t *)&in->rx_green;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_green) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_green = *tmp;
    }
    {
        const mesa_counter_pair_t *tmp = (const mesa_counter_pair_t *)&in->rx_yellow;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_yellow) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_yellow = *tmp;
    }
    {
        const mesa_counter_pair_t *tmp = (const mesa_counter_pair_t *)&in->rx_red;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_red) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_red = *tmp;
    }
#if defined(VTSS_FEATURE_PSFP)
    out->rx_match = in->rx_match;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_gate_pass = in->rx_gate_pass;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_gate_discard = in->rx_gate_discard;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_sdu_pass = in->rx_sdu_pass;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_sdu_discard = in->rx_sdu_discard;
#endif  // defined(VTSS_FEATURE_PSFP)
    {
        const mesa_counter_pair_t *tmp = (const mesa_counter_pair_t *)&in->rx_discard;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_discard) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_discard = *tmp;
    }
    {
        const mesa_counter_pair_t *tmp = (const mesa_counter_pair_t *)&in->tx_discard;
#ifdef __cplusplus
        static_assert(sizeof(out.tx_discard) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tx_discard = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_ingress_counters_t_to_vtss_ingress_counters_t(const mesa_ingress_counters_t *in, vtss_ingress_counters_t *out) /* ag.rb:1687 */
{
    {
        const vtss_counter_pair_t *tmp = (const vtss_counter_pair_t *)&in->rx_green;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_green) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_green = *tmp;
    }
    {
        const vtss_counter_pair_t *tmp = (const vtss_counter_pair_t *)&in->rx_yellow;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_yellow) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_yellow = *tmp;
    }
    {
        const vtss_counter_pair_t *tmp = (const vtss_counter_pair_t *)&in->rx_red;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_red) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_red = *tmp;
    }
#if defined(VTSS_FEATURE_PSFP)
    out->rx_match = in->rx_match;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_gate_pass = in->rx_gate_pass;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_gate_discard = in->rx_gate_discard;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_sdu_pass = in->rx_sdu_pass;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    out->rx_sdu_discard = in->rx_sdu_discard;
#endif  // defined(VTSS_FEATURE_PSFP)
    {
        const vtss_counter_pair_t *tmp = (const vtss_counter_pair_t *)&in->rx_discard;
#ifdef __cplusplus
        static_assert(sizeof(out.rx_discard) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rx_discard = *tmp;
    }
    {
        const vtss_counter_pair_t *tmp = (const vtss_counter_pair_t *)&in->tx_discard;
#ifdef __cplusplus
        static_assert(sizeof(out.tx_discard) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tx_discard = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_XSTAT)
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_conv_vtss_iflow_conf_t_to_mesa_iflow_conf_t(const vtss_iflow_conf_t *in, mesa_iflow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_enable = in->cnt_enable;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_id = in->cnt_id;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_XDLB)
    out->dlb_enable = in->dlb_enable;
#endif  // defined(VTSS_FEATURE_XDLB)
#if defined(VTSS_FEATURE_XDLB)
    out->dlb_id = in->dlb_id;
#endif  // defined(VTSS_FEATURE_XDLB)
#if defined(VTSS_FEATURE_VOP)
    out->voe_idx = in->voe_idx;
#endif  // defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
    out->voi_idx = in->voi_idx;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_FRER)
    {
        const mesa_frer_iflow_conf_t *tmp = (const mesa_frer_iflow_conf_t *)&in->frer;
#ifdef __cplusplus
        static_assert(sizeof(out.frer) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->frer = *tmp;
    }
#endif  // defined(VTSS_FEATURE_FRER)
#if defined(VTSS_FEATURE_PSFP)
    {
        const mesa_psfp_iflow_conf_t *tmp = (const mesa_psfp_iflow_conf_t *)&in->psfp;
#ifdef __cplusplus
        static_assert(sizeof(out.psfp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->psfp = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
    out->cut_through_disable = in->cut_through_disable;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_iflow_conf_t_to_vtss_iflow_conf_t(const mesa_iflow_conf_t *in, vtss_iflow_conf_t *out) /* ag.rb:1687 */
{
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_enable = in->cnt_enable;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_id = in->cnt_id;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_XDLB)
    out->dlb_enable = in->dlb_enable;
#endif  // defined(VTSS_FEATURE_XDLB)
#if defined(VTSS_FEATURE_XDLB)
    out->dlb_id = in->dlb_id;
#endif  // defined(VTSS_FEATURE_XDLB)
#if defined(VTSS_FEATURE_VOP)
    out->voe_idx = in->voe_idx;
#endif  // defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
    out->voi_idx = in->voi_idx;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_FRER)
    {
        const vtss_frer_iflow_conf_t *tmp = (const vtss_frer_iflow_conf_t *)&in->frer;
#ifdef __cplusplus
        static_assert(sizeof(out.frer) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->frer = *tmp;
    }
#endif  // defined(VTSS_FEATURE_FRER)
#if defined(VTSS_FEATURE_PSFP)
    {
        const vtss_psfp_iflow_conf_t *tmp = (const vtss_psfp_iflow_conf_t *)&in->psfp;
#ifdef __cplusplus
        static_assert(sizeof(out.psfp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->psfp = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
    out->cut_through_disable = in->cut_through_disable;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_XFLOW)
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_tce_key_t_to_mesa_tce_key_t(const vtss_tce_key_t *in, mesa_tce_key_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    out->vid = in->vid;
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_enable = in->flow_enable;
#endif  // defined(VTSS_FEATURE_XFLOW)
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_id = in->flow_id;
#endif  // defined(VTSS_FEATURE_XFLOW)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_tce_key_t_to_vtss_tce_key_t(const mesa_tce_key_t *in, vtss_tce_key_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    out->vid = in->vid;
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_enable = in->flow_enable;
#endif  // defined(VTSS_FEATURE_XFLOW)
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_id = in->flow_id;
#endif  // defined(VTSS_FEATURE_XFLOW)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_tce_tag_t_to_mesa_tce_tag_t(const vtss_tce_tag_t *in, mesa_tce_tag_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_tpid_sel_t *tmp = (const mesa_tpid_sel_t *)&in->tpid;
#ifdef __cplusplus
        static_assert(sizeof(out.tpid) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tpid = *tmp;
    }
    out->vid = in->vid;
    {
        const mesa_pcp_sel_t *tmp = (const mesa_pcp_sel_t *)&in->pcp_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.pcp_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->pcp_sel = *tmp;
    }
    out->pcp = in->pcp;
    {
        const mesa_dei_sel_t *tmp = (const mesa_dei_sel_t *)&in->dei_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.dei_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dei_sel = *tmp;
    }
    out->dei = in->dei;
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    out->map_id = in->map_id;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_MAP)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_tce_tag_t_to_vtss_tce_tag_t(const mesa_tce_tag_t *in, vtss_tce_tag_t *out) /* ag.rb:1687 */
{
    {
        const vtss_tpid_sel_t *tmp = (const vtss_tpid_sel_t *)&in->tpid;
#ifdef __cplusplus
        static_assert(sizeof(out.tpid) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tpid = *tmp;
    }
    out->vid = in->vid;
    {
        const vtss_pcp_sel_t *tmp = (const vtss_pcp_sel_t *)&in->pcp_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.pcp_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->pcp_sel = *tmp;
    }
    out->pcp = in->pcp;
    {
        const vtss_dei_sel_t *tmp = (const vtss_dei_sel_t *)&in->dei_sel;
#ifdef __cplusplus
        static_assert(sizeof(out.dei_sel) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dei_sel = *tmp;
    }
    out->dei = in->dei;
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    out->map_id = in->map_id;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_MAP)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_tce_action_t_to_mesa_tce_action_t(const vtss_tce_action_t *in, mesa_tce_action_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_tce_tag_t_to_mesa_tce_tag_t(&in->tag, &out->tag)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_tce_tag_t_to_mesa_tce_tag_t(&in->inner_tag, &out->inner_tag)); /* ag.rb:1455 */
    out->pop_cnt = in->pop_cnt;
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_id = in->flow_id;
#endif  // defined(VTSS_FEATURE_XFLOW)
#if defined(VTSS_FEATURE_FRER)
    {
        const mesa_tce_rtag_t *tmp = (const mesa_tce_rtag_t *)&in->rtag;
#ifdef __cplusplus
        static_assert(sizeof(out.rtag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rtag = *tmp;
    }
#endif  // defined(VTSS_FEATURE_FRER)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_tce_action_t_to_vtss_tce_action_t(const mesa_tce_action_t *in, vtss_tce_action_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_tce_tag_t_to_vtss_tce_tag_t(&in->tag, &out->tag)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_tce_tag_t_to_vtss_tce_tag_t(&in->inner_tag, &out->inner_tag)); /* ag.rb:1455 */
    out->pop_cnt = in->pop_cnt;
#if defined(VTSS_FEATURE_XFLOW)
    out->flow_id = in->flow_id;
#endif  // defined(VTSS_FEATURE_XFLOW)
#if defined(VTSS_FEATURE_FRER)
    {
        const vtss_tce_rtag_t *tmp = (const vtss_tce_rtag_t *)&in->rtag;
#ifdef __cplusplus
        static_assert(sizeof(out.rtag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rtag = *tmp;
    }
#endif  // defined(VTSS_FEATURE_FRER)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_tce_t_to_mesa_tce_t(const vtss_tce_t *in, mesa_tce_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->id = in->id;
    __RC(mesa_conv_vtss_tce_key_t_to_mesa_tce_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_tce_action_t_to_mesa_tce_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_tce_t_to_vtss_tce_t(const mesa_tce_t *in, vtss_tce_t *out) /* ag.rb:1687 */
{
    out->id = in->id;
    __RC(mesa_conv_mesa_tce_key_t_to_vtss_tce_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_tce_action_t_to_vtss_tce_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_conv_vtss_eflow_conf_t_to_mesa_eflow_conf_t(const vtss_eflow_conf_t *in, mesa_eflow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_enable = in->cnt_enable;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_id = in->cnt_id;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_VOP)
    out->voe_idx = in->voe_idx;
#endif  // defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
    out->voi_idx = in->voi_idx;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_eflow_conf_t_to_vtss_eflow_conf_t(const mesa_eflow_conf_t *in, vtss_eflow_conf_t *out) /* ag.rb:1687 */
{
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_enable = in->cnt_enable;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_XSTAT)
    out->cnt_id = in->cnt_id;
#endif  // defined(VTSS_FEATURE_XSTAT)
#if defined(VTSS_FEATURE_VOP)
    out->voe_idx = in->voe_idx;
#endif  // defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
    out->voi_idx = in->voi_idx;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_XFLOW)
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_vlan_trans_port2grp_conf_t_to_mesa_vlan_trans_port2grp_conf_t(const vtss_vlan_trans_port2grp_conf_t *in, mesa_vlan_trans_port2grp_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: ports@vtss_vlan_trans_port2grp_conf_t
    // skipped: port_list@mesa_vlan_trans_port2grp_conf_t
    out->group_id = in->group_id;

    return mesa_conv2_vtss_vlan_trans_port2grp_conf_t_to_mesa_vlan_trans_port2grp_conf_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_vlan_trans_port2grp_conf_t_to_vtss_vlan_trans_port2grp_conf_t(const mesa_vlan_trans_port2grp_conf_t *in, vtss_vlan_trans_port2grp_conf_t *out) /* ag.rb:1687 */
{
    // skipped: port_list@mesa_vlan_trans_port2grp_conf_t
    // skipped: ports@vtss_vlan_trans_port2grp_conf_t
    out->group_id = in->group_id;

    return mesa_conv2_mesa_vlan_trans_port2grp_conf_t_to_vtss_vlan_trans_port2grp_conf_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_conv_vtss_mirror_conf_t_to_mesa_mirror_conf_t(const vtss_mirror_conf_t *in, mesa_mirror_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->port_no = in->port_no;
    out->fwd_enable = in->fwd_enable;
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const mesa_mirror_tag_t *tmp = (const mesa_mirror_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->vid = in->vid;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->pcp = in->pcp;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->dei = in->dei;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_mirror_conf_t_to_vtss_mirror_conf_t(const mesa_mirror_conf_t *in, vtss_mirror_conf_t *out) /* ag.rb:1687 */
{
    out->port_no = in->port_no;
    out->fwd_enable = in->fwd_enable;
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const vtss_mirror_tag_t *tmp = (const vtss_mirror_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->vid = in->vid;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->pcp = in->pcp;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->dei = in->dei;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_LAYER2)

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_conv_vtss_macsec_mac_counters_t_to_mesa_macsec_mac_counters_t(const vtss_macsec_mac_counters_t *in, mesa_macsec_mac_counters_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
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

mesa_rc mesa_conv_mesa_macsec_mac_counters_t_to_vtss_macsec_mac_counters_t(const mesa_macsec_mac_counters_t *in, vtss_macsec_mac_counters_t *out) /* ag.rb:1687 */
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

mesa_rc mesa_conv_vtss_debug_info_t_to_mesa_debug_info_t(const vtss_debug_info_t *in, mesa_debug_info_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
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
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    out->full = in->full;
    out->clear = in->clear;
    out->vml_format = in->vml_format;
    out->has_action = in->has_action;
    out->action = in->action;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_debug_info_t_to_vtss_debug_info_t(const mesa_debug_info_t *in, vtss_debug_info_t *out) /* ag.rb:1687 */
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
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    out->full = in->full;
    out->clear = in->clear;
    out->vml_format = in->vml_format;
    out->has_action = in->has_action;
    out->action = in->action;

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_INTERRUPTS)
mesa_rc mesa_conv_vtss_intr_t_to_mesa_intr_t(const vtss_intr_t *in, mesa_intr_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->link_change, &out->link_change)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_intr_t_to_vtss_intr_t(const mesa_intr_t *in, vtss_intr_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->link_change, out->link_change)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_INTERRUPTS)

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_conv_vtss_packet_rx_queue_conf_t_to_mesa_packet_rx_queue_conf_t(const vtss_packet_rx_queue_conf_t *in, mesa_packet_rx_queue_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: grp_map@mesa_packet_rx_queue_conf_t
    out->size = in->size;
    {
        const mesa_packet_rx_queue_npi_conf_t *tmp = (const mesa_packet_rx_queue_npi_conf_t *)&in->npi;
#ifdef __cplusplus
        static_assert(sizeof(out.npi) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->npi = *tmp;
    }
#if defined(VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER)
    out->rate = in->rate;
#endif  // defined(VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER)

    return mesa_conv2_vtss_packet_rx_queue_conf_t_to_mesa_packet_rx_queue_conf_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_packet_rx_queue_conf_t_to_vtss_packet_rx_queue_conf_t(const mesa_packet_rx_queue_conf_t *in, vtss_packet_rx_queue_conf_t *out) /* ag.rb:1687 */
{
    // skipped: grp_map@mesa_packet_rx_queue_conf_t
    out->size = in->size;
    {
        const vtss_packet_rx_queue_npi_conf_t *tmp = (const vtss_packet_rx_queue_npi_conf_t *)&in->npi;
#ifdef __cplusplus
        static_assert(sizeof(out.npi) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->npi = *tmp;
    }
#if defined(VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER)
    out->rate = in->rate;
#endif  // defined(VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER)

    return mesa_conv2_mesa_packet_rx_queue_conf_t_to_vtss_packet_rx_queue_conf_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_FEATURE_PACKET)

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_conv_vtss_packet_rx_queue_map_t_to_mesa_packet_rx_queue_map_t(const vtss_packet_rx_queue_map_t *in, mesa_packet_rx_queue_map_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->bpdu_queue = in->bpdu_queue;
    out->garp_queue = in->garp_queue;
    out->learn_queue = in->learn_queue;
    out->igmp_queue = in->igmp_queue;
    out->ipmc_ctrl_queue = in->ipmc_ctrl_queue;
    out->mac_vid_queue = in->mac_vid_queue;
    out->sflow_queue = in->sflow_queue;
    out->lrn_all_queue = in->lrn_all_queue;
#if defined(VTSS_FEATURE_LAYER3)
    out->l3_uc_queue = in->l3_uc_queue;
#endif  // defined(VTSS_FEATURE_LAYER3)
#if defined(VTSS_FEATURE_LAYER3)
    out->l3_other_queue = in->l3_other_queue;
#endif  // defined(VTSS_FEATURE_LAYER3)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_packet_rx_queue_map_t_to_vtss_packet_rx_queue_map_t(const mesa_packet_rx_queue_map_t *in, vtss_packet_rx_queue_map_t *out) /* ag.rb:1687 */
{
    out->bpdu_queue = in->bpdu_queue;
    out->garp_queue = in->garp_queue;
    out->learn_queue = in->learn_queue;
    out->igmp_queue = in->igmp_queue;
    out->ipmc_ctrl_queue = in->ipmc_ctrl_queue;
    out->mac_vid_queue = in->mac_vid_queue;
    out->sflow_queue = in->sflow_queue;
    out->lrn_all_queue = in->lrn_all_queue;
#if defined(VTSS_FEATURE_LAYER3)
    out->l3_uc_queue = in->l3_uc_queue;
#endif  // defined(VTSS_FEATURE_LAYER3)
#if defined(VTSS_FEATURE_LAYER3)
    out->l3_other_queue = in->l3_other_queue;
#endif  // defined(VTSS_FEATURE_LAYER3)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PACKET)

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_conv_vtss_packet_rx_conf_t_to_mesa_packet_rx_conf_t(const vtss_packet_rx_conf_t *in, mesa_packet_rx_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: grp_map@vtss_packet_rx_conf_t
    for (size_t i = 0; i < MESA_PACKET_RX_QUEUE_CNT; ++i) {
        __RC(mesa_conv_vtss_packet_rx_queue_conf_t_to_mesa_packet_rx_queue_conf_t(&in->queue[i], &out->queue[i])); /* ag.rb:1455 */
    }
    {
        const mesa_packet_rx_reg_t *tmp = (const mesa_packet_rx_reg_t *)&in->reg;
#ifdef __cplusplus
        static_assert(sizeof(out.reg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->reg = *tmp;
    }
    __RC(mesa_conv_vtss_packet_rx_queue_map_t_to_mesa_packet_rx_queue_map_t(&in->map, &out->map)); /* ag.rb:1455 */
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
    out->shaper_rate = in->shaper_rate;
#endif  // defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_packet_rx_conf_t_to_vtss_packet_rx_conf_t(const mesa_packet_rx_conf_t *in, vtss_packet_rx_conf_t *out) /* ag.rb:1687 */
{
    // skipped: grp_map@vtss_packet_rx_conf_t
    for (size_t i = 0; i < VTSS_PACKET_RX_QUEUE_CNT; ++i) {
        __RC(mesa_conv_mesa_packet_rx_queue_conf_t_to_vtss_packet_rx_queue_conf_t(&in->queue[i], &out->queue[i])); /* ag.rb:1455 */
    }
    {
        const vtss_packet_rx_reg_t *tmp = (const vtss_packet_rx_reg_t *)&in->reg;
#ifdef __cplusplus
        static_assert(sizeof(out.reg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->reg = *tmp;
    }
    __RC(mesa_conv_mesa_packet_rx_queue_map_t_to_vtss_packet_rx_queue_map_t(&in->map, &out->map)); /* ag.rb:1455 */
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
    out->shaper_rate = in->shaper_rate;
#endif  // defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PACKET)

#if defined(VTSS_FEATURE_PACKET)
#if defined(VTSS_FEATURE_PACKET_PIPELINE_PT)
mesa_rc mesa_conv_vtss_packet_pipeline_pt_t_to_mesa_packet_pipeline_pt_t(const vtss_packet_pipeline_pt_t *in, mesa_packet_pipeline_pt_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        // skipped: VTSS_PACKET_PIPELINE_PT_ANA_DONE
        case VTSS_PACKET_PIPELINE_PT_NONE:
            *out = MESA_PACKET_PIPELINE_PT_NONE;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_PORT_VOE:
            *out = MESA_PACKET_PIPELINE_PT_ANA_PORT_VOE;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_CL:
            *out = MESA_PACKET_PIPELINE_PT_ANA_CL;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_CLM:
            *out = MESA_PACKET_PIPELINE_PT_ANA_CLM;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_OU_VOI:
            *out = MESA_PACKET_PIPELINE_PT_ANA_OU_VOI;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_OU_SW:
            *out = MESA_PACKET_PIPELINE_PT_ANA_OU_SW;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_OU_VOE:
            *out = MESA_PACKET_PIPELINE_PT_ANA_OU_VOE;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_IN_VOE:
            *out = MESA_PACKET_PIPELINE_PT_ANA_IN_VOE;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_IN_SW:
            *out = MESA_PACKET_PIPELINE_PT_ANA_IN_SW;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_ANA_IN_VOI:
            *out = MESA_PACKET_PIPELINE_PT_ANA_IN_VOI;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_REW_IN_VOI:
            *out = MESA_PACKET_PIPELINE_PT_REW_IN_VOI;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_REW_IN_SW:
            *out = MESA_PACKET_PIPELINE_PT_REW_IN_SW;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_REW_IN_VOE:
            *out = MESA_PACKET_PIPELINE_PT_REW_IN_VOE;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_REW_OU_VOE:
            *out = MESA_PACKET_PIPELINE_PT_REW_OU_VOE;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_REW_OU_SW:
            *out = MESA_PACKET_PIPELINE_PT_REW_OU_SW;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_REW_OU_VOI:
            *out = MESA_PACKET_PIPELINE_PT_REW_OU_VOI;
            return VTSS_RC_OK;
        case VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE:
            *out = MESA_PACKET_PIPELINE_PT_REW_PORT_VOE;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_packet_pipeline_pt_t_to_vtss_packet_pipeline_pt_t(const mesa_packet_pipeline_pt_t *in, vtss_packet_pipeline_pt_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        // skipped: VTSS_PACKET_PIPELINE_PT_ANA_DONE
        case MESA_PACKET_PIPELINE_PT_NONE:
            *out = VTSS_PACKET_PIPELINE_PT_NONE;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_PORT_VOE:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_PORT_VOE;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_CL:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_CL;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_CLM:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_CLM;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_OU_VOI:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_OU_VOI;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_OU_SW:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_OU_SW;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_OU_VOE:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_OU_VOE;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_IN_VOE:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_IN_VOE;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_IN_SW:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_IN_SW;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_ANA_IN_VOI:
            *out = VTSS_PACKET_PIPELINE_PT_ANA_IN_VOI;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_REW_IN_VOI:
            *out = VTSS_PACKET_PIPELINE_PT_REW_IN_VOI;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_REW_IN_SW:
            *out = VTSS_PACKET_PIPELINE_PT_REW_IN_SW;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_REW_IN_VOE:
            *out = VTSS_PACKET_PIPELINE_PT_REW_IN_VOE;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_REW_OU_VOE:
            *out = VTSS_PACKET_PIPELINE_PT_REW_OU_VOE;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_REW_OU_SW:
            *out = VTSS_PACKET_PIPELINE_PT_REW_OU_SW;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_REW_OU_VOI:
            *out = VTSS_PACKET_PIPELINE_PT_REW_OU_VOI;
            return VTSS_RC_OK;
        case MESA_PACKET_PIPELINE_PT_REW_PORT_VOE:
            *out = VTSS_PACKET_PIPELINE_PT_REW_PORT_VOE;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_PACKET_PIPELINE_PT)
#endif  // defined(VTSS_FEATURE_PACKET)

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_conv_vtss_packet_tx_info_t_to_mesa_packet_tx_info_t(const vtss_packet_tx_info_t *in, mesa_packet_tx_info_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->switch_frm = in->switch_frm;
    out->dst_port_mask = in->dst_port_mask;
    out->dst_port = in->dst_port;
    {
        const mesa_vlan_tag_t *tmp = (const mesa_vlan_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
    out->cos = in->cos;
    out->cosid = in->cosid;
    out->dp = in->dp;
    {
        const mesa_packet_ptp_action_t *tmp = (const mesa_packet_ptp_action_t *)&in->ptp_action;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp_action) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp_action = *tmp;
    }
    out->ptp_domain = in->ptp_domain;
    out->ptp_id = in->ptp_id;
    out->ptp_timestamp = in->ptp_timestamp;
    {
        const mesa_packet_oam_type_t *tmp = (const mesa_packet_oam_type_t *)&in->oam_type;
#ifdef __cplusplus
        static_assert(sizeof(out.oam_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->oam_type = *tmp;
    }
    out->iflow_id = in->iflow_id;
    out->masquerade_port = in->masquerade_port;
    out->pdu_offset = in->pdu_offset;
#if defined(VTSS_FEATURE_AFI_SWC)
    out->afi_id = in->afi_id;
#endif  // defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_FEATURE_PACKET_PIPELINE_PT)
    __RC(mesa_conv_vtss_packet_pipeline_pt_t_to_mesa_packet_pipeline_pt_t(&in->pipeline_pt, &out->pipeline_pt)); /* ag.rb:1455 */
#endif  // defined(VTSS_FEATURE_PACKET_PIPELINE_PT)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_packet_tx_info_t_to_vtss_packet_tx_info_t(const mesa_packet_tx_info_t *in, vtss_packet_tx_info_t *out) /* ag.rb:1687 */
{
    out->switch_frm = in->switch_frm;
    out->dst_port_mask = in->dst_port_mask;
    out->dst_port = in->dst_port;
    {
        const vtss_vlan_tag_t *tmp = (const vtss_vlan_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
    out->cos = in->cos;
    out->cosid = in->cosid;
    out->dp = in->dp;
    {
        const vtss_packet_ptp_action_t *tmp = (const vtss_packet_ptp_action_t *)&in->ptp_action;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp_action) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp_action = *tmp;
    }
    out->ptp_domain = in->ptp_domain;
    out->ptp_id = in->ptp_id;
    out->ptp_timestamp = in->ptp_timestamp;
    {
        const vtss_packet_oam_type_t *tmp = (const vtss_packet_oam_type_t *)&in->oam_type;
#ifdef __cplusplus
        static_assert(sizeof(out.oam_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->oam_type = *tmp;
    }
    out->iflow_id = in->iflow_id;
    out->masquerade_port = in->masquerade_port;
    out->pdu_offset = in->pdu_offset;
#if defined(VTSS_FEATURE_AFI_SWC)
    out->afi_id = in->afi_id;
#endif  // defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_FEATURE_PACKET_PIPELINE_PT)
    __RC(mesa_conv_mesa_packet_pipeline_pt_t_to_vtss_packet_pipeline_pt_t(&in->pipeline_pt, &out->pipeline_pt)); /* ag.rb:1455 */
#endif  // defined(VTSS_FEATURE_PACKET_PIPELINE_PT)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PACKET)

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_conv_vtss_oper_mode_t_to_mesa_oper_mode_t(const vtss_oper_mode_t *in, mesa_oper_mode_t *out) /* ag.rb:1679 */
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

mesa_rc mesa_conv_mesa_oper_mode_t_to_vtss_oper_mode_t(const mesa_oper_mode_t *in, vtss_oper_mode_t *out) /* ag.rb:1687 */
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
mesa_rc mesa_conv_vtss_phy_10g_mode_t_to_mesa_phy_10g_mode_t(const vtss_phy_10g_mode_t *in, mesa_phy_10g_mode_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_oper_mode_t_to_mesa_oper_mode_t(&in->oper_mode, &out->oper_mode)); /* ag.rb:1455 */
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

mesa_rc mesa_conv_mesa_phy_10g_mode_t_to_vtss_phy_10g_mode_t(const mesa_phy_10g_mode_t *in, vtss_phy_10g_mode_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_oper_mode_t_to_vtss_oper_mode_t(&in->oper_mode, &out->oper_mode)); /* ag.rb:1455 */
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
mesa_rc mesa_conv_vtss_gpio_10g_input_t_to_mesa_gpio_10g_input_t(const vtss_gpio_10g_input_t *in, mesa_gpio_10g_input_t *out) /* ag.rb:1679 */
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

mesa_rc mesa_conv_mesa_gpio_10g_input_t_to_vtss_gpio_10g_input_t(const mesa_gpio_10g_input_t *in, vtss_gpio_10g_input_t *out) /* ag.rb:1687 */
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
mesa_rc mesa_conv_vtss_gpio_10g_gpio_mode_t_to_mesa_gpio_10g_gpio_mode_t(const vtss_gpio_10g_gpio_mode_t *in, mesa_gpio_10g_gpio_mode_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: invert_output@vtss_gpio_10g_gpio_mode_t
    {
        const mesa_10g_phy_gpio_t *tmp = (const mesa_10g_phy_gpio_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
    out->port = in->port;
    __RC(mesa_conv_vtss_gpio_10g_input_t_to_mesa_gpio_10g_input_t(&in->input, &out->input)); /* ag.rb:1455 */
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

mesa_rc mesa_conv_mesa_gpio_10g_gpio_mode_t_to_vtss_gpio_10g_gpio_mode_t(const mesa_gpio_10g_gpio_mode_t *in, vtss_gpio_10g_gpio_mode_t *out) /* ag.rb:1687 */
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
    __RC(mesa_conv_mesa_gpio_10g_input_t_to_vtss_gpio_10g_input_t(&in->input, &out->input)); /* ag.rb:1455 */
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
mesa_rc mesa_conv_vtss_phy_reset_conf_t_to_mesa_phy_reset_conf_t(const vtss_phy_reset_conf_t *in, mesa_phy_reset_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_port_interface_t_to_mesa_port_interface_t(&in->mac_if, &out->mac_if)); /* ag.rb:1455 */
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

mesa_rc mesa_conv_mesa_phy_reset_conf_t_to_vtss_phy_reset_conf_t(const mesa_phy_reset_conf_t *in, vtss_phy_reset_conf_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_port_interface_t_to_vtss_port_interface_t(&in->mac_if, &out->mac_if)); /* ag.rb:1455 */
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

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_conf_t_to_mesa_phy_conf_t(const vtss_phy_conf_t *in, mesa_phy_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
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

mesa_rc mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(const mesa_phy_conf_t *in, vtss_phy_conf_t *out) /* ag.rb:1687 */
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

mesa_rc mesa_conv_vtss_phy_power_mode_t_to_mesa_phy_power_mode_t(const vtss_phy_power_mode_t *in, mesa_phy_power_mode_t *out) /* ag.rb:1679 */
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

mesa_rc mesa_conv_mesa_phy_power_mode_t_to_vtss_phy_power_mode_t(const mesa_phy_power_mode_t *in, vtss_phy_power_mode_t *out) /* ag.rb:1687 */
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

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_conv_vtss_phy_power_conf_t_to_mesa_phy_power_conf_t(const vtss_phy_power_conf_t *in, mesa_phy_power_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_phy_power_mode_t_to_mesa_phy_power_mode_t(&in->mode, &out->mode)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_power_conf_t_to_vtss_phy_power_conf_t(const mesa_phy_power_conf_t *in, vtss_phy_power_conf_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_phy_power_mode_t_to_vtss_phy_power_mode_t(&in->mode, &out->mode)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}
#endif  // VTSS_CHIP_CU_PHY

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_encap_t_to_mesa_phy_ts_encap_t(const vtss_phy_ts_encap_t *in, mesa_phy_ts_encap_t *out) /* ag.rb:1679 */
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

mesa_rc mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(const mesa_phy_ts_encap_t *in, vtss_phy_ts_encap_t *out) /* ag.rb:1687 */
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
mesa_rc mesa_conv_vtss_phy_ts_eng_init_conf_t_to_mesa_phy_ts_eng_init_conf_t(const vtss_phy_ts_eng_init_conf_t *in, mesa_phy_ts_eng_init_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->eng_used = in->eng_used;
    __RC(mesa_conv_vtss_phy_ts_encap_t_to_mesa_phy_ts_encap_t(&in->encap_type, &out->encap_type)); /* ag.rb:1455 */
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

mesa_rc mesa_conv_mesa_phy_ts_eng_init_conf_t_to_vtss_phy_ts_eng_init_conf_t(const mesa_phy_ts_eng_init_conf_t *in, vtss_phy_ts_eng_init_conf_t *out) /* ag.rb:1687 */
{
    out->eng_used = in->eng_used;
    __RC(mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(&in->encap_type, &out->encap_type)); /* ag.rb:1455 */
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
mesa_rc mesa_conv_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(const vtss_phy_ts_eth_flow_conf_t *in, mesa_phy_ts_eth_flow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
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

    return mesa_conv2_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(const mesa_phy_ts_eth_flow_conf_t *in, vtss_phy_ts_eth_flow_conf_t *out) /* ag.rb:1687 */
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

    return mesa_conv2_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(const vtss_phy_ts_eth_conf_t *in, mesa_phy_ts_eth_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->comm_opt.pbb_en = in->comm_opt.pbb_en;
    out->comm_opt.etype = in->comm_opt.etype;
    out->comm_opt.tpid = in->comm_opt.tpid;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_vtss_phy_ts_eth_flow_conf_t_to_mesa_phy_ts_eth_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1455 */
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(const mesa_phy_ts_eth_conf_t *in, vtss_phy_ts_eth_conf_t *out) /* ag.rb:1687 */
{
    out->comm_opt.pbb_en = in->comm_opt.pbb_en;
    out->comm_opt.etype = in->comm_opt.etype;
    out->comm_opt.tpid = in->comm_opt.tpid;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_mesa_phy_ts_eth_flow_conf_t_to_vtss_phy_ts_eth_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1455 */
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(const vtss_phy_ts_ip_flow_conf_t *in, mesa_phy_ts_ip_flow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->flow_en = in->flow_en;
    out->match_mode = in->match_mode;

    return mesa_conv2_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(const mesa_phy_ts_ip_flow_conf_t *in, vtss_phy_ts_ip_flow_conf_t *out) /* ag.rb:1687 */
{
    out->flow_en = in->flow_en;
    out->match_mode = in->match_mode;

    return mesa_conv2_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ip_conf_t_to_mesa_phy_ts_ip_conf_t(const vtss_phy_ts_ip_conf_t *in, mesa_phy_ts_ip_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->comm_opt.ip_mode = in->comm_opt.ip_mode;
    out->comm_opt.sport_val = in->comm_opt.sport_val;
    out->comm_opt.sport_mask = in->comm_opt.sport_mask;
    out->comm_opt.dport_val = in->comm_opt.dport_val;
    out->comm_opt.dport_mask = in->comm_opt.dport_mask;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_vtss_phy_ts_ip_flow_conf_t_to_mesa_phy_ts_ip_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1455 */
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_ip_conf_t_to_vtss_phy_ts_ip_conf_t(const mesa_phy_ts_ip_conf_t *in, vtss_phy_ts_ip_conf_t *out) /* ag.rb:1687 */
{
    out->comm_opt.ip_mode = in->comm_opt.ip_mode;
    out->comm_opt.sport_val = in->comm_opt.sport_val;
    out->comm_opt.sport_mask = in->comm_opt.sport_mask;
    out->comm_opt.dport_val = in->comm_opt.dport_val;
    out->comm_opt.dport_mask = in->comm_opt.dport_mask;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_mesa_phy_ts_ip_flow_conf_t_to_vtss_phy_ts_ip_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1455 */
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(const vtss_phy_ts_mpls_flow_conf_t *in, mesa_phy_ts_mpls_flow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->flow_en = in->flow_en;
    out->stack_depth = in->stack_depth;
    out->stack_ref_point = in->stack_ref_point;

    return mesa_conv2_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(const mesa_phy_ts_mpls_flow_conf_t *in, vtss_phy_ts_mpls_flow_conf_t *out) /* ag.rb:1687 */
{
    out->flow_en = in->flow_en;
    out->stack_depth = in->stack_depth;
    out->stack_ref_point = in->stack_ref_point;

    return mesa_conv2_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_mpls_conf_t_to_mesa_phy_ts_mpls_conf_t(const vtss_phy_ts_mpls_conf_t *in, mesa_phy_ts_mpls_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->comm_opt.cw_en = in->comm_opt.cw_en;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_vtss_phy_ts_mpls_flow_conf_t_to_mesa_phy_ts_mpls_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1455 */
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_mpls_conf_t_to_vtss_phy_ts_mpls_conf_t(const mesa_phy_ts_mpls_conf_t *in, vtss_phy_ts_mpls_conf_t *out) /* ag.rb:1687 */
{
    out->comm_opt.cw_en = in->comm_opt.cw_en;
    for (size_t i = 0; i < 8; ++i) {
        __RC(mesa_conv_mesa_phy_ts_mpls_flow_conf_t_to_vtss_phy_ts_mpls_flow_conf_t(&in->flow_opt[i], &out->flow_opt[i])); /* ag.rb:1455 */
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP)

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_conv_vtss_phy_ts_ptp_engine_flow_conf_t_to_mesa_phy_ts_ptp_engine_flow_conf_t(const vtss_phy_ts_ptp_engine_flow_conf_t *in, mesa_phy_ts_ptp_engine_flow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_phy_ts_ip_conf_t_to_mesa_phy_ts_ip_conf_t(&in->ip1_opt, &out->ip1_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_phy_ts_ip_conf_t_to_mesa_phy_ts_ip_conf_t(&in->ip2_opt, &out->ip2_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_phy_ts_mpls_conf_t_to_mesa_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1455 */
    {
        const mesa_phy_ts_ach_conf_t *tmp = (const mesa_phy_ts_ach_conf_t *)&in->ach_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.ach_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ach_opt = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_ptp_engine_flow_conf_t_to_vtss_phy_ts_ptp_engine_flow_conf_t(const mesa_phy_ts_ptp_engine_flow_conf_t *in, vtss_phy_ts_ptp_engine_flow_conf_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_phy_ts_ip_conf_t_to_vtss_phy_ts_ip_conf_t(&in->ip1_opt, &out->ip1_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_phy_ts_ip_conf_t_to_vtss_phy_ts_ip_conf_t(&in->ip2_opt, &out->ip2_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_phy_ts_mpls_conf_t_to_vtss_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1455 */
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
mesa_rc mesa_conv_vtss_phy_ts_oam_engine_flow_conf_t_to_mesa_phy_ts_oam_engine_flow_conf_t(const vtss_phy_ts_oam_engine_flow_conf_t *in, mesa_phy_ts_oam_engine_flow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_phy_ts_mpls_conf_t_to_mesa_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1455 */
    {
        const mesa_phy_ts_ach_conf_t *tmp = (const mesa_phy_ts_ach_conf_t *)&in->ach_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.ach_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ach_opt = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_oam_engine_flow_conf_t_to_vtss_phy_ts_oam_engine_flow_conf_t(const mesa_phy_ts_oam_engine_flow_conf_t *in, vtss_phy_ts_oam_engine_flow_conf_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth2_opt, &out->eth2_opt)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_phy_ts_mpls_conf_t_to_vtss_phy_ts_mpls_conf_t(&in->mpls_opt, &out->mpls_opt)); /* ag.rb:1455 */
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
mesa_rc mesa_conv_vtss_phy_ts_generic_flow_conf_t_to_mesa_phy_ts_generic_flow_conf_t(const vtss_phy_ts_generic_flow_conf_t *in, mesa_phy_ts_generic_flow_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_phy_ts_eth_conf_t_to_mesa_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1455 */
    {
        const mesa_phy_ts_gen_conf_t *tmp = (const mesa_phy_ts_gen_conf_t *)&in->gen_opt;
#ifdef __cplusplus
        static_assert(sizeof(out.gen_opt) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->gen_opt = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_phy_ts_generic_flow_conf_t_to_vtss_phy_ts_generic_flow_conf_t(const mesa_phy_ts_generic_flow_conf_t *in, vtss_phy_ts_generic_flow_conf_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_phy_ts_eth_conf_t_to_vtss_phy_ts_eth_conf_t(&in->eth1_opt, &out->eth1_opt)); /* ag.rb:1455 */
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
mesa_rc mesa_conv_vtss_phy_ts_init_conf_t_to_mesa_phy_ts_init_conf_t(const vtss_phy_ts_init_conf_t *in, mesa_phy_ts_init_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
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

mesa_rc mesa_conv_mesa_phy_ts_init_conf_t_to_vtss_phy_ts_init_conf_t(const mesa_phy_ts_init_conf_t *in, vtss_phy_ts_init_conf_t *out) /* ag.rb:1687 */
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
mesa_rc mesa_conv_vtss_phy_ts_ptp_message_type_t_to_mesa_phy_ts_ptp_message_type_t(const vtss_phy_ts_ptp_message_type_t *in, mesa_phy_ts_ptp_message_type_t *out) /* ag.rb:1679 */
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

mesa_rc mesa_conv_mesa_phy_ts_ptp_message_type_t_to_vtss_phy_ts_ptp_message_type_t(const mesa_phy_ts_ptp_message_type_t *in, vtss_phy_ts_ptp_message_type_t *out) /* ag.rb:1687 */
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

mesa_rc mesa_conv_vtss_miim_controller_t_to_mesa_miim_controller_t(const vtss_miim_controller_t *in, mesa_miim_controller_t *out) /* ag.rb:1679 */
{
    switch (*in) {
#if defined(VTSS_FEATURE_LAYER2)
        case VTSS_MIIM_CONTROLLER_0:
            *out = MESA_MIIM_CONTROLLER_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_LAYER2)
        case VTSS_MIIM_CONTROLLER_1:
            *out = MESA_MIIM_CONTROLLER_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case VTSS_MIIM_CONTROLLER_2:
            *out = MESA_MIIM_CONTROLLER_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SPARX5)
        case VTSS_MIIM_CONTROLLER_3:
            *out = MESA_MIIM_CONTROLLER_3;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SPARX5)
        case VTSS_MIIM_CONTROLLERS:
            *out = MESA_MIIM_CONTROLLERS;
            return VTSS_RC_OK;
        case VTSS_MIIM_CONTROLLER_NONE:
            *out = MESA_MIIM_CONTROLLER_NONE;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_miim_controller_t_to_vtss_miim_controller_t(const mesa_miim_controller_t *in, vtss_miim_controller_t *out) /* ag.rb:1687 */
{
    switch (*in) {
#if defined(VTSS_FEATURE_LAYER2)
        case MESA_MIIM_CONTROLLER_0:
            *out = VTSS_MIIM_CONTROLLER_0;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_LAYER2)
        case MESA_MIIM_CONTROLLER_1:
            *out = VTSS_MIIM_CONTROLLER_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case MESA_MIIM_CONTROLLER_2:
            *out = VTSS_MIIM_CONTROLLER_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SPARX5)
        case MESA_MIIM_CONTROLLER_3:
            *out = VTSS_MIIM_CONTROLLER_3;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SPARX5)
        case MESA_MIIM_CONTROLLERS:
            *out = VTSS_MIIM_CONTROLLERS;
            return VTSS_RC_OK;
        case MESA_MIIM_CONTROLLER_NONE:
            *out = VTSS_MIIM_CONTROLLER_NONE;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_conv_vtss_port_map_t_to_mesa_port_map_t(const vtss_port_map_t *in, mesa_port_map_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->chip_port = in->chip_port;
    out->chip_no = in->chip_no;
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const mesa_internal_bw_t *tmp = (const mesa_internal_bw_t *)&in->max_bw;
#ifdef __cplusplus
        static_assert(sizeof(out.max_bw) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->max_bw = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    __RC(mesa_conv_vtss_miim_controller_t_to_mesa_miim_controller_t(&in->miim_controller, &out->miim_controller)); /* ag.rb:1455 */
    out->miim_addr = in->miim_addr;
    out->miim_chip_no = in->miim_chip_no;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_map_t_to_vtss_port_map_t(const mesa_port_map_t *in, vtss_port_map_t *out) /* ag.rb:1687 */
{
    out->chip_port = in->chip_port;
    out->chip_no = in->chip_no;
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const vtss_internal_bw_t *tmp = (const vtss_internal_bw_t *)&in->max_bw;
#ifdef __cplusplus
        static_assert(sizeof(out.max_bw) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->max_bw = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    __RC(mesa_conv_mesa_miim_controller_t_to_vtss_miim_controller_t(&in->miim_controller, &out->miim_controller)); /* ag.rb:1455 */
    out->miim_addr = in->miim_addr;
    out->miim_chip_no = in->miim_chip_no;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL)

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_conv_vtss_port_clause_37_remote_fault_t_to_mesa_port_clause_37_remote_fault_t(const vtss_port_clause_37_remote_fault_t *in, mesa_port_clause_37_remote_fault_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_PORT_CLAUSE_37_RF_LINK_OK:
            *out = MESA_PORT_CLAUSE_37_RF_LINK_OK;
            return VTSS_RC_OK;
        case VTSS_PORT_CLAUSE_37_RF_OFFLINE:
            *out = MESA_PORT_CLAUSE_37_RF_OFFLINE;
            return VTSS_RC_OK;
        case VTSS_PORT_CLAUSE_37_RF_LINK_FAILURE:
            *out = MESA_PORT_CLAUSE_37_RF_LINK_FAILURE;
            return VTSS_RC_OK;
        case VTSS_PORT_CLAUSE_37_RF_AUTONEG_ERROR:
            *out = MESA_PORT_CLAUSE_37_RF_AUTONEG_ERROR;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_port_clause_37_remote_fault_t_to_vtss_port_clause_37_remote_fault_t(const mesa_port_clause_37_remote_fault_t *in, vtss_port_clause_37_remote_fault_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_PORT_CLAUSE_37_RF_LINK_OK:
            *out = VTSS_PORT_CLAUSE_37_RF_LINK_OK;
            return VTSS_RC_OK;
        case MESA_PORT_CLAUSE_37_RF_OFFLINE:
            *out = VTSS_PORT_CLAUSE_37_RF_OFFLINE;
            return VTSS_RC_OK;
        case MESA_PORT_CLAUSE_37_RF_LINK_FAILURE:
            *out = VTSS_PORT_CLAUSE_37_RF_LINK_FAILURE;
            return VTSS_RC_OK;
        case MESA_PORT_CLAUSE_37_RF_AUTONEG_ERROR:
            *out = VTSS_PORT_CLAUSE_37_RF_AUTONEG_ERROR;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL)

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_conv_vtss_port_clause_37_adv_t_to_mesa_port_clause_37_adv_t(const vtss_port_clause_37_adv_t *in, mesa_port_clause_37_adv_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->fdx = in->fdx;
    out->hdx = in->hdx;
    out->symmetric_pause = in->symmetric_pause;
    out->asymmetric_pause = in->asymmetric_pause;
    __RC(mesa_conv_vtss_port_clause_37_remote_fault_t_to_mesa_port_clause_37_remote_fault_t(&in->remote_fault, &out->remote_fault)); /* ag.rb:1455 */
    out->acknowledge = in->acknowledge;
    out->next_page = in->next_page;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_clause_37_adv_t_to_vtss_port_clause_37_adv_t(const mesa_port_clause_37_adv_t *in, vtss_port_clause_37_adv_t *out) /* ag.rb:1687 */
{
    out->fdx = in->fdx;
    out->hdx = in->hdx;
    out->symmetric_pause = in->symmetric_pause;
    out->asymmetric_pause = in->asymmetric_pause;
    __RC(mesa_conv_mesa_port_clause_37_remote_fault_t_to_vtss_port_clause_37_remote_fault_t(&in->remote_fault, &out->remote_fault)); /* ag.rb:1455 */
    out->acknowledge = in->acknowledge;
    out->next_page = in->next_page;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL)

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_conv_vtss_port_clause_37_control_t_to_mesa_port_clause_37_control_t(const vtss_port_clause_37_control_t *in, mesa_port_clause_37_control_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->enable = in->enable;
    __RC(mesa_conv_vtss_port_clause_37_adv_t_to_mesa_port_clause_37_adv_t(&in->advertisement, &out->advertisement)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_clause_37_control_t_to_vtss_port_clause_37_control_t(const mesa_port_clause_37_control_t *in, vtss_port_clause_37_control_t *out) /* ag.rb:1687 */
{
    out->enable = in->enable;
    __RC(mesa_conv_mesa_port_clause_37_adv_t_to_vtss_port_clause_37_adv_t(&in->advertisement, &out->advertisement)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL)

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_conv_vtss_port_flow_control_conf_t_to_mesa_port_flow_control_conf_t(const vtss_port_flow_control_conf_t *in, mesa_port_flow_control_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->obey = in->obey;
    out->generate = in->generate;
    {
        const mesa_mac_t *tmp = (const mesa_mac_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
#if defined(VTSS_FEATURE_QOS)
    for (size_t i = 0; i < MESA_PRIO_ARRAY_SIZE; ++i) {
        out->pfc[i] = in->pfc[i];
    }
#endif  // defined(VTSS_FEATURE_QOS)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_flow_control_conf_t_to_vtss_port_flow_control_conf_t(const mesa_port_flow_control_conf_t *in, vtss_port_flow_control_conf_t *out) /* ag.rb:1687 */
{
    out->obey = in->obey;
    out->generate = in->generate;
    {
        const vtss_mac_t *tmp = (const vtss_mac_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
#if defined(VTSS_FEATURE_QOS)
    for (size_t i = 0; i < VTSS_PRIOS; ++i) {
        out->pfc[i] = in->pfc[i];
    }
#endif  // defined(VTSS_FEATURE_QOS)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL)

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_conv_vtss_port_conf_t_to_mesa_port_conf_t(const vtss_port_conf_t *in, mesa_port_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_port_interface_t_to_mesa_port_interface_t(&in->if_type, &out->if_type)); /* ag.rb:1455 */
    out->sd_enable = in->sd_enable;
    out->sd_active_high = in->sd_active_high;
    out->sd_internal = in->sd_internal;
    {
        const mesa_port_frame_gaps_t *tmp = (const mesa_port_frame_gaps_t *)&in->frame_gaps;
#ifdef __cplusplus
        static_assert(sizeof(out.frame_gaps) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->frame_gaps = *tmp;
    }
    out->power_down = in->power_down;
    {
        const mesa_port_speed_t *tmp = (const mesa_port_speed_t *)&in->speed;
#ifdef __cplusplus
        static_assert(sizeof(out.speed) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->speed = *tmp;
    }
    out->fdx = in->fdx;
    __RC(mesa_conv_vtss_port_flow_control_conf_t_to_mesa_port_flow_control_conf_t(&in->flow_control, &out->flow_control)); /* ag.rb:1455 */
    out->max_frame_length = in->max_frame_length;
    out->frame_length_chk = in->frame_length_chk;
    {
        const mesa_port_max_tags_t *tmp = (const mesa_port_max_tags_t *)&in->max_tags;
#ifdef __cplusplus
        static_assert(sizeof(out.max_tags) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->max_tags = *tmp;
    }
    out->exc_col_cont = in->exc_col_cont;
    out->xaui_rx_lane_flip = in->xaui_rx_lane_flip;
    out->xaui_tx_lane_flip = in->xaui_tx_lane_flip;
    {
        const mesa_port_loop_t *tmp = (const mesa_port_loop_t *)&in->loop;
#ifdef __cplusplus
        static_assert(sizeof(out.loop) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->loop = *tmp;
    }
    {
        const mesa_port_serdes_conf_t *tmp = (const mesa_port_serdes_conf_t *)&in->serdes;
#ifdef __cplusplus
        static_assert(sizeof(out.serdes) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->serdes = *tmp;
    }
#if defined(VTSS_FEATURE_PORT_PCS_CONF)
    {
        const mesa_port_pcs_conf_t *tmp = (const mesa_port_pcs_conf_t *)&in->pcs;
#ifdef __cplusplus
        static_assert(sizeof(out.pcs) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->pcs = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PORT_PCS_CONF)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_conf_t_to_vtss_port_conf_t(const mesa_port_conf_t *in, vtss_port_conf_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_port_interface_t_to_vtss_port_interface_t(&in->if_type, &out->if_type)); /* ag.rb:1455 */
    out->sd_enable = in->sd_enable;
    out->sd_active_high = in->sd_active_high;
    out->sd_internal = in->sd_internal;
    {
        const vtss_port_frame_gaps_t *tmp = (const vtss_port_frame_gaps_t *)&in->frame_gaps;
#ifdef __cplusplus
        static_assert(sizeof(out.frame_gaps) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->frame_gaps = *tmp;
    }
    out->power_down = in->power_down;
    {
        const vtss_port_speed_t *tmp = (const vtss_port_speed_t *)&in->speed;
#ifdef __cplusplus
        static_assert(sizeof(out.speed) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->speed = *tmp;
    }
    out->fdx = in->fdx;
    __RC(mesa_conv_mesa_port_flow_control_conf_t_to_vtss_port_flow_control_conf_t(&in->flow_control, &out->flow_control)); /* ag.rb:1455 */
    out->max_frame_length = in->max_frame_length;
    out->frame_length_chk = in->frame_length_chk;
    {
        const vtss_port_max_tags_t *tmp = (const vtss_port_max_tags_t *)&in->max_tags;
#ifdef __cplusplus
        static_assert(sizeof(out.max_tags) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->max_tags = *tmp;
    }
    out->exc_col_cont = in->exc_col_cont;
    out->xaui_rx_lane_flip = in->xaui_rx_lane_flip;
    out->xaui_tx_lane_flip = in->xaui_tx_lane_flip;
    {
        const vtss_port_loop_t *tmp = (const vtss_port_loop_t *)&in->loop;
#ifdef __cplusplus
        static_assert(sizeof(out.loop) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->loop = *tmp;
    }
    {
        const vtss_port_serdes_conf_t *tmp = (const vtss_port_serdes_conf_t *)&in->serdes;
#ifdef __cplusplus
        static_assert(sizeof(out.serdes) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->serdes = *tmp;
    }
#if defined(VTSS_FEATURE_PORT_PCS_CONF)
    {
        const vtss_port_pcs_conf_t *tmp = (const vtss_port_pcs_conf_t *)&in->pcs;
#ifdef __cplusplus
        static_assert(sizeof(out.pcs) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->pcs = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PORT_PCS_CONF)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL)

mesa_rc mesa_conv_vtss_port_ethernet_like_counters_t_to_mesa_port_ethernet_like_counters_t(const vtss_port_ethernet_like_counters_t *in, mesa_port_ethernet_like_counters_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsAlignmentErrors = in->dot3StatsAlignmentErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsFCSErrors = in->dot3StatsFCSErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsFrameTooLongs = in->dot3StatsFrameTooLongs;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsSymbolErrors = in->dot3StatsSymbolErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3ControlInUnknownOpcodes = in->dot3ControlInUnknownOpcodes;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3InPauseFrames = in->dot3InPauseFrames;
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsSingleCollisionFrames = in->dot3StatsSingleCollisionFrames;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsMultipleCollisionFrames = in->dot3StatsMultipleCollisionFrames;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsDeferredTransmissions = in->dot3StatsDeferredTransmissions;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsLateCollisions = in->dot3StatsLateCollisions;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsExcessiveCollisions = in->dot3StatsExcessiveCollisions;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsCarrierSenseErrors = in->dot3StatsCarrierSenseErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3OutPauseFrames = in->dot3OutPauseFrames;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_ethernet_like_counters_t_to_vtss_port_ethernet_like_counters_t(const mesa_port_ethernet_like_counters_t *in, vtss_port_ethernet_like_counters_t *out) /* ag.rb:1687 */
{
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsAlignmentErrors = in->dot3StatsAlignmentErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsFCSErrors = in->dot3StatsFCSErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsFrameTooLongs = in->dot3StatsFrameTooLongs;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsSymbolErrors = in->dot3StatsSymbolErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3ControlInUnknownOpcodes = in->dot3ControlInUnknownOpcodes;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3InPauseFrames = in->dot3InPauseFrames;
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsSingleCollisionFrames = in->dot3StatsSingleCollisionFrames;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsMultipleCollisionFrames = in->dot3StatsMultipleCollisionFrames;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsDeferredTransmissions = in->dot3StatsDeferredTransmissions;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsLateCollisions = in->dot3StatsLateCollisions;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsExcessiveCollisions = in->dot3StatsExcessiveCollisions;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3StatsCarrierSenseErrors = in->dot3StatsCarrierSenseErrors;
#endif  // defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
    out->dot3OutPauseFrames = in->dot3OutPauseFrames;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_vtss_port_counters_t_to_mesa_port_counters_t(const vtss_port_counters_t *in, mesa_port_counters_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: prop@vtss_port_counters_t
    // skipped: evc@vtss_port_counters_t
    // skipped: prio@mesa_port_counters_t
    {
        const mesa_port_rmon_counters_t *tmp = (const mesa_port_rmon_counters_t *)&in->rmon;
#ifdef __cplusplus
        static_assert(sizeof(out.rmon) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rmon = *tmp;
    }
    {
        const mesa_port_if_group_counters_t *tmp = (const mesa_port_if_group_counters_t *)&in->if_group;
#ifdef __cplusplus
        static_assert(sizeof(out.if_group) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->if_group = *tmp;
    }
    __RC(mesa_conv_vtss_port_ethernet_like_counters_t_to_mesa_port_ethernet_like_counters_t(&in->ethernet_like, &out->ethernet_like)); /* ag.rb:1455 */
#if defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
    {
        const mesa_port_bridge_counters_t *tmp = (const mesa_port_bridge_counters_t *)&in->bridge;
#ifdef __cplusplus
        static_assert(sizeof(out.bridge) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->bridge = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    {
        const mesa_port_dot3br_counters_t *tmp = (const mesa_port_dot3br_counters_t *)&in->dot3br;
#ifdef __cplusplus
        static_assert(sizeof(out.dot3br) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dot3br = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)

    return mesa_conv2_vtss_port_counters_t_to_mesa_port_counters_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_port_counters_t_to_vtss_port_counters_t(const mesa_port_counters_t *in, vtss_port_counters_t *out) /* ag.rb:1687 */
{
    // skipped: prio@mesa_port_counters_t
    // skipped: prop@vtss_port_counters_t
    // skipped: evc@vtss_port_counters_t
    {
        const vtss_port_rmon_counters_t *tmp = (const vtss_port_rmon_counters_t *)&in->rmon;
#ifdef __cplusplus
        static_assert(sizeof(out.rmon) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rmon = *tmp;
    }
    {
        const vtss_port_if_group_counters_t *tmp = (const vtss_port_if_group_counters_t *)&in->if_group;
#ifdef __cplusplus
        static_assert(sizeof(out.if_group) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->if_group = *tmp;
    }
    __RC(mesa_conv_mesa_port_ethernet_like_counters_t_to_vtss_port_ethernet_like_counters_t(&in->ethernet_like, &out->ethernet_like)); /* ag.rb:1455 */
#if defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
    {
        const vtss_port_bridge_counters_t *tmp = (const vtss_port_bridge_counters_t *)&in->bridge;
#ifdef __cplusplus
        static_assert(sizeof(out.bridge) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->bridge = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PORT_CNT_BRIDGE)
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    {
        const vtss_port_dot3br_counters_t *tmp = (const vtss_port_dot3br_counters_t *)&in->dot3br;
#ifdef __cplusplus
        static_assert(sizeof(out.dot3br) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dot3br = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)

    return mesa_conv2_mesa_port_counters_t_to_vtss_port_counters_t(in, out); /* ag.rb:1500 */
}

#if defined(VTSS_FEATURE_PORT_CONTROL)
#if defined(VTSS_FEATURE_PORT_IFH)
mesa_rc mesa_conv_vtss_port_ifh_t_to_mesa_port_ifh_t(const vtss_port_ifh_t *in, mesa_port_ifh_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
#if defined(VTSS_ARCH_SERVAL)
    out->ena_inj_header = in->ena_inj_header;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_JAGUAR_2)
    out->ena_inj_header = in->ena_inj_header;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_SERVAL)
    out->ena_xtr_header = in->ena_xtr_header;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_JAGUAR_2)
    out->ena_xtr_header = in->ena_xtr_header;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_JAGUAR_2)
    out->ena_ifh_header = in->ena_ifh_header;
#endif  // defined(VTSS_ARCH_JAGUAR_2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_port_ifh_t_to_vtss_port_ifh_t(const mesa_port_ifh_t *in, vtss_port_ifh_t *out) /* ag.rb:1687 */
{
#if defined(VTSS_ARCH_SERVAL)
    out->ena_inj_header = in->ena_inj_header;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_JAGUAR_2)
    out->ena_inj_header = in->ena_inj_header;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_SERVAL)
    out->ena_xtr_header = in->ena_xtr_header;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_JAGUAR_2)
    out->ena_xtr_header = in->ena_xtr_header;
#endif  // defined(VTSS_ARCH_JAGUAR_2)
#if defined(VTSS_ARCH_JAGUAR_2)
    out->ena_ifh_header = in->ena_ifh_header;
#endif  // defined(VTSS_ARCH_JAGUAR_2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_PORT_IFH)
#endif  // defined(VTSS_FEATURE_PORT_CONTROL)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_dscp_emode_t_to_mesa_dscp_emode_t(const vtss_dscp_emode_t *in, mesa_dscp_emode_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_DSCP_EMODE_DISABLE:
            *out = MESA_DSCP_EMODE_DISABLE;
            return VTSS_RC_OK;
        case VTSS_DSCP_EMODE_REMARK:
            *out = MESA_DSCP_EMODE_REMARK;
            return VTSS_RC_OK;
        case VTSS_DSCP_EMODE_REMAP:
            *out = MESA_DSCP_EMODE_REMAP;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        case VTSS_DSCP_EMODE_REMAP_DPA:
            *out = MESA_DSCP_EMODE_REMAP_DPA;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_dscp_emode_t_to_vtss_dscp_emode_t(const mesa_dscp_emode_t *in, vtss_dscp_emode_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_DSCP_EMODE_DISABLE:
            *out = VTSS_DSCP_EMODE_DISABLE;
            return VTSS_RC_OK;
        case MESA_DSCP_EMODE_REMARK:
            *out = VTSS_DSCP_EMODE_REMARK;
            return VTSS_RC_OK;
        case MESA_DSCP_EMODE_REMAP:
            *out = VTSS_DSCP_EMODE_REMAP;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        case MESA_DSCP_EMODE_REMAP_DPA:
            *out = VTSS_DSCP_EMODE_REMAP_DPA;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_tag_remark_mode_t_to_mesa_tag_remark_mode_t(const vtss_tag_remark_mode_t *in, mesa_tag_remark_mode_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_TAG_REMARK_MODE_CLASSIFIED:
            *out = MESA_TAG_REMARK_MODE_CLASSIFIED;
            return VTSS_RC_OK;
        case VTSS_TAG_REMARK_MODE_DEFAULT:
            *out = MESA_TAG_REMARK_MODE_DEFAULT;
            return VTSS_RC_OK;
        case VTSS_TAG_REMARK_MODE_MAPPED:
            *out = MESA_TAG_REMARK_MODE_MAPPED;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_tag_remark_mode_t_to_vtss_tag_remark_mode_t(const mesa_tag_remark_mode_t *in, vtss_tag_remark_mode_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_TAG_REMARK_MODE_CLASSIFIED:
            *out = VTSS_TAG_REMARK_MODE_CLASSIFIED;
            return VTSS_RC_OK;
        case MESA_TAG_REMARK_MODE_DEFAULT:
            *out = VTSS_TAG_REMARK_MODE_DEFAULT;
            return VTSS_RC_OK;
        case MESA_TAG_REMARK_MODE_MAPPED:
            *out = VTSS_TAG_REMARK_MODE_MAPPED;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_shaper_t_to_mesa_shaper_t(const vtss_shaper_t *in, mesa_shaper_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->level = in->level;
    out->rate = in->rate;
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
    out->ebs = in->ebs;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
    out->eir = in->eir;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT)
    {
        const mesa_shaper_mode_t *tmp = (const mesa_shaper_mode_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT)
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)
    out->credit_enable = in->credit_enable;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_shaper_t_to_vtss_shaper_t(const mesa_shaper_t *in, vtss_shaper_t *out) /* ag.rb:1687 */
{
    out->level = in->level;
    out->rate = in->rate;
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
    out->ebs = in->ebs;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
    out->eir = in->eir;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT)
    {
        const vtss_shaper_mode_t *tmp = (const vtss_shaper_mode_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT)
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)
    out->credit_enable = in->credit_enable;
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_qos_port_conf_t_to_mesa_qos_port_conf_t(const vtss_qos_port_conf_t *in, mesa_qos_port_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: policer_port@vtss_qos_port_conf_t
    // skipped: policer_ext_port@vtss_qos_port_conf_t
    // skipped: policer_queue@vtss_qos_port_conf_t
    // skipped: shaper_port@vtss_qos_port_conf_t
    // skipped: shaper_queue@vtss_qos_port_conf_t
    // skipped: excess_enable@vtss_qos_port_conf_t
    // skipped: cut_through_enable@vtss_qos_port_conf_t
    // skipped: usr_prio@vtss_qos_port_conf_t
    // skipped: default_dei@vtss_qos_port_conf_t
    // skipped: tag_class_enable@vtss_qos_port_conf_t
    // skipped: qos_class_map@vtss_qos_port_conf_t
    // skipped: dp_level_map@vtss_qos_port_conf_t
    // skipped: dscp_class_enable@vtss_qos_port_conf_t
    // skipped: dscp_mode@vtss_qos_port_conf_t
    // skipped: dscp_emode@vtss_qos_port_conf_t
    // skipped: dscp_translate@vtss_qos_port_conf_t
    // skipped: tag_remark_mode@vtss_qos_port_conf_t
    // skipped: tag_default_pcp@vtss_qos_port_conf_t
    // skipped: tag_default_dei@vtss_qos_port_conf_t
    // skipped: tag_pcp_map@vtss_qos_port_conf_t
    // skipped: tag_dei_map@vtss_qos_port_conf_t
    // skipped: queue_pct@vtss_qos_port_conf_t
    // skipped: shaper@mesa_qos_port_conf_t
    // skipped: tag@mesa_qos_port_conf_t
    // skipped: dscp@mesa_qos_port_conf_t
    // skipped: queue@mesa_qos_port_conf_t
    out->default_prio = in->default_prio;
    out->default_dpl = in->default_dpl;
    out->dwrr_enable = in->dwrr_enable;
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
    out->dwrr_cnt = in->dwrr_cnt;
#endif  // defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
#if defined(VTSS_FEATURE_QCL_DMAC_DIP)
    out->dmac_dip = in->dmac_dip;
#endif  // defined(VTSS_FEATURE_QCL_DMAC_DIP)
#if defined(VTSS_FEATURE_QCL_KEY_TYPE)
    {
        const mesa_vcap_key_type_t *tmp = (const mesa_vcap_key_type_t *)&in->key_type;
#ifdef __cplusplus
        static_assert(sizeof(out.key_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->key_type = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_TYPE)
#if defined(VTSS_FEATURE_QOS_WRED_V3)
    out->wred_group = in->wred_group;
#endif  // defined(VTSS_FEATURE_QOS_WRED_V3)
#if (defined VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
    out->cosid = in->cosid;
#endif  // (defined VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
#if (defined VTSS_FEATURE_QOS_INGRESS_MAP)
    out->ingress_map = in->ingress_map;
#endif  // (defined VTSS_FEATURE_QOS_INGRESS_MAP)
#if (defined VTSS_FEATURE_QOS_EGRESS_MAP)
    out->egress_map = in->egress_map;
#endif  // (defined VTSS_FEATURE_QOS_EGRESS_MAP)

    return mesa_conv2_vtss_qos_port_conf_t_to_mesa_qos_port_conf_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_qos_port_conf_t_to_vtss_qos_port_conf_t(const mesa_qos_port_conf_t *in, vtss_qos_port_conf_t *out) /* ag.rb:1687 */
{
    // skipped: shaper@mesa_qos_port_conf_t
    // skipped: tag@mesa_qos_port_conf_t
    // skipped: dscp@mesa_qos_port_conf_t
    // skipped: queue@mesa_qos_port_conf_t
    // skipped: policer_port@vtss_qos_port_conf_t
    // skipped: policer_ext_port@vtss_qos_port_conf_t
    // skipped: policer_queue@vtss_qos_port_conf_t
    // skipped: shaper_port@vtss_qos_port_conf_t
    // skipped: shaper_queue@vtss_qos_port_conf_t
    // skipped: excess_enable@vtss_qos_port_conf_t
    // skipped: cut_through_enable@vtss_qos_port_conf_t
    // skipped: usr_prio@vtss_qos_port_conf_t
    // skipped: default_dei@vtss_qos_port_conf_t
    // skipped: tag_class_enable@vtss_qos_port_conf_t
    // skipped: qos_class_map@vtss_qos_port_conf_t
    // skipped: dp_level_map@vtss_qos_port_conf_t
    // skipped: dscp_class_enable@vtss_qos_port_conf_t
    // skipped: dscp_mode@vtss_qos_port_conf_t
    // skipped: dscp_emode@vtss_qos_port_conf_t
    // skipped: dscp_translate@vtss_qos_port_conf_t
    // skipped: tag_remark_mode@vtss_qos_port_conf_t
    // skipped: tag_default_pcp@vtss_qos_port_conf_t
    // skipped: tag_default_dei@vtss_qos_port_conf_t
    // skipped: tag_pcp_map@vtss_qos_port_conf_t
    // skipped: tag_dei_map@vtss_qos_port_conf_t
    // skipped: queue_pct@vtss_qos_port_conf_t
    out->default_prio = in->default_prio;
    out->default_dpl = in->default_dpl;
    out->dwrr_enable = in->dwrr_enable;
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
    out->dwrr_cnt = in->dwrr_cnt;
#endif  // defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
#if defined(VTSS_FEATURE_QCL_DMAC_DIP)
    out->dmac_dip = in->dmac_dip;
#endif  // defined(VTSS_FEATURE_QCL_DMAC_DIP)
#if defined(VTSS_FEATURE_QCL_KEY_TYPE)
    {
        const vtss_vcap_key_type_t *tmp = (const vtss_vcap_key_type_t *)&in->key_type;
#ifdef __cplusplus
        static_assert(sizeof(out.key_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->key_type = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_TYPE)
#if defined(VTSS_FEATURE_QOS_WRED_V3)
    out->wred_group = in->wred_group;
#endif  // defined(VTSS_FEATURE_QOS_WRED_V3)
#if (defined VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
    out->cosid = in->cosid;
#endif  // (defined VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
#if (defined VTSS_FEATURE_QOS_INGRESS_MAP)
    out->ingress_map = in->ingress_map;
#endif  // (defined VTSS_FEATURE_QOS_INGRESS_MAP)
#if (defined VTSS_FEATURE_QOS_EGRESS_MAP)
    out->egress_map = in->egress_map;
#endif  // (defined VTSS_FEATURE_QOS_EGRESS_MAP)

    return mesa_conv2_mesa_qos_port_conf_t_to_vtss_qos_port_conf_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_qce_mac_t_to_mesa_qce_mac_t(const vtss_qce_mac_t *in, mesa_qce_mac_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_vcap_bit_t *tmp = (const mesa_vcap_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const mesa_vcap_bit_t *tmp = (const mesa_vcap_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_DMAC)
    {
        const mesa_vcap_u48_t *tmp = (const mesa_vcap_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_DMAC)
    {
        const mesa_vcap_u48_t *tmp = (const mesa_vcap_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_qce_mac_t_to_vtss_qce_mac_t(const mesa_qce_mac_t *in, vtss_qce_mac_t *out) /* ag.rb:1687 */
{
    {
        const vtss_vcap_bit_t *tmp = (const vtss_vcap_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const vtss_vcap_bit_t *tmp = (const vtss_vcap_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_DMAC)
    {
        const vtss_vcap_u48_t *tmp = (const vtss_vcap_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_DMAC)
    {
        const vtss_vcap_u48_t *tmp = (const vtss_vcap_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_qce_frame_ipv4_t_to_mesa_qce_frame_ipv4_t(const vtss_qce_frame_ipv4_t *in, mesa_qce_frame_ipv4_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_vcap_bit_t *tmp = (const mesa_vcap_bit_t *)&in->fragment;
#ifdef __cplusplus
        static_assert(sizeof(out.fragment) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->fragment = *tmp;
    }
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const mesa_vcap_u8_t *tmp = (const mesa_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const mesa_vcap_ip_t *tmp = (const mesa_vcap_ip_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const mesa_vcap_ip_t *tmp = (const mesa_vcap_ip_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_qce_frame_ipv4_t_to_vtss_qce_frame_ipv4_t(const mesa_qce_frame_ipv4_t *in, vtss_qce_frame_ipv4_t *out) /* ag.rb:1687 */
{
    {
        const vtss_vcap_bit_t *tmp = (const vtss_vcap_bit_t *)&in->fragment;
#ifdef __cplusplus
        static_assert(sizeof(out.fragment) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->fragment = *tmp;
    }
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const vtss_vcap_u8_t *tmp = (const vtss_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const vtss_vcap_ip_t *tmp = (const vtss_vcap_ip_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const vtss_vcap_ip_t *tmp = (const vtss_vcap_ip_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_qce_frame_ipv6_t_to_mesa_qce_frame_ipv6_t(const vtss_qce_frame_ipv6_t *in, mesa_qce_frame_ipv6_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const mesa_vcap_u8_t *tmp = (const mesa_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const mesa_vcap_u128_t *tmp = (const mesa_vcap_u128_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const mesa_vcap_u128_t *tmp = (const mesa_vcap_u128_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const mesa_vcap_vr_t *tmp = (const mesa_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_qce_frame_ipv6_t_to_vtss_qce_frame_ipv6_t(const mesa_qce_frame_ipv6_t *in, vtss_qce_frame_ipv6_t *out) /* ag.rb:1687 */
{
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dscp;
#ifdef __cplusplus
        static_assert(sizeof(out.dscp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dscp = *tmp;
    }
    {
        const vtss_vcap_u8_t *tmp = (const vtss_vcap_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const vtss_vcap_u128_t *tmp = (const vtss_vcap_u128_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const vtss_vcap_u128_t *tmp = (const vtss_vcap_u128_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_DIP)
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const vtss_vcap_vr_t *tmp = (const vtss_vcap_vr_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_qce_key_t_to_mesa_qce_key_t(const vtss_qce_key_t *in, mesa_qce_key_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_qce_mac_t_to_mesa_qce_mac_t(&in->mac, &out->mac)); /* ag.rb:1455 */
    {
        const mesa_qce_tag_t *tmp = (const mesa_qce_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const mesa_qce_tag_t *tmp = (const mesa_qce_tag_t *)&in->inner_tag;
#ifdef __cplusplus
        static_assert(sizeof(out.inner_tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->inner_tag = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const mesa_qce_type_t *tmp = (const mesa_qce_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }

    return mesa_conv2_vtss_qce_key_t_to_mesa_qce_key_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_qce_key_t_to_vtss_qce_key_t(const mesa_qce_key_t *in, vtss_qce_key_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_qce_mac_t_to_vtss_qce_mac_t(&in->mac, &out->mac)); /* ag.rb:1455 */
    {
        const vtss_qce_tag_t *tmp = (const vtss_qce_tag_t *)&in->tag;
#ifdef __cplusplus
        static_assert(sizeof(out.tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tag = *tmp;
    }
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const vtss_qce_tag_t *tmp = (const vtss_qce_tag_t *)&in->inner_tag;
#ifdef __cplusplus
        static_assert(sizeof(out.inner_tag) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->inner_tag = *tmp;
    }
#endif  // defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    {
        const vtss_qce_type_t *tmp = (const vtss_qce_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }

    return mesa_conv2_mesa_qce_key_t_to_vtss_qce_key_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_qce_action_t_to_mesa_qce_action_t(const vtss_qce_action_t *in, mesa_qce_action_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->prio_enable = in->prio_enable;
    out->prio = in->prio;
    out->dp_enable = in->dp_enable;
    out->dp = in->dp;
    out->dscp_enable = in->dscp_enable;
    out->dscp = in->dscp;
    out->pcp_dei_enable = in->pcp_dei_enable;
    out->pcp = in->pcp;
    out->dei = in->dei;
    out->policy_no_enable = in->policy_no_enable;
    out->policy_no = in->policy_no;
#if (defined VTSS_FEATURE_QCL_MAP_ACTION)
    out->map_id_enable = in->map_id_enable;
#endif  // (defined VTSS_FEATURE_QCL_MAP_ACTION)
#if (defined VTSS_FEATURE_QCL_MAP_ACTION)
    out->map_id = in->map_id;
#endif  // (defined VTSS_FEATURE_QCL_MAP_ACTION)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_qce_action_t_to_vtss_qce_action_t(const mesa_qce_action_t *in, vtss_qce_action_t *out) /* ag.rb:1687 */
{
    out->prio_enable = in->prio_enable;
    out->prio = in->prio;
    out->dp_enable = in->dp_enable;
    out->dp = in->dp;
    out->dscp_enable = in->dscp_enable;
    out->dscp = in->dscp;
    out->pcp_dei_enable = in->pcp_dei_enable;
    out->pcp = in->pcp;
    out->dei = in->dei;
    out->policy_no_enable = in->policy_no_enable;
    out->policy_no = in->policy_no;
#if (defined VTSS_FEATURE_QCL_MAP_ACTION)
    out->map_id_enable = in->map_id_enable;
#endif  // (defined VTSS_FEATURE_QCL_MAP_ACTION)
#if (defined VTSS_FEATURE_QCL_MAP_ACTION)
    out->map_id = in->map_id;
#endif  // (defined VTSS_FEATURE_QCL_MAP_ACTION)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_conv_vtss_qce_t_to_mesa_qce_t(const vtss_qce_t *in, mesa_qce_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->id = in->id;
    __RC(mesa_conv_vtss_qce_key_t_to_mesa_qce_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_qce_action_t_to_mesa_qce_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_qce_t_to_vtss_qce_t(const mesa_qce_t *in, vtss_qce_t *out) /* ag.rb:1687 */
{
    out->id = in->id;
    __RC(mesa_conv_mesa_qce_key_t_to_vtss_qce_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_qce_action_t_to_vtss_qce_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
mesa_rc mesa_conv_vtss_dlb_policer_conf_t_to_mesa_dlb_policer_conf_t(const vtss_dlb_policer_conf_t *in, mesa_dlb_policer_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_policer_type_t *tmp = (const mesa_policer_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }
    out->enable = in->enable;
#if defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
    out->cm = in->cm;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
    out->cf = in->cf;
    out->line_rate = in->line_rate;
    out->cir = in->cir;
    out->cbs = in->cbs;
    out->eir = in->eir;
    out->ebs = in->ebs;
#if defined(VTSS_FEATURE_PSFP)
    out->drop_yellow = in->drop_yellow;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    {
        const mesa_opt_bool_t *tmp = (const mesa_opt_bool_t *)&in->mark_all_red;
#ifdef __cplusplus
        static_assert(sizeof(out.mark_all_red) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mark_all_red = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PSFP)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_dlb_policer_conf_t_to_vtss_dlb_policer_conf_t(const mesa_dlb_policer_conf_t *in, vtss_dlb_policer_conf_t *out) /* ag.rb:1687 */
{
    {
        const vtss_policer_type_t *tmp = (const vtss_policer_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }
    out->enable = in->enable;
#if defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
    out->cm = in->cm;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
    out->cf = in->cf;
    out->line_rate = in->line_rate;
    out->cir = in->cir;
    out->cbs = in->cbs;
    out->eir = in->eir;
    out->ebs = in->ebs;
#if defined(VTSS_FEATURE_PSFP)
    out->drop_yellow = in->drop_yellow;
#endif  // defined(VTSS_FEATURE_PSFP)
#if defined(VTSS_FEATURE_PSFP)
    {
        const vtss_opt_bool_t *tmp = (const vtss_opt_bool_t *)&in->mark_all_red;
#ifdef __cplusplus
        static_assert(sizeof(out.mark_all_red) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mark_all_red = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PSFP)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS_POLICER_DLB)
#endif  // defined(VTSS_FEATURE_QOS)

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_conv_vtss_acl_ptp_action_t_to_mesa_acl_ptp_action_t(const vtss_acl_ptp_action_t *in, mesa_acl_ptp_action_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_ACL_PTP_ACTION_NONE:
            *out = MESA_ACL_PTP_ACTION_NONE;
            return VTSS_RC_OK;
        case VTSS_ACL_PTP_ACTION_ONE_STEP:
            *out = MESA_ACL_PTP_ACTION_ONE_STEP;
            return VTSS_RC_OK;
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case VTSS_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY:
            *out = MESA_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1:
            *out = MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2:
            *out = MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_LUTON26)
        case VTSS_ACL_PTP_ACTION_ONE_AND_TWO_STEP:
            *out = MESA_ACL_PTP_ACTION_ONE_AND_TWO_STEP;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
        case VTSS_ACL_PTP_ACTION_TWO_STEP:
            *out = MESA_ACL_PTP_ACTION_TWO_STEP;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_acl_ptp_action_t_to_vtss_acl_ptp_action_t(const mesa_acl_ptp_action_t *in, vtss_acl_ptp_action_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_ACL_PTP_ACTION_NONE:
            *out = VTSS_ACL_PTP_ACTION_NONE;
            return VTSS_RC_OK;
        case MESA_ACL_PTP_ACTION_ONE_STEP:
            *out = VTSS_ACL_PTP_ACTION_ONE_STEP;
            return VTSS_RC_OK;
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case MESA_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY:
            *out = VTSS_ACL_PTP_ACTION_ONE_STEP_ADD_DELAY;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1:
            *out = VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_1;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        case MESA_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2:
            *out = VTSS_ACL_PTP_ACTION_ONE_STEP_SUB_DELAY_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_LUTON26)
        case MESA_ACL_PTP_ACTION_ONE_AND_TWO_STEP:
            *out = VTSS_ACL_PTP_ACTION_ONE_AND_TWO_STEP;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_LUTON26)
        case MESA_ACL_PTP_ACTION_TWO_STEP:
            *out = VTSS_ACL_PTP_ACTION_TWO_STEP;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_ACL)

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_conv_vtss_acl_action_t_to_mesa_acl_action_t(const vtss_acl_action_t *in, mesa_acl_action_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->cpu = in->cpu;
    out->cpu_once = in->cpu_once;
    out->cpu_disable = in->cpu_disable;
    out->cpu_queue = in->cpu_queue;
    out->police = in->police;
    out->policer_no = in->policer_no;
#if defined(VTSS_FEATURE_EVC_POLICERS)
    out->evc_police = in->evc_police;
#endif  // defined(VTSS_FEATURE_EVC_POLICERS)
#if defined(VTSS_FEATURE_EVC_POLICERS)
    out->evc_policer_id = in->evc_policer_id;
#endif  // defined(VTSS_FEATURE_EVC_POLICERS)
    out->learn = in->learn;
    {
        const mesa_acl_port_action_t *tmp = (const mesa_acl_port_action_t *)&in->port_action;
#ifdef __cplusplus
        static_assert(sizeof(out.port_action) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->port_action = *tmp;
    }
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    out->mirror = in->mirror;
    __RC(mesa_conv_vtss_acl_ptp_action_t_to_mesa_acl_ptp_action_t(&in->ptp_action, &out->ptp_action)); /* ag.rb:1455 */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const mesa_acl_ptp_action_conf_t *tmp = (const mesa_acl_ptp_action_conf_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const mesa_acl_addr_action_t *tmp = (const mesa_acl_addr_action_t *)&in->addr;
#ifdef __cplusplus
        static_assert(sizeof(out.addr) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->addr = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL)
    out->lm_cnt_disable = in->lm_cnt_disable;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->mac_swap = in->mac_swap;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->ifh_flag = in->ifh_flag;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_acl_action_t_to_vtss_acl_action_t(const mesa_acl_action_t *in, vtss_acl_action_t *out) /* ag.rb:1687 */
{
    out->cpu = in->cpu;
    out->cpu_once = in->cpu_once;
    out->cpu_disable = in->cpu_disable;
    out->cpu_queue = in->cpu_queue;
    out->police = in->police;
    out->policer_no = in->policer_no;
#if defined(VTSS_FEATURE_EVC_POLICERS)
    out->evc_police = in->evc_police;
#endif  // defined(VTSS_FEATURE_EVC_POLICERS)
#if defined(VTSS_FEATURE_EVC_POLICERS)
    out->evc_policer_id = in->evc_policer_id;
#endif  // defined(VTSS_FEATURE_EVC_POLICERS)
    out->learn = in->learn;
    {
        const vtss_acl_port_action_t *tmp = (const vtss_acl_port_action_t *)&in->port_action;
#ifdef __cplusplus
        static_assert(sizeof(out.port_action) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->port_action = *tmp;
    }
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    out->mirror = in->mirror;
    __RC(mesa_conv_mesa_acl_ptp_action_t_to_vtss_acl_ptp_action_t(&in->ptp_action, &out->ptp_action)); /* ag.rb:1455 */
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const vtss_acl_ptp_action_conf_t *tmp = (const vtss_acl_ptp_action_conf_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    {
        const vtss_acl_addr_action_t *tmp = (const vtss_acl_addr_action_t *)&in->addr;
#ifdef __cplusplus
        static_assert(sizeof(out.addr) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->addr = *tmp;
    }
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL)
    out->lm_cnt_disable = in->lm_cnt_disable;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->mac_swap = in->mac_swap;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->ifh_flag = in->ifh_flag;
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_ACL)

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_conv_vtss_acl_port_conf_t_to_mesa_acl_port_conf_t(const vtss_acl_port_conf_t *in, mesa_acl_port_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->policy_no = in->policy_no;
    __RC(mesa_conv_vtss_acl_action_t_to_mesa_acl_action_t(&in->action, &out->action)); /* ag.rb:1455 */
    {
        const mesa_acl_frame_key_t *tmp = (const mesa_acl_frame_key_t *)&in->key;
#ifdef __cplusplus
        static_assert(sizeof(out.key) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->key = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_acl_port_conf_t_to_vtss_acl_port_conf_t(const mesa_acl_port_conf_t *in, vtss_acl_port_conf_t *out) /* ag.rb:1687 */
{
    out->policy_no = in->policy_no;
    __RC(mesa_conv_mesa_acl_action_t_to_vtss_acl_action_t(&in->action, &out->action)); /* ag.rb:1455 */
    {
        const vtss_acl_frame_key_t *tmp = (const vtss_acl_frame_key_t *)&in->key;
#ifdef __cplusplus
        static_assert(sizeof(out.key) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->key = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_ACL)

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_conv_vtss_ace_frame_ipv4_t_to_mesa_ace_frame_ipv4_t(const vtss_ace_frame_ipv4_t *in, mesa_ace_frame_ipv4_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->ttl;
#ifdef __cplusplus
        static_assert(sizeof(out.ttl) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ttl = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->fragment;
#ifdef __cplusplus
        static_assert(sizeof(out.fragment) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->fragment = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->options;
#ifdef __cplusplus
        static_assert(sizeof(out.options) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->options = *tmp;
    }
    {
        const mesa_ace_u8_t *tmp = (const mesa_ace_u8_t *)&in->ds;
#ifdef __cplusplus
        static_assert(sizeof(out.ds) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ds = *tmp;
    }
    {
        const mesa_ace_u8_t *tmp = (const mesa_ace_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const mesa_ace_ip_t *tmp = (const mesa_ace_ip_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
    {
        const mesa_ace_ip_t *tmp = (const mesa_ace_ip_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->data;
#ifdef __cplusplus
        static_assert(sizeof(out.data) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->data = *tmp;
    }
    {
        const mesa_ace_udp_tcp_t *tmp = (const mesa_ace_udp_tcp_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const mesa_ace_udp_tcp_t *tmp = (const mesa_ace_udp_tcp_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_fin;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_fin) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_fin = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_syn;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_syn) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_syn = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_rst;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_rst) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_rst = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_psh;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_psh) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_psh = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_ack;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_ack) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_ack = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_urg;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_urg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_urg = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->sip_eq_dip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip_eq_dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip_eq_dip = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->sport_eq_dport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport_eq_dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport_eq_dport = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->seq_zero;
#ifdef __cplusplus
        static_assert(sizeof(out.seq_zero) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->seq_zero = *tmp;
    }
    {
        const mesa_ace_ptp_t *tmp = (const mesa_ace_ptp_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
    {
        const mesa_ace_sip_smac_t *tmp = (const mesa_ace_sip_smac_t *)&in->sip_smac;
#ifdef __cplusplus
        static_assert(sizeof(out.sip_smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip_smac = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_ace_frame_ipv4_t_to_vtss_ace_frame_ipv4_t(const mesa_ace_frame_ipv4_t *in, vtss_ace_frame_ipv4_t *out) /* ag.rb:1687 */
{
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->ttl;
#ifdef __cplusplus
        static_assert(sizeof(out.ttl) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ttl = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->fragment;
#ifdef __cplusplus
        static_assert(sizeof(out.fragment) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->fragment = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->options;
#ifdef __cplusplus
        static_assert(sizeof(out.options) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->options = *tmp;
    }
    {
        const vtss_ace_u8_t *tmp = (const vtss_ace_u8_t *)&in->ds;
#ifdef __cplusplus
        static_assert(sizeof(out.ds) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ds = *tmp;
    }
    {
        const vtss_ace_u8_t *tmp = (const vtss_ace_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const vtss_ace_ip_t *tmp = (const vtss_ace_ip_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
    {
        const vtss_ace_ip_t *tmp = (const vtss_ace_ip_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->data;
#ifdef __cplusplus
        static_assert(sizeof(out.data) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->data = *tmp;
    }
    {
        const vtss_ace_udp_tcp_t *tmp = (const vtss_ace_udp_tcp_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const vtss_ace_udp_tcp_t *tmp = (const vtss_ace_udp_tcp_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_fin;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_fin) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_fin = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_syn;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_syn) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_syn = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_rst;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_rst) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_rst = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_psh;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_psh) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_psh = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_ack;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_ack) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_ack = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_urg;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_urg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_urg = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->sip_eq_dip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip_eq_dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip_eq_dip = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->sport_eq_dport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport_eq_dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport_eq_dport = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->seq_zero;
#ifdef __cplusplus
        static_assert(sizeof(out.seq_zero) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->seq_zero = *tmp;
    }
    {
        const vtss_ace_ptp_t *tmp = (const vtss_ace_ptp_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
    {
        const vtss_ace_sip_smac_t *tmp = (const vtss_ace_sip_smac_t *)&in->sip_smac;
#ifdef __cplusplus
        static_assert(sizeof(out.sip_smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip_smac = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_ACL)

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_conv_vtss_ace_frame_ipv6_t_to_mesa_ace_frame_ipv6_t(const vtss_ace_frame_ipv6_t *in, mesa_ace_frame_ipv6_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const mesa_ace_u8_t *tmp = (const mesa_ace_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const mesa_ace_u128_t *tmp = (const mesa_ace_u128_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_ACL_EXT_DIP)
    {
        const mesa_ace_u128_t *tmp = (const mesa_ace_u128_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_DIP)
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->ttl;
#ifdef __cplusplus
        static_assert(sizeof(out.ttl) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ttl = *tmp;
    }
    {
        const mesa_ace_u8_t *tmp = (const mesa_ace_u8_t *)&in->ds;
#ifdef __cplusplus
        static_assert(sizeof(out.ds) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ds = *tmp;
    }
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->data;
#ifdef __cplusplus
        static_assert(sizeof(out.data) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->data = *tmp;
    }
    {
        const mesa_ace_udp_tcp_t *tmp = (const mesa_ace_udp_tcp_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const mesa_ace_udp_tcp_t *tmp = (const mesa_ace_udp_tcp_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_fin;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_fin) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_fin = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_syn;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_syn) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_syn = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_rst;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_rst) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_rst = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_psh;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_psh) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_psh = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_ack;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_ack) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_ack = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->tcp_urg;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_urg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_urg = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->sip_eq_dip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip_eq_dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip_eq_dip = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->sport_eq_dport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport_eq_dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport_eq_dport = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->seq_zero;
#ifdef __cplusplus
        static_assert(sizeof(out.seq_zero) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->seq_zero = *tmp;
    }
    {
        const mesa_ace_ptp_t *tmp = (const mesa_ace_ptp_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_ace_frame_ipv6_t_to_vtss_ace_frame_ipv6_t(const mesa_ace_frame_ipv6_t *in, vtss_ace_frame_ipv6_t *out) /* ag.rb:1687 */
{
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_MAC)
    {
        const vtss_ace_u8_t *tmp = (const vtss_ace_u8_t *)&in->proto;
#ifdef __cplusplus
        static_assert(sizeof(out.proto) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->proto = *tmp;
    }
    {
        const vtss_ace_u128_t *tmp = (const vtss_ace_u128_t *)&in->sip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip = *tmp;
    }
#if defined(VTSS_FEATURE_ACL_EXT_DIP)
    {
        const vtss_ace_u128_t *tmp = (const vtss_ace_u128_t *)&in->dip;
#ifdef __cplusplus
        static_assert(sizeof(out.dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dip = *tmp;
    }
#endif  // defined(VTSS_FEATURE_ACL_EXT_DIP)
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->ttl;
#ifdef __cplusplus
        static_assert(sizeof(out.ttl) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ttl = *tmp;
    }
    {
        const vtss_ace_u8_t *tmp = (const vtss_ace_u8_t *)&in->ds;
#ifdef __cplusplus
        static_assert(sizeof(out.ds) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ds = *tmp;
    }
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->data;
#ifdef __cplusplus
        static_assert(sizeof(out.data) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->data = *tmp;
    }
    {
        const vtss_ace_udp_tcp_t *tmp = (const vtss_ace_udp_tcp_t *)&in->sport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport = *tmp;
    }
    {
        const vtss_ace_udp_tcp_t *tmp = (const vtss_ace_udp_tcp_t *)&in->dport;
#ifdef __cplusplus
        static_assert(sizeof(out.dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dport = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_fin;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_fin) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_fin = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_syn;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_syn) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_syn = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_rst;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_rst) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_rst = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_psh;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_psh) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_psh = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_ack;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_ack) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_ack = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->tcp_urg;
#ifdef __cplusplus
        static_assert(sizeof(out.tcp_urg) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->tcp_urg = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->sip_eq_dip;
#ifdef __cplusplus
        static_assert(sizeof(out.sip_eq_dip) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sip_eq_dip = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->sport_eq_dport;
#ifdef __cplusplus
        static_assert(sizeof(out.sport_eq_dport) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->sport_eq_dport = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->seq_zero;
#ifdef __cplusplus
        static_assert(sizeof(out.seq_zero) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->seq_zero = *tmp;
    }
    {
        const vtss_ace_ptp_t *tmp = (const vtss_ace_ptp_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_ACL)

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_conv_vtss_ace_t_to_mesa_ace_t(const vtss_ace_t *in, mesa_ace_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->id = in->id;
#if defined(VTSS_ARCH_SERVAL)
    out->lookup = in->lookup;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    out->isdx_enable = in->isdx_enable;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    out->isdx_disable = in->isdx_disable;
#endif  // defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    {
        const mesa_ace_u8_t *tmp = (const mesa_ace_u8_t *)&in->policy;
#ifdef __cplusplus
        static_assert(sizeof(out.policy) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->policy = *tmp;
    }
    {
        const mesa_ace_type_t *tmp = (const mesa_ace_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }
    out->type_ext = in->type_ext;
    __RC(mesa_conv_vtss_acl_action_t_to_mesa_acl_action_t(&in->action, &out->action)); /* ag.rb:1455 */
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
    {
        const mesa_ace_vlan_t *tmp = (const mesa_ace_vlan_t *)&in->vlan;
#ifdef __cplusplus
        static_assert(sizeof(out.vlan) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->vlan = *tmp;
    }

    return mesa_conv2_vtss_ace_t_to_mesa_ace_t(in, out); /* ag.rb:1500 */
}

mesa_rc mesa_conv_mesa_ace_t_to_vtss_ace_t(const mesa_ace_t *in, vtss_ace_t *out) /* ag.rb:1687 */
{
    out->id = in->id;
#if defined(VTSS_ARCH_SERVAL)
    out->lookup = in->lookup;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    out->isdx_enable = in->isdx_enable;
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    out->isdx_disable = in->isdx_disable;
#endif  // defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    {
        const vtss_ace_u8_t *tmp = (const vtss_ace_u8_t *)&in->policy;
#ifdef __cplusplus
        static_assert(sizeof(out.policy) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->policy = *tmp;
    }
    {
        const vtss_ace_type_t *tmp = (const vtss_ace_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }
    out->type_ext = in->type_ext;
    __RC(mesa_conv_mesa_acl_action_t_to_vtss_acl_action_t(&in->action, &out->action)); /* ag.rb:1455 */
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
    {
        const vtss_ace_vlan_t *tmp = (const vtss_ace_vlan_t *)&in->vlan;
#ifdef __cplusplus
        static_assert(sizeof(out.vlan) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->vlan = *tmp;
    }

    return mesa_conv2_mesa_ace_t_to_vtss_ace_t(in, out); /* ag.rb:1500 */
}
#endif  // defined(VTSS_FEATURE_ACL)

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_conv_vtss_hace_key_t_to_mesa_hace_key_t(const vtss_hace_key_t *in, mesa_hace_key_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    {
        const mesa_rleg_list_t *tmp = (const mesa_rleg_list_t *)&in->rleg_list;
#ifdef __cplusplus
        static_assert(sizeof(out.rleg_list) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rleg_list = *tmp;
    }
    {
        const mesa_ace_u8_t *tmp = (const mesa_ace_u8_t *)&in->policy;
#ifdef __cplusplus
        static_assert(sizeof(out.policy) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->policy = *tmp;
    }
    out->type_ext = in->type_ext;
    {
        const mesa_ace_type_t *tmp = (const mesa_ace_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }
    {
        const mesa_ace_vlan_t *tmp = (const mesa_ace_vlan_t *)&in->vlan;
#ifdef __cplusplus
        static_assert(sizeof(out.vlan) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->vlan = *tmp;
    }
    {
        const mesa_ace_ptp_t *tmp = (const mesa_ace_ptp_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const mesa_ace_bit_t *tmp = (const mesa_ace_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
    {
        const mesa_ace_u48_t *tmp = (const mesa_ace_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
    {
        const mesa_hace_frame_etype_t *tmp = (const mesa_hace_frame_etype_t *)&in->etype;
#ifdef __cplusplus
        static_assert(sizeof(out.etype) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->etype = *tmp;
    }
    {
        const mesa_hace_frame_llc_t *tmp = (const mesa_hace_frame_llc_t *)&in->llc;
#ifdef __cplusplus
        static_assert(sizeof(out.llc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->llc = *tmp;
    }
    {
        const mesa_hace_frame_snap_t *tmp = (const mesa_hace_frame_snap_t *)&in->snap;
#ifdef __cplusplus
        static_assert(sizeof(out.snap) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->snap = *tmp;
    }
    {
        const mesa_hace_frame_arp_t *tmp = (const mesa_hace_frame_arp_t *)&in->arp;
#ifdef __cplusplus
        static_assert(sizeof(out.arp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->arp = *tmp;
    }
    {
        const mesa_hace_frame_ipv4_t *tmp = (const mesa_hace_frame_ipv4_t *)&in->ipv4;
#ifdef __cplusplus
        static_assert(sizeof(out.ipv4) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ipv4 = *tmp;
    }
    {
        const mesa_hace_frame_ipv6_t *tmp = (const mesa_hace_frame_ipv6_t *)&in->ipv6;
#ifdef __cplusplus
        static_assert(sizeof(out.ipv6) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ipv6 = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_hace_key_t_to_vtss_hace_key_t(const mesa_hace_key_t *in, vtss_hace_key_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    {
        const vtss_rleg_list_t *tmp = (const vtss_rleg_list_t *)&in->rleg_list;
#ifdef __cplusplus
        static_assert(sizeof(out.rleg_list) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->rleg_list = *tmp;
    }
    {
        const vtss_ace_u8_t *tmp = (const vtss_ace_u8_t *)&in->policy;
#ifdef __cplusplus
        static_assert(sizeof(out.policy) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->policy = *tmp;
    }
    {
        const vtss_ace_type_t *tmp = (const vtss_ace_type_t *)&in->type;
#ifdef __cplusplus
        static_assert(sizeof(out.type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->type = *tmp;
    }
    out->type_ext = in->type_ext;
    {
        const vtss_ace_vlan_t *tmp = (const vtss_ace_vlan_t *)&in->vlan;
#ifdef __cplusplus
        static_assert(sizeof(out.vlan) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->vlan = *tmp;
    }
    {
        const vtss_ace_ptp_t *tmp = (const vtss_ace_ptp_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->dmac_mc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_mc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_mc = *tmp;
    }
    {
        const vtss_ace_bit_t *tmp = (const vtss_ace_bit_t *)&in->dmac_bc;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_bc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_bc = *tmp;
    }
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac = *tmp;
    }
    {
        const vtss_ace_u48_t *tmp = (const vtss_ace_u48_t *)&in->smac;
#ifdef __cplusplus
        static_assert(sizeof(out.smac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->smac = *tmp;
    }
    {
        const vtss_hace_frame_etype_t *tmp = (const vtss_hace_frame_etype_t *)&in->etype;
#ifdef __cplusplus
        static_assert(sizeof(out.etype) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->etype = *tmp;
    }
    {
        const vtss_hace_frame_llc_t *tmp = (const vtss_hace_frame_llc_t *)&in->llc;
#ifdef __cplusplus
        static_assert(sizeof(out.llc) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->llc = *tmp;
    }
    {
        const vtss_hace_frame_snap_t *tmp = (const vtss_hace_frame_snap_t *)&in->snap;
#ifdef __cplusplus
        static_assert(sizeof(out.snap) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->snap = *tmp;
    }
    {
        const vtss_hace_frame_arp_t *tmp = (const vtss_hace_frame_arp_t *)&in->arp;
#ifdef __cplusplus
        static_assert(sizeof(out.arp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->arp = *tmp;
    }
    {
        const vtss_hace_frame_ipv4_t *tmp = (const vtss_hace_frame_ipv4_t *)&in->ipv4;
#ifdef __cplusplus
        static_assert(sizeof(out.ipv4) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ipv4 = *tmp;
    }
    {
        const vtss_hace_frame_ipv6_t *tmp = (const vtss_hace_frame_ipv6_t *)&in->ipv6;
#ifdef __cplusplus
        static_assert(sizeof(out.ipv6) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ipv6 = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_HACL)

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_conv_vtss_hacl_action_t_to_mesa_hacl_action_t(const vtss_hacl_action_t *in, mesa_hacl_action_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_acl_port_action_t *tmp = (const mesa_acl_port_action_t *)&in->port_action;
#ifdef __cplusplus
        static_assert(sizeof(out.port_action) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->port_action = *tmp;
    }
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(in->port_list, &out->port_list)); /* ag.rb:1455 */
    out->cpu = in->cpu;
    out->cpu_once = in->cpu_once;
    out->cpu_disable = in->cpu_disable;
    out->cpu_queue = in->cpu_queue;
    out->police = in->police;
    out->policer_no = in->policer_no;
    out->mirror = in->mirror;
    __RC(mesa_conv_vtss_acl_ptp_action_t_to_mesa_acl_ptp_action_t(&in->ptp_action, &out->ptp_action)); /* ag.rb:1455 */
    {
        const mesa_acl_ptp_action_conf_t *tmp = (const mesa_acl_ptp_action_conf_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
    {
        const mesa_acl_addr_action_t *tmp = (const mesa_acl_addr_action_t *)&in->addr;
#ifdef __cplusplus
        static_assert(sizeof(out.addr) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->addr = *tmp;
    }
    out->ifh_flag = in->ifh_flag;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_hacl_action_t_to_vtss_hacl_action_t(const mesa_hacl_action_t *in, vtss_hacl_action_t *out) /* ag.rb:1687 */
{
    {
        const vtss_acl_port_action_t *tmp = (const vtss_acl_port_action_t *)&in->port_action;
#ifdef __cplusplus
        static_assert(sizeof(out.port_action) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->port_action = *tmp;
    }
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(&in->port_list, out->port_list)); /* ag.rb:1455 */
    out->cpu = in->cpu;
    out->cpu_once = in->cpu_once;
    out->cpu_disable = in->cpu_disable;
    out->cpu_queue = in->cpu_queue;
    out->police = in->police;
    out->policer_no = in->policer_no;
    out->mirror = in->mirror;
    __RC(mesa_conv_mesa_acl_ptp_action_t_to_vtss_acl_ptp_action_t(&in->ptp_action, &out->ptp_action)); /* ag.rb:1455 */
    {
        const vtss_acl_ptp_action_conf_t *tmp = (const vtss_acl_ptp_action_conf_t *)&in->ptp;
#ifdef __cplusplus
        static_assert(sizeof(out.ptp) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->ptp = *tmp;
    }
    {
        const vtss_acl_addr_action_t *tmp = (const vtss_acl_addr_action_t *)&in->addr;
#ifdef __cplusplus
        static_assert(sizeof(out.addr) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->addr = *tmp;
    }
    out->ifh_flag = in->ifh_flag;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_HACL)

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_conv_vtss_hace_t_to_mesa_hace_t(const vtss_hace_t *in, mesa_hace_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->id = in->id;
    __RC(mesa_conv_vtss_hace_key_t_to_mesa_hace_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_vtss_hacl_action_t_to_mesa_hacl_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_hace_t_to_vtss_hace_t(const mesa_hace_t *in, vtss_hace_t *out) /* ag.rb:1687 */
{
    out->id = in->id;
    __RC(mesa_conv_mesa_hace_key_t_to_vtss_hace_key_t(&in->key, &out->key)); /* ag.rb:1455 */
    __RC(mesa_conv_mesa_hacl_action_t_to_vtss_hacl_action_t(&in->action, &out->action)); /* ag.rb:1455 */

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_HACL)

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_conv_vtss_synce_divider_t_to_mesa_synce_divider_t(const vtss_synce_divider_t *in, mesa_synce_divider_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_SYNCE_DIVIDER_1:
            *out = MESA_SYNCE_DIVIDER_1;
            return VTSS_RC_OK;
        case VTSS_SYNCE_DIVIDER_4:
            *out = MESA_SYNCE_DIVIDER_4;
            return VTSS_RC_OK;
        case VTSS_SYNCE_DIVIDER_5:
            *out = MESA_SYNCE_DIVIDER_5;
            return VTSS_RC_OK;
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case VTSS_SYNCE_DIVIDER_2:
            *out = MESA_SYNCE_DIVIDER_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case VTSS_SYNCE_DIVIDER_8:
            *out = MESA_SYNCE_DIVIDER_8;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case VTSS_SYNCE_DIVIDER_16:
            *out = MESA_SYNCE_DIVIDER_16;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case VTSS_SYNCE_DIVIDER_25:
            *out = MESA_SYNCE_DIVIDER_25;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_synce_divider_t_to_vtss_synce_divider_t(const mesa_synce_divider_t *in, vtss_synce_divider_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_SYNCE_DIVIDER_1:
            *out = VTSS_SYNCE_DIVIDER_1;
            return VTSS_RC_OK;
        case MESA_SYNCE_DIVIDER_4:
            *out = VTSS_SYNCE_DIVIDER_4;
            return VTSS_RC_OK;
        case MESA_SYNCE_DIVIDER_5:
            *out = VTSS_SYNCE_DIVIDER_5;
            return VTSS_RC_OK;
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case MESA_SYNCE_DIVIDER_2:
            *out = VTSS_SYNCE_DIVIDER_2;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case MESA_SYNCE_DIVIDER_8:
            *out = VTSS_SYNCE_DIVIDER_8;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case MESA_SYNCE_DIVIDER_16:
            *out = VTSS_SYNCE_DIVIDER_16;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        case MESA_SYNCE_DIVIDER_25:
            *out = VTSS_SYNCE_DIVIDER_25;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5)
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_SYNCE)

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_conv_vtss_synce_clock_out_t_to_mesa_synce_clock_out_t(const vtss_synce_clock_out_t *in, mesa_synce_clock_out_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_synce_divider_t_to_mesa_synce_divider_t(&in->divider, &out->divider)); /* ag.rb:1455 */
    out->enable = in->enable;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_synce_clock_out_t_to_vtss_synce_clock_out_t(const mesa_synce_clock_out_t *in, vtss_synce_clock_out_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_synce_divider_t_to_vtss_synce_divider_t(&in->divider, &out->divider)); /* ag.rb:1455 */
    out->enable = in->enable;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE)

#if defined(VTSS_FEATURE_SYNCE)
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5)
mesa_rc mesa_conv_vtss_synce_clock_in_type_t_to_mesa_synce_clock_in_type_t(const vtss_synce_clock_in_type_t *in, mesa_synce_clock_in_type_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_SYNCE_CLOCK_INTERFACE:
            *out = MESA_SYNCE_CLOCK_INTERFACE;
            return VTSS_RC_OK;
#if defined(VTSS_ARCH_SERVAL_T)
        case VTSS_SYNCE_CLOCK_STATION_CLK:
            *out = MESA_SYNCE_CLOCK_STATION_CLK;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T)
#if defined(VTSS_ARCH_SERVAL_T)
        case VTSS_SYNCE_CLOCK_DIFF:
            *out = MESA_SYNCE_CLOCK_DIFF;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T)
#if defined(VTSS_ARCH_SPARX5)
        case VTSS_SYNCE_CLOCK_AUX:
            *out = MESA_SYNCE_CLOCK_AUX;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SPARX5)
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_synce_clock_in_type_t_to_vtss_synce_clock_in_type_t(const mesa_synce_clock_in_type_t *in, vtss_synce_clock_in_type_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_SYNCE_CLOCK_INTERFACE:
            *out = VTSS_SYNCE_CLOCK_INTERFACE;
            return VTSS_RC_OK;
#if defined(VTSS_ARCH_SERVAL_T)
        case MESA_SYNCE_CLOCK_STATION_CLK:
            *out = VTSS_SYNCE_CLOCK_STATION_CLK;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T)
#if defined(VTSS_ARCH_SERVAL_T)
        case MESA_SYNCE_CLOCK_DIFF:
            *out = VTSS_SYNCE_CLOCK_DIFF;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SERVAL_T)
#if defined(VTSS_ARCH_SPARX5)
        case MESA_SYNCE_CLOCK_AUX:
            *out = VTSS_SYNCE_CLOCK_AUX;
            return VTSS_RC_OK;
#endif  // defined(VTSS_ARCH_SPARX5)
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5)
#endif  // defined(VTSS_FEATURE_SYNCE)

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_conv_vtss_synce_clock_in_t_to_mesa_synce_clock_in_t(const vtss_synce_clock_in_t *in, mesa_synce_clock_in_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->port_no = in->port_no;
    out->squelsh = in->squelsh;
    out->enable = in->enable;
#if defined (VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5)
    __RC(mesa_conv_vtss_synce_clock_in_type_t_to_mesa_synce_clock_in_type_t(&in->clk_in, &out->clk_in)); /* ag.rb:1455 */
#endif  // defined (VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_synce_clock_in_t_to_vtss_synce_clock_in_t(const mesa_synce_clock_in_t *in, vtss_synce_clock_in_t *out) /* ag.rb:1687 */
{
    out->port_no = in->port_no;
    out->squelsh = in->squelsh;
    out->enable = in->enable;
#if defined (VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5)
    __RC(mesa_conv_mesa_synce_clock_in_type_t_to_vtss_synce_clock_in_type_t(&in->clk_in, &out->clk_in)); /* ag.rb:1455 */
#endif  // defined (VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE)

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_conv_vtss_synce_station_clock_out_t_to_mesa_synce_station_clock_out_t(const vtss_synce_station_clock_out_t *in, mesa_synce_station_clock_out_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_synce_divider_t_to_mesa_synce_divider_t(&in->divider, &out->divider)); /* ag.rb:1455 */
    out->enable = in->enable;
    out->dpll_out_no = in->dpll_out_no;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_synce_station_clock_out_t_to_vtss_synce_station_clock_out_t(const mesa_synce_station_clock_out_t *in, vtss_synce_station_clock_out_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_synce_divider_t_to_vtss_synce_divider_t(&in->divider, &out->divider)); /* ag.rb:1455 */
    out->enable = in->enable;
    out->dpll_out_no = in->dpll_out_no;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_SYNCE)

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_conv_vtss_ts_operation_mode_t_to_mesa_ts_operation_mode_t(const vtss_ts_operation_mode_t *in, mesa_ts_operation_mode_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_ts_mode_t *tmp = (const mesa_ts_mode_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->domain = in->domain;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_ts_operation_mode_t_to_vtss_ts_operation_mode_t(const mesa_ts_operation_mode_t *in, vtss_ts_operation_mode_t *out) /* ag.rb:1687 */
{
    {
        const vtss_ts_mode_t *tmp = (const vtss_ts_mode_t *)&in->mode;
#ifdef __cplusplus
        static_assert(sizeof(out.mode) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->mode = *tmp;
    }
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    out->domain = in->domain;
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP)

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_conv_vtss_ts_timestamp_alloc_t_to_mesa_ts_timestamp_alloc_t(const vtss_ts_timestamp_alloc_t *in, mesa_ts_timestamp_alloc_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->port_mask = in->port_mask;
    out->context = in->context;
    {
        const mesa_ts_timestamp_alloc_cb_t *tmp = (const mesa_ts_timestamp_alloc_cb_t *)&in->cb;
#ifdef __cplusplus
        static_assert(sizeof(out.cb) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->cb = *tmp;
    }

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_ts_timestamp_alloc_t_to_vtss_ts_timestamp_alloc_t(const mesa_ts_timestamp_alloc_t *in, vtss_ts_timestamp_alloc_t *out) /* ag.rb:1687 */
{
    out->port_mask = in->port_mask;
    out->context = in->context;
    {
        const vtss_ts_timestamp_alloc_cb_t *tmp = (const vtss_ts_timestamp_alloc_cb_t *)&in->cb;
#ifdef __cplusplus
        static_assert(sizeof(out.cb) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->cb = *tmp;
    }

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP)

#if defined(VTSS_FEATURE_QOS_TAS)
mesa_rc mesa_conv_vtss_qos_tas_port_conf_t_to_mesa_qos_tas_port_conf_t(const vtss_qos_tas_port_conf_t *in, mesa_qos_tas_port_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    // skipped: gcl_length@vtss_qos_tas_port_conf_t
    // skipped: gcl@vtss_qos_tas_port_conf_t
    for (size_t i = 0; i < MESA_QUEUE_ARRAY_SIZE; ++i) {
        out->max_sdu[i] = in->max_sdu[i];
    }
    out->gate_enabled = in->gate_enabled;
    for (size_t i = 0; i < MESA_QUEUE_ARRAY_SIZE; ++i) {
        out->gate_open[i] = in->gate_open[i];
    }
    out->cycle_time = in->cycle_time;
    out->cycle_time_ext = in->cycle_time_ext;
    {
        const mesa_timestamp_t *tmp = (const mesa_timestamp_t *)&in->base_time;
#ifdef __cplusplus
        static_assert(sizeof(out.base_time) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->base_time = *tmp;
    }
    out->config_change = in->config_change;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_qos_tas_port_conf_t_to_vtss_qos_tas_port_conf_t(const mesa_qos_tas_port_conf_t *in, vtss_qos_tas_port_conf_t *out) /* ag.rb:1687 */
{
    // skipped: gcl_length@vtss_qos_tas_port_conf_t
    // skipped: gcl@vtss_qos_tas_port_conf_t
    for (size_t i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        out->max_sdu[i] = in->max_sdu[i];
    }
    out->gate_enabled = in->gate_enabled;
    for (size_t i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        out->gate_open[i] = in->gate_open[i];
    }
    out->cycle_time = in->cycle_time;
    out->cycle_time_ext = in->cycle_time_ext;
    {
        const vtss_timestamp_t *tmp = (const vtss_timestamp_t *)&in->base_time;
#ifdef __cplusplus
        static_assert(sizeof(out.base_time) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->base_time = *tmp;
    }
    out->config_change = in->config_change;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_QOS_TAS)

mesa_rc mesa_conv_vtss_port_interface_t_to_mesa_port_interface_t(const vtss_port_interface_t *in, mesa_port_interface_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        // skipped: VTSS_PORT_INTERFACE_SXGMII
        // skipped: VTSS_PORT_INTERFACE_USGMII
        // skipped: VTSS_PORT_INTERFACE_QXGMII
        // skipped: VTSS_PORT_INTERFACE_DXGMII_5G
        // skipped: VTSS_PORT_INTERFACE_DXGMII_10G
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
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_port_interface_t_to_vtss_port_interface_t(const mesa_port_interface_t *in, vtss_port_interface_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        // skipped: VTSS_PORT_INTERFACE_SXGMII
        // skipped: VTSS_PORT_INTERFACE_USGMII
        // skipped: VTSS_PORT_INTERFACE_QXGMII
        // skipped: VTSS_PORT_INTERFACE_DXGMII_5G
        // skipped: VTSS_PORT_INTERFACE_DXGMII_10G
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
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_vtss_serdes_mode_t_to_mesa_serdes_mode_t(const vtss_serdes_mode_t *in, mesa_serdes_mode_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        // skipped: VTSS_SERDES_MODE_SFI_KR
        // skipped: VTSS_SERDES_MODE_USXGMII
        // skipped: VTSS_SERDES_MODE_USGMII
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
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_serdes_mode_t_to_vtss_serdes_mode_t(const mesa_serdes_mode_t *in, vtss_serdes_mode_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        // skipped: VTSS_SERDES_MODE_SFI_KR
        // skipped: VTSS_SERDES_MODE_USXGMII
        // skipped: VTSS_SERDES_MODE_USGMII
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
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_vtss_packet_reg_type_t_to_mesa_packet_reg_type_t(const vtss_packet_reg_type_t *in, mesa_packet_reg_type_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_PACKET_REG_NORMAL:
            *out = MESA_PACKET_REG_NORMAL;
            return VTSS_RC_OK;
        case VTSS_PACKET_REG_FORWARD:
            *out = MESA_PACKET_REG_FORWARD;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
        case VTSS_PACKET_REG_DISCARD:
            *out = MESA_PACKET_REG_DISCARD;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
#if defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
        case VTSS_PACKET_REG_CPU_COPY:
            *out = MESA_PACKET_REG_CPU_COPY;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
        case VTSS_PACKET_REG_CPU_ONLY:
            *out = MESA_PACKET_REG_CPU_ONLY;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_packet_reg_type_t_to_vtss_packet_reg_type_t(const mesa_packet_reg_type_t *in, vtss_packet_reg_type_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_PACKET_REG_NORMAL:
            *out = VTSS_PACKET_REG_NORMAL;
            return VTSS_RC_OK;
        case MESA_PACKET_REG_FORWARD:
            *out = VTSS_PACKET_REG_FORWARD;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
        case MESA_PACKET_REG_DISCARD:
            *out = VTSS_PACKET_REG_DISCARD;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
#if defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
        case MESA_PACKET_REG_CPU_COPY:
            *out = VTSS_PACKET_REG_CPU_COPY;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_PACKET_PORT_REG_DISCARD)
        case MESA_PACKET_REG_CPU_ONLY:
            *out = VTSS_PACKET_REG_CPU_ONLY;
            return VTSS_RC_OK;
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_vtss_packet_rx_port_conf_t_to_mesa_packet_rx_port_conf_t(const vtss_packet_rx_port_conf_t *in, mesa_packet_rx_port_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
#if defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_vtss_packet_reg_type_t_to_mesa_packet_reg_type_t(&in->ipmc_ctrl_reg, &out->ipmc_ctrl_reg)); /* ag.rb:1455 */
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_vtss_packet_reg_type_t_to_mesa_packet_reg_type_t(&in->igmp_reg, &out->igmp_reg)); /* ag.rb:1455 */
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_vtss_packet_reg_type_t_to_mesa_packet_reg_type_t(&in->mld_reg, &out->mld_reg)); /* ag.rb:1455 */
#endif  // defined(VTSS_ARCH_SERVAL)
    for (size_t i = 0; i < 16; ++i) {
        __RC(mesa_conv_vtss_packet_reg_type_t_to_mesa_packet_reg_type_t(&in->bpdu_reg[i], &out->bpdu_reg[i])); /* ag.rb:1455 */
    }
    for (size_t i = 0; i < 16; ++i) {
        __RC(mesa_conv_vtss_packet_reg_type_t_to_mesa_packet_reg_type_t(&in->garp_reg[i], &out->garp_reg[i])); /* ag.rb:1455 */
    }
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
    for (size_t i = 0; i < 16; ++i) {
    const     mesa_packet_rx_port_l2cp_conf_t *tmp = (const mesa_packet_rx_port_l2cp_conf_t *)&in->bpdu[i];
        out->bpdu[i] = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
    for (size_t i = 0; i < 16; ++i) {
    const     mesa_packet_rx_port_l2cp_conf_t *tmp = (const mesa_packet_rx_port_l2cp_conf_t *)&in->garp[i];
        out->garp[i] = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_packet_rx_port_conf_t_to_vtss_packet_rx_port_conf_t(const mesa_packet_rx_port_conf_t *in, vtss_packet_rx_port_conf_t *out) /* ag.rb:1687 */
{
#if defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_mesa_packet_reg_type_t_to_vtss_packet_reg_type_t(&in->ipmc_ctrl_reg, &out->ipmc_ctrl_reg)); /* ag.rb:1455 */
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_mesa_packet_reg_type_t_to_vtss_packet_reg_type_t(&in->igmp_reg, &out->igmp_reg)); /* ag.rb:1455 */
#endif  // defined(VTSS_ARCH_SERVAL)
#if defined(VTSS_ARCH_SERVAL)
    __RC(mesa_conv_mesa_packet_reg_type_t_to_vtss_packet_reg_type_t(&in->mld_reg, &out->mld_reg)); /* ag.rb:1455 */
#endif  // defined(VTSS_ARCH_SERVAL)
    for (size_t i = 0; i < 16; ++i) {
        __RC(mesa_conv_mesa_packet_reg_type_t_to_vtss_packet_reg_type_t(&in->bpdu_reg[i], &out->bpdu_reg[i])); /* ag.rb:1455 */
    }
    for (size_t i = 0; i < 16; ++i) {
        __RC(mesa_conv_mesa_packet_reg_type_t_to_vtss_packet_reg_type_t(&in->garp_reg[i], &out->garp_reg[i])); /* ag.rb:1455 */
    }
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
    for (size_t i = 0; i < 16; ++i) {
    const     vtss_packet_rx_port_l2cp_conf_t *tmp = (const vtss_packet_rx_port_l2cp_conf_t *)&in->bpdu[i];
        out->bpdu[i] = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
    for (size_t i = 0; i < 16; ++i) {
    const     vtss_packet_rx_port_l2cp_conf_t *tmp = (const vtss_packet_rx_port_l2cp_conf_t *)&in->garp[i];
        out->garp[i] = *tmp;
    }
#endif  // defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_vop_conf_t_to_mesa_vop_conf_t(const vtss_vop_conf_t *in, mesa_vop_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    {
        const mesa_mac_t *tmp = (const mesa_mac_t *)&in->multicast_dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.multicast_dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->multicast_dmac = *tmp;
    }
#if defined(VTSS_FEATURE_VOP_V2)
    for (size_t i = 0; i < 2; ++i) {
        out->auto_copy_period[i] = in->auto_copy_period[i];
    }
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_ccm_valid = in->auto_copy_ccm_valid;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_ccm_tlv = in->auto_copy_ccm_tlv;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_ccm_err = in->auto_copy_ccm_err;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_lbr = in->auto_copy_lbr;
#endif  // defined(VTSS_FEATURE_VOP_V2)
    out->voe_queue_ccm = in->voe_queue_ccm;
    out->voe_queue_lt = in->voe_queue_lt;
    out->voe_queue_lbm = in->voe_queue_lbm;
    out->voe_queue_lbr = in->voe_queue_lbr;
    out->voe_queue_aps = in->voe_queue_aps;
    out->voe_queue_err = in->voe_queue_err;
#if defined(VTSS_FEATURE_VOP_V2)
    out->voi_queue = in->voi_queue;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_vop_conf_t_to_vtss_vop_conf_t(const mesa_vop_conf_t *in, vtss_vop_conf_t *out) /* ag.rb:1687 */
{
    {
        const vtss_mac_t *tmp = (const vtss_mac_t *)&in->multicast_dmac;
#ifdef __cplusplus
        static_assert(sizeof(out.multicast_dmac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->multicast_dmac = *tmp;
    }
#if defined(VTSS_FEATURE_VOP_V2)
    for (size_t i = 0; i < 2; ++i) {
        out->auto_copy_period[i] = in->auto_copy_period[i];
    }
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_ccm_valid = in->auto_copy_ccm_valid;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_ccm_tlv = in->auto_copy_ccm_tlv;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_ccm_err = in->auto_copy_ccm_err;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->auto_copy_lbr = in->auto_copy_lbr;
#endif  // defined(VTSS_FEATURE_VOP_V2)
    out->voe_queue_ccm = in->voe_queue_ccm;
    out->voe_queue_lt = in->voe_queue_lt;
    out->voe_queue_lbm = in->voe_queue_lbm;
    out->voe_queue_lbr = in->voe_queue_lbr;
    out->voe_queue_aps = in->voe_queue_aps;
    out->voe_queue_err = in->voe_queue_err;
#if defined(VTSS_FEATURE_VOP_V2)
    out->voi_queue = in->voi_queue;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_conf_t_to_mesa_voe_conf_t(const vtss_voe_conf_t *in, mesa_voe_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->enable = in->enable;
    {
        const mesa_mac_t *tmp = (const mesa_mac_t *)&in->unicast_mac;
#ifdef __cplusplus
        static_assert(sizeof(out.unicast_mac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->unicast_mac = *tmp;
    }
    out->meg_level = in->meg_level;
    {
        const mesa_voe_dmac_check_t *tmp = (const mesa_voe_dmac_check_t *)&in->dmac_check_type;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_check_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_check_type = *tmp;
    }
    out->loop_iflow_id = in->loop_iflow_id;
#if defined(VTSS_FEATURE_VOP_V2)
    out->block_mel_high = in->block_mel_high;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_conf_t_to_vtss_voe_conf_t(const mesa_voe_conf_t *in, vtss_voe_conf_t *out) /* ag.rb:1687 */
{
    out->enable = in->enable;
    {
        const vtss_mac_t *tmp = (const vtss_mac_t *)&in->unicast_mac;
#ifdef __cplusplus
        static_assert(sizeof(out.unicast_mac) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->unicast_mac = *tmp;
    }
    out->meg_level = in->meg_level;
    {
        const vtss_voe_dmac_check_t *tmp = (const vtss_voe_dmac_check_t *)&in->dmac_check_type;
#ifdef __cplusplus
        static_assert(sizeof(out.dmac_check_type) == sizeof(*tmp), "size check");
#endif // __cplusplus
        out->dmac_check_type = *tmp;
    }
    out->loop_iflow_id = in->loop_iflow_id;
#if defined(VTSS_FEATURE_VOP_V2)
    out->block_mel_high = in->block_mel_high;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_ccm_period_t_to_mesa_voe_ccm_period_t(const vtss_voe_ccm_period_t *in, mesa_voe_ccm_period_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_VOE_CCM_PERIOD_3_3_MS:
            *out = MESA_VOE_CCM_PERIOD_3_3_MS;
            return VTSS_RC_OK;
        case VTSS_VOE_CCM_PERIOD_10_MS:
            *out = MESA_VOE_CCM_PERIOD_10_MS;
            return VTSS_RC_OK;
        case VTSS_VOE_CCM_PERIOD_100_MS:
            *out = MESA_VOE_CCM_PERIOD_100_MS;
            return VTSS_RC_OK;
        case VTSS_VOE_CCM_PERIOD_1_SEC:
            *out = MESA_VOE_CCM_PERIOD_1_SEC;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_VOP_V2)
        case VTSS_VOE_CCM_PERIOD_10_SEC:
            *out = MESA_VOE_CCM_PERIOD_10_SEC;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_VOP_V2)
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_voe_ccm_period_t_to_vtss_voe_ccm_period_t(const mesa_voe_ccm_period_t *in, vtss_voe_ccm_period_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_VOE_CCM_PERIOD_3_3_MS:
            *out = VTSS_VOE_CCM_PERIOD_3_3_MS;
            return VTSS_RC_OK;
        case MESA_VOE_CCM_PERIOD_10_MS:
            *out = VTSS_VOE_CCM_PERIOD_10_MS;
            return VTSS_RC_OK;
        case MESA_VOE_CCM_PERIOD_100_MS:
            *out = VTSS_VOE_CCM_PERIOD_100_MS;
            return VTSS_RC_OK;
        case MESA_VOE_CCM_PERIOD_1_SEC:
            *out = VTSS_VOE_CCM_PERIOD_1_SEC;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_VOP_V2)
        case MESA_VOE_CCM_PERIOD_10_SEC:
            *out = VTSS_VOE_CCM_PERIOD_10_SEC;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_VOP_V2)
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_oam_cpu_copy_t_to_mesa_oam_cpu_copy_t(const vtss_oam_cpu_copy_t *in, mesa_oam_cpu_copy_t *out) /* ag.rb:1679 */
{
    switch (*in) {
        case VTSS_OAM_CPU_COPY_NONE:
            *out = MESA_OAM_CPU_COPY_NONE;
            return VTSS_RC_OK;
        case VTSS_OAM_CPU_COPY_ALL:
            *out = MESA_OAM_CPU_COPY_ALL;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_VOP_V2)
        case VTSS_OAM_CPU_COPY_AUTO:
            *out = MESA_OAM_CPU_COPY_AUTO;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_VOP_V2)
        default:
            return VTSS_RC_ERROR;
    }
}

mesa_rc mesa_conv_mesa_oam_cpu_copy_t_to_vtss_oam_cpu_copy_t(const mesa_oam_cpu_copy_t *in, vtss_oam_cpu_copy_t *out) /* ag.rb:1687 */
{
    switch (*in) {
        case MESA_OAM_CPU_COPY_NONE:
            *out = VTSS_OAM_CPU_COPY_NONE;
            return VTSS_RC_OK;
        case MESA_OAM_CPU_COPY_ALL:
            *out = VTSS_OAM_CPU_COPY_ALL;
            return VTSS_RC_OK;
#if defined(VTSS_FEATURE_VOP_V2)
        case MESA_OAM_CPU_COPY_AUTO:
            *out = VTSS_OAM_CPU_COPY_AUTO;
            return VTSS_RC_OK;
#endif  // defined(VTSS_FEATURE_VOP_V2)
        default:
            return VTSS_RC_ERROR;
    }
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_cc_conf_t_to_mesa_voe_cc_conf_t(const vtss_voe_cc_conf_t *in, mesa_voe_cc_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->enable = in->enable;
    __RC(mesa_conv_vtss_oam_cpu_copy_t_to_mesa_oam_cpu_copy_t(&in->cpu_copy, &out->cpu_copy)); /* ag.rb:1455 */
    out->seq_no_update = in->seq_no_update;
    out->count_as_selected = in->count_as_selected;
    __RC(mesa_conv_vtss_voe_ccm_period_t_to_mesa_voe_ccm_period_t(&in->expected_period, &out->expected_period)); /* ag.rb:1455 */
    out->expected_priority = in->expected_priority;
    for (size_t i = 0; i < MESA_OAM_MEG_ID_LENGTH; ++i) {
        out->expected_megid[i] = in->expected_megid[i];
    }
    out->expected_peer_mepid = in->expected_peer_mepid;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_cc_conf_t_to_vtss_voe_cc_conf_t(const mesa_voe_cc_conf_t *in, vtss_voe_cc_conf_t *out) /* ag.rb:1687 */
{
    out->enable = in->enable;
    __RC(mesa_conv_mesa_oam_cpu_copy_t_to_vtss_oam_cpu_copy_t(&in->cpu_copy, &out->cpu_copy)); /* ag.rb:1455 */
    out->seq_no_update = in->seq_no_update;
    out->count_as_selected = in->count_as_selected;
    __RC(mesa_conv_mesa_voe_ccm_period_t_to_vtss_voe_ccm_period_t(&in->expected_period, &out->expected_period)); /* ag.rb:1455 */
    out->expected_priority = in->expected_priority;
    for (size_t i = 0; i < VTSS_OAM_MEG_ID_LENGTH; ++i) {
        out->expected_megid[i] = in->expected_megid[i];
    }
    out->expected_peer_mepid = in->expected_peer_mepid;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_lb_conf_t_to_mesa_voe_lb_conf_t(const vtss_voe_lb_conf_t *in, mesa_voe_lb_conf_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->enable = in->enable;
    out->count_as_selected = in->count_as_selected;
    out->lbm_cpu_copy = in->lbm_cpu_copy;
    __RC(mesa_conv_vtss_oam_cpu_copy_t_to_mesa_oam_cpu_copy_t(&in->lbr_cpu_copy, &out->lbr_cpu_copy)); /* ag.rb:1455 */
    out->trans_id = in->trans_id;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_lb_conf_t_to_vtss_voe_lb_conf_t(const mesa_voe_lb_conf_t *in, vtss_voe_lb_conf_t *out) /* ag.rb:1687 */
{
    out->enable = in->enable;
    out->count_as_selected = in->count_as_selected;
    out->lbm_cpu_copy = in->lbm_cpu_copy;
    __RC(mesa_conv_mesa_oam_cpu_copy_t_to_vtss_oam_cpu_copy_t(&in->lbr_cpu_copy, &out->lbr_cpu_copy)); /* ag.rb:1455 */
    out->trans_id = in->trans_id;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_status_t_to_mesa_voe_status_t(const vtss_voe_status_t *in, mesa_voe_status_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->opcode_unexp_seen = in->opcode_unexp_seen;
    out->dmac_unexp_seen = in->dmac_unexp_seen;
    out->tx_level_low_seen = in->tx_level_low_seen;
#if defined(VTSS_FEATURE_VOP_V2)
    out->version_unexp_seen = in->version_unexp_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_level_low_seen = in->rx_level_low_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_level_high_seen = in->rx_level_high_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_status_t_to_vtss_voe_status_t(const mesa_voe_status_t *in, vtss_voe_status_t *out) /* ag.rb:1687 */
{
    out->opcode_unexp_seen = in->opcode_unexp_seen;
    out->dmac_unexp_seen = in->dmac_unexp_seen;
    out->tx_level_low_seen = in->tx_level_low_seen;
#if defined(VTSS_FEATURE_VOP_V2)
    out->version_unexp_seen = in->version_unexp_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_level_low_seen = in->rx_level_low_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_level_high_seen = in->rx_level_high_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_counters_t_to_mesa_voe_counters_t(const vtss_voe_counters_t *in, mesa_voe_counters_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->rx_counter = in->rx_counter;
    out->tx_counter = in->tx_counter;
    out->rx_selected_counter = in->rx_selected_counter;
    out->tx_selected_counter = in->tx_selected_counter;
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_discard_counter = in->rx_discard_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->tx_discard_counter = in->tx_discard_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_counters_t_to_vtss_voe_counters_t(const mesa_voe_counters_t *in, vtss_voe_counters_t *out) /* ag.rb:1687 */
{
    out->rx_counter = in->rx_counter;
    out->tx_counter = in->tx_counter;
    out->rx_selected_counter = in->rx_selected_counter;
    out->tx_selected_counter = in->tx_selected_counter;
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_discard_counter = in->rx_discard_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->tx_discard_counter = in->tx_discard_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_cc_status_t_to_mesa_voe_cc_status_t(const vtss_voe_cc_status_t *in, mesa_voe_cc_status_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->zero_period = in->zero_period;
    out->rdi = in->rdi;
    out->loc = in->loc;
    out->period_unexp = in->period_unexp;
    out->priority_unexp = in->priority_unexp;
    out->mep_id_unexp = in->mep_id_unexp;
    out->meg_id_unexp = in->meg_id_unexp;
#if defined(VTSS_FEATURE_VOP_V2)
    out->mel_unexp = in->mel_unexp;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_port = in->rx_port;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->port_status_tlv = in->port_status_tlv;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->if_status_tlv = in->if_status_tlv;
#endif  // defined(VTSS_FEATURE_VOP_V2)
    out->seen = in->seen;
#if defined(VTSS_FEATURE_VOP_V2)
    out->tlv_seen = in->tlv_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->seq_unexp_seen = in->seq_unexp_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_cc_status_t_to_vtss_voe_cc_status_t(const mesa_voe_cc_status_t *in, vtss_voe_cc_status_t *out) /* ag.rb:1687 */
{
    out->zero_period = in->zero_period;
    out->rdi = in->rdi;
    out->loc = in->loc;
    out->period_unexp = in->period_unexp;
    out->priority_unexp = in->priority_unexp;
    out->mep_id_unexp = in->mep_id_unexp;
    out->meg_id_unexp = in->meg_id_unexp;
#if defined(VTSS_FEATURE_VOP_V2)
    out->mel_unexp = in->mel_unexp;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_port = in->rx_port;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->port_status_tlv = in->port_status_tlv;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->if_status_tlv = in->if_status_tlv;
#endif  // defined(VTSS_FEATURE_VOP_V2)
    out->seen = in->seen;
#if defined(VTSS_FEATURE_VOP_V2)
    out->tlv_seen = in->tlv_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->seq_unexp_seen = in->seq_unexp_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_lb_status_t_to_mesa_voe_lb_status_t(const vtss_voe_lb_status_t *in, mesa_voe_lb_status_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->lbm_seen = in->lbm_seen;
    out->lbr_seen = in->lbr_seen;
#if defined(VTSS_FEATURE_VOP_V2)
    out->trans_unexp_seen = in->trans_unexp_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
    out->tx_trans_id = in->tx_trans_id;
    out->rx_trans_id = in->rx_trans_id;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_lb_status_t_to_vtss_voe_lb_status_t(const mesa_voe_lb_status_t *in, vtss_voe_lb_status_t *out) /* ag.rb:1687 */
{
    out->lbm_seen = in->lbm_seen;
    out->lbr_seen = in->lbr_seen;
#if defined(VTSS_FEATURE_VOP_V2)
    out->trans_unexp_seen = in->trans_unexp_seen;
#endif  // defined(VTSS_FEATURE_VOP_V2)
    out->tx_trans_id = in->tx_trans_id;
    out->rx_trans_id = in->rx_trans_id;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_conv_vtss_voe_lb_counters_t_to_mesa_voe_lb_counters_t(const vtss_voe_lb_counters_t *in, mesa_voe_lb_counters_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    out->rx_lbr_counter = in->rx_lbr_counter;
    out->tx_lbm_counter = in->tx_lbm_counter;
    out->rx_lbr_oo_counter = in->rx_lbr_oo_counter;
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_lbr_crc_counter = in->rx_lbr_crc_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->tx_lbr_counter = in->tx_lbr_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_voe_lb_counters_t_to_vtss_voe_lb_counters_t(const mesa_voe_lb_counters_t *in, vtss_voe_lb_counters_t *out) /* ag.rb:1687 */
{
    out->rx_lbr_counter = in->rx_lbr_counter;
    out->tx_lbm_counter = in->tx_lbm_counter;
    out->rx_lbr_oo_counter = in->rx_lbr_oo_counter;
#if defined(VTSS_FEATURE_VOP_V2)
    out->rx_lbr_crc_counter = in->rx_lbr_crc_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)
#if defined(VTSS_FEATURE_VOP_V2)
    out->tx_lbr_counter = in->tx_lbr_counter;
#endif  // defined(VTSS_FEATURE_VOP_V2)

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_VOP)

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_conv_vtss_ewis_tti_mode_t_to_mesa_ewis_tti_mode_t(const vtss_ewis_tti_mode_t *in, mesa_ewis_tti_mode_t *out) /* ag.rb:1679 */
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

mesa_rc mesa_conv_mesa_ewis_tti_mode_t_to_vtss_ewis_tti_mode_t(const mesa_ewis_tti_mode_t *in, vtss_ewis_tti_mode_t *out) /* ag.rb:1687 */
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
mesa_rc mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(const vtss_ewis_tti_t *in, mesa_ewis_tti_t *out) /* ag.rb:1679 */
{
    memset(out, 0, sizeof(*out)); /* ag.rb:1308 */
    __RC(mesa_conv_vtss_ewis_tti_mode_t_to_mesa_ewis_tti_mode_t(&in->mode, &out->mode)); /* ag.rb:1455 */
    for (size_t i = 0; i < 64; ++i) {
        out->tti[i] = in->tti[i];
    }
    out->valid = in->valid;

    return VTSS_RC_OK;
}

mesa_rc mesa_conv_mesa_ewis_tti_t_to_vtss_ewis_tti_t(const mesa_ewis_tti_t *in, vtss_ewis_tti_t *out) /* ag.rb:1687 */
{
    __RC(mesa_conv_mesa_ewis_tti_mode_t_to_vtss_ewis_tti_mode_t(&in->mode, &out->mode)); /* ag.rb:1455 */
    for (size_t i = 0; i < 64; ++i) {
        out->tti[i] = in->tti[i];
    }
    out->valid = in->valid;

    return VTSS_RC_OK;
}
#endif  // defined(VTSS_FEATURE_WIS)

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V1)
mesa_rc mesa_afi_free(const mesa_inst_t inst, mesa_afi_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_free((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_free(const mesa_inst_t inst, mesa_afi_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V1) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_free(const mesa_inst_t inst, mesa_afi_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V1)
mesa_rc mesa_afi_hijack(const mesa_inst_t inst, mesa_afi_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_hijack((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_hijack(const mesa_inst_t inst, mesa_afi_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V1) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_hijack(const mesa_inst_t inst, mesa_afi_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_fast_inj_alloc(const mesa_inst_t inst, const mesa_afi_fast_inj_alloc_cfg_t *const cfg, mesa_afi_fastid_t *const fastid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_afi_fast_inj_alloc_cfg_t) == sizeof(mesa_afi_fast_inj_alloc_cfg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_afi_fast_inj_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_afi_fast_inj_alloc_cfg_t *)cfg /* ag.rb:1867 */, fastid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_fast_inj_alloc(const mesa_inst_t inst, const mesa_afi_fast_inj_alloc_cfg_t *const cfg, mesa_afi_fastid_t *const fastid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_fast_inj_alloc(const mesa_inst_t inst, const mesa_afi_fast_inj_alloc_cfg_t *const cfg, mesa_afi_fastid_t *const fastid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_fast_inj_free(const mesa_inst_t inst, mesa_afi_fastid_t fastid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_fast_inj_free((const vtss_inst_t)inst /* ag.rb:1870 */, fastid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_fast_inj_free(const mesa_inst_t inst, mesa_afi_fastid_t fastid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_fast_inj_free(const mesa_inst_t inst, mesa_afi_fastid_t fastid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_fast_inj_frm_hijack(const mesa_inst_t inst, mesa_afi_fastid_t fastid, const mesa_afi_fast_inj_frm_cfg_t *const cfg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_afi_fast_inj_frm_cfg_t) == sizeof(mesa_afi_fast_inj_frm_cfg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_afi_fast_inj_frm_hijack((const vtss_inst_t)inst /* ag.rb:1870 */, fastid, (const vtss_afi_fast_inj_frm_cfg_t *)cfg /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_fast_inj_frm_hijack(const mesa_inst_t inst, mesa_afi_fastid_t fastid, const mesa_afi_fast_inj_frm_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_fast_inj_frm_hijack(const mesa_inst_t inst, mesa_afi_fastid_t fastid, const mesa_afi_fast_inj_frm_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_fast_inj_stop(const mesa_inst_t inst, mesa_afi_fastid_t fastid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_fast_inj_stop((const vtss_inst_t)inst /* ag.rb:1870 */, fastid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_fast_inj_stop(const mesa_inst_t inst, mesa_afi_fastid_t fastid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_fast_inj_stop(const mesa_inst_t inst, mesa_afi_fastid_t fastid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_fast_inj_seq_cnt_get(const mesa_inst_t inst, mesa_afi_fastid_t fastid, uint32_t *const seq_cnt)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_fast_inj_seq_cnt_get((const vtss_inst_t)inst /* ag.rb:1870 */, fastid, seq_cnt); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_fast_inj_seq_cnt_get(const mesa_inst_t inst, mesa_afi_fastid_t fastid, uint32_t *const seq_cnt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_fast_inj_seq_cnt_get(const mesa_inst_t inst, mesa_afi_fastid_t fastid, uint32_t *const seq_cnt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_slow_inj_alloc(const mesa_inst_t inst, const mesa_afi_slow_inj_alloc_cfg_t *const cfg, mesa_afi_slowid_t *const slowid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_afi_slow_inj_alloc_cfg_t) == sizeof(mesa_afi_slow_inj_alloc_cfg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_afi_slow_inj_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_afi_slow_inj_alloc_cfg_t *)cfg /* ag.rb:1867 */, slowid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_slow_inj_alloc(const mesa_inst_t inst, const mesa_afi_slow_inj_alloc_cfg_t *const cfg, mesa_afi_slowid_t *const slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_slow_inj_alloc(const mesa_inst_t inst, const mesa_afi_slow_inj_alloc_cfg_t *const cfg, mesa_afi_slowid_t *const slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_slow_inj_free(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_slow_inj_free((const vtss_inst_t)inst /* ag.rb:1870 */, slowid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_slow_inj_free(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_slow_inj_free(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_slow_inj_frm_hijack(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_slow_inj_frm_hijack((const vtss_inst_t)inst /* ag.rb:1870 */, slowid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_slow_inj_frm_hijack(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_slow_inj_frm_hijack(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_slow_inj_start(const mesa_inst_t inst, mesa_afi_slowid_t slowid, const mesa_afi_slow_inj_start_cfg_t *const cfg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_afi_slow_inj_start_cfg_t) == sizeof(mesa_afi_slow_inj_start_cfg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_afi_slow_inj_start((const vtss_inst_t)inst /* ag.rb:1870 */, slowid, (const vtss_afi_slow_inj_start_cfg_t *)cfg /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_slow_inj_start(const mesa_inst_t inst, mesa_afi_slowid_t slowid, const mesa_afi_slow_inj_start_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_slow_inj_start(const mesa_inst_t inst, mesa_afi_slowid_t slowid, const mesa_afi_slow_inj_start_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_slow_inj_stop(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_slow_inj_stop((const vtss_inst_t)inst /* ag.rb:1870 */, slowid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_slow_inj_stop(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_slow_inj_stop(const mesa_inst_t inst, mesa_afi_slowid_t slowid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_port_start(const mesa_inst_t inst, mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_port_start((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_port_start(const mesa_inst_t inst, mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_port_start(const mesa_inst_t inst, mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_AFI_SWC)
#if defined(VTSS_AFI_V2)
mesa_rc mesa_afi_port_stop(const mesa_inst_t inst, mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_afi_port_stop((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_afi_port_stop(const mesa_inst_t inst, mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_AFI_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_afi_port_stop(const mesa_inst_t inst, mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_AFI_SWC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_rd(const mesa_inst_t inst, const uint32_t addr, uint32_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_rd((const vtss_inst_t)inst /* ag.rb:1870 */, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_rd(const mesa_inst_t inst, const uint32_t addr, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_wr(const mesa_inst_t inst, const uint32_t addr, const uint32_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_wr((const vtss_inst_t)inst /* ag.rb:1870 */, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_wr(const mesa_inst_t inst, const uint32_t addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_wrm(const mesa_inst_t inst, const uint32_t addr, const uint32_t value, const uint32_t mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_wrm((const vtss_inst_t)inst /* ag.rb:1870 */, addr, value, mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_wrm(const mesa_inst_t inst, const uint32_t addr, const uint32_t value, const uint32_t mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_global_enable_set(const mesa_inst_t inst, const mesa_clock_global_enable_t ena)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_global_enable_set((const vtss_inst_t)inst /* ag.rb:1870 */, ena); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_global_enable_set(const mesa_inst_t inst, const mesa_clock_global_enable_t ena)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_global_enable_get(const mesa_inst_t inst, mesa_clock_global_enable_t * ena)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_global_enable_get((const vtss_inst_t)inst /* ag.rb:1870 */, ena); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_global_enable_get(const mesa_inst_t inst, mesa_clock_global_enable_t * ena)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_global_sw_reset(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_global_sw_reset((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_global_sw_reset(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_shutdown(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_shutdown((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_shutdown(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_selection_mode_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_selection_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_selection_conf_t) == sizeof(mesa_clock_selection_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_selection_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (const vtss_clock_selection_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_selection_mode_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_selection_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_selection_mode_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_selection_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_selection_conf_t) == sizeof(mesa_clock_selection_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_selection_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (vtss_clock_selection_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_selection_mode_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_selection_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_operation_conf_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_dpll_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_dpll_conf_t) == sizeof(mesa_clock_dpll_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_operation_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (const vtss_clock_dpll_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_operation_conf_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_dpll_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_operation_conf_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_dpll_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_dpll_conf_t) == sizeof(mesa_clock_dpll_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_operation_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (vtss_clock_dpll_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_operation_conf_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_dpll_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_ho_stack_conf_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_ho_stack_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_ho_stack_conf_t) == sizeof(mesa_clock_ho_stack_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_ho_stack_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (const vtss_clock_ho_stack_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_ho_stack_conf_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_ho_stack_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_ho_stack_conf_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_ho_stack_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_ho_stack_conf_t) == sizeof(mesa_clock_ho_stack_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_ho_stack_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (vtss_clock_ho_stack_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_ho_stack_conf_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_ho_stack_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_ho_stack_content_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_ho_stack_content_t *const cont)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_ho_stack_content_t) == sizeof(mesa_clock_ho_stack_content_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_ho_stack_content_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (vtss_clock_ho_stack_content_t *)cont /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_ho_stack_content_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_ho_stack_content_t *const cont)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_dco_frequency_offset_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const int64_t offset)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_dco_frequency_offset_set((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, offset); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_dco_frequency_offset_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const int64_t offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_dco_frequency_offset_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, int64_t *const offset)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_dco_frequency_offset_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, offset); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_dco_frequency_offset_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, int64_t *const offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_filter_bw_set(const mesa_inst_t inst, const uint8_t clock_output, const uint32_t bw_100uhz)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_filter_bw_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, bw_100uhz); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_filter_bw_set(const mesa_inst_t inst, const uint8_t clock_output, const uint32_t bw_100uhz)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_filter_bw_get(const mesa_inst_t inst, const uint8_t clock_output, uint32_t * bw_100uhz)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_filter_bw_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, bw_100uhz); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_filter_bw_get(const mesa_inst_t inst, const uint8_t clock_output, uint32_t * bw_100uhz)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_filter_lock_fast_set(const mesa_inst_t inst, const uint8_t clock_output)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_filter_lock_fast_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_filter_lock_fast_set(const mesa_inst_t inst, const uint8_t clock_output)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_filter_lock_fast_get(const mesa_inst_t inst, const uint8_t clock_output, mesa_bool_t * lock_completed)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_filter_lock_fast_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, lock_completed); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_filter_lock_fast_get(const mesa_inst_t inst, const uint8_t clock_output, mesa_bool_t * lock_completed)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_psl_conf_set(const mesa_inst_t inst, const uint8_t clock_output, const mesa_clock_psl_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_psl_conf_t) == sizeof(mesa_clock_psl_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_output_psl_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, (const vtss_clock_psl_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_psl_conf_set(const mesa_inst_t inst, const uint8_t clock_output, const mesa_clock_psl_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_psl_conf_get(const mesa_inst_t inst, const uint8_t clock_output, mesa_clock_psl_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_psl_conf_t) == sizeof(mesa_clock_psl_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_output_psl_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, (vtss_clock_psl_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_psl_conf_get(const mesa_inst_t inst, const uint8_t clock_output, mesa_clock_psl_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_adj_frequency_set(const mesa_inst_t inst, const uint8_t clock_output, const int64_t adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_adj_frequency_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_adj_frequency_set(const mesa_inst_t inst, const uint8_t clock_output, const int64_t adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_adj_frequency_get(const mesa_inst_t inst, const uint8_t clock_output, int64_t *const adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_adj_frequency_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_adj_frequency_get(const mesa_inst_t inst, const uint8_t clock_output, int64_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_adj_phase_set(const mesa_inst_t inst, const uint8_t clock_output, const int32_t adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_adj_phase_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_adj_phase_set(const mesa_inst_t inst, const uint8_t clock_output, const int32_t adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_adj_phase_get(const mesa_inst_t inst, mesa_bool_t *const adj_ongoing)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_adj_phase_get((const vtss_inst_t)inst /* ag.rb:1870 */, adj_ongoing); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_adj_phase_get(const mesa_inst_t inst, mesa_bool_t *const adj_ongoing)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_priority_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const uint8_t clock_input, const mesa_clock_priority_selector_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_priority_selector_t) == sizeof(mesa_clock_priority_selector_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_priority_set((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, clock_input, (const vtss_clock_priority_selector_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_priority_set(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const uint8_t clock_input, const mesa_clock_priority_selector_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_priority_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const uint8_t clock_input, mesa_clock_priority_selector_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_priority_selector_t) == sizeof(mesa_clock_priority_selector_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_priority_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, clock_input, (vtss_clock_priority_selector_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_priority_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const uint8_t clock_input, mesa_clock_priority_selector_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_frequency_set(const mesa_inst_t inst, const uint8_t clock_input, const uint32_t freq_khz, const mesa_bool_t use_internal_clock_src)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_input_frequency_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, freq_khz, use_internal_clock_src); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_frequency_set(const mesa_inst_t inst, const uint8_t clock_input, const uint32_t freq_khz, const mesa_bool_t use_internal_clock_src)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_frequency_get(const mesa_inst_t inst, const uint8_t clock_input, uint32_t *const freq_khz, mesa_bool_t *const use_internal_clock_src)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_input_frequency_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, freq_khz, use_internal_clock_src); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_frequency_get(const mesa_inst_t inst, const uint8_t clock_input, uint32_t *const freq_khz, mesa_bool_t *const use_internal_clock_src)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_frequency_ratio_set(const mesa_inst_t inst, const uint8_t clock_input, const uint32_t freq_khz, const mesa_clock_ratio_t *const ratio, const mesa_bool_t use_internal_clock_src)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_ratio_t) == sizeof(mesa_clock_ratio_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_frequency_ratio_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, freq_khz, (const vtss_clock_ratio_t *)ratio /* ag.rb:1867 */, use_internal_clock_src); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_frequency_ratio_set(const mesa_inst_t inst, const uint8_t clock_input, const uint32_t freq_khz, const mesa_clock_ratio_t *const ratio, const mesa_bool_t use_internal_clock_src)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_frequency_ratio_get(const mesa_inst_t inst, const uint8_t clock_input, uint32_t *const freq_khz, mesa_clock_ratio_t *const ratio, mesa_bool_t *const use_internal_clock_src)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_ratio_t) == sizeof(mesa_clock_ratio_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_frequency_ratio_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, freq_khz, (vtss_clock_ratio_t *)ratio /* ag.rb:1867 */, use_internal_clock_src); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_frequency_ratio_get(const mesa_inst_t inst, const uint8_t clock_input, uint32_t *const freq_khz, mesa_clock_ratio_t *const ratio, mesa_bool_t *const use_internal_clock_src)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_frequency_set(const mesa_inst_t inst, const uint8_t clock_output, const uint32_t freq_khz, const uint32_t par_freq_khz)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_frequency_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, freq_khz, par_freq_khz); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_frequency_set(const mesa_inst_t inst, const uint8_t clock_output, const uint32_t freq_khz, const uint32_t par_freq_khz)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_frequency_get(const mesa_inst_t inst, const uint8_t clock_output, uint32_t *const freq_khz, uint32_t *const par_freq_khz)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_frequency_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, freq_khz, par_freq_khz); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_frequency_get(const mesa_inst_t inst, const uint8_t clock_output, uint32_t *const freq_khz, uint32_t *const par_freq_khz)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_frequency_ratio_set(const mesa_inst_t inst, const uint8_t clock_output, const uint32_t freq_khz, const uint32_t par_freq_khz, const mesa_clock_ratio_t *const ratio)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_ratio_t) == sizeof(mesa_clock_ratio_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_output_frequency_ratio_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, freq_khz, par_freq_khz, (const vtss_clock_ratio_t *)ratio /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_frequency_ratio_set(const mesa_inst_t inst, const uint8_t clock_output, const uint32_t freq_khz, const uint32_t par_freq_khz, const mesa_clock_ratio_t *const ratio)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_frequency_ratio_get(const mesa_inst_t inst, const uint8_t clock_output, uint32_t *const freq_khz, uint32_t *const par_freq_khz, mesa_clock_ratio_t *const ratio)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_ratio_t) == sizeof(mesa_clock_ratio_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_output_frequency_ratio_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, freq_khz, par_freq_khz, (vtss_clock_ratio_t *)ratio /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_frequency_ratio_get(const mesa_inst_t inst, const uint8_t clock_output, uint32_t *const freq_khz, uint32_t *const par_freq_khz, mesa_clock_ratio_t *const ratio)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_level_set(const mesa_inst_t inst, const uint8_t clock_output, const uint16_t level_mv)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_level_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, level_mv); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_level_set(const mesa_inst_t inst, const uint8_t clock_output, const uint16_t level_mv)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_level_get(const mesa_inst_t inst, const uint8_t clock_output, uint16_t *const level_mv)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_output_level_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, level_mv); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_level_get(const mesa_inst_t inst, const uint8_t clock_output, uint16_t *const level_mv)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_selector_set(const mesa_inst_t inst, const uint8_t clock_output, const mesa_clock_input_selector_t *const input)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_input_selector_t) == sizeof(mesa_clock_input_selector_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_output_selector_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, (const vtss_clock_input_selector_t *)input /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_selector_set(const mesa_inst_t inst, const uint8_t clock_output, const mesa_clock_input_selector_t *const input)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_output_selector_get(const mesa_inst_t inst, const uint8_t clock_output, mesa_clock_input_selector_t *const input)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_input_selector_t) == sizeof(mesa_clock_input_selector_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_output_selector_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_output, (vtss_clock_input_selector_t *)input /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_output_selector_get(const mesa_inst_t inst, const uint8_t clock_output, mesa_clock_input_selector_t *const input)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_alarm_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_input_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_input_conf_t) == sizeof(mesa_clock_input_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_alarm_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (const vtss_clock_input_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_alarm_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_input_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_alarm_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_input_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_input_conf_t) == sizeof(mesa_clock_input_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_alarm_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (vtss_clock_input_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_alarm_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_input_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_cfm_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_cfm_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_cfm_conf_t) == sizeof(mesa_clock_cfm_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_cfm_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (const vtss_clock_cfm_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_cfm_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_cfm_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_cfm_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_cfm_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_cfm_conf_t) == sizeof(mesa_clock_cfm_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_cfm_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (vtss_clock_cfm_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_cfm_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_cfm_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_pfm_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_pfm_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_pfm_conf_t) == sizeof(mesa_clock_pfm_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_pfm_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (const vtss_clock_pfm_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_pfm_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_pfm_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_pfm_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_pfm_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_pfm_conf_t) == sizeof(mesa_clock_pfm_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_pfm_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (vtss_clock_pfm_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_pfm_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_pfm_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_gst_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_gst_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_gst_conf_t) == sizeof(mesa_clock_gst_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_gst_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (const vtss_clock_gst_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_gst_conf_set(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_gst_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_gst_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_gst_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_gst_conf_t) == sizeof(mesa_clock_gst_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_gst_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (vtss_clock_gst_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_gst_conf_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_gst_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_selector_state_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_selector_state_t *const selector_state, uint8_t *const clock_input)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_selector_state_t) == sizeof(mesa_clock_selector_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_selector_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (vtss_clock_selector_state_t *)selector_state /* ag.rb:1867 */, clock_input); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_selector_state_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_selector_state_t *const selector_state, uint8_t *const clock_input)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_dpll_state_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_dpll_state_t *const pll_state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_dpll_state_t) == sizeof(mesa_clock_dpll_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_dpll_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, (vtss_clock_dpll_state_t *)pll_state /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_dpll_state_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_dpll_state_t *const pll_state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_ho_stack_frequency_offset_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, int64_t *const offset)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_ho_stack_frequency_offset_get((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, offset); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_ho_stack_frequency_offset_get(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, int64_t *const offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_state_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_input_state_t *const input_state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_clock_input_state_t) == sizeof(mesa_clock_input_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_clock_input_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, (vtss_clock_input_state_t *)input_state /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_state_get(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_input_state_t *const input_state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_event_poll(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_input_event_type_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_input_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_event_poll(const mesa_inst_t inst, const uint8_t clock_input, mesa_clock_input_event_type_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_input_event_enable(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_input_event_type_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_input_event_enable((const vtss_inst_t)inst /* ag.rb:1870 */, clock_input, ev_mask, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_input_event_enable(const mesa_inst_t inst, const uint8_t clock_input, const mesa_clock_input_event_type_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_dpll_event_poll(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_dpll_event_type_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_dpll_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_dpll_event_poll(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, mesa_clock_dpll_event_type_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_CLOCK)
mesa_rc mesa_clock_dpll_event_enable(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_dpll_event_type_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_clock_dpll_event_enable((const vtss_inst_t)inst /* ag.rb:1870 */, dpll, ev_mask, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_clock_dpll_event_enable(const mesa_inst_t inst, const mesa_clock_dpll_inst_t dpll, const mesa_clock_dpll_event_type_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_CLOCK) /* ag.rb:1989 */

mesa_rc mesa_inst_get(const mesa_target_type_t target, mesa_inst_create_t *const create)
{ /* ag.rb:1845 */
    vtss_target_type_t __target;
    vtss_inst_create_t __create;

    __RC(mesa_conv_mesa_target_type_t_to_vtss_target_type_t(&target, &__target)) /* ag.rb:1916 */; /* ag.rb:1965 */

    mesa_rc rc = vtss_inst_get(__target, &__create); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_inst_create_t_to_mesa_inst_create_t(&__create, create)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}

mesa_rc mesa_inst_create(const mesa_inst_create_t *const create, mesa_inst_t *const inst)
{ /* ag.rb:1845 */
    vtss_inst_create_t __create;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_inst_create_t_to_vtss_inst_create_t(create, &__create)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_inst_create(&__create, (vtss_inst_t *)inst /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

mesa_rc mesa_inst_destroy(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_inst_destroy((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}

mesa_rc mesa_init_conf_get(const mesa_inst_t inst, mesa_init_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_init_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_init_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_init_conf_t_to_mesa_init_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}

mesa_rc mesa_init_conf_set(const mesa_inst_t inst, const mesa_init_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_init_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_init_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_init_conf_t_to_vtss_init_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_init_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1976*/ 
}

mesa_rc mesa_register_access_mode_set(const mesa_inst_t inst, mesa_bool_t spi_bus)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_register_access_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, spi_bus); /* ag.rb:1976*/ 
}

mesa_rc mesa_register_access_mode_get(const mesa_inst_t inst, mesa_bool_t * spi_bus)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_register_access_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, spi_bus); /* ag.rb:1976*/ 
}

mesa_rc mesa_spi_slave_init(const mesa_spi_slave_init_t *const conf)
{ /* ag.rb:1845 */
    vtss_spi_slave_init_t __conf;
    __RC(mesa_conv_mesa_spi_slave_init_t_to_vtss_spi_slave_init_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_spi_slave_init(&__conf); /* ag.rb:1976*/ 
}

#if defined(VTSS_FEATURE_WARM_START)
mesa_rc mesa_restart_conf_end(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_restart_conf_end((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_restart_conf_end(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WARM_START) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WARM_START)
mesa_rc mesa_restart_status_get(const mesa_inst_t inst, mesa_restart_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_restart_status_t) == sizeof(mesa_restart_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_restart_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_restart_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_restart_status_get(const mesa_inst_t inst, mesa_restart_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WARM_START) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WARM_START)
mesa_rc mesa_restart_conf_get(const mesa_inst_t inst, mesa_restart_t *const restart)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_restart_t) == sizeof(mesa_restart_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_restart_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_restart_t *)restart /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_restart_conf_get(const mesa_inst_t inst, mesa_restart_t *const restart)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WARM_START) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WARM_START)
mesa_rc mesa_restart_conf_set(const mesa_inst_t inst, const mesa_restart_t restart)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_restart_t) == sizeof(mesa_restart_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_restart_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_restart_t *)&restart) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_restart_conf_set(const mesa_inst_t inst, const mesa_restart_t restart)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WARM_START) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_add(const mesa_inst_t inst, const mesa_mac_table_entry_t *const entry)
{ /* ag.rb:1845 */
    vtss_mac_table_entry_t __entry;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_mac_table_entry_t_to_vtss_mac_table_entry_t(entry, &__entry)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_mac_table_add((const vtss_inst_t)inst /* ag.rb:1870 */, &__entry); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_add(const mesa_inst_t inst, const mesa_mac_table_entry_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_del(const mesa_inst_t inst, const mesa_vid_mac_t *const vid_mac)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vid_mac_t) == sizeof(mesa_vid_mac_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_mac_table_del((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_vid_mac_t *)vid_mac /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_del(const mesa_inst_t inst, const mesa_vid_mac_t *const vid_mac)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_get(const mesa_inst_t inst, const mesa_vid_mac_t *const vid_mac, mesa_mac_table_entry_t *const entry)
{ /* ag.rb:1845 */
    vtss_mac_table_entry_t __entry;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vid_mac_t) == sizeof(mesa_vid_mac_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_mac_table_get((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_vid_mac_t *)vid_mac /* ag.rb:1867 */, &__entry); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_mac_table_entry_t_to_mesa_mac_table_entry_t(&__entry, entry)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_mac_table_get(const mesa_inst_t inst, const mesa_vid_mac_t *const vid_mac, mesa_mac_table_entry_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_get_next(const mesa_inst_t inst, const mesa_vid_mac_t *const vid_mac, mesa_mac_table_entry_t *const entry)
{ /* ag.rb:1845 */
    vtss_mac_table_entry_t __entry;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vid_mac_t) == sizeof(mesa_vid_mac_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_mac_table_get_next((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_vid_mac_t *)vid_mac /* ag.rb:1867 */, &__entry); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_mac_table_entry_t_to_mesa_mac_table_entry_t(&__entry, entry)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_mac_table_get_next(const mesa_inst_t inst, const mesa_vid_mac_t *const vid_mac, mesa_mac_table_entry_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_age_time_get(const mesa_inst_t inst, mesa_mac_table_age_time_t *const age_time)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_age_time_get((const vtss_inst_t)inst /* ag.rb:1870 */, age_time); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_age_time_get(const mesa_inst_t inst, mesa_mac_table_age_time_t *const age_time)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_age_time_set(const mesa_inst_t inst, const mesa_mac_table_age_time_t age_time)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_age_time_set((const vtss_inst_t)inst /* ag.rb:1870 */, age_time); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_age_time_set(const mesa_inst_t inst, const mesa_mac_table_age_time_t age_time)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_age(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_age((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_age(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_vlan_age(const mesa_inst_t inst, const mesa_vid_t vid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_vlan_age((const vtss_inst_t)inst /* ag.rb:1870 */, vid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_vlan_age(const mesa_inst_t inst, const mesa_vid_t vid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_flush(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_flush((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_flush(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_port_flush(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_port_flush((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_port_flush(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_vlan_flush(const mesa_inst_t inst, const mesa_vid_t vid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_vlan_flush((const vtss_inst_t)inst /* ag.rb:1870 */, vid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_vlan_flush(const mesa_inst_t inst, const mesa_vid_t vid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_vlan_port_flush(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vid_t vid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_table_vlan_port_flush((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, vid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_vlan_port_flush(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vid_t vid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mac_table_status_get(const mesa_inst_t inst, mesa_mac_table_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_mac_table_status_t) == sizeof(mesa_mac_table_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_mac_table_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_mac_table_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_table_status_get(const mesa_inst_t inst, mesa_mac_table_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_learn_port_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_learn_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_learn_mode_t) == sizeof(mesa_learn_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_learn_port_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_learn_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_learn_port_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_learn_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_learn_port_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_learn_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_learn_mode_t) == sizeof(mesa_learn_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_learn_port_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_learn_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_learn_port_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_learn_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_port_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, state); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_port_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_state_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, state); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_stp_port_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_stp_state_t *const state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_stp_state_t) == sizeof(mesa_stp_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_stp_port_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_stp_state_t *)state /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_stp_port_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_stp_state_t *const state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_stp_port_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_stp_state_t state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_stp_state_t) == sizeof(mesa_stp_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_stp_port_state_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_stp_state_t *)&state) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_stp_port_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_stp_state_t state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mstp_vlan_msti_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_msti_t *const msti)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mstp_vlan_msti_get((const vtss_inst_t)inst /* ag.rb:1870 */, vid, msti); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mstp_vlan_msti_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_msti_t *const msti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mstp_vlan_msti_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_msti_t msti)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mstp_vlan_msti_set((const vtss_inst_t)inst /* ag.rb:1870 */, vid, msti); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mstp_vlan_msti_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_msti_t msti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mstp_port_msti_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_msti_t msti, mesa_stp_state_t *const state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_stp_state_t) == sizeof(mesa_stp_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_mstp_port_msti_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, msti, (vtss_stp_state_t *)state /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mstp_port_msti_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_msti_t msti, mesa_stp_state_t *const state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mstp_port_msti_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_msti_t msti, const mesa_stp_state_t state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_stp_state_t) == sizeof(mesa_stp_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_mstp_port_msti_state_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, msti, *((const vtss_stp_state_t *)&state) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mstp_port_msti_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_msti_t msti, const mesa_stp_state_t state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_conf_get(const mesa_inst_t inst, mesa_vlan_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vlan_conf_t) == sizeof(mesa_vlan_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_vlan_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_vlan_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vlan_conf_get(const mesa_inst_t inst, mesa_vlan_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_conf_set(const mesa_inst_t inst, const mesa_vlan_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vlan_conf_t) == sizeof(mesa_vlan_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_vlan_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_vlan_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vlan_conf_set(const mesa_inst_t inst, const mesa_vlan_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_vlan_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_vlan_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_vlan_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_vlan_port_conf_t_to_mesa_vlan_port_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_vlan_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_vlan_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vlan_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_vlan_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_vlan_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_vlan_port_conf_t_to_vtss_vlan_port_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_vlan_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vlan_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vlan_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_port_members_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_vlan_port_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, vid, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_vlan_port_members_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_port_members_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_vlan_port_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, vid, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vlan_port_members_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_vid_conf_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_vlan_vid_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_vlan_vid_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_vlan_vid_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, vid, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_vlan_vid_conf_t_to_mesa_vlan_vid_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_vlan_vid_conf_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_vlan_vid_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vlan_vid_conf_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_vlan_vid_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_vlan_vid_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_vlan_vid_conf_t_to_vtss_vlan_vid_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_vlan_vid_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, vid, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vlan_vid_conf_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_vlan_vid_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
mesa_rc mesa_vlan_counters_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_vlan_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vlan_counters_t) == sizeof(mesa_vlan_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_vlan_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, vid, (vtss_vlan_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vlan_counters_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_vlan_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VLAN_COUNTERS) /* ag.rb:1989 */
#else
mesa_rc mesa_vlan_counters_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_vlan_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
mesa_rc mesa_vlan_counters_clear(const mesa_inst_t inst, const mesa_vid_t vid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_vlan_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, vid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vlan_counters_clear(const mesa_inst_t inst, const mesa_vid_t vid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VLAN_COUNTERS) /* ag.rb:1989 */
#else
mesa_rc mesa_vlan_counters_clear(const mesa_inst_t inst, const mesa_vid_t vid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vcl_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_vcl_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vcl_port_conf_t) == sizeof(mesa_vcl_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_vcl_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_vcl_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vcl_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_vcl_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vcl_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vcl_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vcl_port_conf_t) == sizeof(mesa_vcl_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_vcl_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_vcl_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vcl_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vcl_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vce_init(const mesa_inst_t inst, const mesa_vce_type_t type, mesa_vce_t *const vce)
{ /* ag.rb:1845 */
    vtss_vce_t __vce;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vce_type_t) == sizeof(mesa_vce_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_vce_init((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_vce_type_t *)&type) /* ag.rb:1872 */, &__vce); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_vce_t_to_mesa_vce_t(&__vce, vce)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_vce_init(const mesa_inst_t inst, const mesa_vce_type_t type, mesa_vce_t *const vce)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vce_add(const mesa_inst_t inst, const mesa_vce_id_t vce_id, const mesa_vce_t *const vce)
{ /* ag.rb:1845 */
    vtss_vce_t __vce;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_vce_t_to_vtss_vce_t(vce, &__vce)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_vce_add((const vtss_inst_t)inst /* ag.rb:1870 */, vce_id, &__vce); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vce_add(const mesa_inst_t inst, const mesa_vce_id_t vce_id, const mesa_vce_t *const vce)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_vce_del(const mesa_inst_t inst, const mesa_vce_id_t vce_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_vce_del((const vtss_inst_t)inst /* ag.rb:1870 */, vce_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vce_del(const mesa_inst_t inst, const mesa_vce_id_t vce_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_ingress_cnt_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_ingress_cnt_id_t *const id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ingress_cnt_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, cnt, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ingress_cnt_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_ingress_cnt_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_ingress_cnt_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_ingress_cnt_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_ingress_cnt_free(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ingress_cnt_free((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ingress_cnt_free(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_ingress_cnt_free(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_ingress_cnt_get(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id, const mesa_cosid_t cosid, mesa_ingress_counters_t * counters)
{ /* ag.rb:1845 */
    vtss_ingress_counters_t __counters;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ingress_cnt_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, cosid, &__counters); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_ingress_counters_t_to_mesa_ingress_counters_t(&__counters, counters)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ingress_cnt_get(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id, const mesa_cosid_t cosid, mesa_ingress_counters_t * counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_ingress_cnt_get(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id, const mesa_cosid_t cosid, mesa_ingress_counters_t * counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_ingress_cnt_clear(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id, const mesa_cosid_t cosid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ingress_cnt_clear((const vtss_inst_t)inst /* ag.rb:1870 */, id, cosid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ingress_cnt_clear(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id, const mesa_cosid_t cosid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_ingress_cnt_clear(const mesa_inst_t inst, const mesa_ingress_cnt_id_t id, const mesa_cosid_t cosid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XDLB)
mesa_rc mesa_dlb_policer_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_dlb_policer_id_t *const id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_dlb_policer_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, cnt, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_dlb_policer_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_dlb_policer_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XDLB) /* ag.rb:1989 */
#else
mesa_rc mesa_dlb_policer_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_dlb_policer_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XDLB)
mesa_rc mesa_dlb_policer_free(const mesa_inst_t inst, const mesa_dlb_policer_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_dlb_policer_free((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_dlb_policer_free(const mesa_inst_t inst, const mesa_dlb_policer_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XDLB) /* ag.rb:1989 */
#else
mesa_rc mesa_dlb_policer_free(const mesa_inst_t inst, const mesa_dlb_policer_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XDLB)
mesa_rc mesa_dlb_policer_conf_get(const mesa_inst_t inst, const mesa_dlb_policer_id_t id, const mesa_cosid_t cosid, mesa_dlb_policer_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_dlb_policer_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_dlb_policer_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, cosid, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_dlb_policer_conf_t_to_mesa_dlb_policer_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_dlb_policer_conf_get(const mesa_inst_t inst, const mesa_dlb_policer_id_t id, const mesa_cosid_t cosid, mesa_dlb_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XDLB) /* ag.rb:1989 */
#else
mesa_rc mesa_dlb_policer_conf_get(const mesa_inst_t inst, const mesa_dlb_policer_id_t id, const mesa_cosid_t cosid, mesa_dlb_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XDLB)
mesa_rc mesa_dlb_policer_conf_set(const mesa_inst_t inst, const mesa_dlb_policer_id_t id, const mesa_cosid_t cosid, const mesa_dlb_policer_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_dlb_policer_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_dlb_policer_conf_t_to_vtss_dlb_policer_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_dlb_policer_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, cosid, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_dlb_policer_conf_set(const mesa_inst_t inst, const mesa_dlb_policer_id_t id, const mesa_cosid_t cosid, const mesa_dlb_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XDLB) /* ag.rb:1989 */
#else
mesa_rc mesa_dlb_policer_conf_set(const mesa_inst_t inst, const mesa_dlb_policer_id_t id, const mesa_cosid_t cosid, const mesa_dlb_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_iflow_alloc(const mesa_inst_t inst, mesa_iflow_id_t *const id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_iflow_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_iflow_alloc(const mesa_inst_t inst, mesa_iflow_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_iflow_alloc(const mesa_inst_t inst, mesa_iflow_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_iflow_free(const mesa_inst_t inst, const mesa_iflow_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_iflow_free((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_iflow_free(const mesa_inst_t inst, const mesa_iflow_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_iflow_free(const mesa_inst_t inst, const mesa_iflow_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_iflow_conf_get(const mesa_inst_t inst, const mesa_iflow_id_t id, mesa_iflow_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_iflow_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_iflow_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_iflow_conf_t_to_mesa_iflow_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_iflow_conf_get(const mesa_inst_t inst, const mesa_iflow_id_t id, mesa_iflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_iflow_conf_get(const mesa_inst_t inst, const mesa_iflow_id_t id, mesa_iflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_iflow_conf_set(const mesa_inst_t inst, const mesa_iflow_id_t id, const mesa_iflow_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_iflow_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_iflow_conf_t_to_vtss_iflow_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_iflow_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_iflow_conf_set(const mesa_inst_t inst, const mesa_iflow_id_t id, const mesa_iflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_iflow_conf_set(const mesa_inst_t inst, const mesa_iflow_id_t id, const mesa_iflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_tce_init(const mesa_inst_t inst, mesa_tce_t *const tce)
{ /* ag.rb:1845 */
    vtss_tce_t __tce;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_tce_init((const vtss_inst_t)inst /* ag.rb:1870 */, &__tce); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_tce_t_to_mesa_tce_t(&__tce, tce)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_tce_init(const mesa_inst_t inst, mesa_tce_t *const tce)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_tce_add(const mesa_inst_t inst, const mesa_tce_id_t tce_id, const mesa_tce_t *const tce)
{ /* ag.rb:1845 */
    vtss_tce_t __tce;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_tce_t_to_vtss_tce_t(tce, &__tce)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_tce_add((const vtss_inst_t)inst /* ag.rb:1870 */, tce_id, &__tce); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_tce_add(const mesa_inst_t inst, const mesa_tce_id_t tce_id, const mesa_tce_t *const tce)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_tce_del(const mesa_inst_t inst, const mesa_tce_id_t tce_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_tce_del((const vtss_inst_t)inst /* ag.rb:1870 */, tce_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_tce_del(const mesa_inst_t inst, const mesa_tce_id_t tce_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_egress_cnt_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_egress_cnt_id_t *const id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_egress_cnt_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, cnt, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_egress_cnt_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_egress_cnt_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_egress_cnt_alloc(const mesa_inst_t inst, const mesa_class_cnt_t cnt, mesa_egress_cnt_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_egress_cnt_free(const mesa_inst_t inst, const mesa_egress_cnt_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_egress_cnt_free((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_egress_cnt_free(const mesa_inst_t inst, const mesa_egress_cnt_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_egress_cnt_free(const mesa_inst_t inst, const mesa_egress_cnt_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_egress_cnt_get(const mesa_inst_t inst, const mesa_egress_cnt_id_t id, const mesa_cosid_t cosid, mesa_egress_counters_t * counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_egress_counters_t) == sizeof(mesa_egress_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_egress_cnt_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, cosid, (vtss_egress_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_egress_cnt_get(const mesa_inst_t inst, const mesa_egress_cnt_id_t id, const mesa_cosid_t cosid, mesa_egress_counters_t * counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_egress_cnt_get(const mesa_inst_t inst, const mesa_egress_cnt_id_t id, const mesa_cosid_t cosid, mesa_egress_counters_t * counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XSTAT)
mesa_rc mesa_egress_cnt_clear(const mesa_inst_t inst, const mesa_egress_cnt_id_t id, const mesa_cosid_t cosid)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_egress_cnt_clear((const vtss_inst_t)inst /* ag.rb:1870 */, id, cosid); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_egress_cnt_clear(const mesa_inst_t inst, const mesa_egress_cnt_id_t id, const mesa_cosid_t cosid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XSTAT) /* ag.rb:1989 */
#else
mesa_rc mesa_egress_cnt_clear(const mesa_inst_t inst, const mesa_egress_cnt_id_t id, const mesa_cosid_t cosid)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_eflow_alloc(const mesa_inst_t inst, mesa_eflow_id_t *const id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_eflow_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eflow_alloc(const mesa_inst_t inst, mesa_eflow_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_eflow_alloc(const mesa_inst_t inst, mesa_eflow_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_eflow_free(const mesa_inst_t inst, const mesa_eflow_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_eflow_free((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eflow_free(const mesa_inst_t inst, const mesa_eflow_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_eflow_free(const mesa_inst_t inst, const mesa_eflow_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_eflow_conf_get(const mesa_inst_t inst, const mesa_eflow_id_t id, mesa_eflow_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_eflow_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_eflow_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_eflow_conf_t_to_mesa_eflow_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_eflow_conf_get(const mesa_inst_t inst, const mesa_eflow_id_t id, mesa_eflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_eflow_conf_get(const mesa_inst_t inst, const mesa_eflow_id_t id, mesa_eflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_XFLOW)
mesa_rc mesa_eflow_conf_set(const mesa_inst_t inst, const mesa_eflow_id_t id, const mesa_eflow_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_eflow_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_eflow_conf_t_to_vtss_eflow_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_eflow_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eflow_conf_set(const mesa_inst_t inst, const mesa_eflow_id_t id, const mesa_eflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_XFLOW) /* ag.rb:1989 */
#else
mesa_rc mesa_eflow_conf_set(const mesa_inst_t inst, const mesa_eflow_id_t id, const mesa_eflow_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_ARCH_SERVAL)
mesa_rc mesa_vcap_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_vcap_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vcap_port_conf_t) == sizeof(mesa_vcap_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_vcap_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_vcap_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vcap_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_vcap_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) /* ag.rb:1989 */
#else
mesa_rc mesa_vcap_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_vcap_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_ARCH_SERVAL)
mesa_rc mesa_vcap_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vcap_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_vcap_port_conf_t) == sizeof(mesa_vcap_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_vcap_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_vcap_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vcap_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vcap_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) /* ag.rb:1989 */
#else
mesa_rc mesa_vcap_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_vcap_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_isolated_vlan_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_bool_t *const isolated)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_isolated_vlan_get((const vtss_inst_t)inst /* ag.rb:1870 */, vid, isolated); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_isolated_vlan_get(const mesa_inst_t inst, const mesa_vid_t vid, mesa_bool_t *const isolated)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_isolated_vlan_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_bool_t isolated)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_isolated_vlan_set((const vtss_inst_t)inst /* ag.rb:1870 */, vid, isolated); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_isolated_vlan_set(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_bool_t isolated)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_isolated_port_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_isolated_port_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_isolated_port_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_isolated_port_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_isolated_port_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_isolated_port_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_pvlan_port_members_get(const mesa_inst_t inst, const mesa_pvlan_no_t pvlan_no, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_pvlan_port_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, pvlan_no, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_pvlan_port_members_get(const mesa_inst_t inst, const mesa_pvlan_no_t pvlan_no, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_pvlan_port_members_set(const mesa_inst_t inst, const mesa_pvlan_no_t pvlan_no, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_pvlan_port_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, pvlan_no, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_pvlan_port_members_set(const mesa_inst_t inst, const mesa_pvlan_no_t pvlan_no, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_apvlan_port_members_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_apvlan_port_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_apvlan_port_members_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_apvlan_port_members_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_apvlan_port_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_apvlan_port_members_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_dgroup_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_dgroup_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_dgroup_port_conf_t) == sizeof(mesa_dgroup_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_dgroup_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_dgroup_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_dgroup_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_dgroup_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_dgroup_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_dgroup_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_dgroup_port_conf_t) == sizeof(mesa_dgroup_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_dgroup_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_dgroup_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_dgroup_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_dgroup_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_sflow_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_sflow_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_sflow_port_conf_t) == sizeof(mesa_sflow_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_sflow_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_sflow_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_sflow_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_sflow_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_sflow_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_sflow_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_sflow_port_conf_t) == sizeof(mesa_sflow_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_sflow_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_sflow_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_sflow_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_sflow_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_sflow_sampling_rate_convert(const mesa_inst_t inst, const mesa_bool_t power2, const uint32_t rate_in, uint32_t *const rate_out)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_sflow_sampling_rate_convert((const vtss_inst_t)inst /* ag.rb:1870 */, power2, rate_in, rate_out); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_sflow_sampling_rate_convert(const mesa_inst_t inst, const mesa_bool_t power2, const uint32_t rate_in, uint32_t *const rate_out)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_aggr_port_members_get(const mesa_inst_t inst, const mesa_aggr_no_t aggr_no, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_aggr_port_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, aggr_no, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_aggr_port_members_get(const mesa_inst_t inst, const mesa_aggr_no_t aggr_no, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_aggr_port_members_set(const mesa_inst_t inst, const mesa_aggr_no_t aggr_no, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_aggr_port_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, aggr_no, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_aggr_port_members_set(const mesa_inst_t inst, const mesa_aggr_no_t aggr_no, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_aggr_mode_get(const mesa_inst_t inst, mesa_aggr_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_aggr_mode_t) == sizeof(mesa_aggr_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_aggr_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_aggr_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_aggr_mode_get(const mesa_inst_t inst, mesa_aggr_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_aggr_mode_set(const mesa_inst_t inst, const mesa_aggr_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_aggr_mode_t) == sizeof(mesa_aggr_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_aggr_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_aggr_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_aggr_mode_set(const mesa_inst_t inst, const mesa_aggr_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_conf_get(const mesa_inst_t inst, mesa_mirror_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_mirror_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_mirror_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_mirror_conf_t_to_mesa_mirror_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_mirror_conf_get(const mesa_inst_t inst, mesa_mirror_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_conf_set(const mesa_inst_t inst, const mesa_mirror_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_mirror_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_mirror_conf_t_to_vtss_mirror_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_mirror_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_conf_set(const mesa_inst_t inst, const mesa_mirror_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_monitor_port_get(const mesa_inst_t inst, mesa_port_no_t *const port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mirror_monitor_port_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_monitor_port_get(const mesa_inst_t inst, mesa_port_no_t *const port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_monitor_port_set(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mirror_monitor_port_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_monitor_port_set(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_ingress_ports_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_mirror_ingress_ports_get((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_mirror_ingress_ports_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_ingress_ports_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_mirror_ingress_ports_set((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_ingress_ports_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_egress_ports_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_mirror_egress_ports_get((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_mirror_egress_ports_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_egress_ports_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_mirror_egress_ports_set((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_egress_ports_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_cpu_ingress_get(const mesa_inst_t inst, mesa_bool_t * member)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mirror_cpu_ingress_get((const vtss_inst_t)inst /* ag.rb:1870 */, member); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_cpu_ingress_get(const mesa_inst_t inst, mesa_bool_t * member)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_cpu_ingress_set(const mesa_inst_t inst, const mesa_bool_t member)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mirror_cpu_ingress_set((const vtss_inst_t)inst /* ag.rb:1870 */, member); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_cpu_ingress_set(const mesa_inst_t inst, const mesa_bool_t member)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_cpu_egress_get(const mesa_inst_t inst, mesa_bool_t * member)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mirror_cpu_egress_get((const vtss_inst_t)inst /* ag.rb:1870 */, member); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_cpu_egress_get(const mesa_inst_t inst, mesa_bool_t * member)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mirror_cpu_egress_set(const mesa_inst_t inst, const mesa_bool_t member)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mirror_cpu_egress_set((const vtss_inst_t)inst /* ag.rb:1870 */, member); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mirror_cpu_egress_set(const mesa_inst_t inst, const mesa_bool_t member)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_uc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_uc_flood_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_uc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_uc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_uc_flood_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_uc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_mc_flood_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_mc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_mc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_mc_flood_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_ipv4_mc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ipv4_mc_flood_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ipv4_mc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_ipv4_mc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_ipv4_mc_flood_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv4_mc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_IPV4_MC_SIP)
mesa_rc mesa_ipv4_mc_add(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ip_t sip, const mesa_ip_t dip, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_ipv4_mc_add((const vtss_inst_t)inst /* ag.rb:1870 */, vid, sip, dip, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv4_mc_add(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ip_t sip, const mesa_ip_t dip, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_IPV4_MC_SIP) /* ag.rb:1989 */
#else
mesa_rc mesa_ipv4_mc_add(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ip_t sip, const mesa_ip_t dip, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_IPV4_MC_SIP)
mesa_rc mesa_ipv4_mc_del(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ip_t sip, const mesa_ip_t dip)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ipv4_mc_del((const vtss_inst_t)inst /* ag.rb:1870 */, vid, sip, dip); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv4_mc_del(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ip_t sip, const mesa_ip_t dip)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_IPV4_MC_SIP) /* ag.rb:1989 */
#else
mesa_rc mesa_ipv4_mc_del(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ip_t sip, const mesa_ip_t dip)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_ipv6_mc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ipv6_mc_flood_members_get((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1970 */
    __RC(mesa_conv_uint8_t_to_mesa_port_list_t(__port_list, port_list)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ipv6_mc_flood_members_get(const mesa_inst_t inst, mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_ipv6_mc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_ipv6_mc_flood_members_set((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv6_mc_flood_members_set(const mesa_inst_t inst, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_ipv6_mc_ctrl_flood_get(const mesa_inst_t inst, mesa_bool_t *const scope)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ipv6_mc_ctrl_flood_get((const vtss_inst_t)inst /* ag.rb:1870 */, scope); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv6_mc_ctrl_flood_get(const mesa_inst_t inst, mesa_bool_t *const scope)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_ipv6_mc_ctrl_flood_set(const mesa_inst_t inst, const mesa_bool_t scope)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ipv6_mc_ctrl_flood_set((const vtss_inst_t)inst /* ag.rb:1870 */, scope); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv6_mc_ctrl_flood_set(const mesa_inst_t inst, const mesa_bool_t scope)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_IPV6_MC_SIP)
mesa_rc mesa_ipv6_mc_add(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ipv6_t sip, const mesa_ipv6_t dip, const mesa_port_list_t * port_list)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORT_ARRAY_SIZE];

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ipv6_t) == sizeof(mesa_ipv6_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ipv6_t) == sizeof(mesa_ipv6_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_ipv6_mc_add((const vtss_inst_t)inst /* ag.rb:1870 */, vid, *((const vtss_ipv6_t *)&sip) /* ag.rb:1872 */, *((const vtss_ipv6_t *)&dip) /* ag.rb:1872 */, __port_list); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv6_mc_add(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ipv6_t sip, const mesa_ipv6_t dip, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_IPV6_MC_SIP) /* ag.rb:1989 */
#else
mesa_rc mesa_ipv6_mc_add(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ipv6_t sip, const mesa_ipv6_t dip, const mesa_port_list_t * port_list)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
#if defined(VTSS_FEATURE_IPV6_MC_SIP)
mesa_rc mesa_ipv6_mc_del(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ipv6_t sip, const mesa_ipv6_t dip)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ipv6_t) == sizeof(mesa_ipv6_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ipv6_t) == sizeof(mesa_ipv6_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ipv6_mc_del((const vtss_inst_t)inst /* ag.rb:1870 */, vid, *((const vtss_ipv6_t *)&sip) /* ag.rb:1872 */, *((const vtss_ipv6_t *)&dip) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ipv6_mc_del(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ipv6_t sip, const mesa_ipv6_t dip)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_IPV6_MC_SIP) /* ag.rb:1989 */
#else
mesa_rc mesa_ipv6_mc_del(const mesa_inst_t inst, const mesa_vid_t vid, const mesa_ipv6_t sip, const mesa_ipv6_t dip)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_eps_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_eps_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_eps_port_conf_t) == sizeof(mesa_eps_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_eps_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_eps_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eps_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_eps_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_eps_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_eps_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_eps_port_conf_t) == sizeof(mesa_eps_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_eps_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_eps_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eps_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_eps_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_eps_port_selector_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_eps_selector_t *const selector)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_eps_selector_t) == sizeof(mesa_eps_selector_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_eps_port_selector_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_eps_selector_t *)selector /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eps_port_selector_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_eps_selector_t *const selector)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_eps_port_selector_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_eps_selector_t selector)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_eps_selector_t) == sizeof(mesa_eps_selector_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_eps_port_selector_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_eps_selector_t *)&selector) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eps_port_selector_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_eps_selector_t selector)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_erps_vlan_member_get(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_vid_t vid, mesa_bool_t *const member)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_erps_vlan_member_get((const vtss_inst_t)inst /* ag.rb:1870 */, erpi, vid, member); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_erps_vlan_member_get(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_vid_t vid, mesa_bool_t *const member)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_erps_vlan_member_set(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_vid_t vid, const mesa_bool_t member)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_erps_vlan_member_set((const vtss_inst_t)inst /* ag.rb:1870 */, erpi, vid, member); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_erps_vlan_member_set(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_vid_t vid, const mesa_bool_t member)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_erps_port_state_get(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_port_no_t port_no, mesa_erps_state_t *const state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_erps_state_t) == sizeof(mesa_erps_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_erps_port_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, erpi, port_no, (vtss_erps_state_t *)state /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_erps_port_state_get(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_port_no_t port_no, mesa_erps_state_t *const state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_erps_port_state_set(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_port_no_t port_no, const mesa_erps_state_t state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_erps_state_t) == sizeof(mesa_erps_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_erps_port_state_set((const vtss_inst_t)inst /* ag.rb:1870 */, erpi, port_no, *((const vtss_erps_state_t *)&state) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_erps_port_state_set(const mesa_inst_t inst, const mesa_erpi_t erpi, const mesa_port_no_t port_no, const mesa_erps_state_t state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_flush(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_l3_flush((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_flush(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_common_get(const mesa_inst_t inst, mesa_l3_common_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_common_conf_t) == sizeof(mesa_l3_common_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_common_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_l3_common_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_common_get(const mesa_inst_t inst, mesa_l3_common_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_common_set(const mesa_inst_t inst, const mesa_l3_common_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_common_conf_t) == sizeof(mesa_l3_common_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_common_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_l3_common_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_common_set(const mesa_inst_t inst, const mesa_l3_common_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_rleg_get_specific(const mesa_inst_t inst, mesa_vid_t vid, mesa_l3_rleg_conf_t * conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_rleg_conf_t) == sizeof(mesa_l3_rleg_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_rleg_get_specific((const vtss_inst_t)inst /* ag.rb:1870 */, vid, (vtss_l3_rleg_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_rleg_get_specific(const mesa_inst_t inst, mesa_vid_t vid, mesa_l3_rleg_conf_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_rleg_add(const mesa_inst_t inst, const mesa_l3_rleg_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_rleg_conf_t) == sizeof(mesa_l3_rleg_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_rleg_add((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_l3_rleg_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_rleg_add(const mesa_inst_t inst, const mesa_l3_rleg_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_rleg_update(const mesa_inst_t inst, const mesa_l3_rleg_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_rleg_conf_t) == sizeof(mesa_l3_rleg_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_rleg_update((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_l3_rleg_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_rleg_update(const mesa_inst_t inst, const mesa_l3_rleg_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_rleg_del(const mesa_inst_t inst, const mesa_vid_t vlan)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_l3_rleg_del((const vtss_inst_t)inst /* ag.rb:1870 */, vlan); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_rleg_del(const mesa_inst_t inst, const mesa_vid_t vlan)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_route_add(const mesa_inst_t inst, const mesa_routing_entry_t *const entry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_entry_t) == sizeof(mesa_routing_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_route_add((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_routing_entry_t *)entry /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_route_add(const mesa_inst_t inst, const mesa_routing_entry_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_route_bulk_add(const mesa_inst_t inst, const uint32_t cnt, const mesa_routing_entry_t * entry, uint32_t *const rt_added)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_entry_t) == sizeof(mesa_routing_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_route_bulk_add((const vtss_inst_t)inst /* ag.rb:1870 */, cnt, (const vtss_routing_entry_t *)entry /* ag.rb:1867 */, rt_added); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_route_bulk_add(const mesa_inst_t inst, const uint32_t cnt, const mesa_routing_entry_t * entry, uint32_t *const rt_added)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_route_del(const mesa_inst_t inst, const mesa_routing_entry_t *const entry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_entry_t) == sizeof(mesa_routing_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_route_del((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_routing_entry_t *)entry /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_route_del(const mesa_inst_t inst, const mesa_routing_entry_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_route_bulk_del(const mesa_inst_t inst, const uint32_t cnt, const mesa_routing_entry_t * entry, uint32_t *const rt_deleted)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_entry_t) == sizeof(mesa_routing_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_route_bulk_del((const vtss_inst_t)inst /* ag.rb:1870 */, cnt, (const vtss_routing_entry_t *)entry /* ag.rb:1867 */, rt_deleted); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_route_bulk_del(const mesa_inst_t inst, const uint32_t cnt, const mesa_routing_entry_t * entry, uint32_t *const rt_deleted)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_neighbour_add(const mesa_inst_t inst, const mesa_l3_neighbour_t *const entry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_neighbour_t) == sizeof(mesa_l3_neighbour_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_neighbour_add((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_l3_neighbour_t *)entry /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_neighbour_add(const mesa_inst_t inst, const mesa_l3_neighbour_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_neighbour_del(const mesa_inst_t inst, const mesa_l3_neighbour_t *const entry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_neighbour_t) == sizeof(mesa_l3_neighbour_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_neighbour_del((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_l3_neighbour_t *)entry /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_neighbour_del(const mesa_inst_t inst, const mesa_l3_neighbour_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_mc_route_add(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_mc_entry_t) == sizeof(mesa_routing_mc_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_mc_route_add((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_routing_mc_entry_t *)entry /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_mc_route_add(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_mc_route_del(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_mc_entry_t) == sizeof(mesa_routing_mc_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_mc_route_del((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_routing_mc_entry_t *)entry /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_mc_route_del(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_mc_route_rleg_add(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry, const mesa_vid_t dest_rleg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_mc_entry_t) == sizeof(mesa_routing_mc_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_mc_route_rleg_add((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_routing_mc_entry_t *)entry /* ag.rb:1867 */, dest_rleg); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_mc_route_rleg_add(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry, const mesa_vid_t dest_rleg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_mc_route_rleg_del(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry, const mesa_vid_t dest_rleg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_mc_entry_t) == sizeof(mesa_routing_mc_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_mc_route_rleg_del((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_routing_mc_entry_t *)entry /* ag.rb:1867 */, dest_rleg); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_mc_route_rleg_del(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry, const mesa_vid_t dest_rleg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_mc_route_active_get(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry, mesa_bool_t *const active)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_routing_mc_entry_t) == sizeof(mesa_routing_mc_entry_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_mc_route_active_get((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_routing_mc_entry_t *)entry /* ag.rb:1867 */, active); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_mc_route_active_get(const mesa_inst_t inst, const mesa_routing_mc_entry_t *const entry, mesa_bool_t *const active)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_counters_reset(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_l3_counters_reset((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_counters_reset(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_counters_system_get(const mesa_inst_t inst, mesa_l3_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_counters_t) == sizeof(mesa_l3_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_counters_system_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_l3_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_counters_system_get(const mesa_inst_t inst, mesa_l3_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_counters_rleg_get(const mesa_inst_t inst, const mesa_vid_t vlan, mesa_l3_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_l3_counters_t) == sizeof(mesa_l3_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_l3_counters_rleg_get((const vtss_inst_t)inst /* ag.rb:1870 */, vlan, (vtss_l3_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_counters_rleg_get(const mesa_inst_t inst, const mesa_vid_t vlan, mesa_l3_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER3)
mesa_rc mesa_l3_counters_rleg_clear(const mesa_inst_t inst, const mesa_vid_t vlan)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_l3_counters_rleg_clear((const vtss_inst_t)inst /* ag.rb:1870 */, vlan); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_l3_counters_rleg_clear(const mesa_inst_t inst, const mesa_vid_t vlan)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER3) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_init_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_init_t *const init)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_init_t) == sizeof(mesa_macsec_init_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_init_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_macsec_init_t *)init /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_init_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_init_t *const init)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_init_t *const init)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_init_t) == sizeof(mesa_macsec_init_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_init_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_init_t *)init /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_init_t *const init)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_secy_conf_t) == sizeof(mesa_macsec_secy_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_add((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_secy_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_conf_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_secy_conf_t) == sizeof(mesa_macsec_secy_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_update((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_secy_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_conf_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_secy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_secy_conf_t) == sizeof(mesa_macsec_secy_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_secy_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_conf_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_conf_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_conf_del((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_conf_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_controlled_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_controlled_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_controlled_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_controlled_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_bool_t *const enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_controlled_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_controlled_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_bool_t *const enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_port_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_secy_port_status_t) == sizeof(mesa_macsec_secy_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_port_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_secy_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_port_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_port_get_next(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_port_t *const search_macsec_port, mesa_macsec_port_t *const found_macsec_port)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_port_get_next((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_macsec_port_t *)search_macsec_port /* ag.rb:1867 */, (vtss_macsec_port_t *)found_macsec_port /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_port_get_next(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_port_t *const search_macsec_port, mesa_macsec_port_t *const found_macsec_port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_add((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sc_add(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const mesa_macsec_rx_sc_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_rx_sc_conf_t) == sizeof(mesa_macsec_rx_sc_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_update((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, (const vtss_macsec_rx_sc_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const mesa_macsec_rx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_rx_sc_conf_t) == sizeof(mesa_macsec_rx_sc_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_get_conf((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, (vtss_macsec_rx_sc_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_get_next(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const search_sci, mesa_macsec_sci_t *const found_sci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_get_next((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)search_sci /* ag.rb:1867 */, (vtss_macsec_sci_t *)found_sci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sc_get_next(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const search_sci, mesa_macsec_sci_t *const found_sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_del((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_rx_sc_status_t) == sizeof(mesa_macsec_rx_sc_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, (vtss_macsec_rx_sc_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_set(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sc_set(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tx_sc_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tx_sc_conf_t) == sizeof(mesa_macsec_tx_sc_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_update((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_tx_sc_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sc_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tx_sc_conf_t) == sizeof(mesa_macsec_tx_sc_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_get_conf((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_tx_sc_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sc_get_conf(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_del((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sc_del(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tx_sc_status_t) == sizeof(mesa_macsec_tx_sc_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_tx_sc_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sc_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn, const mesa_macsec_sak_t *const sak)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, lowest_pn, (const vtss_macsec_sak_t *)sak /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn, const mesa_macsec_sak_t *const sak)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, uint32_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, lowest_pn, (vtss_macsec_sak_t *)sak /* ag.rb:1867 */, active); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, uint32_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_activate((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_disable((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_del((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_lowest_pn_update((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, lowest_pn); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const uint32_t lowest_pn)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_rx_sa_status_t) == sizeof(mesa_macsec_rx_sa_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, (vtss_macsec_rx_sa_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_seca_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, *((const vtss_macsec_pkt_num_t *)&lowest_pn) /* ag.rb:1872 */, (const vtss_macsec_sak_t *)sak /* ag.rb:1867 */, (const vtss_macsec_ssci_t *)ssci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_pkt_num_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_seca_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, (vtss_macsec_pkt_num_t *)lowest_pn /* ag.rb:1867 */, (vtss_macsec_sak_t *)sak /* ag.rb:1867 */, active, (vtss_macsec_ssci_t *)ssci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_pkt_num_t *const lowest_pn, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_seca_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_seca_lowest_pn_update((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, *((const vtss_macsec_pkt_num_t *)&lowest_pn) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_seca_lowest_pn_update(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, const mesa_macsec_pkt_num_t lowest_pn)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const uint32_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an, next_pn, confidentiality, (const vtss_macsec_sak_t *)sak /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sa_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const uint32_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, uint32_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an, next_pn, confidentiality, (vtss_macsec_sak_t *)sak /* ag.rb:1867 */, active); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sa_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, uint32_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_activate((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sa_activate(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_disable((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sa_disable(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_del((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sa_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tx_sa_status_t) == sizeof(mesa_macsec_tx_sa_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an, (vtss_macsec_tx_sa_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sa_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const mesa_macsec_pkt_num_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_seca_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an, *((const vtss_macsec_pkt_num_t *)&next_pn) /* ag.rb:1872 */, confidentiality, (const vtss_macsec_sak_t *)sak /* ag.rb:1867 */, (const vtss_macsec_ssci_t *)ssci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_seca_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, const mesa_macsec_pkt_num_t next_pn, const mesa_bool_t confidentiality, const mesa_macsec_sak_t *const sak, const mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_pkt_num_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_pkt_num_t) == sizeof(mesa_macsec_pkt_num_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sak_t) == sizeof(mesa_macsec_sak_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_ssci_t) == sizeof(mesa_macsec_ssci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_seca_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an, (vtss_macsec_pkt_num_t *)next_pn /* ag.rb:1867 */, confidentiality, (vtss_macsec_sak_t *)sak /* ag.rb:1867 */, active, (vtss_macsec_ssci_t *)ssci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_seca_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_pkt_num_t *const next_pn, mesa_bool_t *const confidentiality, mesa_macsec_sak_t *const sak, mesa_bool_t *const active, mesa_macsec_ssci_t *const ssci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_controlled_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_secy_port_counters_t) == sizeof(mesa_macsec_secy_port_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_controlled_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_secy_port_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_controlled_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_port_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_uncontrolled_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_uncontrolled_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_uncontrolled_counters_t) == sizeof(mesa_macsec_uncontrolled_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_uncontrolled_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_uncontrolled_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_uncontrolled_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_uncontrolled_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_common_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_common_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_common_counters_t) == sizeof(mesa_macsec_common_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_common_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_common_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_common_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_common_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_cap_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_secy_cap_t *const cap)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_secy_cap_t) == sizeof(mesa_macsec_secy_cap_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_cap_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_secy_cap_t *)cap /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_cap_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_secy_cap_t *const cap)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_secy_counters_t) == sizeof(mesa_macsec_secy_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_secy_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_secy_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_counters_update(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_counters_update((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_counters_update(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_rx_sc_counters_t) == sizeof(mesa_macsec_rx_sc_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sc_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, (vtss_macsec_rx_sc_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, mesa_macsec_rx_sc_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tx_sc_counters_t) == sizeof(mesa_macsec_tx_sc_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sc_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_tx_sc_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sc_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tx_sc_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_tx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tx_sa_counters_t) == sizeof(mesa_macsec_tx_sa_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_tx_sa_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an, (vtss_macsec_tx_sa_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_tx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an, mesa_macsec_tx_sa_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_rx_sa_counters_t) == sizeof(mesa_macsec_rx_sa_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rx_sa_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, (vtss_macsec_rx_sa_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rx_sa_counters_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_macsec_rx_sa_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_control_frame_match_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_control_frame_match_conf_t *const conf, uint32_t *const rule_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_control_frame_match_conf_t) == sizeof(mesa_macsec_control_frame_match_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_control_frame_match_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_macsec_control_frame_match_conf_t *)conf /* ag.rb:1867 */, rule_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_control_frame_match_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_control_frame_match_conf_t *const conf, uint32_t *const rule_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_control_frame_match_conf_del(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t rule_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_control_frame_match_conf_del((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, rule_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_control_frame_match_conf_del(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t rule_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_control_frame_match_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_control_frame_match_conf_t *const conf, uint32_t rule_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_control_frame_match_conf_t) == sizeof(mesa_macsec_control_frame_match_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_control_frame_match_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_control_frame_match_conf_t *)conf /* ag.rb:1867 */, rule_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_control_frame_match_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_control_frame_match_conf_t *const conf, uint32_t rule_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_pattern_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, const mesa_macsec_match_pattern_t *const pattern)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_direction_t) == sizeof(mesa_macsec_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_match_action_t) == sizeof(mesa_macsec_match_action_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_match_pattern_t) == sizeof(mesa_macsec_match_pattern_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_pattern_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, *((const vtss_macsec_direction_t *)&direction) /* ag.rb:1872 */, *((const vtss_macsec_match_action_t *)&action) /* ag.rb:1872 */, (const vtss_macsec_match_pattern_t *)pattern /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_pattern_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, const mesa_macsec_match_pattern_t *const pattern)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_pattern_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_direction_t) == sizeof(mesa_macsec_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_match_action_t) == sizeof(mesa_macsec_match_action_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_pattern_del((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, *((const vtss_macsec_direction_t *)&direction) /* ag.rb:1872 */, *((const vtss_macsec_match_action_t *)&action) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_pattern_del(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_pattern_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, mesa_macsec_match_pattern_t *const pattern)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_direction_t) == sizeof(mesa_macsec_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_match_action_t) == sizeof(mesa_macsec_match_action_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_match_pattern_t) == sizeof(mesa_macsec_match_pattern_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_pattern_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, *((const vtss_macsec_direction_t *)&direction) /* ag.rb:1872 */, *((const vtss_macsec_match_action_t *)&action) /* ag.rb:1872 */, (vtss_macsec_match_pattern_t *)pattern /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_pattern_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_direction_t direction, const mesa_macsec_match_action_t action, mesa_macsec_match_pattern_t *const pattern)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_default_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_default_action_policy_t *const policy)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_default_action_policy_t) == sizeof(mesa_macsec_default_action_policy_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_default_action_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_macsec_default_action_policy_t *)policy /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_default_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_default_action_policy_t *const policy)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_default_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_default_action_policy_t *const policy)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_default_action_policy_t) == sizeof(mesa_macsec_default_action_policy_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_default_action_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_default_action_policy_t *)policy /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_default_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_default_action_policy_t *const policy)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_bypass_mode_t *const bypass)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_bypass_mode_t) == sizeof(mesa_macsec_bypass_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_bypass_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_macsec_bypass_mode_t *)bypass /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_bypass_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_bypass_mode_t *const bypass)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_bypass_mode_t *const bypass)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_bypass_mode_t) == sizeof(mesa_macsec_bypass_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_bypass_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_bypass_mode_t *)bypass /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_bypass_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_bypass_mode_t *const bypass)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_tag_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tag_bypass_t tag)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tag_bypass_t) == sizeof(mesa_macsec_tag_bypass_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_bypass_tag_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, *((const vtss_macsec_tag_bypass_t *)&tag) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_bypass_tag_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_tag_bypass_t tag)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_bypass_tag_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tag_bypass_t *const tag)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_tag_bypass_t) == sizeof(mesa_macsec_tag_bypass_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_bypass_tag_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (vtss_macsec_tag_bypass_t *)tag /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_bypass_tag_get(const mesa_inst_t inst, const mesa_macsec_port_t port, mesa_macsec_tag_bypass_t *const tag)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_mtu_t *const mtu_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_mtu_t) == sizeof(mesa_macsec_mtu_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_mtu_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_macsec_mtu_t *)mtu_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_mtu_t *const mtu_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mtu_t * mtu_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_mtu_t) == sizeof(mesa_macsec_mtu_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_mtu_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_mtu_t *)mtu_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mtu_t * mtu_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_frame_capture_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_frame_capture_t capture)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_frame_capture_t) == sizeof(mesa_macsec_frame_capture_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_frame_capture_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_macsec_frame_capture_t *)&capture) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_frame_capture_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_frame_capture_t capture)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_frame_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t buf_length, uint32_t *const return_length, uint8_t *const frame)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_frame_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, buf_length, return_length, frame); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_frame_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t buf_length, uint32_t *const return_length, uint8_t *const frame)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_event_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_event_t) == sizeof(mesa_macsec_event_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_event_enable_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_macsec_event_t *)&ev_mask) /* ag.rb:1872 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_macsec_event_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_event_t) == sizeof(mesa_macsec_event_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_event_enable_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_event_t *)ev_mask /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_event_t) == sizeof(mesa_macsec_event_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_event_t *)ev_mask /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_seq_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t threshold)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_event_seq_threshold_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, threshold); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_event_seq_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_event_seq_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const threshold)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_event_seq_threshold_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, threshold); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_event_seq_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mmd, const uint32_t addr, uint32_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_csr_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mmd, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mmd, const uint32_t addr, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t mmd, const uint32_t addr, const uint32_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_csr_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mmd, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t mmd, const uint32_t addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_rc_dbg_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_rc_dbg_counters_t) == sizeof(mesa_macsec_rc_dbg_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_dbg_counter_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_rc_dbg_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_dbg_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_rc_dbg_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_hmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{ /* ag.rb:1845 */
    vtss_macsec_mac_counters_t __counters;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_macsec_hmac_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__counters, clear); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_macsec_mac_counters_t_to_mesa_macsec_mac_counters_t(&__counters, counters)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_macsec_hmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_lmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{ /* ag.rb:1845 */
    vtss_macsec_mac_counters_t __counters;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_macsec_lmac_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__counters, clear); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_macsec_mac_counters_t_to_mesa_macsec_mac_counters_t(&__counters, counters)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_macsec_lmac_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_mac_counters_t *const counters, const mesa_bool_t clear)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_is_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * capable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_is_capable((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, capable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_is_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * capable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_dbg_reg_dump((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, pr); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_dbg_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_lmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_lmac_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_lmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_hmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_hmac_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_hmac_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_debug_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_debug_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_debug_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_common_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_common_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_common_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_uncontrolled_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_uncontrolled_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_uncontrolled_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_controlled_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_controlled_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_controlled_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rxsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rxsa_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rxsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rxsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rxsc_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rxsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_txsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_txsa_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_txsa_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port, const uint16_t an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_txsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_txsc_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_txsc_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_secy_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_secy_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_secy_counters_clear(const mesa_inst_t inst, const mesa_macsec_port_t port)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_port_enable_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_port_enable_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, status); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_port_enable_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_rxsa_an_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_bool_t * status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_rxsa_an_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, status); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_rxsa_an_status_get(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, const uint16_t an, mesa_bool_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_mac_block_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const mtu_value, mesa_bool_t *const mtu_tag_check)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_block_mtu_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mtu_value, mtu_tag_check); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_block_mtu_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const mtu_value, mesa_bool_t *const mtu_tag_check)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_mac_block_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mtu_value, const mesa_bool_t mtu_tag_check)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_mac_block_mtu_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mtu_value, mtu_tag_check); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_mac_block_mtu_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mtu_value, const mesa_bool_t mtu_tag_check)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_fcbuf_frame_gap_comp_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t frm_gap)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_fcbuf_frame_gap_comp_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, frm_gap); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_fcbuf_frame_gap_comp_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t frm_gap)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_fcb_block_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_dbg_fcb_block_reg_dump((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, pr); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_dbg_fcb_block_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_frm_match_handling_ctrl_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_macsec_dbg_frm_match_handling_ctrl_reg_dump((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, pr); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_dbg_frm_match_handling_ctrl_reg_dump(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_debug_printf_t pr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_dbg_update_seq_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, uint16_t an, mesa_bool_t egr, const mesa_bool_t disable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_sci_t) == sizeof(mesa_macsec_sci_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_dbg_update_seq_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_macsec_port_t *)&port) /* ag.rb:1872 */, (const vtss_macsec_sci_t *)sci /* ag.rb:1867 */, an, egr, disable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_dbg_update_seq_set(const mesa_inst_t inst, const mesa_macsec_port_t port, const mesa_macsec_sci_t *const sci, uint16_t an, mesa_bool_t egr, const mesa_bool_t disable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MACSEC)
mesa_rc mesa_macsec_egr_intr_sa_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_port_t *const port, uint16_t *const an)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_macsec_port_t) == sizeof(mesa_macsec_port_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_macsec_egr_intr_sa_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_macsec_port_t *)port /* ag.rb:1867 */, an); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_macsec_egr_intr_sa_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_macsec_port_t *const port, uint16_t *const an)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MACSEC) /* ag.rb:1989 */

mesa_rc mesa_trace_conf_get(const mesa_trace_group_t group, mesa_trace_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_trace_group_t) == sizeof(mesa_trace_group_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_trace_conf_t) == sizeof(mesa_trace_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_trace_conf_get(*((const vtss_trace_group_t *)&group) /* ag.rb:1872 */, (vtss_trace_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

mesa_rc mesa_trace_conf_set(const mesa_trace_group_t group, const mesa_trace_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_trace_group_t) == sizeof(mesa_trace_group_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_trace_conf_t) == sizeof(mesa_trace_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_trace_conf_set(*((const vtss_trace_group_t *)&group) /* ag.rb:1872 */, (const vtss_trace_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

mesa_rc mesa_debug_info_get(mesa_debug_info_t *const info)
{ /* ag.rb:1845 */
    vtss_debug_info_t __info;
    mesa_rc rc = vtss_debug_info_get(&__info); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_debug_info_t_to_mesa_debug_info_t(&__info, info)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}

mesa_rc mesa_debug_info_print(const mesa_inst_t inst, const mesa_debug_printf_t prntf, const mesa_debug_info_t *const info)
{ /* ag.rb:1845 */
    vtss_debug_info_t __info;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    memset(&__info, 0, sizeof(__info)); /* ag.rb:1926 */; /* ag.rb:1965 */
    __RC(mesa_conv_mesa_debug_info_t_to_vtss_debug_info_t(info, &__info)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_debug_info_print((const vtss_inst_t)inst /* ag.rb:1870 */, prntf, &__info); /* ag.rb:1976*/ 
}

mesa_rc mesa_debug_lock(const mesa_inst_t inst, const mesa_debug_lock_t *const lock)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_debug_lock_t) == sizeof(mesa_debug_lock_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_debug_lock((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_debug_lock_t *)lock /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

mesa_rc mesa_debug_unlock(const mesa_inst_t inst, mesa_debug_lock_t *const lock)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_debug_lock_t) == sizeof(mesa_debug_lock_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_debug_unlock((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_debug_lock_t *)lock /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_reg_read(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const uint32_t addr, uint32_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_reg_read((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_reg_read(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const uint32_t addr, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_reg_write(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const uint32_t addr, const uint32_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_reg_write((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_reg_write(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const uint32_t addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_reg_write_masked(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const uint32_t addr, const uint32_t value, const uint32_t mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_reg_write_masked((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, addr, value, mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_reg_write_masked(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const uint32_t addr, const uint32_t value, const uint32_t mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_intr_sticky_clear(const mesa_inst_t inst, uint32_t ext)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_intr_sticky_clear((const vtss_inst_t)inst /* ag.rb:1870 */, ext); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_intr_sticky_clear(const mesa_inst_t inst, uint32_t ext)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_chip_id_get(const mesa_inst_t inst, mesa_chip_id_t *const chip_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_chip_id_t) == sizeof(mesa_chip_id_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_chip_id_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_chip_id_t *)chip_id /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_chip_id_get(const mesa_inst_t inst, mesa_chip_id_t *const chip_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_poll_1sec(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_poll_1sec((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_poll_1sec(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_ptp_event_poll(const mesa_inst_t inst, mesa_ptp_event_type_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ptp_event_type_t) == sizeof(mesa_ptp_event_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ptp_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_ptp_event_type_t *)ev_mask /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ptp_event_poll(const mesa_inst_t inst, mesa_ptp_event_type_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_ptp_event_enable(const mesa_inst_t inst, const mesa_ptp_event_type_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ptp_event_type_t) == sizeof(mesa_ptp_event_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ptp_event_enable((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_ptp_event_type_t *)&ev_mask) /* ag.rb:1872 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ptp_event_enable(const mesa_inst_t inst, const mesa_ptp_event_type_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_dev_all_event_poll(const mesa_inst_t inst, const mesa_dev_all_event_poll_t poll_type, mesa_dev_all_event_type_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_dev_all_event_poll_t) == sizeof(mesa_dev_all_event_poll_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_dev_all_event_type_t) == sizeof(mesa_dev_all_event_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_dev_all_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_dev_all_event_poll_t *)&poll_type) /* ag.rb:1872 */, (vtss_dev_all_event_type_t *)ev_mask /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_dev_all_event_poll(const mesa_inst_t inst, const mesa_dev_all_event_poll_t poll_type, mesa_dev_all_event_type_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_MISC)
mesa_rc mesa_dev_all_event_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_dev_all_event_type_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_dev_all_event_type_t) == sizeof(mesa_dev_all_event_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_dev_all_event_enable((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_dev_all_event_type_t *)&ev_mask) /* ag.rb:1872 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_dev_all_event_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_dev_all_event_type_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_MISC) /* ag.rb:1989 */

#if defined(VTSS_GPIOS)
mesa_rc mesa_gpio_mode_set(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, const mesa_gpio_mode_t mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_gpio_mode_t) == sizeof(mesa_gpio_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_gpio_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, gpio_no, *((const vtss_gpio_mode_t *)&mode) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_gpio_mode_set(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, const mesa_gpio_mode_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_GPIOS) /* ag.rb:1989 */

#if defined(VTSS_GPIOS)
mesa_rc mesa_gpio_direction_set(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, const mesa_bool_t output)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_gpio_direction_set((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, gpio_no, output); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_gpio_direction_set(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, const mesa_bool_t output)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_GPIOS) /* ag.rb:1989 */

#if defined(VTSS_GPIOS)
mesa_rc mesa_gpio_read(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, mesa_bool_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_gpio_read((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, gpio_no, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_gpio_read(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, mesa_bool_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_GPIOS) /* ag.rb:1989 */

#if defined(VTSS_GPIOS)
mesa_rc mesa_gpio_write(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, const mesa_bool_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_gpio_write((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, gpio_no, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_gpio_write(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, const mesa_bool_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_GPIOS) /* ag.rb:1989 */

#if defined(VTSS_GPIOS)
mesa_rc mesa_gpio_event_poll(const mesa_inst_t inst, const mesa_chip_no_t chip_no, mesa_bool_t *const events)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_gpio_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, events); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_gpio_event_poll(const mesa_inst_t inst, const mesa_chip_no_t chip_no, mesa_bool_t *const events)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_GPIOS) /* ag.rb:1989 */

#if defined(VTSS_GPIOS)
mesa_rc mesa_gpio_event_enable(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_gpio_event_enable((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, gpio_no, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_gpio_event_enable(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_gpio_no_t gpio_no, mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_GPIOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SERIAL_GPIO)
mesa_rc mesa_sgpio_conf_get(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, mesa_sgpio_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_sgpio_conf_t) == sizeof(mesa_sgpio_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_sgpio_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, group, (vtss_sgpio_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_sgpio_conf_get(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, mesa_sgpio_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SERIAL_GPIO) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SERIAL_GPIO)
mesa_rc mesa_sgpio_conf_set(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, const mesa_sgpio_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_sgpio_conf_t) == sizeof(mesa_sgpio_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_sgpio_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, group, (const vtss_sgpio_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_sgpio_conf_set(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, const mesa_sgpio_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SERIAL_GPIO) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SERIAL_GPIO)
mesa_rc mesa_sgpio_event_poll(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, const uint32_t bit, mesa_bool_t *const events)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_sgpio_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, group, bit, events); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_sgpio_event_poll(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, const uint32_t bit, mesa_bool_t *const events)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SERIAL_GPIO) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SERIAL_GPIO)
mesa_rc mesa_sgpio_event_enable(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, const mesa_port_no_t port, const uint32_t bit, mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_sgpio_event_enable((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, group, port, bit, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_sgpio_event_enable(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_sgpio_group_t group, const mesa_port_no_t port, const uint32_t bit, mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SERIAL_GPIO) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_INTERRUPTS)
mesa_rc mesa_intr_cfg(const mesa_inst_t inst, const uint32_t mask, const mesa_bool_t polarity, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_intr_cfg((const vtss_inst_t)inst /* ag.rb:1870 */, mask, polarity, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_intr_cfg(const mesa_inst_t inst, const uint32_t mask, const mesa_bool_t polarity, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_INTERRUPTS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_INTERRUPTS)
mesa_rc mesa_intr_mask_set(const mesa_inst_t inst, mesa_intr_t * mask)
{ /* ag.rb:1845 */
    vtss_intr_t __mask;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_intr_mask_set((const vtss_inst_t)inst /* ag.rb:1870 */, &__mask); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_intr_t_to_mesa_intr_t(&__mask, mask)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_intr_mask_set(const mesa_inst_t inst, mesa_intr_t * mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_INTERRUPTS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_INTERRUPTS)
mesa_rc mesa_intr_status_get(const mesa_inst_t inst, mesa_intr_t * status)
{ /* ag.rb:1845 */
    vtss_intr_t __status;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_intr_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__status); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_intr_t_to_mesa_intr_t(&__status, status)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_intr_status_get(const mesa_inst_t inst, mesa_intr_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_INTERRUPTS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_INTERRUPTS)
mesa_rc mesa_intr_pol_negation(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_intr_pol_negation((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_intr_pol_negation(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_INTERRUPTS) /* ag.rb:1989 */

#ifdef VTSS_FEATURE_IRQ_CONTROL
mesa_rc mesa_irq_conf_get(const mesa_inst_t inst, const mesa_irq_t irq, mesa_irq_conf_t * conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_irq_t) == sizeof(mesa_irq_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_irq_conf_t) == sizeof(mesa_irq_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_irq_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_irq_t *)&irq) /* ag.rb:1872 */, (vtss_irq_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_irq_conf_get(const mesa_inst_t inst, const mesa_irq_t irq, mesa_irq_conf_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_IRQ_CONTROL /* ag.rb:1989 */

#ifdef VTSS_FEATURE_IRQ_CONTROL
mesa_rc mesa_irq_conf_set(const mesa_inst_t inst, const mesa_irq_t irq, const mesa_irq_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_irq_t) == sizeof(mesa_irq_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_irq_conf_t) == sizeof(mesa_irq_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_irq_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_irq_t *)&irq) /* ag.rb:1872 */, (const vtss_irq_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_irq_conf_set(const mesa_inst_t inst, const mesa_irq_t irq, const mesa_irq_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_IRQ_CONTROL /* ag.rb:1989 */

#ifdef VTSS_FEATURE_IRQ_CONTROL
mesa_rc mesa_irq_status_get_and_mask(const mesa_inst_t inst, mesa_irq_status_t * status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_irq_status_t) == sizeof(mesa_irq_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_irq_status_get_and_mask((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_irq_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_irq_status_get_and_mask(const mesa_inst_t inst, mesa_irq_status_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_IRQ_CONTROL /* ag.rb:1989 */

#ifdef VTSS_FEATURE_IRQ_CONTROL
mesa_rc mesa_irq_enable(const mesa_inst_t inst, const mesa_irq_t irq, mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_irq_t) == sizeof(mesa_irq_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_irq_enable((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_irq_t *)&irq) /* ag.rb:1872 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_irq_enable(const mesa_inst_t inst, const mesa_irq_t irq, mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_IRQ_CONTROL /* ag.rb:1989 */

uint32_t mesa_tod_get_ns_cnt()
{ /* ag.rb:1845 */
    return vtss_tod_get_ns_cnt(); /* ag.rb:1976*/ 
}

void mesa_tod_set_ns_cnt_cb(tod_get_ns_cnt_cb_t cb)
{ /* ag.rb:1845 */
    return vtss_tod_set_ns_cnt_cb(cb); /* ag.rb:1976*/ 
}

#if defined(VTSS_FEATURE_FAN)
#if defined(VTSS_FEATURE_TEMP_SENSOR)
mesa_rc mesa_temp_sensor_init(const mesa_inst_t inst, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_temp_sensor_init((const vtss_inst_t)inst /* ag.rb:1870 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_temp_sensor_init(const mesa_inst_t inst, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TEMP_SENSOR) /* ag.rb:1989 */
#else
mesa_rc mesa_temp_sensor_init(const mesa_inst_t inst, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FAN) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FAN)
#if defined(VTSS_FEATURE_TEMP_SENSOR)
mesa_rc mesa_temp_sensor_get(const mesa_inst_t inst, int16_t * temperature)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_temp_sensor_get((const vtss_inst_t)inst /* ag.rb:1870 */, temperature); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_temp_sensor_get(const mesa_inst_t inst, int16_t * temperature)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TEMP_SENSOR) /* ag.rb:1989 */
#else
mesa_rc mesa_temp_sensor_get(const mesa_inst_t inst, int16_t * temperature)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FAN) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FAN)
mesa_rc mesa_fan_cool_lvl_set(const mesa_inst_t inst, uint8_t lvl)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_fan_cool_lvl_set((const vtss_inst_t)inst /* ag.rb:1870 */, lvl); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_fan_cool_lvl_set(const mesa_inst_t inst, uint8_t lvl)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FAN) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FAN)
mesa_rc mesa_fan_controller_init(const mesa_inst_t inst, const mesa_fan_conf_t *const spec)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_fan_conf_t) == sizeof(mesa_fan_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_fan_controller_init((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_fan_conf_t *)spec /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_fan_controller_init(const mesa_inst_t inst, const mesa_fan_conf_t *const spec)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FAN) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FAN)
mesa_rc mesa_fan_cool_lvl_get(const mesa_inst_t inst, uint8_t * lvl)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_fan_cool_lvl_get((const vtss_inst_t)inst /* ag.rb:1870 */, lvl); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_fan_cool_lvl_get(const mesa_inst_t inst, uint8_t * lvl)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FAN) /* ag.rb:1989 */

#ifdef VTSS_FEATURE_EEE
mesa_rc mesa_eee_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_eee_port_conf_t *const eee_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_eee_port_conf_t) == sizeof(mesa_eee_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_eee_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_eee_port_conf_t *)eee_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_eee_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_eee_port_conf_t *const eee_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_EEE /* ag.rb:1989 */

mesa_rc mesa_symreg_data_get(const mesa_inst_t inst, mesa_symreg_data_t *const data)
{ /* ag.rb:1845 */
    vtss_symreg_data_t __data;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_symreg_data_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__data); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_symreg_data_t_to_mesa_symreg_data_t(&__data, data)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_npi_conf_get(const mesa_inst_t inst, mesa_npi_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_npi_conf_t) == sizeof(mesa_npi_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_npi_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_npi_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_npi_conf_get(const mesa_inst_t inst, mesa_npi_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_npi_conf_set(const mesa_inst_t inst, const mesa_npi_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_npi_conf_t) == sizeof(mesa_npi_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_npi_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_npi_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_npi_conf_set(const mesa_inst_t inst, const mesa_npi_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_rx_conf_get(const mesa_inst_t inst, mesa_packet_rx_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_packet_rx_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_packet_rx_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_packet_rx_conf_t_to_mesa_packet_rx_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_packet_rx_conf_get(const mesa_inst_t inst, mesa_packet_rx_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_rx_conf_set(const mesa_inst_t inst, const mesa_packet_rx_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_packet_rx_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_packet_rx_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_packet_rx_conf_t_to_vtss_packet_rx_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_packet_rx_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_rx_conf_set(const mesa_inst_t inst, const mesa_packet_rx_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_rx_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_packet_rx_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_packet_rx_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_packet_rx_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_packet_rx_port_conf_t_to_mesa_packet_rx_port_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_packet_rx_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_packet_rx_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_rx_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_packet_rx_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_packet_rx_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_packet_rx_port_conf_t_to_vtss_packet_rx_port_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_packet_rx_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_rx_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_packet_rx_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
void mesa_packet_frame_info_init(mesa_packet_frame_info_t *const info)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_packet_frame_info_t) == sizeof(mesa_packet_frame_info_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_packet_frame_info_init((vtss_packet_frame_info_t *)info /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_frame_filter(const mesa_inst_t inst, const mesa_packet_frame_info_t *const info, mesa_packet_filter_t *const filter)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_frame_info_t) == sizeof(mesa_packet_frame_info_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_filter_t) == sizeof(mesa_packet_filter_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_packet_frame_filter((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_packet_frame_info_t *)info /* ag.rb:1867 */, (vtss_packet_filter_t *)filter /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_frame_filter(const mesa_inst_t inst, const mesa_packet_frame_info_t *const info, mesa_packet_filter_t *const filter)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_port_info_init(mesa_packet_port_info_t *const info)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_packet_port_info_t) == sizeof(mesa_packet_port_info_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_packet_port_info_init((vtss_packet_port_info_t *)info /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_port_info_init(mesa_packet_port_info_t *const info)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_vlan_status_get(const mesa_inst_t inst, mesa_packet_vlan_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_vlan_status_t) == sizeof(mesa_packet_vlan_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_packet_vlan_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_packet_vlan_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_vlan_status_get(const mesa_inst_t inst, mesa_packet_vlan_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_rx_hdr_decode(const mesa_inst_t inst, const mesa_packet_rx_meta_t *const meta, const uint8_t hdr[MESA_PACKET_HDR_SIZE_BYTES], mesa_packet_rx_info_t *const info)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_rx_meta_t) == sizeof(mesa_packet_rx_meta_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_rx_info_t) == sizeof(mesa_packet_rx_info_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_packet_rx_hdr_decode((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_packet_rx_meta_t *)meta /* ag.rb:1867 */, hdr, (vtss_packet_rx_info_t *)info /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_rx_hdr_decode(const mesa_inst_t inst, const mesa_packet_rx_meta_t *const meta, const uint8_t hdr[MESA_PACKET_HDR_SIZE_BYTES], mesa_packet_rx_info_t *const info)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_tx_frame(const mesa_inst_t inst, const mesa_packet_tx_info_t *const tx_info, const uint8_t *const frame, const uint32_t length)
{ /* ag.rb:1845 */
    vtss_packet_tx_info_t __tx_info;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_packet_tx_info_t_to_vtss_packet_tx_info_t(tx_info, &__tx_info)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_packet_tx_frame((const vtss_inst_t)inst /* ag.rb:1870 */, &__tx_info, frame, length); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_tx_frame(const mesa_inst_t inst, const mesa_packet_tx_info_t *const tx_info, const uint8_t *const frame, const uint32_t length)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_tx_info_init(const mesa_inst_t inst, mesa_packet_tx_info_t *const info)
{ /* ag.rb:1845 */
    vtss_packet_tx_info_t __info;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_packet_tx_info_init((const vtss_inst_t)inst /* ag.rb:1870 */, &__info); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_packet_tx_info_t_to_mesa_packet_tx_info_t(&__info, info)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_packet_tx_info_init(const mesa_inst_t inst, mesa_packet_tx_info_t *const info)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_rx_frame(const mesa_inst_t inst, uint8_t *const data, const uint32_t buflen, mesa_packet_rx_info_t *const rx_info)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_rx_info_t) == sizeof(mesa_packet_rx_info_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_packet_rx_frame((const vtss_inst_t)inst /* ag.rb:1870 */, data, buflen, (vtss_packet_rx_info_t *)rx_info /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_rx_frame(const mesa_inst_t inst, uint8_t *const data, const uint32_t buflen, mesa_packet_rx_info_t *const rx_info)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_phy_cnt_to_ts_cnt(const mesa_inst_t inst, const uint32_t phy_cnt, uint64_t * ts_cnt)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_packet_phy_cnt_to_ts_cnt((const vtss_inst_t)inst /* ag.rb:1870 */, phy_cnt, ts_cnt); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_phy_cnt_to_ts_cnt(const mesa_inst_t inst, const uint32_t phy_cnt, uint64_t * ts_cnt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_packet_ns_to_ts_cnt(const mesa_inst_t inst, const uint32_t ns, uint64_t * ts_cnt)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_packet_ns_to_ts_cnt((const vtss_inst_t)inst /* ag.rb:1870 */, ns, ts_cnt); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_packet_ns_to_ts_cnt(const mesa_inst_t inst, const uint32_t ns, uint64_t * ts_cnt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PACKET)
mesa_rc mesa_ptp_get_timestamp(const mesa_inst_t inst, const uint8_t frm[MESA_PTP_FRAME_TS_LENGTH], const mesa_packet_rx_info_t *const rx_info, mesa_packet_ptp_message_type_t message_type, mesa_packet_timestamp_props_t ts_props, uint64_t * rxTime, mesa_bool_t * timestamp_ok)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_rx_info_t) == sizeof(mesa_packet_rx_info_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_ptp_message_type_t) == sizeof(mesa_packet_ptp_message_type_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_packet_timestamp_props_t) == sizeof(mesa_packet_timestamp_props_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ptp_get_timestamp((const vtss_inst_t)inst /* ag.rb:1870 */, frm, (const vtss_packet_rx_info_t *)rx_info /* ag.rb:1867 */, *((vtss_packet_ptp_message_type_t *)&message_type) /* ag.rb:1872 */, *((vtss_packet_timestamp_props_t *)&ts_props) /* ag.rb:1872 */, rxTime, timestamp_ok); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ptp_get_timestamp(const mesa_inst_t inst, const uint8_t frm[MESA_PTP_FRAME_TS_LENGTH], const mesa_packet_rx_info_t *const rx_info, mesa_packet_ptp_message_type_t message_type, mesa_packet_timestamp_props_t ts_props, uint64_t * rxTime, mesa_bool_t * timestamp_ok)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PACKET) /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_init_parm_t *const init_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_init_parm_t) == sizeof(mesa_phy_10g_init_parm_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_init((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_init_parm_t *)init_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_init_parm_t *const init_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_mode_t *const mode)
{ /* ag.rb:1845 */
    vtss_phy_10g_mode_t __mode;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_10g_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__mode); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_phy_10g_mode_t_to_mesa_phy_10g_mode_t(&__mode, mode)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_10g_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_mode_t *const mode)
{ /* ag.rb:1845 */
    vtss_phy_10g_mode_t __mode;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_phy_10g_mode_t_to_vtss_phy_10g_mode_t(mode, &__mode)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_phy_10g_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__mode); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ib_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ib_conf_t *const ib_conf, mesa_bool_t is_host)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_ib_conf_t) == sizeof(mesa_phy_10g_ib_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_ib_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_ib_conf_t *)ib_conf /* ag.rb:1867 */, is_host); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_ib_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ib_conf_t *const ib_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ib_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_ib_conf_t *const ib_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_ib_conf_t) == sizeof(mesa_phy_10g_ib_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_ib_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, is_host, (vtss_phy_10g_ib_conf_t *)ib_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_ib_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_ib_conf_t *const ib_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ib_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ib_status_t *const ib_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_ib_status_t) == sizeof(mesa_phy_10g_ib_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_ib_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_ib_status_t *)ib_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_ib_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ib_status_t *const ib_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_apc_conf_t *const apc_conf, const mesa_bool_t is_host)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_apc_conf_t) == sizeof(mesa_phy_10g_apc_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_apc_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_apc_conf_t *)apc_conf /* ag.rb:1867 */, is_host); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_apc_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_apc_conf_t *const apc_conf, const mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_conf_t *const apc_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_apc_conf_t) == sizeof(mesa_phy_10g_apc_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_apc_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, is_host, (vtss_phy_10g_apc_conf_t *)apc_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_apc_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_conf_t *const apc_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_status_t *const apc_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_apc_status_t) == sizeof(mesa_phy_10g_apc_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_apc_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, is_host, (vtss_phy_10g_apc_status_t *)apc_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_apc_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host, mesa_phy_10g_apc_status_t *const apc_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_apc_restart(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_apc_restart((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, is_host); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_apc_restart(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_jitter_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_jitter_conf_t) == sizeof(mesa_phy_10g_jitter_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_jitter_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_jitter_conf_t *)jitter_conf /* ag.rb:1867 */, is_host); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_jitter_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_jitter_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t * jitter_conf, mesa_bool_t is_host)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_jitter_conf_t) == sizeof(mesa_phy_10g_jitter_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_jitter_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_jitter_conf_t *)jitter_conf /* ag.rb:1867 */, is_host); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_jitter_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t * jitter_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_jitter_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_jitter_conf_t) == sizeof(mesa_phy_10g_jitter_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_jitter_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_jitter_conf_t *)jitter_conf /* ag.rb:1867 */, is_host); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_jitter_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_jitter_conf_t *const jitter_conf, mesa_bool_t is_host)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_fc_buffer_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_fc_buffer_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_fc_buffer_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_synce_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const synce_clkout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_synce_clkout_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, synce_clkout); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_synce_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_synce_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_synce_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t synce_clkout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_synce_clkout_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, synce_clkout); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_synce_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_synce_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t synce_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_xfp_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const xfp_clkout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_xfp_clkout_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, xfp_clkout); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_xfp_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_xfp_clkout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_xfp_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t xfp_clkout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_xfp_clkout_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, xfp_clkout); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_xfp_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_xfp_clkout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t xfp_clkout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_rxckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_rxckout_conf_t *const rxckout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_rxckout_conf_t) == sizeof(mesa_phy_10g_rxckout_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_rxckout_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_rxckout_conf_t *)rxckout /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_rxckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_rxckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_rxckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_rxckout_conf_t *const rxckout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_rxckout_conf_t) == sizeof(mesa_phy_10g_rxckout_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_rxckout_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_rxckout_conf_t *)rxckout /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_rxckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_rxckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_rxckout_conf_t *const rxckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_txckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_txckout_conf_t *const txckout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_txckout_conf_t) == sizeof(mesa_phy_10g_txckout_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_txckout_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_txckout_conf_t *)txckout /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_txckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_txckout_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_txckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_txckout_conf_t *const txckout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_txckout_conf_t) == sizeof(mesa_phy_10g_txckout_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_txckout_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_txckout_conf_t *)txckout /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_txckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_txckout_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_txckout_conf_t *const txckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_srefclk_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_srefclk_mode_t *const srefclk)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_srefclk_mode_t) == sizeof(mesa_phy_10g_srefclk_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_srefclk_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_srefclk_mode_t *)srefclk /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_srefclk_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_srefclk_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_srefclk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_srefclk_mode_t *const srefclk)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_srefclk_mode_t) == sizeof(mesa_phy_10g_srefclk_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_srefclk_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_srefclk_mode_t *)srefclk /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_srefclk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_srefclk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_srefclk_mode_t *const srefclk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_sckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_sckout_conf_t *const sckout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_sckout_conf_t) == sizeof(mesa_phy_10g_sckout_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_sckout_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_sckout_conf_t *)sckout /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_sckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_sckout_conf_t *const sckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_sckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_sckout_conf_t *const sckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_ckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ckout_conf_t *const ckout)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_ckout_conf_t) == sizeof(mesa_phy_10g_ckout_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_ckout_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_ckout_conf_t *)ckout /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_ckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ckout_conf_t *const ckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_ckout_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_ckout_conf_t *const ckout)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_line_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_line_clk_conf_t) == sizeof(mesa_phy_10g_line_clk_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_line_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_line_clk_conf_t *)line_clk /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_line_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_line_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_host_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_host_clk_conf_t) == sizeof(mesa_phy_10g_host_clk_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_host_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_host_clk_conf_t *)host_clk /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_host_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_host_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_line_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_line_clk_conf_t) == sizeof(mesa_phy_10g_line_clk_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_line_recvrd_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_line_clk_conf_t *)line_clk /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_line_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_line_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_line_clk_conf_t *const line_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#if defined(VTSS_FEATURE_SYNCE_10G)
mesa_rc mesa_phy_10g_host_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_host_clk_conf_t) == sizeof(mesa_phy_10g_host_clk_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_host_recvrd_clk_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_host_clk_conf_t *)host_clk /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_host_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE_10G) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_host_recvrd_clk_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_host_clk_conf_t *const host_clk)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_lane_sync_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_lane_sync_conf_t *const lane_sync)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_lane_sync_conf_t) == sizeof(mesa_phy_10g_lane_sync_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_lane_sync_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_lane_sync_conf_t *)lane_sync /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_lane_sync_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_lane_sync_conf_t *const lane_sync)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_debug_register_dump((const vtss_inst_t)inst /* ag.rb:1870 */, pr, clear, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_base_kr_train_aneg_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_train_aneg_t) == sizeof(mesa_phy_10g_base_kr_train_aneg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_train_aneg_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_base_kr_train_aneg_t *)kr_tr_aneg /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_base_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_train_aneg_t) == sizeof(mesa_phy_10g_base_kr_train_aneg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_train_aneg_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_base_kr_train_aneg_t *)kr_tr_aneg /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_base_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_base_host_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_train_aneg_t) == sizeof(mesa_phy_10g_base_kr_train_aneg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_base_host_kr_train_aneg_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_base_kr_train_aneg_t *)kr_tr_aneg /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_base_host_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_base_host_kr_train_aneg_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_train_aneg_t *const kr_tr_aneg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
#ifdef VTSS_FEATURE_10GBASE_KR
mesa_rc mesa_phy_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t direction, mesa_phy_10g_base_kr_status_t *const kr_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_status_t) == sizeof(mesa_phy_10g_base_kr_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_kr_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, direction, (vtss_phy_10g_base_kr_status_t *)kr_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t direction, mesa_phy_10g_base_kr_status_t *const kr_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_FEATURE_10GBASE_KR /* ag.rb:1989 */
#else
mesa_rc mesa_phy_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t direction, mesa_phy_10g_base_kr_status_t *const kr_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_base_kr_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_base_kr_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_host_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_host_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_base_kr_host_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_base_kr_host_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_base_kr_conf_t) == sizeof(mesa_phy_10g_base_kr_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_base_kr_host_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_base_kr_conf_t *)kr_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_base_kr_host_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_base_kr_conf_t *const kr_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_ob_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ob_status_t *const ob_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_ob_status_t) == sizeof(mesa_phy_10g_ob_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_ob_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_ob_status_t *)ob_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_ob_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_ob_status_t *const ob_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_status_t) == sizeof(mesa_phy_10g_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_serdes_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_serdes_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_serdes_status_t) == sizeof(mesa_phy_10g_serdes_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_serdes_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_serdes_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_serdes_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_serdes_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_clause_37_status_get(const mesa_inst_t inst, mesa_port_no_t port_no, mesa_phy_10g_clause_37_cmn_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_clause_37_cmn_status_t) == sizeof(mesa_phy_10g_clause_37_cmn_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_clause_37_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_clause_37_cmn_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_clause_37_status_get(const mesa_inst_t inst, mesa_port_no_t port_no, mesa_phy_10g_clause_37_cmn_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_clause_37_control_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_clause_37_control_t *const control)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_clause_37_control_t) == sizeof(mesa_phy_10g_clause_37_control_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_clause_37_control_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_clause_37_control_t *)control /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_clause_37_control_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_clause_37_control_t *const control)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_clause_37_control_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_clause_37_control_t *const control)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_clause_37_control_t) == sizeof(mesa_phy_10g_clause_37_control_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_clause_37_control_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_clause_37_control_t *)control /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_clause_37_control_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_clause_37_control_t *const control)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_loopback_t *const loopback)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_loopback_t) == sizeof(mesa_phy_10g_loopback_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_loopback_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_loopback_t *)loopback /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_loopback_t *const loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_loopback_t *const loopback)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_loopback_t) == sizeof(mesa_phy_10g_loopback_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_loopback_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_loopback_t *)loopback /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_loopback_t *const loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_cnt_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_cnt_t *const cnt)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_cnt_t) == sizeof(mesa_phy_10g_cnt_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_cnt_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_cnt_t *)cnt /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_cnt_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_cnt_t *const cnt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_power_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_power_t *const power)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_power_t) == sizeof(mesa_phy_10g_power_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_power_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_power_t *)power /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_power_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_power_t *const power)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_power_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_power_t *const power)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_power_t) == sizeof(mesa_phy_10g_power_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_power_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_power_t *)power /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_power_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_power_t *const power)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_bool_t mesa_phy_10G_is_valid(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10G_is_valid((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_failover_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_failover_mode_t) == sizeof(mesa_phy_10g_failover_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_failover_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_failover_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_failover_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_failover_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_failover_mode_t) == sizeof(mesa_phy_10g_failover_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_failover_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_failover_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_failover_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_failover_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_auto_failover_set(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_auto_failover_conf_t) == sizeof(mesa_phy_10g_auto_failover_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_auto_failover_set((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_phy_10g_auto_failover_conf_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_auto_failover_set(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_auto_failover_get(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_auto_failover_conf_t) == sizeof(mesa_phy_10g_auto_failover_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_auto_failover_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_phy_10g_auto_failover_conf_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_auto_failover_get(const mesa_inst_t inst, mesa_phy_10g_auto_failover_conf_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_vscope_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_vscope_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_vscope_conf_t) == sizeof(mesa_phy_10g_vscope_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_vscope_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_10g_vscope_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_vscope_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_vscope_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_vscope_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_vscope_conf_t) == sizeof(mesa_phy_10g_vscope_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_vscope_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_vscope_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_vscope_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_vscope_scan_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_scan_status_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_vscope_scan_status_t) == sizeof(mesa_phy_10g_vscope_scan_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_vscope_scan_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_vscope_scan_status_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_vscope_scan_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_vscope_scan_status_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_generator_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_generator_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_generator_conf_t) == sizeof(mesa_phy_10g_prbs_generator_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_generator_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1872 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1872 */, (vtss_phy_10g_prbs_generator_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_generator_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_generator_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_generator_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_generator_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_generator_conf_t) == sizeof(mesa_phy_10g_prbs_generator_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_generator_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1872 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1872 */, (const vtss_phy_10g_prbs_generator_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_generator_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_generator_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_monitor_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_monitor_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_monitor_conf_t) == sizeof(mesa_phy_10g_prbs_monitor_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_monitor_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1872 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1872 */, (vtss_phy_10g_prbs_monitor_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_monitor_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, mesa_phy_10g_prbs_monitor_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_monitor_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_monitor_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_monitor_conf_t) == sizeof(mesa_phy_10g_prbs_monitor_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_monitor_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1872 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1872 */, (const vtss_phy_10g_prbs_monitor_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_monitor_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_phy_10g_prbs_monitor_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_monitor_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_bool_t reset, mesa_phy_10g_prbs_monitor_status_t *const mon_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_type_t) == sizeof(mesa_phy_10g_prbs_type_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_direction_t) == sizeof(mesa_phy_10g_direction_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_monitor_status_t) == sizeof(mesa_phy_10g_prbs_monitor_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_monitor_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_10g_prbs_type_t *)&type) /* ag.rb:1872 */, *((const vtss_phy_10g_direction_t *)&direction) /* ag.rb:1872 */, reset, (vtss_phy_10g_prbs_monitor_status_t *)mon_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_monitor_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_prbs_type_t type, const mesa_phy_10g_direction_t direction, const mesa_bool_t reset, mesa_phy_10g_prbs_monitor_status_t *const mon_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_gen_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_gen_conf_t) == sizeof(mesa_phy_10g_prbs_gen_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_gen_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_prbs_gen_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_gen_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_gen_conf_t) == sizeof(mesa_phy_10g_prbs_gen_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_gen_conf((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_prbs_gen_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_gen_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_mon_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_mon_conf_t) == sizeof(mesa_phy_10g_prbs_mon_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_mon_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_prbs_mon_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_mon_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_prbs_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_prbs_mon_conf_t) == sizeof(mesa_phy_10g_prbs_mon_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_prbs_mon_conf((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_prbs_mon_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_prbs_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_prbs_mon_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pkt_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_gen_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_pkt_gen_conf_t) == sizeof(mesa_phy_10g_pkt_gen_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_pkt_gen_conf((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_pkt_gen_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_pkt_gen_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_gen_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pkt_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ts_rd, mesa_phy_10g_pkt_mon_conf_t *const conf, mesa_phy_10g_timestamp_val_t *const conf_ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_pkt_mon_conf_t) == sizeof(mesa_phy_10g_pkt_mon_conf_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_timestamp_val_t) == sizeof(mesa_phy_10g_timestamp_val_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_pkt_mon_conf((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ts_rd, (vtss_phy_10g_pkt_mon_conf_t *)conf /* ag.rb:1867 */, (vtss_phy_10g_timestamp_val_t *)conf_ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_pkt_mon_conf(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ts_rd, mesa_phy_10g_pkt_mon_conf_t *const conf, mesa_phy_10g_timestamp_val_t *const conf_ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pkt_mon_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_mon_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_pkt_mon_conf_t) == sizeof(mesa_phy_10g_pkt_mon_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_pkt_mon_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_pkt_mon_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_pkt_mon_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_pkt_mon_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_id_t *const phy_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_id_t) == sizeof(mesa_phy_10g_id_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_id_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_id_t *)phy_id /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_id_t *const phy_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_gpio_10g_gpio_mode_t *const mode)
{ /* ag.rb:1845 */
    vtss_gpio_10g_gpio_mode_t __mode;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_phy_10g_gpio_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, &__mode);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_gpio_10g_gpio_mode_t_to_vtss_gpio_10g_gpio_mode_t(mode, &__mode)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_phy_10g_gpio_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, &__mode); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_gpio_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_gpio_10g_gpio_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_gpio_10g_gpio_mode_t *const mode)
{ /* ag.rb:1845 */
    vtss_gpio_10g_gpio_mode_t __mode;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_10g_gpio_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, &__mode); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_gpio_10g_gpio_mode_t_to_mesa_gpio_10g_gpio_mode_t(&__mode, mode)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_10g_gpio_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_gpio_10g_gpio_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_bool_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_gpio_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_gpio_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, mesa_bool_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_gpio_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_bool_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_gpio_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_gpio_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_gpio_10g_no_t gpio_no, const mesa_bool_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_event_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_event_enable_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_event_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_event_enable_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_extended_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_extended_event_enable_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ex_ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_extended_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_pcs_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_pcs_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ex_events); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_pcs_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_extended_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_extended_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ex_events); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_extended_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_extnd_event_t *const ex_events)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_extended_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_extnd_event_t ex_ev_mask, const mesa_bool_t extnd_enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_extended_event_enable_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ex_ev_mask, extnd_enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_extended_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_10g_extnd_event_t ex_ev_mask, const mesa_bool_t extnd_enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_poll_1sec(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_poll_1sec((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_poll_1sec(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_edc_fw_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_fw_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_fw_status_t) == sizeof(mesa_phy_10g_fw_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_edc_fw_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_fw_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_edc_fw_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_fw_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, uint32_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_csr_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, dev, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_csr_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, const uint32_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_csr_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, dev, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_csr_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t dev, const uint32_t addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_warm_start_10g_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_warm_start_10g_failed_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_warm_start_10g_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_sgmii_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_sgmii_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_sgmii_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, uint16_t * value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_i2c_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, uint16_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, const uint16_t * value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_i2c_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t addr, const uint16_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_slave_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t *const i2c_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_i2c_slave_conf_t) == sizeof(mesa_phy_10g_i2c_slave_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_i2c_slave_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_i2c_slave_conf_t *)i2c_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_i2c_slave_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t *const i2c_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_i2c_slave_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t * i2c_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_10g_i2c_slave_conf_t) == sizeof(mesa_phy_10g_i2c_slave_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_10g_i2c_slave_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_10g_i2c_slave_conf_t *)i2c_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_i2c_slave_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_10g_i2c_slave_conf_t * i2c_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_10G_PHY
mesa_rc mesa_phy_10g_get_user_data(const mesa_inst_t inst, const mesa_port_no_t port_no, void ** user_data)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_10g_get_user_data((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, user_data); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_10g_get_user_data(const mesa_inst_t inst, const mesa_port_no_t port_no, void ** user_data)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_10G_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_pre_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_pre_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_pre_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_post_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_post_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_post_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_pre_system_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_pre_system_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_pre_system_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_reset_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_phy_reset_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_phy_reset_conf_t_to_vtss_phy_reset_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_phy_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_reset_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_reset_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_reset_conf_t * conf)
{ /* ag.rb:1845 */
    vtss_phy_reset_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_reset_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_phy_reset_conf_t_to_mesa_phy_reset_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_reset_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_reset_conf_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_chip_temp_get(const mesa_inst_t inst, const mesa_port_no_t port_no, int16_t *const temp)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_chip_temp_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, temp); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_chip_temp_get(const mesa_inst_t inst, const mesa_port_no_t port_no, int16_t *const temp)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_chip_temp_init(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_chip_temp_init((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_chip_temp_init(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_phy_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_phy_conf_t_to_mesa_phy_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_phy_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_phy_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_phy_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_cl37_lp_abil_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_cl37_lp_abil_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_cl37_lp_abil_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_type_t * phy_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_type_t) == sizeof(mesa_phy_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_id_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_type_t *)phy_id /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_id_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_type_t * phy_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ring_resiliency_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ring_resiliency_conf_t) == sizeof(mesa_phy_ring_resiliency_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ring_resiliency_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_ring_resiliency_conf_t *)ring_rslnt_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ring_resiliency_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ring_resiliency_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ring_resiliency_conf_t) == sizeof(mesa_phy_ring_resiliency_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ring_resiliency_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_ring_resiliency_conf_t *)ring_rslnt_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ring_resiliency_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ring_resiliency_conf_t *const ring_rslnt_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_1g_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_conf_1g_t) == sizeof(mesa_phy_conf_1g_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_conf_1g_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_conf_1g_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_conf_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_conf_1g_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_conf_1g_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_1g_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_conf_1g_t) == sizeof(mesa_phy_conf_1g_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_conf_1g_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_conf_1g_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_conf_1g_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_conf_1g_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_status_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_status_1g_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_status_1g_t) == sizeof(mesa_phy_status_1g_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_status_1g_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_status_1g_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_status_1g_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_status_1g_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_power_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_phy_power_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_power_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_phy_power_conf_t_to_mesa_phy_power_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_power_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_power_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_power_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_phy_power_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_phy_power_conf_t_to_vtss_phy_power_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_phy_power_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_power_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_power_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_power_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_power_status_t) == sizeof(mesa_phy_power_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_power_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_power_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_power_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_power_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_clock_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, const mesa_phy_clock_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_clock_conf_t) == sizeof(mesa_phy_clock_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_clock_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, clock_port, (const vtss_phy_clock_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_clock_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, const mesa_phy_clock_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_clock_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, mesa_phy_clock_conf_t *const conf, mesa_port_no_t *const clock_source)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_clock_conf_t) == sizeof(mesa_phy_clock_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_clock_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, clock_port, (vtss_phy_clock_conf_t *)conf /* ag.rb:1867 */, clock_source); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_clock_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_recov_clk_t clock_port, mesa_phy_clock_conf_t *const conf, mesa_port_no_t *const clock_source)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t *const value, uint8_t cnt, mesa_bool_t word_access)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_i2c_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, i2c_mux, i2c_reg_addr, i2c_device_addr, value, cnt, word_access); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_i2c_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t *const value, uint8_t cnt, mesa_bool_t word_access)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t * value, uint8_t cnt, mesa_bool_t word_access)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_i2c_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, i2c_mux, i2c_reg_addr, i2c_device_addr, value, cnt, word_access); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_i2c_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t i2c_mux, const uint8_t i2c_reg_addr, const uint8_t i2c_device_addr, uint8_t * value, uint8_t cnt, mesa_bool_t word_access)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, uint16_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, uint16_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_read_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t page, const uint32_t addr, uint16_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_read_page((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, page, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_read_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t page, const uint32_t addr, uint16_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mmd_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_mmd_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, devad, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_mmd_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mmd_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_mmd_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, devad, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_mmd_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t devad, const uint32_t addr, uint16_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_write_masked(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value, const uint16_t mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_write_masked((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, addr, value, mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_write_masked(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t addr, const uint16_t value, const uint16_t mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_write_masked_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t page, const uint16_t addr, const uint16_t value, const uint16_t mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_write_masked_page((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, page, addr, value, mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_write_masked_page(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t page, const uint16_t addr, const uint16_t value, const uint16_t mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_gpio_mode(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, const mesa_phy_gpio_mode_t mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_gpio_mode_t) == sizeof(mesa_phy_gpio_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_gpio_mode((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, *((const vtss_phy_gpio_mode_t *)&mode) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_gpio_mode(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, const mesa_phy_gpio_mode_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_gpio_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t * value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_gpio_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_gpio_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_gpio_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_gpio_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, gpio_no, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_gpio_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t gpio_no, mesa_bool_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
#if VTSS_PHY_OPT_VERIPHY
mesa_rc mesa_phy_veriphy_start(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_veriphy_start((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mode); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_veriphy_start(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_PHY_OPT_VERIPHY /* ag.rb:1989 */
#else
mesa_rc mesa_phy_veriphy_start(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
#if VTSS_PHY_OPT_VERIPHY
mesa_rc mesa_phy_veriphy_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_veriphy_result_t *const result)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_veriphy_result_t) == sizeof(mesa_phy_veriphy_result_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_veriphy_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_veriphy_result_t *)result /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_veriphy_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_veriphy_result_t *const result)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_PHY_OPT_VERIPHY /* ag.rb:1989 */
#else
mesa_rc mesa_phy_veriphy_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_veriphy_result_t *const result)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_led_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_mode_select_t led_mode_select)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_led_mode_select_t) == sizeof(mesa_phy_led_mode_select_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_led_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_led_mode_select_t *)&led_mode_select) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_led_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_mode_select_t led_mode_select)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_led_intensity_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_intensity intensity)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_led_intensity_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, intensity); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_led_intensity_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_intensity intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_led_intensity_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_led_intensity intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_led_intensity_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_led_intensity * intensity)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_led_intensity_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, intensity); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_led_intensity_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_led_intensity * intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_led_intensity_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_led_intensity * intensity)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_enhanced_led_control_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_enhanced_led_control_t conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_enhanced_led_control_t) == sizeof(mesa_phy_enhanced_led_control_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_enhanced_led_control_init((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_enhanced_led_control_t *)&conf) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_enhanced_led_control_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_enhanced_led_control_t conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_enhanced_led_control_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_enhanced_led_control_t conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
#if defined(VTSS_FEATURE_LED_POW_REDUC)
mesa_rc mesa_phy_enhanced_led_control_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_enhanced_led_control_t * conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_enhanced_led_control_t) == sizeof(mesa_phy_enhanced_led_control_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_enhanced_led_control_init_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_enhanced_led_control_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_enhanced_led_control_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_enhanced_led_control_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LED_POW_REDUC) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_enhanced_led_control_init_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_enhanced_led_control_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_coma_mode_disable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_coma_mode_disable((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_coma_mode_disable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_coma_mode_enable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_coma_mode_enable((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_coma_mode_enable(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_port_eee_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * eee_capable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_port_eee_capable((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, eee_capable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_port_eee_capable(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * eee_capable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_ena(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_eee_ena((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_eee_ena(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_eee_conf_t * conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_eee_conf_t) == sizeof(mesa_phy_eee_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_eee_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_eee_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_eee_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_eee_conf_t * conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_eee_conf_t conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_eee_conf_t) == sizeof(mesa_phy_eee_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_eee_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_eee_conf_t *)&conf) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_eee_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_eee_conf_t conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_power_save_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * rx_in_power_save_state, mesa_bool_t * tx_in_power_save_state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_eee_power_save_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, rx_in_power_save_state, tx_in_power_save_state); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_eee_power_save_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * rx_in_power_save_state, mesa_bool_t * tx_in_power_save_state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_eee_link_partner_advertisements_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * advertisement)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_eee_link_partner_advertisements_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, advertisement); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_eee_link_partner_advertisements_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * advertisement)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_event_t ev_mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_event_enable_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_event_t ev_mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t * ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_event_enable_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t * ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_squelch_workaround(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_squelch_workaround((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_squelch_workaround(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_csr_wr(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, const uint32_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_csr_wr((const vtss_inst_t)inst /* ag.rb:1870 */, page, port_no, target, csr_reg_addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_csr_wr(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, const uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_csr_rd(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_csr_rd((const vtss_inst_t)inst /* ag.rb:1870 */, page, port_no, target, csr_reg_addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_csr_rd(const mesa_inst_t inst, const uint16_t page, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_statistic_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_statistic_t * statistics)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_statistic_t) == sizeof(mesa_phy_statistic_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_statistic_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_statistic_t *)statistics /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_statistic_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_statistic_t * statistics)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_do_page_chk_set(const mesa_inst_t inst, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_do_page_chk_set((const vtss_inst_t)inst /* ag.rb:1870 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_do_page_chk_set(const mesa_inst_t inst, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_do_page_chk_get(const mesa_inst_t inst, mesa_bool_t * enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_do_page_chk_get((const vtss_inst_t)inst /* ag.rb:1870 */, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_do_page_chk_get(const mesa_inst_t inst, mesa_bool_t * enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t loopback)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_loopback_t) == sizeof(mesa_phy_loopback_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_loopback_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((vtss_phy_loopback_t *)&loopback) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_loopback_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t * loopback)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_loopback_t) == sizeof(mesa_phy_loopback_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_loopback_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_loopback_t *)loopback /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_loopback_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_loopback_t * loopback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_is_8051_crc_ok(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t code_length, uint16_t expected_crc)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_is_8051_crc_ok((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, code_length, expected_crc); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_is_8051_crc_ok(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t code_length, uint16_t expected_crc)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_cfg_ob_post0(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_cfg_ob_post0((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_cfg_ob_post0(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_cfg_ib_cterm(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ib_cterm_ena, const uint8_t ib_eq_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_cfg_ib_cterm((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ib_cterm_ena, ib_eq_mode); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_cfg_ib_cterm(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ib_cterm_ena, const uint8_t ib_eq_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes6g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_rcpll_status_t) == sizeof(mesa_rcpll_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_serdes6g_rcpll_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_rcpll_status_t *)rcpll_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_serdes6g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes1g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_rcpll_status_t) == sizeof(mesa_rcpll_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_serdes1g_rcpll_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_rcpll_status_t *)rcpll_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_serdes1g_rcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_rcpll_status_t * rcpll_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_lcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_lcpll_status_t * lcpll_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_lcpll_status_t) == sizeof(mesa_lcpll_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_lcpll_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_lcpll_status_t *)lcpll_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_lcpll_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_lcpll_status_t * lcpll_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
void mesa_phy_reg_decode_status(mesa_port_no_t port_no, uint16_t lp_auto_neg_advertisment_reg, uint16_t lp_1000base_t_status_reg, uint16_t mii_status_reg, const mesa_phy_conf_t phy_setup, mesa_port_status_t *const status)
{ /* ag.rb:1845 */
    vtss_phy_conf_t __phy_setup;

#ifdef __cplusplus
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    memset(&__phy_setup, 0, sizeof(__phy_setup)); /* ag.rb:1926 */; /* ag.rb:1965 */
    mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(&phy_setup, &__phy_setup) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_phy_reg_decode_status(port_no, lp_auto_neg_advertisment_reg, lp_1000base_t_status_reg, mii_status_reg, __phy_setup, (vtss_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_flowcontrol_decode_status(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t lp_auto_neg_advertisment_reg, const mesa_phy_conf_t phy_setup, mesa_port_status_t *const status)
{ /* ag.rb:1845 */
    vtss_phy_conf_t __phy_setup;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    memset(&__phy_setup, 0, sizeof(__phy_setup)); /* ag.rb:1926 */; /* ag.rb:1965 */
    __RC(mesa_conv_mesa_phy_conf_t_to_vtss_phy_conf_t(&phy_setup, &__phy_setup)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_phy_flowcontrol_decode_status((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, lp_auto_neg_advertisment_reg, __phy_setup, (vtss_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_flowcontrol_decode_status(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t lp_auto_neg_advertisment_reg, const mesa_phy_conf_t phy_setup, mesa_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_stat_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_debug_stat_print((const vtss_inst_t)inst /* ag.rb:1870 */, pr, port_no, print_hdr); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_debug_stat_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_warm_start_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_warm_start_failed_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_warm_start_failed_get(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_phyinfo_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_debug_phyinfo_print((const vtss_inst_t)inst /* ag.rb:1870 */, pr, port_no, print_hdr); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_debug_phyinfo_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_bool_t print_hdr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_debug_register_dump((const vtss_inst_t)inst /* ag.rb:1870 */, pr, clear, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_debug_register_dump(const mesa_inst_t inst, const mesa_debug_printf_t pr, mesa_bool_t clear, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_detect_base_ports(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_detect_base_ports((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_detect_base_ports(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ext_connector_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t lpback)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ext_connector_loopback((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, lpback); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ext_connector_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t lpback)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes_sgmii_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_serdes_sgmii_loopback((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mode); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_serdes_sgmii_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_serdes_fmedia_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_serdes_fmedia_loopback((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mode); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_serdes_fmedia_loopback(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_debug_regdump_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_port_no_t page_no, const mesa_bool_t print_hdr)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_debug_regdump_print((const vtss_inst_t)inst /* ag.rb:1870 */, pr, port_no, page_no, print_hdr); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_debug_regdump_print(const mesa_inst_t inst, const mesa_debug_printf_t pr, const mesa_port_no_t port_no, const mesa_port_no_t page_no, const mesa_bool_t print_hdr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_wol_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_wol_enable((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_wol_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_wol_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_wol_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_wol_conf_t) == sizeof(mesa_phy_wol_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_wol_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_wol_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_wol_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_wol_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_wol_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_wol_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_wol_conf_t) == sizeof(mesa_phy_wol_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_wol_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_wol_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_wol_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_wol_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_reset_lcpll(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_reset_lcpll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_reset_lcpll(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_post_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_post0, uint8_t * ob_post1)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_post_rd((vtss_inst_t)inst /* ag.rb:1870 */, port_no, ob_post0, ob_post1); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_sd6g_ob_post_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_post0, uint8_t * ob_post1)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_post_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_post0, const uint8_t ob_post1)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_post_wr((vtss_inst_t)inst /* ag.rb:1870 */, port_no, ob_post0, ob_post1); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_sd6g_ob_post_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_post0, const uint8_t ob_post1)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_lev_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_level)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_lev_rd((vtss_inst_t)inst /* ag.rb:1870 */, port_no, ob_level); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_sd6g_ob_lev_rd(mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t * ob_level)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_sd6g_ob_lev_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_level)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_sd6g_ob_lev_wr((vtss_inst_t)inst /* ag.rb:1870 */, port_no, ob_level); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_sd6g_ob_lev_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t ob_level)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mac_media_inhibit_odd_start(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t mac_inhibit, const mesa_bool_t media_inhibit)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_mac_media_inhibit_odd_start((vtss_inst_t)inst /* ag.rb:1870 */, port_no, mac_inhibit, media_inhibit); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_mac_media_inhibit_odd_start(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t mac_inhibit, const mesa_bool_t media_inhibit)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_fefi_get(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_fefi_mode_t * fefi)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_fefi_mode_t) == sizeof(mesa_fefi_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_fefi_get((vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_fefi_mode_t *)fefi /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_fefi_get(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_fefi_mode_t * fefi)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_fefi_set(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_fefi_mode_t fefi)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_fefi_mode_t) == sizeof(mesa_fefi_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_fefi_set((vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_fefi_mode_t *)&fefi) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_fefi_set(mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_fefi_mode_t fefi)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_fefi_detect(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * fefi_detect)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_fefi_detect((vtss_inst_t)inst /* ag.rb:1870 */, port_no, fefi_detect); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_fefi_detect(mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * fefi_detect)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mse_100m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mse)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_mse_100m_get((vtss_inst_t)inst /* ag.rb:1870 */, port_no, mse); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_mse_100m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mse)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_mse_1000m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mseA, uint32_t * mseB, uint32_t * mseC, uint32_t * mseD)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_mse_1000m_get((vtss_inst_t)inst /* ag.rb:1870 */, port_no, mseA, mseB, mseC, mseD); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_mse_1000m_get(mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t * mseA, uint32_t * mseB, uint32_t * mseC, uint32_t * mseD)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_read_tr_addr(mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t tr_addr, uint16_t * tr_lower, uint16_t * tr_upper)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_read_tr_addr((vtss_inst_t)inst /* ag.rb:1870 */, port_no, tr_addr, tr_lower, tr_upper); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_read_tr_addr(mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t tr_addr, uint16_t * tr_lower, uint16_t * tr_upper)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_is_viper_revB(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * is_viper_revB)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_is_viper_revB((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, is_viper_revB); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_is_viper_revB(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t * is_viper_revB)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_ext_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ext_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ext_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_firmware_update(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t *const fw, uint32_t *const len)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_firmware_update((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, fw, len); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_firmware_update(const mesa_inst_t inst, const mesa_port_no_t port_no, uint8_t *const fw, uint32_t *const len)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_macsec_csr_sd6g_rd(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_macsec_csr_sd6g_rd((vtss_inst_t)inst /* ag.rb:1870 */, port_no, target, csr_reg_addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_macsec_csr_sd6g_rd(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t * value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_macsec_csr_sd6g_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_macsec_csr_sd6g_wr((vtss_inst_t)inst /* ag.rb:1870 */, port_no, target, csr_reg_addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_macsec_csr_sd6g_wr(mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t target, const uint32_t csr_reg_addr, uint32_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_alt_clock_saved_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const saved)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_alt_clock_saved_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, saved); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_alt_clock_saved_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint32_t *const saved)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_alt_clock_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_alt_clock_mode_t) == sizeof(mesa_phy_ts_alt_clock_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_alt_clock_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_ts_alt_clock_mode_t *)phy_alt_clock_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_alt_clock_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_alt_clock_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_alt_clock_mode_t) == sizeof(mesa_phy_ts_alt_clock_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_alt_clock_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_ts_alt_clock_mode_t *)phy_alt_clock_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_alt_clock_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_alt_clock_mode_t *const phy_alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_pps_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_pps_conf_t) == sizeof(mesa_phy_ts_pps_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_pps_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_ts_pps_conf_t *)phy_pps_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_pps_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_pps_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_pps_conf_t) == sizeof(mesa_phy_ts_pps_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_pps_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_ts_pps_conf_t *)phy_pps_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_pps_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_pps_conf_t *const phy_pps_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_ingress_latency_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_ingress_latency_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_egress_latency_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_egress_latency_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_path_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const path_delay)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_path_delay_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, path_delay); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_path_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const path_delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_path_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const path_delay)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_path_delay_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, path_delay); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_path_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const path_delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_delay_asymmetry_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const delay_asym)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_delay_asymmetry_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, delay_asym); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_delay_asymmetry_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const delay_asym)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_delay_asymmetry_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const delay_asym)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_delay_asymmetry_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, delay_asym); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_delay_asymmetry_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const delay_asym)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_timestamp_t) == sizeof(mesa_phy_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ptptime_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ptptime_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_set_done(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_ptptime_set_done((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ptptime_set_done(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_arm(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_ptptime_arm((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ptptime_arm(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_timestamp_t) == sizeof(mesa_phy_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ptptime_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_load_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_timestamp_t) == sizeof(mesa_phy_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_load_ptptime_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_load_ptptime_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_sertod_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_sertod_conf_t *const sertod_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_sertod_conf_t) == sizeof(mesa_phy_ts_sertod_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_sertod_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_ts_sertod_conf_t *)sertod_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_sertod_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_sertod_conf_t *const sertod_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_sertod_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_sertod_conf_t *const sertod_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_sertod_conf_t) == sizeof(mesa_phy_ts_sertod_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_sertod_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_ts_sertod_conf_t *)sertod_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_sertod_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_sertod_conf_t *const sertod_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_loadpulse_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t *const delay)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_loadpulse_delay_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, delay); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_loadpulse_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint16_t *const delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_loadpulse_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const delay)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_loadpulse_delay_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, delay); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_loadpulse_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, uint16_t *const delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_clock_rateadj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_scaled_ppb_t *const adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_clock_rateadj_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_clock_rateadj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_scaled_ppb_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_clock_rateadj_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_scaled_ppb_t *const adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_clock_rateadj_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_clock_rateadj_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_scaled_ppb_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ptptime_adj1ns(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t incr)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_ptptime_adj1ns((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, incr); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ptptime_adj1ns(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t incr)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_timeofday_offset_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const int32_t offset)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_timeofday_offset_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, offset); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_timeofday_offset_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const int32_t offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ongoing_adjustment(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_todadj_status_t *const ongoing_adjustment)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_todadj_status_t) == sizeof(mesa_phy_ts_todadj_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ongoing_adjustment((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_ts_todadj_status_t *)ongoing_adjustment /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ongoing_adjustment(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_todadj_status_t *const ongoing_adjustment)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ltc_freq_synth_t) == sizeof(mesa_phy_ltc_freq_synth_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ltc_freq_synth_pulse_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_ltc_freq_synth_t *)ltc_freq_synthesis /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ltc_freq_synth_t) == sizeof(mesa_phy_ltc_freq_synth_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ltc_freq_synth_pulse_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_ltc_freq_synth_t *)ltc_freq_synthesis /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ltc_freq_synth_pulse_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ltc_freq_synth_t *const ltc_freq_synthesis)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_daisy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_daisy_chain_conf_t *const daisy_chain)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_daisy_chain_conf_t) == sizeof(mesa_phy_daisy_chain_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_daisy_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_daisy_chain_conf_t *)daisy_chain /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_daisy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */
#else
mesa_rc mesa_phy_daisy_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#ifdef VTSS_CHIP_CU_PHY
mesa_rc mesa_phy_daisy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_daisy_chain_conf_t *const daisy_chain)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_daisy_chain_conf_t) == sizeof(mesa_phy_daisy_chain_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_daisy_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_daisy_chain_conf_t *)daisy_chain /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_daisy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // VTSS_CHIP_CU_PHY /* ag.rb:1989 */
#else
mesa_rc mesa_phy_daisy_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_daisy_chain_conf_t *const daisy_chain)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_sig_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_sig_mask_t sig_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_fifo_sig_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, sig_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_fifo_sig_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_sig_mask_t sig_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_sig_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_fifo_sig_mask_t *const sig_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_fifo_sig_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, sig_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_fifo_sig_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_fifo_sig_mask_t *const sig_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_empty(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_fifo_empty((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_fifo_empty(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_read_install(const mesa_inst_t inst, mesa_phy_ts_fifo_read rd_cb, void * cntxt)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_fifo_read) == sizeof(mesa_phy_ts_fifo_read), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_fifo_read_install((const vtss_inst_t)inst /* ag.rb:1870 */, *((vtss_phy_ts_fifo_read *)&rd_cb) /* ag.rb:1872 */, cntxt); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_fifo_read_install(const mesa_inst_t inst, mesa_phy_ts_fifo_read rd_cb, void * cntxt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_fifo_read_cb_get(const mesa_inst_t inst, mesa_phy_ts_fifo_read * rd_cb, void ** cntxt)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_fifo_read) == sizeof(mesa_phy_ts_fifo_read), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_fifo_read_cb_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_phy_ts_fifo_read *)rd_cb /* ag.rb:1867 */, cntxt); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_fifo_read_cb_get(const mesa_inst_t inst, mesa_phy_ts_fifo_read * rd_cb, void ** cntxt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{ /* ag.rb:1845 */
    vtss_phy_ts_encap_t __encap_type;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_match_t) == sizeof(mesa_phy_ts_engine_flow_match_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(&encap_type, &__encap_type)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_phy_ts_ingress_engine_init((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, __encap_type, flow_st_index, flow_end_index, *((const vtss_phy_ts_engine_flow_match_t *)&flow_match_mode) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{ /* ag.rb:1845 */
    vtss_phy_ts_eng_init_conf_t __init_conf;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_phy_ts_ingress_engine_init_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, &__init_conf); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_phy_ts_eng_init_conf_t_to_mesa_phy_ts_eng_init_conf_t(&__init_conf, init_conf)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_ts_ingress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{ /* ag.rb:1845 */
    vtss_phy_ts_encap_t __encap_type;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_match_t) == sizeof(mesa_phy_ts_engine_flow_match_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_phy_ts_encap_t_to_vtss_phy_ts_encap_t(&encap_type, &__encap_type)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_phy_ts_egress_engine_init((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, __encap_type, flow_st_index, flow_end_index, *((const vtss_phy_ts_engine_flow_match_t *)&flow_match_mode) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_engine_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_encap_t encap_type, const uint8_t flow_st_index, const uint8_t flow_end_index, const mesa_phy_ts_engine_flow_match_t flow_match_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{ /* ag.rb:1845 */
    vtss_phy_ts_eng_init_conf_t __init_conf;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_phy_ts_egress_engine_init_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, &__init_conf); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_phy_ts_eng_init_conf_t_to_mesa_phy_ts_eng_init_conf_t(&__init_conf, init_conf)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_ts_egress_engine_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_eng_init_conf_t *const init_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_engine_clear(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (const vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (const vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_engine_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_flow_conf_t) == sizeof(mesa_phy_ts_engine_flow_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (vtss_phy_ts_engine_flow_conf_t *)flow_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_engine_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_flow_conf_t *const flow_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_action_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (const vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_ingress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_ingress_engine_action_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_ingress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_action_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (const vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_engine_action_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, const mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_egress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_action_t) == sizeof(mesa_phy_ts_engine_action_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_egress_engine_action_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, (vtss_phy_ts_engine_action_t *)action_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_egress_engine_action_get(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_engine_t eng_id, mesa_phy_ts_engine_action_t *const action_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_phy_ts_event_t ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_event_enable_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_event_enable_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_phy_ts_event_t ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_event_enable_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_event_enable_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, status); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_event_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_stats_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_stats_t *const statistics)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_stats_t) == sizeof(mesa_phy_ts_stats_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_stats_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_phy_ts_stats_t *)statistics /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_stats_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_stats_t *const statistics)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_correction_overflow_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const ingr_overflow, mesa_bool_t *const egr_overflow)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_correction_overflow_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ingr_overflow, egr_overflow); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_correction_overflow_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const ingr_overflow, mesa_bool_t *const egr_overflow)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_init_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_phy_ts_init_conf_t __conf;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    memset(&__conf, 0, sizeof(__conf)); /* ag.rb:1926 */; /* ag.rb:1965 */
    __RC(mesa_conv_mesa_phy_ts_init_conf_t_to_vtss_phy_ts_init_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_phy_ts_init((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_init(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_init_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const init_done, mesa_phy_ts_init_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_phy_ts_init_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_phy_ts_init_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, init_done, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_phy_ts_init_conf_t_to_mesa_phy_ts_init_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_phy_ts_init_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t *const init_done, mesa_phy_ts_init_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_nphase_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_nphase_sampler_t sampler, mesa_phy_ts_nphase_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_nphase_sampler_t) == sizeof(mesa_phy_ts_nphase_sampler_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_nphase_status_t) == sizeof(mesa_phy_ts_nphase_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_nphase_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((vtss_phy_ts_nphase_sampler_t *)&sampler) /* ag.rb:1872 */, (vtss_phy_ts_nphase_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_nphase_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_phy_ts_nphase_sampler_t sampler, mesa_phy_ts_nphase_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#if defined(VTSS_CHIP_10G_PHY)
mesa_rc mesa_phy_ts_phy_oper_mode_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_ts_phy_oper_mode_change((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_phy_oper_mode_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_CHIP_10G_PHY) /* ag.rb:1989 */
#else
mesa_rc mesa_phy_ts_phy_oper_mode_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_1588_csr_reg_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, const uint32_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_1588_csr_reg_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, blk_id, csr_address, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_1588_csr_reg_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, const uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_1588_csr_reg_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, uint32_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_phy_1588_csr_reg_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, blk_id, csr_address, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_1588_csr_reg_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint32_t blk_id, const uint16_t csr_address, uint32_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_viper_fifo_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_conf_t * fifo_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_fifo_conf_t) == sizeof(mesa_phy_ts_fifo_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_phy_ts_viper_fifo_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_phy_ts_fifo_conf_t *)fifo_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_viper_fifo_reset(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_phy_ts_fifo_conf_t * fifo_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_OPT_PHY_TIMESTAMP)
mesa_rc mesa_phy_ts_flow_clear_cf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ingress, const mesa_phy_ts_engine_t eng_id, uint8_t act_id, const mesa_phy_ts_ptp_message_type_t msgtype)
{ /* ag.rb:1845 */
    vtss_phy_ts_ptp_message_type_t __msgtype;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_phy_ts_engine_t) == sizeof(mesa_phy_ts_engine_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_phy_ts_ptp_message_type_t_to_vtss_phy_ts_ptp_message_type_t(&msgtype, &__msgtype)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_phy_ts_flow_clear_cf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ingress, *((const vtss_phy_ts_engine_t *)&eng_id) /* ag.rb:1872 */, act_id, __msgtype); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_phy_ts_flow_clear_cf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_bool_t ingress, const mesa_phy_ts_engine_t eng_id, uint8_t act_id, const mesa_phy_ts_ptp_message_type_t msgtype)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_OPT_PHY_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_clause_37_control_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_clause_37_control_t *const control)
{ /* ag.rb:1845 */
    vtss_port_clause_37_control_t __control;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_port_clause_37_control_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__control); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_port_clause_37_control_t_to_mesa_port_clause_37_control_t(&__control, control)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_port_clause_37_control_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_clause_37_control_t *const control)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_clause_37_control_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_clause_37_control_t *const control)
{ /* ag.rb:1845 */
    vtss_port_clause_37_control_t __control;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_clause_37_control_t_to_vtss_port_clause_37_control_t(control, &__control)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_port_clause_37_control_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__control); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_clause_37_control_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_clause_37_control_t *const control)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_conf_t_to_vtss_port_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_port_conf_t_to_mesa_port_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_status_t) == sizeof(mesa_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_counters_update(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_counters_update((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_counters_update(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_counters_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_counters_t *const counters)
{ /* ag.rb:1845 */
    vtss_port_counters_t __counters;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_port_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__counters); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_port_counters_t_to_mesa_port_counters_t(&__counters, counters)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_port_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_basic_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_basic_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_basic_counters_t) == sizeof(mesa_basic_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_basic_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_basic_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_basic_counters_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_basic_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_forward_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_forward_t *const forward)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_forward_t) == sizeof(mesa_port_forward_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_forward_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_port_forward_t *)forward /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_forward_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_forward_t *const forward)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_port_forward_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_forward_t forward)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_forward_t) == sizeof(mesa_port_forward_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_forward_state_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_port_forward_t *)&forward) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_forward_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_forward_t forward)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
#if defined(VTSS_FEATURE_PORT_IFH)
mesa_rc mesa_port_ifh_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_ifh_t *const conf)
{ /* ag.rb:1845 */
    vtss_port_ifh_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_ifh_t_to_vtss_port_ifh_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_port_ifh_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_ifh_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_ifh_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_IFH) /* ag.rb:1989 */
#else
mesa_rc mesa_port_ifh_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_ifh_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
#if defined(VTSS_FEATURE_PORT_IFH)
mesa_rc mesa_port_ifh_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_ifh_t *const conf)
{ /* ag.rb:1845 */
    vtss_port_ifh_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_port_ifh_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_port_ifh_t_to_mesa_port_ifh_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_port_ifh_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_ifh_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_IFH) /* ag.rb:1989 */
#else
mesa_rc mesa_port_ifh_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_ifh_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_miim_read(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_miim_controller_t miim_controller, const uint8_t miim_addr, const uint8_t addr, uint16_t *const value)
{ /* ag.rb:1845 */
    vtss_miim_controller_t __miim_controller;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_miim_controller_t_to_vtss_miim_controller_t(&miim_controller, &__miim_controller)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_miim_read((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, __miim_controller, miim_addr, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_miim_read(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_miim_controller_t miim_controller, const uint8_t miim_addr, const uint8_t addr, uint16_t *const value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PORT_CONTROL)
mesa_rc mesa_miim_write(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_miim_controller_t miim_controller, const uint8_t miim_addr, const uint8_t addr, const uint16_t value)
{ /* ag.rb:1845 */
    vtss_miim_controller_t __miim_controller;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_miim_controller_t_to_vtss_miim_controller_t(&miim_controller, &__miim_controller)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_miim_write((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, __miim_controller, miim_addr, addr, value); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_miim_write(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_miim_controller_t miim_controller, const uint8_t miim_addr, const uint8_t addr, const uint16_t value)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PORT_CONTROL) /* ag.rb:1989 */

mesa_rc mesa_port_mmd_read(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mmd, const uint16_t addr, uint16_t *const value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_mmd_read((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mmd, addr, value); /* ag.rb:1976*/ 
}

mesa_rc mesa_port_mmd_read_inc(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mmd, const uint16_t addr, uint16_t *const buf, uint8_t count)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_mmd_read_inc((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mmd, addr, buf, count); /* ag.rb:1976*/ 
}

mesa_rc mesa_port_mmd_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mmd, const uint16_t addr, const uint16_t value)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_mmd_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mmd, addr, value); /* ag.rb:1976*/ 
}

mesa_rc mesa_port_mmd_masked_write(const mesa_inst_t inst, const mesa_port_no_t port_no, const uint8_t mmd, const uint16_t addr, const uint16_t value, const uint16_t mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_port_mmd_masked_write((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, mmd, addr, value, mask); /* ag.rb:1976*/ 
}

mesa_rc mesa_mmd_read(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_miim_controller_t miim_controller, const uint8_t miim_addr, const uint8_t mmd, const uint16_t addr, uint16_t *const value)
{ /* ag.rb:1845 */
    vtss_miim_controller_t __miim_controller;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_miim_controller_t_to_vtss_miim_controller_t(&miim_controller, &__miim_controller)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_mmd_read((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, __miim_controller, miim_addr, mmd, addr, value); /* ag.rb:1976*/ 
}

mesa_rc mesa_mmd_write(const mesa_inst_t inst, const mesa_chip_no_t chip_no, const mesa_miim_controller_t miim_controller, const uint8_t miim_addr, const uint8_t mmd, const uint16_t addr, const uint16_t value)
{ /* ag.rb:1845 */
    vtss_miim_controller_t __miim_controller;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_miim_controller_t_to_vtss_miim_controller_t(&miim_controller, &__miim_controller)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_mmd_write((const vtss_inst_t)inst /* ag.rb:1870 */, chip_no, __miim_controller, miim_addr, mmd, addr, value); /* ag.rb:1976*/ 
}

#if defined(VTSS_FEATURE_10GBASE_KR_V2)
mesa_rc mesa_port_10g_kr_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_10g_kr_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_10g_kr_conf_t) == sizeof(mesa_port_10g_kr_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_10g_kr_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_port_10g_kr_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_10g_kr_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_10g_kr_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_10GBASE_KR_V2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_10GBASE_KR_V2)
mesa_rc mesa_port_10g_kr_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_10g_kr_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_10g_kr_conf_t) == sizeof(mesa_port_10g_kr_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_10g_kr_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_port_10g_kr_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_10g_kr_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_10g_kr_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_10GBASE_KR_V2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_10GBASE_KR_V2)
mesa_rc mesa_port_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_10g_kr_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_10g_kr_status_t) == sizeof(mesa_port_10g_kr_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_10g_kr_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_port_10g_kr_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_port_10g_kr_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_10g_kr_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_10GBASE_KR_V2) /* ag.rb:1989 */

mesa_rc mesa_port_test_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_port_test_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_test_conf_t) == sizeof(mesa_port_test_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_test_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_port_test_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

mesa_rc mesa_port_test_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_test_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_test_conf_t) == sizeof(mesa_port_test_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_test_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_port_test_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

mesa_rc mesa_port_serdes_debug_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_port_serdes_debug_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_port_serdes_debug_t) == sizeof(mesa_port_serdes_debug_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_port_serdes_debug_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_port_serdes_debug_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_qos_conf_set(const mesa_inst_t inst, const mesa_qos_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_qos_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_qos_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_qos_conf_t_to_vtss_qos_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_qos_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_conf_set(const mesa_inst_t inst, const mesa_qos_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_qos_conf_get(const mesa_inst_t inst, mesa_qos_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_qos_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_qos_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_qos_conf_t_to_mesa_qos_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_qos_conf_get(const mesa_inst_t inst, mesa_qos_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_qos_status_get(const mesa_inst_t inst, mesa_qos_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_status_t) == sizeof(mesa_qos_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_qos_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_status_get(const mesa_inst_t inst, mesa_qos_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_qos_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_qos_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_qos_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_qos_port_conf_t_to_mesa_qos_port_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_qos_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_qos_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_qos_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_qos_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_qos_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_qos_port_conf_t_to_vtss_qos_port_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_qos_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_qos_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
mesa_rc mesa_qce_init(const mesa_inst_t inst, const mesa_qce_type_t type, mesa_qce_t *const qce)
{ /* ag.rb:1845 */
    vtss_qce_t __qce;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qce_type_t) == sizeof(mesa_qce_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_qce_init((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_qce_type_t *)&type) /* ag.rb:1872 */, &__qce); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_qce_t_to_mesa_qce_t(&__qce, qce)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_qce_init(const mesa_inst_t inst, const mesa_qce_type_t type, mesa_qce_t *const qce)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
mesa_rc mesa_qos_ingress_map_init(const mesa_inst_t inst, const mesa_qos_ingress_map_key_t key, mesa_qos_ingress_map_t *const map)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_ingress_map_key_t) == sizeof(mesa_qos_ingress_map_key_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_ingress_map_t) == sizeof(mesa_qos_ingress_map_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_ingress_map_init((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_qos_ingress_map_key_t *)&key) /* ag.rb:1872 */, (vtss_qos_ingress_map_t *)map /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_ingress_map_init(const mesa_inst_t inst, const mesa_qos_ingress_map_key_t key, mesa_qos_ingress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_ingress_map_init(const mesa_inst_t inst, const mesa_qos_ingress_map_key_t key, mesa_qos_ingress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
mesa_rc mesa_qos_ingress_map_add(const mesa_inst_t inst, const mesa_qos_ingress_map_t *const map)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_ingress_map_t) == sizeof(mesa_qos_ingress_map_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_ingress_map_add((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_qos_ingress_map_t *)map /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_ingress_map_add(const mesa_inst_t inst, const mesa_qos_ingress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_ingress_map_add(const mesa_inst_t inst, const mesa_qos_ingress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
mesa_rc mesa_qos_ingress_map_del(const mesa_inst_t inst, const mesa_qos_ingress_map_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_qos_ingress_map_del((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_ingress_map_del(const mesa_inst_t inst, const mesa_qos_ingress_map_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_ingress_map_del(const mesa_inst_t inst, const mesa_qos_ingress_map_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
mesa_rc mesa_qos_ingress_map_del_all(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_qos_ingress_map_del_all((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_ingress_map_del_all(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_INGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_ingress_map_del_all(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
mesa_rc mesa_qos_egress_map_init(const mesa_inst_t inst, const mesa_qos_egress_map_key_t key, mesa_qos_egress_map_t *const map)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_egress_map_key_t) == sizeof(mesa_qos_egress_map_key_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_egress_map_t) == sizeof(mesa_qos_egress_map_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_egress_map_init((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_qos_egress_map_key_t *)&key) /* ag.rb:1872 */, (vtss_qos_egress_map_t *)map /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_egress_map_init(const mesa_inst_t inst, const mesa_qos_egress_map_key_t key, mesa_qos_egress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_egress_map_init(const mesa_inst_t inst, const mesa_qos_egress_map_key_t key, mesa_qos_egress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
mesa_rc mesa_qos_egress_map_add(const mesa_inst_t inst, const mesa_qos_egress_map_t *const map)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_egress_map_t) == sizeof(mesa_qos_egress_map_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_egress_map_add((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_qos_egress_map_t *)map /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_egress_map_add(const mesa_inst_t inst, const mesa_qos_egress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_egress_map_add(const mesa_inst_t inst, const mesa_qos_egress_map_t *const map)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
mesa_rc mesa_qos_egress_map_del(const mesa_inst_t inst, const mesa_qos_egress_map_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_qos_egress_map_del((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_egress_map_del(const mesa_inst_t inst, const mesa_qos_egress_map_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_egress_map_del(const mesa_inst_t inst, const mesa_qos_egress_map_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
mesa_rc mesa_qos_egress_map_del_all(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_qos_egress_map_del_all((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_egress_map_del_all(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_EGRESS_MAP) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_egress_map_del_all(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_ARCH_SERVAL)
mesa_rc mesa_qos_shaper_calibrate(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_qos_shaper_calibrate((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_shaper_calibrate(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) /* ag.rb:1989 */
#else
mesa_rc mesa_qos_shaper_calibrate(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_EVC_POLICERS)
mesa_rc mesa_evc_policer_conf_get(const mesa_inst_t inst, const mesa_evc_policer_id_t policer_id, mesa_evc_policer_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_evc_policer_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_evc_policer_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, policer_id, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_dlb_policer_conf_t_to_mesa_dlb_policer_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_evc_policer_conf_get(const mesa_inst_t inst, const mesa_evc_policer_id_t policer_id, mesa_evc_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_EVC_POLICERS) /* ag.rb:1989 */
#else
mesa_rc mesa_evc_policer_conf_get(const mesa_inst_t inst, const mesa_evc_policer_id_t policer_id, mesa_evc_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS)
#if defined(VTSS_FEATURE_EVC_POLICERS)
mesa_rc mesa_evc_policer_conf_set(const mesa_inst_t inst, const mesa_evc_policer_id_t policer_id, const mesa_evc_policer_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_evc_policer_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_dlb_policer_conf_t_to_vtss_dlb_policer_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_evc_policer_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, policer_id, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_evc_policer_conf_set(const mesa_inst_t inst, const mesa_evc_policer_id_t policer_id, const mesa_evc_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_EVC_POLICERS) /* ag.rb:1989 */
#else
mesa_rc mesa_evc_policer_conf_set(const mesa_inst_t inst, const mesa_evc_policer_id_t policer_id, const mesa_evc_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_auth_port_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_auth_state_t *const state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_auth_state_t) == sizeof(mesa_auth_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_auth_port_state_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_auth_state_t *)state /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_auth_port_state_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_auth_state_t *const state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_LAYER2)
mesa_rc mesa_auth_port_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_auth_state_t state)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_auth_state_t) == sizeof(mesa_auth_state_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_auth_port_state_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, *((const vtss_auth_state_t *)&state) /* ag.rb:1872 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_auth_port_state_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_auth_state_t state)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_LAYER2) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_acl_policer_conf_get(const mesa_inst_t inst, const mesa_acl_policer_no_t policer_no, mesa_acl_policer_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_acl_policer_conf_t) == sizeof(mesa_acl_policer_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_acl_policer_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, policer_no, (vtss_acl_policer_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_acl_policer_conf_get(const mesa_inst_t inst, const mesa_acl_policer_no_t policer_no, mesa_acl_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_acl_policer_conf_set(const mesa_inst_t inst, const mesa_acl_policer_no_t policer_no, const mesa_acl_policer_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_acl_policer_conf_t) == sizeof(mesa_acl_policer_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_acl_policer_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, policer_no, (const vtss_acl_policer_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_acl_policer_conf_set(const mesa_inst_t inst, const mesa_acl_policer_no_t policer_no, const mesa_acl_policer_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
mesa_rc mesa_acl_sip_conf_set(const mesa_inst_t inst, const mesa_acl_sip_idx_t idx, const mesa_acl_sip_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_acl_sip_conf_t) == sizeof(mesa_acl_sip_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_acl_sip_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, idx, (const vtss_acl_sip_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_acl_sip_conf_set(const mesa_inst_t inst, const mesa_acl_sip_idx_t idx, const mesa_acl_sip_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* ag.rb:1989 */
#else
mesa_rc mesa_acl_sip_conf_set(const mesa_inst_t inst, const mesa_acl_sip_idx_t idx, const mesa_acl_sip_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_acl_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_acl_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_acl_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_acl_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_acl_port_conf_t_to_mesa_acl_port_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_acl_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_acl_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_acl_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_acl_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_acl_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_acl_port_conf_t_to_vtss_acl_port_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_acl_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_acl_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_acl_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_acl_port_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_acl_port_counter_t *const counter)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_acl_port_counter_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, counter); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_acl_port_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_acl_port_counter_t *const counter)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_acl_port_counter_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_acl_port_counter_clear((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_acl_port_counter_clear(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_ace_init(const mesa_inst_t inst, const mesa_ace_type_t type, mesa_ace_t *const ace)
{ /* ag.rb:1845 */
    vtss_ace_t __ace;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ace_type_t) == sizeof(mesa_ace_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_ace_init((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_ace_type_t *)&type) /* ag.rb:1872 */, &__ace); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_ace_t_to_mesa_ace_t(&__ace, ace)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ace_init(const mesa_inst_t inst, const mesa_ace_type_t type, mesa_ace_t *const ace)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_ace_add(const mesa_inst_t inst, const mesa_ace_id_t ace_id_next, const mesa_ace_t *const ace)
{ /* ag.rb:1845 */
    vtss_ace_t __ace;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_ace_t_to_vtss_ace_t(ace, &__ace)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_ace_add((const vtss_inst_t)inst /* ag.rb:1870 */, ace_id_next, &__ace); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ace_add(const mesa_inst_t inst, const mesa_ace_id_t ace_id_next, const mesa_ace_t *const ace)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_ace_del(const mesa_inst_t inst, const mesa_ace_id_t ace_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ace_del((const vtss_inst_t)inst /* ag.rb:1870 */, ace_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ace_del(const mesa_inst_t inst, const mesa_ace_id_t ace_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_ace_counter_get(const mesa_inst_t inst, const mesa_ace_id_t ace_id, mesa_ace_counter_t *const counter)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ace_counter_get((const vtss_inst_t)inst /* ag.rb:1870 */, ace_id, counter); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ace_counter_get(const mesa_inst_t inst, const mesa_ace_id_t ace_id, mesa_ace_counter_t *const counter)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
mesa_rc mesa_ace_counter_clear(const mesa_inst_t inst, const mesa_ace_id_t ace_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ace_counter_clear((const vtss_inst_t)inst /* ag.rb:1870 */, ace_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ace_counter_clear(const mesa_inst_t inst, const mesa_ace_id_t ace_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_ACL)
#if defined(VTSS_ARCH_LUTON26)
mesa_rc mesa_ace_status_get(const mesa_inst_t inst, const mesa_ace_id_t ace_id, mesa_ace_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ace_status_t) == sizeof(mesa_ace_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ace_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, ace_id, (vtss_ace_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ace_status_get(const mesa_inst_t inst, const mesa_ace_id_t ace_id, mesa_ace_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_LUTON26) /* ag.rb:1989 */
#else
mesa_rc mesa_ace_status_get(const mesa_inst_t inst, const mesa_ace_id_t ace_id, mesa_ace_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_ACL) /* ag.rb:1989 */

void mesa_rleg_list_set(mesa_rleg_list_t * l, mesa_l3_rleg_id_t rleg, mesa_bool_t val)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_rleg_list_t) == sizeof(mesa_rleg_list_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_rleg_list_set((vtss_rleg_list_t *)l /* ag.rb:1867 */, rleg, val); /* ag.rb:1976*/ 
}

mesa_bool_t mesa_rleg_list_get(const mesa_rleg_list_t * l, mesa_l3_rleg_id_t rleg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_rleg_list_t) == sizeof(mesa_rleg_list_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_rleg_list_get((const vtss_rleg_list_t *)l /* ag.rb:1867 */, rleg); /* ag.rb:1976*/ 
}

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_hace_init(const mesa_inst_t inst, const mesa_ace_type_t type, mesa_hace_t *const hace)
{ /* ag.rb:1845 */
    vtss_hace_t __hace;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ace_type_t) == sizeof(mesa_ace_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    mesa_rc rc = vtss_hace_init((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_ace_type_t *)&type) /* ag.rb:1872 */, &__hace); /* ag.rb:1970 */

    __RC(mesa_conv_vtss_hace_t_to_mesa_hace_t(&__hace, hace)) /* ag.rb:1916 */; /* ag.rb:1972 */

    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_hace_init(const mesa_inst_t inst, const mesa_ace_type_t type, mesa_hace_t *const hace)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_HACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_hace_add(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id_next, const mesa_hace_t *const hace)
{ /* ag.rb:1845 */
    vtss_hace_t __hace;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_hacl_type_t) == sizeof(mesa_hacl_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_hace_t_to_vtss_hace_t(hace, &__hace)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_hace_add((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_hacl_type_t *)&type) /* ag.rb:1872 */, ace_id_next, &__hace); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_hace_add(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id_next, const mesa_hace_t *const hace)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_HACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_hace_del(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_hacl_type_t) == sizeof(mesa_hacl_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_hace_del((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_hacl_type_t *)&type) /* ag.rb:1872 */, ace_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_hace_del(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_HACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_hace_counter_get(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id, mesa_ace_counter_t *const counter)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_hacl_type_t) == sizeof(mesa_hacl_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_hace_counter_get((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_hacl_type_t *)&type) /* ag.rb:1872 */, ace_id, counter); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_hace_counter_get(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id, mesa_ace_counter_t *const counter)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_HACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_HACL)
mesa_rc mesa_hace_counter_clear(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_hacl_type_t) == sizeof(mesa_hacl_type_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_hace_counter_clear((const vtss_inst_t)inst /* ag.rb:1870 */, *((const vtss_hacl_type_t *)&type) /* ag.rb:1872 */, ace_id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_hace_counter_clear(const mesa_inst_t inst, const mesa_hacl_type_t type, const mesa_ace_id_t ace_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_HACL) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_synce_clock_out_set(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, const mesa_synce_clock_out_t *const conf)
{ /* ag.rb:1845 */
    vtss_synce_clock_out_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_synce_clock_out_t_to_vtss_synce_clock_out_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_synce_clock_out_set((const vtss_inst_t)inst /* ag.rb:1870 */, clk_port, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_synce_clock_out_set(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, const mesa_synce_clock_out_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_synce_clock_out_get(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, mesa_synce_clock_out_t *const conf)
{ /* ag.rb:1845 */
    vtss_synce_clock_out_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_synce_clock_out_get((const vtss_inst_t)inst /* ag.rb:1870 */, clk_port, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_synce_clock_out_t_to_mesa_synce_clock_out_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_synce_clock_out_get(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, mesa_synce_clock_out_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_synce_clock_in_set(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, const mesa_synce_clock_in_t *const conf)
{ /* ag.rb:1845 */
    vtss_synce_clock_in_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_synce_clock_in_t_to_vtss_synce_clock_in_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_synce_clock_in_set((const vtss_inst_t)inst /* ag.rb:1870 */, clk_port, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_synce_clock_in_set(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, const mesa_synce_clock_in_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_synce_clock_in_get(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, mesa_synce_clock_in_t *const conf)
{ /* ag.rb:1845 */
    vtss_synce_clock_in_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_synce_clock_in_get((const vtss_inst_t)inst /* ag.rb:1870 */, clk_port, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_synce_clock_in_t_to_mesa_synce_clock_in_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_synce_clock_in_get(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, mesa_synce_clock_in_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SYNCE)
mesa_rc mesa_synce_synce_station_clk_out_set(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, const mesa_synce_station_clock_out_t *const conf)
{ /* ag.rb:1845 */
    vtss_synce_station_clock_out_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_synce_station_clock_out_t_to_vtss_synce_station_clock_out_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_synce_synce_station_clk_out_set((const vtss_inst_t)inst /* ag.rb:1870 */, clk_port, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_synce_synce_station_clk_out_set(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, const mesa_synce_station_clock_out_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_SYNCE)
#if defined(VTSS_ARCH_SERVAL_T)     /* TBD_henrikb */
mesa_rc mesa_synce_synce_station_clk_out_get(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, mesa_synce_station_clock_out_t *const conf)
{ /* ag.rb:1845 */
    vtss_synce_station_clock_out_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_synce_synce_station_clk_out_get((const vtss_inst_t)inst /* ag.rb:1870 */, clk_port, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_synce_station_clock_out_t_to_mesa_synce_station_clock_out_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_synce_synce_station_clk_out_get(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, mesa_synce_station_clock_out_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL_T)     /* TBD_henrikb */ /* ag.rb:1989 */
#else
mesa_rc mesa_synce_synce_station_clk_out_get(const mesa_inst_t inst, const mesa_synce_clk_port_t clk_port, mesa_synce_station_clock_out_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_SYNCE) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_timeofday_set(const mesa_inst_t inst, const mesa_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_timeofday_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_set(const mesa_inst_t inst, const mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_domain_timeofday_set(const mesa_inst_t inst, const uint32_t domain, const mesa_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_domain_timeofday_set((const vtss_inst_t)inst /* ag.rb:1870 */, domain, (const vtss_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_domain_timeofday_set(const mesa_inst_t inst, const uint32_t domain, const mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_timeofday_set_delta(const mesa_inst_t inst, const mesa_timestamp_t * ts, mesa_bool_t negative)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_timeofday_set_delta((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_timestamp_t *)ts /* ag.rb:1867 */, negative); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_set_delta(const mesa_inst_t inst, const mesa_timestamp_t * ts, mesa_bool_t negative)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_domain_timeofday_set_delta(const mesa_inst_t inst, const uint32_t domain, const mesa_timestamp_t * ts, mesa_bool_t negative)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_domain_timeofday_set_delta((const vtss_inst_t)inst /* ag.rb:1870 */, domain, (const vtss_timestamp_t *)ts /* ag.rb:1867 */, negative); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_domain_timeofday_set_delta(const mesa_inst_t inst, const uint32_t domain, const mesa_timestamp_t * ts, mesa_bool_t negative)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_timeofday_offset_set(const mesa_inst_t inst, const int32_t offset)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_timeofday_offset_set((const vtss_inst_t)inst /* ag.rb:1870 */, offset); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_offset_set(const mesa_inst_t inst, const int32_t offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_domain_timeofday_offset_set(const mesa_inst_t inst, const uint32_t domain, const int32_t offset)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_domain_timeofday_offset_set((const vtss_inst_t)inst /* ag.rb:1870 */, domain, offset); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_domain_timeofday_offset_set(const mesa_inst_t inst, const uint32_t domain, const int32_t offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_adjtimer_one_sec(const mesa_inst_t inst, mesa_bool_t *const ongoing_adjustment)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_adjtimer_one_sec((const vtss_inst_t)inst /* ag.rb:1870 */, ongoing_adjustment); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_adjtimer_one_sec(const mesa_inst_t inst, mesa_bool_t *const ongoing_adjustment)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_ongoing_adjustment(const mesa_inst_t inst, mesa_bool_t *const ongoing_adjustment)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_ongoing_adjustment((const vtss_inst_t)inst /* ag.rb:1870 */, ongoing_adjustment); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_ongoing_adjustment(const mesa_inst_t inst, mesa_bool_t *const ongoing_adjustment)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_timeofday_get(const mesa_inst_t inst, mesa_timestamp_t *const ts, uint64_t *const tc)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_timeofday_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_timestamp_t *)ts /* ag.rb:1867 */, tc); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_get(const mesa_inst_t inst, mesa_timestamp_t *const ts, uint64_t *const tc)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_timeofday_raw(const mesa_inst_t inst, mesa_timestamp_t *const ts, uint64_t *const tc)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_timeofday_raw((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_timestamp_t *)ts /* ag.rb:1867 */, tc); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_raw(const mesa_inst_t inst, mesa_timestamp_t *const ts, uint64_t *const tc)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_domain_timeofday_get(const mesa_inst_t inst, const uint32_t domain, mesa_timestamp_t *const ts, uint64_t *const tc)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_domain_timeofday_get((const vtss_inst_t)inst /* ag.rb:1870 */, domain, (vtss_timestamp_t *)ts /* ag.rb:1867 */, tc); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_domain_timeofday_get(const mesa_inst_t inst, const uint32_t domain, mesa_timestamp_t *const ts, uint64_t *const tc)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_timeofday_next_pps_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_timeofday_next_pps_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_next_pps_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_timeofday_prev_pps_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_timeofday_prev_pps_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_prev_pps_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_domain_timeofday_next_pps_get(const mesa_inst_t inst, const uint32_t domain, mesa_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_domain_timeofday_next_pps_get((const vtss_inst_t)inst /* ag.rb:1870 */, domain, (vtss_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_domain_timeofday_next_pps_get(const mesa_inst_t inst, const uint32_t domain, mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_adjtimer_set(const mesa_inst_t inst, const int32_t adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_adjtimer_set((const vtss_inst_t)inst /* ag.rb:1870 */, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_adjtimer_set(const mesa_inst_t inst, const int32_t adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_adjtimer_get(const mesa_inst_t inst, int32_t *const adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_adjtimer_get((const vtss_inst_t)inst /* ag.rb:1870 */, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_adjtimer_get(const mesa_inst_t inst, int32_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_domain_adjtimer_set(const mesa_inst_t inst, const uint32_t domain, const int32_t adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_domain_adjtimer_set((const vtss_inst_t)inst /* ag.rb:1870 */, domain, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_domain_adjtimer_set(const mesa_inst_t inst, const uint32_t domain, const int32_t adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_domain_adjtimer_get(const mesa_inst_t inst, const uint32_t domain, int32_t *const adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_domain_adjtimer_get((const vtss_inst_t)inst /* ag.rb:1870 */, domain, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_domain_adjtimer_get(const mesa_inst_t inst, const uint32_t domain, int32_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_freq_offset_get(const mesa_inst_t inst, int32_t *const adj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_freq_offset_get((const vtss_inst_t)inst /* ag.rb:1870 */, adj); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_freq_offset_get(const mesa_inst_t inst, int32_t *const adj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */
mesa_rc mesa_ts_alt_clock_saved_get(const mesa_inst_t inst, uint64_t *const saved)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_alt_clock_saved_get((const vtss_inst_t)inst /* ag.rb:1870 */, saved); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_alt_clock_saved_get(const mesa_inst_t inst, uint64_t *const saved)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */ /* ag.rb:1989 */
#else
mesa_rc mesa_ts_alt_clock_saved_get(const mesa_inst_t inst, uint64_t *const saved)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */
#if defined(VTSS_ARCH_SERVAL)
mesa_rc mesa_ts_alt_clock_saved_timeofday_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_alt_clock_saved_timeofday_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_alt_clock_saved_timeofday_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_alt_clock_saved_timeofday_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */ /* ag.rb:1989 */
#else
mesa_rc mesa_ts_alt_clock_saved_timeofday_get(const mesa_inst_t inst, mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */
mesa_rc mesa_ts_alt_clock_mode_set(const mesa_inst_t inst, const mesa_ts_alt_clock_mode_t *const alt_clock_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_alt_clock_mode_t) == sizeof(mesa_ts_alt_clock_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_alt_clock_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_ts_alt_clock_mode_t *)alt_clock_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_alt_clock_mode_set(const mesa_inst_t inst, const mesa_ts_alt_clock_mode_t *const alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */ /* ag.rb:1989 */
#else
mesa_rc mesa_ts_alt_clock_mode_set(const mesa_inst_t inst, const mesa_ts_alt_clock_mode_t *const alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */
mesa_rc mesa_ts_alt_clock_mode_get(const mesa_inst_t inst, mesa_ts_alt_clock_mode_t *const alt_clock_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_alt_clock_mode_t) == sizeof(mesa_ts_alt_clock_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_alt_clock_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_ts_alt_clock_mode_t *)alt_clock_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_alt_clock_mode_get(const mesa_inst_t inst, mesa_ts_alt_clock_mode_t *const alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */ /* ag.rb:1989 */
#else
mesa_rc mesa_ts_alt_clock_mode_get(const mesa_inst_t inst, mesa_ts_alt_clock_mode_t *const alt_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */
mesa_rc mesa_ts_timeofday_next_pps_set(const mesa_inst_t inst, const mesa_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_timeofday_next_pps_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_timeofday_next_pps_set(const mesa_inst_t inst, const mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_SERVAL) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* TBD_henrikb */ /* ag.rb:1989 */
#else
mesa_rc mesa_ts_timeofday_next_pps_set(const mesa_inst_t inst, const mesa_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_external_clock_mode_get(const mesa_inst_t inst, mesa_ts_ext_clock_mode_t *const ext_clock_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_ext_clock_mode_t) == sizeof(mesa_ts_ext_clock_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_external_clock_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_ts_ext_clock_mode_t *)ext_clock_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_external_clock_mode_get(const mesa_inst_t inst, mesa_ts_ext_clock_mode_t *const ext_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_external_clock_mode_set(const mesa_inst_t inst, const mesa_ts_ext_clock_mode_t *const ext_clock_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_ext_clock_mode_t) == sizeof(mesa_ts_ext_clock_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_external_clock_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_ts_ext_clock_mode_t *)ext_clock_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_external_clock_mode_set(const mesa_inst_t inst, const mesa_ts_ext_clock_mode_t *const ext_clock_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
mesa_rc mesa_ts_external_io_mode_get(const mesa_inst_t inst, const uint32_t io, mesa_ts_ext_io_mode_t *const ext_io_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_ext_io_mode_t) == sizeof(mesa_ts_ext_io_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_external_io_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, io, (vtss_ts_ext_io_mode_t *)ext_io_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_external_io_mode_get(const mesa_inst_t inst, const uint32_t io, mesa_ts_ext_io_mode_t *const ext_io_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_external_io_mode_get(const mesa_inst_t inst, const uint32_t io, mesa_ts_ext_io_mode_t *const ext_io_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
mesa_rc mesa_ts_external_io_mode_set(const mesa_inst_t inst, const uint32_t io, const mesa_ts_ext_io_mode_t *const ext_io_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_ext_io_mode_t) == sizeof(mesa_ts_ext_io_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_external_io_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, io, (const vtss_ts_ext_io_mode_t *)ext_io_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_external_io_mode_set(const mesa_inst_t inst, const uint32_t io, const mesa_ts_ext_io_mode_t *const ext_io_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_external_io_mode_set(const mesa_inst_t inst, const uint32_t io, const mesa_ts_ext_io_mode_t *const ext_io_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
mesa_rc mesa_ts_saved_timeofday_get(const mesa_inst_t inst, const uint32_t io, mesa_timestamp_t *const ts, uint64_t *const tc)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_timestamp_t) == sizeof(mesa_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_saved_timeofday_get((const vtss_inst_t)inst /* ag.rb:1870 */, io, (vtss_timestamp_t *)ts /* ag.rb:1867 */, tc); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_saved_timeofday_get(const mesa_inst_t inst, const uint32_t io, mesa_timestamp_t *const ts, uint64_t *const tc)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_saved_timeofday_get(const mesa_inst_t inst, const uint32_t io, mesa_timestamp_t *const ts, uint64_t *const tc)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
mesa_rc mesa_ts_output_clock_edge_offset_get(const mesa_inst_t inst, const uint32_t io, uint32_t *const offset)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_output_clock_edge_offset_get((const vtss_inst_t)inst /* ag.rb:1870 */, io, offset); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_output_clock_edge_offset_get(const mesa_inst_t inst, const uint32_t io, uint32_t *const offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_output_clock_edge_offset_get(const mesa_inst_t inst, const uint32_t io, uint32_t *const offset)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_external_clock_saved_get(const mesa_inst_t inst, uint32_t *const saved)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_external_clock_saved_get((const vtss_inst_t)inst /* ag.rb:1870 */, saved); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_external_clock_saved_get(const mesa_inst_t inst, uint32_t *const saved)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_ingress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const ingress_latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_ingress_latency_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ingress_latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_ingress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const ingress_latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_ingress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const ingress_latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_ingress_latency_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, ingress_latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_ingress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const ingress_latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_p2p_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const p2p_delay)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_p2p_delay_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, p2p_delay); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_p2p_delay_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const p2p_delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_p2p_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const p2p_delay)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_p2p_delay_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, p2p_delay); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_p2p_delay_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const p2p_delay)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_egress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const egress_latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_egress_latency_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, egress_latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_egress_latency_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const egress_latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_egress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const egress_latency)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_egress_latency_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, egress_latency); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_egress_latency_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const egress_latency)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_delay_asymmetry_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const delay_asymmetry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_delay_asymmetry_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, delay_asymmetry); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_delay_asymmetry_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_timeinterval_t *const delay_asymmetry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_delay_asymmetry_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const delay_asymmetry)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_delay_asymmetry_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, delay_asymmetry); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_delay_asymmetry_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_timeinterval_t *const delay_asymmetry)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_operation_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ts_operation_mode_t *const mode)
{ /* ag.rb:1845 */
    vtss_ts_operation_mode_t __mode;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_ts_operation_mode_t_to_vtss_ts_operation_mode_t(mode, &__mode)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_ts_operation_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__mode); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_operation_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ts_operation_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_operation_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ts_operation_mode_t *const mode)
{ /* ag.rb:1845 */
    vtss_ts_operation_mode_t __mode;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ts_operation_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__mode); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_ts_operation_mode_t_to_mesa_ts_operation_mode_t(&__mode, mode)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ts_operation_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ts_operation_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_internal_mode_set(const mesa_inst_t inst, const mesa_ts_internal_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_internal_mode_t) == sizeof(mesa_ts_internal_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_internal_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_ts_internal_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_internal_mode_set(const mesa_inst_t inst, const mesa_ts_internal_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_internal_mode_get(const mesa_inst_t inst, mesa_ts_internal_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_internal_mode_t) == sizeof(mesa_ts_internal_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_internal_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_ts_internal_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_internal_mode_get(const mesa_inst_t inst, mesa_ts_internal_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_tx_timestamp_update(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_tx_timestamp_update((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_tx_timestamp_update(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_rx_timestamp_get(const mesa_inst_t inst, const mesa_ts_id_t *const ts_id, mesa_ts_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_id_t) == sizeof(mesa_ts_id_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_timestamp_t) == sizeof(mesa_ts_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_rx_timestamp_get((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_ts_id_t *)ts_id /* ag.rb:1867 */, (vtss_ts_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_rx_timestamp_get(const mesa_inst_t inst, const mesa_ts_id_t *const ts_id, mesa_ts_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_rx_timestamp_id_release(const mesa_inst_t inst, const mesa_ts_id_t *const ts_id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_id_t) == sizeof(mesa_ts_id_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_rx_timestamp_id_release((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_ts_id_t *)ts_id /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_rx_timestamp_id_release(const mesa_inst_t inst, const mesa_ts_id_t *const ts_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_rx_master_timestamp_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ts_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_timestamp_t) == sizeof(mesa_ts_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_rx_master_timestamp_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ts_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_rx_master_timestamp_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ts_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined (VTSS_ARCH_SERVAL_CE)
mesa_rc mesa_oam_timestamp_get(const mesa_inst_t inst, const mesa_oam_ts_id_t *const id, mesa_oam_ts_timestamp_t *const ts)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_oam_ts_id_t) == sizeof(mesa_oam_ts_id_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_oam_ts_timestamp_t) == sizeof(mesa_oam_ts_timestamp_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_oam_timestamp_get((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_oam_ts_id_t *)id /* ag.rb:1867 */, (vtss_oam_ts_timestamp_t *)ts /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_oam_timestamp_get(const mesa_inst_t inst, const mesa_oam_ts_id_t *const id, mesa_oam_ts_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined (VTSS_ARCH_SERVAL_CE) /* ag.rb:1989 */
#else
mesa_rc mesa_oam_timestamp_get(const mesa_inst_t inst, const mesa_oam_ts_id_t *const id, mesa_oam_ts_timestamp_t *const ts)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_tx_timestamp_idx_alloc(const mesa_inst_t inst, const mesa_ts_timestamp_alloc_t *const alloc_parm, mesa_ts_id_t *const ts_id)
{ /* ag.rb:1845 */
    vtss_ts_timestamp_alloc_t __alloc_parm;

#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_id_t) == sizeof(mesa_ts_id_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    __RC(mesa_conv_mesa_ts_timestamp_alloc_t_to_vtss_ts_timestamp_alloc_t(alloc_parm, &__alloc_parm)) /* ag.rb:1916 */; /* ag.rb:1965 */

    return vtss_tx_timestamp_idx_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, &__alloc_parm, (vtss_ts_id_t *)ts_id /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_tx_timestamp_idx_alloc(const mesa_inst_t inst, const mesa_ts_timestamp_alloc_t *const alloc_parm, mesa_ts_id_t *const ts_id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_timestamp_age(const mesa_inst_t inst)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_timestamp_age((const vtss_inst_t)inst /* ag.rb:1870 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_timestamp_age(const mesa_inst_t inst)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_status_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_status_change((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_status_change(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
mesa_rc mesa_ts_autoresp_dom_cfg_set(const mesa_inst_t inst, const uint8_t domain, const mesa_ts_autoresp_dom_cfg_t *const cfg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_autoresp_dom_cfg_t) == sizeof(mesa_ts_autoresp_dom_cfg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_autoresp_dom_cfg_set((const vtss_inst_t)inst /* ag.rb:1870 */, domain, (const vtss_ts_autoresp_dom_cfg_t *)cfg /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_autoresp_dom_cfg_set(const mesa_inst_t inst, const uint8_t domain, const mesa_ts_autoresp_dom_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_autoresp_dom_cfg_set(const mesa_inst_t inst, const uint8_t domain, const mesa_ts_autoresp_dom_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
mesa_rc mesa_ts_autoresp_dom_cfg_get(const mesa_inst_t inst, const uint8_t domain, mesa_ts_autoresp_dom_cfg_t *const cfg)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ts_autoresp_dom_cfg_t) == sizeof(mesa_ts_autoresp_dom_cfg_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_autoresp_dom_cfg_get((const vtss_inst_t)inst /* ag.rb:1870 */, domain, (vtss_ts_autoresp_dom_cfg_t *)cfg /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_autoresp_dom_cfg_get(const mesa_inst_t inst, const uint8_t domain, mesa_ts_autoresp_dom_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_autoresp_dom_cfg_get(const mesa_inst_t inst, const uint8_t domain, mesa_ts_autoresp_dom_cfg_t *const cfg)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
mesa_rc mesa_ts_smac_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_mac_t *const smac)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_mac_t) == sizeof(mesa_mac_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_smac_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_mac_t *)smac /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_smac_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_mac_t *const smac)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_smac_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_mac_t *const smac)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
#if defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
mesa_rc mesa_ts_smac_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_mac_t *const smac)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_mac_t) == sizeof(mesa_mac_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ts_smac_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_mac_t *)smac /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_smac_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_mac_t *const smac)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined (VTSS_FEATURE_DELAY_REQ_AUTO_RESP) /* ag.rb:1989 */
#else
mesa_rc mesa_ts_smac_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_mac_t *const smac)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_TIMESTAMP)
mesa_rc mesa_ts_seq_cnt_get(const mesa_inst_t inst, const uint32_t sec_cntr, uint16_t *const cnt_val)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ts_seq_cnt_get((const vtss_inst_t)inst /* ag.rb:1870 */, sec_cntr, cnt_val); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ts_seq_cnt_get(const mesa_inst_t inst, const uint32_t sec_cntr, uint16_t *const cnt_val)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_TIMESTAMP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_cstream_conf_get(const mesa_inst_t inst, const mesa_frer_cstream_id_t id, mesa_frer_stream_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_frer_stream_conf_t) == sizeof(mesa_frer_stream_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_frer_cstream_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, (vtss_frer_stream_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_cstream_conf_get(const mesa_inst_t inst, const mesa_frer_cstream_id_t id, mesa_frer_stream_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_cstream_conf_set(const mesa_inst_t inst, const mesa_frer_cstream_id_t id, const mesa_frer_stream_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_frer_stream_conf_t) == sizeof(mesa_frer_stream_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_frer_cstream_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, (const vtss_frer_stream_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_cstream_conf_set(const mesa_inst_t inst, const mesa_frer_cstream_id_t id, const mesa_frer_stream_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_cstream_cnt_get(const mesa_inst_t inst, const mesa_frer_cstream_id_t id, mesa_frer_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_frer_counters_t) == sizeof(mesa_frer_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_frer_cstream_cnt_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, (vtss_frer_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_cstream_cnt_get(const mesa_inst_t inst, const mesa_frer_cstream_id_t id, mesa_frer_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_cstream_cnt_clear(const mesa_inst_t inst, const mesa_frer_cstream_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_frer_cstream_cnt_clear((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_cstream_cnt_clear(const mesa_inst_t inst, const mesa_frer_cstream_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_mstream_alloc(const mesa_inst_t inst, const mesa_port_list_t * port_list, mesa_frer_mstream_id_t *const id)
{ /* ag.rb:1845 */
    BOOL __port_list[VTSS_PORTS];
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_port_list_t_to_uint8_t(port_list, __port_list)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_frer_mstream_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, __port_list, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_mstream_alloc(const mesa_inst_t inst, const mesa_port_list_t * port_list, mesa_frer_mstream_id_t *const id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_mstream_free(const mesa_inst_t inst, const mesa_frer_mstream_id_t id)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_frer_mstream_free((const vtss_inst_t)inst /* ag.rb:1870 */, id); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_mstream_free(const mesa_inst_t inst, const mesa_frer_mstream_id_t id)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_mstream_conf_get(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no, mesa_frer_stream_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_frer_stream_conf_t) == sizeof(mesa_frer_stream_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_frer_mstream_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, port_no, (vtss_frer_stream_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_mstream_conf_get(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no, mesa_frer_stream_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_mstream_conf_set(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no, const mesa_frer_stream_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_frer_stream_conf_t) == sizeof(mesa_frer_stream_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_frer_mstream_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, port_no, (const vtss_frer_stream_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_mstream_conf_set(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no, const mesa_frer_stream_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_mstream_cnt_get(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no, mesa_frer_counters_t *const counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_frer_counters_t) == sizeof(mesa_frer_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_frer_mstream_cnt_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, port_no, (vtss_frer_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_mstream_cnt_get(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no, mesa_frer_counters_t *const counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_FRER)
mesa_rc mesa_frer_mstream_cnt_clear(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_frer_mstream_cnt_clear((const vtss_inst_t)inst /* ag.rb:1870 */, id, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_frer_mstream_cnt_clear(const mesa_inst_t inst, const mesa_frer_mstream_id_t id, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_FRER) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PSFP)
mesa_rc mesa_psfp_gcl_conf_get(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, const uint32_t max_cnt, mesa_psfp_gce_t *const gcl, uint32_t *const gce_cnt)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_psfp_gce_t) == sizeof(mesa_psfp_gce_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_psfp_gcl_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, max_cnt, (vtss_psfp_gce_t *)gcl /* ag.rb:1867 */, gce_cnt); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_psfp_gcl_conf_get(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, const uint32_t max_cnt, mesa_psfp_gce_t *const gcl, uint32_t *const gce_cnt)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PSFP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PSFP)
mesa_rc mesa_psfp_gcl_conf_set(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, const uint32_t gce_cnt, const mesa_psfp_gce_t *const gcl)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_psfp_gce_t) == sizeof(mesa_psfp_gce_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_psfp_gcl_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, gce_cnt, (const vtss_psfp_gce_t *)gcl /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_psfp_gcl_conf_set(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, const uint32_t gce_cnt, const mesa_psfp_gce_t *const gcl)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PSFP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PSFP)
mesa_rc mesa_psfp_gate_conf_get(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, mesa_psfp_gate_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_psfp_gate_conf_t) == sizeof(mesa_psfp_gate_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_psfp_gate_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, (vtss_psfp_gate_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_psfp_gate_conf_get(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, mesa_psfp_gate_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PSFP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PSFP)
mesa_rc mesa_psfp_gate_conf_set(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, const mesa_psfp_gate_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_psfp_gate_conf_t) == sizeof(mesa_psfp_gate_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_psfp_gate_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, (const vtss_psfp_gate_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_psfp_gate_conf_set(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, const mesa_psfp_gate_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PSFP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PSFP)
mesa_rc mesa_psfp_gate_status_get(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, mesa_psfp_gate_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_psfp_gate_status_t) == sizeof(mesa_psfp_gate_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_psfp_gate_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, (vtss_psfp_gate_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_psfp_gate_status_get(const mesa_inst_t inst, const mesa_psfp_gate_id_t id, mesa_psfp_gate_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PSFP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PSFP)
mesa_rc mesa_psfp_filter_conf_get(const mesa_inst_t inst, const mesa_psfp_filter_id_t id, mesa_psfp_filter_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_psfp_filter_conf_t) == sizeof(mesa_psfp_filter_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_psfp_filter_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, id, (vtss_psfp_filter_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_psfp_filter_conf_get(const mesa_inst_t inst, const mesa_psfp_filter_id_t id, mesa_psfp_filter_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PSFP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_PSFP)
mesa_rc mesa_psfp_filter_conf_set(const mesa_inst_t inst, const mesa_psfp_filter_id_t id, const mesa_psfp_filter_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_psfp_filter_conf_t) == sizeof(mesa_psfp_filter_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_psfp_filter_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, id, (const vtss_psfp_filter_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_psfp_filter_conf_set(const mesa_inst_t inst, const mesa_psfp_filter_id_t id, const mesa_psfp_filter_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_PSFP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_TAS)
mesa_rc mesa_qos_tas_conf_get(const mesa_inst_t inst, mesa_qos_tas_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_tas_conf_t) == sizeof(mesa_qos_tas_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_tas_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, (vtss_qos_tas_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_tas_conf_get(const mesa_inst_t inst, mesa_qos_tas_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_TAS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_TAS)
mesa_rc mesa_qos_tas_conf_set(const mesa_inst_t inst, const mesa_qos_tas_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_tas_conf_t) == sizeof(mesa_qos_tas_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_tas_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_qos_tas_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_tas_conf_set(const mesa_inst_t inst, const mesa_qos_tas_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_TAS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_TAS)
mesa_rc mesa_qos_tas_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_tas_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_qos_tas_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_qos_tas_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_qos_tas_port_conf_t_to_mesa_qos_tas_port_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_qos_tas_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_tas_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_TAS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_TAS)
mesa_rc mesa_qos_tas_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_qos_tas_port_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_qos_tas_port_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    vtss_qos_tas_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf);  /* ag.rb:1962 */ // get-before-set
    __RC(mesa_conv_mesa_qos_tas_port_conf_t_to_vtss_qos_tas_port_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_qos_tas_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_tas_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_qos_tas_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_TAS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_TAS)
mesa_rc mesa_qos_tas_port_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_tas_port_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_tas_port_status_t) == sizeof(mesa_qos_tas_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_tas_port_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_qos_tas_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_tas_port_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_tas_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_TAS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
mesa_rc mesa_qos_fp_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_fp_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_fp_port_conf_t) == sizeof(mesa_qos_fp_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_fp_port_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_qos_fp_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_fp_port_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_fp_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
mesa_rc mesa_qos_fp_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_qos_fp_port_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_fp_port_conf_t) == sizeof(mesa_qos_fp_port_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_fp_port_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_qos_fp_port_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_fp_port_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_qos_fp_port_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
mesa_rc mesa_qos_fp_port_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_fp_port_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_qos_fp_port_status_t) == sizeof(mesa_qos_fp_port_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_qos_fp_port_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_qos_fp_port_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_qos_fp_port_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_qos_fp_port_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_vop_conf_set(const mesa_inst_t inst, const mesa_vop_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_vop_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_vop_conf_t_to_vtss_vop_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_vop_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_vop_conf_set(const mesa_inst_t inst, const mesa_vop_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_vop_conf_get(const mesa_inst_t inst, mesa_vop_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_vop_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_vop_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_vop_conf_t_to_mesa_vop_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_vop_conf_get(const mesa_inst_t inst, mesa_vop_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_alloc(const mesa_inst_t inst, const mesa_voe_allocation_t *const param, mesa_voe_idx_t *const voe_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_allocation_t) == sizeof(mesa_voe_allocation_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_voe_allocation_t *)param /* ag.rb:1867 */, voe_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_alloc(const mesa_inst_t inst, const mesa_voe_allocation_t *const param, mesa_voe_idx_t *const voe_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_free(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_free((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_free(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_voe_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_voe_conf_t_to_vtss_voe_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_voe_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_voe_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_conf_t_to_mesa_voe_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_cc_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_voe_cc_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_voe_cc_conf_t_to_vtss_voe_cc_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_voe_cc_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_cc_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_cc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_cc_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_voe_cc_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_cc_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_cc_conf_t_to_mesa_voe_cc_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_cc_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_cc_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_rdi_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_bool_t rdi)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_cc_rdi_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, rdi); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_cc_rdi_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_bool_t rdi)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_rdi_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_bool_t *const rdi)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_cc_rdi_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, rdi); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_cc_rdi_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_bool_t *const rdi)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_cpu_copy_next_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_cc_cpu_copy_next_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_cc_cpu_copy_next_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lt_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_lt_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_lt_conf_t) == sizeof(mesa_voe_lt_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_lt_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, (const vtss_voe_lt_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_lt_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_lt_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lt_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lt_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_lt_conf_t) == sizeof(mesa_voe_lt_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_lt_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, (vtss_voe_lt_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_lt_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lt_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lb_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_lb_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_voe_lb_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_voe_lb_conf_t_to_vtss_voe_lb_conf_t(conf, &__conf)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_voe_lb_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__conf); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_lb_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_lb_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lb_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lb_conf_t *const conf)
{ /* ag.rb:1845 */
    vtss_voe_lb_conf_t __conf;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_lb_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__conf); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_lb_conf_t_to_mesa_voe_lb_conf_t(&__conf, conf)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_lb_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lb_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_laps_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_laps_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_laps_conf_t) == sizeof(mesa_voe_laps_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_laps_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, (const vtss_voe_laps_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_laps_conf_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const mesa_voe_laps_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_laps_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_laps_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_laps_conf_t) == sizeof(mesa_voe_laps_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_laps_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, (vtss_voe_laps_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_laps_conf_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_laps_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_status_t *const status)
{ /* ag.rb:1845 */
    vtss_voe_status_t __status;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__status); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_status_t_to_mesa_voe_status_t(&__status, status)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_counters_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_counters_t * counters)
{ /* ag.rb:1845 */
    vtss_voe_counters_t __counters;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__counters); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_counters_t_to_mesa_voe_counters_t(&__counters, counters)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_counters_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_counters_t * counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_counters_clear(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_counters_clear(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_cc_status_t * status)
{ /* ag.rb:1845 */
    vtss_voe_cc_status_t __status;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_cc_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__status); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_cc_status_t_to_mesa_voe_cc_status_t(&__status, status)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_cc_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_cc_status_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_counters_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_cc_counters_t * counters)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_cc_counters_t) == sizeof(mesa_voe_cc_counters_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_cc_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, (vtss_voe_cc_counters_t *)counters /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_cc_counters_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_cc_counters_t * counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_cc_counters_clear(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_cc_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_cc_counters_clear(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lt_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lt_status_t * status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_lt_status_t) == sizeof(mesa_voe_lt_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_lt_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, (vtss_voe_lt_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_lt_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lt_status_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lb_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lb_status_t * status)
{ /* ag.rb:1845 */
    vtss_voe_lb_status_t __status;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_lb_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__status); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_lb_status_t_to_mesa_voe_lb_status_t(&__status, status)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_lb_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lb_status_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lb_counters_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lb_counters_t * counters)
{ /* ag.rb:1845 */
    vtss_voe_lb_counters_t __counters;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_voe_lb_counters_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, &__counters); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_voe_lb_counters_t_to_mesa_voe_lb_counters_t(&__counters, counters)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_voe_lb_counters_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_lb_counters_t * counters)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_lb_counters_clear(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_lb_counters_clear((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_lb_counters_clear(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_laps_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_laps_status_t * status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voe_laps_status_t) == sizeof(mesa_voe_laps_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voe_laps_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, (vtss_voe_laps_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_laps_status_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, mesa_voe_laps_status_t * status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_event_active_get(const mesa_inst_t inst, const uint32_t active_size, uint32_t *const active)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_event_active_get((const vtss_inst_t)inst /* ag.rb:1870 */, active_size, active); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_event_active_get(const mesa_inst_t inst, const uint32_t active_size, uint32_t *const active)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_event_mask_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const uint32_t mask, const mesa_bool_t enable)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_event_mask_set((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, mask, enable); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_event_mask_set(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, const uint32_t mask, const mesa_bool_t enable)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_event_mask_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, uint32_t *const mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_event_mask_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_event_mask_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, uint32_t *const mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
mesa_rc mesa_voe_event_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, uint32_t *const mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voe_event_get((const vtss_inst_t)inst /* ag.rb:1870 */, voe_idx, mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voe_event_get(const mesa_inst_t inst, const mesa_voe_idx_t voe_idx, uint32_t *const mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
mesa_rc mesa_voi_alloc(const mesa_inst_t inst, const mesa_voi_allocation_t *const param, mesa_voi_idx_t *const voi_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voi_allocation_t) == sizeof(mesa_voi_allocation_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voi_alloc((const vtss_inst_t)inst /* ag.rb:1870 */, (const vtss_voi_allocation_t *)param /* ag.rb:1867 */, voi_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voi_alloc(const mesa_inst_t inst, const mesa_voi_allocation_t *const param, mesa_voi_idx_t *const voi_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_voi_alloc(const mesa_inst_t inst, const mesa_voi_allocation_t *const param, mesa_voi_idx_t *const voi_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
mesa_rc mesa_voi_free(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_voi_free((const vtss_inst_t)inst /* ag.rb:1870 */, voi_idx); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voi_free(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_voi_free(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
mesa_rc mesa_voi_conf_set(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx, const mesa_voi_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voi_conf_t) == sizeof(mesa_voi_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voi_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, voi_idx, (const vtss_voi_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voi_conf_set(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx, const mesa_voi_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_voi_conf_set(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx, const mesa_voi_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_VOP)
#if defined(VTSS_FEATURE_VOP_V2)
mesa_rc mesa_voi_conf_get(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx, mesa_voi_conf_t *const conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_voi_conf_t) == sizeof(mesa_voi_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_voi_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, voi_idx, (vtss_voi_conf_t *)conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_voi_conf_get(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx, mesa_voi_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP_V2) /* ag.rb:1989 */
#else
mesa_rc mesa_voi_conf_get(const mesa_inst_t inst, const mesa_voi_idx_t voi_idx, mesa_voi_conf_t *const conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_VOP) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_event_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_mask)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ewis_event_enable((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable, ev_mask); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_event_enable(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_mask)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_event_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ewis_event_poll((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, status); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_event_poll(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_event_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_event_force(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_force)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ewis_event_force((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, enable, ev_force); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_event_force(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_bool_t enable, const mesa_ewis_event_t ev_force)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_static_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_static_conf_t *const stat_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_static_conf_t) == sizeof(mesa_ewis_static_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_static_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_static_conf_t *)stat_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_static_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_static_conf_t *const stat_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_force_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_force_mode_t *const force_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_force_mode_t) == sizeof(mesa_ewis_force_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_force_conf_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_force_mode_t *)force_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_force_conf_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_force_mode_t *const force_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_force_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_force_mode_t *const force_conf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_force_mode_t) == sizeof(mesa_ewis_force_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_force_conf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_force_mode_t *)force_conf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_force_conf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_force_mode_t *const force_conf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_t *const tx_oh)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_tx_oh_t) == sizeof(mesa_ewis_tx_oh_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_tx_oh_t *)tx_oh /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_tx_oh_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_t *const tx_oh)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_t *const tx_oh)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_tx_oh_t) == sizeof(mesa_ewis_tx_oh_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_tx_oh_t *)tx_oh /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_tx_oh_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_t *const tx_oh)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_passthru_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_tx_oh_passthru_t) == sizeof(mesa_ewis_tx_oh_passthru_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_passthru_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_tx_oh_passthru_t *)tx_oh_passthru /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_tx_oh_passthru_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_tx_oh_passthru_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_tx_oh_passthru_t) == sizeof(mesa_ewis_tx_oh_passthru_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_tx_oh_passthru_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_tx_oh_passthru_t *)tx_oh_passthru /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_tx_oh_passthru_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tx_oh_passthru_t *const tx_oh_passthru)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_mode_t) == sizeof(mesa_ewis_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_mode_t *const mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_mode_t) == sizeof(mesa_ewis_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_mode_t *)mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_mode_t *const mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    return vtss_ewis_reset((const vtss_inst_t)inst /* ag.rb:1870 */, port_no); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_reset(const mesa_inst_t inst, const mesa_port_no_t port_no)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_cons_act_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_cons_act_t *const cons_act)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_cons_act_t) == sizeof(mesa_ewis_cons_act_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_cons_act_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_cons_act_t *)cons_act /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_cons_act_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_cons_act_t *const cons_act)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_cons_act_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_cons_act_t *const cons_act)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_cons_act_t) == sizeof(mesa_ewis_cons_act_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_cons_act_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_cons_act_t *)cons_act /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_cons_act_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_cons_act_t *const cons_act)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_section_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{ /* ag.rb:1845 */
    vtss_ewis_tti_t __txti;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_ewis_tti_t_to_vtss_ewis_tti_t(txti, &__txti)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_ewis_section_txti_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__txti); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_section_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_section_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{ /* ag.rb:1845 */
    vtss_ewis_tti_t __txti;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_section_txti_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__txti); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__txti, txti)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ewis_section_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_exp_sl_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_sl_conf_t *const sl)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_sl_conf_t) == sizeof(mesa_ewis_sl_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_exp_sl_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_sl_conf_t *)sl /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_exp_sl_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_sl_conf_t *const sl)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_path_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{ /* ag.rb:1845 */
    vtss_ewis_tti_t __txti;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    __RC(mesa_conv_mesa_ewis_tti_t_to_vtss_ewis_tti_t(txti, &__txti)) /* ag.rb:1916 */; /* ag.rb:1965 */
    return vtss_ewis_path_txti_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__txti); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_path_txti_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_path_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{ /* ag.rb:1845 */
    vtss_ewis_tti_t __txti;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_path_txti_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__txti); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__txti, txti)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ewis_path_txti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const txti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_test_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_test_conf_t *const test_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_test_conf_t) == sizeof(mesa_ewis_test_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_test_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_test_conf_t *)test_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_test_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_test_conf_t *const test_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_test_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_conf_t *const test_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_test_conf_t) == sizeof(mesa_ewis_test_conf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_test_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_test_conf_t *)test_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_test_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_conf_t *const test_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_prbs31_err_inj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_prbs31_err_inj_t *const inj)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_prbs31_err_inj_t) == sizeof(mesa_ewis_prbs31_err_inj_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_prbs31_err_inj_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_prbs31_err_inj_t *)inj /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_prbs31_err_inj_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_prbs31_err_inj_t *const inj)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_test_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_status_t *const test_status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_test_status_t) == sizeof(mesa_ewis_test_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_test_counter_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_test_status_t *)test_status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_test_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_test_status_t *const test_status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_defects_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_defects_t *const def)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_defects_t) == sizeof(mesa_ewis_defects_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_defects_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_defects_t *)def /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_defects_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_defects_t *const def)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_status_t *const status)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_status_t) == sizeof(mesa_ewis_status_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_status_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_status_t *)status /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_status_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_status_t *const status)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_section_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{ /* ag.rb:1845 */
    vtss_ewis_tti_t __acti;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_section_acti_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__acti); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__acti, acti)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ewis_section_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_path_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{ /* ag.rb:1845 */
    vtss_ewis_tti_t __acti;
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus
    mesa_rc rc = vtss_ewis_path_acti_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, &__acti); /* ag.rb:1970 */
    __RC(mesa_conv_vtss_ewis_tti_t_to_mesa_ewis_tti_t(&__acti, acti)) /* ag.rb:1916 */; /* ag.rb:1972 */
    return rc; /* ag.rb:1974 */
}
#else
mesa_rc mesa_ewis_path_acti_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_tti_t *const acti)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_t *const counter)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_counter_t) == sizeof(mesa_ewis_counter_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_counter_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_counter_t *)counter /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_counter_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_t *const counter)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_perf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_t *const perf)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_perf_t) == sizeof(mesa_ewis_perf_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_perf_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_perf_t *)perf /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_perf_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_t *const perf)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_counter_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_counter_threshold_t *const threshold)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_counter_threshold_t) == sizeof(mesa_ewis_counter_threshold_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_counter_threshold_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_counter_threshold_t *)threshold /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_counter_threshold_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_counter_threshold_t *const threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_counter_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_threshold_t *const threshold)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_counter_threshold_t) == sizeof(mesa_ewis_counter_threshold_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_counter_threshold_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_counter_threshold_t *)threshold /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_counter_threshold_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_counter_threshold_t *const threshold)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_perf_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_perf_mode_t *const perf_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_perf_mode_t) == sizeof(mesa_ewis_perf_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_perf_mode_set((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (const vtss_ewis_perf_mode_t *)perf_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_perf_mode_set(const mesa_inst_t inst, const mesa_port_no_t port_no, const mesa_ewis_perf_mode_t *const perf_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#if defined(VTSS_FEATURE_WIS)
mesa_rc mesa_ewis_perf_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_mode_t *const perf_mode)
{ /* ag.rb:1845 */
#ifdef __cplusplus
    static_assert(sizeof(vtss_inst_t) == sizeof(mesa_inst_t), "Check size"); /* ag.rb:1956 */
    static_assert(sizeof(vtss_ewis_perf_mode_t) == sizeof(mesa_ewis_perf_mode_t), "Check size"); /* ag.rb:1956 */
#endif // __cplusplus

    return vtss_ewis_perf_mode_get((const vtss_inst_t)inst /* ag.rb:1870 */, port_no, (vtss_ewis_perf_mode_t *)perf_mode /* ag.rb:1867 */); /* ag.rb:1976*/ 
}
#else
mesa_rc mesa_ewis_perf_mode_get(const mesa_inst_t inst, const mesa_port_no_t port_no, mesa_ewis_perf_mode_t *const perf_mode)
{
    return MESA_RC_NOT_IMPLEMENTED;
}
#endif  // defined(VTSS_FEATURE_WIS) /* ag.rb:1989 */

#pragma GCC diagnostic pop
