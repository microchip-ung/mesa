// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"
#include "vtss_fa_sd10g28_setup.h"
#include "vtss_fa_sd25g28_setup.h"

#if defined(VTSS_ARCH_FA)

u32 vtss_to_sd6g_lane(u32 indx)
{
    switch (indx) {
    case 0:  return VTSS_TO_SD6G_LANE_0;
    case 1:  return VTSS_TO_SD6G_LANE_1;
    case 2:  return VTSS_TO_SD6G_LANE_2;
    case 3:  return VTSS_TO_SD6G_LANE_3;
    case 4:  return VTSS_TO_SD6G_LANE_4;
    case 5:  return VTSS_TO_SD6G_LANE_5;
    case 6:  return VTSS_TO_SD6G_LANE_6;
    case 7:  return VTSS_TO_SD6G_LANE_7;
    case 8:  return VTSS_TO_SD6G_LANE_8;
    case 9:  return VTSS_TO_SD6G_LANE_9;
    case 10: return VTSS_TO_SD6G_LANE_10;
    case 11: return VTSS_TO_SD6G_LANE_11;
    case 12: return VTSS_TO_SD6G_LANE_12;
    default:
        VTSS_E("illegal 6G_lane index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd10g_lane(u32 indx)
{
    switch (indx) {
    case 0:  return VTSS_TO_SD10G_LANE_0;
    case 1:  return VTSS_TO_SD10G_LANE_1;
    case 2:  return VTSS_TO_SD10G_LANE_2;
    case 3:  return VTSS_TO_SD10G_LANE_3;
    case 4:  return VTSS_TO_SD10G_LANE_4;
    case 5:  return VTSS_TO_SD10G_LANE_5;
    case 6:  return VTSS_TO_SD10G_LANE_6;
    case 7:  return VTSS_TO_SD10G_LANE_7;
    case 8:  return VTSS_TO_SD10G_LANE_8;
    case 9:  return VTSS_TO_SD10G_LANE_9;
    case 10: return VTSS_TO_SD10G_LANE_10;
    case 11: return VTSS_TO_SD10G_LANE_11;
    default:
        VTSS_E("illegal 10G_lane index %d",indx);
        return 0;
    }

}

u32 vtss_to_sd25g_lane(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD25G_LANE_0;
    case 1: return VTSS_TO_SD25G_LANE_1;
    case 2: return VTSS_TO_SD25G_LANE_2;
    case 3: return VTSS_TO_SD25G_LANE_3;
    case 4: return VTSS_TO_SD25G_LANE_4;
    case 5: return VTSS_TO_SD25G_LANE_5;
    case 6: return VTSS_TO_SD25G_LANE_6;
    case 7: return VTSS_TO_SD25G_LANE_7;
    default:
        VTSS_E("illegal 25G_lane index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd_cmu(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD_CMU_0;
    case 1: return VTSS_TO_SD_CMU_1;
    case 2: return VTSS_TO_SD_CMU_2;
    case 3: return VTSS_TO_SD_CMU_3;
    case 4: return VTSS_TO_SD_CMU_4;
    case 5: return VTSS_TO_SD_CMU_5;
    case 6: return VTSS_TO_SD_CMU_6;
    case 7: return VTSS_TO_SD_CMU_7;
    case 8: return VTSS_TO_SD_CMU_8;
    case 9: return VTSS_TO_SD_CMU_9;
    case 10: return VTSS_TO_SD_CMU_10;
    case 11: return VTSS_TO_SD_CMU_11;
    case 12: return VTSS_TO_SD_CMU_12;
    case 13: return VTSS_TO_SD_CMU_13;
    default:
        VTSS_E("illegal sd_cmu index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd_cmu_cfg(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD_CMU_CFG_0;
    case 1: return VTSS_TO_SD_CMU_CFG_1;
    case 2: return VTSS_TO_SD_CMU_CFG_2;
    case 3: return VTSS_TO_SD_CMU_CFG_3;
    case 4: return VTSS_TO_SD_CMU_CFG_4;
    case 5: return VTSS_TO_SD_CMU_CFG_5;
    case 6: return VTSS_TO_SD_CMU_CFG_6;
    case 7: return VTSS_TO_SD_CMU_CFG_7;
    case 8: return VTSS_TO_SD_CMU_CFG_8;
    case 9: return VTSS_TO_SD_CMU_CFG_9;
    case 10: return VTSS_TO_SD_CMU_CFG_10;
    case 11: return VTSS_TO_SD_CMU_CFG_11;
    case 12: return VTSS_TO_SD_CMU_CFG_12;
    case 13: return VTSS_TO_SD_CMU_CFG_13;
    default:
        VTSS_E("illegal sd_cmu index %d",indx);
        return 0;
    }
}

u32 vtss_to_sd_lane(u32 indx)
{
    switch (indx) {
    case 0: return VTSS_TO_SD_LANE_0;
    case 1: return VTSS_TO_SD_LANE_1;
    case 2: return VTSS_TO_SD_LANE_2;
    case 3: return VTSS_TO_SD_LANE_3;
    case 4: return VTSS_TO_SD_LANE_4;
    case 5: return VTSS_TO_SD_LANE_5;
    case 6: return VTSS_TO_SD_LANE_6;
    case 7: return VTSS_TO_SD_LANE_7;
    case 8: return VTSS_TO_SD_LANE_8;
    case 9: return VTSS_TO_SD_LANE_9;
    case 10: return VTSS_TO_SD_LANE_10;
    case 11: return VTSS_TO_SD_LANE_11;
    case 12: return VTSS_TO_SD_LANE_12;
    case 13: return VTSS_TO_SD_LANE_13;
    case 14: return VTSS_TO_SD_LANE_14;
    case 15: return VTSS_TO_SD_LANE_15;
    case 16: return VTSS_TO_SD_LANE_16;
    case 17: return VTSS_TO_SD_LANE_17;
    case 18: return VTSS_TO_SD_LANE_18;
    case 19: return VTSS_TO_SD_LANE_19;
    case 20: return VTSS_TO_SD_LANE_20;
    case 21: return VTSS_TO_SD_LANE_21;
    case 22: return VTSS_TO_SD_LANE_22;
    case 23: return VTSS_TO_SD_LANE_23;
    case 24: return VTSS_TO_SD_LANE_24;
    case 25: return VTSS_TO_SD_LANE_25;
    case 26: return VTSS_TO_SD_LANE_26;
    case 27: return VTSS_TO_SD_LANE_27;
    case 28: return VTSS_TO_SD_LANE_28;
    case 29: return VTSS_TO_SD_LANE_29;
    case 30: return VTSS_TO_SD_LANE_30;
    case 31: return VTSS_TO_SD_LANE_31;
    case 32: return VTSS_TO_SD_LANE_32;
    default:
        VTSS_E("illegal sd_lane index %d",indx);
        return 0;
    }
}

static vtss_sd10g28_preset_t serdes2preset(vtss_sd10g_media_type_t m)
{
    switch (m) {
    case VTSS_SD10G_MEDIA_SR:
    case VTSS_SD10G_MEDIA_ZR:     return(VTSS_SD10G28_SR);
    case VTSS_SD10G_MEDIA_DAC:    return(VTSS_SD10G28_DAC3M); // Default to 3m
    case VTSS_SD10G_MEDIA_DAC_1M: return(VTSS_SD10G28_DAC1M);
    case VTSS_SD10G_MEDIA_DAC_2M: return(VTSS_SD10G28_DAC2M);
    case VTSS_SD10G_MEDIA_DAC_3M: return(VTSS_SD10G28_DAC3M);
    case VTSS_SD10G_MEDIA_DAC_5M: return(VTSS_SD10G28_DAC5M);
    case VTSS_SD10G_MEDIA_BP:
    case VTSS_SD10G_MEDIA_B2B:
    case VTSS_SD10G_MEDIA_10G_KR: return(VTSS_SD10G28_DAC3M);
    default:
    return(VTSS_SD10G28_PRESET_NONE);
    }
}

const char *vtss_serdes_preset_txt(vtss_sd10g28_preset_t pr)
{
    switch (pr) {
    case VTSS_SD10G28_ATE:         return "ATE";
    case VTSS_SD10G28_ZR:          return "ZR";
    case VTSS_SD10G28_DAC3M:       return "DAC3M";
    case VTSS_SD10G28_DAC5M:       return "DAC5M";
    case VTSS_SD10G28_DAC2M:       return "DAC2M";
    case VTSS_SD10G28_DAC1M:       return "DAC1M";
    case VTSS_SD10G28_DAC3M_PVT:   return "DAC3_PVT";
    case VTSS_SD10G28_SR:          return "SR";
    case VTSS_SD10G28_KR:          return "KR";
    case VTSS_SD10G28_FX100:       return "100FX";
    case VTSS_SD10G28_PRESET_NONE: return "None";
    }
    return "?   ";
}

static vtss_sd25g28_preset_t serdes2preset_25g(vtss_sd10g_media_type_t m, vtss_port_speed_t speed)
{
    if (speed == VTSS_SPEED_10G) {
        switch (m) {
        case VTSS_SD10G_MEDIA_SR:
        case VTSS_SD10G_MEDIA_ZR:     return(VTSS_SD25G28_10GSR);
        case VTSS_SD10G_MEDIA_DAC:    return(VTSS_SD25G28_10GDAC3M); // Default to 3m
        case VTSS_SD10G_MEDIA_DAC_1M: return(VTSS_SD25G28_10GDAC1M);
        case VTSS_SD10G_MEDIA_DAC_2M: return(VTSS_SD25G28_10GDAC3M);
        case VTSS_SD10G_MEDIA_DAC_3M: return(VTSS_SD25G28_10GDAC3M);
        case VTSS_SD10G_MEDIA_DAC_5M: return(VTSS_SD25G28_10GDAC5M);
        case VTSS_SD10G_MEDIA_BP:
        case VTSS_SD10G_MEDIA_B2B:
        case VTSS_SD10G_MEDIA_10G_KR: return(VTSS_SD25G28_10GDAC3M);
        default:
            return(VTSS_SD25G28_PRESET_NONE);
        }
    } else {
        switch (m) {
        case VTSS_SD10G_MEDIA_SR:
        case VTSS_SD10G_MEDIA_ZR:     return(VTSS_SD25G28_25GSR);
        case VTSS_SD10G_MEDIA_DAC:
        case VTSS_SD10G_MEDIA_DAC_1M:
        case VTSS_SD10G_MEDIA_DAC_2M:
        case VTSS_SD10G_MEDIA_DAC_3M:
        case VTSS_SD10G_MEDIA_DAC_5M:
        case VTSS_SD10G_MEDIA_BP:
        case VTSS_SD10G_MEDIA_B2B:
        case VTSS_SD10G_MEDIA_10G_KR: return(VTSS_SD25G28_25GDAC2M);
        default:
            return(VTSS_SD25G28_PRESET_NONE);
        }
    }
}

const char *vtss_serdes25g_preset_txt(vtss_sd25g28_preset_t pr)
{
    switch (pr) {
    case VTSS_SD25G28_ATE:         return "ATE";
    case VTSS_SD25G28_ZR:          return "ZR";
    case VTSS_SD25G28_10GDAC3M:    return "10G-DAC3m";
    case VTSS_SD25G28_10GDAC5M:    return "10G-DAC5m";
    case VTSS_SD25G28_10GDAC1M:    return "10G-DAC1m";
    case VTSS_SD25G28_10GDAC3M_PVT:return "10G-DAC3m_PVT";
    case VTSS_SD25G28_10GSR:       return "10G-SR";
    case VTSS_SD25G28_KR_HW:       return "KR";
    case VTSS_SD25G28_25GSR:       return "25G-SR";
    case VTSS_SD25G28_25GDAC2M:    return "25G-DAC2m";
    case VTSS_SD25G28_PRESET_NONE: return "None";
    }
    return "?   ";
}

static vtss_rc fa_get_lane_target(u32 type, u32 indx)
{
    if (type == FA_SERDES_TYPE_6G) {
        return VTSS_TO_SD6G_LANE(indx);
    } else if (type == FA_SERDES_TYPE_10G) {
        return VTSS_TO_SD10G_LANE(indx);
    } else {
        return VTSS_TO_SD25G_LANE(indx);
    }
}


u32 vtss_fa_sd10g28_get_cmu (vtss_state_t *vtss_state, vtss_sd10g28_cmu_t cmu_type, vtss_port_no_t port_no) {

    u32 serdes_no;

    serdes_no = vtss_fa_sd_lane_indx(vtss_state, port_no);

    if (cmu_type == 0) {
        // Main CMU of FA
        if (serdes_no < 8 ) {
            return 2;
        } else if (serdes_no < 16 ) {
            return 5;
        } else if (serdes_no == 16) {
            return 8;
        } else {
            return 11;
        }
    } else if ( cmu_type == 1) {
        // AUX1 CMU of FA
        if (serdes_no < 2 ) {
            return 0;
        } else if (serdes_no < 10 ) {
            return 3;
        } else if (serdes_no < 17) {
            return 6;
        } else if (serdes_no < 19) {
            return 9;
        } else {
            return 12;
        }
    } else {
        // AUX2 CMU of FA
        if (serdes_no < 4 ) {
            return 1;
        } else if (serdes_no < 12 ) {
            return 4;
        } else if (serdes_no < 17) {
            return 7;
        } else if (serdes_no < 21) {
            return 10;
        } else {
            return 13;
        }
    }
}

static void buf_set(char *buf, u32 *u_ptr)
{
    u32 num;
    buf[0] = '\0';
    for (int a = 7; a >= 0; a--) {
        num = u_ptr[a];
        for (int i = 7; i >= 0; i--) {
            VTSS_SPRINTF(buf + VTSS_STRLEN(buf), "%d",(num & (1 << i)) >> i);
        }
    }
}

static void kr_ampcode_2_drv(u32 ampcode, u32 *ipdriver, u32 *vcdriver)
{
    if  (ampcode < 16) {
        *ipdriver = 6;
        *vcdriver = ampcode;
    } else if (16 <= ampcode && ampcode < 32) {
        *ipdriver = 5;
        *vcdriver = ampcode - 16;
    } else if (32 <= ampcode && ampcode < 46) {
        *ipdriver = 7;
        *vcdriver = ampcode - 30;
    } else if (46 <= ampcode && ampcode < 58) {
        *ipdriver = 4;
        *vcdriver = ampcode - 42;
    } else if (58 <= ampcode && ampcode < 69) {
        *ipdriver = 3;
        *vcdriver = ampcode - 53;
    } else if (69 <= ampcode && ampcode < 79) {
        *ipdriver = 2;
        *vcdriver = ampcode - 63;
    } else if (79 <= ampcode && ampcode < 88) {
        *ipdriver = 0;
        *vcdriver = ampcode - 72;
    } else if (88 <= ampcode && ampcode < 102) {
        *ipdriver = 1;
        *vcdriver = ampcode - 86;
    }
}

static u32 kr_drv_2_ampcode(u32 ipdriver, u32 vcdriver)
{
    if (ipdriver == 6) {
        return vcdriver;
    } else if (ipdriver == 5) {
        return (vcdriver + 16);
    } else if (ipdriver == 7) {
        return (30 + vcdriver);
    } else if (ipdriver == 4) {
        return (vcdriver + 42);
    } else if (ipdriver == 3) {
        return (vcdriver + 53);
    } else if (ipdriver == 2) {
        return (vcdriver + 63);
    } else if (ipdriver == 0) {
        return (vcdriver + 72);
    } else if (ipdriver == 1) {
        return (vcdriver + 86);
    } else {
        VTSS_E("Should not happend");
        return 0;
    }
}

vtss_rc fa_port_25g_kr_tap_get(vtss_state_t *vtss_state, vtss_port_no_t port_no,
                               u16 *tap_dly, u16 *tap_adv, u16 *ampl)
{
    u32 sd_indx, sd_type, sd25g_tgt, val1, ipdriver, vcdriver;
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));
    sd25g_tgt = VTSS_TO_SD25G_LANE(sd_indx);

    REG_RD(VTSS_SD25G_TARGET_LANE_03(sd25g_tgt), &val1);
    *tap_dly = VTSS_X_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0(val1);

    REG_RD(VTSS_SD25G_TARGET_LANE_06(sd25g_tgt), &val1);
    *tap_adv = VTSS_X_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0(val1);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xff),
            VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);
    REG_RD(VTSS_SD25G_TARGET_CMU_47(sd25g_tgt), &val1);
    ipdriver = VTSS_X_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0(val1);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0),
            VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);
    REG_RD(VTSS_SD25G_TARGET_LANE_00(sd25g_tgt), &val1);
    vcdriver = VTSS_X_SD25G_TARGET_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(val1);

    *ampl = kr_drv_2_ampcode(ipdriver, vcdriver);

    return VTSS_RC_OK;
}

static vtss_rc fa_port_25g_kr_tap_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no, u16 tap_dly, u16 tap_adv, u16 ampl)
{
    u32 sd_indx, sd_type, sd25g_tgt, ipdriver = 0, vcdriver = 0;
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));
    sd25g_tgt = VTSS_TO_SD25G_LANE(sd_indx);

    (void)kr_ampcode_2_drv(ampl, &ipdriver, &vcdriver);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xff),
            VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_WRM(VTSS_SD25G_TARGET_CMU_47(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0(ipdriver),
            VTSS_M_SD25G_TARGET_CMU_47_L0_CFG_ITX_IPDRIVER_BASE_2_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0),
            VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    REG_WRM(VTSS_SD25G_TARGET_LANE_00(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0(vcdriver),
            VTSS_M_SD25G_TARGET_LANE_00_LN_CFG_ITX_VC_DRIVER_3_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_03(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0(tap_dly),
            VTSS_M_SD25G_TARGET_LANE_03_LN_CFG_TAP_DLY_4_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_06(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0(tap_adv),
            VTSS_M_SD25G_TARGET_LANE_06_LN_CFG_TAP_ADV_3_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_07(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY(1),
            VTSS_M_SD25G_TARGET_LANE_07_LN_CFG_EN_DLY);

    REG_WRM(VTSS_SD25G_TARGET_LANE_07(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_07_LN_CFG_EN_ADV(1),
            VTSS_M_SD25G_TARGET_LANE_07_LN_CFG_EN_ADV);

    return VTSS_RC_OK;
}


static vtss_rc fa_port_10g_kr_tap_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                                      u16 tap_dly, u16 tap_adv, u16 ampl)
{
    u32 sd_indx, sd_type, sd_tgt;
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));
    sd_tgt = fa_get_lane_target(sd_type, sd_indx);

    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_04(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_04_CFG_TAP_DLY_4_0(tap_dly),
            VTSS_M_SD10G_LANE_TARGET_LANE_04_CFG_TAP_DLY_4_0);

    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_02(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_02_CFG_TAP_ADV_3_0(tap_adv),
            VTSS_M_SD10G_LANE_TARGET_LANE_02_CFG_TAP_ADV_3_0);

    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_33(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0(ampl >> 6),
            VTSS_M_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0);

    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_52(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0(ampl & 0x3F),
            VTSS_M_SD10G_LANE_TARGET_LANE_52_CFG_IBIAS_TUNE_RESERVE_5_0);

    return VTSS_RC_OK;

}

vtss_rc fa_port_10g_kr_tap_get(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 *tap_dly, u16 *tap_adv, u16 *ampl)
{
    u32 sd_indx = 0, sd_type, sd_tgt, val1, val2;

    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));
    sd_tgt = fa_get_lane_target(sd_type, sd_indx);

    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_04(sd_tgt), &val1);
    *tap_dly = (u16)VTSS_X_SD10G_LANE_TARGET_LANE_04_CFG_TAP_DLY_4_0(val1);

    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_02(sd_tgt), &val1);
    *tap_adv = (u16)VTSS_X_SD10G_LANE_TARGET_LANE_02_CFG_TAP_ADV_3_0(val1);

    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_33(sd_tgt), &val1);
    val1 = VTSS_X_SD10G_LANE_TARGET_LANE_33_CFG_ITX_IPDRIVER_BASE_2_0(val1) << 6;
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_52(sd_tgt), &val2);
    *ampl = (u16)(val1 + val2);

    return VTSS_RC_OK;
}


