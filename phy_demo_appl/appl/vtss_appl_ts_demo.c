// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include "vtss_api.h"   // For board initialization
#include "vtss_appl.h"  // For vtss_board_t
#include "vtss_port_api.h"

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
extern FILE   *fp;
#endif

#ifdef VTSS_FEATURE_PHY_TIMESTAMP
#include "vtss_phy_ts_api.h"
#include "vtss_appl_ts_demo.h"


#define EVAL_BOARD_1588_CAPABLE

#endif

// Assuming that if this one is not defined, the others are not defined either
// byte order is handled by the API
#ifndef ETHERTYPE_IEEE_802_1_AE
#define ETHERTYPE_IEEE_IPV4       0x0800
#define ETHERTYPE_IEEE_ARP        0x0806
#define ETHERTYPE_IEEE_WOL        0x0842
#define ETHERTYPE_IEEE_VLAN_TAG   0x8100
#define ETHERTYPE_IEEE_IPV6       0x86DD
#define ETHERTYPE_IEEE_MPLS_UNI   0x8847
#define ETHERTYPE_IEEE_MPLS_MULTI 0x8848
#define ETHERTYPE_IEEE_JUMBO      0x8870
#define ETHERTYPE_IEEE_802_1_AG   0x8902
#define ETHERTYPE_IEEE_802_1_X    0x888E
#define ETHERTYPE_IEEE_802_1_AE   0x88E5
#define ETHERTYPE_IEEE_802_1_AH   0x88E7
#define ETHERTYPE_IEEE_PTP_1588   0x88F7
#define ETHERTYPE_IEEE_802_1_AD   0x88A8
#endif


#ifdef EVAL_BOARD_1588_CAPABLE

/* ********************************************************** */
/* *** Example of init of SPI for Timestamp Push Out  ******* */
/* ********************************************************** */

static vtss_rc vtss_1588_init_for_spi (const vtss_inst_t inst,  const vtss_port_no_t port_no)
{
    vtss_phy_ts_init_conf_t conf;
    vtss_rc rc;

    do {
        /* reference clock frequency */
        conf.clk_freq     = VTSS_PHY_TS_CLOCK_FREQ_15625M;
        /* Clock Source */
        conf.clk_src      = VTSS_PHY_TS_CLOCK_SRC_EXTERNAL;
        /* 10byte Full Tx timestamp */
        conf.tx_ts_len    = VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE;
        /*  Timestamps to pushed out on the SPI interface */
        conf.tx_fifo_mode = VTSS_PHY_TS_FIFO_MODE_SPI;
        /*  Rx timestamp in PTP reserved bytes */
        conf.rx_ts_pos    = VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP;
        /*  Rx timestamp update nano seconds part */
        conf.rx_ts_len    = VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT;
        /* TC operating mode is Mode C */
        conf.tc_op_mode   = VTSS_PHY_TS_TC_OP_MODE_A;

        rc = vtss_phy_ts_init(inst, port_no, &conf);
        if (rc == VTSS_RC_OK) {
            printf("PHY TS Init Success  \n");
        } else {
            printf("PHY TS Init Failed  \n");
            break;
        }

        rc = vtss_phy_ts_mode_set (inst, port_no, TRUE);
        if (rc != VTSS_RC_OK) {
            printf("PHY TS Block Enable Failed \n");
            break;
        }
    } while (0);

    return rc;
}


/* ********************************************************** */
/* *************     MULTIPLE ENCAPS - PTP TIME STAMP ******* */
/* ********************************************************** */
/* Vtss Sample Application for BC
  --->P1-->S1  --->  S2-->P1  (P:Port S: Switch)

If we pass same ing_port_no and egr_port_no to this application that port
will be configured for both ing and egr functionalities of BC App,
and needs be called on both switches.
Application: Ordinary/Boundary clock, 1 step
Delay method: End-to-End delay measurement method
*/
/* ETH-PTP Encapsulation */
static vtss_rc vtss_1588_sample_flows_ep(const vtss_inst_t inst,
                                         const vtss_port_no_t ing_port_no,
                                         const vtss_port_no_t egr_port_no,
	                                 const vtss_phy_ts_engine_t eng_id,
                                         int   numflows,
                                         u8    in_flow,
                                         BOOL  resv_oos_flow7)

{
    vtss_rc                         rc = VTSS_RC_ERROR;
    u8                              flow_id = 0;
    u8                              addr_match_mode = 0;
    u16                             value=0;
    char                            value_str[20] = {0};
    unsigned char                   vlan_n=0;
    unsigned char                   vlan_check = FALSE;
    vtss_phy_ts_engine_flow_conf_t *flow_conf;

    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */

        do {
            printf ("addr_match_mode: (0=ETH_ADDR_MATCH_ANY_MULTICAST-ANY_UNICAST / 1=ETH_ADDR_MATCH_48BIT):");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            value = strtol(value_str, NULL, 10);
            if (value) {
                printf ("addr_match_mode::ETH_ADDR_MATCH_ANY-MULTICAST-ANY-UNICAST Selected!!\n ");
                addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST | VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST;
                break;
            } else {
                printf ("addr_match_mode::ETH_ADDR_MATCH_48BIT Selected!!\n ");
                addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                break;
            }
        } while (!(value > 1 ));

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/PTP \n",
                          ing_port_no, eng_id, in_flow, numflows);
        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Number of Vlans (0 / 1 / 2 / Any # above 2 = NO_VLAN):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                vlan_n = strtol(value_str, NULL, 10);
                if (vlan_n == 0 ) {
                        printf ("Number VLANs :%d        Selected!!  vlan_check = TRUE but NO VLAN ID!\n ", vlan_n);
                        vlan_check = TRUE;
                        break;
                } else if ((vlan_n <= 2 ) && (vlan_n > 0)) {
                        printf ("Number VLANs : %d       Selected!!  vlan_check = TRUE    VLAN_VALUE = %d \n ", vlan_n, 1);
                        vlan_check = TRUE;
                        break;
                } else {
                        printf ("INVALID OPTION Selected: %d!! Options are: 0/1/2 -  Setting vlan_check = FALSE\n", vlan_n);
                        vlan_check = FALSE;
                        break;
                }

        } while (!(vlan_n > 2 ));


	do {
                /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                /* This is an Auto-configuration of flows based upon the FLOW_ID and NumFlows for DEMO Purposes ONLY */
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

#ifdef TESLA_ING_TS_ERRFIX
                    /* If OOS Patch is enabled, then we need to Reserve Flow_id=7 (Not Enable) for OOS recovery steps */
                    if (flow_id == 7) {
                        if (resv_oos_flow7) {
                            printf("PHY TS Engine %d  Disabling FLOW_7, Reserving for OOS Recovery!\n", eng_id);
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = FALSE;
                        } else {
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                        }
                    }
#endif
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;

		    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
                    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
                    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = addr_match_mode;

		    /* Notify the engine which mac address needs to be matched(dest/src/both) */
                    /* Options are: VTSS_PHY_TS_ETH_MATCH_DEST_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;

		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = vlan_check;
                    /* Config for Checking Specific VLAN Tagging  */
                    if (vlan_check) {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = vlan_n;
                        if (vlan_n == 0) {
                        } else if (vlan_n == 1) {
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 1;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        } else if (vlan_n == 2) {
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 0x88A8;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        }
                    }

		    /* Configure the MAC address of the flow, needs to be time stamped */
		    /* This is only applicable if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT */
		    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST or */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST, then mac_addr is not used i- Zero'd */
                    if (flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode == VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) {
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    } else {
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x00;
                    }

                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* if not in Multi-Cast or Uni-Cast                                          */
                    /* ************************************************************************* */

	            printf("flow_id: %d::ETHERTYPE_IEEE_PTP_1588:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
                }

                /* Set the Ethernet Type to be matched  */
		flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_PTP_1588; 	//0x8847;

                /* Set the INGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
		rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
		} else {
			 printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
			 break;
		}
	        printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/PTP\n",
                          egr_port_no, eng_id, flow_id, numflows);

                /* Set the EGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
                /* This config is Symmetric since INGRESS and EGRESS are being configured identically  */
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);

}

/* ETH-OAM Encapsulation */
static vtss_rc vtss_1588_sample_flows_eoam(const vtss_inst_t inst,
                                           const vtss_port_no_t ing_port_no,
                                           const vtss_port_no_t egr_port_no,
                                           const vtss_phy_ts_engine_t eng_id,
                                           int   numflows,
                                           u8    in_flow)
{
    vtss_rc                         rc = VTSS_RC_ERROR;
    u8                              addr_match_mode = 0;
    u8                              flow_id = 0;
    u16                             value=0;
    char                            value_str[20] = {0};
    vtss_phy_ts_engine_flow_conf_t *flow_conf;

   /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */

        do {
            printf ("addr_match_mode: (0=ETH_ADDR_MATCH_ANY_MULTICAST-ANY_UNICAST / 1=ETH_ADDR_MATCH_48BIT):");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            value = strtol(value_str, NULL, 10);
            if (value) {
                printf ("addr_match_mode::ETH_ADDR_MATCH_ANY-MULTICAST-ANY-UNICAST Selected!!\n ");
                addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST | VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST;
                break;
            } else {
                printf ("addr_match_mode::ETH_ADDR_MATCH_48BIT Selected!!\n ");
                addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                break;
            }
        } while (!(value > 1 ));

        if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
                printf("Engine flow_conf memory allocation Failed!\n");
                return -1;
        }
        memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/OAM \n",
                          ing_port_no, eng_id, in_flow, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
               /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
                rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
                        break;
                }

                /* engine enable */
                flow_conf->eng_mode = TRUE;
                /* This is an Auto-configuration of flows based upon the FLOW_ID and NumFlows for DEMO Purposes ONLY */
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
                    /* Map each flow to the channel which already mapped to the port */
                    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
                    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
                    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = addr_match_mode;
                    /* Notify the engine which mac address needs to be matched(dest/src/both) */
                    /* Options are: VTSS_PHY_TS_ETH_MATCH_DEST_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
                    /* Configure the MAC address of the flow, needs to be time stamped */
                    /* This is only applicable if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST or */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST, then mac_addr is not used i- Zero'd */
                    if (flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode == VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    } else {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x00;
                    }

                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* ************************************************************************* */
                    printf("flow_id: %d::ETHERTYPE_IEEE_PTP_1588:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
                }

                /* Set the Ethernet Type to be matched  */
                flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AG;      //0x8902
                /* Set the INGRESS Engine Config - for ETH-OAM, all other comparitors are skipped  */
                rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                         printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
                } else {
                         printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
                         break;
                }
                printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/OAM\n",
                          egr_port_no, eng_id, flow_id, numflows);

                /* Set the EGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
                /* This config is Symmetric since INGRESS and EGRESS are being configured identically  */
                rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

}


/* ETH-IP-PTP Encapsulation */
/* This is Really ETH-IP-UDP-PTP Encapsulation and you can select IPv4 or IPv6 */
static vtss_rc vtss_1588_sample_flows_eip(const vtss_inst_t inst,
                                          const vtss_port_no_t ing_port_no,
                                          const vtss_port_no_t egr_port_no,
	                                  const vtss_phy_ts_engine_t eng_id,
                                          int   numflows,
                                          const u8 in_flow,
                                          BOOL  resv_oos_flow7)


