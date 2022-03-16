// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// Avoid "options.h not used in module vtss_phy_init_scripts.c"
/*lint --e{766} */

#include "vtss_phy_api.h"
#ifdef VTSS_CHIP_CU_PHY

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PHY

#include "vtss_phy_api.h"

#if defined(VTSS_OPT_PHY_TIMESTAMP)
#include "../ts/vtss_phy_ts.h"
#endif

#include "../common/vtss_phy_common.h"
#include "vtss_phy_init_scripts.h"


//#include "../../ail/vtss_state.h"
//#include "../../ail/vtss_common.h"
//#include "vtss_phy_init_scripts.h"

/************************************************************************/
/* Support functions                                               */
/************************************************************************/

// Conversion from vtss_phy_family_t to printable text.
//
// In : family : The family type
//
// Return :  Printable text
const char *vtss_phy_family2txt(vtss_phy_family_t family)
{
    switch (family) {
    case VTSS_PHY_FAMILY_NONE:
        return "None";
    case VTSS_PHY_FAMILY_MUSTANG:
        return "Mustang";
    case VTSS_PHY_FAMILY_BLAZER:
        return "Blazer";
    case VTSS_PHY_FAMILY_COBRA:
        return "Cobra";
    case VTSS_PHY_FAMILY_QUATTRO:
        return "Quattro";
    case VTSS_PHY_FAMILY_SPYDER:
        return "Spyder";
    case VTSS_PHY_FAMILY_COOPER:
        return "Cooper";
    case VTSS_PHY_FAMILY_LUTON:
        return "Luton";
    case VTSS_PHY_FAMILY_LUTON24:
        return "Luton24";
    case VTSS_PHY_FAMILY_LUTON_E:
        return "Luton E";
    case VTSS_PHY_FAMILY_INTRIGUE:
        return "Intrigue";
    case VTSS_PHY_FAMILY_ENZO:
        return "Enzo";
    case VTSS_PHY_FAMILY_ATOM:
        return "Atom";
    case VTSS_PHY_FAMILY_LUTON26:
        return "Luton26";
    case VTSS_PHY_FAMILY_TESLA:
        return "Tesla";
    case VTSS_PHY_FAMILY_VIPER:
        return "Viper";
    case VTSS_PHY_FAMILY_ELISE:
        return "Elise";
    case VTSS_PHY_FAMILY_NANO:
        return "Nano";

    }
    return "Unknown";
}


// Function for downloading code into the internal 8051 CPU.
// In : port_no - Any port within the chip where to download the 8051 code
//      code_array - Pointer to array containing the 8051 code
//      code_size  - The size of the code to be downloaded.
// Return : VTSS_RC_OK if download was done else error code.
static vtss_rc download_8051_code(vtss_state_t *vtss_state,
                                  vtss_port_no_t port_no, u8 const *code_array, u16 code_size)
{
    u16 i;

    if (vtss_state->sync_calling_private) {
        VTSS_I("Skipping download of 8051 code, we can't do register value check for this part (Checked by checking CRC later)");
        return VTSS_RC_OK;
    }

    VTSS_D("download_8051_code port:%d, code_size:%d ", port_no, code_size);

    // Note that the micro/GPIO-page, Reg31=0x10, is a global page, one per PHY chip
    // thus even though broadcast is turned off, it is still sufficient to do once`
    // Hold the micro in reset during patch download
    VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x7009));      //  Hold 8051 in SW Reset,Enable auto incr address and patch clock,Disable the 8051 clock

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5002));     // write to addr 4000= 02
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_11, 0x0000));     // write to address reg.

    for (i = 0; i < code_size; i++) {
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x5000 | code_array[i]));
    }

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0000));     // Clear internal memory access

    // Signaling the micropatch has been downloaded. Note: port_no MUST be the base port no at this point.
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no)); // Switch back to standard register-page
    return VTSS_RC_OK;
}

// Function that wait for the micro code to complete
// In : port_no : port number staring from 0.
vtss_rc vtss_phy_wait_for_micro_complete(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    //increased timeout from 500 to 1000 due to bugzilla#20356
    u16 timeout = 1000;
    u16 reg18g = 0;
    vtss_rc rc = VTSS_RC_OK;

    VTSS_N("vtss_state->system_reseting:%d", vtss_state->system_reseting);
    // Skipping MCB wait, because the system is rebooting (due to bugzilla#5731)
    if (vtss_state->system_reseting) {
        return VTSS_RC_OK;
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

    // Wait for micro to complete MCB command (bit 15)
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
    while (reg18g & 0x8000 && timeout > 0) {
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, &reg18g));
        timeout--; // Make sure that we don't run forever
        MEPA_MSLEEP(1);
        VTSS_D("MCB timer, port_no %u, timeout = %d", port_no , timeout);
    }

    if (timeout == 0) {
        VTSS_E("MCB timeout, port_no %u", port_no);
        rc = VTSS_RC_ERROR;
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    return rc;
}


//Function for checking that the 8051 code is loaded correctly.

//In : port_no : port number staring from 0.
//     code_length : The length of the downloaded 8051 code
//     expected_crc: The expected CRC for the downloaded 78051 code
vtss_rc vtss_phy_is_8051_crc_ok_private(
    vtss_state_t *vtss_state,
    vtss_port_no_t port_no, u16 start_addr, u16 code_length, u16 expected_crc, BOOL first_time)
{
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_VERIPHY_CTRL_REG2, start_addr));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_VERIPHY_CTRL_REG3, code_length));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Change to GPIO page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x8008)); // Start Mirco command

    //MISSING VTSS_RC() is not an omission, it is intended so we get a CRC error
    (void) vtss_phy_wait_for_micro_complete(vtss_state, port_no);

    // Get the CRC
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_VERIPHY_CTRL_REG2, &vtss_state->phy_state[port_no].micro_patch_crc));

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no)); // return to standard page


    if (vtss_state->phy_state[port_no].micro_patch_crc == expected_crc) {
        VTSS_I("CRC_OK: 8051 crc_calculated: 0x%X; expected_crc = 0x%X", vtss_state->phy_state[port_no].micro_patch_crc, expected_crc);
        return VTSS_RC_OK;
    } else {
        // The First Time this get called and the code has not been downloaded, It is not an error
        if (!first_time) {
            VTSS_E("Microcode crc_calculated = 0x%X, expected_crc = 0x%X - Note vtss_phy_pre_reset_private MUST be called with the first PHY port within the chip - current port_no:%d", vtss_state->phy_state[port_no].micro_patch_crc, expected_crc, port_no);
        }
        return VTSS_RC_ERROR;
    }
}

/************************************************************************/
/* Blazer family functions                                               */
/************************************************************************/

/* Init Scripts for VSC/CIS 8204 - aka Blazer */
vtss_rc vtss_phy_init_seq_blazer(vtss_state_t *vtss_state,
                                 vtss_phy_port_state_t *ps,
                                 vtss_port_no_t        port_no)
{
    if (ps->type.revision == 4) {
        /* VSC8204 B3 */
        VTSS_RC(vtss_phy_wr(vtss_state, port_no, 31, 0xf01d));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_MODE_CONTROL, 0x9040));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_STD_27, 0x0115));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_1, 0x8000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_1000BASE_T_CONTROL, 0x0300));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x0208));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_5, 0x8000));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0085));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x21f0));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8770));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0085));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x23f0));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8770));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x1b00));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8fa0));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x7d00));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8fac));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x00e0));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0xe30d));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x870c));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0010));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f84));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0012));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f84));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0040));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f86));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x0008));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(vtss_phy_page_0x2daf(vtss_state, port_no));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_1, 0x0000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_MODE_CONTROL, 0x1840));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_MODE_CONTROL, 0x1040));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_1000BASE_T_CONTROL, 0x0300));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, 0x8000));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0208));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x9782));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x9782));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x003c));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x3800));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f8a));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x003c));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x3800));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8f8a));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0008));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x1240));
    } else if (ps->type.revision == 5) {
        /* VSC8204 B4 */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL, 0x1100));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(vtss_phy_wr(vtss_state, port_no, 31, 0xF01D));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x8000));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0208));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0085));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x23F0));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8770));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0400));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8F88));
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_2, 0x0000));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_1, 0x0400));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_0, 0x8F88));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0008));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_1, 0x0000));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x1840));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x1040));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
        VTSS_RC(vtss_phy_page_0x2daf(vtss_state, port_no));
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    } else if (ps->type.revision == 6) {
        /* VSC8204 B5 */
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_STD_27, 0x0114)); /* LED configuration */
    }
    return VTSS_RC_OK;
}


/************************************************************************/
/* ATOM family functions                                               */
/************************************************************************/

static const u16 tr_base_reg_write_cmd = 0x8486;
static const u16 tr_last_reg_write_cmd = 0x84b4;
#ifdef VTSS_10BASE_TE
static const u8 tr_reg_bits_msb[] = {
    0x00,   0x65,   0x00,   0xeb,   0x00,   0x65,   0x59,   0x48,   //0x8486 - 0x8494
    0x00,   0xeb,   0x00,   0x55,   0x00,   0x00,   0x51,   0x30,   //0x8496 - 0x84a4
    0x10,   0x00,   0x00,   0x29,   0x79,   0x71,   0x61,   0x59    //0x84a6 - 0x84b4
};
static const u16 tr_reg_bits_lsw[] = {
    0xf410, 0xb719, 0x0914, 0xcefb, 0x0eb9, 0x6596, 0x2492, 0xa02a, //0x8486 - 0x8494
    0x0ab6, 0xcef9, 0x0caa, 0x5555, 0x0555, 0x0015, 0x240e, 0xa206, //0x8496 - 0x84a4
    0x2000, 0x0000, 0x0000, 0x2659, 0xf79d, 0xb699, 0x6596, 0x6596  //0x84a6 - 0x84b4
};
#else //System uses regular 10BASE-T to support Cat3 (and uglier) cables
static const u8 tr_reg_bits_msb[] = {
    0x20,   0x75,   0x00,   0xf7,   0x00,   0x49,   0x41,   0x40,   //0x8486 - 0x8494
    0x00,   0xf7,   0x00,   0x49,   0x00,   0x00,   0x38,   0x00,   //0x8496 - 0x84a4
    0x00,   0x00,   0x00,   0x29,   0x7d,   0x75,   0x41,   0x41    //0x84a6 - 0x84b4
};
static const u16 tr_reg_bits_lsw[] = {
    0xa497, 0xf71a, 0x0a14, 0xff7a, 0x0db2, 0x2410, 0x0410, 0xca39, //0x8486 - 0x8494
    0x0eff, 0xff7a, 0x0db2, 0x2492, 0x0410, 0x0010, 0xc244, 0x0000, //0x8496 - 0x84a4
    0x0000, 0x0000, 0x0000, 0x265d, 0xf7df, 0x9551, 0x0410, 0x0410  //0x84a6 - 0x84b4
};
#endif /* VTSS_10BASE_TE */


static vtss_rc vtss_phy_65nm_10BASE_init(
    vtss_state_t *vtss_state,
    const vtss_port_no_t port_no,
    const u8 invert_pulse)
{
    int i;
    u16 msb, lsw, tr_cmd;

    //Configure 10BASE-Te (EEE reduced transmit amplitude spec for 10Mb)
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
#ifdef VTSS_10BASE_TE
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_CU_PMD_TX_CTRL, 0x0007, 0x000f));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, 0x8000, 0x8000));
#else //System uses regular 10BASE-T to support Cat3 (and uglier) cables
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, 0x0000, 0x8000));
#endif /* VTSS_10BASE_TE */

    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));

    for ( tr_cmd = tr_base_reg_write_cmd, i = 0; tr_cmd <= tr_last_reg_write_cmd;
          tr_cmd += 2, ++i ) {
        msb = tr_reg_bits_msb[i];
        lsw = tr_reg_bits_lsw[i];
        if (invert_pulse) {
            if (tr_cmd == 0x848a) {
                lsw ^= 0x1040;
            } else {
                msb ^= 0x82;
                lsw ^= 0x0820;
            }
        }
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, msb));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, lsw));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, tr_cmd));
    }

    return VTSS_RC_OK;
}
// Atom  Rev. B. Internal 8051 patch.
// In     : port_no - any port within the chip where to load the 8051 code.
// Return : VTSS_RC_OK if configuration done else error code.