vtss_rc fa_port_kr_tap_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 tap_dly, u16 tap_adv, u16 ampl)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    if (VTSS_PORT_IS_25G(port)) {
        VTSS_RC(fa_port_25g_kr_tap_set(vtss_state, port_no, tap_dly, tap_adv, ampl));
    } else {
        VTSS_RC(fa_port_10g_kr_tap_set(vtss_state, port_no, tap_dly, tap_adv, ampl));
    }

    return VTSS_RC_OK;
}

vtss_rc fa_port_kr_tap_get(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 *tap_dly, u16 *tap_adv, u16 *ampl)
{
    u32 port = VTSS_CHIP_PORT(port_no);

    if (VTSS_PORT_IS_25G(port)) {
        VTSS_RC(fa_port_25g_kr_tap_get(vtss_state, port_no, tap_dly, tap_adv, ampl));
    } else {
        VTSS_RC(fa_port_10g_kr_tap_get(vtss_state, port_no, tap_dly, tap_adv, ampl));
    }

    return VTSS_RC_OK;
}


#if defined(VTSS_FEATURE_PORT_KR_IRQ)

/** \brief 10G KR coefficient types */
typedef enum {
    VTSS_COEF_PRESET,
    VTSS_COEF_INIT,
    VTSS_COEF_CP1,
    VTSS_COEF_C0,
    VTSS_COEF_CM1,
} vtss_port_kr_coef_type_t;

/** \brief 10G KR coefficient action types */
typedef enum {
    VTSS_COEF_HOLD,
    VTSS_COEF_INCR,
    VTSS_COEF_DECR
} vtss_port_kr_coef_update_t;

typedef enum {
    VTSS_COEF_NOT_UPDATED = 0,
    VTSS_COEF_UPDATED = 1,
    VTSS_COEF_MINIMUM = 2,
    VTSS_COEF_MAXIMUM = 3
} vtss_port_kr_coef_status_t;

#define BT(x) (1 << (x))

//vtss_port_kr_temp_storage_t kr_coef_store[VTSS_PORTS] = {0};

const char *raw_sts2txt(u32 frm_in)
{
    u32 action = 0;

    if ((frm_in & 0x3) > 0) {
        action = frm_in & 0x3;
    } else if ((frm_in & 0xc) > 0) {
        action = (frm_in >> 2) & 3;
    } else if ((frm_in & 0x30) > 0 ) {
        action = (frm_in >> 4) & 3;
    } else if ((frm_in & 0x3f) == 0 ) {
        action = 0;
    }
    if (action == 0) {
        return "NOT_UPDATED";
    } else if (action == 1) {
        return "UPDATED";
    } else if (action == 2) {
        return "MINUMUN";
    } else {
        return "MAXIMUM";
    }
}

const vtss_port_kr_coef_status_t raw_sts2enum(u32 frm_in)
{
    u32 action = 0;

    if ((frm_in & 0x3) > 0) {
        action = frm_in & 0x3;
    } else if ((frm_in & 0xc) > 0) {
        action = (frm_in >> 2) & 3;
    } else if ((frm_in & 0x30) > 0 ) {
        action = (frm_in >> 4) & 3;
    } else if ((frm_in & 0x3f) == 0 ) {
        action = 0;
    }
    if (action == 0) {
        return VTSS_COEF_NOT_UPDATED;
    } else if (action == 1) {
        return VTSS_COEF_UPDATED;
    } else if (action == 2) {
        return VTSS_COEF_MINIMUM;
    } else  {
        return VTSS_COEF_MAXIMUM; // must be 3
    }
}


const char *vtss_kr_status2txt(vtss_port_kr_coef_status_t sts)
{
    switch (sts) {
    case VTSS_COEF_NOT_UPDATED: return "NOT_UPDATED";
    case VTSS_COEF_UPDATED:     return "UPDATED";
    case VTSS_COEF_MINIMUM:     return "MINIMUM";
    case VTSS_COEF_MAXIMUM:     return "MAXIMUM";
    }
    return "?   ";
}

const char *vtss_kr_upd2txt(vtss_port_kr_coef_update_t upd)
{
    switch (upd) {
    case VTSS_COEF_HOLD: return "HOLD";
    case VTSS_COEF_INCR: return "INCR";
    case VTSS_COEF_DECR: return "DECR";
    }
    return "?   ";
}

const char *vtss_kr_coef2txt(vtss_port_kr_coef_type_t coef)
{
    switch (coef) {
    case VTSS_COEF_PRESET: return "PRESET";
    case VTSS_COEF_INIT:   return "INIT";
    case VTSS_COEF_CP1:    return "CP1";
    case VTSS_COEF_C0:     return "C0";
    case VTSS_COEF_CM1:    return "CM1";
    }
    return "?   ";
}

typedef enum {
    VTSS_KR_STS_UPDATED,
    VTSS_KR_STS_PCS2PMA_BELOW_30,
    VTSS_KR_STS_PCS2PMA_ABOVE_255,
    VTSS_KR_STS_TAP_DLY_BELOW_0,
    VTSS_KR_STS_TAP_DLY_ABOVE_31,
    VTSS_KR_STS_TAP_ADV_BELOW_0,
    VTSS_KR_STS_TAP_ADV_ABOVE_15,
    VTSS_KR_STS_ADV_DLY_ABOVE_LIMIT,
    VTSS_KR_STS_TAP_ADV_ABOVE_LIMIT,
    VTSS_KR_STS_ADV_DLY_OUT_OF_RANGE,
    VTSS_KR_STS_TAP_ADV_ABOVE_14,
    VTSS_KR_STS_TAP_AMP_BELOW_48,
    VTSS_KR_STS_AMP_CODE_BELOW_16,
    VTSS_KR_STS_AMP_CODE_ABOVE_94,
} vtss_port_kr_status_codes_t;

const char *vtss_kr_sts_code2txt(vtss_port_kr_status_codes_t sts)
{
    switch (sts) {
    case VTSS_KR_STS_UPDATED:             return "OK";
    case VTSS_KR_STS_PCS2PMA_BELOW_30:    return "PCS2PMA_BELOW_30";
    case VTSS_KR_STS_PCS2PMA_ABOVE_255:   return "PCS2PMA_ABOVE_255";
    case VTSS_KR_STS_TAP_DLY_BELOW_0:     return "TAP_DLY_BELOW_0";
    case VTSS_KR_STS_TAP_DLY_ABOVE_31:    return "TAP_DLY_ABOVE_31";
    case VTSS_KR_STS_TAP_ADV_BELOW_0:     return "TAP_ADV_BELOW_0";
    case VTSS_KR_STS_TAP_ADV_ABOVE_15:     return"TAP_ADV_ABOVE_15";
    case VTSS_KR_STS_ADV_DLY_ABOVE_LIMIT: return "SUM_ADV_DLY_ABOVE_LIMIT";
    case VTSS_KR_STS_TAP_ADV_ABOVE_LIMIT: return "TAP_ADV_ABOVE_LIMIT";
    case VTSS_KR_STS_ADV_DLY_OUT_OF_RANGE:return "SUM_ADV_DLY_OUT_OF_RANGE";
    case VTSS_KR_STS_TAP_ADV_ABOVE_14:    return "SUM_TAP_ADV_ABOVE_14";
    case VTSS_KR_STS_TAP_AMP_BELOW_48:    return "TAP_DLY_BELOW_48";
    case VTSS_KR_STS_AMP_CODE_BELOW_16:   return "AMP_CODE_BELOW_16";
    case VTSS_KR_STS_AMP_CODE_ABOVE_94:   return "AMP_CODE_ABOVE_94";

    }
    return "?   ";
}

static vtss_port_kr_coef_type_t coef2tap(u16 frm_in)
{
    if (BT(13) & frm_in) {
        return VTSS_COEF_PRESET;
    } else if (BT(12) & frm_in) {
        return VTSS_COEF_INIT;
    } else if ((frm_in & 0x3) > 0) {
        return VTSS_COEF_CM1;
    } else if ((frm_in & 0xc) > 0) {
        return VTSS_COEF_C0;
    } else if ((frm_in & 0x30) > 0 ) {
        return VTSS_COEF_CP1;
    }
    return VTSS_COEF_CM1;
}

static vtss_port_kr_coef_update_t coef2act(u16 frm_in)
{
    u32 action = 0;

    if ((frm_in & 0x3) > 0) {
        action = frm_in & 0x3;
    } else if ((frm_in & 0xc) > 0) {
        action = (frm_in >> 2) & 3;
    } else if  ((frm_in & 0x30) > 0 ) {
        action = (frm_in >> 4) & 3;
    } else if ((frm_in & 0xf) == 0 ) {
        action = 0;
    }

    if (action == 1) {
        return VTSS_COEF_INCR;
    } else if (action == 2) {
        return VTSS_COEF_DECR;
    } else {
        return VTSS_COEF_HOLD;
    }
}

static vtss_port_kr_coef_status_t coef2sts(u16 frm_in)
{
    u16 action = 0;

    if ((frm_in & 0xc) > 0) {
        action = (frm_in >> 2) & 3;
    } else if ((frm_in & 0x30) > 0) {
        action = (frm_in >> 4) & 3;
    } else if ((frm_in & 0x3) > 0) {
        action = frm_in & 0x3;
    }
    if (action == 1) {
        return VTSS_COEF_UPDATED;
    } else if (action == 2) {
        return VTSS_COEF_MINIMUM;
    } else if (action == 3) {
        return VTSS_COEF_MAXIMUM;
    }
    return VTSS_COEF_NOT_UPDATED;
}

static u16 sts2rawsts(vtss_port_kr_coef_type_t tap, vtss_port_kr_coef_status_t status, u16 sts_out)
{
    if ((tap == VTSS_COEF_PRESET) || (tap == VTSS_COEF_INIT)) {
        return (sts_out);
    } else if (tap == VTSS_COEF_CP1) {
        return (status = status << 4);
    } else if (tap == VTSS_COEF_C0) {
        return (status = status << 2);
    }
    return status;
}

// GUC algorithm for 10G TxEQ KR tuning
static vtss_port_kr_status_codes_t fa_coef_status_10g_calc(u32 p, const u16 coef_in,
                                                           u32 *pcs2pma, u32 *tap_dly, u32 *tap_adv, u16 *status_out, BOOL verify_only)
{
    u32 dG = 0, dCd = 0, dCa = 0, adv_dly_sum = 99, tap_adv_max = 99;
    int _pcs2pma = *pcs2pma, _tap_dly = *tap_dly, _tap_adv = *tap_adv;
    vtss_port_kr_coef_status_t status = VTSS_COEF_UPDATED;
    vtss_port_kr_status_codes_t sts_code = VTSS_KR_STS_UPDATED;
    vtss_port_kr_coef_type_t tap = coef2tap(coef_in);
    vtss_port_kr_coef_update_t action = coef2act(coef_in);

    switch (tap) {
    case VTSS_COEF_PRESET:
        _pcs2pma = 192;
        _tap_adv = 0;
        _tap_dly = 0;
        *status_out = ((VTSS_COEF_UPDATED << 4) | (VTSS_COEF_MAXIMUM << 2) |  VTSS_COEF_UPDATED);
        break;
    case VTSS_COEF_INIT:
        _pcs2pma = 192;
        _tap_adv = 4;
        _tap_dly = 22;
        *status_out = ((VTSS_COEF_UPDATED << 4) | (VTSS_COEF_UPDATED << 2) |  VTSS_COEF_UPDATED);
        break;
    case VTSS_COEF_CP1:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (30 <= _pcs2pma && _pcs2pma <= 75) {
            if (0 <= _tap_dly && _tap_dly <= 11) {
                dG  = 9;
                dCd = 3;
            } else if (12 <= _tap_dly && _tap_dly <= 31) {
                dG  = 6;
                dCd = 2;
            }
        } else if (76 <= _pcs2pma && _pcs2pma <= 115) {
            dG  = 7;
            dCd = 2;
        } else if (116 <= _pcs2pma && _pcs2pma <= 145) {
            dG  = 9;
            dCd = 2;
        } else if (146 <= _pcs2pma && _pcs2pma <= 175) {
            if (0 <= _tap_dly && _tap_dly <= 11) {
                dG  = 10;
                dCd = 2;
            } else if (12 <= _tap_dly && _tap_dly <= 31) {
                dG  = 5;
                dCd = 1;
                tap_adv_max = 14;
            }
        } else if (176 <= _pcs2pma && _pcs2pma <= 199) {
            if (0 <= _tap_dly && _tap_dly <= 11) {
                dG  = 11;
                dCd = 2;
            } else if (12 <= _tap_dly && _tap_dly <= 31) {
                dG  = 5;
                dCd = 1;
                tap_adv_max = 14;
            }
        } else if (200 <= _pcs2pma && _pcs2pma <= 255) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 5;
                dCd = 1;
                tap_adv_max = 14;
            }
        } else {
            VTSS_E("Should not occur (pcs2pma=%d)",_pcs2pma);
        }
        if (!verify_only) {
            _tap_dly = (action == VTSS_COEF_INCR) ? _tap_dly - dCd : _tap_dly + dCd;
            _pcs2pma = (action == VTSS_COEF_INCR) ? _pcs2pma - dG  : _pcs2pma + dG;
        }

        if (_pcs2pma < 30) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_PCS2PMA_BELOW_30;
        } else if (_pcs2pma > 255) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_PCS2PMA_ABOVE_255;
        } else if (_tap_dly < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_BELOW_0;
        } else if (_tap_dly > 31) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_ABOVE_31;
        } else if (_tap_adv > tap_adv_max) {
            status = (action == VTSS_COEF_INCR) ? VTSS_COEF_MAXIMUM : VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_ABOVE_14;
        }
        break;
    case VTSS_COEF_C0:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }

        if (30 <= _pcs2pma && _pcs2pma <= 200) {
            if (0 <= _tap_dly && _tap_dly <= 14) {
                dG  = 12;
                dCd = 0;
            } else if (15 <= _tap_dly && _tap_dly <= 31) {
                dG  = 7;
                dCd = 1;
                tap_adv_max = 14;
            }
        } else if (201 <= _pcs2pma && _pcs2pma <= 255) {
            if (0 <= _tap_dly && _tap_dly <= 14) {
                dG  = 12;
                dCd = 0;
            } else if (15 <= _tap_dly && _tap_dly <= 31) {
                dG  = 5;
                dCd = 1;
                tap_adv_max = 14;
            }
        } else {
            VTSS_E("Should not occur (pcs2pma=%d)",_pcs2pma);
        }
        if (!verify_only) {
            _tap_dly = (action == VTSS_COEF_INCR) ? _tap_dly - dCd : _tap_dly + dCd;
            _pcs2pma = (action == VTSS_COEF_INCR) ? _pcs2pma + dG  : _pcs2pma - dG;
        }

        if (_pcs2pma < 30) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_PCS2PMA_BELOW_30;
        } else if (_pcs2pma > 255) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_PCS2PMA_ABOVE_255;
        } else if (_tap_dly < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_BELOW_0;
        } else if (_tap_dly > 31) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_ABOVE_31;
        } else if (_tap_adv > tap_adv_max) {
            status = action == VTSS_COEF_INCR ? VTSS_COEF_MAXIMUM : VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_ABOVE_LIMIT;
        }

        break;
    case VTSS_COEF_CM1:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (30 <= _pcs2pma && _pcs2pma <= 75) {
            if (0 <= _tap_dly && _tap_dly <= 11) {
                dG  = 9;
                dCa = 3;
                dCd = 0;
            } else if (12 <= _tap_dly && _tap_dly <= 31) {
                dG  = 6;
                dCa = 3;
                dCd = 1;
            }
        } else if (76 <= _pcs2pma && _pcs2pma <= 149) {
            if (0 <= _tap_dly && _tap_dly <= 19) {
                dG  = 7;
                dCa = 2;
                dCd = 0;
            } else if (20 <= _tap_dly && _tap_dly <= 31) {
                dG  = 4;
                dCa = 2;
                dCd = 1;
            }
        } else if (150 <= _pcs2pma && _pcs2pma <= 187) {
            if (0 <= _tap_dly && _tap_dly <= 13) {
                dG  = 10;
                dCa = 2;
                dCd = 0;
            } else if (14 <= _tap_dly && _tap_dly <= 31) {
                dG  = 6;
                dCa = 2;
                dCd = 1;
            }
        } else if (188 <= _pcs2pma && _pcs2pma <= 200) {
            if (0 <= _tap_dly && _tap_dly <= 10) {
                dG  = 10;
                dCa = 2;
                dCd = 0;
            } else if (11 <= _tap_dly && _tap_dly <= 31) {
                dG  = 6;
                dCa = 2;
                dCd = 1;
            }
        } else if (201 <= _pcs2pma && _pcs2pma <= 220) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 12;
                dCa = 2;
                dCd = 0;
                adv_dly_sum = 22;
            }
        } else if (221 <= _pcs2pma && _pcs2pma <= 255) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 12;
                dCa = 2;
                dCd = 0;
                adv_dly_sum = 18;
            }
        } else {
            VTSS_E("Should not occur (pcs2pma=%d)",_pcs2pma);
        }
        if (!verify_only) {
            _tap_dly = (action == VTSS_COEF_INCR) ? _tap_dly + dCd : _tap_dly - dCd;
            _pcs2pma = (action == VTSS_COEF_INCR) ? _pcs2pma - dG  : _pcs2pma + dG;
            _tap_adv = (action == VTSS_COEF_INCR) ? _tap_adv - dCa : _tap_adv + dCa;
        }
        if (_pcs2pma < 30) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_PCS2PMA_BELOW_30;
        } else if (_pcs2pma > 255) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_PCS2PMA_ABOVE_255;
        } else if (_tap_dly < 0) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_BELOW_0;
        } else if (_tap_dly > 31) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_ABOVE_31;
        } else if (_tap_adv < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_BELOW_0;
        } else if ((_tap_adv + _tap_dly) >= adv_dly_sum) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_ADV_DLY_ABOVE_LIMIT;
        }

        break;
    default:{ VTSS_E("COEF tap not supported"); }
    }

    if (status == VTSS_COEF_UPDATED) {
        // Common restrictions
        if (214 <= _pcs2pma && _pcs2pma <= 250) {
            if (_tap_adv + _tap_dly > 37) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (129 <= _pcs2pma && _pcs2pma <= 213) {
            if (_tap_adv + _tap_dly > 36) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (77 <= _pcs2pma && _pcs2pma <= 128) {
            if (_tap_adv + _tap_dly > 35) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (43 <= _pcs2pma && _pcs2pma <= 76) {
            if (_tap_adv + _tap_dly > 34) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (30 <= _pcs2pma && _pcs2pma <= 42) {
            if (_tap_adv + _tap_dly > 33) {
                status = VTSS_COEF_MINIMUM;
            }
        }
        if (status != VTSS_COEF_UPDATED) {
            sts_code = VTSS_KR_STS_ADV_DLY_OUT_OF_RANGE;
        }
    }

    if (((action == VTSS_COEF_INCR) && (status == VTSS_COEF_MINIMUM)) ||
        ((action == VTSS_COEF_DECR) && (status == VTSS_COEF_MAXIMUM))) {
        VTSS_E("FAILURE! p:%d Tap:%s Action:%s  _pcs2pma=%d (in:%d) _tap_dly=%d (in:%d)  _tap_adv=%d (in:%d) (dly+adv=%d) -> Status:%s (Reason:%s)\n",
               p, vtss_kr_coef2txt(tap), vtss_kr_upd2txt(action), _pcs2pma,*pcs2pma,_tap_dly,*tap_dly,_tap_adv,*tap_adv,
               _tap_adv+_tap_dly, vtss_kr_status2txt(status), vtss_kr_sts_code2txt(sts_code));
    }

    *status_out = sts2rawsts(tap, status, *status_out);
    *tap_dly = _tap_dly;
    *pcs2pma = _pcs2pma;
    *tap_adv = _tap_adv;

    return sts_code;
}

// GUC algorithm for 25G TxEQ KR tuning
static vtss_port_kr_status_codes_t fa_coef_status_25g_calc(u32 p, const u16 coef_in,
                                                          u32 *amp_code, u32 *tap_dly, u32 *tap_adv, u16 *status_out, BOOL verify_only)
{
    int _amp_code = *amp_code, _tap_dly = *tap_dly, _tap_adv = *tap_adv;
    vtss_port_kr_coef_status_t status = VTSS_COEF_UPDATED;
    vtss_port_kr_status_codes_t sts_code = VTSS_KR_STS_UPDATED;
    vtss_port_kr_coef_type_t tap = coef2tap(coef_in);
    vtss_port_kr_coef_update_t action = coef2act(coef_in);

    switch (tap) {
    case VTSS_COEF_PRESET:
        _amp_code = 80;
        _tap_adv = 0;
        _tap_dly = 0;
        *status_out = ((VTSS_COEF_UPDATED << 4) | (VTSS_COEF_MAXIMUM << 2) |  VTSS_COEF_UPDATED);
        break;
    case VTSS_COEF_INIT:
        _amp_code = 80;
        _tap_adv = 4;
        _tap_dly = 22;
        *status_out = ((VTSS_COEF_UPDATED << 4) | (VTSS_COEF_UPDATED << 2) |  VTSS_COEF_UPDATED);
        break;
    case VTSS_COEF_CP1:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (0 <= _tap_dly && _tap_dly <= 31) {
            if (!verify_only) {
                if (action == VTSS_COEF_INCR) {
                    _tap_dly -= 2;
                } else {
                    _tap_dly += 2;
                }
            }
        } else {
            VTSS_E("Should not occur (_tap_dly=%d)",_tap_dly);
        }
        if (_tap_dly < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_BELOW_0;
        } else if (_tap_dly > 31) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_ABOVE_31;
        }
        break;
    case VTSS_COEF_C0:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (48 <= _amp_code && _amp_code <= 94) {
            if (!verify_only) {
                if (action == VTSS_COEF_INCR) {
                    _amp_code += 1;
                } else {
                    _amp_code -= 1;
                }
            }
        } else {
            VTSS_E("Should not occur (_amp_code=%d)",_amp_code);
        }
        if (_amp_code < 48) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_AMP_BELOW_48;
        } else if (_amp_code > 94) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_AMP_CODE_ABOVE_94;
        }
        break;
    case VTSS_COEF_CM1:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (0 <= _tap_adv && _tap_adv <= 31) {
            if (!verify_only) {
                if (action == VTSS_COEF_INCR) {
                    _tap_adv -= 2;
                } else {
                    _tap_adv += 2;
                }
            }
        } else {
            VTSS_E("Should not occur (_tap_adv=%d)",_tap_adv);
        }
        if (_tap_adv < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_BELOW_0;
        } else if (_tap_adv > 15) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_ABOVE_15;
        }
        break;
    default:{ VTSS_E("COEF tap not supported"); }
    }

    if (((action == VTSS_COEF_INCR) && (status == VTSS_COEF_MINIMUM)) ||
        ((action == VTSS_COEF_DECR) && (status == VTSS_COEF_MAXIMUM))) {
        VTSS_E("FAILURE! p:%d Tap:%s Action:%s  _pcs2pma=%d (in:%d) _tap_dly=%d (in:%d)  _tap_adv=%d (in:%d) (dly+adv=%d) -> Status:%s (Reason:%s)\n",
               p, vtss_kr_coef2txt(tap), vtss_kr_upd2txt(action), _amp_code,*amp_code,_tap_dly, *tap_dly, _tap_adv, *tap_adv,
               _tap_adv+_tap_dly, vtss_kr_status2txt(status), vtss_kr_sts_code2txt(sts_code));
    }

    *status_out = sts2rawsts(tap, status, *status_out);

    *tap_dly    = _tap_dly;
    *amp_code   = _amp_code;
    *tap_adv    = _tap_adv;

    return sts_code;
}

