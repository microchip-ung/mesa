// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// Avoid "vtss_api.h not used in module vtss_10g_phy_api.c"
/*lint --e{766} */
#include "vtss_phy_api.h"
#if defined(VTSS_CHIP_10G_PHY)
#include "../common/vtss_phy_common.h"


vtss_rc vtss_phy_10g_csr_read(const vtss_inst_t           inst,
                              const vtss_port_no_t        port_no,
                              const u32                   dev,
                              const u32                   addr,
                              u32                         *const value)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU) {
            rc = VTSS_FUNC_COLD(cil.malibu_phy_10g_csr_read, port_no, dev, addr, value);
        } else if (vtss_state->phy_10g_state[port_no].family != VTSS_PHY_FAMILY_10G_NONE) {
            rc = VTSS_FUNC_COLD(cil.phy_10g_csr_read, port_no, dev, addr, value);
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_phy_10g_csr_write(const vtss_inst_t           inst,
                               const vtss_port_no_t        port_no,
                               const u32                   dev,
                               const u32                   addr,
                               const u32                   value)
{
    vtss_state_t *vtss_state;
    vtss_rc rc = VTSS_RC_ERROR;
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        if (vtss_state->phy_10g_state[port_no].family == VTSS_PHY_FAMILY_MALIBU) {
            rc = VTSS_FUNC_COLD(cil.malibu_phy_10g_csr_write, port_no, dev, addr, value);
        } else if (vtss_state->phy_10g_state[port_no].family != VTSS_PHY_FAMILY_10G_NONE) {
            rc = VTSS_FUNC_COLD(cil.phy_10g_csr_write, port_no, dev, addr, value);
        }
    }
    VTSS_EXIT();
    return rc;
}


#endif /* VTSS_CHIP_10G_PHY */