{
    vtss_rc                         rc = VTSS_RC_ERROR;
    u8                              flow_id = 0;
    u8                              addr_match_mode = 0;
    u16                             value=0;
    char                            value_str[20] = {0};
    unsigned char                   vlan_n=0;
    unsigned char                   vlan_check = FALSE;
    unsigned char                   ipver=0;
    vtss_phy_ts_engine_flow_conf_t *flow_conf;

   /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */

        do {
            printf ("addr_match_mode: (0=ETH_ADDR_MATCH_ANY_MULTICAST-ANY_UNICAST / 1=ETH_ADDR_MATCH_48BIT):");
            memset (&value_str[0], 0, sizeof(value_str));
            scanf("%s", &value_str[0]);
            if (value_str[0] == '0' ) {
                printf ("addr_match_mode::ETH_ADDR_MATCH_ANY-MULTICAST-ANY-UNICAST Selected!!\n ");
                addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST | VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST;
                break;
            } else if (value_str[0] == '1' ) {
                printf ("addr_match_mode::ETH_ADDR_MATCH_48BIT Selected!!\n ");
                addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                break;
            } else {
                printf ("addr_match_mode::INVALID Selection!!\n ");
            }
        } while (1);


	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

	do {
		printf ("Number of Vlans (0 / 1 / 2 / Any # above 2 = NO_VLAN):");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);
		vlan_n = strtol(value_str, NULL, 10);
		if (vlan_n == 0 ) {
			printf ("Number VLANs :%d        Selected!!  vlan_check = TRUE but NO VLAN ID!\n ", vlan_n);
                        vlan_check = TRUE;
                        break;
		} else if ((vlan_n <= 2 ) && (vlan_n > 0)) {
			printf ("Number VLANs : %d	 Selected!!  vlan_check = TRUE    VLAN_VALUE = %d \n ", vlan_n, vlan_n);
                        vlan_check = TRUE;
                        break;
		} else {
			printf ("INVALID OPTION Selected: %d!! Options are: 0/1/2 -  Setting vlan_check = FALSE\n", vlan_n);
                        vlan_check = FALSE;
                        break;
		}

        } while (!(vlan_n > 2 ));

	do {

		printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);
		ipver = strtol(value_str, NULL, 10);
		if ((ipver == 0) || (ipver == 1)) {
			printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
		} else {
			printf ("INVALID OPTION Selected!!	Options are: 0/1\n");
		}

	} while (!((ipver == 0) || (ipver == 1)));

	do {
                /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;

               /* This is an Auto-configuration of flows based upon the FLOW_ID and NumFlows for DEMO Purposes ONLY */
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
#ifdef TESLA_ING_TS_ERRFIX
                    /* If OOS Patch is enabled, then we need to Reserve Flow_id=7 (Not Enable) for OOS recovery steps */
                    if (flow_id == 7) {
                        if (resv_oos_flow7) {
                            printf("PHY TS Engine %d  Disabling FLOW_7, Reserving for OOS Recovery!\n", eng_id);
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = FALSE;
                        } else {
                            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                        }
                    }
#endif
                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
                    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
                    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = addr_match_mode;
                    /* Notify the engine which mac address needs to be matched(dest/src/both) */
                    /* Options are: VTSS_PHY_TS_ETH_MATCH_DEST_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = vlan_check;

		    /* Config for Checking Specific VLAN Tagging  */
                    if (vlan_check) {
		        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = vlan_n;
                        if (vlan_n == 0) {
                        } else if (vlan_n == 1) {
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 1;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        } else if (vlan_n == 2) {
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.val = 0x88A8;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag.value.mask = 0xFFFF;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.val = 1;
		            flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag.value.mask = 0xFFFF;
                        }
                    }

                    /* Configure the MAC address of the flow, needs to be time stamped */
                    /* This is only applicable if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST or */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST, then mac_addr is not used i- Zero'd */
                    if (flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode == VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    } else {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x00;
                    }

                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* For Demo Purpose ONLY, Modify ip1 IP_Addr for each flow to be different */
                    /* ************************************************************************* */

                     /* ipver == 0 is IPv4;   ipver != 0 is IPv6 */
		     if(ipver == 0 ){
		         /* match 1st IPv4 address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800;
	                 /* Set IP Version to IPv4 */
	                 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* Note: To completely SKIP IPv4 Matching, set the ip_addr.ipv4.mask = 0x0 */
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;	/* 153.136.119.102	<<<< FLow_Diff */
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
			       flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
			       flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
		     } else {
		         /* match 1st IPv6 address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;	//0x86DD;
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id;

                         /* Note: To completely SKIP IPv6 Matching, set the ip_addr.ipv6.mask[0..3] = 0x0 */
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
		     }

		     /* Enable the IP flow */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		     /* match 1st IP address - Depends on SRC or DEST or BOTH Flag*/
                     /* Options are: VTSS_PHY_TS_IP_MATCH_SRC; VTSS_PHY_TS_IP_MATCH_DEST; VTSS_PHY_TS_IP_MATCH_SRC_OR_DEST */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;

	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);
                 }

		 /* Set dest port to 319 to receive PTP event messages */
		 /* If setup for Tesla OOS Recovery, EPG can only support one of the following: */
                 /* dport_val = 319; dport_mask = 0xffff; sport_val=0; sport_mask=0  */
                 /* dport_val = 319; dport_mask = 0xffff; sport_val=319; sport_mask=0xffff  */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 0x0;	/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0x0; 	  /* UDP Source Port Mask */
                 printf("Flow: %d  IP1: UDP_dport: %d; dportM:0x%04x;  UDP_Sport: %d; SportM: 0x%04x\n", flow_id,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask);

                 /* Set the INGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
	         printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);

                /* Set the EGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
                /* This config is Symmetric since INGRESS and EGRESS are being configured identically  */
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);

}

/* ETH-IP-IP-PTP Encapsulation */
/* This is Really ETH-IP-IP-UDP-PTP Encapsulation and you can select IPv4 or IPv6 */
static vtss_rc vtss_1588_sample_flows_eiip(const vtss_inst_t inst,
                                           const vtss_port_no_t ing_port_no,
                                           const vtss_port_no_t egr_port_no,
		                           const vtss_phy_ts_engine_t eng_id,
                                           int   numflows,
                                           const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;
	unsigned char vlan_n=0;
        unsigned char vlan_check = FALSE;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/IP/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Number of Vlans (0 / 1 / 2):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                vlan_n = strtol(value_str, NULL, 10);
                if (vlan_n == 0 ) {
                        printf ("Number VLANs :%d        Selected!!  vlan_check = FALSE\n ", vlan_n);
                        vlan_check = FALSE;
                        break;
                } else if ((vlan_n <= 2 ) && (vlan_n > 0)) {
                        printf ("Number VLANs : %d       Selected!!  vlan_check = TRUE\n ", vlan_n);
                        vlan_check = TRUE;
                        break;
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1/2\n");
                        vlan_check = FALSE;
                        break;
                }

        } while (!(vlan_n > 2 ));

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

	} while (!((ipver == 0) || (ipver == 1)));

	do {
                /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;

                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    /* Options are: VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT if Eth_Addr to be matched, */
                    /* VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST if only matching on UNICAST bit,  */
                    /* or  VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST if MULTICAST bit is set */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src/both) */
                    /* Options are: VTSS_PHY_TS_ETH_MATCH_DEST_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_ADDR, VTSS_PHY_TS_ETH_MATCH_SRC_OR_DEST */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
                    /* Configure the MAC address of the flow, needs to be time stamped */
                    /* This is only applicable if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST or */
                    /* if flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST, then mac_addr is not used i- Zero'd */
                    if (flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode == VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT) {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    } else {
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x00;
                    }

                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		     /* Enable the IP1 flow */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
                     /* match 1st IP address - Depends on SRC or DEST or BOTH Flag*/
                     /* Options are: VTSS_PHY_TS_IP_MATCH_SRC; VTSS_PHY_TS_IP_MATCH_DEST; VTSS_PHY_TS_IP_MATCH_SRC_OR_DEST */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                     /* ipver == 0 is IPv4;   ipver != 0 is IPv6 */
                     if(ipver == 0 ){
		         /* Set IP Version to IPv4 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800;
                         /* Note: To completely SKIP IPv4 Matching, set the ip_addr.ipv4.mask = 0x0 */
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                     } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;        //0x86DD
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id;
                         /* Note: To completely SKIP IPv6 Matching, set the ip_addr.ipv6.mask[0..3] = 0x0 */
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
		     }

		     /* Enable the IP2 flow */
		     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].flow_en = TRUE;
                     /* match 2nd IP address - Depends on SRC or DEST or BOTH Flag*/
                     /* Options are: VTSS_PHY_TS_IP_MATCH_SRC; VTSS_PHY_TS_IP_MATCH_DEST; VTSS_PHY_TS_IP_MATCH_SRC_OR_DEST */
		     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                     /* ipver == 0 is IPv4;   ipver != 0 is IPv6 */
                     if(ipver == 0 ) {
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip2_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800;
                         /* Note: To completely SKIP IPv4 Matching, set the ip_addr.ipv4.mask = 0x0 */
                         flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP2: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                     } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;        //0x86DD
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id;
                         /* Note: To completely SKIP IPv6 Matching, set the ip_addr.ipv6.mask[0..3] = 0x0 */
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP2: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip2_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                     }
                 }

                 /* IP1 */
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 0;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0x0; 	  /* UDP Source Port Mask */
                 printf("Flow: %d  IP1: UDP_dport: %d; dportM:0x%04x;  UDP_Sport: %d; SportM: 0x%04x\n", flow_id,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask);

                 /* IP2 */
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.sport_val = 0;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip2_opt.comm_opt.sport_mask = 0x0; 	/* UDP Source Port Mask */
                 printf("Flow: %d  IP2: UDP_dport: %d; dportM:0x%04x;  UDP_Sport: %d; SportM: 0x%04x\n", flow_id,
                     flow_conf->flow_conf.ptp.ip2_opt.comm_opt.dport_val,
                     flow_conf->flow_conf.ptp.ip2_opt.comm_opt.dport_mask,
                     flow_conf->flow_conf.ptp.ip2_opt.comm_opt.sport_val,
                     flow_conf->flow_conf.ptp.ip2_opt.comm_opt.sport_mask);

                 /* Set the INGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
	         printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/IP/IP/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);

                /* Set the EGRESS Engine Config - for ETH-PTP, all other comparitors are skipped  */
                /* This config is Symmetric since INGRESS and EGRESS are being configured identically  */
		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);
}

/* ETH-ETH-PTP Encapsulation */
static vtss_rc vtss_1588_sample_flows_eep(const vtss_inst_t inst,
                                          const vtss_port_no_t ing_port_no,
                                          const vtss_port_no_t egr_port_no,
		                          const vtss_phy_ts_engine_t eng_id,
                                          int   numflows,
                                          const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8 flow_id = 0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

	do {
		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
                }

                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		    /* Enable the MAC flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		     /* Notify the engine which mac address needs to be matched(dest/src) */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		     /* Notify the engine if it is VLAN flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		     /* Configure the MAC address of the flow, needs to be time stamped */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);
                }

		flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AD;	//0x88A8;
		flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_PTP_1588; 	//0x0800;

		rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
		    printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
		    printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
		    break;
		}
                printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);

		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);
}