//BOOL c0_done[VTSS_PORTS] = {0};
// GUC algorithm for 25G @ 10G TxEQ KR tuning
static vtss_port_kr_status_codes_t fa_coef_status_25g_10g_calc(vtss_state_t *vtss_state, u32 p, const u16 coef_in,
                                                              u32 *amp_code, u32 *tap_dly, u32 *tap_adv, u16 *status_out, BOOL verify_only)
{
    u32 dG = 0, dCd = 0, dCa = 0, adv_dly_sum = 99, tap_adv_max = 99;
    int _amp_code = *amp_code, _tap_dly = *tap_dly, _tap_adv = *tap_adv;
    vtss_port_kr_coef_status_t status = VTSS_COEF_UPDATED;
    vtss_port_kr_status_codes_t sts_code = VTSS_KR_STS_UPDATED;
    vtss_port_kr_coef_type_t tap = coef2tap(coef_in);
    vtss_port_kr_coef_update_t action = coef2act(coef_in);
    BOOL *c0_done = &vtss_state->port.kr_store[p].c0_done;

    switch (tap) {
    case VTSS_COEF_PRESET:
        _amp_code = 80;
        _tap_adv = 0;
        _tap_dly = 0;
        *c0_done = FALSE;
        *status_out = ((VTSS_COEF_UPDATED << 4) | (VTSS_COEF_MAXIMUM << 2) | VTSS_COEF_UPDATED);
        break;
    case VTSS_COEF_INIT:
        _amp_code = 80;
        _tap_adv = 4;
        _tap_dly = 22;
        *c0_done = FALSE;
        *status_out = ((VTSS_COEF_UPDATED << 4) | (VTSS_COEF_UPDATED << 2) | VTSS_COEF_UPDATED);
        break;
    case VTSS_COEF_CP1:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (16 <= _amp_code && _amp_code <= 35) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCd = 3;
            }
        } else if (36 <= _amp_code && _amp_code <= 48) {
            if (0 <= _tap_dly && _tap_dly <= 9) {
                dG  = 4;
                dCd = 3;
            } else if (10 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCd = 2;
            }
        } else if (49 <= _amp_code && _amp_code <= 58) {
            if (0 <= _tap_dly && _tap_dly <= 4) {
                dG  = 4;
                dCd = 3;
            } else if (5 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCd = 2;
            }
        } else if (59 <= _amp_code && _amp_code <= 66) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCd = 2;
            }
        } else if (67 <= _amp_code && _amp_code <= 70) {
            if (0 <= _tap_dly && _tap_dly <= 17) {
                dG  = 3;
                dCd = 2;
            } else if (18 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCd = 1;
            }
        } else if (71 <= _amp_code && _amp_code <= 76) {
            if (0 <= _tap_dly && _tap_dly <= 18) {
                dG  = 3;
                dCd = 2;
                adv_dly_sum = 28;
            } else if (19 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCd = 1;
                adv_dly_sum = 28;
            }
        } else if (77 <= _amp_code && _amp_code <= 82) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCd = 2;
                adv_dly_sum = 28;
            }
        } else if (83 <= _amp_code && _amp_code <= 88) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCd = 2;
                if (!*c0_done) {
                    adv_dly_sum = 17;
                } else {
                    adv_dly_sum = _tap_dly + _tap_dly;
                }
            }
        } else if (89 <= _amp_code && _amp_code <= 94) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 1;
                dCd = 1;
                tap_adv_max = 13;
            }
        } else {
            VTSS_E("Should not occur (amp_code=%d)",_amp_code);
        }
        if (!verify_only) {
            _tap_dly = (action == VTSS_COEF_INCR) ? _tap_dly - dCd : _tap_dly + dCd;
            _amp_code = (action == VTSS_COEF_INCR) ? _amp_code - dG  : _amp_code + dG;
        }
        if (_amp_code < 16) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_AMP_CODE_BELOW_16;
        } else if (_amp_code > 94) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_AMP_CODE_ABOVE_94;
        } else if (_tap_dly < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_BELOW_0;
        } else if (_tap_dly > 31) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_ABOVE_31;
        } else if (_tap_adv > tap_adv_max) {
            status = (action == VTSS_COEF_INCR) ? VTSS_COEF_MAXIMUM : VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_ABOVE_LIMIT;
        } else if ((_tap_adv + _tap_dly) > adv_dly_sum) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_ADV_DLY_ABOVE_LIMIT;
        }
        break;
    case VTSS_COEF_C0:
        *c0_done = TRUE;
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (16 <= _amp_code && _amp_code <= 28) {
            if (0 <= _tap_dly && _tap_dly <= 12) {
                dG  = 5;
                dCd = 0;
            } else if (13 <= _tap_dly && _tap_dly <= 31) {
                dG  = 5;
                dCd = 1;
            }
        } else if (29 <= _amp_code && _amp_code <= 55) {
            if (0 <= _tap_dly && _tap_dly <= 9) {
                dG  = 4;
                dCd = 0;
            } else if (10 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCd = 1;
            }
        } else if (56 <= _amp_code && _amp_code <= 71) {
            if (0 <= _tap_dly && _tap_dly <= 9) {
                dG  = 3;
                dCd = 0;
            } else if (10 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCd = 1;
            }
        } else if (72 <= _amp_code && _amp_code <= 78) {
            if (0 <= _tap_dly && _tap_dly <= 12) {
                dG  = 3;
                dCd = 0;
            } else if (13 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCd = 1;
            }
        } else if (79 <= _amp_code && _amp_code <= 84) {
            if (0 <= _tap_dly && _tap_dly <= 18) {
                dG  = 3;
                dCd = 0;
                adv_dly_sum = 27;
            } else if (19 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCd = 1;
            }
        } else if (85 <= _amp_code && _amp_code <= 94) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCd = 0;
                adv_dly_sum = 25; // 24 Workaround
            }
        } else {
            VTSS_E("Should not occur (amp_code=%d)",_amp_code);
        }
        if (!verify_only) {
            _tap_dly = (action == VTSS_COEF_INCR) ? _tap_dly - dCd : _tap_dly + dCd;
            _amp_code = (action == VTSS_COEF_INCR) ? _amp_code + dG  : _amp_code - dG;
        }
        if (_amp_code < 16) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_AMP_CODE_BELOW_16;
        } else if (_amp_code > 94) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_AMP_CODE_ABOVE_94;
        } else if (_tap_dly < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_BELOW_0;
        } else if (_tap_dly > 31) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_ABOVE_31;
        } else if ((_tap_adv + _tap_dly) > adv_dly_sum) {
            status = (action == VTSS_COEF_INCR) ? VTSS_COEF_MAXIMUM : VTSS_COEF_MINIMUM; // Workaround
            sts_code = VTSS_KR_STS_ADV_DLY_ABOVE_LIMIT;
        }
        break;
    case VTSS_COEF_CM1:
        if (action == VTSS_COEF_HOLD) {
            status = VTSS_COEF_NOT_UPDATED;
            break;
        }
        if (16 <= _amp_code && _amp_code <= 47) {
            if (0 <= _tap_dly && _tap_dly <= 8) {
                dG  = 3;
                dCa = 3;
                dCd = 0;
            } else if (9 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCa = 3;
                dCd = 1;
            }
        } else if (48 <= _amp_code && _amp_code <= 53) {
            if (0 <= _tap_dly && _tap_dly <= 8) {
                dG  = 4;
                dCa = 3;
                dCd = 0;
            } else if (9 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCa = 3;
                dCd = 1;
            }
        } else if (54 <= _amp_code && _amp_code <= 69) {
            if (0 <= _tap_dly && _tap_dly <= 20) {
                dG  = 3;
                dCa = 2;
                dCd = 0;
            } else if (31 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCa = 2;
                dCd = 1;
            }
        } else if (70 <= _amp_code && _amp_code <= 74) {
            if (0 <= _tap_dly && _tap_dly <= 17) {
                dG  = 3;
                dCa = 2;
                dCd = 0;
            } else if (18 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCa = 2;
                dCd = 1;
            }
        } else if (75 <= _amp_code && _amp_code <= 82) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 3;
                dCa = 2;
                dCd = 0;
                adv_dly_sum = 27;
            }
        } else if (83 <= _amp_code && _amp_code <= 90) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 2;
                dCa = 2;
                dCd = 0;
                adv_dly_sum = 17;
            }
        } else if (91 <= _amp_code && _amp_code <= 94) {
            if (0 <= _tap_dly && _tap_dly <= 31) {
                dG  = 1;
                dCa = 1;
                dCd = 0;
                tap_adv_max = 13;
            }
        } else {
            VTSS_E("Should not occur (amp_code=%d)",_amp_code);
        }
        if (!verify_only) {
            _tap_dly = (action == VTSS_COEF_INCR) ? _tap_dly + dCd : _tap_dly - dCd;
            _amp_code = (action == VTSS_COEF_INCR) ? _amp_code - dG  : _amp_code + dG;
            _tap_adv = (action == VTSS_COEF_INCR) ? _tap_adv - dCa : _tap_adv + dCa;
        }
        if (_amp_code < 16) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_AMP_CODE_BELOW_16;
        } else if (_amp_code > 94) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_AMP_CODE_ABOVE_94;
        } else if (_tap_dly < 0) {
            status = VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_BELOW_0;
        } else if (_tap_dly > 31) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_DLY_ABOVE_31;
        } else if (_tap_adv < 0) {
            status = VTSS_COEF_MAXIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_BELOW_0;
        } else if ((_tap_adv + _tap_dly) > adv_dly_sum) {
            status = (action == VTSS_COEF_INCR) ? VTSS_COEF_MAXIMUM : VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_ADV_DLY_ABOVE_LIMIT;
        } else if (_tap_adv > tap_adv_max) {
            status = (action == VTSS_COEF_INCR) ? VTSS_COEF_MAXIMUM : VTSS_COEF_MINIMUM;
            sts_code = VTSS_KR_STS_TAP_ADV_ABOVE_LIMIT;
        }

        break;
    default:{ VTSS_E("COEF tap not supported"); }
    }

    if (status == VTSS_COEF_UPDATED) {
        // Common restrictions
        if (86 <= _amp_code && _amp_code <= 94) {
            if (_tap_adv + _tap_dly > 37) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (61 <= _amp_code && _amp_code <= 85) {
            if (_tap_adv + _tap_dly > 36) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (44 <= _amp_code && _amp_code <= 60) {
            if (_tap_adv + _tap_dly > 35) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (30 <= _amp_code && _amp_code <= 43) {
            if (_tap_adv + _tap_dly > 34) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (18 <= _amp_code && _amp_code <= 29) {
            if (_tap_adv + _tap_dly > 33) {
                status = VTSS_COEF_MINIMUM;
            }
        } else if (16 <= _amp_code && _amp_code <= 17) {
            if (_tap_adv + _tap_dly > 32) {
                status = VTSS_COEF_MINIMUM;
            }
        }
        if (status != VTSS_COEF_UPDATED) {
            sts_code = VTSS_KR_STS_ADV_DLY_OUT_OF_RANGE;
        }
    }
    if (tap == VTSS_COEF_CP1 || tap == VTSS_COEF_C0 || tap == VTSS_COEF_CM1) {
        if (((action == VTSS_COEF_INCR) && (status == VTSS_COEF_MINIMUM)) ||
            ((action == VTSS_COEF_DECR) && (status == VTSS_COEF_MAXIMUM))) {
            VTSS_E("FAILURE! p:%d Tap:%s Action:%s amp_code=%d->%d tap_dly=%d->%d tap_adv=%d->%d (dly+adv=%d) --> Status:%s (Reason:%s) (verify:%d)\n",
                   p, vtss_kr_coef2txt(tap), vtss_kr_upd2txt(action), *amp_code, _amp_code,*tap_dly,_tap_dly,*tap_adv,_tap_adv,
                   _tap_adv+_tap_dly, vtss_kr_status2txt(status), vtss_kr_sts_code2txt(sts_code), verify_only);
        }
    }

    *status_out = sts2rawsts(tap, status, *status_out);
    *tap_dly    = _tap_dly;
    *amp_code   = _amp_code;
    *tap_adv    = _tap_adv;

    return sts_code;;
}

vtss_rc fa_kr_coef2status(vtss_state_t *vtss_state,
                          const vtss_port_no_t port_no,
                          const u16 coef_in,
                          vtss_kr_status_results_t *const status_out)
{
    u32 port = VTSS_CHIP_PORT(port_no);
    u16 sts_tmp = 0;
    vtss_port_kr_temp_storage_t *st = &vtss_state->port.kr_store[port_no];
    vtss_port_kr_status_codes_t int_status;
    vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[port_no];
    u32 amplitude = st->amplitude, tap_dly=st->tap_dly, tap_adv=st->tap_adv;

    // 1. Calculate next settings based on coeficent request INIT/PRESET/INCR/DECR
    // 2. Verify calculated settings
    // 3. If PRESET/INIT or status == UPDATED: Apply calculated settings to the Tx-EQ
    // 4. Return Status report incl actual TxEq settings

    if (VTSS_PORT_IS_10G(port)) { // 10GSD @ 10G
        int_status = fa_coef_status_10g_calc(port_no, coef_in, &amplitude, &tap_dly, &tap_adv, &sts_tmp, 0); // 10G Calculate
        if (int_status == VTSS_KR_STS_UPDATED) {
            int_status = fa_coef_status_10g_calc(port_no, coef_in, &amplitude, &tap_dly, &tap_adv, &sts_tmp, 1); // 10G Verify
        }
    } else {     // 25GSD @ 25GG
        if (vtss_state->port.current_speed[port_no] == VTSS_SPEED_25G) {
            int_status = fa_coef_status_25g_calc(port_no, coef_in, &amplitude, &tap_dly, &tap_adv, &sts_tmp, 0); // 25G Calculate
            if (int_status == VTSS_KR_STS_UPDATED) {
                int_status = fa_coef_status_25g_calc(port_no, coef_in, &amplitude, &tap_dly, &tap_adv, &sts_tmp, 1);// 25G Verify
            }
        } else { // 25GSD @ 10G
            int_status = fa_coef_status_25g_10g_calc(vtss_state, port_no, coef_in, &amplitude, &tap_dly, &tap_adv, &sts_tmp, 0);    // 25GSD@10G Calculate
            if (int_status == VTSS_KR_STS_UPDATED) {
                int_status = fa_coef_status_25g_10g_calc(vtss_state, port_no, coef_in, &amplitude, &tap_dly, &tap_adv, &sts_tmp, 1);// 25GSD@10G Verify
            }
        }
    }

    if (coef2sts(sts_tmp) == VTSS_COEF_UPDATED ||
        coef2tap(coef_in) == VTSS_COEF_PRESET ||
        coef2tap(coef_in) == VTSS_COEF_INIT) {
        st->amplitude = amplitude;
        st->tap_dly = tap_dly;
        st->tap_adv = tap_adv;
        if (!kr->train.no_eq_apply) { // for debug support
            VTSS_RC(fa_port_kr_tap_set(vtss_state, port_no, tap_dly, tap_adv, amplitude)); // Apply the settings
        }
    }
    status_out->status = sts_tmp; // Return status report
    status_out->cm1 = tap_adv; // Also return the EQ values for debug purposes
    status_out->cp1 = tap_dly;
    status_out->c0 = amplitude;

    return VTSS_RC_OK;
}

vtss_rc fa_serdes_40b_mode(vtss_state_t *vtss_state, u32 port_no)
{
    u32 indx = vtss_fa_port2sd_indx(vtss_state, port_no);
    u32 sd25g_tgt = VTSS_TO_SD25G_LANE(indx);

    // Change back to 25G 40 bit mode

    REG_WR(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt), 0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_40(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN(1),
            VTSS_M_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN);
    REG_WR(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt), 0xFF);

    REG_WRM(VTSS_SD25G_TARGET_CMU_01(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_01_CFG_TX_RSTB_15_8(0),
            VTSS_M_SD25G_TARGET_CMU_01_CFG_TX_RSTB_15_8);

    REG_WRM(VTSS_SD25G_TARGET_CMU_00(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_00_CFG_TX_RSTB_7_0(0),
            VTSS_M_SD25G_TARGET_CMU_00_CFG_TX_RSTB_7_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_1A(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_2_0(4),
            VTSS_M_SD25G_TARGET_CMU_1A_R_DWIDTHCTRL_2_0);

    REG_WRM(VTSS_SD25G_TARGET_CMU_30(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0(0) |
            VTSS_F_SD25G_TARGET_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0(0),
            VTSS_M_SD25G_TARGET_CMU_30_R_TXFIFO_CK_DIV_PMAD_2_0 |
            VTSS_M_SD25G_TARGET_CMU_30_R_RXFIFO_CK_DIV_PMAD_2_0);

    REG_WR(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt), 0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_18(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_RXDIV_SEL_2_0(3),
            VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_RXDIV_SEL_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_0C(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0(3),
            VTSS_M_SD25G_TARGET_LANE_0C_LN_CFG_PMA_TX_CK_BITWIDTH_2_0);

    REG_WRM(VTSS_SD25G_TARGET_LANE_40(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN(0),
            VTSS_M_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN);

    REG_WRM(VTSS_SD25G_TARGET_LANE_40(sd25g_tgt),
            VTSS_F_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN(1),
            VTSS_M_SD25G_TARGET_LANE_40_LN_R_CDR_RSTN);

    REG_WR(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt), 0xFF);

    REG_WRM(VTSS_SD25G_TARGET_CMU_01(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_01_CFG_TX_RSTB_15_8(0xFF),
            VTSS_M_SD25G_TARGET_CMU_01_CFG_TX_RSTB_15_8);

    REG_WRM(VTSS_SD25G_TARGET_CMU_00(sd25g_tgt),
            VTSS_F_SD25G_TARGET_CMU_00_CFG_TX_RSTB_7_0(0xFF),
            VTSS_M_SD25G_TARGET_CMU_00_CFG_TX_RSTB_7_0);

//    VTSS_MSLEEP(1);

    return VTSS_RC_OK;
}

vtss_rc fa_serdes_tx_eq_tune(vtss_state_t *vtss_state, const vtss_debug_printf_t pr,
                             u32 port_no, vtss_port_kr_coef_type_t coef, vtss_port_kr_coef_update_t action)
{
    vtss_kr_status_results_t status_out;
    u16 coef_in = 0;
    u16 action_sts = 0;
    char action_out[20];

    if (coef == VTSS_COEF_PRESET) {
        coef_in = BT(13);
    } else if (coef == VTSS_COEF_INIT) {
        coef_in = BT(12);
    } else if ((coef == VTSS_COEF_CM1) && (action == VTSS_COEF_INCR)) {
          coef_in = 0x1;
    } else if ((coef == VTSS_COEF_CM1) && (action == VTSS_COEF_DECR)) {
          coef_in = 0x2;
    } else if ((coef == VTSS_COEF_C0) && (action == VTSS_COEF_INCR)) {
          coef_in = 2 << 0x1;
    } else if ((coef == VTSS_COEF_C0) && (action == VTSS_COEF_DECR)) {
          coef_in = 2 << 0x2;
    } else if ((coef == VTSS_COEF_CP1) && (action == VTSS_COEF_INCR)) {
          coef_in = 4 << 0x1;
    } else if ((coef == VTSS_COEF_CP1) && (action == VTSS_COEF_DECR)) {
          coef_in = 4 << 0x2;
    } else {
        pr("unsupported choice\n");
        return VTSS_RC_OK;
    }

    fa_kr_coef2status(vtss_state, port_no, coef_in, &status_out);

    if ((status_out.status & 0x3) > 0) {
        action_sts = status_out.status & 0x3;
    } else if ((status_out.status & 0xc) > 0) {
        action_sts = (status_out.status >> 2) & 3;
    } else if ((status_out.status & 0x30) > 0 ) {
        action_sts = (status_out.status >> 4) & 3;
    } else {
        action_sts = 0;
    }

    if (action_sts == 0) {
        VTSS_SPRINTF(action_out, "NOT_UPDATED");
    } else if (action_sts == 1) {
        VTSS_SPRINTF(action_out, "UPDATED");
    } else if (action_sts == 2) {
        VTSS_SPRINTF(action_out, "MIN");
    } else if (action_sts == 3) {
        VTSS_SPRINTF(action_out, "MAX");
    }
    pr("Results: %s [CM(tap_adv):%d CP(tap_dly):%d C0(amp):%d]\n", action_out, status_out.cm1, status_out.cp1, status_out.c0);

    return VTSS_RC_OK;
}


#endif /* VTSS_FEATURE_PORT_KR_IRQ */


static vtss_rc fa_port_kr_square_wave(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no, BOOL ena)
{
    u32 indx, type, sd_tgt;
    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        // User define square wave
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_96(sd_tgt), 0xAA);
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_97(sd_tgt), 0xAA);
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_98(sd_tgt), 0xAA);
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_99(sd_tgt), 0xAA);
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_9A(sd_tgt), 0xAA);
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_9B(sd_tgt), 0xAA);
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_9C(sd_tgt), 0xAA);
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_9D(sd_tgt), 0xAA);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_76(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_76_R_BIST_EN(ena),
                VTSS_M_SD10G_LANE_TARGET_LANE_76_R_BIST_EN);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_77(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK(ena),
                VTSS_M_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_74(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_74_R_BIST_TIMER_7_0(0),
                VTSS_M_SD10G_LANE_TARGET_LANE_74_R_BIST_TIMER_7_0);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_75(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_75_R_BIST_TIMER_15_8(0),
                VTSS_M_SD10G_LANE_TARGET_LANE_75_R_BIST_TIMER_15_8);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_76(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_76_R_BIST_MODE_2_0(7) | // User defined pattern
                VTSS_F_SD10G_LANE_TARGET_LANE_76_R_FREE_RUN_MODE(1) |
                VTSS_F_SD10G_LANE_TARGET_LANE_76_R_BIST_ERRINJEC(0),
                VTSS_M_SD10G_LANE_TARGET_LANE_76_R_BIST_MODE_2_0 |
                VTSS_M_SD10G_LANE_TARGET_LANE_76_R_FREE_RUN_MODE |
                VTSS_M_SD10G_LANE_TARGET_LANE_76_R_BIST_ERRINJEC);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_77(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_77_R_BIST_ERRSTOP(0) |
                VTSS_F_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK_ZERO(1),
                VTSS_M_SD10G_LANE_TARGET_LANE_77_R_BIST_ERRSTOP |
                VTSS_M_SD10G_LANE_TARGET_LANE_77_R_BIST_CHK_ZERO);

    } else {
        // FA_SERDES_TYPE_25G

        REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xFF),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

        // User define square wave
        REG_WR(VTSS_SD25G_TARGET_CMU_21(sd_tgt), 0xAA);
        REG_WR(VTSS_SD25G_TARGET_CMU_22(sd_tgt), 0xAA);
        REG_WR(VTSS_SD25G_TARGET_CMU_23(sd_tgt), 0xAA);
        REG_WR(VTSS_SD25G_TARGET_CMU_24(sd_tgt), 0xAA);
        REG_WR(VTSS_SD25G_TARGET_CMU_25(sd_tgt), 0xAA);
        REG_WR(VTSS_SD25G_TARGET_CMU_26(sd_tgt), 0xAA);
        REG_WR(VTSS_SD25G_TARGET_CMU_27(sd_tgt), 0xAA);
        REG_WR(VTSS_SD25G_TARGET_CMU_28(sd_tgt), 0xAA);

        REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

        REG_WRM(VTSS_SD25G_TARGET_LANE_33(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_33_LN_R_BIST_EN(ena),
                VTSS_M_SD25G_TARGET_LANE_33_LN_R_BIST_EN);

        REG_WRM(VTSS_SD25G_TARGET_LANE_34(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_34_LN_R_BIST_CHK(ena),
                VTSS_M_SD25G_TARGET_LANE_34_LN_R_BIST_CHK);

        REG_WRM(VTSS_SD25G_TARGET_LANE_46(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_46_LN_R_BIST_TIMER_7_0(0),
                VTSS_M_SD25G_TARGET_LANE_46_LN_R_BIST_TIMER_7_0);

        REG_WRM(VTSS_SD25G_TARGET_LANE_47(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_47_LN_R_BIST_TIMER_15_8(0),
                VTSS_M_SD25G_TARGET_LANE_47_LN_R_BIST_TIMER_15_8);

        REG_WRM(VTSS_SD25G_TARGET_LANE_33(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_33_LN_R_BIST_MODE_2_0(7),
                VTSS_M_SD25G_TARGET_LANE_33_LN_R_BIST_MODE_2_0);

        REG_WRM(VTSS_SD25G_TARGET_LANE_34(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_34_LN_R_FREE_RUN_MODE(1),
                VTSS_M_SD25G_TARGET_LANE_34_LN_R_FREE_RUN_MODE);

        REG_WRM(VTSS_SD25G_TARGET_LANE_33(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_33_LN_R_BIST_ERRINJEC(0),
                VTSS_M_SD25G_TARGET_LANE_33_LN_R_BIST_ERRINJEC);

        REG_WRM(VTSS_SD25G_TARGET_LANE_34(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_34_LN_R_BIST_ERRSTOP(0) |
                VTSS_F_SD25G_TARGET_LANE_34_LN_R_BIST_CHK_ZERO(1),
                VTSS_M_SD25G_TARGET_LANE_34_LN_R_BIST_ERRSTOP |
                VTSS_M_SD25G_TARGET_LANE_34_LN_R_BIST_CHK_ZERO);

        REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xFF),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);
    }
    pr("Square wave %s\n", ena ? "started" : "stopped");
    return VTSS_RC_OK;
}


static vtss_rc fa_serdes_dfe_set(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no, BOOL ena)
{
    u32 indx, type, sd_tgt, sd_lane_tgt = 0;
    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);
    if (type == FA_SERDES_TYPE_6G) {
        sd_lane_tgt = VTSS_TO_SD_LANE(indx);
    } else if (type == FA_SERDES_TYPE_10G) {
        sd_lane_tgt = VTSS_TO_SD_LANE(indx+VTSS_SERDES_10G_START);
    } else {
        sd_lane_tgt = VTSS_TO_SD_LANE(indx+VTSS_SERDES_25G_START);
    }

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_EN_DFEDIG(ena) |
                VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN(ena) |
                VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD(!ena) |
                VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD(!ena),
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_EN_DFEDIG |
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN |
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD |
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_22(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_22_CFG_DFETAP_EN_5_1(ena ? 0x1f : 0),
                VTSS_M_SD10G_LANE_TARGET_LANE_22_CFG_DFETAP_EN_5_1);
        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1A(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_1A_CFG_PI_DFE_EN(ena),
                VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_DFE_EN);

        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_0D(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_SUMMER_EN);

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_31(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DFEDIG(ena),
                VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DFEDIG);

        if (!ena) {
            REG_WRM_SET(VTSS_SD_LANE_TARGET_SD_LANE_CFG(sd_lane_tgt),
                    VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_LANE_RST);
            VTSS_MSLEEP(1);
            REG_WRM_CLR(VTSS_SD_LANE_TARGET_SD_LANE_CFG(sd_lane_tgt),
                        VTSS_M_SD_LANE_TARGET_SD_LANE_CFG_LANE_RST);
        }
        if (ena) {
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1C(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_1C_CFG_DFEDIG_BYP_5_0(0),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1C_CFG_DFEDIG_BYP_5_0);
        }

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_31(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DFEDIG(ena),
                VTSS_M_SD10G_LANE_TARGET_LANE_31_CFG_RSTN_DFEDIG);


    } else {
        REG_WRM(VTSS_SD25G_TARGET_LANE_0E(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG(ena),
                VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG);
        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_0D(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_DFECK_EN);
        REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD(!ena),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD);
        REG_WRM(VTSS_SD25G_TARGET_LANE_0F(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_0F_LN_CFG_DFETAP_EN_5_1(ena ? 0x1F : 0),
                VTSS_M_SD25G_TARGET_LANE_0F_LN_CFG_DFETAP_EN_5_1);
        REG_WRM(VTSS_SD25G_TARGET_LANE_18(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD(!ena),
                    VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD);
        REG_WRM(VTSS_SD25G_TARGET_LANE_1D(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_1D_LN_CFG_PI_DFE_EN(ena),
                VTSS_M_SD25G_TARGET_LANE_1D_LN_CFG_PI_DFE_EN);
        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_0D(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_SUMMER_EN);
        REG_WRM(VTSS_SD25G_TARGET_LANE_2E(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG(ena),
                VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG);
        REG_WRM_SET(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                    VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_LANE_RST);
        VTSS_MSLEEP(1);
        REG_WRM_CLR(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                    VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_LANE_RST);
    }

    pr("DFE %s\n", ena ? "enabled" : "disabled");
    return VTSS_RC_OK;
}


static vtss_rc fa_serdes_oscal_set(vtss_state_t *vtss_state, u32 sd_tgt, u32 port_no)
{
    u32 val;
    REG_WRM_CLR(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);
    REG_WRM_SET(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD);
    REG_RD(VTSS_SD25G_TARGET_LANE_44(sd_tgt), &val);
    u32 read_cfg_reserve = VTSS_X_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0(val);
    REG_WRM(VTSS_SD25G_TARGET_LANE_44(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0(read_cfg_reserve & 0xbf),
            VTSS_M_SD25G_TARGET_LANE_44_LN_CFG_RX_RESERVE_7_0);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_0D(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_0D_LN_CFG_DMUX_PD);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_0E(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_DMUX_CLK_PD);
    REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD(0),
            VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD);
    REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD(1),
            VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD);
    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
            VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xFF),
            VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

   return VTSS_RC_OK;
}

static vtss_rc fa_serdes_oscal_ena(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no)
{
    u32 indx, type, sd_tgt;
    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);
    VTSS_RC(fa_serdes_oscal_set(vtss_state, sd_tgt, port_no));

    pr("Offset calibration done\n");
   return VTSS_RC_OK;
}

static vtss_rc fa_serdes_dfe_read(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no)
{
    u32 indx, type, val, sd_tgt;
    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C5(sd_tgt), &val);
        pr("ln_h1 (max 0x1F)  :0x%x\n", val);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C6(sd_tgt), &val);
        pr("ln_h2 (max 0x1F)  :0x%x\n", val);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C7(sd_tgt), &val);
        pr("ln_h3 (max 0xF)   :0x%x\n", val);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C8(sd_tgt), &val);
        pr("ln_h4 (max 0xF)   :0x%x\n", val);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C9(sd_tgt), &val);
        pr("ln_h5 (max 0xF)   :0x%x\n", val);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_CA(sd_tgt), &val);
        pr("ln_dlev (max 0x7F):0x%x\n", val);
    } else {
        REG_RD(VTSS_SD25G_TARGET_LANE_CA(sd_tgt), &val);
        pr("ln_h1 (max 0x1F)  :0x%x\n", val);
        REG_RD(VTSS_SD25G_TARGET_LANE_CB(sd_tgt), &val);
        pr("ln_h2 (max 0x1F)  :0x%x\n", val);
        REG_RD(VTSS_SD25G_TARGET_LANE_CC(sd_tgt), &val);
        pr("ln_h3 (max 0xF)   :0x%x\n", val);
        REG_RD(VTSS_SD25G_TARGET_LANE_CD(sd_tgt), &val);
        pr("ln_h4 (max 0xF)   :0x%x\n", val);
        REG_RD(VTSS_SD25G_TARGET_LANE_CE(sd_tgt), &val);
        pr("ln_h5 (max 0xF)   :0x%x\n", val);
        REG_RD(VTSS_SD25G_TARGET_LANE_CF(sd_tgt), &val);
        pr("ln_dlev (max 0x7F):0x%x\n", val);

    }

   return VTSS_RC_OK;
}