// Initializes micro patch for entire 12-port chip containing specified PHY
static vtss_rc luton26_atom12_revB_patch(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val = 0;
    u16 chip_port_no = 0;

    const u8 patch_arr[] = {
        0x43, 0xe9, 0x02, 0x40, 0x58, 0x02, 0x40, 0x4e, 0x02, 0x44,
        0x00, 0x02, 0x42, 0x2b, 0x02, 0x41, 0x82, 0x74, 0x05, 0xfb,
        0x02, 0x08, 0x21, 0x94, 0x14, 0xec, 0x64, 0x80, 0x94, 0x80,
        0x50, 0x12, 0xe5, 0x51, 0x24, 0x18, 0x12, 0x16, 0xea, 0x12,
        0x17, 0x54, 0xe4, 0xf0, 0xa3, 0x74, 0x24, 0x02, 0x0a, 0xf6,
        0xe9, 0x12, 0x17, 0xbd, 0xe5, 0x51, 0x24, 0x18, 0x12, 0x16,
        0xea, 0x12, 0x17, 0x54, 0xe4, 0x75, 0xf0, 0x10, 0x02, 0x0b,
        0x0b, 0x12, 0x43, 0x6d, 0x02, 0x09, 0xde, 0x12, 0x42, 0xcf,
        0xd0, 0x1d, 0xd0, 0x1d, 0x02, 0x39, 0xb1, 0xe4, 0xf5, 0x28,
        0xf5, 0x29, 0xe5, 0x1e, 0x54, 0x0f, 0x64, 0x09, 0x60, 0x03,
        0x02, 0x41, 0x77, 0xfb, 0xfa, 0x7d, 0xff, 0x7f, 0x92, 0x12,
        0x35, 0xdb, 0x53, 0x91, 0x7f, 0xa2, 0xaf, 0x92, 0x08, 0xc2,
        0xaf, 0x75, 0xff, 0x10, 0x75, 0xfd, 0x84, 0x75, 0xfe, 0xb7,
        0x75, 0xfc, 0x94, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0x12, 0x43,
        0xff, 0x75, 0xff, 0x11, 0xe4, 0xff, 0xf5, 0xfb, 0xe5, 0xfb,
        0xd3, 0x94, 0x0b, 0x50, 0x25, 0x75, 0xfc, 0xd0, 0xe5, 0xfc,
        0x30, 0xe0, 0xfb, 0xe5, 0xfd, 0x54, 0x3c, 0xfe, 0xbe, 0x2c,
        0x11, 0xae, 0x07, 0x0f, 0x74, 0x22, 0x2e, 0xf8, 0xa6, 0xfb,
        0xc3, 0xef, 0x64, 0x80, 0x94, 0x86, 0x50, 0x04, 0x05, 0xfb,
        0x80, 0xd4, 0xd3, 0xef, 0x64, 0x80, 0x94, 0x80, 0x50, 0x03,
        0x02, 0x41, 0x63, 0xe4, 0xf5, 0xfb, 0x75, 0xff, 0x10, 0x75,
        0xfd, 0x84, 0x75, 0xfe, 0xb7, 0x75, 0xfc, 0x94, 0xe5, 0xfc,
        0x30, 0xe0, 0xfb, 0x12, 0x43, 0xff, 0xe4, 0xfe, 0x74, 0x22,
        0x2e, 0xf8, 0xe6, 0xf5, 0xfb, 0x75, 0xff, 0x11, 0x75, 0xfc,
        0xd0, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0xe5, 0xfd, 0x54, 0x3c,
        0x64, 0x2c, 0x70, 0x4d, 0x75, 0xfe, 0x10, 0xf5, 0xfd, 0x75,
        0xfc, 0x90, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0x75, 0xff, 0x10,
        0x75, 0xfe, 0x8f, 0x75, 0xfd, 0x88, 0x75, 0xfc, 0x90, 0xe5,
        0xfc, 0x30, 0xe0, 0xfb, 0x12, 0x43, 0xff, 0x75, 0xff, 0x11,
        0xe4, 0xf5, 0xfe, 0xf5, 0xfd, 0x75, 0xfc, 0x90, 0xe5, 0xfc,
        0x30, 0xe0, 0xfb, 0x75, 0xff, 0x10, 0x75, 0xfe, 0x8f, 0x75,
        0xfd, 0x88, 0x75, 0xfc, 0x90, 0xe5, 0xfc, 0x30, 0xe0, 0xfb,
        0x12, 0x43, 0xff, 0x05, 0x29, 0xe5, 0x29, 0x70, 0x02, 0x05,
        0x28, 0x0e, 0xc3, 0xef, 0x64, 0x80, 0xf8, 0xee, 0x64, 0x80,
        0x98, 0x40, 0x8d, 0xab, 0x29, 0xaa, 0x28, 0x7d, 0x0a, 0x7f,
        0x04, 0x12, 0x3c, 0x26, 0x30, 0xcf, 0x05, 0xc2, 0xcf, 0x12,
        0x42, 0xcf, 0xe5, 0x91, 0x20, 0xe7, 0x03, 0x02, 0x40, 0x7a,
        0xa2, 0x08, 0x92, 0xaf, 0x7b, 0x01, 0x7a, 0x00, 0x7d, 0xee,
        0x7f, 0x92, 0x02, 0x35, 0xdb, 0xe5, 0x1e, 0x20, 0xe5, 0x03,
        0x02, 0x42, 0x2a, 0x90, 0x47, 0xd5, 0x30, 0xe4, 0x33, 0xe0,
        0x54, 0xc7, 0xf0, 0x44, 0x10, 0xf0, 0x90, 0x47, 0xd8, 0xe0,
        0x54, 0x1f, 0xf0, 0xf0, 0xa3, 0xe0, 0x54, 0xf8, 0xf0, 0xf0,
        0x90, 0x47, 0xd5, 0xe0, 0x54, 0x3f, 0xf0, 0x44, 0xc0, 0xf0,
        0xa3, 0xe0, 0x54, 0xfc, 0xf0, 0x44, 0x01, 0xf0, 0x90, 0x47,
        0xdc, 0xe0, 0x54, 0xc7, 0xf0, 0x44, 0x28, 0xf0, 0x80, 0x2e,
        0xe0, 0x54, 0xc7, 0xf0, 0x44, 0x08, 0xf0, 0x90, 0x47, 0xda,
        0xe0, 0x44, 0x04, 0xf0, 0x90, 0x47, 0xd8, 0xe0, 0x54, 0x1f,
        0xf0, 0x44, 0x40, 0xf0, 0xa3, 0xe0, 0x54, 0xf8, 0xf0, 0xf0,
        0x90, 0x47, 0xd4, 0xe0, 0x54, 0x1f, 0xf0, 0xf0, 0xa3, 0xe0,
        0x54, 0xf8, 0xf0, 0x44, 0x03, 0xf0, 0x90, 0x47, 0xd6, 0xe0,
        0x44, 0x40, 0xf0, 0x90, 0x47, 0xe0, 0xe0, 0x54, 0xf8, 0xf0,
        0x44, 0x05, 0xf0, 0x54, 0x1f, 0xf0, 0x44, 0x40, 0xf0, 0xa3,
        0xe0, 0x54, 0xf8, 0xf0, 0x44, 0x06, 0xf0, 0x90, 0x47, 0xde,
        0xe0, 0x54, 0x1f, 0xf0, 0xf0, 0x54, 0xe3, 0xf0, 0xf0, 0x90,
        0x47, 0xdd, 0xe0, 0x54, 0x7f, 0xf0, 0xf0, 0xa3, 0xe0, 0x54,
        0xfc, 0xf0, 0xf0, 0x22, 0x90, 0x47, 0xd0, 0xe0, 0x54, 0xef,
        0xf0, 0x44, 0x80, 0xf0, 0x90, 0x47, 0xd8, 0xe0, 0x54, 0x7f,
        0xf0, 0x44, 0x80, 0xf0, 0xa3, 0xe0, 0x54, 0xfc, 0xf0, 0xf0,
        0x90, 0x47, 0xd7, 0xe0, 0x54, 0x7f, 0xf0, 0x90, 0x47, 0xda,
        0xe0, 0x54, 0xc7, 0xf0, 0x44, 0x10, 0xf0, 0x90, 0x47, 0xd6,
        0xe0, 0x54, 0xe7, 0xf0, 0x44, 0x18, 0xf0, 0x90, 0x47, 0xd5,
        0xe0, 0x54, 0x8f, 0xf0, 0x44, 0x20, 0xf0, 0x90, 0x47, 0xd4,
        0xe0, 0x54, 0x3f, 0xf0, 0xf0, 0xa3, 0xe0, 0x54, 0xfc, 0xf0,
        0x44, 0x01, 0xf0, 0x90, 0x47, 0xd8, 0xe0, 0x44, 0x04, 0xf0,
        0x90, 0x47, 0xd7, 0xe0, 0x54, 0xc7, 0xf0, 0x44, 0x18, 0xf0,
        0x7c, 0x00, 0xe5, 0x1e, 0x54, 0x0f, 0xfd, 0x64, 0x01, 0x70,
        0x19, 0xe5, 0x1e, 0x30, 0xe4, 0x14, 0xa3, 0xe0, 0x44, 0x02,
        0xf0, 0x90, 0x47, 0xda, 0xe0, 0x54, 0xc7, 0xf0, 0x44, 0x18,
        0xf0, 0x54, 0xf8, 0xf0, 0xf0, 0x22, 0xed, 0x64, 0x01, 0x4c,
        0x70, 0x12, 0x90, 0x47, 0xd5, 0xe0, 0x54, 0x7f, 0xf0, 0x44,
        0x80, 0xf0, 0xa3, 0xe0, 0x54, 0xf8, 0xf0, 0x44, 0x07, 0xf0,
        0x90, 0x47, 0xd8, 0xe0, 0x54, 0xfd, 0xf0, 0x22, 0xe4, 0xf5,
        0xfb, 0x7d, 0x1c, 0xe4, 0xff, 0x12, 0x3b, 0xe6, 0xad, 0x07,
        0xac, 0x06, 0xec, 0x54, 0xc0, 0xff, 0xed, 0x54, 0x3f, 0x4f,
        0xf5, 0x20, 0x30, 0x06, 0x2c, 0x30, 0x01, 0x08, 0xa2, 0x04,
        0x72, 0x03, 0x92, 0x07, 0x80, 0x21, 0x30, 0x04, 0x06, 0x7b,
        0xcc, 0x7d, 0x11, 0x80, 0x0d, 0x30, 0x03, 0x06, 0x7b, 0xcc,
        0x7d, 0x10, 0x80, 0x04, 0x7b, 0x66, 0x7d, 0x16, 0xe4, 0xff,
        0x12, 0x3b, 0x25, 0xee, 0x4f, 0x24, 0xff, 0x92, 0x07, 0xaf,
        0xfb, 0x74, 0xaf, 0x2f, 0xf8, 0xe6, 0xff, 0xa6, 0x20, 0x20,
        0x07, 0x39, 0x8f, 0x20, 0x30, 0x07, 0x34, 0x30, 0x00, 0x31,
        0x20, 0x04, 0x2e, 0x20, 0x03, 0x2b, 0xe4, 0xf5, 0xff, 0x75,
        0xfc, 0xc2, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0xaf, 0xfe, 0xef,
        0x20, 0xe3, 0x1a, 0xae, 0xfd, 0x44, 0x08, 0xf5, 0xfe, 0x75,
        0xfc, 0x80, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0x8f, 0xfe, 0x8e,
        0xfd, 0x75, 0xfc, 0x80, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0x05,
        0xfb, 0xaf, 0xfb, 0xef, 0xc3, 0x94, 0x0c, 0x50, 0x03, 0x02,
        0x42, 0xd2, 0xe4, 0xf5, 0xfb, 0x22, 0xe4, 0xf5, 0x4b, 0x75,
        0x4c, 0x01, 0xf5, 0x4d, 0x7f, 0x40, 0x7e, 0x02, 0x12, 0x3b,
        0x4e, 0xe4, 0xf5, 0x2a, 0xe5, 0x2a, 0x25, 0xe0, 0x24, 0xc9,
        0xf5, 0x82, 0xe4, 0x34, 0x43, 0xf5, 0x83, 0xe4, 0x93, 0xfe,
        0x74, 0x01, 0x93, 0xf5, 0x4b, 0xee, 0xff, 0x8f, 0x4c, 0xe5,
        0x4c, 0x30, 0xe7, 0x04, 0x7f, 0xff, 0x80, 0x02, 0x7f, 0x00,
        0x8f, 0x4d, 0xe5, 0x2a, 0x25, 0xe0, 0xff, 0xe4, 0x33, 0x44,
        0x02, 0xfe, 0x12, 0x3b, 0x4e, 0x05, 0x2a, 0xe5, 0x2a, 0xc3,
        0x94, 0x10, 0x40, 0xc4, 0xe4, 0xf5, 0x4b, 0xf5, 0x4c, 0xf5,
        0x4d, 0x7f, 0x40, 0x7e, 0x02, 0x02, 0x3b, 0x4e, 0x17, 0x55,
        0xfc, 0xaf, 0xeb, 0x8c, 0xd9, 0xec, 0x7f, 0xff, 0x45, 0x31,
        0xbb, 0x3e, 0x15, 0xee, 0xf8, 0x8a, 0xd9, 0x60, 0xf4, 0x6b,
        0xf5, 0xde, 0x01, 0xa4, 0xfb, 0xf4, 0xeb, 0xf4, 0xfc, 0x03,
        0xc2, 0xe9, 0xc2, 0x61, 0x75, 0xe9, 0xff, 0x75, 0xed, 0x0f,
        0x90, 0x47, 0xfe, 0xe0, 0x54, 0xf8, 0x44, 0x02, 0xf0, 0xd2,
        0x6c, 0x22, 0x22, 0x22
    };
    // Only download 8051 Patches to Port 0 of PHY!
    // Check to see if this is PHY Port 0, If it is not, the 8051 CRC Calculation will Fail on other PHY Ports */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    chip_port_no = (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11;
    VTSS_D("reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    if (chip_port_no != 0) {
        VTSS_E("ERROR: Attempting to download patch on Non-Base Port.  reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
        return VTSS_RC_ERR_PHY_PATCH_SETTING_NOT_SUPPORTED;
    }

    // Check to see if the code has already been downloaded correctly, if so, Just return, No need to do it again
    if (vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                        FIRMWARE_START_ADDR,
                                        sizeof(patch_arr) + 1 /* Add one for the byte auto-added in the download function */,
                                        0xB2AA, TRUE) == VTSS_RC_OK) {
        VTSS_I("Skipping download of 8051, CRC for Download correct");
        return VTSS_RC_OK;
    }

    VTSS_RC(download_8051_code(vtss_state, port_no, &patch_arr[0], sizeof(patch_arr)));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4018));     // Enable 8051 clock; clear patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc018));     // Release 8051 SW Reset

    // Check that code is downloaded correctly.
    VTSS_RC(vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                            FIRMWARE_START_ADDR,
                                            sizeof(patch_arr) + 1, // Add one for the byte auto-added in the download function
                                            0xB2AA, FALSE));

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Switch back to micro/GPIO register-page
    VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_3, 0x081c));     // ROM addr. to trap for patch0
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_4, 0x4012));     // PRAM jump addr. for patch0
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_5, 0x0ade));     // ROM addr. to trap for patch1
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_6, 0x4018));     // PRAM jump addr. for patch1
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_7, 0x06df));     // ROM addr. to trap for patch2
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_8, 0x06fd));     // PRAM jump addr. to patch around invalid x-short preservation
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_9, 0x09db));     // ROM addr. to trap for patch3
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_10, 0x4048));     // PRAM jump addr. for patch3
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0f00));     // set bit 11:8 to enable patch0-3 trapping
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4098));     // Enable 8051 clock; indicate patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc098));     // Release 8051 SW Reset
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));// Switch back to main register-page
    return VTSS_RC_OK;
}