/* ETH-ETH-IP-PTP Encapsulation */
static vtss_rc vtss_1588_sample_flows_eeip(const vtss_inst_t inst,
                                           const vtss_port_no_t ing_port_no,
                                           const vtss_port_no_t egr_port_no,
	                                   const vtss_phy_ts_engine_t eng_id,
                                           int   numflows,
                                           const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

	printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/IP/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

        } while (!((ipver == 0) || (ipver == 1)));

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		     flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AD;	//0x88A8;
		     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4; 		//0x0800;

		    /* Enable the ETH-2 flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		     /* Notify the engine which mac address needs to be matched(dest/src) */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		     /* Notify the engine if it is VLAN flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		     /* Configure the MAC address of the flow, needs to be time stamped */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */

	             printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);

		     /* Enable the IP flow */
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;

		     /* match 1st IP address - Depends on SRC or DEST Flag*/
		     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                     if(ipver == 0 ){
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                     } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;        //0x86DD
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id;

			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                     }
                 }
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 0;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0x0; 	  /* UDP Source Port Mask */

                 printf("Flow: %d  IP1: UDP_dport: %d; dportM:0x%04x;  UDP_Sport: %d; SportM: 0x%04x\n", flow_id,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask);

		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
	        printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/ETH/IP/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);

		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}
	} while (0);
}

/* ETH-MPLS-IP-PTP Encapsulation */
static vtss_rc vtss_1588_sample_flows_emip(const vtss_inst_t inst,
                                           const vtss_port_no_t ing_port_no,
                                           const vtss_port_no_t egr_port_no,
	                                   const vtss_phy_ts_engine_t eng_id,
                                           int   numflows,
                                           const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/IP/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

        } while (!((ipver == 0) || (ipver == 1)));

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	             printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		    flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI; 	//0x8847;

		    /* Enable the MPLS flow */
		    flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_END;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 0xF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower =0xF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
		    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;

		    /* Enable the IP flow */
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		    /* match 1st IP address - Depends on SRC or DEST Flag*/
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                    if(ipver == 0 ){
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                    } else {
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id;

			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                    }
                 }
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 0;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0x0; 	  /* UDP Source Port Mask */

                 printf("Flow: %d  IP1: UDP_dport: %d; dportM:0x%04x;  UDP_Sport: %d; SportM: 0x%04x\n", flow_id,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask);

		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
                printf("Engress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/IP/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);

		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);


}

/* ETH-MPLS-ETH-PTP Encapsulation */
static vtss_rc vtss_1588_sample_flows_emep(const vtss_inst_t inst,
                                           const vtss_port_no_t ing_port_no,
                                           const vtss_port_no_t egr_port_no,
	                                   const vtss_phy_ts_engine_t eng_id,
                                           int   numflows,
                                           const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		    /* Map each flow to the channel which already mapped to the port */
		    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		    /* Enable the MAC flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		    /* Notify the engine which mac address needs to be matched(dest/src) */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		    /* Notify the engine if it is VLAN flow */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		    /* Configure the MAC address of the flow, needs to be time stamped */
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	            printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

		     flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI; 	//0x8847;
		     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_PTP_1588; 	//0x0800;

		    /* Enable the MPLS flow */
		     flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_END;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 0xFFFFF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 0xF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower =0xF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
		     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
                     flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;

		    /* Enable the MAC flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		     /* Notify the engine which mac address needs to be matched(dest/src) */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		     /* Notify the engine if it is VLAN flow */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		     /* Configure the MAC address of the flow, needs to be time stamped */
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	            printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);
                 }


		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
                printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);

		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);

}

/* ETH-MPLS-ETH-IP-PTP Encapsulation */
static vtss_rc vtss_1588_sample_flows_emeip(const vtss_inst_t inst,
                                            const vtss_port_no_t ing_port_no,
                                            const vtss_port_no_t egr_port_no,
	                                    const vtss_phy_ts_engine_t eng_id,
                                            int   numflows,
                                            const u8 in_flow)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_flow_conf_t *flow_conf;
        u8   flow_id = 0;
        char value_str[20] = {0};
	unsigned char ipver=0;

	if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
		printf("Engine flow_conf memory allocation Failed!\n");
		return -1;
	}
	memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/IP/PTP \n",
                    ing_port_no, eng_id, flow_id, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                printf ("Select IP version Mode (0 = IPv4; 1 = IPv6):");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ipver = strtol(value_str, NULL, 10);
                if ((ipver == 0) || (ipver == 1)) {
                        printf ("IP Version : %d  : %s   Selected!!\n ", ipver, (ipver == 1 ? "IPv6" : "IPv4"));
                } else {
                        printf ("INVALID OPTION Selected!!      Options are: 0/1\n");
                }

        } while (!((ipver == 0) || (ipver == 1)));

	do {

		rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
			break;
		}

		/* engine enable */
		flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
		   /* Map each flow to the channel which already mapped to the port */
		   flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		   /* Enable the MAC flow */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		   /* Notify the engine which mac address needs to be matched(dest/src) */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		   /* Notify the engine if it is VLAN flow */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
		   /* Configure the MAC address of the flow, needs to be time stamped */
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	           printf("flow_id: %d::ETH1 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);


		   flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI; 	//0x8847;
		   /* Enable the IP flow */

		   /* Enable the MPLS flow */
		   flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_END;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 0xF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower =0xF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
		   flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;

		   /* Enable the MAC flow */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
		   /* Notify the engine which mac address needs to be matched(dest/src) */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
		   /* Notify the engine if it is VLAN flow */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
		   /* Configure the MAC address of the flow, needs to be time stamped */
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
		   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
	           printf("flow_id: %d::ETH2 MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
		     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);

		    /* Enable the IP1 flow */
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].flow_en = TRUE;
		    /* match 1st IP address - Depends on SRC or DEST Flag*/
		    flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].match_mode = VTSS_PHY_TS_IP_MATCH_DEST;
                    if(ipver == 0 ){
                         /* match 1st IP address - Depends on SRC or DEST Flag*/
                         flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV4;    //0x0800;
                         /* Set IP Version to IPv4 */
                         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_4;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask = 0xffffffff;
                         flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr = 0x0a0a0a0a+flow_id;     /* 153.136.119.102      <<<< FLow_Diff */
                         printf("flow_id: %d::ETHERTYPE_IEEE_IPV4:: IP1: 0x%08x  Mask:0x%08x\n", flow_id,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.addr,
                               flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv4.mask);
                    } else {
                         flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_IPV6;    //0x0800;
		         /* Set IP Version to IPv6 */
		         flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode = VTSS_PHY_TS_IP_VER_6;
		         /* match 1st IP address - Depends on SRC or DEST Flag*/
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3] = 0xA000000A;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2] = 0xB000000B;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1] = 0xC000000C;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0] = 0x1+flow_id;

			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1] = 0xFFFFFFFF;
			 flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0] = 0xFFFFFFFF;

	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: IP1: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.addr[0]);
	                 printf("flow_id: %d::ETHERTYPE_IEEE_IPV6:: MSK: 0x%08x:%08x:%08x:%08x\n", flow_id,
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[3],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[2],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[1],
			     flow_conf->flow_conf.ptp.ip1_opt.flow_opt[flow_id].ip_addr.ipv6.mask[0]);
                    }
                 }
		 /* Set dest port to 319 to receive PTP event messages */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val = 319; 	 /* UDP Dest Port 319/320 */
		 /* Set dest port mask 0 means any port 0xFFFF means exact match to given port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask = 0xffff;  /* UDP Dest Port Mask	*/
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val = 0;		/* UDP Source Port */
		 flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask = 0x0; 	  /* UDP Source Port Mask */

                 printf("Flow: %d  IP1: UDP_dport: %d; dportM:0x%04x;  UDP_Sport: %d; SportM: 0x%04x\n", flow_id,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.dport_mask,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_val,
                     flow_conf->flow_conf.ptp.ip1_opt.comm_opt.sport_mask);

		 rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
		 if (rc == VTSS_RC_OK) {
			 printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		 } else {
			 printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			 break;
		 }
                printf("Egress:: Port:%d : Engine#%d Flow_id:%d, numFlows:%d :: Encapsulation: ETH/MPLS/ETH/IP/PTP \n",
                    egr_port_no, eng_id, flow_id, numflows);

		rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
			break;
		}

	} while (0);


}


/* ETH-ETH-OAM Encapsulation */
static vtss_rc vtss_1588_sample_flows_eeoam(const vtss_inst_t inst,
                                            const vtss_port_no_t ing_port_no,
                                            const vtss_port_no_t egr_port_no,
                                            const vtss_phy_ts_engine_t eng_id,
                                            int   numflows,
                                            u8    in_flow)
{
        vtss_rc rc = VTSS_RC_ERROR;
        u8      flow_id = 0;
        vtss_phy_ts_engine_flow_conf_t *flow_conf;

        if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
                printf("Engine flow_conf memory allocation Failed!\n");
                return -1;
        }
        memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/OAM \n",
                          ing_port_no, eng_id, in_flow, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
                        break;
                }

                /* engine enable */
                flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
                    /* Map each flow to the channel which already mapped to the port */
                    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src) */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
                    /* Configure the MAC address of the flow, needs to be time stamped */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* ************************************************************************* */

                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = 2;
                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_B;
                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_I;
                   flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                   printf ("VLAN num_tags: %d, TagRange: 0x%04X;   OuterTagType: 0x%04X;  InnerTagType: 0x%04X \n",
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type);

		   flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AD;  //0x88A8;
                   /* Enable the IP flow */
                   printf("flow_id: %d::ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                        flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype,
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);

                   /* Enable the MAC flow */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                   /* Notify the engine which mac address needs to be matched(dest/src) */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                   /* Notify the engine if it is VLAN flow */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = FALSE;
                   /* Configure the MAC address of the flow, needs to be time stamped */
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                   flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
                   flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AG;    // 0x8902

                   printf("flow_id: %d::ETH2-ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype,
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);

               }

                rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                         printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
                } else {
                         printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
                         break;
                }
                printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/OAM\n",
                          egr_port_no, eng_id, flow_id, numflows);

                rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

}