static vtss_rc fa_serdes_vga_adjust(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no)
{
    u32 indx, type, sd_tgt;
    u32 eye_height = 0, highest = 0;

    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);

    if (pr) {
        pr("Adjust %s VGA\n",type == FA_SERDES_TYPE_10G ? "10G" : type == FA_SERDES_TYPE_6G ? "6G" : "25G");
    }

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        int cfg_eq_res = 0xf;
        u32 cfg_eq_res_best;

        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0B(sd_tgt), &cfg_eq_res_best);
        cfg_eq_res_best = VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(cfg_eq_res_best);

        while (cfg_eq_res >= 0) {
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0B(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(cfg_eq_res),
                    VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0);
            VTSS_NSLEEP(10000);
            fa_kr_eye_height(vtss_state, port_no, 3, &eye_height);
            if (pr)
                pr("cfg_eq_res:%d eye_height:%d\n",cfg_eq_res, eye_height);

            if (eye_height > highest) {
                highest = eye_height;
                cfg_eq_res_best = (u32)cfg_eq_res;
            }
            cfg_eq_res--;
        }

        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0B(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(cfg_eq_res_best),
                VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0);
        if (pr)
            pr("Using cfg_eq_res:%d \n",cfg_eq_res_best);

    } else if (type == FA_SERDES_TYPE_25G) {
        u32 ln_cfg_vga_ctrl = 4;
        u32 ln_cfg_vga_ctrl_best;

        REG_RD(VTSS_SD25G_TARGET_LANE_21(sd_tgt), &ln_cfg_vga_ctrl_best);
        ln_cfg_vga_ctrl_best = VTSS_F_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(ln_cfg_vga_ctrl_best);

        while (ln_cfg_vga_ctrl < 15) {
            REG_WRM(VTSS_SD25G_TARGET_LANE_21(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(ln_cfg_vga_ctrl),
                    VTSS_M_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0);
            VTSS_NSLEEP(10000);
            fa_kr_eye_height(vtss_state, port_no, 3, &eye_height);
            if (pr)
                pr("ln_cfg_vga_ctrl:%d eye_height:%d\n",ln_cfg_vga_ctrl, eye_height);

            if (eye_height > highest) {
                highest = eye_height;
                ln_cfg_vga_ctrl_best = ln_cfg_vga_ctrl;
            }
            ln_cfg_vga_ctrl++;
        }

        REG_WRM(VTSS_SD25G_TARGET_LANE_21(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(ln_cfg_vga_ctrl_best),
                VTSS_M_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0);

        if (pr)
            pr("Using ln_cfg_vga_ctrl:%d \n",ln_cfg_vga_ctrl_best);
    } else {
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_serdes_eqr_adjust(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no)
{
    u32 indx, type, sd_tgt;
    u32 cfg_vga_ctrl, vga_ctrl_best = 0;
    u32 eye_height = 0, highest = 0;

    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt), &vga_ctrl_best);
        vga_ctrl_best = VTSS_F_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(vga_ctrl_best),
        cfg_vga_ctrl = 0x8;
    } else {
        REG_RD(VTSS_SD25G_TARGET_LANE_22(sd_tgt), &vga_ctrl_best);
        vga_ctrl_best = VTSS_F_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(vga_ctrl_best);
        cfg_vga_ctrl = 0x4;
    }

    if (pr)
        pr("Adjust %s EQR, start from %d :\n",type == FA_SERDES_TYPE_10G ? "10G" : type == FA_SERDES_TYPE_6G ? "6G" : "25G", cfg_vga_ctrl);

    while (cfg_vga_ctrl <= 15) {
        if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(cfg_vga_ctrl),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0);
        } else {
            REG_WRM(VTSS_SD25G_TARGET_LANE_22(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(cfg_vga_ctrl),
                    VTSS_M_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0);
        }
        VTSS_NSLEEP(10000);
        fa_kr_eye_height(vtss_state, port_no, 3, &eye_height);
        if (pr)
            pr("eqr_val:%d eye_height:%d\n",cfg_vga_ctrl, eye_height);

        if (eye_height > highest) {
            highest = eye_height;
            vga_ctrl_best = cfg_vga_ctrl;
        }

        cfg_vga_ctrl++;
    }

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(vga_ctrl_best),
                VTSS_M_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0);
    } else {
        REG_WRM(VTSS_SD25G_TARGET_LANE_22(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(vga_ctrl_best),
                VTSS_M_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0);
    }

    if (pr)
        pr("Using eqr_ctrl:%d \n",vga_ctrl_best);


    return VTSS_RC_OK;
}