// Atom  Rev. C. Internal 8051 patch.
// In     : port_no - any port within the chip where to load the 8051 code.
// Return : VTSS_RC_OK if configuration done else error code.
//
// Previous Patch was:
// Download patch into PRAM for the internal 8051
// CRC: 0x1E5E
//
// Current Patch is:
// Download patch into PRAM for the internal 8051
// Sept. 15, 2015
// CRC: 0x8F96
// Bug 19146 - BugZero#73251/73098:Default 1G SerDes config incorrect for 100-FX Mode of operation
//             Update SigDet Threshold and SerDes sensitivity for 100FX mode of operation.
//
// Initializes micro patch for entire 12-port chip containing specified PHY
static vtss_rc luton26_atom12_revC_patch(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val = 0;
    u16 chip_port_no = 0;
    BOOL skip_dnload = FALSE;
    BOOL patch_ok = FALSE;

    const u8 patch_arr[] = {
        0x42, 0x81, 0x02, 0x42, 0x76, 0x02, 0x42, 0x8b, 0x02, 0x42,
        0x8e, 0x02, 0x40, 0x33, 0x02, 0x41, 0x7d, 0xef, 0x03, 0x03,
        0xf5, 0x62, 0x02, 0x1d, 0xf2, 0x12, 0x41, 0xe2, 0x02, 0x09,
        0xbb, 0xed, 0xff, 0xe5, 0xfc, 0x54, 0x38, 0x64, 0x20, 0x70,
        0x08, 0x65, 0xff, 0x70, 0x04, 0xed, 0x44, 0x80, 0xff, 0x22,
        0x90, 0x47, 0xd0, 0xe0, 0x54, 0xef, 0xf0, 0x44, 0x80, 0xf0,
        0x90, 0x47, 0xd8, 0xe0, 0x54, 0x7f, 0xf0, 0x44, 0x80, 0xf0,
        0xa3, 0xe0, 0x54, 0xfc, 0xf0, 0xf0, 0x90, 0x47, 0xd7, 0xe0,
        0x54, 0x7f, 0x12, 0x42, 0x6a, 0x90, 0x47, 0xd6, 0xe0, 0x54,
        0xe7, 0xf0, 0x44, 0x18, 0xf0, 0x90, 0x47, 0xd5, 0xe0, 0x54,
        0x8f, 0xf0, 0x44, 0x20, 0xf0, 0x90, 0x47, 0xd7, 0xe0, 0x54,
        0xc7, 0xf0, 0x44, 0x18, 0xf0, 0x7c, 0x00, 0xe5, 0x6f, 0x54,
        0x0f, 0xfd, 0x64, 0x01, 0x70, 0x2f, 0xe5, 0x6f, 0x30, 0xe4,
        0x2a, 0xa3, 0xe0, 0x44, 0x02, 0xf0, 0x54, 0xfb, 0xf0, 0x90,
        0x47, 0xdc, 0xe0, 0x44, 0x04, 0xf0, 0x90, 0x47, 0xda, 0xe0,
        0x54, 0xc7, 0xf0, 0x44, 0x18, 0xf0, 0xa3, 0xe0, 0x54, 0xf0,
        0xf0, 0x44, 0x0e, 0xf0, 0x90, 0x47, 0xda, 0xe0, 0x54, 0xf8,
        0xf0, 0xf0, 0x22, 0xed, 0x64, 0x01, 0x4c, 0x70, 0x0f, 0x90,
        0x47, 0xd5, 0xe0, 0x54, 0x7f, 0xf0, 0x44, 0x80, 0x12, 0x42,
        0x63, 0x44, 0x07, 0xf0, 0x90, 0x47, 0xd8, 0xe0, 0x54, 0xfd,
        0xf0, 0x44, 0x04, 0xf0, 0x90, 0x47, 0xdc, 0xe0, 0x54, 0xfb,
        0x12, 0x42, 0x6a, 0xa3, 0xe0, 0x54, 0xf0, 0xf0, 0x44, 0x06,
        0xf0, 0x22, 0xe4, 0xf5, 0xfb, 0x7d, 0x1c, 0xe4, 0xff, 0x12,
        0x3c, 0x2a, 0xad, 0x07, 0xac, 0x06, 0xec, 0x54, 0xc0, 0xff,
        0xed, 0x54, 0x3f, 0x4f, 0xf5, 0x20, 0x30, 0x06, 0x2c, 0x30,
        0x01, 0x08, 0xa2, 0x04, 0x72, 0x03, 0x92, 0x07, 0x80, 0x21,
        0x30, 0x04, 0x06, 0x7b, 0xcc, 0x7d, 0x11, 0x80, 0x0d, 0x30,
        0x03, 0x06, 0x7b, 0xcc, 0x7d, 0x10, 0x80, 0x04, 0x7b, 0x66,
        0x7d, 0x16, 0xe4, 0xff, 0x12, 0x3b, 0x49, 0xee, 0x4f, 0x24,
        0xff, 0x92, 0x07, 0xaf, 0xfb, 0x74, 0xb6, 0x2f, 0xf8, 0xe6,
        0xff, 0xa6, 0x20, 0x20, 0x07, 0x39, 0x8f, 0x20, 0x30, 0x07,
        0x34, 0x30, 0x00, 0x31, 0x20, 0x04, 0x2e, 0x20, 0x03, 0x2b,
        0xe4, 0xf5, 0xff, 0x75, 0xfc, 0xc2, 0xe5, 0xfc, 0x30, 0xe0,
        0xfb, 0xaf, 0xfe, 0xef, 0x20, 0xe3, 0x1a, 0xae, 0xfd, 0x44,
        0x08, 0xf5, 0xfe, 0x75, 0xfc, 0x80, 0xe5, 0xfc, 0x30, 0xe0,
        0xfb, 0x8f, 0xfe, 0x8e, 0xfd, 0x75, 0xfc, 0x80, 0xe5, 0xfc,
        0x30, 0xe0, 0xfb, 0x05, 0xfb, 0xaf, 0xfb, 0xef, 0xc3, 0x94,
        0x0c, 0x50, 0x03, 0x02, 0x40, 0xe2, 0xe4, 0xf5, 0xfb, 0x22,
        0xe5, 0x6f, 0x30, 0xe5, 0x5f, 0x90, 0x47, 0xd5, 0x30, 0xe4,
        0x2c, 0x12, 0x42, 0x6e, 0x90, 0x47, 0xd8, 0xe0, 0x54, 0x1f,
        0xf0, 0x12, 0x42, 0x63, 0xf0, 0x90, 0x47, 0xd5, 0xe0, 0x54,
        0x3f, 0xf0, 0x44, 0xc0, 0xf0, 0xa3, 0xe0, 0x54, 0xfc, 0xf0,
        0x44, 0x01, 0xf0, 0x90, 0x47, 0xdc, 0xe0, 0x54, 0xc7, 0xf0,
        0x44, 0x28, 0xf0, 0x80, 0x1d, 0xe0, 0x54, 0xc7, 0xf0, 0x44,
        0x08, 0xf0, 0x90, 0x47, 0xda, 0xe0, 0x44, 0x04, 0xf0, 0x90,
        0x47, 0xd8, 0xe0, 0x12, 0x42, 0x5e, 0xf0, 0x90, 0x47, 0xd6,
        0xe0, 0x44, 0x40, 0xf0, 0x90, 0x47, 0xe0, 0xe0, 0x54, 0xf8,
        0xf0, 0x44, 0x05, 0xf0, 0x12, 0x42, 0x5e, 0x44, 0x06, 0xf0,
        0x22, 0xe4, 0xf5, 0x4b, 0x75, 0x4c, 0x01, 0xf5, 0x4d, 0x7f,
        0x40, 0x7e, 0x02, 0x12, 0x3b, 0x72, 0xe4, 0xf5, 0x21, 0xe5,
        0x21, 0x25, 0xe0, 0x24, 0x3e, 0xf5, 0x82, 0xe4, 0x34, 0x42,
        0xf5, 0x83, 0xe4, 0x93, 0xfe, 0x74, 0x01, 0x93, 0xf5, 0x4b,
        0xee, 0xff, 0x8f, 0x4c, 0xe5, 0x4c, 0x30, 0xe7, 0x04, 0x7f,
        0xff, 0x80, 0x02, 0x7f, 0x00, 0x8f, 0x4d, 0xe5, 0x21, 0x25,
        0xe0, 0xff, 0xe4, 0x33, 0x44, 0x02, 0xfe, 0x12, 0x3b, 0x72,
        0x05, 0x21, 0xe5, 0x21, 0xc3, 0x94, 0x10, 0x40, 0xc4, 0xe4,
        0xf5, 0x4b, 0xf5, 0x4c, 0xf5, 0x4d, 0x7f, 0x40, 0x7e, 0x02,
        0x02, 0x3b, 0x72, 0x17, 0x55, 0xfc, 0xaf, 0xeb, 0x8c, 0xd9,
        0xec, 0x7f, 0xff, 0x45, 0x31, 0xbb, 0x3e, 0x15, 0xee, 0xf8,
        0x8a, 0xd9, 0x60, 0xf4, 0x6b, 0xf5, 0xde, 0x01, 0xa4, 0xfb,
        0xf4, 0xeb, 0xf4, 0xfc, 0x03, 0x54, 0x1f, 0xf0, 0x44, 0x40,
        0xf0, 0xa3, 0xe0, 0x54, 0xf8, 0xf0, 0x22, 0xf0, 0x90, 0x47,
        0xda, 0xe0, 0x54, 0xc7, 0xf0, 0x44, 0x10, 0xf0, 0x22, 0x7b,
        0x01, 0x7a, 0x00, 0x7d, 0xee, 0x7f, 0x92, 0x02, 0x36, 0x7f,
        0x90, 0x47, 0xfe, 0xe0, 0x54, 0xf8, 0x44, 0x02, 0xf0, 0x22,
        0x02, 0x40, 0xdf, 0x22
    };

    // Only download 8051 Patches to Port 0 of PHY!
    // Check to see if this is PHY Port 0, If it is not, the 8051 CRC Calculation will Fail on other PHY Ports */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    chip_port_no = (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11;
    VTSS_D("reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    if (chip_port_no != 0) {
        VTSS_E("ERROR: Attempting to download patch on Non-Base Port.  reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
        return VTSS_RC_ERR_PHY_PATCH_SETTING_NOT_SUPPORTED;
    }

    // Check to see if the code has already been downloaded correctly, if so, Just return, No need to do it again
    if (vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                        FIRMWARE_START_ADDR,
                                        sizeof(patch_arr) + 1 /* Add one for the byte auto-added in the download function */,
                                        0x8F96, TRUE) == VTSS_RC_OK) {
        VTSS_I("Skipping download of 8051, CRC for Download correct");

        // CRC is Correct, So at this point, we can skip the Micro Dnload
        skip_dnload = TRUE;
        patch_ok = TRUE;

        // CRC is Correct, Make sure that all the patches are still present
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_3, &reg_val));
        // Check: Trap ROM at _MicroSmiRead+0x1d to spoof patch-presence
        if (reg_val != 0x1def) {
            VTSS_I("CRC for Download correct: FAIL-Check::ROM addr. to trap for patch0; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Branch to starting address of SpoofPatchPresence
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_4, &reg_val));
        if (reg_val != 0x4012) {
            VTSS_I("CRC for Download correct: FAIL-Check::PRAM jump addr. for patch0; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Branch to starting address of SpoofPatchPresence
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_5, &reg_val));
        if (reg_val != 0x09b8) {
            VTSS_I("CRC for Download correct: FAIL-Check::ROM Addr to trap for Patch1; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Branch to starting address of SpoofPatchPresence
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_6, &reg_val));
        if (reg_val != 0x401a) {
            VTSS_I("CRC for Download correct: FAIL-Check::PRAM Jump Addr for Patch1; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Branch to starting address of SpoofPatchPresence
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_7, &reg_val));
        if (reg_val != 0x3c47) {
            VTSS_I("CRC for Download correct: FAIL-Check::Trap ROM at _MicroSmiRead+0x1d to spoof patch-presence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Branch to starting address of SpoofPatchPresence
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_8, &reg_val));
        if (reg_val != 0x4020) {
            VTSS_I("CRC for Download correct: FAIL-Check::Branch to starting address of SpoofPatchPresence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Enable patch fram trap described in register 3-4
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, &reg_val));
        if (reg_val != 0x0700) {
            VTSS_I("CRC for Download correct: FAIL-Check::set bits 8-10 to enable patch0-2 trapping; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Micro not in Reset, Enable 8051 clock enable; operate at 125 MHz
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, &reg_val));
        if ((reg_val & 0xf1ff) != 0x4018) {
            // mask off bits 11:9 and check that speed, etc., are set as expected; i.e., "normal" operating mode with 125 MHz clock
            VTSS_I("CRC for Download correct: FAIL-Check::Enable 8051 Clk Enable and Operating Speed set to 125MHz; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    }

    if (skip_dnload && patch_ok) {
        VTSS_I("Skipping download of 8051, CRC for Download correct; Micro-Patch Enabled and OK");
    } else {
        if (skip_dnload) {
            VTSS_D("Skipping download of 8051, CRC for Download correct; However, Micro-Patch Not Enabled");
        } else {
            VTSS_D("Downloading 8051 Patch, CRC for Download NOT correct;  Setting Micro-Patch to Not Enabled");
            VTSS_RC(download_8051_code(vtss_state, port_no, &patch_arr[0], sizeof(patch_arr)));
            patch_ok = FALSE;
        }

        if (!patch_ok) {
            VTSS_I("Micro-Patch Not Enabled - Enabling at this time");
            if (skip_dnload) {
                VTSS_I("Micro-Assert-Reset Performed, Download of 8051 Skipped, Enabling Micro-Patch \n");
                VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
            }
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4018));    // Enable 8051 clock; clear patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc018));    // Release 8051 SW Reset

            // Check that code is downloaded correctly.
            VTSS_RC(vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                                    FIRMWARE_START_ADDR,
                                                    sizeof(patch_arr) + 1, // Add one for the byte auto-added in the download function
                                                    0x8F96, FALSE));

//            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Switch back to micro/GPIO register-page
//            VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_3, 0x1def));    // ROM addr. to trap for patch0
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_4, 0x4012));    // PRAM jump addr. for patch0
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_5, 0x09b8));    // ROM addr. to trap for patch1
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_6, 0x401a));    // PRAM jump addr. for patch1
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_7, 0x3c47));    // Trap ROM at _MicroSmiRead+0x1d to spoof patch-presence
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_8, 0x4020));    // Branch to starting address of SpoofPatchPresence
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0700));    // set bits 8-10 to enable patch0-2 trapping
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4018));    // Enable 8051 clock; clear patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc018));    // Release 8051 SW Reset

            VTSS_I("Enable 8051 clk, Patch present Spoofed, Release SW Reset");

            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

        }
    }

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no)); // Switch back to standard register-page

    return VTSS_RC_OK;
}

// Initialization need for ATOM12 rev. C & D. (For whole chip and must be done before init. of the individual ports)
//
// In : phy - Any port with the chip.
//
// Return : VTSS_RC_OK if configuration done else error code.
// Date   : 30-10-2012
static vtss_rc luton26_atom12_revCD_init_script(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 revision)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x0040));
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_CU_PMD_TX_CTRL, 0x02be));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x4420));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0c00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_9, 0x18c8));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_5, 0x1320));

    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    if (revision == VTSS_PHY_ATOM_REV_D) {
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0027));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x303d));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9792));
    } else { //VTSS_PHY_ATOM_REV_C
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0032));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x303d));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9792));
    }
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf147));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0005));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2f54));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x01bd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fe));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0006));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0150));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x480a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0034));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f80));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x82e0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0005));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0208));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9186));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3700));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fb0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9fa1));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9688));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9fa0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0020));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x640b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9690));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2220));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8258));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2a20));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3060));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3fa0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xe0f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x4489));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f92));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0010));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2048));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0091));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9880));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd602));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fea));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ef));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xef00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7100));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x5064));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));
#ifndef VTSS_10BASE_TE
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0071));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf6d9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0db6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0059));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x6596));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0514));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0041));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0280));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf7dd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x006d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x95d4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0049));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2410));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
#else //using 10BASE-Te
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, 31, 0x0002));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, 0x8000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, 31, 0x52b5));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa499));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0075));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf759));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0914));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff7b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0eb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x85d6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8490));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0055));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x44d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8492));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0044));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa8aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8494));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0cb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8496));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff79));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8498));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0caa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0029));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x265d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd658));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b4));
#endif

    // Improve 100BASE-TX link startup robustness to address interop issue
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001));

    VTSS_I("luton26_atom12_revCD_init_script done");
    return luton26_atom12_revC_patch(vtss_state, port_no);
}

// Initialization need for ATOM12 rev. B. (For whole chip and must be done before init. of the individual ports)
//
// In : phy - Any port within the chip.
//
// Return : VTSS_RC_OK if configuration done else error code.
// Date   : 30-10-2012
//
//Initializes entire 12-port chip containing specified PHY
static vtss_rc luton26_atom12_revB_init_script(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001)); //Turn ON broadcast to all 12 PHYs

    VTSS_I("phy:%d", port_no);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MODE_CONTROL, 0x1000));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x2040));
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_CU_PMD_TX_CTRL, 0x02f0));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x6530));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_9, 0x1800));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8212));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0001));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1b00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fa0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0001));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xe489));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f92));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0151));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0011));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7100));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x547f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf00d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7620));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x345f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x481a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2d00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fb0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd6bb));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xbf81));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9688));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0013));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x292a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fa4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x003c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3800));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f8a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0422));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f86));

    // Fix for bugzilla#9870 (Atheros EEE interop) and bugzilla#9885 (1000BT too long to link up)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x01bd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fac));

    // Improve 100BASE-TX link startup robustness to address interop issue
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf7df));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffdf));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0085));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf3c6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x07c2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x002b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2dff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9794));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x00ba));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe2));

    // Bugzilla#8183 - Ports with different speeds can get link up.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fe));

    VTSS_RC(vtss_phy_65nm_10BASE_init(vtss_state, port_no, 0));

    // Work-around solution for bugzilla#6859 from James McIntosh
    //Our solution is to force the BlindSampleTimer to 0x080 by setting
    //BlindSampleTimerForce to '1' (bit 22) and BlindSampleTimerForceVal to 0x080
    //(bits 21:13) in register 0x3d in the AutoNegDbgNode.  This increases the time
    //to wait for the link to come up before allowing the crossover state to switch
    //to ~511 ms.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0212));
    VTSS_RC(luton26_atom12_revB_patch(vtss_state, port_no)); // Download Luton26/Atom12 Rev. B patch

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001)); //Turn off broadcast to all 12 PHYs

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_pre_init_seq_atom(vtss_state_t *vtss_state,
                                          vtss_port_no_t port_no, BOOL luton26_mode)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no]; // Get PHY info

    // REV A work around
    VTSS_I("ps->type.revision:%d", ps->type.revision);
    if (ps->type.revision == VTSS_PHY_ATOM_REV_A) {
        VTSS_E("Atom revison A not supported");
        return VTSS_RC_ERROR;
    } else if (ps->type.revision == VTSS_PHY_ATOM_REV_B) {
        // So far this is Rev. B.
        VTSS_RC(luton26_atom12_revB_init_script(vtss_state, port_no));
    } else if (ps->type.revision == VTSS_PHY_ATOM_REV_C) {
        VTSS_RC(luton26_atom12_revCD_init_script(vtss_state, port_no, ps->type.revision));
    } else if (ps->type.revision == VTSS_PHY_ATOM_REV_D) {
        VTSS_RC(luton26_atom12_revCD_init_script(vtss_state, port_no, ps->type.revision));
    } else {
        VTSS_I("Pre_init script not implemented for Atom rev:%d, defaulting to latest known init script", ps->type.revision);
        VTSS_RC(luton26_atom12_revCD_init_script(vtss_state, port_no, ps->type.revision));
    }


    return VTSS_RC_OK;
}

// Initializing 8512/8522/Luton26 PHY for the individual ports.
// In  : port_no       - Phy port number
//       luton26_mode  - Set to TRUE if the phy is the internal Luton26 phy.
vtss_rc vtss_phy_init_seq_atom(
    vtss_state_t *vtss_state,
    vtss_phy_port_state_t *ps,
    vtss_port_no_t        port_no,
    BOOL                  luton26_mode)
{
    if (ps->type.revision == VTSS_PHY_ATOM_REV_A) {
        // Workaround for REV A
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_25, 1)) ; //Inhibit low-power features that may or may not be causing trouble
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_22, 0x1800)); // band-gap boost +3 setting, leave cac and vac trims alone for now
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8012)); // Make sure TRClk125 is running (needed during COMA)
        VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 3));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0)); // Use minimum setting for 10BT line-drivers as all higher-power setting increase 200MHz noise on transmitter
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe0));
        VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8012)); // Restore normal gating for TRClk125
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    }

    return VTSS_RC_OK;
}

/************************************************************************/
/* Tesla family functions                                               */
/************************************************************************/

// Tesla  Rev. A. Internal 8051 patch.(From James M., 9-27-2011)
// (additional workaround for BZ #5545 and SPI output bug)
// In     : port_no - any port within the chip where to load the 8051 code.
// Return : VTSS_RC_OK if configuration done else error code.