/* ETH-MPLS-ETH-OAM Encapsulation */
static vtss_rc vtss_1588_sample_flows_emeoam(const vtss_inst_t inst,
                                             const vtss_port_no_t ing_port_no,
                                             const vtss_port_no_t egr_port_no,
                                             const vtss_phy_ts_engine_t eng_id,
                                             int   numflows,
                                             u8    in_flow)
{
        vtss_rc rc = VTSS_RC_ERROR;
        u8      flow_id = 0;
        vtss_phy_ts_engine_flow_conf_t *flow_conf;

        if ((flow_conf = (vtss_phy_ts_engine_flow_conf_t*)malloc(sizeof(vtss_phy_ts_engine_flow_conf_t))) == NULL) {
                printf("Engine flow_conf memory allocation Failed!\n");
                return -1;
        }
        memset(flow_conf, 0, sizeof(vtss_phy_ts_engine_flow_conf_t));

        printf("Ingress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: Encapsulation: ETH/OAM \n",
                          ing_port_no, eng_id, in_flow, numflows);

        if (numflows == 0xff) {
            numflows = in_flow+1;
        } else if ((numflows >= 0) && (numflows <= 8)) {
            printf("Valid numflows: %x!\n", numflows);
        } else {
            printf("Invalid numflows: %x!\n", numflows);
            return 0;
        }

        do {
                rc = vtss_phy_ts_ingress_engine_conf_get(inst, ing_port_no, eng_id, flow_conf);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_get Failed!\n", eng_id);
                        break;
                }

                /* engine enable */
                flow_conf->eng_mode = TRUE;
                for (flow_id = in_flow; flow_id < numflows; flow_id++) {
                    /* Map each flow to the channel which already mapped to the port */
                    flow_conf->channel_map[flow_id] = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src) */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Configure the MAC address of the flow, needs to be time stamped */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5] = 0x01+flow_id;
                    /* ************************************************************************* */
                    /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                    /* ************************************************************************* */
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].vlan_check = FALSE;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag = 0;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                    flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                    printf ("ETH1: VLAN num_tags: %d, TagRange: 0x%04X;   OuterTagType: 0x%04X;  InnerTagType: 0x%04X \n",
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].num_tag,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].tag_range_mode,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].outer_tag_type,
                       flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].inner_tag_type);

                    flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype = ETHERTYPE_IEEE_MPLS_UNI;  //0x8847;
                    flow_conf->flow_conf.ptp.eth1_opt.comm_opt.pbb_en = FALSE;

                    printf("flow_id: %d::ETH1-ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                        flow_conf->flow_conf.ptp.eth1_opt.comm_opt.etype,
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[0],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[1],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[2],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[3],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[4],
                        flow_conf->flow_conf.ptp.eth1_opt.flow_opt[flow_id].mac_addr[5]);


                    /* Enable the MPLS flow */
                    flow_conf->flow_conf.ptp.mpls_opt.comm_opt.cw_en = FALSE;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_depth = VTSS_PHY_TS_MPLS_STACK_DEPTH_1;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_ref_point = VTSS_PHY_TS_MPLS_STACK_REF_POINT_TOP;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.upper = 40;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.top.lower = 30;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.upper = 0xFFFFF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.frst_lvl_after_top.lower = 0xF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.upper = 0xFFFFF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.snd_lvl_after_top.lower = 0xF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.upper = 0xFFFFF;
                    flow_conf->flow_conf.ptp.mpls_opt.flow_opt[flow_id].stack_level.top_down.thrd_lvl_after_top.lower = 0xF;

                    /* Enable the MAC flow */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].flow_en = TRUE;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_mode = VTSS_PHY_TS_ETH_ADDR_MATCH_48BIT;
                    /* Notify the engine which mac address needs to be matched(dest/src) */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].addr_match_select = VTSS_PHY_TS_ETH_MATCH_DEST_ADDR;
                    /* Notify the engine if it is VLAN flow */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].vlan_check = TRUE;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].num_tag = 0;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].outer_tag_type = VTSS_PHY_TS_TAG_TYPE_S;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].inner_tag_type = VTSS_PHY_TS_TAG_TYPE_C;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].tag_range_mode = VTSS_PHY_TS_TAG_RANGE_NONE;
                    printf ("ETH2: VLAN num_tags: %d, TagRange: 0x%04X;   OuterTagType: 0x%04X;  InnerTagType: 0x%04X \n",
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].num_tag,
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].tag_range_mode,
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].outer_tag_type,
                       flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].inner_tag_type);

                    /* Configure the MAC address of the flow, needs to be time stamped */
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4] = 0x00;
                    flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5] = 0x21+flow_id;
                /* ************************************************************************* */
                /* For Demo Purpose ONLY, Modify eth1 MAC Addr for each flow to be different */
                /* ************************************************************************* */
                    flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype = ETHERTYPE_IEEE_802_1_AG;      //0x8902

                    printf("flow_id: %d::ETH2-ETHERTYPE: 0x%04X:: MAC_Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", flow_id,
                     flow_conf->flow_conf.ptp.eth2_opt.comm_opt.etype,
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[0],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[1],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[2],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[3],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[4],
                     flow_conf->flow_conf.ptp.eth2_opt.flow_opt[flow_id].mac_addr[5]);
                }

                rc = vtss_phy_ts_ingress_engine_conf_set(inst, ing_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                         printf("PHY TS Engine %d  Conf_set Success \n", eng_id);
                } else {
                         printf("PHY TS Engine %d  Conf_set Failed! \n", eng_id);
                         break;
                }
                printf("Egress:: Port:%d : Engine#%d  Flow_id:%d, numFlows:%d :: ETH/OAM\n",
                          egr_port_no, eng_id, flow_id, numflows);

                rc = vtss_phy_ts_egress_engine_conf_set(inst, egr_port_no, eng_id, flow_conf);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Conf_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Conf_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

}


/* PTP Actions */
static vtss_rc vtss_1588_sample_actions(const vtss_inst_t inst,
                                        const vtss_port_no_t ing_port_no,
                                        const vtss_port_no_t egr_port_no,
	                                const vtss_phy_ts_engine_t eng_id,
                                        const u8 action_id)
{
	vtss_rc rc = VTSS_RC_ERROR;
	vtss_phy_ts_engine_action_t *ptp_action;
	vtss_phy_ts_ptp_clock_mode_t   clk_mode;
	vtss_phy_ts_ptp_delaym_type_t	delay_type = VTSS_PHY_TS_PTP_DELAYM_E2E;
    char value_str[255] = {0};

	printf ("\nPTP Clock configuration: BC1STEP/BC2STEP/TC1STEP/TC2STEP/DELAY_COMP_ENG\n\n");

	if ((ptp_action = (vtss_phy_ts_engine_action_t*)malloc(sizeof(vtss_phy_ts_engine_action_t))) == NULL) {
		printf("Engine ptp_action memory allocation Failed!\n");
		return -1;
	}
	memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));
	do {

		printf ("Select Clock Mode (0=BC1STEP/1=BC2STEP/2=TC1STEP/3=TC2STEP/4=DELAY_COMP_ENG:");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);
		clk_mode = strtol(value_str, NULL, 10);
		if ((clk_mode <= 4) && (clk_mode >= 0)) {
			printf ("Clock Mode OPTION: %d	 Selected!! \n", clk_mode);
		} else {
			printf ("INVALID OPTION Selected!!	Options are: 0/1/2/3/4 \n");
		}

	} while (!((clk_mode <= 4) && (clk_mode >= 0)));


    printf("Ingress Clock Action: Engine#%d, action_id: %d,  clk_mode: %s, Delay_Type: %s \n", eng_id, action_id,
                    (clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP ? "BC1STEP" :
                     clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP ? "BC2STEP" :
                     clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP ? "TC1STEP" :
                     clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP ? "TC2STEP" :
                     clk_mode == VTSS_PHY_TS_PTP_DELAY_COMP_ENGINE  ? "DELAY_COMP_ENG" : "INVALID CLK MODE SELECTION"),
                    (delay_type == VTSS_PHY_TS_PTP_DELAYM_P2P ? "DELAY_P2P" :
                     delay_type == VTSS_PHY_TS_PTP_DELAYM_E2E ? "DELAY_E2E" : "INVALID DELAY SELECTION"));

	do {
                /* ALWAYS perform a "Get" before performing modifications and calling a "Set" */
		rc = vtss_phy_ts_ingress_engine_action_get(inst, ing_port_no, eng_id, ptp_action);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine Action_get Failed!\n");
			break;
		}

                /* The PTP Actions reflect the pre-defined sequence of operations based upon the clk_mode and delay_type */
                /* The API fills in the Minimum PTP_ACTIONS for each clk_mode and delay_type */
                /* As an example:*/
                /* action_id=0 is the SYNC Packet processing       */
                /* action_id=1 is the DELAY_REQ Packet processing  */
                /* action_id=2 is the PDELAY_REQ Packet processing */
                /* action_id=3 is the PDELAY_RSP Packet processing */
		ptp_action->action_ptp = TRUE;
		ptp_action->action.ptp_conf[action_id].enable = TRUE;
		ptp_action->action.ptp_conf[action_id].channel_map = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		ptp_action->action.ptp_conf[action_id].ptp_conf.range_en = FALSE;
		ptp_action->action.ptp_conf[action_id].clk_mode = clk_mode;	    // bc1step, bc2step,  tc1step, tc2step
		ptp_action->action.ptp_conf[action_id].delaym_type = delay_type;    // P2P or E2E

		rc = vtss_phy_ts_ingress_engine_action_set(inst, ing_port_no, eng_id, ptp_action);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Action_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
			break;
		}

		memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));

		printf("Egress Clock Action: Engine#%d, action_id: %d,  clk_mode: %s, Delay_Type: %s \n", eng_id, action_id,
                        (clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP ? "BC1STEP" :
                         clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP ? "BC2STEP" :
                         clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP ? "TC1STEP" :
                         clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP ? "TC2STEP" :
                         clk_mode == VTSS_PHY_TS_PTP_DELAY_COMP_ENGINE  ? "DELAY_COMP_ENG" : "INVALID CLK MODE SELECTION"),
                        (delay_type == VTSS_PHY_TS_PTP_DELAYM_P2P ? "DELAY_P2P" :
                         delay_type == VTSS_PHY_TS_PTP_DELAYM_E2E ? "DELAY_E2E" : "INVALID DELAY SELECTION"));

		rc = vtss_phy_ts_egress_engine_action_get(inst, egr_port_no, eng_id, ptp_action);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Engine %d  Action_get Failed!\n", eng_id);
			break;
		}

		ptp_action->action_ptp = TRUE;
		ptp_action->action.ptp_conf[action_id].enable = TRUE;
		ptp_action->action.ptp_conf[action_id].channel_map = VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
		ptp_action->action.ptp_conf[action_id].ptp_conf.range_en = FALSE;
		ptp_action->action.ptp_conf[action_id].clk_mode = clk_mode;	    // bc1step, bc2step,  tc1step, tc2step
		ptp_action->action.ptp_conf[action_id].delaym_type = delay_type;    // P2P or E2E

		rc = vtss_phy_ts_egress_engine_action_set(inst, egr_port_no, eng_id, ptp_action);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Engine %d  Action_set Success\n", eng_id);
		} else {
			printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
			break;
		}

	} while (0);
	return rc;
}


/* OAM Actions */
static vtss_rc vtss_oam_sample_actions(const vtss_inst_t inst,
                                       const vtss_port_no_t ing_port_no,
                                       const vtss_port_no_t egr_port_no,
                                       const vtss_phy_ts_engine_t eng_id )
{
        vtss_rc rc = VTSS_RC_ERROR;
        vtss_phy_ts_engine_action_t *ptp_action;
        vtss_phy_ts_oam_engine_action_t *oam_action;
        vtss_phy_ts_ptp_delaym_type_t   delay_type = VTSS_PHY_TS_PTP_DELAYM_E2E;
        char value_str[255] = {0};

        printf ("\n OAM Action configuration:\n\n");

        if ((ptp_action = (vtss_phy_ts_engine_action_t*)malloc(sizeof(vtss_phy_ts_engine_action_t))) == NULL) {
                printf("Engine ptp_action memory allocation Failed!\n");
                return -1;
        }
        memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));

        do {
                rc = vtss_phy_ts_ingress_engine_action_get(inst, ing_port_no, eng_id, ptp_action);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine Action_get Failed!\n");
                        break;
                }
                oam_action = &ptp_action->action.oam_conf[0];
                oam_action->enable = TRUE;
                oam_action->channel_map =  VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
                oam_action->version     = 0;
                oam_action->y1731_en    = TRUE;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_DMM;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_Y1731_OAM_DELAYM_1DM;
                oam_action->oam_conf.y1731_oam_conf.range_en = TRUE;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.lower = 0;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.upper = 0xF;

                rc = vtss_phy_ts_ingress_engine_action_set(inst, ing_port_no, eng_id, ptp_action);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Action_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
                        break;
                }

                memset(ptp_action, 0, sizeof(vtss_phy_ts_engine_action_t));


                rc = vtss_phy_ts_egress_engine_action_get(inst, egr_port_no, eng_id, ptp_action);
                if (rc != VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Action_get Failed!\n", eng_id);
                        break;
                }

                oam_action = &ptp_action->action.oam_conf[0];
                oam_action->enable = TRUE;
                oam_action->channel_map =  VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH0 | VTSS_PHY_TS_ENG_FLOW_VALID_FOR_CH1;
                oam_action->version     = 0;
                oam_action->y1731_en    = TRUE;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_IETF_MPLS_ACH_OAM_DELAYM_DMM;
                oam_action->oam_conf.y1731_oam_conf.delaym_type = VTSS_PHY_TS_Y1731_OAM_DELAYM_1DM;
                oam_action->oam_conf.y1731_oam_conf.range_en = TRUE;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.lower = 0;
                oam_action->oam_conf.y1731_oam_conf.meg_level.range.upper = 0xF;

                rc = vtss_phy_ts_egress_engine_action_set(inst, egr_port_no, eng_id, ptp_action);
                if (rc == VTSS_RC_OK) {
                        printf("PHY TS Engine %d  Action_set Success\n", eng_id);
                } else {
                        printf("PHY TS Engine %d  Action_set Failed!\n", eng_id);
                        break;
                }
        } while (0);

        return rc;
}


