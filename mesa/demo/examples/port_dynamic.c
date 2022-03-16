// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "microchip/ethernet/switch/api.h"

const char *dynamic_help_txt = "\
This is a port_dynamic test.\n\
\n\
There are two required parameters, 'port_to_change' and 'interface'.\n\
'port_to_change' should be the port within the serdes that can run at 5G or 10G (MESA_INTERFACE_MODE_SFI).\n\
'interface' can be '0' = MESA_INTERFACE_MODE_SFI or '1' = MESA_INTERFACE_MODE_QSGMII.\n\
'The test will change a port to the wanted interface mode and verify the API configuration.\n\
";


static int dynamic_phy_setup(meba_inst_t meba_inst, mesa_port_no_t port_no)
{
    mepa_reset_param_t    phy_reset = {};
    mepa_conf_t           phy_conf = {};
    mesa_rc               rc;

    // Re-install the new phys with:
    // 1. Pre reset
    // 2. Normal reset
    // 3. Phy setup (to default)

    // Pre reset PHY
    meba_inst->api.meba_reset(meba_inst, MEBA_PHY_INITIALIZE);
    phy_reset.reset_point = MEPA_RESET_POINT_PRE;
    phy_reset.media_intf = MESA_PHY_MEDIA_IF_CU;
    rc = (meba_phy_reset(meba_inst, port_no, &phy_reset));
    if (rc == MESA_RC_NOT_IMPLEMENTED || rc == MESA_RC_ERR_PHY_BASE_NO_NOT_FOUND || rc == MESA_RC_OK) {
        // We don't care if its not implemented (third party) or if its not the base port (only one of them is)
    } else {
        cli_printf("meba_pre_phy_reset(%u) failed: %d", port_no, rc);
        return -1;
    }

    // Normal reset PHY
    phy_reset.reset_point = MEPA_RESET_POINT_DEFAULT;
    rc = (meba_phy_reset(meba_inst, port_no, &phy_reset));
    if (rc == MESA_RC_NOT_IMPLEMENTED || rc == MESA_RC_OK) {
        // We don't care if its not implemented (third party)
    } else {
        cli_printf("meba_phy_reset(%u) failed: %d", port_no, rc);
        return -1;
    }

    // Setup PHY to default
    phy_conf.speed = MESA_SPEED_AUTO;
    phy_conf.admin.enable = TRUE;
    if (meba_phy_conf_set(meba_inst, port_no, &phy_conf) != MESA_RC_OK) {
        cli_printf("meba_phy_conf_set(%u) failed", port_no);
        return -1;
    }
    return 0;
}

static int port_dynamic_init(int argc, const char *argv[])
{
    uint32_t port_to_change = ARGV_INT("port_to_change", "Apply config from this port");
    uint32_t interface = ARGV_INT("interface", "Apply this interface. 0 = SFI, 1 = QSGMII");
    uint32_t port_max_cnt = mesa_port_cnt(NULL), dyna_group_set, port_no;
    meba_port_entry_t   entry;
    meba_inst_t meba_inst = mesa_example_meba_inst();
    mesa_port_map_t map[port_max_cnt];
    uint32_t port_cnt = MEBA_WRAP(meba_capability, meba_inst, MEBA_CAP_BOARD_PORT_COUNT);
    mesa_port_conf_t conf;
    mesa_port_interface_t if_type;
    mepa_phy_info_t phy_id;

    if (interface == 0) {
        if_type = MESA_PORT_INTERFACE_SFI;
    } else if (interface == 1) {
        if_type = MESA_PORT_INTERFACE_QSGMII;
    } else {
        cli_printf("Interface type unsupported\n");
        return -1;
    }

    EXAMPLE_BARRIER(argc);

    // Get the ports capability, but for test reason do not break the test if the capabilities are not found
    meba_inst->api.meba_port_entry_get(meba_inst, port_to_change, &entry);

    if (!(entry.cap & MEBA_PORT_CAP_DYNAMIC)) {
        // Notify but do not stop test
        cli_printf("MEBA_PORT_CAP_DYNAMIC not set - Cap. should be set in MEBA\n");
    }
    if (!(entry.cap & MEBA_PORT_CAP_5G_FDX)) {
        // Notify but do not stop test
        cli_printf("Port does not support 5G/10G - Cap. should be set in MEBA\n");
    }

    // Note the 4 port group (QSGMII/QXGMII) the main port belongs to
    dyna_group_set = entry.map.chip_port / 4;

    // Change the port interface type to SFI or QSGMII
    RC(mesa_port_conf_get(NULL, port_to_change, &conf));
    conf.if_type = if_type;
    if (if_type == MESA_PORT_INTERFACE_SFI) {
        conf.speed = (entry.cap & MEBA_PORT_CAP_10G_FDX) ? MESA_SPEED_10G : MESA_SPEED_5G;
    } else {
        conf.speed = MESA_SPEED_1G;
    }
    RC(mesa_port_conf_set(NULL, port_to_change, &conf));

    //
    // Now the API is configured to the new interface type incl. switch core BW
    //

    // Now remove/attach phys on all 4 ports and verify that the API is configured as expected
    RC(mesa_port_map_get(NULL, port_cnt, map));

    for (port_no = 0; port_no < port_cnt; port_no++) {
        meba_inst->api.meba_port_entry_get(meba_inst, port_no, &entry);

        // Only handle the 4 port group from above
        if (dyna_group_set != entry.map.chip_port / 4) {
            continue;
        }

        RC(mesa_port_conf_get(NULL, port_no, &conf));

        if (if_type == MESA_PORT_INTERFACE_SFI) {
            if (port_no == port_to_change) {
                if (map[port_no].max_bw != MESA_BW_5G) {
                    cli_printf("Error: port:%d wrong BW", port_no);
                    return -1;
                }
            } else {
                if (map[port_no].max_bw != MESA_BW_NONE && conf.if_type != MESA_PORT_INTERFACE_NO_CONNECTION) {
                    cli_printf("Error: port:%d wrong BW and/or if_type", port_to_change);
                    return -1;
                }
            }

            // The phys are leaving, delete them from the system
            if (meba_phy_delete(meba_inst, port_no) != MESA_RC_OK) {
                cli_printf("Error: Could not delete phy instance %d\n",port_no);
                return -1;
            }
            if ((meba_phy_info_get(meba_inst, port_no, &phy_id)) == MESA_RC_OK) {
                cli_printf("Error: Phy should be deleted %d\n",port_no);
                return -1;
            } else {
                cli_printf("Phy for port %d is deleted as expected\n",port_no);
            }
        } else { // QSGMII
            // Phys are re-appearing and need to be reset and configured
            RC(dynamic_phy_setup(meba_inst, port_no));

            // Configure the port interface to QSGMII
            conf.if_type = MESA_PORT_INTERFACE_QSGMII;
            conf.speed = MESA_SPEED_1G;
            RC(mesa_port_conf_set(NULL, port_no, &conf));
            RC(mesa_port_conf_get(NULL, port_no, &conf));

            // Verify the config
            if (map[port_no].max_bw != MESA_BW_1G && conf.if_type != MESA_PORT_INTERFACE_QSGMII) {
                cli_printf("Error: port:%d wrong BW and/or if_type", port_no);
                return -1;
            } else {
                cli_printf("Port:%d BW and Interface matches expected\n",port_no);
            }
        }
    }
    return 0;
}

static int port_dynamic_clean()
{
    return 0;
}

static const char* port_dynamic_help()
{
    return dynamic_help_txt;
}

EXAMPLE(port_dynamic, port_dynamic_init, NULL, port_dynamic_clean, port_dynamic_help);