// Download patch into PRAM for the internal 8051
static vtss_rc tesla_revA_8051_patch_9_27_2011(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val = 0;
    u16 chip_port_no = 0;
    BOOL skip_dnload = FALSE;
    BOOL patch_ok = FALSE;

    static const u8 patch_arr[] = {
        0x44, 0xdd, 0x02, 0x41, 0xff, 0x02, 0x42, 0xc3, 0x02, 0x45,
        0x06, 0x02, 0x45, 0x07, 0x02, 0x45, 0x08, 0x8f, 0x27, 0x7b,
        0xbb, 0x7d, 0x0e, 0x7f, 0x04, 0x12, 0x3c, 0x20, 0xef, 0x4e,
        0x60, 0x03, 0x02, 0x41, 0xe6, 0xe4, 0xf5, 0x19, 0x74, 0x01,
        0x7e, 0x00, 0xa8, 0x19, 0x08, 0x80, 0x05, 0xc3, 0x33, 0xce,
        0x33, 0xce, 0xd8, 0xf9, 0xff, 0xef, 0x55, 0x27, 0x70, 0x03,
        0x02, 0x41, 0xda, 0x85, 0x19, 0xfb, 0x7b, 0xbb, 0xe4, 0xfd,
        0xff, 0x12, 0x3c, 0x20, 0xef, 0x4e, 0x60, 0x03, 0x02, 0x41,
        0xda, 0xe5, 0x19, 0x54, 0x02, 0x75, 0x55, 0x00, 0x25, 0xe0,
        0x25, 0xe0, 0xf5, 0x54, 0xe4, 0x78, 0x93, 0xf6, 0xd2, 0x02,
        0x12, 0x41, 0xe7, 0x7b, 0xff, 0x7d, 0x12, 0x7f, 0x07, 0x12,
        0x3c, 0x20, 0xef, 0x4e, 0x60, 0x03, 0x02, 0x41, 0xd4, 0xc2,
        0x02, 0x74, 0x95, 0x25, 0x19, 0xf9, 0x74, 0xb5, 0x25, 0x19,
        0xf8, 0xe6, 0x27, 0xf5, 0x28, 0xe5, 0x55, 0x24, 0x5b, 0x12,
        0x44, 0x8c, 0x12, 0x3d, 0x48, 0x7b, 0xfc, 0x7d, 0x11, 0x7f,
        0x07, 0x12, 0x3c, 0x20, 0x78, 0x9a, 0xef, 0xf6, 0x78, 0x8f,
        0xe6, 0xfe, 0xef, 0xd3, 0x9e, 0x40, 0x06, 0x78, 0x9a, 0xe6,
        0x78, 0x8f, 0xf6, 0x12, 0x41, 0xe7, 0x7b, 0xec, 0x7d, 0x12,
        0x7f, 0x07, 0x12, 0x3c, 0x20, 0x78, 0x99, 0xef, 0xf6, 0xbf,
        0x07, 0x06, 0x78, 0x91, 0x76, 0x1a, 0x80, 0x1f, 0x78, 0x93,
        0xe6, 0xff, 0x60, 0x0f, 0xc3, 0xe5, 0x28, 0x9f, 0xff, 0x78,
        0x99, 0xe6, 0x85, 0x28, 0xf0, 0xa4, 0x2f, 0x80, 0x07, 0x78,
        0x99, 0xe6, 0x85, 0x28, 0xf0, 0xa4, 0x78, 0x91, 0xf6, 0xe4,
        0x78, 0x90, 0xf6, 0x78, 0x90, 0xe6, 0xff, 0xc3, 0x08, 0x96,
        0x40, 0x03, 0x02, 0x41, 0xbe, 0xef, 0x54, 0x03, 0x60, 0x33,
        0x14, 0x60, 0x46, 0x24, 0xfe, 0x60, 0x42, 0x04, 0x70, 0x4b,
        0xef, 0x24, 0x02, 0xff, 0xe4, 0x33, 0xfe, 0xef, 0x78, 0x02,
        0xce, 0xa2, 0xe7, 0x13, 0xce, 0x13, 0xd8, 0xf8, 0xff, 0xe5,
        0x55, 0x24, 0x5c, 0xcd, 0xe5, 0x54, 0x34, 0xf0, 0xcd, 0x2f,
        0xff, 0xed, 0x3e, 0xfe, 0x12, 0x44, 0xaf, 0x7d, 0x11, 0x80,
        0x0b, 0x78, 0x90, 0xe6, 0x70, 0x04, 0x7d, 0x11, 0x80, 0x02,
        0x7d, 0x12, 0x7f, 0x07, 0x12, 0x3d, 0x08, 0x8e, 0x29, 0x8f,
        0x2a, 0x80, 0x03, 0xe5, 0x29, 0xff, 0x78, 0x93, 0xe6, 0x06,
        0x24, 0x9b, 0xf8, 0xa6, 0x07, 0x78, 0x90, 0x06, 0xe6, 0xb4,
        0x1a, 0x0a, 0xe5, 0x55, 0x24, 0x5c, 0x12, 0x44, 0x8c, 0x12,
        0x3d, 0x48, 0x78, 0x93, 0xe6, 0x65, 0x28, 0x70, 0x82, 0x75,
        0xdb, 0x20, 0x75, 0xdb, 0x28, 0x12, 0x44, 0xa4, 0x12, 0x44,
        0xa4, 0xe5, 0x19, 0x12, 0x44, 0x97, 0xe5, 0x19, 0xc3, 0x13,
        0x12, 0x44, 0x97, 0x78, 0x93, 0x16, 0xe6, 0x24, 0x9b, 0xf8,
        0xe6, 0xff, 0x7e, 0x08, 0x1e, 0xef, 0xa8, 0x06, 0x08, 0x80,
        0x02, 0xc3, 0x13, 0xd8, 0xfc, 0xfd, 0xc4, 0x33, 0x54, 0xe0,
        0xf5, 0xdb, 0xef, 0xa8, 0x06, 0x08, 0x80, 0x02, 0xc3, 0x13,
        0xd8, 0xfc, 0xfd, 0xc4, 0x33, 0x54, 0xe0, 0x44, 0x08, 0xf5,
        0xdb, 0xee, 0x70, 0xd8, 0x78, 0x93, 0xe6, 0x70, 0xc8, 0x75,
        0xdb, 0x10, 0x02, 0x40, 0xea, 0x78, 0x90, 0xe6, 0xc3, 0x94,
        0x17, 0x50, 0x0e, 0xe5, 0x55, 0x24, 0x62, 0x12, 0x41, 0xf5,
        0xe5, 0x55, 0x24, 0x5c, 0x12, 0x41, 0xf5, 0x20, 0x02, 0x03,
        0x02, 0x40, 0x63, 0x05, 0x19, 0xe5, 0x19, 0xc3, 0x94, 0x04,
        0x50, 0x03, 0x02, 0x40, 0x27, 0x22, 0xe5, 0x55, 0x24, 0x5c,
        0xff, 0xe5, 0x54, 0x34, 0xf0, 0xfe, 0x12, 0x44, 0xaf, 0x22,
        0xff, 0xe5, 0x54, 0x34, 0xf0, 0xfe, 0x12, 0x44, 0xaf, 0x22,
        0xd2, 0x00, 0x75, 0xfb, 0x03, 0xab, 0x59, 0xaa, 0x58, 0x7d,
        0x19, 0x7f, 0x03, 0x12, 0x3d, 0x48, 0xe5, 0x59, 0x54, 0x0f,
        0x24, 0xf1, 0x70, 0x03, 0x02, 0x42, 0xb8, 0x24, 0x02, 0x60,
        0x03, 0x02, 0x42, 0xad, 0x12, 0x44, 0xc8, 0x12, 0x44, 0xcf,
        0xd8, 0xfb, 0xff, 0x20, 0xe2, 0x2a, 0x13, 0x92, 0x04, 0xef,
        0xa2, 0xe1, 0x92, 0x03, 0x30, 0x04, 0x1f, 0xe4, 0xf5, 0x21,
        0xe5, 0x21, 0x24, 0x17, 0xfd, 0x7b, 0x54, 0x7f, 0x04, 0x12,
        0x3c, 0x20, 0x74, 0xbd, 0x25, 0x21, 0xf8, 0xa6, 0x07, 0x05,
        0x21, 0xe5, 0x21, 0xc3, 0x94, 0x02, 0x40, 0xe4, 0x12, 0x44,
        0xc8, 0x12, 0x44, 0xcf, 0xd8, 0xfb, 0x54, 0x05, 0x64, 0x04,
        0x70, 0x27, 0x78, 0x92, 0xe6, 0x78, 0x94, 0xf6, 0xe5, 0x58,
        0xff, 0x33, 0x95, 0xe0, 0xef, 0x54, 0x0f, 0x78, 0x92, 0xf6,
        0x12, 0x43, 0x85, 0x20, 0x04, 0x0c, 0x12, 0x44, 0xc8, 0x12,
        0x44, 0xcf, 0xd8, 0xfb, 0x13, 0x92, 0x05, 0x22, 0xc2, 0x05,
        0x22, 0x12, 0x44, 0xc8, 0x12, 0x44, 0xcf, 0xd8, 0xfb, 0x54,
        0x05, 0x64, 0x05, 0x70, 0x1e, 0x78, 0x92, 0x7d, 0xb8, 0x12,
        0x42, 0xb9, 0x78, 0x8f, 0x7d, 0x74, 0x12, 0x42, 0xb9, 0xe4,
        0x78, 0x8f, 0xf6, 0x22, 0x7b, 0x01, 0x7a, 0x00, 0x7d, 0xee,
        0x7f, 0x92, 0x12, 0x37, 0x1c, 0x22, 0xe6, 0xfb, 0x7a, 0x00,
        0x7f, 0x92, 0x12, 0x37, 0x1c, 0x22, 0x30, 0x04, 0x03, 0x12,
        0x44, 0x3d, 0x78, 0x92, 0xe6, 0xff, 0x60, 0x03, 0x12, 0x40,
        0x12, 0xe4, 0xf5, 0x19, 0x12, 0x44, 0xd6, 0x20, 0xe7, 0x03,
        0x02, 0x43, 0x78, 0x85, 0x19, 0xfb, 0x7d, 0x1c, 0xe4, 0xff,
        0x12, 0x3d, 0x08, 0x8e, 0x54, 0x8f, 0x55, 0xe5, 0x54, 0x13,
        0x13, 0x13, 0x54, 0x0c, 0x44, 0x80, 0xf5, 0x1b, 0xe5, 0x54,
        0x54, 0xc0, 0x70, 0x06, 0xe5, 0x55, 0x54, 0x18, 0x60, 0x12,
        0x7e, 0x00, 0xe5, 0x55, 0x54, 0x18, 0x78, 0x03, 0xce, 0xc3,
        0x13, 0xce, 0x13, 0xd8, 0xf9, 0x04, 0x42, 0x1b, 0xe5, 0x1b,
        0x54, 0x03, 0x64, 0x03, 0x70, 0x33, 0x12, 0x44, 0xd6, 0x54,
        0x03, 0x64, 0x03, 0x60, 0x21, 0x75, 0x14, 0xc4, 0x75, 0x15,
        0x06, 0x7d, 0x0a, 0xe4, 0xff, 0x12, 0x3d, 0x08, 0xee, 0x30,
        0xe6, 0x08, 0x43, 0x1b, 0x10, 0x75, 0x16, 0x02, 0x80, 0x2b,
        0x53, 0x1b, 0xef, 0x75, 0x16, 0x03, 0x80, 0x23, 0x12, 0x44,
        0xd6, 0x54, 0x10, 0x42, 0x1b, 0x80, 0x21, 0xe5, 0x1b, 0x54,
        0x03, 0x64, 0x03, 0x60, 0x19, 0x12, 0x44, 0xd6, 0x54, 0x03,
        0xff, 0xbf, 0x03, 0x10, 0x75, 0x14, 0xc4, 0x75, 0x15, 0x06,
        0xe4, 0xf5, 0x16, 0x7f, 0xfe, 0x7e, 0x0e, 0x12, 0x3c, 0x49,
        0x74, 0xb9, 0x25, 0x19, 0xf8, 0xa6, 0x1b, 0x05, 0x19, 0xe5,
        0x19, 0xc3, 0x94, 0x04, 0x50, 0x03, 0x02, 0x42, 0xd5, 0x22,
        0x78, 0x8f, 0xe6, 0xfb, 0x7a, 0x00, 0x7d, 0x74, 0x7f, 0x92,
        0x12, 0x37, 0x1c, 0xe4, 0x78, 0x8f, 0xf6, 0xf5, 0x22, 0x74,
        0x01, 0x7e, 0x00, 0xa8, 0x22, 0x08, 0x80, 0x05, 0xc3, 0x33,
        0xce, 0x33, 0xce, 0xd8, 0xf9, 0xff, 0x78, 0x92, 0xe6, 0xfd,
        0xef, 0x5d, 0x60, 0x44, 0x85, 0x22, 0xfb, 0xe5, 0x22, 0x54,
        0x02, 0x25, 0xe0, 0x25, 0xe0, 0xfe, 0xe4, 0x24, 0x5b, 0xfb,
        0xee, 0x12, 0x44, 0x8f, 0x12, 0x3d, 0x48, 0x7b, 0x40, 0x7d,
        0x11, 0x7f, 0x07, 0x12, 0x3c, 0x20, 0x74, 0x95, 0x25, 0x22,
        0xf8, 0xa6, 0x07, 0x7b, 0x11, 0x7d, 0x12, 0x7f, 0x07, 0x12,
        0x3c, 0x20, 0xef, 0x4e, 0x60, 0x09, 0x74, 0xb5, 0x25, 0x22,
        0xf8, 0x76, 0x04, 0x80, 0x07, 0x74, 0xb5, 0x25, 0x22, 0xf8,
        0x76, 0x0a, 0x05, 0x22, 0xe5, 0x22, 0xc3, 0x94, 0x04, 0x40,
        0x9a, 0x78, 0x94, 0xe6, 0x70, 0x15, 0x78, 0x92, 0xe6, 0x60,
        0x10, 0x75, 0xd9, 0x38, 0x75, 0xdb, 0x10, 0x7d, 0xfe, 0x12,
        0x44, 0x33, 0x7d, 0x76, 0x12, 0x44, 0x33, 0x79, 0x94, 0xe7,
        0x78, 0x92, 0x66, 0xff, 0x60, 0x03, 0x12, 0x40, 0x12, 0x78,
        0x92, 0xe6, 0x70, 0x09, 0xfb, 0xfa, 0x7d, 0xfe, 0x7f, 0x8e,
        0x12, 0x37, 0x1c, 0x22, 0x7b, 0x01, 0x7a, 0x00, 0x7f, 0x8e,
        0x12, 0x37, 0x1c, 0x22, 0xe4, 0xf5, 0x4b, 0x74, 0xbd, 0x25,
        0x4b, 0xf8, 0xe6, 0x64, 0x03, 0x60, 0x38, 0xe5, 0x4b, 0x24,
        0x17, 0xfd, 0x7b, 0xeb, 0x7f, 0x04, 0x12, 0x3c, 0x20, 0x8f,
        0x19, 0x85, 0x19, 0xfb, 0x7b, 0x22, 0x7d, 0x18, 0x7f, 0x06,
        0x12, 0x3c, 0x20, 0xef, 0x64, 0x01, 0x4e, 0x70, 0x07, 0x12,
        0x44, 0xed, 0x7b, 0x03, 0x80, 0x0a, 0x12, 0x44, 0xed, 0x74,
        0xbd, 0x25, 0x4b, 0xf8, 0xe6, 0xfb, 0x7a, 0x00, 0x7d, 0x54,
        0x12, 0x37, 0x1c, 0x05, 0x4b, 0xe5, 0x4b, 0xc3, 0x94, 0x02,
        0x40, 0xb5, 0x22, 0xfb, 0xe5, 0x54, 0x34, 0xf0, 0xfa, 0x7d,
        0x10, 0x7f, 0x07, 0x22, 0x54, 0x01, 0xc4, 0x33, 0x54, 0xe0,
        0xf5, 0xdb, 0x44, 0x08, 0xf5, 0xdb, 0x22, 0xf5, 0xdb, 0x75,
        0xdb, 0x08, 0xf5, 0xdb, 0x75, 0xdb, 0x08, 0x22, 0xab, 0x07,
        0xaa, 0x06, 0x7d, 0x10, 0x7f, 0x07, 0x12, 0x3d, 0x48, 0x7b,
        0xff, 0x7d, 0x10, 0x7f, 0x07, 0x12, 0x3c, 0x20, 0xef, 0x4e,
        0x60, 0xf3, 0x22, 0xe5, 0x59, 0xae, 0x58, 0x78, 0x04, 0x22,
        0xce, 0xa2, 0xe7, 0x13, 0xce, 0x13, 0x22, 0x74, 0xb9, 0x25,
        0x19, 0xf8, 0xe6, 0x22, 0x7f, 0x04, 0x78, 0xb9, 0x74, 0x88,
        0xf6, 0x08, 0xdf, 0xfc, 0x12, 0x45, 0x01, 0x02, 0x44, 0xf7,
        0xe5, 0x4b, 0x24, 0x17, 0x54, 0x1f, 0x44, 0x80, 0xff, 0x22,
        0xe4, 0x78, 0x92, 0xf6, 0xc2, 0x05, 0x78, 0x8f, 0xf6, 0x22,
        0xc2, 0x04, 0xc2, 0x03, 0x22, 0x22, 0x22, 0x22
    };

    // Only download 8051 Patches to Port 0 of PHY!
    // Check to see if this is PHY Port 0, If it is not, the 8051 CRC Calculation will Fail on other PHY Ports */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    chip_port_no = (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11;
    VTSS_D("reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    if (chip_port_no != 0) {
        VTSS_I("Download of micro-patch on Non-Base Port. reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
        //return VTSS_RC_ERR_PHY_PATCH_SETTING_NOT_SUPPORTED;
    }

    // Check to see if the code has already been downloaded correctly, if so, Just return, No need to do it again */
    if (vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                        FIRMWARE_START_ADDR,
                                        sizeof(patch_arr) + 1 /* Add one for the byte auto-added in the download function */,
                                        0x4EE4, FALSE) == VTSS_RC_OK) {

        vtss_state->phy_state[port_no].micro_patch_crc = 0x4EE4;
        // CRC is Correct, So at this point, we can skip the Micro Dnload
        skip_dnload = TRUE;
        patch_ok = TRUE;

        // CRC is Correct, Make sure that all the patches are still present
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_3, &reg_val));
        // Check: Trap ROM at _MicroSmiRead+0x1d to spoof patch-presence
        if (reg_val != 0x3eb7) {
            VTSS_I("CRC for Download correct: FAIL-Check::SpoofPatchPresence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Branch to starting address of SpoofPatchPresence
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_4, &reg_val));
        if (reg_val != 0x4012) {
            VTSS_I("CRC for Download correct: FAIL-Check::Branch to Start Addr of SpoofPatchPresence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Enable patch fram trap described in register 3-4
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, &reg_val));
        if (reg_val != 0x0100) {
            VTSS_I("CRC for Download correct: FAIL-Check::Enabling patch trap for SpoofPatchPresence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Micro not in Reset, Enable 8051 clock enable; operate at 125 MHz
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, &reg_val));
        if ((reg_val & 0xf1ff) != 0xc018) {
            // mask off bits 11:9 and check that speed, etc., are set as expected; i.e., "normal" operating mode with 125 MHz clock
            VTSS_I("CRC for Download correct: FAIL-Check::Enable 8051 Clk Enable and Operating Speed set to 125MHz; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    }

    if (skip_dnload && patch_ok) {
        VTSS_I("Skipping download of 8051, CRC for Download correct; Micro-Patch Enabled and OK");
    } else {
        if (skip_dnload) {
            VTSS_I("Skipping download of 8051, CRC for Download correct; However, Micro-Patch Not Enabled");
        } else {
            VTSS_I("Downloading 8051 Patch, CRC for Download NOT correct;  Setting Micro-Patch to Not Enabled");
            VTSS_RC(download_8051_code(vtss_state, port_no, &patch_arr[0], sizeof(patch_arr)));
            patch_ok = FALSE;
        }

        if (!patch_ok) {
            if (skip_dnload) {
                VTSS_I("Micro-Assert-Reset Performed, Download of 8051 Skipped, Enabling Micro-Patch \n");
                VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
            }
            VTSS_I("Micro-Patch Not Enabled - Enabling at this time");
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_3, 0x3eb7));  // Trap ROM at _MicroSmiRead+0x1d to spoof patch-presence
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_4, 0x4012));  // Branch to starting address of SpoofPatchPresence
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0100)); // Enable patch fram trap described in register 3-4
            // Enable 8051 clock; CLEAR patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4018));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc018));  // Release 8051 SW Reset
            VTSS_I("Enable 8051 clk, Patch present Spoofed, Release SW Reset");

            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            // Check that code is downloaded correctly.
            VTSS_RC(vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                                    FIRMWARE_START_ADDR,
                                                    sizeof(patch_arr) + 1, // Add one for the byte auto-added in the download function
                                                    0x4EE4, FALSE));
        }
    }

    return VTSS_RC_OK;
}

