//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_control/gphy_ssc_pdi_def.xml
// Register File Name  : GPHY_SSC_PDI
// Register File Title : Control/Status registers of GPHY CDB SSC
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPHY_SSC_PDI_H
#define _GPHY_SSC_PDI_H

//! \defgroup GPHY_SSC_PDI Register File GPHY_SSC_PDI - Control/Status registers of GPHY CDB SSC
//! @{

//! Base Address of GPHY_SSC_PDI
#define GPHY_SSC_PDI_MODULE_BASE 0x00D20200u

//! \defgroup GPHY_SSC_PDI_SSC_CTRL Register GPHY_SSC_PDI_SSC_CTRL - SSC Control
//! @{

//! Register Offset (relative)
#define GPHY_SSC_PDI_SSC_CTRL 0x0
//! Register Offset (absolute) for 1st Instance GPHY_SSC_PDI
#define GPHY_SSC_PDI_GPHY_SSC_PDI_SSC_CTRL 0x00D20200u

//! Register Reset Value
#define GPHY_SSC_PDI_SSC_CTRL_RST 0x00000000u

//! Field EN - Enable
#define GPHY_SSC_PDI_SSC_CTRL_EN_POS 0
//! Field EN - Enable
#define GPHY_SSC_PDI_SSC_CTRL_EN_MASK 0x1u

//! Field DOWN - SSC DownSpread
#define GPHY_SSC_PDI_SSC_CTRL_DOWN_POS 1
//! Field DOWN - SSC DownSpread
#define GPHY_SSC_PDI_SSC_CTRL_DOWN_MASK 0x2u

//! Field SPREAD - Percentage of Spread Specification
#define GPHY_SSC_PDI_SSC_CTRL_SPREAD_POS 4
//! Field SPREAD - Percentage of Spread Specification
#define GPHY_SSC_PDI_SSC_CTRL_SPREAD_MASK 0x1F0u

//! Field DIV - SSC Divider
#define GPHY_SSC_PDI_SSC_CTRL_DIV_POS 12
//! Field DIV - SSC Divider
#define GPHY_SSC_PDI_SSC_CTRL_DIV_MASK 0xF000u

//! @}

//! \defgroup GPHY_SSC_PDI_SSC_SCALE Register GPHY_SSC_PDI_SSC_SCALE - SSC Scaling
//! @{

//! Register Offset (relative)
#define GPHY_SSC_PDI_SSC_SCALE 0x4
//! Register Offset (absolute) for 1st Instance GPHY_SSC_PDI
#define GPHY_SSC_PDI_GPHY_SSC_PDI_SSC_SCALE 0x00D20204u

//! Register Reset Value
#define GPHY_SSC_PDI_SSC_SCALE_RST 0x00000000u

//! Field GSCALE - SSC to GPHY IP Scaling
#define GPHY_SSC_PDI_SSC_SCALE_GSCALE_POS 0
//! Field GSCALE - SSC to GPHY IP Scaling
#define GPHY_SSC_PDI_SSC_SCALE_GSCALE_MASK 0xFFu

//! @}

//! @}

#endif
