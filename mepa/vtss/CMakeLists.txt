

set(inc_mepa ../../me/include ../include)

set(src_vtss src/vtss.c
             src/vtss_ts.c
             src/vtss_macsec.c
             src/vtss_stubs.c
             src/common/vtss_phy_common.c
             src/phy_1g/vtss_phy_init_scripts.c
             src/phy_1g/vtss_phy_veriphy.c
             src/phy_1g/vtss_phy.c
             src/macsec/vtss_macsec_api.c
             src/phy_10g/vtss_venice_c_sd10g65_setup.c
             src/phy_10g/vtss_phy_10g_malibu.c
             src/phy_10g/vtss_malibu_b_f2df_df2f_sd10g65_setup.c
             src/phy_10g/vtss_venice_c_f2df_sd10g65_setup.c
             src/phy_10g/vtss_malibu_b_host_pma_sd10g65_setup.c
             src/phy_10g/vtss_malibu_line_pma_sd10g65_setup.c
             src/phy_10g/vtss_phy_10g.c
             src/phy_10g/vtss_phy_10g_api.c
             src/phy_10g/vtss_wis_api.c
             src/phy_10g/vtss_malibu_b_pll5g_setup.c
             src/phy_10g/vtss_malibu_f2df_df2f_sd10g65_setup.c
             src/phy_10g/vtss_malibu_host_pma_sd10g65_setup.c
             src/phy_10g/vtss_phy_10g_venice.c
             src/phy_10g/vtss_malibu_b_line_pma_sd10g65_setup.c
             src/phy_10g/vtss_venice_f2df_sd10g65_setup.c
             src/phy_10g/vtss_pll5g_procs.c
             src/phy_10g/vtss_sd10g65_procs.c
             src/phy_10g/vtss_sd10g65_apc_procs.c
             src/ts/vtss_phy_ts_api.c
             src/ts/vtss_phy_ewis.c
             src/ts/vtss_phy_ts_util.c)
set(inc_vtss include)

MEPA_DRV(LIB_NAME mepa_drv_vtss
         SRCS     ${src_vtss}
         INCL_PUB ${inc_mepa}
         INCL_PRI ${inc_vtss})

MEPA_DRV(LIB_NAME mepa_drv_vtss_10g_only
         DEFS     -DVTSS_OPT_PHY_1G=0 -DVTSS_OPT_PHY_10G=1
         SRCS     ${src_vtss}
         INCL_PUB ${inc_mepa}
         INCL_PRI ${inc_vtss})

MEPA_DRV(LIB_NAME mepa_drv_vtss_ts
         DEFS     -DVTSS_OPT_PHY_TIMESTAMP=1
         SRCS     ${src_vtss}
         INCL_PUB ${inc_mepa}
         INCL_PRI ${inc_vtss})

MEPA_DRV(LIB_NAME mepa_drv_vtss_10g_ts
         DEFS     -DVTSS_OPT_PHY_10G=1 -DVTSS_OPT_PHY_TIMESTAMP=1
         SRCS     ${src_vtss}
         INCL_PUB ${inc_mepa}
         INCL_PRI ${inc_vtss})

MEPA_DRV(LIB_NAME mepa_drv_vtss_10g_macsec_ts
         DEFS     -DVTSS_OPT_PHY_10G=1 -DVTSS_OPT_PHY_MACSEC=1 -DVTSS_OPT_PHY_TIMESTAMP=1
         SRCS     ${src_vtss}
         INCL_PUB ${inc_mepa}
         INCL_PRI ${inc_vtss})

set(mepa_vtss_custom_defs)

option(MEPA_vtss_opt_1g      "Compile vtss family with 1G support" ON)
if (${MEPA_vtss_opt_1g})
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_1G=1)
else()
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_1G=0)
endif()

option(MEPA_vtss_opt_10g     "Compile vtss family with 10G support" OFF)
if (${MEPA_vtss_opt_10g})
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_10G=1)
else()
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_10G=0)
endif()

option(MEPA_vtss_opt_ts      "Compile vtss family with time-stamp support" OFF)
if (${MEPA_vtss_opt_ts})
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_TIMESTAMP=1)
else()
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_TIMESTAMP=0)
endif()

option(MEPA_vtss_opt_macsec  "Compile vtss family with macsec support" OFF)
if (${MEPA_vtss_opt_macsec})
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_MACSEC=1)
else()
    set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_MACSEC=0)
endif()

set(MEPA_vtss_opt_cnt 64 CACHE STRING "Max number of ports supported by the vtss lib")
set(mepa_vtss_custom_defs ${mepa_vtss_custom_defs} -DVTSS_OPT_PHY_PORT_COUNT=${MEPA_vtss_opt_cnt})

MEPA_DRV(LIB_NAME mepa_drv_vtss_custom
         DEFS     ${mepa_vtss_custom_defs}
         SRCS     ${src_vtss}
         INCL_PUB ${inc_mepa}
         INCL_PRI ${inc_vtss})

option(MEPA_vtss "Add VTSS family support in libmeba" OFF)
if (${MEPA_vtss})
    set(mepa_drvs ${mepa_drvs} mepa_drv_vtss_custom CACHE INTERNAL "")
    set(mepa_defs ${mepa_defs} -DMEPA_HAS_VTSS CACHE INTERNAL "")
endif()