// Tesla  Rev. B Internal 8051 patch.
// In     : port_no - any port within the chip where to load the 8051 code.
// Return : VTSS_RC_OK if configuration done else error code.
//
// Previous Patch was:
// Download patch into PRAM for the internal 8051
// Date: 3Oct2013
// CRC: 0x2BB0
//
// Current Patch is:
// Download patch into PRAM for the internal 8051
// Sept. 15, 2015
// CRC: 0x29E8
// Bug 19146 - BugZero#73251/73098:Default 1G SerDes config incorrect for 100-FX Mode of operation
//             Update SigDet Threshold and SerDes sensitivity for 100FX mode of operation.
//
// Initializes micro patch for all ports of chip containing specified PHY
static vtss_rc tesla_revB_8051_patch(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val = 0;
    u16 chip_port_no = 0;
    BOOL skip_dnload = FALSE;
    BOOL patch_ok = FALSE;

    const u8 patch_arr[] = {
        0x46, 0x4a, 0x02, 0x43, 0x37, 0x02, 0x46, 0x26, 0x02, 0x46,
        0x77, 0x02, 0x45, 0x60, 0x02, 0x45, 0xaf, 0xed, 0xff, 0xe5,
        0xfc, 0x54, 0x38, 0x64, 0x20, 0x70, 0x08, 0x65, 0xff, 0x70,
        0x04, 0xed, 0x44, 0x80, 0xff, 0x22, 0x8f, 0x19, 0x7b, 0xbb,
        0x7d, 0x0e, 0x7f, 0x04, 0x12, 0x3d, 0xd7, 0xef, 0x4e, 0x60,
        0x03, 0x02, 0x41, 0xf9, 0xe4, 0xf5, 0x1a, 0x74, 0x01, 0x7e,
        0x00, 0xa8, 0x1a, 0x08, 0x80, 0x05, 0xc3, 0x33, 0xce, 0x33,
        0xce, 0xd8, 0xf9, 0xff, 0xef, 0x55, 0x19, 0x70, 0x03, 0x02,
        0x41, 0xed, 0x85, 0x1a, 0xfb, 0x7b, 0xbb, 0xe4, 0xfd, 0xff,
        0x12, 0x3d, 0xd7, 0xef, 0x4e, 0x60, 0x03, 0x02, 0x41, 0xed,
        0xe5, 0x1a, 0x54, 0x02, 0x75, 0x1d, 0x00, 0x25, 0xe0, 0x25,
        0xe0, 0xf5, 0x1c, 0xe4, 0x78, 0xc5, 0xf6, 0xd2, 0x0a, 0x12,
        0x41, 0xfa, 0x7b, 0xff, 0x7d, 0x12, 0x7f, 0x07, 0x12, 0x3d,
        0xd7, 0xef, 0x4e, 0x60, 0x03, 0x02, 0x41, 0xe7, 0xc2, 0x0a,
        0x74, 0xc7, 0x25, 0x1a, 0xf9, 0x74, 0xe7, 0x25, 0x1a, 0xf8,
        0xe6, 0x27, 0xf5, 0x1b, 0xe5, 0x1d, 0x24, 0x5b, 0x12, 0x45,
        0xea, 0x12, 0x3e, 0xda, 0x7b, 0xfc, 0x7d, 0x11, 0x7f, 0x07,
        0x12, 0x3d, 0xd7, 0x78, 0xcc, 0xef, 0xf6, 0x78, 0xc1, 0xe6,
        0xfe, 0xef, 0xd3, 0x9e, 0x40, 0x06, 0x78, 0xcc, 0xe6, 0x78,
        0xc1, 0xf6, 0x12, 0x41, 0xfa, 0x7b, 0xec, 0x7d, 0x12, 0x7f,
        0x07, 0x12, 0x3d, 0xd7, 0x78, 0xcb, 0xef, 0xf6, 0xbf, 0x07,
        0x06, 0x78, 0xc3, 0x76, 0x1a, 0x80, 0x1f, 0x78, 0xc5, 0xe6,
        0xff, 0x60, 0x0f, 0xc3, 0xe5, 0x1b, 0x9f, 0xff, 0x78, 0xcb,
        0xe6, 0x85, 0x1b, 0xf0, 0xa4, 0x2f, 0x80, 0x07, 0x78, 0xcb,
        0xe6, 0x85, 0x1b, 0xf0, 0xa4, 0x78, 0xc3, 0xf6, 0xe4, 0x78,
        0xc2, 0xf6, 0x78, 0xc2, 0xe6, 0xff, 0xc3, 0x08, 0x96, 0x40,
        0x03, 0x02, 0x41, 0xd1, 0xef, 0x54, 0x03, 0x60, 0x33, 0x14,
        0x60, 0x46, 0x24, 0xfe, 0x60, 0x42, 0x04, 0x70, 0x4b, 0xef,
        0x24, 0x02, 0xff, 0xe4, 0x33, 0xfe, 0xef, 0x78, 0x02, 0xce,
        0xa2, 0xe7, 0x13, 0xce, 0x13, 0xd8, 0xf8, 0xff, 0xe5, 0x1d,
        0x24, 0x5c, 0xcd, 0xe5, 0x1c, 0x34, 0xf0, 0xcd, 0x2f, 0xff,
        0xed, 0x3e, 0xfe, 0x12, 0x46, 0x0d, 0x7d, 0x11, 0x80, 0x0b,
        0x78, 0xc2, 0xe6, 0x70, 0x04, 0x7d, 0x11, 0x80, 0x02, 0x7d,
        0x12, 0x7f, 0x07, 0x12, 0x3e, 0x9a, 0x8e, 0x1e, 0x8f, 0x1f,
        0x80, 0x03, 0xe5, 0x1e, 0xff, 0x78, 0xc5, 0xe6, 0x06, 0x24,
        0xcd, 0xf8, 0xa6, 0x07, 0x78, 0xc2, 0x06, 0xe6, 0xb4, 0x1a,
        0x0a, 0xe5, 0x1d, 0x24, 0x5c, 0x12, 0x45, 0xea, 0x12, 0x3e,
        0xda, 0x78, 0xc5, 0xe6, 0x65, 0x1b, 0x70, 0x82, 0x75, 0xdb,
        0x20, 0x75, 0xdb, 0x28, 0x12, 0x46, 0x02, 0x12, 0x46, 0x02,
        0xe5, 0x1a, 0x12, 0x45, 0xf5, 0xe5, 0x1a, 0xc3, 0x13, 0x12,
        0x45, 0xf5, 0x78, 0xc5, 0x16, 0xe6, 0x24, 0xcd, 0xf8, 0xe6,
        0xff, 0x7e, 0x08, 0x1e, 0xef, 0xa8, 0x06, 0x08, 0x80, 0x02,
        0xc3, 0x13, 0xd8, 0xfc, 0xfd, 0xc4, 0x33, 0x54, 0xe0, 0xf5,
        0xdb, 0xef, 0xa8, 0x06, 0x08, 0x80, 0x02, 0xc3, 0x13, 0xd8,
        0xfc, 0xfd, 0xc4, 0x33, 0x54, 0xe0, 0x44, 0x08, 0xf5, 0xdb,
        0xee, 0x70, 0xd8, 0x78, 0xc5, 0xe6, 0x70, 0xc8, 0x75, 0xdb,
        0x10, 0x02, 0x40, 0xfd, 0x78, 0xc2, 0xe6, 0xc3, 0x94, 0x17,
        0x50, 0x0e, 0xe5, 0x1d, 0x24, 0x62, 0x12, 0x42, 0x08, 0xe5,
        0x1d, 0x24, 0x5c, 0x12, 0x42, 0x08, 0x20, 0x0a, 0x03, 0x02,
        0x40, 0x76, 0x05, 0x1a, 0xe5, 0x1a, 0xc3, 0x94, 0x04, 0x50,
        0x03, 0x02, 0x40, 0x3a, 0x22, 0xe5, 0x1d, 0x24, 0x5c, 0xff,
        0xe5, 0x1c, 0x34, 0xf0, 0xfe, 0x12, 0x46, 0x0d, 0x22, 0xff,
        0xe5, 0x1c, 0x34, 0xf0, 0xfe, 0x12, 0x46, 0x0d, 0x22, 0xe4,
        0xf5, 0x19, 0x12, 0x46, 0x43, 0x20, 0xe7, 0x1e, 0x7b, 0xfe,
        0x12, 0x42, 0xf9, 0xef, 0xc4, 0x33, 0x33, 0x54, 0xc0, 0xff,
        0xc0, 0x07, 0x7b, 0x54, 0x12, 0x42, 0xf9, 0xd0, 0xe0, 0x4f,
        0xff, 0x74, 0x2a, 0x25, 0x19, 0xf8, 0xa6, 0x07, 0x12, 0x46,
        0x43, 0x20, 0xe7, 0x03, 0x02, 0x42, 0xdf, 0x54, 0x03, 0x64,
        0x03, 0x70, 0x03, 0x02, 0x42, 0xcf, 0x7b, 0xcb, 0x12, 0x43,
        0x2c, 0x8f, 0xfb, 0x7b, 0x30, 0x7d, 0x03, 0xe4, 0xff, 0x12,
        0x3d, 0xd7, 0xc3, 0xef, 0x94, 0x02, 0xee, 0x94, 0x00, 0x50,
        0x2a, 0x12, 0x42, 0xec, 0xef, 0x4e, 0x70, 0x23, 0x12, 0x43,
        0x04, 0x60, 0x0a, 0x12, 0x43, 0x12, 0x70, 0x0c, 0x12, 0x43,
        0x1f, 0x70, 0x07, 0x12, 0x46, 0x39, 0x7b, 0x03, 0x80, 0x07,
        0x12, 0x46, 0x39, 0x12, 0x46, 0x43, 0xfb, 0x7a, 0x00, 0x7d,
        0x54, 0x80, 0x3e, 0x12, 0x42, 0xec, 0xef, 0x4e, 0x70, 0x24,
        0x12, 0x43, 0x04, 0x60, 0x0a, 0x12, 0x43, 0x12, 0x70, 0x0f,
        0x12, 0x43, 0x1f, 0x70, 0x0a, 0x12, 0x46, 0x39, 0xe4, 0xfb,
        0xfa, 0x7d, 0xee, 0x80, 0x1e, 0x12, 0x46, 0x39, 0x7b, 0x01,
        0x7a, 0x00, 0x7d, 0xee, 0x80, 0x13, 0x12, 0x46, 0x39, 0x12,
        0x46, 0x43, 0x54, 0x40, 0xfe, 0xc4, 0x13, 0x13, 0x54, 0x03,
        0xfb, 0x7a, 0x00, 0x7d, 0xee, 0x12, 0x38, 0xbd, 0x7b, 0xff,
        0x12, 0x43, 0x2c, 0xef, 0x4e, 0x70, 0x07, 0x74, 0x2a, 0x25,
        0x19, 0xf8, 0xe4, 0xf6, 0x05, 0x19, 0xe5, 0x19, 0xc3, 0x94,
        0x02, 0x50, 0x03, 0x02, 0x42, 0x15, 0x22, 0xe5, 0x19, 0x24,
        0x17, 0xfd, 0x7b, 0x20, 0x7f, 0x04, 0x12, 0x3d, 0xd7, 0x22,
        0xe5, 0x19, 0x24, 0x17, 0xfd, 0x7f, 0x04, 0x12, 0x3d, 0xd7,
        0x22, 0x7b, 0x22, 0x7d, 0x18, 0x7f, 0x06, 0x12, 0x3d, 0xd7,
        0xef, 0x64, 0x01, 0x4e, 0x22, 0x7d, 0x1c, 0xe4, 0xff, 0x12,
        0x3e, 0x9a, 0xef, 0x54, 0x1b, 0x64, 0x0a, 0x22, 0x7b, 0xcc,
        0x7d, 0x10, 0xff, 0x12, 0x3d, 0xd7, 0xef, 0x64, 0x01, 0x4e,
        0x22, 0xe5, 0x19, 0x24, 0x17, 0xfd, 0x7f, 0x04, 0x12, 0x3d,
        0xd7, 0x22, 0xd2, 0x08, 0x75, 0xfb, 0x03, 0xab, 0x7e, 0xaa,
        0x7d, 0x7d, 0x19, 0x7f, 0x03, 0x12, 0x3e, 0xda, 0xe5, 0x7e,
        0x54, 0x0f, 0x24, 0xf3, 0x60, 0x03, 0x02, 0x43, 0xe9, 0x12,
        0x46, 0x5a, 0x12, 0x46, 0x61, 0xd8, 0xfb, 0xff, 0x20, 0xe2,
        0x35, 0x13, 0x92, 0x0c, 0xef, 0xa2, 0xe1, 0x92, 0x0b, 0x30,
        0x0c, 0x2a, 0xe4, 0xf5, 0x10, 0x7b, 0xfe, 0x12, 0x43, 0xff,
        0xef, 0xc4, 0x33, 0x33, 0x54, 0xc0, 0xff, 0xc0, 0x07, 0x7b,
        0x54, 0x12, 0x43, 0xff, 0xd0, 0xe0, 0x4f, 0xff, 0x74, 0x2a,
        0x25, 0x10, 0xf8, 0xa6, 0x07, 0x05, 0x10, 0xe5, 0x10, 0xc3,
        0x94, 0x02, 0x40, 0xd9, 0x12, 0x46, 0x5a, 0x12, 0x46, 0x61,
        0xd8, 0xfb, 0x54, 0x05, 0x64, 0x04, 0x70, 0x27, 0x78, 0xc4,
        0xe6, 0x78, 0xc6, 0xf6, 0xe5, 0x7d, 0xff, 0x33, 0x95, 0xe0,
        0xef, 0x54, 0x0f, 0x78, 0xc4, 0xf6, 0x12, 0x44, 0x0a, 0x20,
        0x0c, 0x0c, 0x12, 0x46, 0x5a, 0x12, 0x46, 0x61, 0xd8, 0xfb,
        0x13, 0x92, 0x0d, 0x22, 0xc2, 0x0d, 0x22, 0x12, 0x46, 0x5a,
        0x12, 0x46, 0x61, 0xd8, 0xfb, 0x54, 0x05, 0x64, 0x05, 0x70,
        0x1e, 0x78, 0xc4, 0x7d, 0xb8, 0x12, 0x43, 0xf5, 0x78, 0xc1,
        0x7d, 0x74, 0x12, 0x43, 0xf5, 0xe4, 0x78, 0xc1, 0xf6, 0x22,
        0x7b, 0x01, 0x7a, 0x00, 0x7d, 0xee, 0x7f, 0x92, 0x12, 0x38,
        0xbd, 0x22, 0xe6, 0xfb, 0x7a, 0x00, 0x7f, 0x92, 0x12, 0x38,
        0xbd, 0x22, 0xe5, 0x10, 0x24, 0x17, 0xfd, 0x7f, 0x04, 0x12,
        0x3d, 0xd7, 0x22, 0x78, 0xc1, 0xe6, 0xfb, 0x7a, 0x00, 0x7d,
        0x74, 0x7f, 0x92, 0x12, 0x38, 0xbd, 0xe4, 0x78, 0xc1, 0xf6,
        0xf5, 0x11, 0x74, 0x01, 0x7e, 0x00, 0xa8, 0x11, 0x08, 0x80,
        0x05, 0xc3, 0x33, 0xce, 0x33, 0xce, 0xd8, 0xf9, 0xff, 0x78,
        0xc4, 0xe6, 0xfd, 0xef, 0x5d, 0x60, 0x44, 0x85, 0x11, 0xfb,
        0xe5, 0x11, 0x54, 0x02, 0x25, 0xe0, 0x25, 0xe0, 0xfe, 0xe4,
        0x24, 0x5b, 0xfb, 0xee, 0x12, 0x45, 0xed, 0x12, 0x3e, 0xda,
        0x7b, 0x40, 0x7d, 0x11, 0x7f, 0x07, 0x12, 0x3d, 0xd7, 0x74,
        0xc7, 0x25, 0x11, 0xf8, 0xa6, 0x07, 0x7b, 0x11, 0x7d, 0x12,
        0x7f, 0x07, 0x12, 0x3d, 0xd7, 0xef, 0x4e, 0x60, 0x09, 0x74,
        0xe7, 0x25, 0x11, 0xf8, 0x76, 0x04, 0x80, 0x07, 0x74, 0xe7,
        0x25, 0x11, 0xf8, 0x76, 0x0a, 0x05, 0x11, 0xe5, 0x11, 0xc3,
        0x94, 0x04, 0x40, 0x9a, 0x78, 0xc6, 0xe6, 0x70, 0x15, 0x78,
        0xc4, 0xe6, 0x60, 0x10, 0x75, 0xd9, 0x38, 0x75, 0xdb, 0x10,
        0x7d, 0xfe, 0x12, 0x44, 0xb8, 0x7d, 0x76, 0x12, 0x44, 0xb8,
        0x79, 0xc6, 0xe7, 0x78, 0xc4, 0x66, 0xff, 0x60, 0x03, 0x12,
        0x40, 0x25, 0x78, 0xc4, 0xe6, 0x70, 0x09, 0xfb, 0xfa, 0x7d,
        0xfe, 0x7f, 0x8e, 0x12, 0x38, 0xbd, 0x22, 0x7b, 0x01, 0x7a,
        0x00, 0x7f, 0x8e, 0x12, 0x38, 0xbd, 0x22, 0xe4, 0xf5, 0xfb,
        0x7d, 0x1c, 0xe4, 0xff, 0x12, 0x3e, 0x9a, 0xad, 0x07, 0xac,
        0x06, 0xec, 0x54, 0xc0, 0xff, 0xed, 0x54, 0x3f, 0x4f, 0xf5,
        0x20, 0x30, 0x06, 0x2c, 0x30, 0x01, 0x08, 0xa2, 0x04, 0x72,
        0x03, 0x92, 0x07, 0x80, 0x21, 0x30, 0x04, 0x06, 0x7b, 0xcc,
        0x7d, 0x11, 0x80, 0x0d, 0x30, 0x03, 0x06, 0x7b, 0xcc, 0x7d,
        0x10, 0x80, 0x04, 0x7b, 0x66, 0x7d, 0x16, 0xe4, 0xff, 0x12,
        0x3d, 0xd7, 0xee, 0x4f, 0x24, 0xff, 0x92, 0x07, 0xaf, 0xfb,
        0x74, 0x26, 0x2f, 0xf8, 0xe6, 0xff, 0xa6, 0x20, 0x20, 0x07,
        0x39, 0x8f, 0x20, 0x30, 0x07, 0x34, 0x30, 0x00, 0x31, 0x20,
        0x04, 0x2e, 0x20, 0x03, 0x2b, 0xe4, 0xf5, 0xff, 0x75, 0xfc,
        0xc2, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0xaf, 0xfe, 0xef, 0x20,
        0xe3, 0x1a, 0xae, 0xfd, 0x44, 0x08, 0xf5, 0xfe, 0x75, 0xfc,
        0x80, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0x8f, 0xfe, 0x8e, 0xfd,
        0x75, 0xfc, 0x80, 0xe5, 0xfc, 0x30, 0xe0, 0xfb, 0x05, 0xfb,
        0xaf, 0xfb, 0xef, 0xc3, 0x94, 0x04, 0x50, 0x03, 0x02, 0x44,
        0xc5, 0xe4, 0xf5, 0xfb, 0x22, 0xe5, 0x7e, 0x54, 0x0f, 0x64,
        0x01, 0x70, 0x23, 0xe5, 0x7e, 0x30, 0xe4, 0x1e, 0x90, 0x47,
        0xd0, 0xe0, 0x44, 0x02, 0xf0, 0x54, 0xfb, 0xf0, 0x90, 0x47,
        0xd4, 0xe0, 0x44, 0x04, 0xf0, 0x7b, 0x03, 0x7d, 0x5b, 0x7f,
        0x5d, 0x12, 0x36, 0x29, 0x7b, 0x0e, 0x80, 0x1c, 0x90, 0x47,
        0xd0, 0xe0, 0x54, 0xfd, 0xf0, 0x44, 0x04, 0xf0, 0x90, 0x47,
        0xd4, 0xe0, 0x54, 0xfb, 0xf0, 0x7b, 0x02, 0x7d, 0x5b, 0x7f,
        0x5d, 0x12, 0x36, 0x29, 0x7b, 0x06, 0x7d, 0x60, 0x7f, 0x63,
        0x12, 0x36, 0x29, 0x22, 0xe5, 0x7e, 0x30, 0xe5, 0x35, 0x30,
        0xe4, 0x0b, 0x7b, 0x02, 0x7d, 0x33, 0x7f, 0x35, 0x12, 0x36,
        0x29, 0x80, 0x10, 0x7b, 0x01, 0x7d, 0x33, 0x7f, 0x35, 0x12,
        0x36, 0x29, 0x90, 0x47, 0xd2, 0xe0, 0x44, 0x04, 0xf0, 0x90,
        0x47, 0xd2, 0xe0, 0x54, 0xf7, 0xf0, 0x90, 0x47, 0xd1, 0xe0,
        0x44, 0x10, 0xf0, 0x7b, 0x05, 0x7d, 0x84, 0x7f, 0x86, 0x12,
        0x36, 0x29, 0x22, 0xfb, 0xe5, 0x1c, 0x34, 0xf0, 0xfa, 0x7d,
        0x10, 0x7f, 0x07, 0x22, 0x54, 0x01, 0xc4, 0x33, 0x54, 0xe0,
        0xf5, 0xdb, 0x44, 0x08, 0xf5, 0xdb, 0x22, 0xf5, 0xdb, 0x75,
        0xdb, 0x08, 0xf5, 0xdb, 0x75, 0xdb, 0x08, 0x22, 0xab, 0x07,
        0xaa, 0x06, 0x7d, 0x10, 0x7f, 0x07, 0x12, 0x3e, 0xda, 0x7b,
        0xff, 0x7d, 0x10, 0x7f, 0x07, 0x12, 0x3d, 0xd7, 0xef, 0x4e,
        0x60, 0xf3, 0x22, 0x12, 0x44, 0xc2, 0x30, 0x0c, 0x03, 0x12,
        0x42, 0x12, 0x78, 0xc4, 0xe6, 0xff, 0x60, 0x03, 0x12, 0x40,
        0x25, 0x22, 0xe5, 0x19, 0x24, 0x17, 0x54, 0x1f, 0x44, 0x80,
        0xff, 0x22, 0x74, 0x2a, 0x25, 0x19, 0xf8, 0xe6, 0x22, 0x12,
        0x46, 0x72, 0x12, 0x46, 0x68, 0x90, 0x47, 0xfa, 0xe0, 0x54,
        0xf8, 0x44, 0x02, 0xf0, 0x22, 0xe5, 0x7e, 0xae, 0x7d, 0x78,
        0x04, 0x22, 0xce, 0xa2, 0xe7, 0x13, 0xce, 0x13, 0x22, 0xe4,
        0x78, 0xc4, 0xf6, 0xc2, 0x0d, 0x78, 0xc1, 0xf6, 0x22, 0xc2,
        0x0c, 0xc2, 0x0b, 0x22, 0x22
    };

    // Only download 8051 Patches to Port 0 of PHY!
    // Check to see if this is PHY Port 0, If it is not, the 8051 CRC Calculation will Fail on other PHY Ports */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    chip_port_no = (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11;
    VTSS_D("reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    if (chip_port_no != 0) {
        VTSS_I("Download micro-patch on Non-Base Port.  reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    }
    // Check to see if the code has already been downloaded correctly, if so, Just return, No need to do it again */
    if (vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                        FIRMWARE_START_ADDR,
                                        sizeof(patch_arr) + 1 /* Add one for the byte auto-added in the download function */,
                                        0x29E8, TRUE) == VTSS_RC_OK) {

        // CRC is Correct, So at this point, we can skip the Micro Dnload
        skip_dnload = TRUE;
        patch_ok = TRUE;

        // CRC is Correct, Make sure that all the patches are still present
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_3, &reg_val));
        // Check: Trap ROM at _MicroSmiRead+0x1d to spoof patch-presence
        if (reg_val != 0x3eb7) {
            VTSS_I("CRC for Download correct: FAIL-Check::SpoofPatchPresence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Branch to starting address of SpoofPatchPresence
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_4, &reg_val));
        if (reg_val != 0x4012) {
            VTSS_I("CRC for Download correct: FAIL-Check::Branch to Start Addr of SpoofPatchPresence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Enable patch fram trap described in register 3-4
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, &reg_val));
        if (reg_val != 0x0100) {
            VTSS_I("CRC for Download correct: FAIL-Check::Enabling patch trap for SpoofPatchPresence; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        // Check: Micro not in Reset, Enable 8051 clock enable; operate at 125 MHz
        VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, &reg_val));
        if ((reg_val & 0xf1ff) != 0xc018) {
            // mask off bits 11:9 and check that speed, etc., are set as expected; i.e., "normal" operating mode with 125 MHz clock
            VTSS_I("CRC for Download correct: FAIL-Check::Enable 8051 Clk Enable and Operating Speed set to 125MHz; RegVal: 0x%x", reg_val);
            patch_ok = FALSE;
        }

        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    }

    if (skip_dnload && patch_ok) {
        VTSS_I("Skipping download of 8051, CRC for Download correct; Micro-Patch Enabled and OK");
    } else {
        if (skip_dnload) {
            VTSS_I("Skipping download of 8051, CRC for Download correct; However, Micro-Patch Not Enabled");
        } else {
            VTSS_I("Downloading 8051 Patch, CRC for Download NOT correct;  Setting Micro-Patch to Not Enabled");
            VTSS_RC(download_8051_code(vtss_state, port_no, &patch_arr[0], sizeof(patch_arr)));
            patch_ok = FALSE;
        }

        if (!patch_ok) {
            if (skip_dnload) {
                VTSS_I("Micro-Assert-Reset Performed, Download of 8051 Skipped, Enabling Micro-Patch \n");
                VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
            }
            VTSS_I("Micro-Patch Not Enabled - Enabling at this time");
            VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_3, 0x3eb7));  // Trap ROM at _MicroSmiRead+0x1d to spoof patch-presence
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_4, 0x4012));  // Branch to starting address of SpoofPatchPresence
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0100)); // Enable patch fram trap described in register 3-4
            // Enable 8051 clock; CLEAR patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4018));
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc018));  // Release 8051 SW Reset
            VTSS_I("Enable 8051 clk, Patch present Spoofed, Release SW Reset");

            VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

            // Check that code is downloaded correctly.
            VTSS_RC(vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                                    FIRMWARE_START_ADDR,
                                                    sizeof(patch_arr) + 1, // Add one for the byte auto-added in the download function
                                                    0x29E8, FALSE));
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc vtss_phy_pre_init_tesla_revB_1588(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    if (!vtss_state->sync_calling_private) { // According to Chakri this shall not be done for warmstart register testing.
        /* Pass the cmd to Micro to initialize all 1588 analyzer registers to default */
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
        VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MICRO_PAGE, 0x801A));
        /* Poll on 18G.15 to clear */
        VTSS_RC(vtss_phy_wait_for_micro_complete(vtss_state, port_no));
        /* return to standard page */
        VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    }
    return VTSS_RC_OK;
}

