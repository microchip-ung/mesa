/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPY211_REGS_H_
#define _GPY211_REGS_H_

#ifdef P31G_B0
#include <registers/p31g/aspa_cfg.h>
#include <registers/p31g/cgu_pdi.h>
//#include <registers/p31g/cgu_pdi_registers.h>
#include <registers/p31g/chipid.h>
#include <registers/p31g/eipe_eip_160s_e_32_classifier_control_packet.h>
#include <registers/p31g/eipe_eip_160s_e_32_classifier_debug.h>
#include <registers/p31g/eipe_eip_160s_e_32_classifier_various_control_regs.h>
#include <registers/p31g/eipe_eip_160s_e_32_flow_control_page0.h>
#include <registers/p31g/eipe_eip_160s_e_32_oppe.h>
#include <registers/p31g/eipe_eip_160s_e_32_sam_enable_ctrl.h>
#include <registers/p31g/eipe_eip_160s_e_32_sam_rules_page0.h>
#include <registers/p31g/eipe_eip_160s_e_32_stat_control.h>
#include <registers/p31g/eipe_eip_160s_e_32_stat_global.h>
#include <registers/p31g/eipe_eip_160s_e_32_stat_sa_page0.h>
#include <registers/p31g/eipe_eip_160s_e_32_stat_vlan.h>
#include <registers/p31g/eipe_eip_160s_e_32_system_control.h>
#include <registers/p31g/eipe_eip_201_eip201_registers.h>
#include <registers/p31g/eipe_eip160_eip62_eip62_registers.h>
#include <registers/p31g/eipi_eip_160s_i_32_cc_control.h>
#include <registers/p31g/eipi_eip_160s_i_32_cc_rules_page0.h>
#include <registers/p31g/eipi_eip_160s_i_32_classifier_control_packet.h>
#include <registers/p31g/eipi_eip_160s_i_32_classifier_debug.h>
#include <registers/p31g/eipi_eip_160s_i_32_classifier_various_control_regs.h>
#include <registers/p31g/eipi_eip_160s_i_32_flow_control_page0.h>
#include <registers/p31g/eipi_eip_160s_i_32_oppe.h>
#include <registers/p31g/eipi_eip_160s_i_32_sam_enable_ctrl.h>
#include <registers/p31g/eipi_eip_160s_i_32_sam_rules_page0.h>
#include <registers/p31g/eipi_eip_160s_i_32_stat_control.h>
#include <registers/p31g/eipi_eip_160s_i_32_stat_global.h>
#include <registers/p31g/eipi_eip_160s_i_32_stat_sa_page0.h>
#include <registers/p31g/eipi_eip_160s_i_32_stat_vlan.h>
#include <registers/p31g/eipi_eip_160s_i_32_system_control.h>
#include <registers/p31g/eipi_eip_201_eip201_registers.h>
#include <registers/p31g/eipi_eip160_eip62_eip62_registers.h>
//#include <registers/p31g/ethsw_flow25g_mii_pdi.h>
#include <registers/p31g/fxvl_pdi_registers.h>
#include <registers/p31g/gmacf_eqos_mac.h>
#include <registers/p31g/gmacl_eqos_mac.h>
#include <registers/p31g/gphy_cdb_pdi.h>
//#include <registers/p31g/gphy_fsci_pdi.h>
//#include <registers/p31g/gphy_ropll_pdi.h>
#include <registers/p31g/gphy_shell_pdi.h>
#include <registers/p31g/gphy_ssc_pdi.h>
#include <registers/p31g/gphycdb_fcsi.h>
#include <registers/p31g/gphydcpm_fcsi.h>
#include <registers/p31g/gphyxo_fcsi.h>
#include <registers/p31g/gpio_pdi_registers.h>
#include <registers/p31g/icu_pdi_registers.h>
#include <registers/p31g/led_bctrl_pdi_registers.h>
#include <registers/p31g/mspi_pdi_registers.h>
#include <registers/p31g/otp_pdi_registers.h>
#include <registers/p31g/p31g_mdio_pdi.h>
#include <registers/p31g/pm_pdi.h>
#include <registers/p31g/pmu_pdi_registers.h>
#include <registers/p31g/pvt_pdi_registers.h>
#include <registers/p31g/rcu_pdi_registers.h>
#include <registers/p31g/rcu_stky_pdi_registers.h>
#include <registers/p31g/s_sgmii_pcs_pdi.h>
#include <registers/p31g/sb_pdi_registers.h>
#include <registers/p31g/sgmii_macro_registers.h>
#include <registers/p31g/sgmii_phy_registers.h>
#include <registers/p31g/sgmii_shell_pdi_registers.h>
#include <registers/p31g/smdio_pdi_smdio_registers.h>
//#include <registers/p31g/sspi_pdi_registers.h>
#include <registers/p31g/tbi_pdi.h>
#include <registers/p31g/top_pdi_registers.h>
#include <registers/p31g/uart_pdi_registers.h>
#endif /* P31G_B0 */

