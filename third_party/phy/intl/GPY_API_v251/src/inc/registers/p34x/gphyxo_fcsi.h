//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p34x/p34x_chip/v_emouchel.priv.p34x_chip.registers/ipg_lsd/lsd_sys/source_32b/xml/reg_files/chip_control/GPHYXO_FCSI.xml
// Register File Name  : GPHYXO_FCSI
// Register File Title : XO FCSI-Interface
// Register Width      : 32
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _GPHYXO_FCSI_H
#define _GPHYXO_FCSI_H

//! \defgroup GPHYXO_FCSI Register File GPHYXO_FCSI - XO FCSI-Interface
//! @{

//! Base Address of GPHYXO_FCSI
#define GPHYXO_FCSI_MODULE_BASE 0x00D28080u

//! \defgroup GPHYXO_FCSI_XOCFG Register GPHYXO_FCSI_XOCFG - XO Configuration Register
//! @{

//! Register Offset (relative)
#define GPHYXO_FCSI_XOCFG 0x0
//! Register Offset (absolute) for 1st Instance GPHYXO_FCSI
#define GPHYXO_FCSI_GPHYXO_FCSI_XOCFG 0x00D28080u

//! Register Reset Value
#define GPHYXO_FCSI_XOCFG_RST 0x00000003u

//! Field RUNDETEN - Run Detection Enable
#define GPHYXO_FCSI_XOCFG_RUNDETEN_POS 0
//! Field RUNDETEN - Run Detection Enable
#define GPHYXO_FCSI_XOCFG_RUNDETEN_MASK 0x1u
//! Constant DISBLE - DISABLE (INIT)
#define CONST_GPHYXO_FCSI_XOCFG_RUNDETEN_DISBLE 0x0
//! Constant ENABLE - ENABLE
#define CONST_GPHYXO_FCSI_XOCFG_RUNDETEN_ENABLE 0x1

//! Field FILTERCFG - Filter Configuration
#define GPHYXO_FCSI_XOCFG_FILTERCFG_POS 1
//! Field FILTERCFG - Filter Configuration
#define GPHYXO_FCSI_XOCFG_FILTERCFG_MASK 0x2u

//! Field HYSTSEL - Hysteresis Selection
#define GPHYXO_FCSI_XOCFG_HYSTSEL_POS 2
//! Field HYSTSEL - Hysteresis Selection
#define GPHYXO_FCSI_XOCFG_HYSTSEL_MASK 0x4u

//! Field AMPLREG - Amplitude Regulation
#define GPHYXO_FCSI_XOCFG_AMPLREG_POS 3
//! Field AMPLREG - Amplitude Regulation
#define GPHYXO_FCSI_XOCFG_AMPLREG_MASK 0xF8u

//! Field HYSTVAL - Hystersis Value
#define GPHYXO_FCSI_XOCFG_HYSTVAL_POS 8
//! Field HYSTVAL - Hystersis Value
#define GPHYXO_FCSI_XOCFG_HYSTVAL_MASK 0x300u
//! Constant V100M - 100MV HYSTERESIS
#define CONST_GPHYXO_FCSI_XOCFG_HYSTVAL_V100M 0x0
//! Constant V200M - 200MV HYSTERESIS
#define CONST_GPHYXO_FCSI_XOCFG_HYSTVAL_V200M 0x1
//! Constant V300M - 300MV HYSTERESIS
#define CONST_GPHYXO_FCSI_XOCFG_HYSTVAL_V300M 0x2

//! Field XT1TSTCLK - Test Clock at XT1 pin
#define GPHYXO_FCSI_XOCFG_XT1TSTCLK_POS 10
//! Field XT1TSTCLK - Test Clock at XT1 pin
#define GPHYXO_FCSI_XOCFG_XT1TSTCLK_MASK 0x400u
//! Constant DISABLE - FUNCTION IS DISABLED
#define CONST_GPHYXO_FCSI_XOCFG_XT1TSTCLK_DISABLE 0x0
//! Constant ENABLE - FUNCTION IS ENABLED
#define CONST_GPHYXO_FCSI_XOCFG_XT1TSTCLK_ENABLE 0x1

//! Field FORCEDIGCLK - Force digital clock output
#define GPHYXO_FCSI_XOCFG_FORCEDIGCLK_POS 11
//! Field FORCEDIGCLK - Force digital clock output
#define GPHYXO_FCSI_XOCFG_FORCEDIGCLK_MASK 0x800u
//! Constant DISABLE - FUNCTION IS DISABLED
#define CONST_GPHYXO_FCSI_XOCFG_FORCEDIGCLK_DISABLE 0x0
//! Constant ENABLE - FUNCTION IS ENABLED
#define CONST_GPHYXO_FCSI_XOCFG_FORCEDIGCLK_ENABLE 0x1

//! Field RES0 - Reserved ReadWrite
#define GPHYXO_FCSI_XOCFG_RES0_POS 12
//! Field RES0 - Reserved ReadWrite
#define GPHYXO_FCSI_XOCFG_RES0_MASK 0xF000u

//! @}

//! \defgroup GPHYXO_FCSI_XOSTAT Register GPHYXO_FCSI_XOSTAT - XO Status Register
//! @{