static vtss_rc fa_serdes_eqc_adjust(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no)
{
    u32 indx, type, sd_tgt;
    u32 cfg_eqc_force, cfg_eqc_force_best = 0;
    u32 eye_height = 0, highest = 0;

    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0E(sd_tgt), &cfg_eqc_force_best);
        cfg_eqc_force_best = VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(cfg_eqc_force_best),
        cfg_eqc_force = 0xA;
    } else {
        REG_RD(VTSS_SD25G_TARGET_LANE_1C(sd_tgt), &cfg_eqc_force_best);
        cfg_eqc_force_best = VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(cfg_eqc_force_best);
        cfg_eqc_force = 0x8;
    }

    if (pr)
        pr("Adjust %s EQC, start from %d :\n",type == FA_SERDES_TYPE_10G ? "10G" : type == FA_SERDES_TYPE_6G ? "6G" : "25G", cfg_eqc_force);



    while (cfg_eqc_force <= 15) {

        if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0E(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(cfg_eqc_force),
                    VTSS_M_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0);
        } else {
            REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(cfg_eqc_force),
                    VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0);
        }
        VTSS_NSLEEP(10000); // 10usec
        fa_kr_eye_height(vtss_state, port_no, 3, &eye_height);
        if (pr)
            pr("cfg_eqc_force:%d eye_height:%d\n",cfg_eqc_force, eye_height);

        if (eye_height > highest) {
            highest = eye_height;
            cfg_eqc_force_best = cfg_eqc_force;
        }

        cfg_eqc_force++;
    }

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0E(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(cfg_eqc_force_best),
                VTSS_M_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0);
    } else {
        REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(cfg_eqc_force_best),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0);
    }

    if (pr)
        pr("Using cfg_eqc_force:%d \n",cfg_eqc_force_best);

    return VTSS_RC_OK;
}

vtss_rc fa_serdes_ctle_adjust(vtss_state_t *vtss_state, const vtss_debug_printf_t pr,
                              u32 port_no, BOOL ro, u32 *vga, u32 *eqr, u32 *eqc)
{

    u32 indx, type, sd_tgt;
    u32 cfg_eq_res, cfg_eqc_force, cfg_vga_ctrl;
    u32 eye_height = 0;

    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);

    if (pr != NULL || ro) {
        if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
            REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0B(sd_tgt), &cfg_eq_res);
            cfg_eq_res = VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(cfg_eq_res);
            REG_RD(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt), &cfg_vga_ctrl);
            cfg_vga_ctrl = VTSS_X_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(cfg_vga_ctrl);
            REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0E(sd_tgt), &cfg_eqc_force);
            cfg_eqc_force = VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(cfg_eqc_force);
        } else {
            REG_RD(VTSS_SD25G_TARGET_LANE_21(sd_tgt), &cfg_eq_res);
            cfg_eq_res = VTSS_X_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(cfg_eq_res);
            REG_RD(VTSS_SD25G_TARGET_LANE_22(sd_tgt), &cfg_vga_ctrl);
            cfg_vga_ctrl = VTSS_X_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(cfg_vga_ctrl);
            REG_RD(VTSS_SD25G_TARGET_LANE_1C(sd_tgt), &cfg_eqc_force);
            cfg_eqc_force = VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(cfg_eqc_force);
        }
        if (ro) {
            *vga = cfg_eq_res;
            *eqr = cfg_vga_ctrl;
            *eqc = cfg_eqc_force;
            return VTSS_RC_OK;
        } else {
            fa_kr_eye_height(vtss_state, port_no, 3, &eye_height);
            pr("Before %s CTLE tuning:\n", type == FA_SERDES_TYPE_10G ? "10G" : type == FA_SERDES_TYPE_6G ? "6G" : "25G");
            pr("VGA               :%d\n",cfg_eq_res);
            pr("EQR               :%d\n",cfg_vga_ctrl);
            pr("EQC               :%d\n",cfg_eqc_force);
            pr("Eye height        :%d\n",eye_height);
        }
    }

    VTSS_RC(fa_serdes_vga_adjust(vtss_state, pr, port_no));
    VTSS_RC(fa_serdes_eqr_adjust(vtss_state, pr, port_no));
    VTSS_RC(fa_serdes_eqc_adjust(vtss_state, pr, port_no));
    VTSS_RC(fa_serdes_vga_adjust(vtss_state, pr, port_no));

    if (pr == NULL) {
        return VTSS_RC_OK;
    }

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0B(sd_tgt), &cfg_eq_res);
        cfg_eq_res = VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(cfg_eq_res);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt), &cfg_vga_ctrl);
        cfg_vga_ctrl = VTSS_X_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(cfg_vga_ctrl);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0E(sd_tgt), &cfg_eqc_force);
        cfg_eqc_force = VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(cfg_eqc_force);
    } else  {
        REG_RD(VTSS_SD25G_TARGET_LANE_21(sd_tgt), &cfg_eq_res);
        cfg_eq_res = VTSS_X_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(cfg_eq_res);
        REG_RD(VTSS_SD25G_TARGET_LANE_22(sd_tgt), &cfg_vga_ctrl);
        cfg_vga_ctrl = VTSS_X_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(cfg_vga_ctrl);
        REG_RD(VTSS_SD25G_TARGET_LANE_1C(sd_tgt), &cfg_eqc_force);
        cfg_eqc_force = VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(cfg_eqc_force);
    }
    fa_kr_eye_height(vtss_state, port_no, 3, &eye_height);

    pr("After %s CTLE tuning:\n", type == FA_SERDES_TYPE_10G ? "10G" : type == FA_SERDES_TYPE_6G ? "6G" : "25G");
    pr("VGA               :%d\n",cfg_eq_res);
    pr("EQR               :%d\n",cfg_vga_ctrl);
    pr("EQC               :%d\n",cfg_eqc_force);
    pr("Eye height        :%d\n",eye_height);

    return VTSS_RC_OK;
}


static vtss_rc fa_serdes_ctle_read(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, u32 port_no)
{
    u32 indx, type, val, sd_tgt;

    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &type));
    sd_tgt = fa_get_lane_target(type, indx);

    if (type == FA_SERDES_TYPE_6G || type == FA_SERDES_TYPE_10G) {
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0D(sd_tgt), &val);
        pr("CTLE in manuel mode  :%d\n",VTSS_X_SD10G_LANE_TARGET_LANE_0D_CFG_EQR_BYP(val));
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt), &val);
        pr("VGA resistor set to  :%d\n",VTSS_X_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(val));
        pr("VGA capacitor set to :%d\n",VTSS_X_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CP_2_0(val));
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0E(sd_tgt), &val);
        pr("CTLE C set to        :%d\n",VTSS_X_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(val));
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_0B(sd_tgt), &val);
        pr("CTLE GAIN set to     :%d\n",VTSS_X_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(val));
    } else {
        REG_RD(VTSS_SD25G_TARGET_LANE_23(sd_tgt), &val);
        pr("VGA in manuel mode  :%d\n",VTSS_X_SD25G_TARGET_LANE_23_LN_CFG_VGA_BYP(val));
        REG_RD(VTSS_SD25G_TARGET_LANE_1F(sd_tgt), &val);
        pr("CTLE in manuel mode  :%d\n",VTSS_X_SD25G_TARGET_LANE_1F_LN_CFG_EQR_BYP(val));
        REG_RD(VTSS_SD25G_TARGET_LANE_21(sd_tgt), &val);
        pr("VGA set to           :%d\n",VTSS_X_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(val));
        REG_RD(VTSS_SD25G_TARGET_LANE_22(sd_tgt), &val);
        pr("CTLE R set to        :%d\n",VTSS_X_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(val));
        REG_RD(VTSS_SD25G_TARGET_LANE_1C(sd_tgt), &val);
        pr("CTLE C set to        :%d\n",VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(val));
    }

    return VTSS_RC_OK;

}

static vtss_rc fa_serdes_10g_eye_dimension(vtss_state_t *vtss_state, u32 sd_tgt, u32 *height, vtss_port_no_t port_no)
{
    u32 val, cnt = 0;

    while (cnt <= 500) {
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D0(sd_tgt), &val);
        if (VTSS_X_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE(val)) {
            break;
        }
        VTSS_NSLEEP(1000); // 1 us
        cnt++;
    }
    if (VTSS_X_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE(val) == 0) {
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN);
        VTSS_E("Timed out after %d ms - bailing out",cnt);
        return VTSS_RC_ERROR;
    }
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D0(sd_tgt), &val);

    if (VTSS_X_SD10G_LANE_TARGET_LANE_D0_FAST_EYE_SCAN_FAIL(val) > 0) {
        *height = 0;
        return VTSS_RC_ERROR;
    }
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D1(sd_tgt), height);

    return VTSS_RC_OK;
}