static vtss_rc vtss_ptp_get_pkt_encap(vtss_phy_ts_encap_t * encap)
{
        char value_str[255] = {0};
	vtss_phy_ts_encap_t pkt_encap;
	BOOL invalid_input = FALSE;
	vtss_rc rc = VTSS_RC_OK;
	do {
		printf(" Enter Encapsulation Type: \n");
		printf(" \t0 = ETH/PTP \n");
		printf(" \t1 = ETH/IP/PTP \n");
		printf(" \t2 = ETH/IP/IP/PTP \n");
		printf(" \t3 = ETH/ETH/PTP \n");
		printf(" \t4 = ETH/ETH/IP/PTP \n");
		printf(" \t5 = ETH/MPLS/IP/PTP \n");
		printf(" \t6 = ETH/MPLS/ETH/PTP \n");
		printf(" \t7 = ETH/MPLS/ETH/IP/PTP \n");
		printf(" \t8 = ETH/MPLS/ACH/PTP \n");
		printf(" \t9 = ETH/OAM \n");
		printf(" \tA = ETH/ETH/OAM \n");
		printf(" \tB = ETH/MPLS/ETH/OAM \n");
		printf(" \tC = ETH/MPLS/ACH/OAM \n");

		printf("\nSelect the Encapsulation Type: \n");
		memset (&value_str[0], 0, sizeof(value_str));
		scanf("%s", &value_str[0]);

		switch (value_str[0]) {
		case '0':
			printf("VTSS_PHY_TS_ENCAP_ETH_PTP \n");
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_PTP;
			break;
		case '1':
			printf("VTSS_PHY_TS_ENCAP_ETH_IP_PTP \n");
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_IP_PTP;
			break;
		case '2':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP \n");
			break;
		case '3':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_ETH_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_ETH_PTP \n");
			break;
		case '4':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP \n");
			break;
		case '5':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP \n");
			break;
		case '6':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP \n");
			break;
		case '7':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP \n");
			break;
		case '8':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP\n");
			break;
		/* OAM encap */
		case '9':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_OAM;
			printf("VTSS_PHY_TS_ENCAP_ETH_OAM \n");
                        break;
		case 'A':
		case 'a':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_ETH_OAM;
			printf("VTSS_PHY_TS_ENCAP_ETH_ETH_OAM \n");
			break;
		case 'B':
		case 'b':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM;
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM \n");
			break;
		case 'C':
		case 'c':
			pkt_encap = VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM; /* MPLS-TP OAM */
			printf("VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM \n");
			break;
		default:
			printf("INVALID Selection!!!! Select Encapsulation type Again\n\n\n\n");
			invalid_input = TRUE;
			break;
		}
	} while(invalid_input);

	*encap = pkt_encap;
	return rc;

}

/* ********************************************************** */
/* *************     BOUNDARY CLOCK   *********************** */
/* ************            or            ******************** */
/* *************     TRANSPARENT CLOCK   ******************** */
/* ********************************************************** */
/* Vtss Sample Application for BC
  --->P1-->S1  --->  S2-->P1  (P:Port S: Switch)

If we pass same ing_port_no and egr_port_no to this application that port
will be configured for both ing and egr functionalities of BC App,
and needs be called on both switches.
Application: Ordinary/Boundary clock, 1 step
Delay method: End-to-End delay measurement method
*/


/* ********************************************************** */
/* ********************************************************** */