// Initialization needed for Tesla. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
// Based on matlab init_script.m,  Revision 1.13  2011/08/17 15:20:37  jimb
// Calls James McIntosh' latest patch for the 1588 SPI issue dated 9/12/2011
// On 27-09-2012 - updated to address bugzilla #9871 and #9886

static vtss_rc vtss_phy_pre_init_seq_tesla_17_august_2011 (vtss_state_t *vtss_state,
                                                           vtss_port_no_t port_no)
{
    // MII register writes and test-page register writes go here
    //using broadcast flag to speed things up
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001)); //turn on broadcast writes

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no)); //Switch to test register page
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8,  0x8000, 0x8000)); //Enable token-ring during coma-mode
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no)); //Switch to token-ring register page

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x1));

    /* It is found that the settings commented out below can give a few frames with CRC (one every 1-2 hours), so
       they are left out. The settings are related to EEE, and this may give some EEE problems, but they are going to fixed in chip rev. C.
          VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9fa2));
          VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968a));

          VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0xd2));
          VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x545a));
          VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c)); */

    // Fix for bugzilla#9871 (Atheros EEE interop) and bugzilla#9886 (1000BT too long to link up)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x01bd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fac));


    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xe004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7200));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x5d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xdddd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ee0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0xee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x3f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x5e48));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x2a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2d2e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9794));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x150));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));

    // Improve 100BASE-TX link startup robustness to address interop issue
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));

    //Note that when Tesla is configured for 10BASE-T (not Te), it needs no 10BASE-T configuration as its pulse codes already match
#ifdef VTSS_10BASE_TE
    VTSS_RC(vtss_phy_65nm_10BASE_init(vtss_state, port_no, 0));
#endif
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));             //Switch to test register page
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000)); //Disable token-ring after complete


    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001)); // Turn off broadcast writes

    VTSS_RC(tesla_revB_8051_patch(vtss_state, port_no)); //Load micro patch Tesla RevB

    VTSS_RC(vtss_phy_pre_init_tesla_revB_1588(vtss_state, port_no)); //Init 1588 register using Tesla RevB micro patch

    return VTSS_RC_OK;
}

// Initialization needed for Tesla. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no - First port within the chip.
//
// Return : VTSS_RC_OK if configuration done else error code.

static vtss_rc vtss_phy_pre_init_seq_tesla_4_april_2011(vtss_state_t *vtss_state,
                                                        vtss_port_no_t port_no)
{
    // MII register writes and test-page register writes go here
    //using broadcast flag to speed things up
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no)); //Switch to main register page
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001)); // turn on broadcast writes

    // Set 100BASE-TX edge rate to optimal setting
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x2000, 0xe000));

    // Set 100BASE-TX amplitude to optimal setting after MDI-cal tweak
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no)); //Switch to extended register page 2
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_CU_PMD_TX_CTRL, 0x0200, 0x0f00));

    // Set MDI Cal offset 100 to 0
    // Set MDI Cal offset 1000 to 0
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no)); //Switch to test register page
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x0000, 0x6030));

    //Switch to hardware energy-detector in 1000BASE-T mode
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_9, 0x0000, 0x4000));

    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000)); // Enable token-ring during coma-mode

    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no)); // Switch to token-ring register page

    //TrWrite( base_phy+1, 'eee_TrKp1Short_1000', -1, 0);
    //TrWrite( base_phy+1, 'eee_TrKp2Long_1000', -1, 0);
    //TrWrite( base_phy+1, 'eee_TrKp2Short_1000', -1, 0);
    //TrWrite( base_phy+1, 'eee_TrKp3Long_1000', -1, 1);
    //TrWrite( base_phy+1, 'eee_TrKp3Short_1000', -1, 1);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //eee_Tr... Kp1Long,Kp1Short ..._1000
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0011 )); //eee_Tr... Kp2Long,Kp2Short,Kp3Long,Kp3Short ..._1000
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0 )); //Write eee_TrKp*_1000

    //TrWrite( base_phy+1, 'ph_shift_num1000_eee1', -1, 1); //Double-step when Kp1 selected
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //(no fields)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7100 )); //eee_TrKf1000,ph_shift_num1000_... eee1,eee2,std
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a2 )); //Write eee_TrKf1000,ph_shift_num1000_*

    //TrWrite( base_phy+1, 'SSTrKf1000Slv',-1, 7); //Disable frequency-offset updates at showtime
    //TrWrite( base_phy+1, 'SSTrKp100',-1, 13); //Speed up steady-state to 2*gain of 1 - UNH setting
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00d2 )); //SSTrKp100,SSTrKf100
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x547f )); //SSTrKp1000Mas,SSTrKp1000Slv,SSTrKf1000Slv,Ss[EN]cUpdGain1000
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c )); //Write SSTrK*,SS[EN]cUpdGain1000

    //TrWrite( base_phy+1, 'eee_TrKp1Short_100',-1, 0);
    //TrWrite( base_phy+1, 'eee_TrKp2Long_100',-1, 15);
    //TrWrite( base_phy+1, 'eee_TrKp2Short_100',-1, 0);
    //TrWrite( base_phy+1, 'eee_TrKp3Short_100',-1, 13);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f0 )); //eee_Tr... Kp1Long,Kp1Short ..._100
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf00d )); //eee_Tr... Kp2Long,Kp2Short,Kp3Long,Kp3Short ..._100
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0 )); //Write eee_TrKp*_100

    //TrWrite( base_phy+1, 'ph_shift_num100_eee1', -1, 6); //Quad-step when Kp1 selected
    //TrWrite( base_phy+1, 'ph_shift_num100_eee2', -1, 2); //Double-step when Kp2 selected
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //(no fields)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7100 )); //eee_TrKf100,ph_shift_num100_... eee1,eee2,std
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2 )); //Write eee_TrKf100,ph_shift_num100_*

    //TrWrite( base_phy+1, 'lpi_tr_tmr_val1',-1, '34'); //lengthen tmr1 by 1/2 us
    //TrWrite( base_phy+1, 'lpi_tr_tmr_val2',-1, '5f'); //lengthen tmr2 by 1/2 us
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //(no fields)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x345f )); //lpi_tr_tmr_... val1,val2
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4 )); //Write lpi_tr_tmr_val*

    //TrWrite( base_phy+1, 'nonzero_det_thr1000',-1, 15); // Increase from 8 to reduce noise
    //TrWrite( base_phy+1, 'zero_det_thr_nzd1000',-1, 31); // Increase from 15 to handle 1000BT scrambler length in case 31 zeroes OK
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //nonzero_det_thr1000[5:4]
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf7df )); //nonzero_det_thr1000[3:0],zero_det_thr_... nzd1000,zd1000
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd4 )); //Write non/zero_det_thr*1000

    //TrWrite( base_phy+1, 'nonzero_det_thr100',-1, 15); // Increase from 8 to reduce noise
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //nonzero_det_thr100[5:4]
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf3df )); //nonzero_det_thr100[3:0],zero_det_thr_... nzd100,zd100
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd2 )); //Write non/zero_det_thr*100

    //TrWrite( base_phy+1, 'zero_detect_thresh_zd',-1, 31); // Detect link-partner going quiet more quickly
    //TrWrite( base_phy+1, 'rem_lpi_req_thresh',-1, 15);
    //TrWrite( base_phy+1, 'rem_upd_done_thresh',-1, 15); // Speed up remote update-done detection faster than zero-detection
    //31, 15, and 15 are the default, thus no write

    //TrWrite( base_phy+1, 'LongVgaThresh100',-1, 21); //same as -11 -- UNH setting
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000e )); //DSPreadyTime100[7:2]
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2b00 )); //DSPreadyTime100[1:0],LongVgaThresh100,EnabRandUpdTrig,CMAforces(8b)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fb0 )); //Write DSPreadyTime100,LongVgaThresh100,EnabRandUpdTrig,CMAforces

    //10BT power level optimization for 10BT MAU

    //TrWrite( base_phy+1, 'ld10_pwrlvl_actiphy', -1, 1);
    //TrWrite( base_phy+1, 'ld10_pwrlvl_10tx', -1, 1);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000b )); //SwitchToLD10,PwrUpBothDAC_LD10/G,dac10_keepalive_en
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x05a0 )); //ld10_pwrlvl_... act_ct,g_ct,actiphy,10tx,10rx,100rx,10idle,g
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe0 )); //Write SwitchToLD10,PwrUpBoth*,dac10_keepalive_en,ld10_pwrlvl_*

    //TrWrite( base_phy+1, 'ld10_edge_ctrl1', -1, 3);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //(no fields)
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x00ba )); //ld10_edge_ctrl... 0,1,2,3
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe2 )); //Write ld10_edge_ctrl*

    //TrWrite( base_phy+1, 'VgaGain10',-1, 4);
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000 )); //EnabIndpDfe/Dc/XcUpdTrig,SSFfeDecCntrl,SSEnabFfeUpdTapSel,VgaGain10[4]
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x4689 )); //VgaGain10[3:0],SSVgaSlowDecRate,SSVgaWindow1000/100,SSVgaSerialize
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f92 )); //Write register containing VgaGain10

    // Improve 100BASE-TX link startup robustness to address interop issue
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0060));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));

    //Note that when Tesla is configured for 10BASE-T (not Te), it needs no 10BASE-T configuration as its pulse codes already match