#ifdef P34X_A0
#include <registers/p34x/aspa_cfg.h>
#include <registers/p34x/cgu_pdi.h>
//#include <registers/p34x/cgu_pdi_registers.h>
#include <registers/p34x/chipid.h>
#include <registers/p34x/eipe_eip_160s_e_32_classifier_control_packet.h>
#include <registers/p34x/eipe_eip_160s_e_32_classifier_debug.h>
#include <registers/p34x/eipe_eip_160s_e_32_classifier_various_control_regs.h>
#include <registers/p34x/eipe_eip_160s_e_32_flow_control_page0.h>
#include <registers/p34x/eipe_eip_160s_e_32_oppe.h>
#include <registers/p34x/eipe_eip_160s_e_32_sam_enable_ctrl.h>
#include <registers/p34x/eipe_eip_160s_e_32_sam_rules_page0.h>
#include <registers/p34x/eipe_eip_160s_e_32_stat_control.h>
#include <registers/p34x/eipe_eip_160s_e_32_stat_global.h>
#include <registers/p34x/eipe_eip_160s_e_32_stat_sa_page0.h>
#include <registers/p34x/eipe_eip_160s_e_32_stat_vlan.h>
#include <registers/p34x/eipe_eip_160s_e_32_system_control.h>
#include <registers/p34x/eipe_eip_201_eip201_registers.h>
#include <registers/p34x/eipe_eip160_eip62_eip62_registers.h>
#include <registers/p34x/eipi_eip_160s_i_32_cc_control.h>
#include <registers/p34x/eipi_eip_160s_i_32_cc_rules_page0.h>
#include <registers/p34x/eipi_eip_160s_i_32_classifier_control_packet.h>
#include <registers/p34x/eipi_eip_160s_i_32_classifier_debug.h>
#include <registers/p34x/eipi_eip_160s_i_32_classifier_various_control_regs.h>
#include <registers/p34x/eipi_eip_160s_i_32_flow_control_page0.h>
#include <registers/p34x/eipi_eip_160s_i_32_oppe.h>
#include <registers/p34x/eipi_eip_160s_i_32_sam_enable_ctrl.h>
#include <registers/p34x/eipi_eip_160s_i_32_sam_rules_page0.h>
#include <registers/p34x/eipi_eip_160s_i_32_stat_control.h>
#include <registers/p34x/eipi_eip_160s_i_32_stat_global.h>
#include <registers/p34x/eipi_eip_160s_i_32_stat_sa_page0.h>
//#include <registers/p34x/eipi_eip_160s_i_32_stat_vlan.h>
#include <registers/p34x/eipi_eip_160s_i_32_system_control.h>
#include <registers/p34x/eipi_eip_201_eip201_registers.h>
#include <registers/p34x/eipi_eip160_eip62_eip62_registers.h>
//#include <registers/p34x/ethsw_flow25g_mii_pdi.h>
#include <registers/p34x/fxvl_pdi_registers.h>
#include <registers/p34x/gmacf_eqos_mac.h>
#include <registers/p34x/gmacl_eqos_mac.h>
#include <registers/p34x/gphy_cdb_pdi.h>
//#include <registers/p34x/gphy_fsci_pdi.h>
//#include <registers/p34x/gphy_ropll_pdi.h>
#include <registers/p34x/gphy_shell_pdi.h>
#include <registers/p34x/gphy_ssc_pdi.h>
#include <registers/p34x/gphycdb_fcsi.h>
#include <registers/p34x/gphydcpm_fcsi.h>
#include <registers/p34x/gphyxo_fcsi.h>
#include <registers/p34x/gpio_pdi_registers.h>
//#include <registers/p34x/icu_pdi_registers.h>
#include <registers/p34x/led_bctrl_pdi_registers.h>
#include <registers/p34x/mspi_pdi_registers.h>
#include <registers/p34x/otp_pdi_registers.h>
#include <registers/p34x/p31g_mdio_pdi.h>
#include <registers/p34x/pm_pdi.h>
//#include <registers/p34x/pmu_pdi_registers.h>
#include <registers/p34x/pvt_pdi_registers.h>
#include <registers/p34x/rcu_pdi_registers.h>
#include <registers/p34x/rcu_stky_pdi_registers.h>
#include <registers/p34x/s_sgmii_pcs_pdi.h>
#include <registers/p34x/sb_pdi_registers.h>
#include <registers/p34x/sgmii_macro_registers.h>
#include <registers/p34x/sgmii_phy_registers.h>
#include <registers/p34x/sgmii_shell_pdi_registers.h>
#include <registers/p34x/slice_cgu_pdi_registers.h>
#include <registers/p34x/slice_ctrl_pdi_registers.h>
#include <registers/p34x/slice_icu_pdi_registers.h>
#include <registers/p34x/slice_lp_pdi_registers.h>
#include <registers/p34x/smdio_pdi_smdio_registers.h>
//#include <registers/p34x/sspi_pdi_registers.h>
#include <registers/p34x/tbi_pdi.h>
#include <registers/p34x/top_pdi_registers.h>
#include <registers/p34x/uart_pdi_registers.h>
#include <registers/p34x/usxgmii_pdi_registers.h>
#endif /* P34X_A0 */

#endif /* _GPY211_REGS_H_ */