static vtss_rc vtss_ptp_sample_clock(const vtss_inst_t inst,
                                     const vtss_port_no_t ing_port_no,
                                     const vtss_port_no_t egr_port_no,
                                     const vtss_phy_ts_engine_t  eng_id)
{
        char value_str[255] = {0};
	vtss_phy_ts_init_conf_t conf;
	u8		flow_id = 0;
	u8		ptp_action_id = 0;
	vtss_rc rc;
	int numflows = 0;  // Change the number of flows configured
                           // Value Range 1-8 and 0xff = Configure designated flow_id Only
	int start_flow = 0;
	int end_flow = 1;
	vtss_phy_ts_encap_t pkt_encap = 0;
        unsigned char resv_oos_flow7 = FALSE;

        vtss_phy_ts_fifo_sig_mask_t    sig_mask_min = VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID | VTSS_PHY_TS_FIFO_SIG_SEQ_ID;
        vtss_phy_ts_fifo_sig_mask_t    sig_mask;

#ifdef TESLA_ING_TS_ERRFIX
        resv_oos_flow7 = TRUE;
#endif
	memset(&conf, 0, sizeof(vtss_phy_ts_init_conf_t));
	//memset(&init_conf, 0, sizeof(vtss_phy_ts_eng_init_conf_t));

	/* *****************  Setup Default Configuration for 10G ***************************** */
        /* On Malibu, ALL Internal Clocks are 161.13Mhz                                         */
        /* On Venice, Line Side Internal Clocks are 161.13Mhz                                   */
        /* 161.13MHz is NOT evenly divisible for the required clock speed for accuracy          */
        /* On Venice, Host Side Internal Clocks are 156.25MHz and can be used                   */
        /* Because of these considerations, We recommend using the External CLK Src for 10G PHY */
	/* ************************************************************************************ */

#ifdef VTSS_CHIP_10G_PHY
	conf.clk_freq	   = VTSS_PHY_TS_CLOCK_FREQ_250M; 		/* reference clock frequency */
	conf.clk_src	   = VTSS_PHY_TS_CLOCK_SRC_EXTERNAL;		/* Clock Source - External for 10G */
#elif defined VTSS_CHIP_CU_PHY  /* 1G PHY Config */
	conf.clk_freq	   = VTSS_PHY_TS_CLOCK_FREQ_250M; 		/* reference clock frequency */
	conf.clk_src	   = VTSS_PHY_TS_CLOCK_SRC_INTERNAL;		/* Clock Source */
#else
	conf.clk_freq	   = VTSS_PHY_TS_CLOCK_FREQ_250M; 		/* reference clock frequency */
	conf.clk_src	   = VTSS_PHY_TS_CLOCK_SRC_INTERNAL;		/* Clock Source */
#endif
	conf.rx_ts_pos	   = VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP;	/*	Rx timestamp in PTP reserved bytes */
	conf.rx_ts_len	   = VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT; 							/*	Rx timestamp update nano seconds part */
	conf.tx_fifo_mode  = VTSS_PHY_TS_FIFO_MODE_NORMAL; 		/*	Timestamps to pushed out on the SPI interface */
	conf.tx_ts_len	   = VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE; /* 10byte Full Tx timestamp */
	conf.tc_op_mode    = VTSS_PHY_TS_TC_OP_MODE_B;	   /* TC operating mode is Mode B*/
	conf.auto_clear_ls = FALSE; 					   /* Load and Save of LTC are auto cleared */
	conf.macsec_ena    = FALSE;				   /* MACsec is enabled or disabled */
	conf.chk_ing_modified = FALSE;					   /* True if the flag bit needs to be modified in ingress and thus in egress */

        printf("\n %s :: %s :: %s \n",
	    (conf.clk_src == VTSS_PHY_TS_CLOCK_SRC_INTERNAL ? "VTSS_PHY_TS_CLOCK_SRC_INTERNAL" :
	     conf.clk_src == VTSS_PHY_TS_CLOCK_SRC_EXTERNAL ? "VTSS_PHY_TS_CLOCK_SRC_EXTERNAL" : "INVALID SRC"),
            (conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_125M ? "VTSS_PHY_TS_CLOCK_FREQ_125M" :
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_15625M ? "VTSS_PHY_TS_CLOCK_FREQ_15625M" :
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_200M ? "VTSS_PHY_TS_CLOCK_FREQ_200M" :
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_250M ? "VTSS_PHY_TS_CLOCK_FREQ_250M" :
             conf.clk_freq == VTSS_PHY_TS_CLOCK_FREQ_500M ? "VTSS_PHY_TS_CLOCK_FREQ_500M" : "INVALID CLOCK Freq"),
	    (conf.rx_ts_pos == VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP ? "VTSS_PHY_TS_RX_TIMESTAMP_POS_IN_PTP" :
	     conf.rx_ts_pos == VTSS_PHY_TS_RX_TIMESTAMP_POS_AT_END ? "VTSS_PHY_TS_RX_TIMESTAMP_POS_AT_END" : "INVALID TS POSITION"));

        printf(" %s :: %s :: %s \n",
	    (conf.rx_ts_len == VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT ? "VTSS_PHY_TS_RX_TIMESTAMP_LEN_30BIT" :
	     conf.rx_ts_len == VTSS_PHY_TS_RX_TIMESTAMP_LEN_32BIT ? "VTSS_PHY_TS_RX_TIMESTAMP_LEN_32BIT" : "INVALID TS LENGTH"),
	    (conf.tx_fifo_mode == VTSS_PHY_TS_FIFO_MODE_NORMAL ? "VTSS_PHY_TS_FIFO_MODE_NORMAL" :
	     conf.tx_fifo_mode == VTSS_PHY_TS_FIFO_MODE_SPI ? "VTSS_PHY_TS_FIFO_MODE_SPI" : "INVALID FIFO MODE"),
	    (conf.tx_ts_len == VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE ? "VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE" :
	     conf.tx_ts_len == VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE ? "VTSS_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE" : "INVALID FIFO TS LENGTH"));

        printf(" %s :: MACSEC_ENA: %x \n",
	    (conf.tc_op_mode == VTSS_PHY_TS_TC_OP_MODE_A ? "VTSS_PHY_TS_TC_OP_MODE_A" :
	     conf.tc_op_mode == VTSS_PHY_TS_TC_OP_MODE_B ? "VTSS_PHY_TS_TC_OP_MODE_B" :
	     conf.tc_op_mode == VTSS_PHY_TS_TC_OP_MODE_C ? "VTSS_PHY_TS_TC_OP_MODE_C" : "INVALID TC OP_MODE"),
             conf.macsec_ena);

	rc = vtss_ptp_get_pkt_encap(&pkt_encap);
        printf("\nSelect the Number of Flows to configure (1-8) -- config OOS, Flows = 8  (1-8) : ");
        memset (&value_str[0], 0, sizeof(value_str));
        scanf("%s", &value_str[0]);
        numflows = atoi(value_str);
        if (numflows == 0 || numflows > 8) {
            printf("\nInvalid Number of Flows; Values are (1-7): \n");
            return;
        }
        printf("\nSelected Number of Flows: %d  \n", numflows);

	start_flow = 0;
        end_flow = numflows-1;

        if (((pkt_encap == VTSS_PHY_TS_ENCAP_ETH_PTP) || (pkt_encap == VTSS_PHY_TS_ENCAP_ETH_IP_PTP)) &&
             (numflows == 8)) {
            printf("\nWARNING: Flow_Id: 7 Appears to be Used by Application and will be Over-Written by OOS Recovery! \n ");
            printf("WARNING: Flow_Id: 7 Enabling Flow 7 for OOS Recovery \n ");
            resv_oos_flow7 = TRUE;
        }

#if 0
i### #ifdef _INCLUDE_DEBUG_FILE_PRINT_
        fprintf(fp, "Configure 1588: Encap: %d, Engine:%d, ptp_action_id: %d, clk_mode: %s, Delay_Type: %s \n",
                         pkt_encap, eng_id, ptp_action_id,
                        (ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC1STEP ? "BC1STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_BC2STEP ? "BC2STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC1STEP ? "TC1STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_CLOCK_MODE_TC2STEP ? "TC2STEP" :
                         ptp_clk_mode == VTSS_PHY_TS_PTP_DELAY_COMP_ENGINE  ? "DELAY_COMP_ENG" : "INVALID CLK MODE SELECTION"),
                        (ptp_delay_type == VTSS_PHY_TS_PTP_DELAYM_P2P ? "DELAY_P2P" :
                         ptp_delay_type == VTSS_PHY_TS_PTP_DELAYM_E2E ? "DELAY_E2E" : "INVALID DELAY SELECTION"));
#endif

	do {

		rc = vtss_phy_ts_init(inst, ing_port_no, &conf);
		if (rc == VTSS_RC_OK) {
			printf("PHY TS Init Success for ing_port_no: %d\n", ing_port_no);
		} else {
			printf("PHY TS Init Failed for ing_port_no: %d\n", ing_port_no);
			break;
		}

		rc = vtss_phy_ts_mode_set (inst, ing_port_no, TRUE);
		printf("PHY TS Block Ingress Port: %d, Enabled for channel 0!\n", ing_port_no);
		if (rc != VTSS_RC_OK) {
			printf("PHY TS Block Enable Failed for channel 0!\n");
			break;
		}

		if( ing_port_no!= egr_port_no ){
			rc = vtss_phy_ts_init(inst, egr_port_no, &conf);
			if (rc == VTSS_RC_OK) {
				printf("PHY TS Init Success for egr_port_no: %d\n", egr_port_no);
			} else {
				printf("PHY TS Init Failed for egr_port_no: %d\n", egr_port_no);
				break;
			}

			rc = vtss_phy_ts_mode_set (inst, egr_port_no, TRUE);
			printf("PHY TS Block Egress Port: %d, Enabled for channel 0!\n", egr_port_no);
			if (rc != VTSS_RC_OK) {
				printf("PHY TS Block Enable Failed for channel 1!\n");
				break;
			}
		}

		rc = vtss_phy_ts_ingress_engine_init(inst, ing_port_no,
						eng_id,
						pkt_encap, // VTSS_PHY_TS_ENCAP_ETH_PTP, Simpliest Match = IEEE_PTP_1588, ie. 0x88F7
						start_flow,			 // Flow Start Index
						end_flow,			 // Flow End Index
						VTSS_PHY_TS_ENG_FLOW_MATCH_STRICT);

		if (rc == VTSS_RC_OK) {
			printf("ing_port_no: %d, PHY TS Engine %d  Init Success\n", ing_port_no, eng_id);
		} else {
			printf("ing_port_no: %d, PHY TS Engine %d  Init Failed \n", ing_port_no, eng_id);
			break;
		}

		rc = vtss_phy_ts_egress_engine_init(inst, egr_port_no,
						eng_id,
						pkt_encap,
						start_flow,			 // Flow Start Index
						end_flow,			 // Flow End Index
						VTSS_PHY_TS_ENG_FLOW_MATCH_STRICT);

		if (rc == VTSS_RC_OK) {
			printf("Egress Port: %d, PHY TS Engine %d  Init Success\n", egr_port_no, eng_id);
		} else {
			printf("Egress Port: %d, PHY TS Engine %d  Init Failed \n", egr_port_no, eng_id);
			break;
		}

                flow_id = start_flow; // Flow_id to configure if numflows = 0xff

                switch (pkt_encap) {
                    case VTSS_PHY_TS_ENCAP_ETH_PTP:
#ifdef TESLA_ING_TS_ERRFIX
                        rc = vtss_phy_ts_fifo_sig_get(inst, ing_port_no, &sig_mask);
                        if (sig_mask < sig_mask_min) {
                            printf ("Src IP address:    VTSS_PHY_TS_FIFO_SIG_SRC_IP          = 0x01 \n");
                            printf ("Dest IP address:   VTSS_PHY_TS_FIFO_SIG_DEST_IP         = 0x02 \n");
                            printf ("Msg Type:          VTSS_PHY_TS_FIFO_SIG_MSG_TYPE        = 0x04 \n");
                            printf ("Domain Number:     VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM      = 0x08 \n");
                            printf ("Src Port ID:       VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  = 0x10 \n");
                            printf ("PTP Frame Seq ID:  VTSS_PHY_TS_FIFO_SIG_SEQ_ID          = 0x20 \n");
                            printf ("Dest MAC Addr:     VTSS_PHY_TS_FIFO_SIG_DEST_MAC        = 0x40 \n");
                            printf ("Note: Signature Masks are OR'd together, so Multiple can be chosen \n\n");
                            printf ("Port: %d;   Current TS Signatgure Mask: 0x%04x \n", ing_port_no, sig_mask);
                            printf ("Port: %d;   Minimum TS Signatgure Mask: 0x%04x \n", ing_port_no, sig_mask_min);
                            printf ("Port: %d;   Forcing Sig_Mask to Min Required: 0x%04x \n", ing_port_no, sig_mask_min);
                            vtss_phy_ts_fifo_sig_set(inst, ing_port_no, sig_mask_min);
                        }
#endif
                        vtss_1588_sample_flows_ep(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id, resv_oos_flow7);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_IP_PTP:
#ifdef TESLA_ING_TS_ERRFIX
                        rc = vtss_phy_ts_fifo_sig_get(inst, ing_port_no, &sig_mask);
                        if (sig_mask < sig_mask_min) {
                            printf ("Src IP address:    VTSS_PHY_TS_FIFO_SIG_SRC_IP          = 0x01 \n");
                            printf ("Dest IP address:   VTSS_PHY_TS_FIFO_SIG_DEST_IP         = 0x02 \n");
                            printf ("Msg Type:          VTSS_PHY_TS_FIFO_SIG_MSG_TYPE        = 0x04 \n");
                            printf ("Domain Number:     VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM      = 0x08 \n");
                            printf ("Src Port ID:       VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  = 0x10 \n");
                            printf ("PTP Frame Seq ID:  VTSS_PHY_TS_FIFO_SIG_SEQ_ID          = 0x20 \n");
                            printf ("Dest MAC Addr:     VTSS_PHY_TS_FIFO_SIG_DEST_MAC        = 0x40 \n");
                            printf ("Note: Signature Masks are OR'd together, so Multiple can be chosen \n\n");
                            printf ("Port: %d;   Current TS Signatgure Mask: 0x%04x \n", ing_port_no, sig_mask);
                            printf ("Port: %d;   Minimum TS Signatgure Mask: 0x%04x \n", ing_port_no, sig_mask_min);
                            printf ("Port: %d;   Forcing Sig_Mask to Min Required: 0x%04x \n", ing_port_no, sig_mask_min);
                            vtss_phy_ts_fifo_sig_set(inst, ing_port_no, sig_mask_min);
                        }
#endif
                        vtss_1588_sample_flows_eip(inst, ing_port_no, egr_port_no, eng_id, numflows, flow_id, resv_oos_flow7);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_IP_IP_PTP:
                        vtss_1588_sample_flows_eiip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_ETH_PTP:
                        vtss_1588_sample_flows_eep(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_ETH_IP_PTP:
                        vtss_1588_sample_flows_eeip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_IP_PTP:
                        vtss_1588_sample_flows_emip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP:
                        vtss_1588_sample_flows_emep(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
                        vtss_1588_sample_flows_emeip(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;

                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_PTP:
                        printf("INVALID Encapsulation Type: 0x%x\n", pkt_encap);
                        break;
                    /* OAM encap */
                    case VTSS_PHY_TS_ENCAP_ETH_OAM:
                        vtss_1588_sample_flows_eoam(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;
                    case VTSS_PHY_TS_ENCAP_ETH_ETH_OAM:
                        vtss_1588_sample_flows_eeoam(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;
                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM:
                        vtss_1588_sample_flows_emeoam(inst, ing_port_no,egr_port_no, eng_id, numflows, flow_id);
                        break;
                    case VTSS_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM: /* MPLS-TP OAM */
                        printf("INVALID Encapsulation Type: 0x%x\n", pkt_encap);
                        break;
                    default:
                        printf("INVALID Encapsulation Type: 0x%x\n", pkt_encap);
                        break;
                }

/* *************     Setup:          *********************** */
/* *************       BOUNDARY CLOCK  BC1Step or BC2Step or  ** */
/* *************       TRANSPARENT CLOCK  TC1Step or TC2Step *** */
/* *************       OAM                                   *** */
/* ************************************************************* */

                if(pkt_encap < VTSS_PHY_TS_ENCAP_ETH_OAM) {
                    vtss_1588_sample_actions(inst, ing_port_no,egr_port_no, eng_id, ptp_action_id);
                } else {
                    vtss_oam_sample_actions(inst, ing_port_no,egr_port_no, eng_id);
                }

           } while (0);

    return VTSS_RC_OK;

}

/* Update the internal timestamp table, from HW */
static void demo_ts_phy_fifo_read(  const vtss_inst_t              inst,
                                    const vtss_port_no_t           port_no,
                                    const vtss_phy_timestamp_t     *const fifo_ts,
                                    const vtss_phy_ts_fifo_sig_t   *const sig,
                                    void                           *cntxt,
                                    const vtss_phy_ts_fifo_status_t status)
{
    vtss_phy_ts_fifo_sig_t sig_loc;
    /* Send Message from Daytona to the connected Jaguar Board */
    memset(&sig_loc, 0, sizeof(sig_loc));
    memcpy(&sig_loc, sig, sizeof(vtss_phy_ts_fifo_sig_t));
    printf("port_no %u, tx signature: mask %x, type %d, domain %d, seq %d\n", port_no,
         sig->sig_mask, sig->msg_type, sig->domain_num, sig->sequence_id);
    printf("tx time:  Sec_Hi:%d, Sec_Low:%u,  Nsec: %u, Nsec (hex) ns %x\n",
         fifo_ts->seconds.high, fifo_ts->seconds.low, fifo_ts->nanoseconds, fifo_ts->nanoseconds);
}


void vtss_appl_ts_demo_menu(vtss_inst_t  inst, vtss_port_no_t  port_no)
{
    vtss_rc        rc = 0;
    u16            value = 0;
    char           value_str[255] = {0};
    char           command[255] = {0};
    char           port_no_str[255] = {0};
    BOOL           enable_1588 = FALSE;
    vtss_port_no_t ing_port_no = 0;
    vtss_port_no_t egr_port_no = 0;


#ifdef TESLA_ING_TS_ERRFIX
    BOOL OOS = FALSE;
    vtss_phy_ts_fifo_conf_t        fifo_conf = {.detect_only = FALSE,
                                                .eng_recov = VTSS_PHY_TS_PTP_ENGINE_ID_0,
                                                .eng_minE = VTSS_PHY_TS_OAM_ENGINE_ID_2B
                                               };
#endif  /* TESLA_ING_TS_ERRFIX */

    vtss_phy_ts_engine_t           eng_id = 0;
    vtss_phy_ts_fifo_sig_mask_t    sig_mask=0;

    while(1) {
            value = 0;
            memset (&value_str[0], 0, sizeof(value_str));
            memset (&command[0], 0, sizeof(command));
            memset (&port_no_str[0], 0, sizeof(port_no_str));
            enable_1588 = 1;

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fflush(fp);
#endif
            printf (" \n\n");
            printf (" ptp_clock  <port_no> - Setup Ingress/Egress Ports for 1588v2 Boundary Clk PTP Encap\n");
            printf (" 1588_epg   <port_no> - Setup EPG to generate certain Frame \n");
            printf (" 1588_ena   <port_no> - Enable 1588 on this port - and No other actions \n");
            printf (" 1588_dis   <port_no> - Disable 1588 on this port - and No other actions \n");
            printf (" ing_eng_clr<port_no> - Clear/Release 1588 Analyzer Ingress Engine already Initialized \n");
            printf (" egr_eng_clr<port_no> - Clear/Release 1588 Analyzer Egress Engine already Initialized \n");
            printf (" int_enable <port_no> - Setup Ingress/Egress/LTC INT Enable/Disable for Port for 1588v2\n");
            printf (" event_poll <port_no> - Polling Ingress/Egress/LTC INT for Port for 1588v2\n");
            printf (" ptp_get    <port_no> - Get the PHY PTP timestamp in Secs/NanoSecs, Clear the Save Enable \n");
            printf (" ptp_arm_set <port_no> - Set the PHY timestamp in seconds and nanoseconds \n");
            printf (" arm_set_done <port_no> - Set the PHY timestamp \n");
            printf (" ptp_load   <port_no> - Get the PHY PTP load time in seconds and nanoseconds \n");
            printf (" cb_install <port_no> - Install Call-back to read FIFO \n");
            printf (" read_fifo  <port_no> - Reads the FIFO until empty and then Executes the FIFO Read Call-back \n");
            printf (" ts_reg_dump  <port_no> - Dump 1588 Registers\n");
            printf (" sig_get    <port_no> - Get TS Signature Bytes  \n");
            printf (" sig_set    <port_no> - Set TS Signature Bytes  \n");
            printf (" run_oos    <port_no> - Run the Tesla OOS Recovery via Direct API Call \n");
            printf (" x - exit             - Exit to upper level menu\n");
            printf ("> ");
            rc = scanf("%s", &command[0]);

            if ((strcmp(command, "x") == 0) || (strcmp(command, "X") == 0)) {
                break;
            } else if (strcmp(command, "1588_ena") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                enable_1588 = 1;
                printf("PHY TS Block Enable::vtss_phy_ts_mode_set:Enable: Port: %d\n", port_no);

                rc = vtss_phy_ts_mode_set (inst, port_no, enable_1588);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Block Enable Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "1588_dis") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                enable_1588 = 0;
                printf("PHY TS Block Enable::vtss_phy_ts_mode_set:Disable: Port: %d\n", port_no);

                rc = vtss_phy_ts_mode_set (inst, port_no, enable_1588);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Block Disable Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "ing_eng_clr") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                eng_id = (port_no % 2) ? VTSS_PHY_TS_PTP_ENGINE_ID_1:VTSS_PHY_TS_PTP_ENGINE_ID_0;  // Eval Board Ports 0-3

                rc = vtss_phy_ts_ingress_engine_clear (inst, port_no, eng_id);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Ingress Engine Clear Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "egr_eng_clr") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                eng_id = (port_no % 2) ? VTSS_PHY_TS_PTP_ENGINE_ID_1:VTSS_PHY_TS_PTP_ENGINE_ID_0;  // Eval Board Ports 0-3

                rc = vtss_phy_ts_egress_engine_clear (inst, port_no, eng_id);
                if (rc != VTSS_RC_OK) {
                    printf("PHY TS Ingress Engine Clear Failed for port: %d\n", port_no);
                }
                continue;

            } else if (strcmp(command, "ptp_clock") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_engine_t  eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_0;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                printf ("Please ensure that the FRAME data has Correct EtherType for Encapsulation!!\n" ) ;
                printf ("Please ensure that Dest MAC ADDR, IP Addr, and UDP Src/Dest are set correctly !\n");
                printf ("ETH1 Dest MAC : 00-00-00-00-00-01  (+ Flow_Id (0-7) to make Flows different) \n");
                printf ("ETH2 Dest MAC : 00-00-00-00-00-21 \n");
                printf ("IP1 Dest IP: 10.10.10.10      IP2 Dest IP: 10.10.10.11 \n");
                printf ("MPLS Label Range(F ~ FFFFF) \n");
                printf ("UDP Dest Port: 319         UDP Src Port: 1 \n\n");
                ing_port_no = port_no;
                printf ("Ingress Port %d \n", port_no);
                printf ("\nPlease Enter Egress Port: ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                egr_port_no = atoi(value_str);

                printf ("\nPlease Engine to be Configured (PTP 0/1   OAM:2a/2b): ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '0') {
                    printf ("PTP Eng_0 Selected \n");
                    eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_0;
                } else if (value_str[0] == '1') {
                    printf ("PTP Eng_1 Selected \n");
                    eng_id = VTSS_PHY_TS_PTP_ENGINE_ID_1;
                } else if (value_str[0] == '2') {
                    printf ("OAM Eng_2 Selected \n");
                    if (value_str[1] == 'a' || value_str[1] == 'A') {
                        printf ("OAM Eng_2A Selected \n");
                        eng_id = VTSS_PHY_TS_OAM_ENGINE_ID_2A;
                    } else if (value_str[1] == 'b' || value_str[1] == 'B') {
                        printf ("OAM Eng_2B Selected \n");
                        eng_id = VTSS_PHY_TS_OAM_ENGINE_ID_2B;
                    } else {
                        printf ("Defaulting to OAM Eng_2A \n");
                        eng_id = VTSS_PHY_TS_OAM_ENGINE_ID_2A;
                    }
                } else {
                    printf ("INVALID OPTION Selected!!  Options are: 0/1/2a/2b");
                    continue;
                }

                rc = vtss_ptp_sample_clock(inst, ing_port_no, egr_port_no, eng_id);
                continue;

            } else if (strcmp(command, "ts_reg_dump") == 0) {
                vtss_rc  rc;
                vtss_debug_info_t  dbg_info;
                int i;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

#undef ENABLE_1588_DEBUG_REG_READ_DEMO
#ifdef ENABLE_1588_DEBUG_REG_READ_DEMO
                vtss_debug_printf_t pr=(vtss_debug_printf_t) printf;

                ing_port_no = port_no;
                printf ("Ingress Port %d \n", port_no);
                printf ("\nPlease Enter Egress Port: ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                egr_port_no = atoi(value_str);

		printf("\n\n Register Dump:\n\n");
		rc = vtss_phy_1588_debug_reg_read(inst,ing_port_no, 0, pr);
		rc = vtss_phy_1588_debug_reg_read(inst,egr_port_no, 1, pr);
		rc = vtss_phy_1588_debug_reg_read(inst,ing_port_no, 2, pr);
		rc = vtss_phy_1588_debug_reg_read(inst,egr_port_no, 3, pr);
		rc = vtss_phy_1588_debug_reg_read(inst,ing_port_no, 4, pr);
		rc = vtss_phy_1588_debug_reg_read(inst,ing_port_no, 5, pr);
		rc = vtss_phy_1588_debug_reg_read(inst,ing_port_no, 6, pr);
		rc = vtss_phy_1588_debug_reg_read(inst,ing_port_no, 7, pr);
#else

                memset (&dbg_info, 0, sizeof(vtss_debug_info_t));
                vtss_debug_info_get (&dbg_info); /* This turns on ALL Ports in port list */
                for (i=0; i<VTSS_PORT_ARRAY_SIZE; i++) {
                    dbg_info.port_list[i] = 0;
                }
                dbg_info.port_list[port_no] = 1;
                dbg_info.layer = VTSS_DEBUG_LAYER_ALL;
                dbg_info.group = VTSS_DEBUG_GROUP_PHY_TS;
                dbg_info.full = 1;
                rc = vtss_debug_info_print(inst, (vtss_debug_printf_t) printf, &dbg_info);
#endif

		continue;

            } else if (strcmp(command, "1588_epg") == 0) {
               if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
#ifdef TESLA_ING_TS_ERRFIX
#if 0
                u32 ing_delta = 0;
                u32 egr_delta = 0;
                u16 match_mode = 0x10;  // INGRESS = 0x10; EGRESS = 0x11; BOTH = 0x12;
                printf ("\nPlease Enter Match Mode (No_Match=0/Ingress=16/Egress=17/Both=18): ");
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                match_mode = atoi(value_str);
                printf ("\nMatch Mode: %d\n", match_mode);
                //match_mode = ingress ? MATCH_INGRESS : MATCH_EGRESS;
                rc = vtss_phy_ts_tesla_epg(board->inst, port_no, (vtss_debug_printf_t) printf, 125, match_mode, &ing_delta, &egr_delta);
#endif
#endif
                continue;
#ifdef VTSS_CHIP_CU_PHY  /* These Interrupts are only for 1G CU PHY Silicon */
                         /* 10G PHY Interrupts are routed differently */
           } else if (strcmp(command, "int_enable") == 0) {
                vtss_rc  rc;
                BOOL enable = FALSE;
                vtss_phy_ts_event_t  ev_mask=0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet Event Enable Settings\n");
#endif
                rc = vtss_phy_ts_event_enable_get(inst, port_no, &ev_mask);

                printf ("VTSS_PHY_TS_INGR_ENGINE_ERR            0x01  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_PREAM_ERR          0x02  /**< Preamble too short to append timestamp */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_FCS_ERR            0x04  /**< FCS error in ingress */ \n");
                printf ("VTSS_PHY_TS_EGR_ENGINE_ERR             0x08  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_EGR_RW_FCS_ERR             0x10  /**< FCS error in egress */ \n");
                printf ("VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20  /**< Timestamp captured in Tx TSFIFO */ \n");
                printf ("VTSS_PHY_TS_EGR_FIFO_OVERFLOW          0x40  /**< Tx TSFIFO overflow */ \n");
                printf ("VTSS_PHY_TS_DATA_IN_RSRVD_FIELD        0x80  /**< Data in reserved Field */ \n");
                printf ("VTSS_PHY_TS_LTC_NEW_PPS_INTRPT         0x100 /**< New PPS pushed onto external PPS pin*/ \n");
                printf ("VTSS_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200 /**< New LTC value either loaded in to HW or saved into registers*/ \n");
                printf ("\n");
                printf ("Current 1588 Event Mask: 0x%x\n", ev_mask);
                printf ("\n");
                printf ("Please Enter the Desired Event Mask (Must be in Hex) for Port: %d  (0x0=Exit):", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ev_mask = strtol(value_str, NULL, 16);

                if (ev_mask == 0) {
                    continue;
                }

                enable = FALSE;
                printf ("Event Mask: 0x%x:  Enter Disable(0)/Enable(1) for port  %d :", ev_mask, port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '1') {
                    enable = TRUE;
                }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nSet Event Enable Settings\n");
#endif
                rc = vtss_phy_ts_event_enable_set(inst, port_no, enable, ev_mask);
                printf ("Event Mask: 0x%x:  Enable: 0x%x;  for port  %d :", ev_mask, enable, port_no);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet Event Enable Settings\n");
#endif
                ev_mask = 0;
                rc = vtss_phy_ts_event_enable_get(inst, port_no, &ev_mask);
                printf ("Current 1588 Event Mask: 0x%x\n", ev_mask);

                continue;

           } else if (strcmp(command, "event_poll") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_event_t  ev_mask=0;
                int      loopCnt = 20;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet Event Enable Settings\n");
#endif
                rc = vtss_phy_ts_event_enable_get(inst, port_no, &ev_mask);

                printf ("VTSS_PHY_TS_INGR_ENGINE_ERR            0x01  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_PREAM_ERR          0x02  /**< Preamble too short to append timestamp */ \n");
                printf ("VTSS_PHY_TS_INGR_RW_FCS_ERR            0x04  /**< FCS error in ingress */ \n");
                printf ("VTSS_PHY_TS_EGR_ENGINE_ERR             0x08  /**< More than one engine find match */ \n");
                printf ("VTSS_PHY_TS_EGR_RW_FCS_ERR             0x10  /**< FCS error in egress */ \n");
                printf ("VTSS_PHY_TS_EGR_TIMESTAMP_CAPTURED     0x20  /**< Timestamp captured in Tx TSFIFO */ \n");
                printf ("VTSS_PHY_TS_EGR_FIFO_OVERFLOW          0x40  /**< Tx TSFIFO overflow */ \n");
                printf ("VTSS_PHY_TS_DATA_IN_RSRVD_FIELD        0x80  /**< Data in reserved Field */ \n");
                printf ("VTSS_PHY_TS_LTC_NEW_PPS_INTRPT         0x100 /**< New PPS pushed onto external PPS pin*/ \n");
                printf ("VTSS_PHY_TS_LTC_LOAD_SAVE_NEW_TOD      0x200 /**< New LTC value either loaded in to HW or saved into registers*/ \n");
                printf ("\n");
                printf ("Current 1588 Event Mask: 0x%x \n", ev_mask);
                printf ("\n");

                while (loopCnt > 0) {
                    miim_write(inst, port_no, 31, 0x10);   /* GPIO Pg */
                    miim_read(inst, port_no, 29, &value);  /* 29G - Global Status  */
                    miim_write(inst, port_no, 31, 0);      /* Std Page */
                    ev_mask = 0;
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                    fprintf (fp,"\nPoll Event \n");
#endif
                    rc = vtss_phy_ts_event_poll(inst, port_no, &ev_mask);
                    printf ("Port: %d; LoopCnt: %d;  rc: 0x%x;  Polling 29G: 0x%x;  1588 INT Events: 0x%x  \n", port_no, loopCnt, rc, value, ev_mask);
                    loopCnt--;
                }
                continue;

#endif /* end of  VTSS_CHIP_CU_PHY */

           } else if (strcmp(command, "ptp_get") == 0) {
                vtss_rc  rc;
                vtss_phy_timestamp_t    ts;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset (&ts, 0, sizeof(vtss_phy_timestamp_t));

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nGet PTP Time \n");
#endif
                rc = vtss_phy_ts_ptptime_get(inst, port_no, &ts);
                printf ("Port: %d;   PTP Time:Sec_Hi: %d,  Sec_Low: %d;  NanoSecs: %d \n", port_no, ts.seconds.high, ts.seconds.low, ts.nanoseconds);

                continue;

           } else if (strcmp(command, "ptp_arm_set") == 0) {
                vtss_rc  rc;
                vtss_phy_timestamp_t    ts;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset (&ts, 0, sizeof(vtss_phy_timestamp_t));

                printf ("Port_No: %d, Enter PTP_TIME Sec_Hi: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ts.seconds.high = atoi(value_str);

                printf ("Port_No: %d, Enter PTP_TIME Sec_Low: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ts.seconds.low = atol(value_str);

                printf ("Port_No: %d, Enter PTP_TIME NanoSecs: ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                ts.nanoseconds = atol(value_str);

                printf ("Port: %d;   Arming and Setting PTP Time: Sec_Hi: %d,  Sec_Low: %d;  NanoSecs: %d \n", port_no, ts.seconds.high, ts.seconds.low, ts.nanoseconds);
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nArm PTP_Time Trigger for Next LTC Rising Edge \n");
#endif
                rc = vtss_phy_ts_ptptime_arm(inst, port_no);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nConfigure PTP_Time for Next LTC Rising Edge \n");
#endif
                rc = vtss_phy_ts_ptptime_set(inst, port_no, &ts);

                continue;

           } else if (strcmp(command, "arm_set_done") == 0) {
                vtss_rc  rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                printf ("Port: %d;   Arming, Set, Done! PTP Time\n", port_no);
#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nArm PTP_Time Trigger for Next LTC Rising Edge \n");
#endif
                rc = vtss_phy_ts_ptptime_arm(inst, port_no);

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nPTP_Time_Set_Done  \n");
#endif
                rc = vtss_phy_ts_ptptime_set_done(inst, port_no);

                continue;

           } else if (strcmp(command, "ptp_load") == 0) {
                vtss_rc  rc;
                vtss_phy_timestamp_t    ts;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                memset (&ts, 0, sizeof(vtss_phy_timestamp_t));

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"\nPTP_Time_Load_Get  \n");
#endif
                rc = vtss_phy_ts_load_ptptime_get(inst, port_no, &ts);
                printf ("Port: %d;   LOAD Time: Sec_Hi: %d,  Sec_Low: %d;  NanoSecs: %d \n", port_no, ts.seconds.high, ts.seconds.low, ts.nanoseconds);

                continue;

           } else if (strcmp(command, "sig_get") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_fifo_sig_mask_t    sig_mask=0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                rc = vtss_phy_ts_fifo_sig_get(inst, port_no, &sig_mask);
                printf ("Src IP address:    VTSS_PHY_TS_FIFO_SIG_SRC_IP          = 0x01 \n");
                printf ("Dest IP address:   VTSS_PHY_TS_FIFO_SIG_DEST_IP         = 0x02 \n");
                printf ("Msg Type:          VTSS_PHY_TS_FIFO_SIG_MSG_TYPE        = 0x04 \n");
                printf ("Domain Number:     VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM      = 0x08 \n");
                printf ("Src Port ID:       VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  = 0x10 \n");
                printf ("PTP Frame Seq ID:  VTSS_PHY_TS_FIFO_SIG_SEQ_ID          = 0x20 \n");
                printf ("Dest MAC Addr:     VTSS_PHY_TS_FIFO_SIG_DEST_MAC        = 0x40 \n");
                printf ("Note: Signature Masks are OR'd together, so Multiple can be chosen \n\n");
                printf ("Port: %d;   Current TS Signatgure Mask: 0x%04x \n", port_no, sig_mask);

                continue;

           } else if (strcmp(command, "sig_set") == 0) {
                vtss_rc  rc;
                vtss_phy_ts_fifo_sig_mask_t    sig_mask=0;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }
                rc = vtss_phy_ts_fifo_sig_get(inst, port_no, &sig_mask);
                printf ("Src IP address:    VTSS_PHY_TS_FIFO_SIG_SRC_IP          = 0x01 \n");
                printf ("Dest IP address:   VTSS_PHY_TS_FIFO_SIG_DEST_IP         = 0x02 \n");
                printf ("Msg Type:          VTSS_PHY_TS_FIFO_SIG_MSG_TYPE        = 0x04 \n");
                printf ("Domain Number:     VTSS_PHY_TS_FIFO_SIG_DOMAIN_NUM      = 0x08 \n");
                printf ("Src Port ID:       VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID  = 0x10 \n");
                printf ("PTP Frame Seq ID:  VTSS_PHY_TS_FIFO_SIG_SEQ_ID          = 0x20 \n");
                printf ("Dest MAC Addr:     VTSS_PHY_TS_FIFO_SIG_DEST_MAC        = 0x40 \n");
                printf ("Note: Signature Masks are OR'd together, so Multiple can be chosen \n\n");
                printf ("Port: %d;   Current TS Signatgure Mask: 0x%x \n\n", port_no, sig_mask);

                printf ("Port_No: %d, Enter Signature Mask (in Hex): ", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                sig_mask = strtol(value_str, NULL, 16);

                rc = vtss_phy_ts_fifo_sig_set(inst, port_no, sig_mask);
                printf ("Port: %d;   Setting TS Signatgure Mask to: 0x%04x \n", port_no, sig_mask);

                continue;

           } else if (strcmp(command, "cb_install") == 0) {
                vtss_rc                 rc;
                void                   *appl_cntxt = NULL;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                /* Install the callback function to the PHY_TS_API */
                rc = vtss_phy_ts_fifo_read_install(inst, demo_ts_phy_fifo_read, appl_cntxt);
                if (rc < 0) {
                    printf("Error in installing fifo-read func \n");
                }

                rc = vtss_phy_ts_event_enable_set(inst, port_no, TRUE, 0x3F);
                if (rc < 0) {
                    printf("Error in enabling the event \n\r");
                }

                continue;

           } else if (strcmp(command, "read_fifo") == 0) {
                vtss_rc                 rc;

                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                /* Install the callback function to the PHY_TS_API */
                rc = vtss_phy_ts_fifo_empty(inst, port_no);
                if (rc < 0) {
                    printf("Error in vtss_phy_ts_fifo_empty trying fifo-read func \n");
                }

                continue;

#ifdef TESLA_ING_TS_ERRFIX

           } else if (strcmp(command, "run_oos") == 0) {
                vtss_rc                 rc;
                if (get_valid_port_no(&port_no, port_no_str) == FALSE) {
                    continue;
                }

                /* Note: fifo_conf declared at beginning of 1588 sub-section !! */

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"PHY_Start_of_OOS\n");
#endif
                rc = vtss_phy_ts_fifo_sig_get(inst, port_no, &sig_mask);
                printf("Sig_Mask: 0x%04x  for port %d\n", sig_mask, port_no);
                if (sig_mask < 0x30) {
                    printf("Sig_Mask is not compatable for OOS::FORCING Sig_Mask = 0x30 for port %d\n", port_no);
                    printf("This Over-ride is ONLY for Manually Calling/Testing of OOS Patch! Port_no:%d\n", port_no);
                    printf("Minimum Sig_Mask: VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID | VTSS_PHY_TS_FIFO_SIG_SEQ_ID\n");
                    sig_mask = VTSS_PHY_TS_FIFO_SIG_SOURCE_PORT_ID | VTSS_PHY_TS_FIFO_SIG_SEQ_ID; // 0x30
                    rc = vtss_phy_ts_fifo_sig_set(inst, port_no, sig_mask);
                }

                //fifo.eng_recov = VTSS_PHY_TS_PTP_ENGINE_ID_0;
                //fifo.eng_minE = VTSS_PHY_TS_OAM_ENGINE_ID_2B;
                printf ("Select Primary OOS Recovery Engine (Default: 0): Enter 0/1 for port  %d :", port_no);
                memset (&value_str[0], 0, sizeof(value_str));
                scanf("%s", &value_str[0]);
                if (value_str[0] == '1') {
                    fifo_conf.eng_recov = VTSS_PHY_TS_PTP_ENGINE_ID_1;
                }

               /* Reason for calling twice with engine-id is due to fact that API returns 'VTSS_RC_ERROR'
               only in case of OOS recovery failure and 'VTSS_RC_OK' is returned even in case of incomplete
               API execution. There is a chance of PTP-IP-ETH enabled on engine-1 & different encapsulation on
               engine 0 and it must be allowed to test in API. */
                if (vtss_phy_ts_tesla_tsp_fifo_sync(inst, port_no,(vtss_debug_printf_t)printf, &fifo_conf, &OOS) != VTSS_RC_OK) {
                    printf("\nERROR: FIFO sync API returned pre-maturely for port %d\n", port_no);
                } else {
                    printf("\nFIFO sync API returned VTSS_RC_OK for port %d\n", port_no);
                }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
                fprintf (fp,"PHY_END_of_OOS\n");
#endif
                continue;
#endif  /* TESLA_ING_TS_ERRFIX */
            } else {
                continue;
            }

#ifdef _INCLUDE_DEBUG_FILE_PRINT_
            fflush(fp);
#endif

    } // End of While(1) Loop

} // end of  vtss_appl_ts_demo_menu

#endif // End of 1588