#ifdef VTSS_10BASE_TE
    VTSS_RC(vtss_phy_65nm_10BASE_init(port_no, 0));
#endif

    VTSS_RC(vtss_phy_page_test(vtss_state, port_no)); //Switch to test register page
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000)); // Disable token-ring after complete


    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001)); // Turn off broadcast writes

    VTSS_RC(tesla_revA_8051_patch_9_27_2011(vtss_state, port_no)); //Load micro patch
    return VTSS_RC_OK;
}

// Initialization needed for Tesla. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
// Date : 27-09-2012 - updated to address bugzilla #9871 and #9886
static vtss_rc vtss_phy_pre_init_seq_tesla_rev_d(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x0040));
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_CU_PMD_TX_CTRL, 0x02be));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x4420));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0c00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_9, 0x18cc));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, 0x1320));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x01bd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf147));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0005));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2f54));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0027));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x303d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9792));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0704));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fe));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0006));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0150));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x480a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));
    /*excluding this register configuraiton for tesla revisions <= D , 
      and have to taken care for tesla Rev-E*/
#if 0
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0034));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f80));
#endif
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x82e0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0005));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0208));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9186));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3700));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fb0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9fa0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9688));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9fa0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0020));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x640b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9690));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2220));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8258));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2a20));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3060));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3fa0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xe0f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x4489));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f92));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0010));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2048));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0091));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9880));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd602));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fea));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ef));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xef00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7100));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x5064));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));

    // Improve 100BASE-TX link startup robustness to address interop issue
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));
    // Work-around solution for bugzilla#6859
    //Our solution is to force the BlindSampleTimer to 0x080 by setting
    //BlindSampleTimerForce to '1' (bit 22) and BlindSampleTimerForceVal to 0x080
    //(bits 21:13) in register 0x3d in the AutoNegDbgNode.  This increases the time
    //to wait for the link to come up before allowing the crossover state to switch
    //to ~511 ms.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));

#ifndef VTSS_10BASE_TE
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0071));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf6d9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0db6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0059));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x6596));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0514));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0041));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0280));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf7dd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x006d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x95d4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0049));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2410));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
#else //using 10BASE-Te
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa499));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0075));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf759));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0914));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff7b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0eb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x85d6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8490));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0055));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x44d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8492));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0044));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa8aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8494));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0cb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8496));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff79));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8498));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0caa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0029));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x265d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd658));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b4));
#endif //VTSS_10BASE_TE
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001));

    VTSS_RC(tesla_revB_8051_patch(vtss_state, port_no)); // Rev D. uses the same patch as rev B.

    VTSS_RC(vtss_phy_pre_init_tesla_revB_1588(vtss_state, port_no)); //Init 1588 register using Tesla RevB micro patch

    return VTSS_RC_OK;

}

// Initialization needed for Tesla Rev E. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
// Date : Jan 12,2018 - updated to address bugzilla #9871 and #9886
static vtss_rc vtss_phy_pre_init_seq_tesla_rev_e(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_2, 0x0040));
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_CU_PMD_TX_CTRL, 0x02be));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_20, 0x4320));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0c00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_9, 0x18ca));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, 0x1b20));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x01bd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x000f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf147));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0005));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2f54));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0027));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x303d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9792));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0704));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fe));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0006));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0150));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb00a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0d74));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f80));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x82e0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0005));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0208));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9186));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x000e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3700));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fb0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9f81));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9688));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fd2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9fa2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0020));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x640b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9690));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2220));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8258));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2a20));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3060));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x3fa0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x825e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xe0f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1489));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f92));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1448));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffdd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0091));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb06c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1600));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fea));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0814));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd8f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0400));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fc0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8796));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00c3));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff98));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87f8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x292a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fa4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc46f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0620));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0013));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x132f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00c0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa028));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffc));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0090));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1c09));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fec));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa6a1));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1807));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffe));
#ifndef VTSS_10BASE_TE
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x028e));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa518));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x006d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc696));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0912));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0db6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0059));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x6596));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0514));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0041));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0280));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf7dd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x006d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x95d4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0049));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x2410));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
#else //using 10BASE-Te
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa499));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0075));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf759));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0914));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff7b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0eb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x85d6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8490));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0055));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x44d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8492));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0044));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa8aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8494));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0cb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8496));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff79));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8498));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0caa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0029));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x265d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd658));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b4));
#endif //using 10BASE-Te
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no,  VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001));

#if defined (MICRO_PATCH_REV_TS_FIFO_2)
    VTSS_RC(tesla_revD_8051_patch(vtss_state, port_no)); // Rev D. This is for RevD Only
#else
    VTSS_RC(tesla_revB_8051_patch(vtss_state, port_no)); // This is the OLD-Patch (Non-Middle-Man), where rev B, C, & D have the same patch.
#endif

    VTSS_RC(vtss_phy_pre_init_tesla_revB_1588(vtss_state, port_no)); //Init 1588 register using Tesla RevB micro patch

    return VTSS_RC_OK;
}

// Initialization needed for Tesla. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
static vtss_rc vtss_phy_pre_init_seq_tesla(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    if (ps->type.revision == VTSS_PHY_TESLA_REV_A) {
        VTSS_RC(vtss_phy_pre_init_seq_tesla_4_april_2011(vtss_state, port_no));
    } else if (ps->type.revision == VTSS_PHY_TESLA_REV_B) {
        VTSS_RC(vtss_phy_pre_init_seq_tesla_17_august_2011(vtss_state, port_no));
    } else if (ps->type.revision == VTSS_PHY_TESLA_REV_D) {
        VTSS_RC(vtss_phy_pre_init_seq_tesla_rev_d(vtss_state, port_no));
    } else if (ps->type.revision == VTSS_PHY_TESLA_REV_E) {
        VTSS_D("Pre_init script 'E' implemented for rev:%d ", ps->type.revision);
        VTSS_RC(vtss_phy_pre_init_seq_tesla_rev_e(vtss_state, port_no));
    } else {
        /* Note: EEE Settings for Tesla Rev.E are significantly different than previous versions */
        VTSS_I("Pre_init script not implemented for rev:%d, DEFAULTING to latest known init script: Rev E", ps->type.revision);
        VTSS_RC(vtss_phy_pre_init_seq_tesla_rev_e(vtss_state, port_no));
    }
    return VTSS_RC_OK;
}


/************************************************************************/
/* Viper family functions                                               */
/************************************************************************/

// Viper Rev. A Internal 8051 patch.
// In     : port_no - any port within the chip where to load the 8051 code.
// Return : VTSS_RC_OK if configuration done else error code.

// Download patch into PRAM for the internal 8051
static vtss_rc viper_revA_8051_patch(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val = 0;
    u16 chip_port_no = 0;
    BOOL skip_dnload = FALSE;

    const u8 patch_arr[] = {
        0xe9, 0x78, 0x02, 0xe8, 0xe4, 0x02, 0xe9, 0x6c, 0x02, 0xe9,
        0x7b, 0x02, 0xe9, 0x7c, 0x02, 0xe9, 0x7d, 0xe4, 0xf5, 0x11,
        0x12, 0xe9, 0x65, 0x20, 0xe7, 0x1e, 0x7b, 0xfe, 0x12, 0xe8,
        0xce, 0xef, 0xc4, 0x33, 0x33, 0x54, 0xc0, 0xff, 0xc0, 0x07,
        0x7b, 0x54, 0x12, 0xe8, 0xce, 0xd0, 0xe0, 0x4f, 0xff, 0x74,
        0x16, 0x25, 0x11, 0xf8, 0xa6, 0x07, 0x12, 0xe9, 0x65, 0x20,
        0xe7, 0x03, 0x02, 0xe8, 0xc1, 0x54, 0x03, 0x64, 0x03, 0x60,
        0x62, 0x7b, 0xcb, 0x12, 0xe8, 0xd9, 0x8f, 0xfb, 0x7b, 0x20,
        0x12, 0xe8, 0xd9, 0xef, 0x4e, 0x70, 0x3c, 0x7b, 0x22, 0x7d,
        0x18, 0x7f, 0x06, 0x12, 0x3d, 0xff, 0xef, 0x64, 0x01, 0x4e,
        0x60, 0x1c, 0x7d, 0x1c, 0xe4, 0xff, 0x12, 0x3f, 0x07, 0xef,
        0x54, 0x1b, 0x64, 0x0a, 0x70, 0x16, 0x7b, 0xcc, 0x7d, 0x10,
        0xff, 0x12, 0x3d, 0xff, 0xef, 0x64, 0x01, 0x4e, 0x70, 0x08,
        0x12, 0xe9, 0x5b, 0xe4, 0xfb, 0xfa, 0x80, 0x1a, 0x12, 0xe9,
        0x5b, 0x7b, 0x01, 0x7a, 0x00, 0x80, 0x11, 0x12, 0xe9, 0x5b,
        0x12, 0xe9, 0x65, 0x54, 0x40, 0xfe, 0xc4, 0x13, 0x13, 0x54,
        0x03, 0xfb, 0x7a, 0x00, 0x7d, 0xee, 0x12, 0x39, 0x0f, 0xe5,
        0x11, 0x24, 0x17, 0xfd, 0x7b, 0xff, 0x7f, 0x04, 0x12, 0x3d,
        0xff, 0xef, 0x4e, 0x70, 0x07, 0x74, 0x16, 0x25, 0x11, 0xf8,
        0xe4, 0xf6, 0x05, 0x11, 0xe5, 0x11, 0xc3, 0x94, 0x02, 0x50,
        0x03, 0x02, 0xe8, 0x15, 0x22, 0xe5, 0x11, 0x24, 0x17, 0xfd,
        0x7f, 0x04, 0x12, 0x3d, 0xff, 0x22, 0xe5, 0x11, 0x24, 0x17,
        0xfd, 0x7f, 0x04, 0x12, 0x3d, 0xff, 0x22, 0xd2, 0x02, 0x75,
        0xfb, 0x03, 0xab, 0x70, 0xaa, 0x6f, 0x7d, 0x19, 0x7f, 0x03,
        0x12, 0x3f, 0x47, 0xe5, 0x70, 0x54, 0x0f, 0x24, 0xf3, 0x70,
        0x48, 0xe5, 0x70, 0xae, 0x6f, 0x78, 0x04, 0xce, 0xa2, 0xe7,
        0x13, 0xce, 0x13, 0xd8, 0xf8, 0xff, 0x20, 0xe2, 0x41, 0x13,
        0x92, 0x01, 0xef, 0xa2, 0xe1, 0x92, 0x00, 0x30, 0x01, 0x36,
        0xe4, 0xf5, 0x10, 0x7b, 0xfe, 0x12, 0xe9, 0x50, 0xef, 0xc4,
        0x33, 0x33, 0x54, 0xc0, 0xff, 0xc0, 0x07, 0x7b, 0x54, 0x12,
        0xe9, 0x50, 0xd0, 0xe0, 0x4f, 0xff, 0x74, 0x16, 0x25, 0x10,
        0xf8, 0xa6, 0x07, 0x05, 0x10, 0xe5, 0x10, 0xc3, 0x94, 0x02,
        0x40, 0xd9, 0x22, 0x7b, 0x01, 0x7a, 0x00, 0x7d, 0xee, 0x7f,
        0x92, 0x12, 0x39, 0x0f, 0x22, 0xe5, 0x10, 0x24, 0x17, 0xfd,
        0x7f, 0x04, 0x12, 0x3d, 0xff, 0x22, 0xe5, 0x11, 0x24, 0x17,
        0x54, 0x1f, 0x44, 0x80, 0xff, 0x22, 0x74, 0x16, 0x25, 0x11,
        0xf8, 0xe6, 0x22, 0x30, 0x01, 0x03, 0x12, 0xe8, 0x12, 0x22,
        0xc2, 0x01, 0xc2, 0x00, 0x22, 0x02, 0xe9, 0x73, 0x22, 0x22,
        0x22
    };

    // Only download 8051 Patches to Port 0 of PHY!
    // Check to see if this is PHY Port 0, If it is not, the 8051 CRC Calculation will Fail on other PHY Ports */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    chip_port_no = (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11;
    VTSS_D("reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    if (chip_port_no != 0) {
        VTSS_I("Download of micro-patch on Non-Base Port. reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    }

    // Check to see if the code has already been downloaded correctly, if so, Just return, No need to do it again */
    if (vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                        0xE800,
                                        sizeof(patch_arr) + 1 /* Add one for the byte auto-added in the download function */,
                                        0x9995, TRUE) == VTSS_RC_OK) {

        vtss_state->phy_state[port_no].micro_patch_crc = 0x9995;
        VTSS_I("Skipping download of 8051, CRC for Download correct: 0x9995");
        skip_dnload = TRUE;
    } else {
        VTSS_RC(download_8051_code(vtss_state, port_no, &patch_arr[0], sizeof(patch_arr)));
    }

    if (!vtss_state->sync_calling_private) {
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

        if (skip_dnload) {
            VTSS_I("Skip Patch Dnload: No need to Enable 8051 clk or CLEAR clear-patch present or Release SW Reset");
        } else {
            // Enable 8051 clock; CLEAR patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4018));
            // Release 8051 SW Reset
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc018));
            VTSS_I("Enable 8051 clk, CLEAR clear-patch present, Release SW Reset");
        }
    } else {
        VTSS_I("Skipping access of 8051, we can't do register value check for this part (Checked by checking CRC later)");
    }

    // Check that code is downloaded correctly.
    if (skip_dnload) {
        VTSS_I("PHY micro-patch - Already Loaded and Activated! ");
        return VTSS_RC_OK;
    } else {
        VTSS_RC(vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                                0xE800,
                                                sizeof(patch_arr) + 1, // Add one for the byte auto-added in the download function
                                                0x9995, FALSE));
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0000));        // Clear all patches
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4098));        // Enable 8051 clock; set patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc098));        // Release 8051 SW Reset
    VTSS_I("Enable 8051 clk, SET micro-patch present, Release SW Reset");
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return VTSS_RC_OK;
}