static vtss_rc fa_serdes_10g_normal_eye(vtss_state_t *vtss_state, u32 sd_tgt, const vtss_debug_printf_t pr)
{
    u32 indx, vref, val, cnt = 0;
    u32 eye_res[140][10] = {0};
    u32 vref_cnt = 0;
    char buf[100];
    u32 bottom = 0;
    BOOL top_found = 0;
    BOOL bottom_found = 0;


    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_DB(sd_tgt), &vref);

    while (TRUE) {
        while (cnt <= 500) {
            REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D0(sd_tgt), &val);
            if (VTSS_X_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE(val)) {
                break;
            }
            VTSS_MSLEEP(1);
            cnt++;
        }
        if (VTSS_X_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE(val) == 0) {
            REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                        VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN);
            VTSS_E("Timed out after %d ms - bailing out",cnt);
            return VTSS_RC_ERROR;
        }
        indx = 0;
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D1(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D2(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D3(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D4(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D5(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D6(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D7(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D8(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D9(sd_tgt), &eye_res[vref_cnt][indx++]);

        if ((!bottom_found || !top_found) && vref_cnt > 1) {
            u32 sum = 0;
            for (u16 a = 0; a < 8; a++) {
                sum += eye_res[vref_cnt][a];
            }
//            printf("vref:%d bott:%d top:%d sum:%d\n",vref_cnt,bottom_found, top_found, sum);
            if (!bottom_found && (sum != 2040)) {
                bottom = vref_cnt;
                bottom_found = 1;
            }

            if (!top_found && bottom_found && (sum == 2040)) {
                if (vref_cnt - bottom > 5) {
                    top_found = 1;
                }
            }
        }

        // EYE scan enable
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ADD_VOLT);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ADD_VOLT);
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_DB(sd_tgt), &vref);

        if (vref_cnt == 127) {
            break;
        }
        vref_cnt++;
    }
    if (pr != NULL) {
        for (int i = vref_cnt; i >= 0; i--) {
            if ((i % 4 == 0) || i == 127) {
                (void)buf_set(buf, eye_res[i]);
                pr("%-5d %s\n", i, buf);
            }
        }
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_10g_kr_vref_incr(vtss_state_t *vtss_state, u32 sd_tgt, u32 inc)
{

    for (u32 m = 0; m < inc; m++) {
        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_RSTN(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_STEPSIZE(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_FOM_SEL(1)  |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ADD_VOLT(0) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_MAN_VOLT_EN(0));

        REG_WR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_RSTN(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_STEPSIZE(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_FOM_SEL(1)  |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_ADD_VOLT(1) |
               VTSS_F_SD10G_LANE_TARGET_LANE_2B_CFG_MAN_VOLT_EN(0));
    }
    return VTSS_RC_OK;
}
static vtss_rc fa_serdes_10g_kr_eye(vtss_state_t *vtss_state, u32 sd_tgt, const vtss_debug_printf_t pr, u32 *height)
{
    u32 val, cnt = 0;
    u32 eye_res[10] = {0};
    u32 vref_cnt = 0;
    u32 top = 0;
    u32 bottom = 0;
    BOOL top_found = 0;
    BOOL bottom_found = 0;
    BOOL first = 1;
    u32 repeat;

    for (u32 y = 0; y < 9; y++) {
        eye_res[y] = 0xff;
    }

    while (TRUE) {
        cnt = 0;
        while (cnt <= 500) {
            REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D0(sd_tgt), &val);
            if (VTSS_X_SD10G_LANE_TARGET_LANE_D0_ISCAN_DONE(val)) {
                break;
            }
            VTSS_NSLEEP(1000); // 1us
            cnt++;
        }

        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D3(sd_tgt), &eye_res[2]);
        if (bottom_found) {
            if (eye_res[2] != 0xFF) {
                if (first) {
                    first = 0;
                    repeat = 10;
                } else if (eye_res[2] == 0) {
                    repeat = 5;
                } else {
                    repeat = 2;
                }
                fa_10g_kr_vref_incr(vtss_state, sd_tgt, repeat);
                vref_cnt += repeat;
                continue;
            } else {
                fa_10g_kr_vref_incr(vtss_state, sd_tgt, 2);
                vref_cnt += 2;
            }
        }
        REG_RD(VTSS_SD10G_LANE_TARGET_LANE_D4(sd_tgt), &eye_res[3]);

        if (!bottom_found || !top_found) {
            u32 sum = 0;
            for (u16 a = 0; a < 8; a++) {
                sum += eye_res[a];
            }

            if (!bottom_found && (sum != 2040)) {
                bottom = vref_cnt;
                bottom_found = 1;
            }

            if (!top_found && bottom_found && (sum == 2040)) {
                if (vref_cnt - bottom > 3) {
                    top = vref_cnt;
                    top_found = 1;
                }
            }

            if (top_found && bottom_found) {
                *height = top-bottom;
                break;
            }
        }
        if (vref_cnt < 40) {
            fa_10g_kr_vref_incr(vtss_state, sd_tgt, 40);
            vref_cnt += 40;
        }

        if (!bottom_found) {
            fa_10g_kr_vref_incr(vtss_state, sd_tgt, 2);
            vref_cnt += 2;
        }

        if (vref_cnt >= 127) {
            break;
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_serdes_25g_normal_eye(vtss_state_t *vtss_state, u32 sd_tgt, const vtss_debug_printf_t pr)
{
    u32 vref = 0, indx, cnt = 0, val;
    u32 eye_res[140][10] = {0};
    char buf[100];
    u32 vref_cnt = 0;

    REG_RD(VTSS_SD25G_TARGET_LANE_DA(sd_tgt), &vref);
    while (TRUE) {
        while (cnt <= 500) {
            REG_RD(VTSS_SD25G_TARGET_LANE_DD(sd_tgt), &val);
            if (VTSS_X_SD25G_TARGET_LANE_DD_LN_ISCAN_DONE(val)) {
                break;
            }
            VTSS_MSLEEP(1);
            cnt++;
        }
        if (VTSS_X_SD25G_TARGET_LANE_DD_LN_ISCAN_DONE(val) == 0) {
            VTSS_E("Timed out after %d ms - bailing out",cnt);
            break;;
        }
        indx = 0;
        REG_RD(VTSS_SD25G_TARGET_LANE_D0(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D1(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D2(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D3(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D4(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D5(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D6(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D7(sd_tgt), &eye_res[vref_cnt][indx++]);
        REG_RD(VTSS_SD25G_TARGET_LANE_D8(sd_tgt), &eye_res[vref_cnt][indx++]);

        REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_18(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ADD_VOLT);
        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_18(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ADD_VOLT);
        REG_RD(VTSS_SD25G_TARGET_LANE_DA(sd_tgt), &vref);

        if (vref_cnt == 127) {
            break;
        }
        vref_cnt++;
    }

    if (pr != NULL) {
        for (int i = vref_cnt; i >= 0; i--) {
            if ((i % 4 == 0) || i == 127) {
                (void)buf_set(buf, eye_res[i]);
                pr("%-5d %s\n", i, buf);
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_serdes_25g_eye_dimension(vtss_state_t *vtss_state, u32 sd_tgt, u32 *height, vtss_port_no_t port_no)
{
    u32 val, cnt = 0;

    while (cnt <= 500) {
        REG_RD(VTSS_SD25G_TARGET_LANE_DD(sd_tgt), &val);
        if (VTSS_X_SD25G_TARGET_LANE_DD_LN_ISCAN_DONE(val)) {
            break;
        }
        VTSS_NSLEEP(1000); // 1 us
        cnt++;
    }
    if (VTSS_X_SD25G_TARGET_LANE_DD_LN_ISCAN_DONE(val) == 0) {
        *height = 0;
        VTSS_E("Timed out after %d ms - bailing out",cnt);
        return VTSS_RC_ERROR;
    }

    REG_RD(VTSS_SD25G_TARGET_LANE_C3(sd_tgt), &val);

    if (VTSS_X_SD25G_TARGET_LANE_C3_LN_FAST_EYE_SCAN_FAIL(val) > 0) {
        *height = 0;
        return VTSS_RC_OK;
    }
    REG_RD(VTSS_SD25G_TARGET_LANE_D0(sd_tgt), &val);
    *height = val;

    return VTSS_RC_OK;
}

static u32 two_complement(u32 val, u32 mask)
{
    val = val & mask;
    val = ~val & mask;
    if (val == mask) {
        val = 1;
    } else {
        val++;
    }
    return val;
}

static vtss_rc fa_serdes_25g_eye_setup(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       u32 action,
                                       vtss_port_no_t port_no,
                                       u32 *ret_val,
                                       BOOL ignore_error)
{

    u32 sd_type, indx, sd_tgt, val, dfe_pd, dfedmx_pd;
    u32 rstn_dfedig, height = 0;
//    u32 dlev_6_0, h1_4_0, h2_4_0, h3_3_0, h4_3_0, h5_3_0;
    vtss_rc rc = VTSS_RC_OK;

    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &sd_type));
    sd_tgt = VTSS_TO_SD25G_LANE(indx);

#if 0
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_0E(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG);

    REG_RD(VTSS_SD25G_TARGET_LANE_CA(sd_tgt), &h1_4_0);
    REG_RD(VTSS_SD25G_TARGET_LANE_CB(sd_tgt), &h2_4_0);
    REG_RD(VTSS_SD25G_TARGET_LANE_CC(sd_tgt), &h3_3_0);
    REG_RD(VTSS_SD25G_TARGET_LANE_CD(sd_tgt), &h4_3_0);
    REG_RD(VTSS_SD25G_TARGET_LANE_CE(sd_tgt), &h5_3_0);
    REG_RD(VTSS_SD25G_TARGET_LANE_CF(sd_tgt), &dlev_6_0);


    REG_WR(VTSS_SD25G_TARGET_LANE_10(sd_tgt), dlev_6_0);
    REG_WR(VTSS_SD25G_TARGET_LANE_14(sd_tgt), h1_4_0);

    if (h2_4_0 & 0x10) { // If bit 5
        val = two_complement(h2_4_0, 0xF) | 0x10;
    } else {
        val = h2_4_0;
    }
    REG_WRM(VTSS_SD25G_TARGET_LANE_13(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_13_LN_CFG_DFE_BYP_H2_4_0(val),
            VTSS_M_SD25G_TARGET_LANE_13_LN_CFG_DFE_BYP_H2_4_0);

    if (h3_3_0 & 0x8) { // If bit 4
        val = two_complement(h3_3_0, 0x7) | 0x8;
    } else {
        val = h3_3_0;
    }
    REG_WRM(VTSS_SD25G_TARGET_LANE_12(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_12_LN_CFG_DFE_BYP_H3_3_0(val),
            VTSS_M_SD25G_TARGET_LANE_12_LN_CFG_DFE_BYP_H3_3_0);

    if (h4_3_0 & 0x8) { // If bit 4
        val = two_complement(h4_3_0, 0x7) | 0x8;
    } else {
        val = h4_3_0;
    }
    REG_WRM(VTSS_SD25G_TARGET_LANE_11(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H4_3_0(val),
            VTSS_M_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H4_3_0);

    if (h5_3_0 & 0x8) { // If bit 4
        val = two_complement(h5_3_0, 0x7) | 0x8;
    } else {
        val = h5_3_0;
    }
    REG_WRM(VTSS_SD25G_TARGET_LANE_11(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H5_3_0(val),
            VTSS_M_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H5_3_0);
#endif


    REG_WRM_CLR(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);
    REG_RD(VTSS_SD25G_TARGET_LANE_1C(sd_tgt), &val);
    dfe_pd = VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD(val);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD);
    REG_WRM_SET(VTSS_SD25G_TARGET_LANE_19(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_ISCAN_SEL);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_18(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_ERRAMP_PD);

    if (action == 3 || action == 4) {
        REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_18(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_18_LN_CFG_MAN_VOLT_EN);
    }

    REG_RD(VTSS_SD25G_TARGET_LANE_1C(sd_tgt), &val);
    dfedmx_pd = VTSS_X_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD(val);

#if 0
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD);

#endif
    REG_RD(VTSS_SD25G_TARGET_LANE_2E(sd_tgt), &val);
    rstn_dfedig = VTSS_X_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG(val);

    if (action == 3 || action == 4) {
        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_2E(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG);

        if (action == 3) {
            REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_28(sd_tgt),
                        VTSS_F_SD25G_TARGET_LANE_28_LN_CFG_FIGMERIT_SEL(0)); // Report eye height
        } else {
            REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_28(sd_tgt),
                        VTSS_F_SD25G_TARGET_LANE_28_LN_CFG_FIGMERIT_SEL(1)); // Report eye area
        }
    } else {
        REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_2E(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG);
    }

    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
            VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xff),
            VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);
    REG_WRM_SET(VTSS_SD25G_TARGET_CMU_1A(sd_tgt),
                VTSS_M_SD25G_TARGET_CMU_1A_R_REG_MANUAL);
    REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
            VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0),
            VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    if (action == 2 || action == 3) { // 2 = Draw eye, 3 = Eye height
        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_28(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_28_LN_CFG_ISCAN_MODE_EN);
    }

    if (action == 2) {
        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_0E(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_ISCAN_EN);
    }
    if (action == 3 || action == 4) {
        REG_WRM_SET(VTSS_SD25G_TARGET_LANE_2E(sd_tgt),
                    VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_EN_FAST_ISCAN);
    }

    if (action == 2) {
        VTSS_RC(fa_serdes_25g_normal_eye(vtss_state, sd_tgt, pr));
    } else {
        rc = fa_serdes_25g_eye_dimension(vtss_state, sd_tgt, &height, port_no);
        if (ret_val != NULL) {
            *ret_val = height;
        }
        if (pr != NULL) {
            if (rc == VTSS_RC_ERROR) {
                if (!ignore_error) {
                    VTSS_E("Eye scan fails to complete");
                }
            } else {
                pr("Eye height = %d\n", height);
            }
        }
    }

    // Disable eye scan
    REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD(dfe_pd) |
            VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD(dfedmx_pd),
            VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFEDMX_PD |
            VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_DFE_PD);
    REG_WRM(VTSS_SD25G_TARGET_LANE_2E(sd_tgt),
            VTSS_F_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG(rstn_dfedig),
            VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_RSTN_DFEDIG);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_28(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_28_LN_CFG_ISCAN_MODE_EN);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_19(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_19_LN_CFG_ISCAN_SEL);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_0E(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_ISCAN_EN);
    REG_WRM_CLR(VTSS_SD25G_TARGET_LANE_2E(sd_tgt),
                VTSS_M_SD25G_TARGET_LANE_2E_LN_CFG_EN_FAST_ISCAN);
    /* REG_WRM_SET(VTSS_SD25G_TARGET_LANE_0E(sd_tgt), */
    /*             VTSS_M_SD25G_TARGET_LANE_0E_LN_CFG_EN_DFEDIG); */

    return VTSS_RC_OK;
}


#define FA_DEBUG_LANE(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_SD10G_LANE_TARGET_LANE_##addr, i,\
(sd_type == FA_SERDES_TYPE_10G) ? "VTSS_SD10G_LANE_TARGET_LANE_"name : "VTSS_SD6G_LANE_TARGET_LANE_"name)
#define FA_DEBUG_25G_LANE(pr, addr, i, name) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_SD25G_TARGET_CMU_##addr, i, "VTSS_SD25G_TARGET_CMU_"name)

static vtss_rc fa_serdes_dump(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              vtss_port_no_t port_no)
{

    u32  sd_type, indx, sd_tgt;

    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &sd_type));
    sd_tgt = fa_get_lane_target(sd_type, indx);

    if (sd_type == FA_SERDES_TYPE_25G) {
        FA_DEBUG_25G_LANE(pr, FF(sd_tgt), indx, "FF");
        FA_DEBUG_25G_LANE(pr, 31(sd_tgt), indx, "31");
        FA_DEBUG_25G_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_25G_LANE(pr, 40(sd_tgt), indx, "40");
        FA_DEBUG_25G_LANE(pr, 46(sd_tgt), indx, "46");
        FA_DEBUG_25G_LANE(pr, 45(sd_tgt), indx, "45");
        FA_DEBUG_25G_LANE(pr, 0B(sd_tgt), indx, "0B");
        FA_DEBUG_25G_LANE(pr, 19(sd_tgt), indx, "19");
        FA_DEBUG_25G_LANE(pr, 18(sd_tgt), indx, "18");
        FA_DEBUG_25G_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_25G_LANE(pr, 30(sd_tgt), indx, "30");
        FA_DEBUG_25G_LANE(pr, 0C(sd_tgt), indx, "0C");
        FA_DEBUG_25G_LANE(pr, 0D(sd_tgt), indx, "0D");
        FA_DEBUG_25G_LANE(pr, 0E(sd_tgt), indx, "0E");
        FA_DEBUG_25G_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_25G_LANE(pr, 18(sd_tgt), indx, "18");
        FA_DEBUG_25G_LANE(pr, 2C(sd_tgt), indx, "2C");
        FA_DEBUG_25G_LANE(pr, 28(sd_tgt), indx, "28");
        FA_DEBUG_25G_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_25G_LANE(pr, 0F(sd_tgt), indx, "0F");
        FA_DEBUG_25G_LANE(pr, 1D(sd_tgt), indx, "1D");
        FA_DEBUG_25G_LANE(pr, 19(sd_tgt), indx, "19");
        FA_DEBUG_25G_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_25G_LANE(pr, 03(sd_tgt), indx, "03");
        FA_DEBUG_25G_LANE(pr, 06(sd_tgt), indx, "06");
        FA_DEBUG_25G_LANE(pr, 07(sd_tgt), indx, "07");
        FA_DEBUG_25G_LANE(pr, 43(sd_tgt), indx, "43");
        FA_DEBUG_25G_LANE(pr, 43(sd_tgt), indx, "42");
        FA_DEBUG_25G_LANE(pr, 05(sd_tgt), indx, "05");
        FA_DEBUG_25G_LANE(pr, 0A(sd_tgt), indx, "0A");
        FA_DEBUG_25G_LANE(pr, 09(sd_tgt), indx, "09");
        FA_DEBUG_25G_LANE(pr, 1B(sd_tgt), indx, "09");
        FA_DEBUG_25G_LANE(pr, 2E(sd_tgt), indx, "2E");
        FA_DEBUG_25G_LANE(pr, 44(sd_tgt), indx, "44");
        FA_DEBUG_25G_LANE(pr, 22(sd_tgt), indx, "22");
        FA_DEBUG_25G_LANE(pr, 1C(sd_tgt), indx, "1C");
        FA_DEBUG_25G_LANE(pr, 1E(sd_tgt), indx, "1E");
        FA_DEBUG_25G_LANE(pr, 25(sd_tgt), indx, "25");
        FA_DEBUG_25G_LANE(pr, 26(sd_tgt), indx, "26");
        FA_DEBUG_25G_LANE(pr, 18(sd_tgt), indx, "18");
        FA_DEBUG_25G_LANE(pr, 40(sd_tgt), indx, "40");
        FA_DEBUG_25G_LANE(pr, 04(sd_tgt), indx, "04");
        FA_DEBUG_25G_LANE(pr, 1E(sd_tgt), indx, "1E");
        FA_DEBUG_25G_LANE(pr, 2E(sd_tgt), indx, "2E");
        FA_DEBUG_25G_LANE(pr, 1C(sd_tgt), indx, "1C");
        FA_DEBUG_25G_LANE(pr, C0(sd_tgt), indx, "C0");

    } else {

        FA_DEBUG_LANE(pr, 93(sd_tgt), indx, "93");
        FA_DEBUG_LANE(pr, 94(sd_tgt), indx, "94");
        FA_DEBUG_LANE(pr, 9E(sd_tgt), indx, "9E");
        FA_DEBUG_LANE(pr, A1(sd_tgt), indx, "A1");
        FA_DEBUG_LANE(pr, 50(sd_tgt), indx, "50");
        FA_DEBUG_LANE(pr, 35(sd_tgt), indx, "35");
        FA_DEBUG_LANE(pr, 01(sd_tgt), indx, "01");
        FA_DEBUG_LANE(pr, 30(sd_tgt), indx, "30");
        FA_DEBUG_LANE(pr, A2(sd_tgt), indx, "A2");
        FA_DEBUG_LANE(pr, 13(sd_tgt), indx, "13");
        FA_DEBUG_LANE(pr, 23(sd_tgt), indx, "23");
        FA_DEBUG_LANE(pr, 22(sd_tgt), indx, "22");
        FA_DEBUG_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_LANE(pr, 02(sd_tgt), indx, "02");
        FA_DEBUG_LANE(pr, 03(sd_tgt), indx, "03");
        FA_DEBUG_LANE(pr, 04(sd_tgt), indx, "04");
        FA_DEBUG_LANE(pr, 2F(sd_tgt), indx, "2F");
        FA_DEBUG_LANE(pr, 0B(sd_tgt), indx, "0B");
        FA_DEBUG_LANE(pr, 0D(sd_tgt), indx, "0D");
        FA_DEBUG_LANE(pr, 0E(sd_tgt), indx, "0E");
        FA_DEBUG_LANE(pr, 23(sd_tgt), indx, "23");
        FA_DEBUG_LANE(pr, 06(sd_tgt), indx, "06");
        FA_DEBUG_LANE(pr, 33(sd_tgt), indx, "33");
        FA_DEBUG_LANE(pr, 52(sd_tgt), indx, "52");
        FA_DEBUG_LANE(pr, 37(sd_tgt), indx, "37");
        FA_DEBUG_LANE(pr, 3C(sd_tgt), indx, "3C");
        FA_DEBUG_LANE(pr, 39(sd_tgt), indx, "39");
        FA_DEBUG_LANE(pr, 1A(sd_tgt), indx, "1A");
        FA_DEBUG_LANE(pr, 16(sd_tgt), indx, "16");
        FA_DEBUG_LANE(pr, 15(sd_tgt), indx, "15");
        FA_DEBUG_LANE(pr, 26(sd_tgt), indx, "26");
        FA_DEBUG_LANE(pr, 42(sd_tgt), indx, "42");
        FA_DEBUG_LANE(pr, 0F(sd_tgt), indx, "0F");
        FA_DEBUG_LANE(pr, 24(sd_tgt), indx, "24");
        FA_DEBUG_LANE(pr, 14(sd_tgt), indx, "14");
        FA_DEBUG_LANE(pr, 3A(sd_tgt), indx, "3A");
        FA_DEBUG_LANE(pr, 31(sd_tgt), indx, "31");
        FA_DEBUG_LANE(pr, 48(sd_tgt), indx, "48");
        FA_DEBUG_LANE(pr, 36(sd_tgt), indx, "36");
        FA_DEBUG_LANE(pr, 32(sd_tgt), indx, "32");
        FA_DEBUG_LANE(pr, 37(sd_tgt), indx, "37");
        FA_DEBUG_LANE(pr, 41(sd_tgt), indx, "41");
        FA_DEBUG_LANE(pr, 9E(sd_tgt), indx, "9E");
        FA_DEBUG_LANE(pr, 0C(sd_tgt), indx, "0C");
        FA_DEBUG_LANE(pr, 0B(sd_tgt), indx, "0B");
        FA_DEBUG_LANE(pr, 83(sd_tgt), indx, "83");
        FA_DEBUG_LANE(pr, 06(sd_tgt), indx, "06");
        FA_DEBUG_LANE(pr, 9E(sd_tgt), indx, "9E");
        FA_DEBUG_LANE(pr, 83(sd_tgt), indx, "83");
        FA_DEBUG_LANE(pr, 50(sd_tgt), indx, "50");
        FA_DEBUG_LANE(pr, 34(sd_tgt), indx, "34");
    }
    return VTSS_RC_OK;
}

vtss_rc fa_debug_serdes_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                            const vtss_port_serdes_debug_t *const conf)

{
    u32  sd_type, indx, sd_tgt, sd_lane_tgt = 0, dfe_rstn;
    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &sd_type));
    sd_tgt = fa_get_lane_target(sd_type, indx);
    if (sd_type == FA_SERDES_TYPE_6G) {
        sd_lane_tgt = VTSS_TO_SD_LANE(indx);
    } else if (sd_type == FA_SERDES_TYPE_10G) {
        sd_lane_tgt = VTSS_TO_SD_LANE(indx+VTSS_SERDES_10G_START);
    } else {
        sd_lane_tgt = VTSS_TO_SD_LANE(indx+VTSS_SERDES_25G_START);
    }

    if (conf->debug_type == VTSS_SERDES_DFE_PRM) {

        if (sd_type == FA_SERDES_TYPE_6G || sd_type == FA_SERDES_TYPE_10G) {
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1D(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_1D_CFG_DFE_BYP_H1_4_0(conf->serdes_prm[0]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1D_CFG_DFE_BYP_H1_4_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1E(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_1E_CFG_DFE_BYP_H2_4_0(conf->serdes_prm[1]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1E_CFG_DFE_BYP_H2_4_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1F(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0(conf->serdes_prm[2]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1F(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H4_3_0(conf->serdes_prm[3]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_20(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_20_CFG_DFE_BYP_H5_3_0(conf->serdes_prm[4]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_20_CFG_DFE_BYP_H5_3_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1C(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_1C_CFG_DFEDIG_BYP_5_0(0x3E),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1C_CFG_DFEDIG_BYP_5_0);
            REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_83(sd_tgt),
                        VTSS_M_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN);
        } else {
            REG_WRM(VTSS_SD25G_TARGET_LANE_14(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_14_LN_CFG_DFE_BYP_H1_4_0(conf->serdes_prm[0]),
                    VTSS_M_SD25G_TARGET_LANE_14_LN_CFG_DFE_BYP_H1_4_0);
            REG_WRM(VTSS_SD25G_TARGET_LANE_13(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_13_LN_CFG_DFE_BYP_H2_4_0(conf->serdes_prm[1]),
                    VTSS_M_SD25G_TARGET_LANE_13_LN_CFG_DFE_BYP_H2_4_0);
            REG_WRM(VTSS_SD25G_TARGET_LANE_12(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_12_LN_CFG_DFE_BYP_H3_3_0(conf->serdes_prm[2]),
                    VTSS_M_SD25G_TARGET_LANE_12_LN_CFG_DFE_BYP_H3_3_0);
            REG_WRM(VTSS_SD25G_TARGET_LANE_11(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H4_3_0(conf->serdes_prm[3]) |
                    VTSS_F_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H5_3_0(conf->serdes_prm[4]),
                    VTSS_M_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H5_3_0 |
                    VTSS_M_SD25G_TARGET_LANE_11_LN_CFG_DFE_BYP_H4_3_0);
            REG_WRM(VTSS_SD25G_TARGET_LANE_10(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_10_LN_CFG_DFE_DLEV_6_0(conf->serdes_prm[5]),
                    VTSS_M_SD25G_TARGET_LANE_10_LN_CFG_DFE_DLEV_6_0);
            REG_WRM(VTSS_SD25G_TARGET_LANE_15(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_15_LN_CFG_DFEDIG_BYP_7_0(0x3E),
                    VTSS_M_SD25G_TARGET_LANE_15_LN_CFG_DFEDIG_BYP_7_0);
            REG_WRM_SET(VTSS_SD25G_TARGET_LANE_40(sd_tgt),
                        VTSS_M_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN);
            REG_WRM_SET(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_LANE_RST);
            VTSS_MSLEEP(1);
            REG_WRM_CLR(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                        VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_LANE_RST);
        }
    } else if (conf->debug_type == VTSS_SERDES_CTLE_PRM) {
        if (sd_type == FA_SERDES_TYPE_10G) {
            REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_0D(sd_tgt),
                        VTSS_M_SD10G_LANE_TARGET_LANE_0D_CFG_EQR_BYP);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0(conf->serdes_prm[0]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CTRL_3_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_2F(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CP_2_0(conf->serdes_prm[1]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2F_CFG_VGA_CP_2_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0E(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0(conf->serdes_prm[2]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_0E_CFG_EQC_FORCE_3_0);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_0B(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0(conf->serdes_prm[3]),
                    VTSS_M_SD10G_LANE_TARGET_LANE_0B_CFG_EQ_RES_3_0);
            REG_RD(VTSS_SD10G_LANE_TARGET_LANE_83(sd_tgt), &dfe_rstn);
            dfe_rstn = (VTSS_X_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN(dfe_rstn));
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_83(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN(1),
                    VTSS_M_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN);
            REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_83(sd_tgt),
                    VTSS_F_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN(dfe_rstn),
                    VTSS_M_SD10G_LANE_TARGET_LANE_83_R_DFE_RSTN);
        } else {
            REG_WRM_CLR(VTSS_SD25G_TARGET_CMU_FF(sd_tgt),
                        VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);
            REG_WRM_SET(VTSS_SD25G_TARGET_LANE_23(sd_tgt),
                        VTSS_M_SD25G_TARGET_LANE_23_LN_CFG_VGA_BYP);
            REG_WRM_SET(VTSS_SD25G_TARGET_LANE_1F(sd_tgt),
                        VTSS_M_SD25G_TARGET_LANE_1F_LN_CFG_EQR_BYP);
            REG_WRM(VTSS_SD25G_TARGET_LANE_22(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0(conf->serdes_prm[0]),
                    VTSS_M_SD25G_TARGET_LANE_22_LN_CFG_EQR_FORCE_3_0);
            REG_WRM(VTSS_SD25G_TARGET_LANE_1C(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0(conf->serdes_prm[1]),
                    VTSS_M_SD25G_TARGET_LANE_1C_LN_CFG_EQC_FORCE_3_0);
            REG_WRM(VTSS_SD25G_TARGET_LANE_21(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0(conf->serdes_prm[2]),
                    VTSS_M_SD25G_TARGET_LANE_21_LN_CFG_VGA_CTRL_BYP_4_0);
            REG_RD(VTSS_SD25G_TARGET_LANE_40(sd_tgt), &dfe_rstn);
            dfe_rstn = VTSS_X_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN(dfe_rstn);
            REG_WRM(VTSS_SD25G_TARGET_LANE_40(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN(1),
                    VTSS_M_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN);
            REG_WRM(VTSS_SD25G_TARGET_LANE_40(sd_tgt),
                    VTSS_F_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN(dfe_rstn),
                    VTSS_M_SD25G_TARGET_LANE_40_LN_R_DFE_RSTN);

//            VTSS_RC(fa_serdes_oscal_set(vtss_state, sd_tgt, port_no));
        }
    } else if (conf->debug_type == VTSS_SERDES_TXEQ_PRM) {
        VTSS_RC(fa_port_kr_tap_set(vtss_state, port_no, conf->serdes_prm[0], conf->serdes_prm[1], conf->serdes_prm[2])); // TxEQ set
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_serdes_10g_eye_setup(vtss_state_t *vtss_state,
                                       const vtss_debug_printf_t pr,
                                       u32 action,
                                       vtss_port_no_t port_no,
                                       u32 *ret_val,
                                       BOOL ignore_error)
{
    u32 sd_type, indx, sd_tgt;
    u32 lane_1a, lane_23;
    u32 dlev_6_0, h1_4_0, h2_4_0, h3_3_0, h4_3_0, h5_3_0, val;
    vtss_rc rc = VTSS_RC_OK;

    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &indx, &sd_type));
    sd_tgt = fa_get_lane_target(sd_type, indx);

    REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt),
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_EN_DFEDIG);
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_CA(sd_tgt), &dlev_6_0);
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C5(sd_tgt), &h1_4_0);
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C6(sd_tgt), &h2_4_0);
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C7(sd_tgt), &h3_3_0);
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C8(sd_tgt), &h4_3_0);
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_C9(sd_tgt), &h5_3_0);
    REG_WR(VTSS_SD10G_LANE_TARGET_LANE_21(sd_tgt), dlev_6_0);
    REG_WR(VTSS_SD10G_LANE_TARGET_LANE_1D(sd_tgt), h1_4_0);

    if (h2_4_0 & 0x10) { // If bit 5
        val = two_complement(h2_4_0, 0xF) | 0x10;
    } else {
        val = h2_4_0;
    }
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1E(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_1E_CFG_DFE_BYP_H2_4_0(val),
            VTSS_M_SD10G_LANE_TARGET_LANE_1E_CFG_DFE_BYP_H2_4_0);

    if (h3_3_0 & 0x8) { // If bit 4
        val = two_complement(h3_3_0, 0x7) | 0x8;
    } else {
        val = h3_3_0;
    }
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1F(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0(val),
            VTSS_M_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H3_3_0);

    if (h4_3_0 & 0x8) { // If bit 4
        val = two_complement(h4_3_0, 0x7) | 0x8;
    } else {
        val = h4_3_0;
    }
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1F(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H4_3_0(val),
            VTSS_M_SD10G_LANE_TARGET_LANE_1F_CFG_DFE_BYP_H4_3_0);

    if (h5_3_0 & 0x8) { // If bit 4
        val = two_complement(h5_3_0, 0x7) | 0x8;
    } else {
        val = h5_3_0;
    }
    REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_20(sd_tgt),
            VTSS_F_SD10G_LANE_TARGET_LANE_20_CFG_DFE_BYP_H5_3_0(val),
            VTSS_M_SD10G_LANE_TARGET_LANE_20_CFG_DFE_BYP_H5_3_0);

    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt), &lane_23);
    REG_RD(VTSS_SD10G_LANE_TARGET_LANE_1A(sd_tgt), &lane_1a);
    if (action == 2 || action == 10 ) {
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_93(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_93_R_REG_MANUAL);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_94(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_94_R_ISCAN_REG);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_9E(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_9E_R_RXEQ_REG);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_FOM_SEL);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_1B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1B_CFG_VCM_SEL);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL);
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN);
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_1A(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_DFE_EN);
    } else {

        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_49(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_49_CFG_FIGMERIT_SEL);
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_FOM_SEL);
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_MAN_VOLT_EN);
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2D(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2D_CFG_MAN_VOLT_SEL_6_0);
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2C(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2C_CFG_OS_MAN_EN);
        REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2E(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2E_CFG_OS_5_0);
        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_1B(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_1B_CFG_VCM_SEL(3),
                VTSS_M_SD10G_LANE_TARGET_LANE_1B_CFG_VCM_SEL);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL);
        REG_WRM(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt),
                VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD(0) |
                VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN(1) |
                VTSS_F_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD(0),
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFE_PD |
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_DFECK_EN |
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_ERRAMP_PD);
        REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_1A(sd_tgt),
                    VTSS_M_SD10G_LANE_TARGET_LANE_1A_CFG_PI_DFE_EN);

    }
    VTSS_NSLEEP(1000); // 1 us
    REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
               VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN);

    u32 height = 0;
    if (action == 2) {
        VTSS_RC(fa_serdes_10g_normal_eye(vtss_state, sd_tgt, pr));
    } else if (action == 10) {
        VTSS_RC(fa_serdes_10g_kr_eye(vtss_state, sd_tgt, pr, &height));
        if (ret_val != NULL) {
            *ret_val = height;
        }
        if (pr != NULL) {
            pr("Eye height = %d\n", height);
        }

    } else {
        rc = fa_serdes_10g_eye_dimension(vtss_state, sd_tgt, &height, port_no);
        if (ret_val != NULL) {
            *ret_val = height;
        }
        if (pr != NULL) {
            if (rc == VTSS_RC_ERROR) {
                if (!ignore_error) {
                    VTSS_E("Eye scan fails to complete");
                }
            } else {
                pr("Eye height = %d\n", height);
            }
        }
    }

    REG_WR(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt), lane_23);
    REG_WR(VTSS_SD10G_LANE_TARGET_LANE_1A(sd_tgt), lane_1a);
    REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_SEL);
    REG_WRM_CLR(VTSS_SD10G_LANE_TARGET_LANE_2B(sd_tgt),
                VTSS_M_SD10G_LANE_TARGET_LANE_2B_CFG_ISCAN_EN);

    REG_WRM_SET(VTSS_SD10G_LANE_TARGET_LANE_23(sd_tgt),
                VTSS_M_SD10G_LANE_TARGET_LANE_23_CFG_EN_DFEDIG);


    if (ignore_error) {
        return VTSS_RC_OK;
    }
   return rc;
}

vtss_rc fa_debug_chip_serdes(vtss_state_t *vtss_state,
                             const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info,
                             vtss_port_no_t port_no)
{
    u32  indx = 0, sd_type = 0, ret_val;
    char buf[100]  = {0}, buf1[100] = {0}, buf2[100] = {0}, buf3[20]  = {0};
    u32  sd_indx = vtss_fa_sd_lane_indx(vtss_state, port_no);
    u32  port = VTSS_CHIP_PORT(port_no);

    (void)vtss_fa_port2sd(vtss_state, port_no, &indx, &sd_type);
    if (sd_type == FA_SERDES_TYPE_10G) {
        VTSS_SPRINTF(buf3,"(10G_SD_%d)",indx);
    } else if (sd_type == FA_SERDES_TYPE_25G) {
        VTSS_SPRINTF(buf3,"(25G_SD_%d)",indx);
    } else {
        VTSS_SPRINTF(buf3,"(5G_SD_%d)",indx);
    }
    if (vtss_fa_port_is_high_speed(vtss_state, port)) {
        if (sd_type == FA_SERDES_TYPE_10G) {
            VTSS_SPRINTF(buf2,"%-6s : %s",vtss_serdes_if_txt(vtss_state->port.sd28_mode[sd_indx]),
                    vtss_serdes_preset_txt(serdes2preset(vtss_state->port.conf[port_no].serdes.media_type)));
        } else if (sd_type == FA_SERDES_TYPE_25G) {
            VTSS_SPRINTF(buf2,"%-6s : %s",vtss_serdes_if_txt(vtss_state->port.sd28_mode[sd_indx]),
                    vtss_serdes25g_preset_txt(serdes2preset_25g(vtss_state->port.conf[port_no].serdes.media_type, vtss_state->port.conf[port_no].speed)));
        } else {
            VTSS_SPRINTF(buf2,"%-6s : %s",vtss_serdes_if_txt(vtss_state->port.sd28_mode[sd_indx]),
                    vtss_serdes_preset_txt(serdes2preset(vtss_state->port.serdes_mode[port_no])));
        }
    } else {
        VTSS_SPRINTF(buf2,"%-6s : %s",vtss_serdes_if_txt(vtss_state->port.sd28_mode[sd_indx]),
                vtss_serdes_preset_txt(serdes2preset(vtss_state->port.conf[port_no].serdes.media_type)));
    }
    if (vtss_fa_port_is_high_speed(vtss_state, port)) {
        VTSS_SPRINTF(buf, "Chip port %-2u (API %-2u) Dev%s_%d", port, port_no, VTSS_PORT_IS_25G(port) ? "25G" :  VTSS_PORT_IS_10G(port)\
                ? "10G": VTSS_PORT_IS_5G(port) ? "5G" : "2G5", VTSS_PORT_DEV_INDX(port));
    } else {
        VTSS_SPRINTF(buf, "Chip port %-2u (API %-2u) Dev%s_%d", port, port_no, "2G5", port);
    }
    VTSS_SPRINTF(buf1,"SD%-2d %s", sd_indx, buf3);
    if (info->action == 1) {
        vtss_fa_debug_reg_header(pr, buf);
    } else {
        if (info->action < 3) {
            pr("%-31s -> %-16s %s\n",buf, buf1, buf2);
        }
    }

    if (info->action == 1) {
        VTSS_RC(fa_serdes_dump(vtss_state, pr, port_no));
    } else if (info->action >= 2 && info->action <= 4)  {
        if (sd_type == FA_SERDES_TYPE_10G || sd_type == FA_SERDES_TYPE_6G) {
            VTSS_RC(fa_serdes_10g_eye_setup(vtss_state, pr, info->action, port_no, &ret_val, 0));
        } else {
            VTSS_RC(fa_serdes_25g_eye_setup(vtss_state, pr, info->action, port_no, &ret_val, 0));
        }
    } else if (info->action == 5) {
        // Read DFE settings
        VTSS_RC(fa_serdes_dfe_read(vtss_state, pr, port_no));
    } else if (info->action == 6) {
        VTSS_RC(fa_serdes_ctle_read(vtss_state, pr, port_no));
    } else if (info->action == 7) {
        VTSS_RC(fa_serdes_oscal_ena(vtss_state, pr, port_no));
    } else if (info->action == 8) {
        VTSS_RC(fa_serdes_dfe_set(vtss_state, pr, port_no, FALSE));// DFE Disable
    } else if (info->action == 9) {
        VTSS_RC(fa_serdes_dfe_set(vtss_state, pr, port_no, TRUE)); // DFE Enable
    } else if (info->action == 10) {
        u16 tap_dly=0, tap_adv=0, ampl=0;
        VTSS_RC(fa_port_kr_tap_get(vtss_state, port_no, &tap_dly, &tap_adv, &ampl)); // TxEQ read
        pr("Tap_dly   (CP):%d\n",tap_dly);
        pr("Tap_adv   (CM):%d\n",tap_adv);
        pr("Amplitude:(C0):%d\n",ampl);
    } else if (info->action == 11) {
        VTSS_RC(fa_port_kr_square_wave(vtss_state, pr, port_no, TRUE));
    } else if (info->action == 12) {
        VTSS_RC(fa_port_kr_square_wave(vtss_state, pr, port_no, FALSE));
    } else if (info->action == 13) {
        VTSS_RC(fa_serdes_vga_adjust(vtss_state, pr, port_no));
    } else if (info->action == 14) {
        VTSS_RC(fa_serdes_eqr_adjust(vtss_state, pr, port_no));
    } else if (info->action == 15) {
        VTSS_RC(fa_serdes_eqc_adjust(vtss_state, pr, port_no));
    } else if (info->action == 16) {
        VTSS_RC(fa_serdes_ctle_adjust(vtss_state, pr, port_no, FALSE, NULL, NULL, NULL));
    } else if (info->action >= 20 && info->action <= 26) {
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
        vtss_port_kr_coef_type_t coef = VTSS_COEF_INIT;
        vtss_port_kr_coef_update_t action = 0;

        switch (info->action) {
        case 20:
            pr("Request: INIT\n");
            coef = VTSS_COEF_INIT;
            action = 0;
            break;
        case 21:
            pr("Request: CM DECR\n");
            coef = VTSS_COEF_CM1;
            action = VTSS_COEF_DECR;
            break;
        case 22:
            pr("Request: CM INCR\n");
            coef = VTSS_COEF_CM1;
            action = VTSS_COEF_INCR;
            break;
        case 23:
            pr("Request: CP DECR\n");
            coef = VTSS_COEF_CP1;
            action = VTSS_COEF_DECR;
            break;
        case 24:
            pr("Request: CP INCR\n");
            coef = VTSS_COEF_CP1;
            action = VTSS_COEF_INCR;
            break;
        case 25:
            pr("Request: C0 DECR\n");
            coef = VTSS_COEF_C0;
            action = VTSS_COEF_DECR;
            break;
        case 26:
            coef = VTSS_COEF_C0;
            action = VTSS_COEF_INCR;
            break;
        }
        fa_serdes_tx_eq_tune(vtss_state, pr, port_no, coef, action);
#endif /* VTSS_FEATURE_PORT_KR_IRQ */
    }


    return VTSS_RC_OK;
}

vtss_rc fa_kr_eye_height(vtss_state_t *vtss_state,
                         vtss_port_no_t port_no,
                         u32 action,
                         u32 *ret_val)
{
    vtss_rc rc = VTSS_RC_OK;

    if (VTSS_PORT_IS_10G(VTSS_CHIP_PORT(port_no))) {
        rc = fa_serdes_10g_eye_setup(vtss_state, NULL, action, port_no, ret_val, 1);
    } else {
        rc = fa_serdes_25g_eye_setup(vtss_state, NULL, action, port_no, ret_val, 1);
    }

    return rc;
}

/*  In:  API port
    Out: Index (sd_indx) of the Serdes:
      0-12 for 6G ports
      0-11 for 10G ports
      0-7  for 25G ports
    Out: Type (sd_type) of the Serdes:
      FA_SERDES_TYPE_6G
      FA_SERDES_TYPE_10G
      FA_SERDES_TYPE_25G

    To get target of SD_LANE which is numbered 0-32:
    target = VTSS_TO_SD_LANE(sd_indx + VTSS_SERDES_xxG_START)

    On other targets indx can be used directly:
    E.g. target = VTSS_TO_SD25G_LANE(sd_indx)
 */
vtss_rc vtss_fa_port2sd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *sd_indx, u32 *sd_type)
{
    u32 p = VTSS_CHIP_PORT(port_no);

    switch (vtss_state->port.conf[port_no].if_type) {
    case VTSS_PORT_INTERFACE_QSGMII:
        if (p <= 47) {
            u32 Q = (p -  p % 4) / 4;
            *sd_indx = Q;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_N("(Q QUAD 1G SD) QSGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
        }
        break;
    case VTSS_PORT_INTERFACE_USGMII:
        if (p <= 47) {
            u32 X = (p - p % 8) / 8;
            *sd_indx = X + 4;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_N("(X OCTAL 1G SD) USGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
        }
        break;
    case VTSS_PORT_INTERFACE_QXGMII: /* QXGMII:    4x2G5 devices. Mode 'R'. */
        if (p <= 63) {
            int R = (p < 16) ? p : (p < 32) ? p - 16 : (p < 48) ? p - 32 : p - 48;
            if (R < 8) {
                *sd_indx = R + 4;
                *sd_type = FA_SERDES_TYPE_10G;
                VTSS_N("(R QUAD 2G5 SD) 10USXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
            } else {
                *sd_indx = R - 8;
                *sd_type = FA_SERDES_TYPE_25G;
                VTSS_N("(R QUAD 2G5 SD) 10USXGMII p:%d SD25G_LANE index: %d",p, *sd_indx);
            }
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_10G: /* DXGMII_10G: 2x5G devices. Mode 'U'.*/
        if (p <= 63 && (p <= 15 || p >= 48)) {
            int U = (p < 16) ? p : p - 48;
            if (U < 8) {
                *sd_indx = U + 4;
                *sd_type = FA_SERDES_TYPE_10G;
                VTSS_N("(U DUAL 5G SD) 10USXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
            } else {
                *sd_indx = U - 8;
                *sd_type = FA_SERDES_TYPE_25G;
                VTSS_N("(U DUAL 5G SD) 10USXGMII p:%d SD25G_LANE index: %d",p, *sd_indx);
            }
        }
        break;
    case VTSS_PORT_INTERFACE_DXGMII_5G: /* DXGMII_5G: 2x2G5 devices. Mode 'F'.*/
        if (p <= 63) {
            int F = (p < 32) ? p :  p - 32;
            if (F < 12) {
                *sd_indx = F + 1;
                *sd_type = FA_SERDES_TYPE_6G;
                VTSS_N("(F DUAL 2G5 SD) 5USXGMII p:%d SD6G_LANE index: %d",p, *sd_indx);
            } else if (F < 24) {
                *sd_indx = F - 12;
                *sd_type = FA_SERDES_TYPE_10G;
                VTSS_N("(F DUAL 2G5 SD) 5USXGMII p:%d SD10G_LANE index: %d",p, *sd_indx);
            } else {
                *sd_indx = F - 24;
                *sd_type = FA_SERDES_TYPE_25G;
                VTSS_N("(F DUAL 2G5 SD) 5USXGMII p:%d SD25G_LANE index: %d",p, *sd_indx);
            }
        }
        break;
    default:
        if (p < 12) {
            *sd_indx = p + 1;
            *sd_type = FA_SERDES_TYPE_6G;
            VTSS_N("Single Serdes p:%d SD6G_LANE index: %d",p, *sd_indx);
            return VTSS_TO_SD6G_LANE(p + 1);
        } else if (p >= 12 && p < 16) {
            *sd_indx = p - 12;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_N("Single Serdes p:%d SD10_LANE index: %d",p, *sd_indx);
        } else if (p >= 48 && p < 56) {
            *sd_indx = p - 44;
            *sd_type = FA_SERDES_TYPE_10G;
            VTSS_N("Single Serdes p:%d SD10_LANE index: %d",p, *sd_indx);
        } else if (p >= 56 && p < 64) {
            *sd_indx = p - 56;
            *sd_type = FA_SERDES_TYPE_25G;
            VTSS_N("Single Serdes p:%d SD25_LANE index: %d",p, *sd_indx);
        } else if (p == 64) {
            *sd_indx = 0;
            *sd_type = FA_SERDES_TYPE_6G;
            VTSS_N("Single Serdes p:%d SD6G_LANE index: %d",p, *sd_indx);
        } else {
            VTSS_E("illegal port/interface mode");
            return VTSS_RC_ERROR;
        }
    }
    return VTSS_RC_OK;
}

/* Returns index 0-12 for 6G ports  */
/* Returns index 0-11 for 10G ports */
/* Returns index 0-7  for 25G ports  */
u32 vtss_fa_port2sd_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 sd_indx = 0, sd_type;
    (void)vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type);
    return sd_indx;
}

/* Returns serdes LANE index 0-33 */
u32 vtss_fa_sd_lane_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u32 indx = 0, type;
    (void)vtss_fa_port2sd(vtss_state, port_no, &indx, &type);
    if (type == FA_SERDES_TYPE_6G) {
        return indx;
    } else if (type == FA_SERDES_TYPE_10G) {
        return indx + VTSS_SERDES_10G_START;
    } else {
        return(indx + VTSS_SERDES_25G_START);
    }
}


static vtss_rc fa_sd25g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode)
{
    vtss_sd25g28_setup_args_t sd_cfg = {0};
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
    vtss_port_kr_conf_t *kr = &vtss_state->port.kr_conf[port_no];

    if (kr->train.enable && (speed == VTSS_SPEED_25G) && vtss_state->port.kr_store[port_no].compl_ack) {
        mode = VTSS_SERDES_MODE_SFI_KR;
    }
#endif
    sd_cfg.chip_name = VTSS_SD25G28_CHIP_ANT;
    sd_cfg.txinvert = vtss_state->port.conf[port_no].serdes.tx_invert;
    sd_cfg.rxinvert = !vtss_state->port.conf[port_no].serdes.rx_invert; /* inverted in substrate */
    sd_cfg.txswing = 240;
    sd_cfg.reg_ctrl = 1;
    sd_cfg.preset = serdes2preset_25g(vtss_state->port.conf[port_no].serdes.media_type, speed);
    if (vtss_state->port.serdes_mode[port_no] == VTSS_SERDES_MODE_DISABLE) {
        sd_cfg.reg_rst = 1; // Must start with RST
    }
     /* Apply the serdes mode */
    switch (mode) {
        case VTSS_SERDES_MODE_IDLE:
        case VTSS_SERDES_MODE_SFI_DAC:
        case VTSS_SERDES_MODE_SFI_SR:
        case VTSS_SERDES_MODE_SFI_ZR:
        case VTSS_SERDES_MODE_SFI_BP:
        case VTSS_SERDES_MODE_SFI_B2B:
        case VTSS_SERDES_MODE_SFI_PR_NONE:
        case VTSS_SERDES_MODE_SFI: {
            if (speed == VTSS_SPEED_25G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_25G_LAN;
            } else if (speed == VTSS_SPEED_10G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_10G_LAN;
            } else if (speed == VTSS_SPEED_5G) {
                sd_cfg.mode = VTSS_SD25G28_MODE_5G_LAN;
            } else {
                VTSS_E("Illegal speed");
            }
            break;
        }
        case VTSS_SERDES_MODE_SFI_KR:
            sd_cfg.mode = VTSS_SD25G28_MODE_25G_KR; // KR 64bit mode for now
            break;
        case VTSS_SERDES_MODE_DXGMII_10G: { // 2x5G, mode 'U'
            sd_cfg.mode = VTSS_SD25G28_MODE_10G_DSXGMII;
            break;
        }
        case VTSS_SERDES_MODE_USGMII: { // 8x1G, mode 'X'
            sd_cfg.mode = VTSS_SD10G28_MODE_10G_USGMII;
            break;
        }
        case VTSS_SERDES_MODE_QXGMII: { // 4x2G5, mode 'R'
            sd_cfg.mode = VTSS_SD25G28_MODE_10G_QSXGMII;
            break;
        }
        case VTSS_SERDES_MODE_DXGMII_5G: { // 2x2G5, mode 'F'
            sd_cfg.mode = VTSS_SD25G28_MODE_5G_USXGMII;
            break;
        }
        case VTSS_SERDES_MODE_2G5: {
            sd_cfg.mode = VTSS_SD25G28_MODE_SGMII2G5;
            break;
        }
        case VTSS_SERDES_MODE_SGMII:
        case VTSS_SERDES_MODE_1000BaseX: {
            sd_cfg.mode = VTSS_SD25G28_MODE_SGMII;
            break;
        }
        default: {
            VTSS_E("Serdes mode (%d) not supported",mode);
            return VTSS_RC_ERROR;
        }
    }

    if (vtss_ant_sd25g28_setup_lane(vtss_state, sd_cfg, port_no) != VTSS_RC_OK) {
        VTSS_E("Could not configure Serdes mode (%d) at port:%d",mode,port_no);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_sd10g_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no,  vtss_serdes_mode_t mode, u32 sd_type)
{
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;
    vtss_sd10g28_setup_args_t sd_cfg = {0};

    sd_cfg.chip_name = VTSS_SD10G28_CHIP_ANT;
    sd_cfg.is_6g =  sd_type == FA_SERDES_TYPE_6G ? TRUE : FALSE;
    sd_cfg.txinvert = vtss_state->port.conf[port_no].serdes.tx_invert;
    sd_cfg.rxinvert = !vtss_state->port.conf[port_no].serdes.rx_invert; /* inverted in substrate */
    sd_cfg.txswing = 240;
    sd_cfg.preset = VTSS_SD10G28_PRESET_NONE;

    /* Apply the serdes mode */
    switch (mode) {
        case VTSS_SERDES_MODE_IDLE:
        case VTSS_SERDES_MODE_SFI_DAC:
        case VTSS_SERDES_MODE_SFI_SR:
        case VTSS_SERDES_MODE_SFI_ZR:
        case VTSS_SERDES_MODE_SFI_BP:
        case VTSS_SERDES_MODE_SFI_B2B:
        case VTSS_SERDES_MODE_SFI_PR_NONE:
        case VTSS_SERDES_MODE_SFI_KR:
        case VTSS_SERDES_MODE_SFI: {
            sd_cfg.preset = serdes2preset(vtss_state->port.conf[port_no].serdes.media_type);
            if (speed == VTSS_SPEED_10G) {
                sd_cfg.mode = VTSS_SD10G28_MODE_10G_LAN;
                 } else if (speed == VTSS_SPEED_5G) {
                sd_cfg.mode = VTSS_SD10G28_MODE_5G_LAN;
            } else {
                VTSS_E("Illegal speed");
            }
            break;
        }
        case VTSS_SERDES_MODE_2G5: {
            sd_cfg.mode = VTSS_SD10G28_MODE_SGMII2G5;
            break;
        }
        case VTSS_SERDES_MODE_SGMII:
        case VTSS_SERDES_MODE_1000BaseX: {
            sd_cfg.mode = VTSS_SD10G28_MODE_SGMII;
            break;
        }
        case VTSS_SERDES_MODE_DXGMII_10G: { // 2x5G, mode 'U'
            sd_cfg.mode = VTSS_SD10G28_MODE_10G_DSXGMII;
            break;
        }
       case VTSS_SERDES_MODE_USGMII: { // 8x1G, mode 'X'
            sd_cfg.mode = VTSS_SD10G28_MODE_10G_USGMII;
            break;
        }
        case VTSS_SERDES_MODE_QXGMII: { // 4x2G5, mode 'R'
            sd_cfg.mode = VTSS_SD10G28_MODE_10G_QSXGMII;
            break;
        }
        case VTSS_SERDES_MODE_DXGMII_5G: { // 2x2G5, mode 'F'
            sd_cfg.mode = VTSS_SD10G28_MODE_5G_USXGMII;
            break;
        }
        case VTSS_SERDES_MODE_QSGMII: {
            sd_cfg.mode = VTSS_SD10G28_MODE_QSGMII;
            break;
        }
        case VTSS_SERDES_MODE_100FX: {
            sd_cfg.preset = VTSS_SD10G28_FX100;
            sd_cfg.mode = VTSS_SD10G28_MODE_FX100;
            break;
        }
        default: {
            VTSS_E("Serdes mode (%d) not supported",mode);
            return VTSS_RC_ERROR;
        }
    }
    if (vtss_ant_sd10g28_setup_lane(vtss_state, sd_cfg, port_no) != VTSS_RC_OK) {
        VTSS_E("Could not configure Serdes mode (%d) at port:%d",mode,port_no);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}
// Apply board specific TX equalizer settings
static vtss_rc vtss_fa_sd_board_settings(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 sd_indx, u32 sd_type)
{
    vtss_rc rc = VTSS_RC_OK;
    vtss_port_speed_t speed = vtss_state->port.conf[port_no].speed;
    u32 value;
    u16 tap_dly, tap_adv, ampl;

    if (vtss_state->init_conf.serdes_tap_get == NULL) {
        return VTSS_RC_OK; // Not available
    }

    rc = fa_port_kr_tap_get(vtss_state, port_no, &tap_dly, &tap_adv, &ampl);

    if (vtss_state->init_conf.serdes_tap_get(NULL, port_no, speed, VTSS_SERDES_POST_CURSOR, &value) == VTSS_RC_OK) {
        tap_dly = value;
    }

    if (vtss_state->init_conf.serdes_tap_get(NULL, port_no, speed, VTSS_SERDES_PRE_CURSOR, &value) == VTSS_RC_OK) {
        tap_adv = value;
    }

    if (vtss_state->init_conf.serdes_tap_get(NULL, port_no, speed, VTSS_SERDES_MAIN_CURSOR, &value) == VTSS_RC_OK) {
        ampl = value;
    }

    rc |= fa_port_kr_tap_set(vtss_state,  port_no, tap_dly, tap_adv, ampl);

    return rc;
}

vtss_rc vtss_fa_sd_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no,  vtss_serdes_mode_t mode)
{
    u32 sd_indx, sd_type;

    /* Map API port to Serdes instance */
    VTSS_RC(vtss_fa_port2sd(vtss_state, port_no, &sd_indx, &sd_type));

    if (sd_type == FA_SERDES_TYPE_25G) {
        VTSS_RC(fa_sd25g_cfg(vtss_state, port_no,  mode));
    } else {
        VTSS_RC(fa_sd10g_cfg(vtss_state, port_no,  mode, sd_type));
    }

    /*  Apply board specific TX equalizer settings */
    VTSS_RC(vtss_fa_sd_board_settings(vtss_state, port_no, sd_indx, sd_type));

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_serdes_init(vtss_state_t *vtss_state)
{
    u32 sd25g_tgt, sd_lane_tgt, cmu_tgt, cmu_cfg_tgt;

    /* MESA-853: Disable reference clock termination on 25G Serdeses */
    for (u32 p = 0; p < 8; p++) {
        sd25g_tgt = VTSS_TO_SD25G_LANE(p);
        sd_lane_tgt = VTSS_TO_SD_LANE(VTSS_SERDES_25G_START + p);

        REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST(1),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST);

        REG_WRM(VTSS_SD25G_CFG_TARGET_SD_LANE_CFG(sd_lane_tgt),
                VTSS_F_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST(0),
                VTSS_M_SD25G_CFG_TARGET_SD_LANE_CFG_EXT_CFG_RST);

        REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0xFF),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

        REG_WRM(VTSS_SD25G_TARGET_CMU_31(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_31_CFG_COMMON_RESERVE_7_0(1),
                VTSS_M_SD25G_TARGET_CMU_31_CFG_COMMON_RESERVE_7_0);

        REG_WRM(VTSS_SD25G_TARGET_CMU_FF(sd25g_tgt),
                VTSS_F_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX(0),
                VTSS_M_SD25G_TARGET_CMU_FF_REGISTER_TABLE_INDEX);

    }

    /* MESA-901: Serdes's are default powered up, start with power all down */
    for (u32 s = 0; s <= 32; s++) {
        sd_lane_tgt = VTSS_TO_SD_LANE(s);
        /* Optimal power down settings from GUC */
        if (s < VTSS_SERDES_25G_START) {
            REG_WR(VTSS_SD_LANE_TARGET_QUIET_MODE_6G(sd_lane_tgt), 0x1EF4E0C);
        } else {
            REG_WR(VTSS_SD25G_CFG_TARGET_QUIET_MODE_6G(sd_lane_tgt), 0x1EF4E0C);
        }
    }

    /* MESA-901: CMUs are default powered up, start with power all down */
    for (u32 cmu = 0; cmu <= 13; cmu++) {
        cmu_tgt = VTSS_TO_SD_CMU(cmu);
        cmu_cfg_tgt = VTSS_TO_SD_CMU_CFG(cmu);

        REG_WRM(VTSS_SD_CMU_TERM_TARGET_SD_CMU_CFG(cmu_cfg_tgt),
                VTSS_F_SD_CMU_TERM_TARGET_SD_CMU_CFG_EXT_CFG_RST(0),
                VTSS_M_SD_CMU_TERM_TARGET_SD_CMU_CFG_EXT_CFG_RST);

        REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_05(cmu_tgt),
                VTSS_F_SD10G_CMU_TARGET_CMU_05_CFG_REFCK_TERM_EN(0),
                VTSS_M_SD10G_CMU_TARGET_CMU_05_CFG_REFCK_TERM_EN);

        REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_09(cmu_tgt),
                VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_DN(0),
                VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_DN);

        REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_06(cmu_tgt),
                VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_VCO_PD(1),
                VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_VCO_PD);

        REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_09(cmu_tgt),
                VTSS_F_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_UP(0),
                VTSS_M_SD10G_CMU_TARGET_CMU_09_CFG_EN_TX_CK_UP);

        REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_08(cmu_tgt),
                VTSS_F_SD10G_CMU_TARGET_CMU_08_CFG_CK_TREE_PD(1),
                VTSS_M_SD10G_CMU_TARGET_CMU_08_CFG_CK_TREE_PD);

        REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_0D(cmu_tgt),
                VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_REFCK_PD(1) |
                VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV64(1) |
                VTSS_F_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV66(1),
                VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_REFCK_PD |
                VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV64 |
                VTSS_M_SD10G_CMU_TARGET_CMU_0D_CFG_PD_DIV66);

        REG_WRM(VTSS_SD10G_CMU_TARGET_CMU_06(cmu_tgt),
                VTSS_F_SD10G_CMU_TARGET_CMU_06_CFG_CTRL_LOGIC_PD(1),
                VTSS_M_SD10G_CMU_TARGET_CMU_06_CFG_CTRL_LOGIC_PD);
    }

    return VTSS_RC_OK;
}

#endif /* VTSS_ARCH_FA */