//! Register Offset (relative)
#define GPHYXO_FCSI_XOSTAT 0x4
//! Register Offset (absolute) for 1st Instance GPHYXO_FCSI
#define GPHYXO_FCSI_GPHYXO_FCSI_XOSTAT 0x00D28084u

//! Register Reset Value
#define GPHYXO_FCSI_XOSTAT_RST 0x00000000u

//! Field OSCRUN - Oscillator Running
#define GPHYXO_FCSI_XOSTAT_OSCRUN_POS 0
//! Field OSCRUN - Oscillator Running
#define GPHYXO_FCSI_XOSTAT_OSCRUN_MASK 0x1u

//! Field CLKACT - Clock Active
#define GPHYXO_FCSI_XOSTAT_CLKACT_POS 1
//! Field CLKACT - Clock Active
#define GPHYXO_FCSI_XOSTAT_CLKACT_MASK 0x2u

//! @}

//! \defgroup GPHYXO_FCSI_VREGCFG Register GPHYXO_FCSI_VREGCFG - Voltage regulator configuration register
//! @{

//! Register Offset (relative)
#define GPHYXO_FCSI_VREGCFG 0x8
//! Register Offset (absolute) for 1st Instance GPHYXO_FCSI
#define GPHYXO_FCSI_GPHYXO_FCSI_VREGCFG 0x00D28088u

//! Register Reset Value
#define GPHYXO_FCSI_VREGCFG_RST 0x00000000u

//! Field RES0 - Reserved ReadWrite
#define GPHYXO_FCSI_VREGCFG_RES0_POS 0
//! Field RES0 - Reserved ReadWrite
#define GPHYXO_FCSI_VREGCFG_RES0_MASK 0x1u

//! Field VREGLP - Vreg Low Power Enable
#define GPHYXO_FCSI_VREGCFG_VREGLP_POS 1
//! Field VREGLP - Vreg Low Power Enable
#define GPHYXO_FCSI_VREGCFG_VREGLP_MASK 0x2u
//! Constant NORMAL - NORMAL OPERATION.
#define CONST_GPHYXO_FCSI_VREGCFG_VREGLP_NORMAL 0x0
//! Constant LOWPOWER - LOW POWER OPERATION.
#define CONST_GPHYXO_FCSI_VREGCFG_VREGLP_LOWPOWER 0x1

//! Field VREGPROG - Vreg Voltage Programming
#define GPHYXO_FCSI_VREGCFG_VREGPROG_POS 2
//! Field VREGPROG - Vreg Voltage Programming
#define GPHYXO_FCSI_VREGCFG_VREGPROG_MASK 0x1Cu
//! Constant V1V80 - 1.80 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V80 0x0
//! Constant V1V83 - 1.83 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V83 0x1
//! Constant V1V86 - 1.86 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V86 0x2
//! Constant V1V89 - 1.89 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V89 0x3
//! Constant V1V68 - 1.68 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V68 0x4
//! Constant V1V71 - 1.71 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V71 0x5
//! Constant V1V74 - 1.74 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V74 0x6
//! Constant V1V77 - 1.77 V REG. OUTPUT VOLTAGE
#define CONST_GPHYXO_FCSI_VREGCFG_VREGPROG_V1V77 0x7

//! Field RES1 - Reserved ReadWrite
#define GPHYXO_FCSI_VREGCFG_RES1_POS 5
//! Field RES1 - Reserved ReadWrite
#define GPHYXO_FCSI_VREGCFG_RES1_MASK 0x7FE0u

//! Field OBSEN - XO VREG1V8 Observation Enabled
#define GPHYXO_FCSI_VREGCFG_OBSEN_POS 15
//! Field OBSEN - XO VREG1V8 Observation Enabled
#define GPHYXO_FCSI_VREGCFG_OBSEN_MASK 0x8000u
//! Constant DISCONNECTED - DISCONNECTED FROM OBS.BUS (INIT)
#define CONST_GPHYXO_FCSI_VREGCFG_OBSEN_DISCONNECTED 0x0
//! Constant CONNECTED - CONNECTED
#define CONST_GPHYXO_FCSI_VREGCFG_OBSEN_CONNECTED 0x1

//! @}

//! \defgroup GPHYXO_FCSI_VERSION Register GPHYXO_FCSI_VERSION - Version Register
//! @{

//! Register Offset (relative)
#define GPHYXO_FCSI_VERSION 0xC
//! Register Offset (absolute) for 1st Instance GPHYXO_FCSI
#define GPHYXO_FCSI_GPHYXO_FCSI_VERSION 0x00D2808Cu

//! Register Reset Value
#define GPHYXO_FCSI_VERSION_RST 0x00000100u

//! Field MIN - Minor Version
#define GPHYXO_FCSI_VERSION_MIN_POS 0
//! Field MIN - Minor Version
#define GPHYXO_FCSI_VERSION_MIN_MASK 0xFFu

//! Field MAJ - Major Version
#define GPHYXO_FCSI_VERSION_MAJ_POS 8
//! Field MAJ - Major Version
#define GPHYXO_FCSI_VERSION_MAJ_MASK 0xFF00u

//! @}

//! @}

#endif