// Download patch into PRAM for the internal 8051
static vtss_rc viper_revB_8051_patch(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    u16 reg_val = 0;
    u16 chip_port_no = 0;
    BOOL skip_dnload = FALSE;

    const u8 patch_arr[] = {
        0xe8, 0x59, 0x02, 0xe8, 0x12, 0x02, 0xe8, 0x42, 0x02, 0xe8,
        0x5a, 0x02, 0xe8, 0x5b, 0x02, 0xe8, 0x5c, 0xe5, 0x69, 0x54,
        0x0f, 0x24, 0xf7, 0x60, 0x27, 0x24, 0xfc, 0x60, 0x23, 0x24,
        0x08, 0x70, 0x14, 0xe5, 0x69, 0xae, 0x68, 0x78, 0x04, 0xce,
        0xa2, 0xe7, 0x13, 0xce, 0x13, 0xd8, 0xf8, 0x7e, 0x00, 0x54,
        0x0f, 0x80, 0x00, 0x7b, 0x01, 0x7a, 0x00, 0x7d, 0xee, 0x7f,
        0x92, 0x12, 0x50, 0xee, 0x22, 0xe4, 0xf5, 0x10, 0x85, 0x10,
        0xfb, 0x7d, 0x1c, 0xe4, 0xff, 0x12, 0x59, 0xea, 0x05, 0x10,
        0xe5, 0x10, 0xc3, 0x94, 0x04, 0x40, 0xed, 0x22, 0x22, 0x22,
        0x22, 0x22
    };

    // Only download 8051 Patches to Port 0 of PHY!
    // Check to see if this is PHY Port 0, If it is not, the 8051 CRC Calculation will Fail on other PHY Ports */
    VTSS_RC(vtss_phy_page_ext(vtss_state, port_no));
    VTSS_RC(PHY_RD_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_PHY_CONTROL_4, &reg_val));
    chip_port_no = (reg_val & VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS) >> 11;
    VTSS_D("reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    if (chip_port_no != 0) {
        VTSS_I("Download of micro-patch on Non-Base Port. reg_val:0x%X, chip_port_no:%d, port_no:%u", reg_val,  chip_port_no, port_no);
    }

    // Check to see if the code has already been downloaded correctly, if so, Just return, No need to do it again */
    if (vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                        0xE800,
                                        sizeof(patch_arr) + 1 /* Add one for the byte auto-added in the download function */,
                                        0xfb48, TRUE) == VTSS_RC_OK) {
        vtss_state->phy_state[port_no].micro_patch_crc = 0xfb48;
        VTSS_I("Skipping download of 8051, CRC for Download correct: 0xFB48");
        skip_dnload = TRUE;
    } else {
        VTSS_RC(download_8051_code(vtss_state, port_no, &patch_arr[0], sizeof(patch_arr)));
    }

    if (!vtss_state->sync_calling_private) {
        VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));

        if (skip_dnload) {
            VTSS_I("Skip Patch Dnload: No need to Enable 8051 clk or CLEAR clear-patch present or Release SW Reset");
        } else {
            // Enable 8051 clock; CLEAR patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4018));
            // Release 8051 SW Reset
            VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc018));
            VTSS_I("Enable 8051 clk, CLEAR clear-patch present, Release SW Reset");
        }
    } else {
        VTSS_I("Skipping access of 8051, we can't do register value check for this part (Checked by checking CRC later)");
    }

    // Check that code is downloaded correctly.
    if (skip_dnload) {
        return VTSS_RC_OK;
    } else {
        VTSS_RC(vtss_phy_is_8051_crc_ok_private(vtss_state, port_no,
                                                0xE800,
                                                sizeof(patch_arr) + 1, // Add one for the byte auto-added in the download function
                                                0xfb48, FALSE));
    }

    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no));
    VTSS_RC(vtss_phy_micro_assert_reset(vtss_state, port_no));
    VTSS_RC(vtss_phy_page_gpio(vtss_state, port_no)); // Switch back to micro/GPIO register-page
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_12, 0x0000));        // Clear all patches
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0x4098));        // Enable 8051 clock; set patch present; disable PRAM clock override and addr. auto-incr; operate at 125 MHz
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_GPIO_0, 0xc098));        // Release 8051 SW Reset
    VTSS_I("Enable 8051 clk, SET micro-patch present, Release SW Reset");
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));

    return VTSS_RC_OK;
}


// Initialization needed for Viper. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
// Date : 06-03-2013
static vtss_rc vtss_phy_pre_init_seq_viper_rev_a(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));
    /*- The following code was added for bug 13269 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8796));
    /*- End of added code for bug 13269 */
    // Work-around solution for bugzilla#6859
    //Our solution is to force the BlindSampleTimer to 0x080 by setting
    //BlindSampleTimerForce to '1' (bit 22) and BlindSampleTimerForceVal to 0x080
    //(bits 21:13) in register 0x3d in the AutoNegDbgNode.  This increases the time
    //to wait for the link to come up before allowing the crossover state to switch
    //to ~511 ms.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));

    /* Init script updates from James Bz#22267*/
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd8f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0400));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fc0));

    /* EEE updates from James Bz#22267*/

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb002));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9686));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc46f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0620));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffdd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1448));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0013));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x132f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00c0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa028));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffc));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0091));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb06c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1600));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fea));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xfaff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f80));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0090));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1809));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fec));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffe));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0814));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));

#ifndef VTSS_10BASE_TE
#else //using 10BASE-Te
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, 17, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa499));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0075));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf759));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0914));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff7b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0eb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x85d6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8490));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0055));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x44d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8492));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0044));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa8aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8494));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0cb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8496));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff79));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8498));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0caa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0029));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x265d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd658));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b4));
#endif
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001));

    // According James new chip revision must not use the rev. A micro, even if they are using the Rev. A init settings.
    if (ps->type.revision == VTSS_PHY_VIPER_REV_A) {
        VTSS_RC(viper_revA_8051_patch(vtss_state, port_no)); //Load micro patch
    }
    return VTSS_RC_OK;
}

// Initialization needed for Viper Rev B Silicon.
// Note: For whole chip and must be done before init. of the individual ports
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
// Date : 07-08-2015
static vtss_rc vtss_phy_pre_init_seq_viper_rev_b(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_BYPASS_CONTROL, 0x0008, 0x0008));
    VTSS_RC(vtss_phy_page_ext3(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER, 0x2000));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, 0x1f20));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0xafa4)); 
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0019, 0x007f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fa4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9f81));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9688));

    /* Init script updates from James Bz#22267*/
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd8f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0400));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fc0));

    /* EEE updates from James Bz#22267*/

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb002));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9686));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc46f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0620));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffdd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1448));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0013));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x132f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00c0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa028));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffc));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0091));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb06c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1600));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fea));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xfaff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f80));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0090));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1809));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fec));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffe));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0814));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));

#ifndef VTSS_10BASE_TE
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_CU_PMD_TX_CTRL, 0x028e));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa518));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x006d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc696));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0912));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
#else //using 10BASE-Te
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EEE_CONTROL, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa499));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0075));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf759));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0914));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff7b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0eb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x85d6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8490));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0055));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x44d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8492));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0044));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa8aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8494));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0cb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8496));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff79));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8498));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0caa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0029));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x265d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd658));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b4));
#endif //using 10BASE-Te
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001));

    // NOTE: Viper Rev B. does not have a micro patch at the moment
    // According James new chip revision must not use the rev. A micro, even if they are using the Rev. A init settings.
    if (ps->type.revision == VTSS_PHY_VIPER_REV_B) {
        VTSS_RC(viper_revB_8051_patch(vtss_state, port_no)); //Load micro patch
    }


    return VTSS_RC_OK;
}


// Initialization needed for Viper. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
static vtss_rc vtss_phy_pre_init_seq_viper(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    if (ps->type.revision == VTSS_PHY_VIPER_REV_A) {
        VTSS_RC(vtss_phy_pre_init_seq_viper_rev_a(vtss_state, port_no));
    } else if (ps->type.revision == VTSS_PHY_VIPER_REV_B) {
        VTSS_RC(vtss_phy_pre_init_seq_viper_rev_b(vtss_state, port_no));
    } else {
        VTSS_I("Pre_init script not implemented for rev:%d, defaulting to latest known init script", ps->type.revision);
        VTSS_RC(vtss_phy_pre_init_seq_viper_rev_b(vtss_state, port_no));
    }
#if defined(VTSS_OPT_PHY_TIMESTAMP)
    /* Set the padding for SPI access (done initially for each phy) */
    if (vtss_state->init_conf.spi_read_write != NULL ||
        vtss_state->init_conf.spi_32bit_read_write != NULL) {
        u32 padng_setngs = (0x10 | (MAX_CFG_PADDING_BYTES & 0x0007));
        if (vtss_state->init_conf.spi_32bit_read_write != NULL) {
            VTSS_RC(vtss_state->init_conf.spi_32bit_read_write(vtss_state, port_no, FALSE, 0x40, 0x0, &padng_setngs));
        } else {
            VTSS_RC(vtss_phy_1g_spi_read_write(vtss_state, port_no, 0, FALSE, 0x40, 0x0, &padng_setngs));
        }
    }
#endif

    return VTSS_RC_OK;
}

/************************************************************************/
/* ELISE family functions                                               */
/************************************************************************/
// Initialization needed for ELISE. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
static vtss_rc vtss_phy_pre_init_seq_elise_rev_a(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));
    /*- The following code was added for bug 13269 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8796));
    // Work-around solution for bugzilla#6859
    //Our solution is to force the BlindSampleTimer to 0x080 by setting
    //BlindSampleTimerForce to '1' (bit 22) and BlindSampleTimerForceVal to 0x080
    //(bits 21:13) in register 0x3d in the AutoNegDbgNode.  This increases the time
    //to wait for the link to come up before allowing the crossover state to switch
    //to ~511 ms.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));

    /* EEE updates from James Bz#22266*/

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb002));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9686));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc46f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0620));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffdd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1448));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0013));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x132f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00c0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa028));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffc));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0091));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb06c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1600));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fea));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xfaff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f80));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0090));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1809));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fec));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffe));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0814));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));

#ifndef VTSS_10BASE_TE
#else //using 10BASE-Te
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, 17, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa499));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0075));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf759));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0914));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff7b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0eb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x85d6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8490));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0055));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x44d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8492));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0044));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa8aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8494));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0cb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8496));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff79));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8498));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0caa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0029));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x265d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd658));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b4));
#endif
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000));
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001));

    return VTSS_RC_OK;
}

// Initialization needed for Elise. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
static vtss_rc vtss_phy_pre_init_seq_elise(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    if (ps->type.revision == VTSS_PHY_ELISE_REV_A) {
        VTSS_RC(vtss_phy_pre_init_seq_elise_rev_a(vtss_state, port_no));
    } else {
        VTSS_I("Pre_init script not implemented for rev:%d, defaulting to latest known init script", ps->type.revision);
        VTSS_RC(vtss_phy_pre_init_seq_elise_rev_a(vtss_state, port_no));
    }
    return VTSS_RC_OK;
}

/************************************************************************/
/* NANO family functions                                                */
/************************************************************************/
// Initialization needed for NANO. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
static vtss_rc vtss_phy_pre_init_seq_nano_rev_a(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001)); // Reg 22, Turn on Broadcast Writes
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0000, 0x0400));  // UNH 1.8.1 Clear bias bit for UNH 1000BT Distortion
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, 0x0c00, 0x0e00));   // UNH 1.8.7 Optimize pre-emphasis for 100BaseTx UNH 100BW fix
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));   // Enable Token-Ring during Coma Mode
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));
    /*- The following code was added for bug 13269 */
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8796));
    // Work-around solution for bugzilla#6859
    //Our solution is to force the BlindSampleTimer to 0x080 by setting
    //BlindSampleTimerForce to '1' (bit 22) and BlindSampleTimerForceVal to 0x080
    //(bits 21:13) in register 0x3d in the AutoNegDbgNode.  This increases the time
    //to wait for the link to come up before allowing the crossover state to switch
    //to ~511 ms.
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));

    /* EEE updates from James Bz#22266*/

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0012));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb002));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f82));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9686));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc46f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x968c));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0620));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x97a2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xffdd));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1448));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a6));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0013));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x132f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a4));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96a8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00c0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa028));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffc));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0091));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xb06c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe8));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1600));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fea));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xfaff));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f80));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0090));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1809));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fec));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x1007));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8ffe));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00ee));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff00));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b0));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x7000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b2));

    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0814));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x96b4));


#ifndef VTSS_10BASE_TE
#else //using 10BASE-Te
    VTSS_RC(vtss_phy_page_ext2(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, 17, 0x8000, 0x8000));
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa499));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0075));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xf759));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0914));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff7b));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0eb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x85d6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8490));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0055));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x44d2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8492));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0044));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa8aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8494));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0cb9));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8496));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00f7));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff79));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8498));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0caa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849c));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x849e));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0018));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a6));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84a8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84aa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0029));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x265d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ac));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x007d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xd658));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84ae));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b2));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0061));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8618));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x84b4));
#endif
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000)); // Disable Token-Ring during Coma Mode
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001)); // Turn off Broadcast Writes

    return VTSS_RC_OK;
}

/************************************************************************/
/* Serval_T-NANO Init Scripts                                           */
/************************************************************************/
// Additional Initialization needed for NANO in Serval_T Environment.
// This is performed for whole chip and must be done before init. of the individual ports
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
vtss_rc vtss_phy_pre_init_seq_nano_7435(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0001, 0x0001)); // Reg 22, Turn on Broadcast Writes
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_5, 0x0c00, 0x0e00));   // UNH 1.8.7 Optimize pre-emphasis for 100BaseTx UNH 100BW fix
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_24, 0x0000, 0x0600));  // UNH 1.8.1 Clear bias bit for UNH 1000BT Distortion
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x8000, 0x8000));   // Enable Token-Ring during Coma Mode
    VTSS_RC(vtss_phy_page_tr(vtss_state, port_no));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0008));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa518));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8486));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x006d));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xc696));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8488));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0912));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x848a));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x00c3));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xff98));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87f8));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0050));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x100f));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fa));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0704));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x87fe));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0003));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8796));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xa0f0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x83a4));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x9f81));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x9688));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0000));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x0400));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fc0));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0068));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0x8980));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8f90));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_18, 0x0004));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_17, 0xaf54));
    VTSS_RC(PHY_WR_PAGE(vtss_state, port_no, VTSS_PHY_PAGE_TR_16, 0x8fe4));
    VTSS_RC(vtss_phy_page_test(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_TEST_PAGE_8, 0x0000, 0x8000)); // Disable Token-Ring during Coma Mode
    VTSS_RC(vtss_phy_page_std(vtss_state, port_no));
    VTSS_RC(PHY_WR_MASKED_PAGE(vtss_state, port_no, VTSS_PHY_EXTENDED_CONTROL_AND_STATUS, 0x0000, 0x0001)); // Turn off Broadcast Writes

    return VTSS_RC_OK;
}


// Initialization needed for Nano. (For whole chip and must be done before init. of the individual ports)
//
// In : port_no : Port number (MUST be the first port for the chip)..
//
// Return : VTSS_RC_OK if configuration done else error code.
static vtss_rc vtss_phy_pre_init_seq_nano(vtss_state_t *vtss_state, vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps = &vtss_state->phy_state[port_no];

    if (ps->type.revision == VTSS_PHY_NANO_REV_A) {
        VTSS_RC(vtss_phy_pre_init_seq_nano_rev_a(vtss_state, port_no));
    } else {
        VTSS_I("Pre_init script not implemented for rev:%d, defaulting to latest known init script", ps->type.revision);
        VTSS_RC(vtss_phy_pre_init_seq_nano_rev_a(vtss_state, port_no));
    }
    return VTSS_RC_OK;
}

/************************************************************************/
/* Non family  related functions                                        */
/************************************************************************/


// Function that is called at boot, before port reset.
// The function is calling the initialization scripts.
// IN : port_no - Any port within the chip.
vtss_rc vtss_phy_pre_reset_private(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_phy_port_state_t *ps;
    vtss_rc rc = VTSS_RC_OK;

    // Make sure that you don't get out of bounds.
    if (port_no >= VTSS_PORT_ARRAY_SIZE) {
        return VTSS_RC_ERROR;
    } else {
        ps = &vtss_state->phy_state[port_no];
    }

    VTSS_D("vtss_phy_pre_reset_private enter port_no = %d", port_no);

    switch (ps->family) {
    case VTSS_PHY_FAMILY_ATOM:
        rc = vtss_phy_pre_init_seq_atom(vtss_state, port_no, FALSE);
        break;

    case VTSS_PHY_FAMILY_LUTON26:
        rc = vtss_phy_pre_init_seq_atom(vtss_state, port_no, TRUE);
        break;

    case VTSS_PHY_FAMILY_TESLA:
        rc = vtss_phy_pre_init_seq_tesla(vtss_state, port_no);
        break;

    case VTSS_PHY_FAMILY_VIPER:
        rc = vtss_phy_pre_init_seq_viper(vtss_state, port_no);
        break;

    case VTSS_PHY_FAMILY_ELISE:
        rc = vtss_phy_pre_init_seq_elise(vtss_state, port_no);
        break;

    case VTSS_PHY_FAMILY_NANO:
        rc = vtss_phy_pre_init_seq_nano(vtss_state, port_no);
        /* In Addition to the Normal NANO Init Scripts, For Serval_T, need more Init Script updates */
        if (rc == VTSS_RC_OK) {
            if (ps->type.part_number == VTSS_PHY_TYPE_7435) {   /* Serval_T */
                rc = vtss_phy_pre_init_seq_nano_7435(vtss_state, port_no);
            }
        }

        break;

    default:
        VTSS_D("No pre-initialising needed for family:%s",
               vtss_phy_family2txt(ps->family));
    }
    return rc;
}


#endif

