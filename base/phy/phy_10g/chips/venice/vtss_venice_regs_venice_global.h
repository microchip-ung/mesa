// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_VENICE_REGS_VENICE_GLOBAL_H_
#define _VTSS_VENICE_REGS_VENICE_GLOBAL_H_


#include "vtss_venice_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a VENICE_GLOBAL
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a VENICE_GLOBAL:Device_Info
 *
 * Device ID and Revision
 */


/** 
 * \brief Device ID
 *
 * \details
 * Device ID
 *
 * Register: \a VENICE_GLOBAL:Device_Info:Device_ID
 */
#define VTSS_VENICE_GLOBAL_Device_Info_Device_ID  VTSS_IOREG(0x1e, 0, 0x0000)

/** 
 * \brief
 * This is the device ID register.
 * The register contains 0x8489 for the VSC8489 products
 * The register contains 0x8490 for the VSC8490 products
 * The register contains 0x8491 for the VSC8491 products (the 0x8491 is
 * modified by the TEST1 pin status)

 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_Device_Info_Device_ID . Device_ID
 */
#define  VTSS_F_VENICE_GLOBAL_Device_Info_Device_ID_Device_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_Device_Info_Device_ID_Device_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_Device_Info_Device_ID_Device_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device Revision
 *
 * \details
 * Device Revision
 *
 * Register: \a VENICE_GLOBAL:Device_Info:Device_Revision
 */
#define VTSS_VENICE_GLOBAL_Device_Info_Device_Revision  VTSS_IOREG(0x1e, 0, 0x0001)

/** 
 * \brief
 * This is the revision number register.
 * The register contains 0x0 for rev A devices for all SKUs
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_Device_Info_Device_Revision . Device_Revision
 */
#define  VTSS_F_VENICE_GLOBAL_Device_Info_Device_Revision_Device_Revision(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_GLOBAL_Device_Info_Device_Revision_Device_Revision     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_GLOBAL_Device_Info_Device_Revision_Device_Revision(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a VENICE_GLOBAL:Block_Level_Software_Reset
 *
 * Not documented
 */


/** 
 * \brief Block Level Software Reset
 *
 * \details
 * Register: \a VENICE_GLOBAL:Block_Level_Software_Reset:Block_Level_Software_Reset
 */
#define VTSS_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset  VTSS_IOREG(0x1e, 0, 0x0002)

/** 
 * \brief
 * Reset the datapath and configuration registers in channel 1.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Channel_1
 */
#define  VTSS_F_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Channel_1  VTSS_BIT(9)

/** 
 * \brief
 * Reset the datapath and configuration registers in channel 0.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Channel_0
 */
#define  VTSS_F_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Channel_0  VTSS_BIT(8)

/** 
 * \brief
 * Reset the TWS-slave interface.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_TWS_Slave
 */
#define  VTSS_F_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_TWS_Slave  VTSS_BIT(5)

/** 
 * \brief
 * Reset the MDIO interface.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_MDIO
 */
#define  VTSS_F_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_MDIO  VTSS_BIT(3)

/** 
 * \brief
 * Reset the SPI interface.  This is the SPI interface available to read
 * and write any register, not the push-out SPI interface dedicated to
 * extracting 1588 timestamp data.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_SPI
 */
#define  VTSS_F_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_SPI  VTSS_BIT(2)

/** 
 * \brief
 * Reset the datapath in both channels and all configuration registers
 * except those used for global configuration.	The GPIO pin functions are
 * not modified since global configuration registers are not reset to
 * default settings.  The global registers consist of general chip
 * configuration registers plus registers for the RCOMP, Sync_Eth, host
 * side PLL and line side PLL logic blocks.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Chip
 */
#define  VTSS_F_VENICE_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Chip  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:Data_Switches_Clock_Control
 *
 * Data Switches and Clock Control
 */


/** 
 * \brief Data Switches and Clock Control
 *
 * \details
 * Data Switches and Clock Control
 *
 * Register: \a VENICE_GLOBAL:Data_Switches_Clock_Control:Data_Switches_Clock_Control
 */
#define VTSS_VENICE_GLOBAL_Data_Switches_Clock_Control_Data_Switches_Clock_Control  VTSS_IOREG(0x1e, 0, 0x0003)

/** 
 * \brief
 * Selects the source of the data transmitted from channel 1's client-side
 * interface.
 *
 * \details 
 * 0: Channel 0 PMA input data is transmitted.
 * 1: Channel 1 PMA input data is transmitted.
 *
 * Field: VTSS_VENICE_GLOBAL_Data_Switches_Clock_Control_Data_Switches_Clock_Control . XAUI1_DOUT_SRC
 */
#define  VTSS_F_VENICE_GLOBAL_Data_Switches_Clock_Control_Data_Switches_Clock_Control_XAUI1_DOUT_SRC  VTSS_BIT(5)

/** 
 * \brief
 * Selects the source of the data transmitted from channel 0's client-side
 * interface.
 *
 * \details 
 * 0: Channel 0 PMA input data is transmitted.
 * 1: Channel 1 PMA input data is transmitted.
 *
 * Field: VTSS_VENICE_GLOBAL_Data_Switches_Clock_Control_Data_Switches_Clock_Control . XAUI0_DOUT_SRC
 */
#define  VTSS_F_VENICE_GLOBAL_Data_Switches_Clock_Control_Data_Switches_Clock_Control_XAUI0_DOUT_SRC  VTSS_BIT(4)

/** 
 * \brief
 * Selects the source of the data transmitted from the PMA interfaces.
 *
 * \details 
 * 0: Channel 0 client-side input data is transmitted out PMA channel 0. 
 * Channel 1 client-side input data is transmitted out PMA channel 1.
 * 1: Channel 0 client-side input data is transmitted out PMA channel 1. 
 * Channel 1 client-side input data is transmitted out PMA channel 0.
 *
 * Field: VTSS_VENICE_GLOBAL_Data_Switches_Clock_Control_Data_Switches_Clock_Control . PMA_DOUT_SRC
 */
#define  VTSS_F_VENICE_GLOBAL_Data_Switches_Clock_Control_Data_Switches_Clock_Control_PMA_DOUT_SRC  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:Pin_Status
 *
 * Not documented
 */


/** 
 * \brief Pin Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:Pin_Status:Pin_Status
 */
#define VTSS_VENICE_GLOBAL_Pin_Status_Pin_Status  VTSS_IOREG(0x1e, 0, 0x0004)

/** 
 * \brief
 * State of MODE1 pin
 *
 * \details 
 * 0: Logic low
 * 1: Logic high
 *
 * Field: VTSS_VENICE_GLOBAL_Pin_Status_Pin_Status . MODE1_Pin_State
 */
#define  VTSS_F_VENICE_GLOBAL_Pin_Status_Pin_Status_MODE1_Pin_State  VTSS_BIT(1)

/** 
 * \brief
 * State of MODE0 pin
 *
 * \details 
 * 0: Logic low
 * 1: Logic high
 *
 * Field: VTSS_VENICE_GLOBAL_Pin_Status_Pin_Status . MODE0_Pin_State
 */
#define  VTSS_F_VENICE_GLOBAL_Pin_Status_Pin_Status_MODE0_Pin_State  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:Intr_Pend_Deassert_Time
 *
 * Not documented
 */


/** 
 * \brief Interrupt Pending Deassertion Time
 *
 * \details
 * Register: \a VENICE_GLOBAL:Intr_Pend_Deassert_Time:Intr_Pend_Deassert_Time
 */
#define VTSS_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time  VTSS_IOREG(0x1e, 0, 0x0023)

/** 
 * \brief
 * Specifies the minimum duration a General Purpose Input (GPI) interrupt
 * pending register will be deasserted once it is cleared.  Any interrupt
 * event that happens during the time frame after clearing the GPI
 * interrupt_pending register will not be discarded.  Re-assertion of the
 * interrupt_pending register will just be delayed until the time specified
 * in this register has expired.  The minimum de-assertion time is the
 * value in this register * 12.8 nS.  The interrupt_pending registers for
 * all General Purpose Inputs use this common value.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time . GPIs_Min_Intr_Pend_Deassert_Time
 */
#define  VTSS_F_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time_GPIs_Min_Intr_Pend_Deassert_Time(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time_GPIs_Min_Intr_Pend_Deassert_Time     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time_GPIs_Min_Intr_Pend_Deassert_Time(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Specifies the minimum duration an interrupt pending register in each
 * channel will be deasserted once it is cleared.  Any interrupt event that
 * happens during the time frame after clearing an interrupt_pending
 * register will not be discarded.  Re-assertion of the interrupt_pending
 * register will just be delayed until the time specified in this register
 * has expired.   The minimum de-assertion time is the value in this
 * register * 12.8 nS.	With the exception of register bit
 * Vendor_Specific_LOPC_Status.Interrupt_pending_bit, all interrupt_pending
 * registers in both channels use this common value.
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time . Channels_Min_Intr_Pend_Deassert_Time
 */
#define  VTSS_F_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time_Channels_Min_Intr_Pend_Deassert_Time(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time_Channels_Min_Intr_Pend_Deassert_Time     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_Intr_Pend_Deassert_Time_Intr_Pend_Deassert_Time_Channels_Min_Intr_Pend_Deassert_Time(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a VENICE_GLOBAL:GPIO_Cfg_Stat1
 *
 * GPIO Configuration and Status Register Group 1
 */


/** 
 * \brief GPIO 0 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_0_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status  VTSS_IOREG(0x1e, 0, 0x0100)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_0.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . Trad_GPIO_0_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_Trad_GPIO_0_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_0.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . Trad_GPIO_0_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_Trad_GPIO_0_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_Trad_GPIO_0_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_Trad_GPIO_0_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_0.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . Trad_GPIO_0_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_Trad_GPIO_0_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_0.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . GPI_Intr_Pend0
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPI_Intr_Pend0  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status0.
 * Indicates the present value of the GPIO_0 pin.
 *
 * \details 
 * 0: Present Value of GPIO_0 pin is 0
 * 1: Present Value of GPIO_0 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . GPI_Status0
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPI_Status0  VTSS_BIT(10)

/** 
 * \brief
 * Enables the GPIO pin to be used as a PMTICK strobe source for the WIS
 * statistical counters.  Bit usage applies when the pin is configured as a
 * general purpose input (bits [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of pin as a PMTICK input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . PMTICK_Enable_1
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_PMTICK_Enable_1  VTSS_BIT(9)

/** 
 * \brief
 * Module Status Input Enable for channel 0.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of pin as a module status input for channel 0 and associated
 * interrupt pending generation in EWIS_INTR_PEND2.MODULE_PEND is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . Module_Stat_Input_En_Chan0
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_Module_Stat_Input_En_Chan0  VTSS_BIT(8)

/** 
 * \brief
 * GPIO_0 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt B from channel 0
 * 001: WIS interrupt B from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt B from both channels
 * 101: Logical OR of WIS interrupt B from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . GPIO_0_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_0 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . GPIO_0_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_0 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: Transmit PPS 0
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status . GPIO_0_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config_Status_GPIO_0_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 0 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_0_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2  VTSS_IOREG(0x1e, 0, 0x0101)

/** 
 * \brief
 * Data selected by GPIO_0_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2 . GPIO_0_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2_GPIO_0_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Enables pin to be used as an input for the PPS_0 signal.  Bit usage
 * applies when the pin is configured at GPIO_0_Config_Status register bits
 * [2:0]=100.
 *
 * \details 
 * Use of pin as PPS_0 input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2 . PPS_0_Enable
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2_PPS_0_Enable  VTSS_BIT(8)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_0 when
 * GPIO_0_Config_Status.GPIO_0_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[0]
 * 0xFC: ch0_debug_data[0]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch0_rosi_frm_pulse
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: rcomp_busy
 * 0xDE: ref_clk_sel[2]
 * 0xDD: ref_clk_sel[1]
 * 0xDC: ref_clk_sel[0]
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: l_pll5g_status_calibration_done
 * 0xD8: h_pll5g_status_calibration_done
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_kr_active
 * 0xD0: ch0_kr_active
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: ch1_rx_xgmii_clk_en_client_1g
 * 0xCC: ch0_rx_xgmii_clk_en_client_1g
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: ch1_tx_xgmii_clk_en_client_1g
 * 0xC8: ch0_tx_xgmii_clk_en_client_1g
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: ch1_rx_xgmii_clk_en_line_1g
 * 0xC4: ch0_rx_xgmii_clk_en_line_1g
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: ch1_tx_xgmii_clk_en_line_1g
 * 0xC0: ch0_tx_xgmii_clk_en_line_1g
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: ch1_rx_pcs_pause
 * 0xBC: ch0_rx_pcs_pause
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: ch1_tx_pcs_pause
 * 0xB8: ch0_tx_pcs_pause
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: ch1_rx_wis_pause
 * 0xB4: ch0_rx_wis_pause
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: ch1_tx_wis_pause
 * 0xB0: ch0_tx_wis_pause
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_dft_tx_ena
 * 0xAC: ch0_dft_tx_ena
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: Reserved
 * 0xA8: Reserved
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_ewis_fr_wordpos[2]
 * 0xA4: ch1_ewis_fr_wordpos[1]
 * 0xA3: ch1_ewis_fr_wordpos[0]
 * 0xA2: ch0_ewis_fr_wordpos[2]
 * 0xA1: ch0_ewis_fr_wordpos[1]
 * 0xA0: ch0_ewis_fr_wordpos[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pma_l3_control
 * 0x9C: ch0_pma_l3_control
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: Reserved
 * 0x98: Reserved
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_ewis_fr_bitpos[2]
 * 0x94: ch1_ewis_fr_bitpos[1]
 * 0x93: ch1_ewis_fr_bitpos[0]
 * 0x92: ch0_ewis_fr_bitpos[2]
 * 0x91: ch0_ewis_fr_bitpos[1]
 * 0x90: ch0_ewis_fr_bitpos[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_enable_tpg
 * 0x8C: ch0_enable_tpg
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_macsec_igr_pred_var_lat[2]
 * 0x84: ch1_macsec_igr_pred_var_lat[1]
 * 0x83: ch1_macsec_igr_pred_var_lat[0]
 * 0x82: ch0_macsec_igr_pred_var_lat[2]
 * 0x81: ch0_macsec_igr_pred_var_lat[1]
 * 0x80: ch0_macsec_igr_pred_var_lat[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2 . GPIO_0_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2_GPIO_0_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2_GPIO_0_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_0_Config2_GPIO_0_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 1 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_1_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status  VTSS_IOREG(0x1e, 0, 0x0102)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_1.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . Trad_GPIO_1_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_Trad_GPIO_1_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_1.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . Trad_GPIO_1_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_Trad_GPIO_1_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_Trad_GPIO_1_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_Trad_GPIO_1_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_1.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . Trad_GPIO_1_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_Trad_GPIO_1_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_1.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . GPI_Intr_Pend1
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPI_Intr_Pend1  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status1.
 * Indicates the present value of the GPIO_1 pin.
 *
 * \details 
 * 0: Present Value of GPIO_1 pin is 0
 * 1: Present Value of GPIO_1 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . GPI_Status1
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPI_Status1  VTSS_BIT(10)

/** 
 * \brief
 * Enables pin to be used as an input for the 1588 Load/Save signal.  Bit
 * usage applies when the pin is configured at bits [2:0]=100.
 *
 * \details 
 * Use of pin as a 1588 Load/Save input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . LOAD_SAVE_1588_TS_Enable
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_LOAD_SAVE_1588_TS_Enable  VTSS_BIT(8)

/** 
 * \brief
 * GPIO_1 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . GPIO_1_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_1 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . GPIO_1_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_1 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: Transmit LOAD SAVE 1588
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status . GPIO_1_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config_Status_GPIO_1_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 1 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_1_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config2  VTSS_IOREG(0x1e, 0, 0x0103)

/** 
 * \brief
 * Data selected by GPIO_1_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config2 . GPIO_1_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config2_GPIO_1_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_1 when
 * GPIO_1_Config_Status.GPIO_1_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[1]
 * 0xFC: ch0_debug_data[1]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch0_rosi_sclk
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: rcomp_busy
 * 0xDE: ref_clk_sel[2]
 * 0xDD: ref_clk_sel[1]
 * 0xDC: ref_clk_sel[0]
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: l_pll5g_status_calibration_done
 * 0xD8: h_pll5g_status_calibration_done
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_kr_active
 * 0xD0: ch0_kr_active
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: ch1_rx_xgmii_clk_en_client_1g
 * 0xCC: ch0_rx_xgmii_clk_en_client_1g
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: ch1_tx_xgmii_clk_en_client_1g
 * 0xC8: ch0_tx_xgmii_clk_en_client_1g
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: ch1_rx_xgmii_clk_en_line_1g
 * 0xC4: ch0_rx_xgmii_clk_en_line_1g
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: ch1_tx_xgmii_clk_en_line_1g
 * 0xC0: ch0_tx_xgmii_clk_en_line_1g
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: ch1_rx_pcs_pause
 * 0xBC: ch0_rx_pcs_pause
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: ch1_tx_pcs_pause
 * 0xB8: ch0_tx_pcs_pause
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: ch1_rx_wis_pause
 * 0xB4: ch0_rx_wis_pause
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: ch1_tx_wis_pause
 * 0xB0: ch0_tx_wis_pause
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_dft_tx_ena
 * 0xAC: ch0_dft_tx_ena
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: Reserved
 * 0xA8: Reserved
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_ewis_fr_wordpos[2]
 * 0xA4: ch1_ewis_fr_wordpos[1]
 * 0xA3: ch1_ewis_fr_wordpos[0]
 * 0xA2: ch0_ewis_fr_wordpos[2]
 * 0xA1: ch0_ewis_fr_wordpos[1]
 * 0xA0: ch0_ewis_fr_wordpos[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pma_l3_control
 * 0x9C: ch0_pma_l3_control
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: Reserved
 * 0x98: Reserved
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_ewis_fr_bitpos[2]
 * 0x94: ch1_ewis_fr_bitpos[1]
 * 0x93: ch1_ewis_fr_bitpos[0]
 * 0x92: ch0_ewis_fr_bitpos[2]
 * 0x91: ch0_ewis_fr_bitpos[1]
 * 0x90: ch0_ewis_fr_bitpos[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_enable_tpg
 * 0x8C: ch0_enable_tpg
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_macsec_igr_pred_var_lat[2]
 * 0x84: ch1_macsec_igr_pred_var_lat[1]
 * 0x83: ch1_macsec_igr_pred_var_lat[0]
 * 0x82: ch0_macsec_igr_pred_var_lat[2]
 * 0x81: ch0_macsec_igr_pred_var_lat[1]
 * 0x80: ch0_macsec_igr_pred_var_lat[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config2 . GPIO_1_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config2_GPIO_1_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config2_GPIO_1_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_1_Config2_GPIO_1_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 2 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_2_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status  VTSS_IOREG(0x1e, 0, 0x0104)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_2.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . Trad_GPIO_2_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_Trad_GPIO_2_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_2.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . Trad_GPIO_2_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_Trad_GPIO_2_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_Trad_GPIO_2_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_Trad_GPIO_2_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_2.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . Trad_GPIO_2_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_Trad_GPIO_2_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_2.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . GPI_Intr_Pend2
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPI_Intr_Pend2  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status2.
 * Indicates the present value of the GPIO_2 pin.
 *
 * \details 
 * 0: Present Value of GPIO_2 pin is 0
 * 1: Present Value of GPIO_2 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . GPI_Status2
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPI_Status2  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_2 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt B from channel 0
 * 001: WIS interrupt B from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt B from both channels
 * 101: Logical OR of WIS interrupt B from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . GPIO_2_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_2 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . GPIO_2_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_2 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: SDA for TWS(slave)
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status . GPIO_2_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config_Status_GPIO_2_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 2 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_2_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config2  VTSS_IOREG(0x1e, 0, 0x0105)

/** 
 * \brief
 * Data selected by GPIO_2_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config2 . GPIO_2_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config2_GPIO_2_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_2 when
 * GPIO_2_Config_Status.GPIO_2_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[2]
 * 0xFC: ch0_debug_data[2]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch0_rosi_sdat
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: rcomp_busy
 * 0xDE: ref_clk_sel[2]
 * 0xDD: ref_clk_sel[1]
 * 0xDC: ref_clk_sel[0]
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: l_pll5g_status_calibration_done
 * 0xD8: h_pll5g_status_calibration_done
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_kr_active
 * 0xD0: ch0_kr_active
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: ch1_rx_xgmii_clk_en_client_1g
 * 0xCC: ch0_rx_xgmii_clk_en_client_1g
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: ch1_tx_xgmii_clk_en_client_1g
 * 0xC8: ch0_tx_xgmii_clk_en_client_1g
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: ch1_rx_xgmii_clk_en_line_1g
 * 0xC4: ch0_rx_xgmii_clk_en_line_1g
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: ch1_tx_xgmii_clk_en_line_1g
 * 0xC0: ch0_tx_xgmii_clk_en_line_1g
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: ch1_rx_pcs_pause
 * 0xBC: ch0_rx_pcs_pause
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: ch1_tx_pcs_pause
 * 0xB8: ch0_tx_pcs_pause
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: ch1_rx_wis_pause
 * 0xB4: ch0_rx_wis_pause
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: ch1_tx_wis_pause
 * 0xB0: ch0_tx_wis_pause
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_dft_tx_ena
 * 0xAC: ch0_dft_tx_ena
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: Reserved
 * 0xA8: Reserved
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_ewis_fr_wordpos[2]
 * 0xA4: ch1_ewis_fr_wordpos[1]
 * 0xA3: ch1_ewis_fr_wordpos[0]
 * 0xA2: ch0_ewis_fr_wordpos[2]
 * 0xA1: ch0_ewis_fr_wordpos[1]
 * 0xA0: ch0_ewis_fr_wordpos[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pma_l3_control
 * 0x9C: ch0_pma_l3_control
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: Reserved
 * 0x98: Reserved
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_ewis_fr_bitpos[2]
 * 0x94: ch1_ewis_fr_bitpos[1]
 * 0x93: ch1_ewis_fr_bitpos[0]
 * 0x92: ch0_ewis_fr_bitpos[2]
 * 0x91: ch0_ewis_fr_bitpos[1]
 * 0x90: ch0_ewis_fr_bitpos[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_enable_tpg
 * 0x8C: ch0_enable_tpg
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_macsec_igr_pred_var_lat[2]
 * 0x84: ch1_macsec_igr_pred_var_lat[1]
 * 0x83: ch1_macsec_igr_pred_var_lat[0]
 * 0x82: ch0_macsec_igr_pred_var_lat[2]
 * 0x81: ch0_macsec_igr_pred_var_lat[1]
 * 0x80: ch0_macsec_igr_pred_var_lat[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config2 . GPIO_2_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config2_GPIO_2_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config2_GPIO_2_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_2_Config2_GPIO_2_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 3 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_3_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status  VTSS_IOREG(0x1e, 0, 0x0106)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_3.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . Trad_GPIO_3_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_Trad_GPIO_3_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_3.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . Trad_GPIO_3_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_Trad_GPIO_3_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_Trad_GPIO_3_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_Trad_GPIO_3_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_3.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . Trad_GPIO_3_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_Trad_GPIO_3_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_3.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . GPI_Intr_Pend3
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPI_Intr_Pend3  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status3.
 * Indicates the present value of the GPIO_3 pin.
 *
 * \details 
 * 0: Present Value of GPIO_3 pin is 0
 * 1: Present Value of GPIO_3 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . GPI_Status3
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPI_Status3  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_3 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt B from channel 0
 * 001: WIS interrupt B from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt B from both channels
 * 101: Logical OR of WIS interrupt B from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . GPIO_3_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_3 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . GPIO_3_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_3 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: SCL for TWS(slave)
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status . GPIO_3_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config_Status_GPIO_3_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 3 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_3_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config2  VTSS_IOREG(0x1e, 0, 0x0107)

/** 
 * \brief
 * Data selected by GPIO_3_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config2 . GPIO_3_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config2_GPIO_3_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_3 when
 * GPIO_3_Config_Status.GPIO_3_Pin_Func_Sel=3
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[3]
 * 0xFC: ch0_debug_data[3]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch0_tosi_frm_pulse
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: rcomp_busy
 * 0xDE: ref_clk_sel[2]
 * 0xDD: ref_clk_sel[1]
 * 0xDC: ref_clk_sel[0]
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: l_pll5g_status_calibration_done
 * 0xD8: h_pll5g_status_calibration_done
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_kr_active
 * 0xD0: ch0_kr_active
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: ch1_rx_xgmii_clk_en_client_1g
 * 0xCC: ch0_rx_xgmii_clk_en_client_1g
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: ch1_tx_xgmii_clk_en_client_1g
 * 0xC8: ch0_tx_xgmii_clk_en_client_1g
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: ch1_rx_xgmii_clk_en_line_1g
 * 0xC4: ch0_rx_xgmii_clk_en_line_1g
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: ch1_tx_xgmii_clk_en_line_1g
 * 0xC0: ch0_tx_xgmii_clk_en_line_1g
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: ch1_rx_pcs_pause
 * 0xBC: ch0_rx_pcs_pause
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: ch1_tx_pcs_pause
 * 0xB8: ch0_tx_pcs_pause
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: ch1_rx_wis_pause
 * 0xB4: ch0_rx_wis_pause
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: ch1_tx_wis_pause
 * 0xB0: ch0_tx_wis_pause
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_dft_tx_ena
 * 0xAC: ch0_dft_tx_ena
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: Reserved
 * 0xA8: Reserved
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_ewis_fr_wordpos[2]
 * 0xA4: ch1_ewis_fr_wordpos[1]
 * 0xA3: ch1_ewis_fr_wordpos[0]
 * 0xA2: ch0_ewis_fr_wordpos[2]
 * 0xA1: ch0_ewis_fr_wordpos[1]
 * 0xA0: ch0_ewis_fr_wordpos[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pma_l3_control
 * 0x9C: ch0_pma_l3_control
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: Reserved
 * 0x98: Reserved
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_ewis_fr_bitpos[2]
 * 0x94: ch1_ewis_fr_bitpos[1]
 * 0x93: ch1_ewis_fr_bitpos[0]
 * 0x92: ch0_ewis_fr_bitpos[2]
 * 0x91: ch0_ewis_fr_bitpos[1]
 * 0x90: ch0_ewis_fr_bitpos[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_enable_tpg
 * 0x8C: ch0_enable_tpg
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_macsec_igr_pred_var_lat[2]
 * 0x84: ch1_macsec_igr_pred_var_lat[1]
 * 0x83: ch1_macsec_igr_pred_var_lat[0]
 * 0x82: ch0_macsec_igr_pred_var_lat[2]
 * 0x81: ch0_macsec_igr_pred_var_lat[1]
 * 0x80: ch0_macsec_igr_pred_var_lat[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config2 . GPIO_3_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config2_GPIO_3_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config2_GPIO_3_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_3_Config2_GPIO_3_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 4 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_4_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status  VTSS_IOREG(0x1e, 0, 0x0108)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_4.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . Trad_GPIO_4_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_Trad_GPIO_4_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_4.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . Trad_GPIO_4_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_Trad_GPIO_4_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_Trad_GPIO_4_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_Trad_GPIO_4_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_4.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . Trad_GPIO_4_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_Trad_GPIO_4_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_4.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . GPI_Intr_Pend4
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPI_Intr_Pend4  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status4.
 * Indicates the present value of the GPIO_4 pin.
 *
 * \details 
 * 0: Present Value of GPIO_4 pin is 0
 * 1: Present Value of GPIO_4 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . GPI_Status4
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPI_Status4  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_4 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt B from channel 0
 * 001: WIS interrupt B from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt B from both channels
 * 101: Logical OR of WIS interrupt B from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . GPIO_4_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_4 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . GPIO_4_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_4 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status . GPIO_4_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config_Status_GPIO_4_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 4 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_4_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config2  VTSS_IOREG(0x1e, 0, 0x0109)

/** 
 * \brief
 * Data selected by GPIO_4_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config2 . GPIO_4_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config2_GPIO_4_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_4 when
 * GPIO_4_Config_Status.GPIO_4_Pin_Func_Sel=3
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[4]
 * 0xFC: ch0_debug_data[4]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: ch1_one_pps
 * 0xF8: ch0_tosi_sclk
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: rcomp_busy
 * 0xDE: ref_clk_sel[2]
 * 0xDD: ref_clk_sel[1]
 * 0xDC: ref_clk_sel[0]
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: l_pll5g_status_calibration_done
 * 0xD8: h_pll5g_status_calibration_done
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_kr_active
 * 0xD0: ch0_kr_active
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: ch1_rx_xgmii_clk_en_client_1g
 * 0xCC: ch0_rx_xgmii_clk_en_client_1g
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: ch1_tx_xgmii_clk_en_client_1g
 * 0xC8: ch0_tx_xgmii_clk_en_client_1g
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: ch1_rx_xgmii_clk_en_line_1g
 * 0xC4: ch0_rx_xgmii_clk_en_line_1g
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: ch1_tx_xgmii_clk_en_line_1g
 * 0xC0: ch0_tx_xgmii_clk_en_line_1g
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: ch1_rx_pcs_pause
 * 0xBC: ch0_rx_pcs_pause
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: ch1_tx_pcs_pause
 * 0xB8: ch0_tx_pcs_pause
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: ch1_rx_wis_pause
 * 0xB4: ch0_rx_wis_pause
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: ch1_tx_wis_pause
 * 0xB0: ch0_tx_wis_pause
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_dft_tx_ena
 * 0xAC: ch0_dft_tx_ena
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: Reserved
 * 0xA8: Reserved
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_ewis_fr_wordpos[2]
 * 0xA4: ch1_ewis_fr_wordpos[1]
 * 0xA3: ch1_ewis_fr_wordpos[0]
 * 0xA2: ch0_ewis_fr_wordpos[2]
 * 0xA1: ch0_ewis_fr_wordpos[1]
 * 0xA0: ch0_ewis_fr_wordpos[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pma_l3_control
 * 0x9C: ch0_pma_l3_control
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: Reserved
 * 0x98: Reserved
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_ewis_fr_bitpos[2]
 * 0x94: ch1_ewis_fr_bitpos[1]
 * 0x93: ch1_ewis_fr_bitpos[0]
 * 0x92: ch0_ewis_fr_bitpos[2]
 * 0x91: ch0_ewis_fr_bitpos[1]
 * 0x90: ch0_ewis_fr_bitpos[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_enable_tpg
 * 0x8C: ch0_enable_tpg
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_macsec_igr_pred_var_lat[2]
 * 0x84: ch1_macsec_igr_pred_var_lat[1]
 * 0x83: ch1_macsec_igr_pred_var_lat[0]
 * 0x82: ch0_macsec_igr_pred_var_lat[2]
 * 0x81: ch0_macsec_igr_pred_var_lat[1]
 * 0x80: ch0_macsec_igr_pred_var_lat[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config2 . GPIO_4_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config2_GPIO_4_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config2_GPIO_4_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_4_Config2_GPIO_4_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 5 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_5_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status  VTSS_IOREG(0x1e, 0, 0x010a)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_5.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . Trad_GPIO_5_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_Trad_GPIO_5_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_5.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . Trad_GPIO_5_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_Trad_GPIO_5_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_Trad_GPIO_5_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_Trad_GPIO_5_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_5.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . Trad_GPIO_5_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_Trad_GPIO_5_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_5.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . GPI_Intr_Pend5
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPI_Intr_Pend5  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status5.
 * Indicates the present value of the GPIO_5 pin.
 *
 * \details 
 * 0: Present Value of GPIO_5 pin is 0
 * 1: Present Value of GPIO_5 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . GPI_Status5
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPI_Status5  VTSS_BIT(10)

/** 
 * \brief
 * Enables pin to be used as an input for the PPS_RI signal.  Bit usage
 * applies when the pin is configured as a general purpose input (bits
 * [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of pin as PPS_RI input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . PPS_RI_Enable
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_PPS_RI_Enable  VTSS_BIT(9)

/** 
 * \brief
 * Channel 0 TOSI Data Input Enable.
 * Enables use of this pin as the TOSI data input for channel 0.  Bit usage
 * applies when the pin is configured as a general purpose input (bits
 * [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of this pin as the TOSI data input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . Chan0_TOSI_Data_In_En
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_Chan0_TOSI_Data_In_En  VTSS_BIT(8)

/** 
 * \brief
 * GPIO_5 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . GPIO_5_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_5 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . GPIO_5_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_5 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status . GPIO_5_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config_Status_GPIO_5_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 5 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat1:GPIO_5_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config2  VTSS_IOREG(0x1e, 0, 0x010b)

/** 
 * \brief
 * Data selected by GPIO_5_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config2 . GPIO_5_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config2_GPIO_5_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_5 when
 * GPIO_5_Config_Status.GPIO_5_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[5]
 * 0xFC: ch0_debug_data[5]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: Reserved
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: rcomp_busy
 * 0xDE: ref_clk_sel[2]
 * 0xDD: ref_clk_sel[1]
 * 0xDC: ref_clk_sel[0]
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: l_pll5g_status_calibration_done
 * 0xD8: h_pll5g_status_calibration_done
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_kr_active
 * 0xD0: ch0_kr_active
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: ch1_rx_xgmii_clk_en_client_1g
 * 0xCC: ch0_rx_xgmii_clk_en_client_1g
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: ch1_tx_xgmii_clk_en_client_1g
 * 0xC8: ch0_tx_xgmii_clk_en_client_1g
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: ch1_rx_xgmii_clk_en_line_1g
 * 0xC4: ch0_rx_xgmii_clk_en_line_1g
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: ch1_tx_xgmii_clk_en_line_1g
 * 0xC0: ch0_tx_xgmii_clk_en_line_1g
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: ch1_rx_pcs_pause
 * 0xBC: ch0_rx_pcs_pause
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: ch1_tx_pcs_pause
 * 0xB8: ch0_tx_pcs_pause
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: ch1_rx_wis_pause
 * 0xB4: ch0_rx_wis_pause
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: ch1_tx_wis_pause
 * 0xB0: ch0_tx_wis_pause
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_dft_tx_ena
 * 0xAC: ch0_dft_tx_ena
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: Reserved
 * 0xA8: Reserved
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_ewis_fr_wordpos[2]
 * 0xA4: ch1_ewis_fr_wordpos[1]
 * 0xA3: ch1_ewis_fr_wordpos[0]
 * 0xA2: ch0_ewis_fr_wordpos[2]
 * 0xA1: ch0_ewis_fr_wordpos[1]
 * 0xA0: ch0_ewis_fr_wordpos[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pma_l3_control
 * 0x9C: ch0_pma_l3_control
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: Reserved
 * 0x98: Reserved
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_ewis_fr_bitpos[2]
 * 0x94: ch1_ewis_fr_bitpos[1]
 * 0x93: ch1_ewis_fr_bitpos[0]
 * 0x92: ch0_ewis_fr_bitpos[2]
 * 0x91: ch0_ewis_fr_bitpos[1]
 * 0x90: ch0_ewis_fr_bitpos[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_enable_tpg
 * 0x8C: ch0_enable_tpg
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_macsec_igr_pred_var_lat[2]
 * 0x84: ch1_macsec_igr_pred_var_lat[1]
 * 0x83: ch1_macsec_igr_pred_var_lat[0]
 * 0x82: ch0_macsec_igr_pred_var_lat[2]
 * 0x81: ch0_macsec_igr_pred_var_lat[1]
 * 0x80: ch0_macsec_igr_pred_var_lat[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config2 . GPIO_5_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config2_GPIO_5_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config2_GPIO_5_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat1_GPIO_5_Config2_GPIO_5_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a VENICE_GLOBAL:GPIO_Cfg_Stat2
 *
 * GPIO Configuration and Status Register Group 2
 */


/** 
 * \brief GPIO 6 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_6_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status  VTSS_IOREG(0x1e, 0, 0x0124)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_6.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . Trad_GPIO_6_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_Trad_GPIO_6_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_6.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . Trad_GPIO_6_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_Trad_GPIO_6_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_Trad_GPIO_6_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_Trad_GPIO_6_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_6.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . Trad_GPIO_6_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_Trad_GPIO_6_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_6.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . GPI_Intr_Pend6
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPI_Intr_Pend6  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status6.
 * Indicates the present value of the GPIO_6 pin.
 *
 * \details 
 * 0: Present Value of GPIO_6 pin is 0
 * 1: Present Value of GPIO_6 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . GPI_Status6
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPI_Status6  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_6 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt B from channel 0
 * 001: WIS interrupt B from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt B from both channels
 * 101: Logical OR of WIS interrupt B from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . GPIO_6_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_6 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . GPIO_6_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_6 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: SDA for TWS(master) bus#0
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status . GPIO_6_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config_Status_GPIO_6_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 6 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_6_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config2  VTSS_IOREG(0x1e, 0, 0x0125)

/** 
 * \brief
 * Data selected by GPIO_6_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config2 . GPIO_6_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config2_GPIO_6_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_6 when
 * GPIO_6_Config_Status.GPIO_6_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[6]
 * 0xFC: ch0_debug_data[6]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch1_rosi_frm_pulse
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: ch1_msec_ip1588_igr_sop
 * 0xD8: ch0_msec_ip1588_igr_sop
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: ch1_msec_ip1588_igr_eop
 * 0xD4: ch0_msec_ip1588_igr_eop
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_msec_ip1588_igr_abort
 * 0xD0: ch0_msec_ip1588_igr_abort
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: ch1_line_pcs1g_char_pos[3]
 * 0xC6: ch1_line_pcs1g_char_pos[2]
 * 0xC5: ch1_line_pcs1g_char_pos[1]
 * 0xC4: ch1_line_pcs1g_char_pos[0]
 * 0xC3: ch0_line_pcs1g_char_pos[3]
 * 0xC2: ch0_line_pcs1g_char_pos[2]
 * 0xC1: ch0_line_pcs1g_char_pos[1]
 * 0xC0: ch0_line_pcs1g_char_pos[0]
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: ch1_client_pcs1g_char_pos[3]
 * 0xB6: ch1_client_pcs1g_char_pos[2]
 * 0xB5: ch1_client_pcs1g_char_pos[1]
 * 0xB4: ch1_client_pcs1g_char_pos[0]
 * 0xB3: ch0_client_pcs1g_char_pos[3]
 * 0xB2: ch0_client_pcs1g_char_pos[2]
 * 0xB1: ch0_client_pcs1g_char_pos[1]
 * 0xB0: ch0_client_pcs1g_char_pos[0]
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: Reserved
 * 0xAC: Reserved
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_link_HCD[2]
 * 0xA8: ch1_link_HCD[1]
 * 0xA7: ch1_link_HCD[0]
 * 0xA6: ch0_link_HCD[2]
 * 0xA5: ch0_link_HCD[1]
 * 0xA4: ch0_link_HCD[0]
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: Reserved
 * 0xA0: Reserved
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: Reserved
 * 0x9C: Reserved
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_exe_last[4]
 * 0x98: ch1_exe_last[3]
 * 0x97: ch1_exe_last[2]
 * 0x96: ch1_exe_last[1]
 * 0x95: ch1_exe_last[0]
 * 0x94: ch0_exe_last[4]
 * 0x93: ch0_exe_last[3]
 * 0x92: ch0_exe_last[2]
 * 0x91: ch0_exe_last[1]
 * 0x90: ch0_exe_last[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: sd6g1_ana_status_3_ib_sig_det
 * 0x86: sd6g1_ana_status_2_ib_sig_det
 * 0x85: sd6g1_ana_status_1_ib_sig_det
 * 0x84: sd6g1_ana_status_0_ib_sig_det
 * 0x83: sd6g0_ana_status_3_ib_sig_det
 * 0x82: sd6g0_ana_status_2_ib_sig_det
 * 0x81: sd6g0_ana_status_1_ib_sig_det
 * 0x80: sd6g0_ana_status_0_ib_sig_det
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config2 . GPIO_6_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config2_GPIO_6_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config2_GPIO_6_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_6_Config2_GPIO_6_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 7 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_7_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status  VTSS_IOREG(0x1e, 0, 0x0126)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_7.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . Trad_GPIO_7_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_Trad_GPIO_7_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_7.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . Trad_GPIO_7_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_Trad_GPIO_7_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_Trad_GPIO_7_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_Trad_GPIO_7_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_7.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . Trad_GPIO_7_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_Trad_GPIO_7_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_7.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . GPI_Intr_Pend7
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPI_Intr_Pend7  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status7.
 * Indicates the present value of the GPIO_7 pin.
 *
 * \details 
 * 0: Present Value of GPIO_7 pin is 0
 * 1: Present Value of GPIO_7 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . GPI_Status7
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPI_Status7  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_7 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . GPIO_7_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_7 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . GPIO_7_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_7 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: SCL for TWS(master) bus#0
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status . GPIO_7_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config_Status_GPIO_7_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 7 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_7_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config2  VTSS_IOREG(0x1e, 0, 0x0127)

/** 
 * \brief
 * Data selected by GPIO_7_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config2 . GPIO_7_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config2_GPIO_7_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_7 when
 * GPIO_7_Config_Status.GPIO_7_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[7]
 * 0xFC: ch0_debug_data[7]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch1_rosi_sclk
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: ch1_msec_ip1588_igr_sop
 * 0xD8: ch0_msec_ip1588_igr_sop
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: ch1_msec_ip1588_igr_eop
 * 0xD4: ch0_msec_ip1588_igr_eop
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_msec_ip1588_igr_abort
 * 0xD0: ch0_msec_ip1588_igr_abort
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: ch1_line_pcs1g_char_pos[3]
 * 0xC6: ch1_line_pcs1g_char_pos[2]
 * 0xC5: ch1_line_pcs1g_char_pos[1]
 * 0xC4: ch1_line_pcs1g_char_pos[0]
 * 0xC3: ch0_line_pcs1g_char_pos[3]
 * 0xC2: ch0_line_pcs1g_char_pos[2]
 * 0xC1: ch0_line_pcs1g_char_pos[1]
 * 0xC0: ch0_line_pcs1g_char_pos[0]
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: ch1_client_pcs1g_char_pos[3]
 * 0xB6: ch1_client_pcs1g_char_pos[2]
 * 0xB5: ch1_client_pcs1g_char_pos[1]
 * 0xB4: ch1_client_pcs1g_char_pos[0]
 * 0xB3: ch0_client_pcs1g_char_pos[3]
 * 0xB2: ch0_client_pcs1g_char_pos[2]
 * 0xB1: ch0_client_pcs1g_char_pos[1]
 * 0xB0: ch0_client_pcs1g_char_pos[0]
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: Reserved
 * 0xAC: Reserved
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_link_HCD[2]
 * 0xA8: ch1_link_HCD[1]
 * 0xA7: ch1_link_HCD[0]
 * 0xA6: ch0_link_HCD[2]
 * 0xA5: ch0_link_HCD[1]
 * 0xA4: ch0_link_HCD[0]
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: Reserved
 * 0xA0: Reserved
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: Reserved
 * 0x9C: Reserved
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_exe_last[4]
 * 0x98: ch1_exe_last[3]
 * 0x97: ch1_exe_last[2]
 * 0x96: ch1_exe_last[1]
 * 0x95: ch1_exe_last[0]
 * 0x94: ch0_exe_last[4]
 * 0x93: ch0_exe_last[3]
 * 0x92: ch0_exe_last[2]
 * 0x91: ch0_exe_last[1]
 * 0x90: ch0_exe_last[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: sd6g1_ana_status_3_ib_sig_det
 * 0x86: sd6g1_ana_status_2_ib_sig_det
 * 0x85: sd6g1_ana_status_1_ib_sig_det
 * 0x84: sd6g1_ana_status_0_ib_sig_det
 * 0x83: sd6g0_ana_status_3_ib_sig_det
 * 0x82: sd6g0_ana_status_2_ib_sig_det
 * 0x81: sd6g0_ana_status_1_ib_sig_det
 * 0x80: sd6g0_ana_status_0_ib_sig_det
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config2 . GPIO_7_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config2_GPIO_7_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config2_GPIO_7_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_7_Config2_GPIO_7_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 8 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_8_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status  VTSS_IOREG(0x1e, 0, 0x0128)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_8.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . Trad_GPIO_8_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_Trad_GPIO_8_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_8.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . Trad_GPIO_8_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_Trad_GPIO_8_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_Trad_GPIO_8_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_Trad_GPIO_8_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_8.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . Trad_GPIO_8_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_Trad_GPIO_8_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_8.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . GPI_Intr_Pend8
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPI_Intr_Pend8  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status8.
 * Indicates the present value of the GPIO_8 pin.
 *
 * \details 
 * 0: Present Value of GPIO_8 pin is 0
 * 1: Present Value of GPIO_8 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . GPI_Status8
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPI_Status8  VTSS_BIT(10)

/** 
 * \brief
 * Enables the GPIO pin to be used as a PMTICK strobe source for the WIS
 * statistical counters.  Bit usage applies when the pin is configured as a
 * general purpose input (bits [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of pin as a PMTICK input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . PMTICK_Enable_2
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_PMTICK_Enable_2  VTSS_BIT(9)

/** 
 * \brief
 * Module Status Input Enable for channel 0.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of pin as a module status input for channel 0 and associated
 * interrupt pending generation in EWIS_INTR_PEND2.MODULE_PEND is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . Module_Stat_Input_En_Chan0
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_Module_Stat_Input_En_Chan0  VTSS_BIT(8)

/** 
 * \brief
 * GPIO_8 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . GPIO_8_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_8 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . GPIO_8_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_8 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status . GPIO_8_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config_Status_GPIO_8_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 8 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_8_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config2  VTSS_IOREG(0x1e, 0, 0x0129)

/** 
 * \brief
 * Data selected by GPIO_8_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config2 . GPIO_8_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config2_GPIO_8_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_8 when
 * GPIO_8_Config_Status.GPIO_8_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[8]
 * 0xFC: ch0_debug_data[8]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch1_rosi_sdat
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: ch1_msec_ip1588_igr_sop
 * 0xD8: ch0_msec_ip1588_igr_sop
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: ch1_msec_ip1588_igr_eop
 * 0xD4: ch0_msec_ip1588_igr_eop
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_msec_ip1588_igr_abort
 * 0xD0: ch0_msec_ip1588_igr_abort
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: ch1_line_pcs1g_char_pos[3]
 * 0xC6: ch1_line_pcs1g_char_pos[2]
 * 0xC5: ch1_line_pcs1g_char_pos[1]
 * 0xC4: ch1_line_pcs1g_char_pos[0]
 * 0xC3: ch0_line_pcs1g_char_pos[3]
 * 0xC2: ch0_line_pcs1g_char_pos[2]
 * 0xC1: ch0_line_pcs1g_char_pos[1]
 * 0xC0: ch0_line_pcs1g_char_pos[0]
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: ch1_client_pcs1g_char_pos[3]
 * 0xB6: ch1_client_pcs1g_char_pos[2]
 * 0xB5: ch1_client_pcs1g_char_pos[1]
 * 0xB4: ch1_client_pcs1g_char_pos[0]
 * 0xB3: ch0_client_pcs1g_char_pos[3]
 * 0xB2: ch0_client_pcs1g_char_pos[2]
 * 0xB1: ch0_client_pcs1g_char_pos[1]
 * 0xB0: ch0_client_pcs1g_char_pos[0]
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: Reserved
 * 0xAC: Reserved
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_link_HCD[2]
 * 0xA8: ch1_link_HCD[1]
 * 0xA7: ch1_link_HCD[0]
 * 0xA6: ch0_link_HCD[2]
 * 0xA5: ch0_link_HCD[1]
 * 0xA4: ch0_link_HCD[0]
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: Reserved
 * 0xA0: Reserved
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: Reserved
 * 0x9C: Reserved
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_exe_last[4]
 * 0x98: ch1_exe_last[3]
 * 0x97: ch1_exe_last[2]
 * 0x96: ch1_exe_last[1]
 * 0x95: ch1_exe_last[0]
 * 0x94: ch0_exe_last[4]
 * 0x93: ch0_exe_last[3]
 * 0x92: ch0_exe_last[2]
 * 0x91: ch0_exe_last[1]
 * 0x90: ch0_exe_last[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: sd6g1_ana_status_3_ib_sig_det
 * 0x86: sd6g1_ana_status_2_ib_sig_det
 * 0x85: sd6g1_ana_status_1_ib_sig_det
 * 0x84: sd6g1_ana_status_0_ib_sig_det
 * 0x83: sd6g0_ana_status_3_ib_sig_det
 * 0x82: sd6g0_ana_status_2_ib_sig_det
 * 0x81: sd6g0_ana_status_1_ib_sig_det
 * 0x80: sd6g0_ana_status_0_ib_sig_det
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config2 . GPIO_8_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config2_GPIO_8_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config2_GPIO_8_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_8_Config2_GPIO_8_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 9 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_9_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status  VTSS_IOREG(0x1e, 0, 0x012a)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_9.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . Trad_GPIO_9_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_Trad_GPIO_9_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_9.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . Trad_GPIO_9_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_Trad_GPIO_9_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_Trad_GPIO_9_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_Trad_GPIO_9_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_9.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . Trad_GPIO_9_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_Trad_GPIO_9_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_9.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . GPI_Intr_Pend9
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPI_Intr_Pend9  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status9.
 * Indicates the present value of the GPIO_9 pin.
 *
 * \details 
 * 0: Present Value of GPIO_9 pin is 0
 * 1: Present Value of GPIO_9 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . GPI_Status9
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPI_Status9  VTSS_BIT(10)

/** 
 * \brief
 * Enables the GPIO pin to be used as a PMTICK strobe source for the WIS
 * statistical counters.  Bit usage applies when the pin is configured as a
 * general purpose input (bits [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of pin as a PMTICK input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . PMTICK_Enable_3
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_PMTICK_Enable_3  VTSS_BIT(9)

/** 
 * \brief
 * Module Status Input Enable for channel 1.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of pin as a module status input for channel 1 and associated
 * interrupt pending generation in EWIS_INTR_PEND2.MODULE_PEND is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . Module_Stat_Input_En_Chan1
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_Module_Stat_Input_En_Chan1  VTSS_BIT(8)

/** 
 * \brief
 * GPIO_9 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . GPIO_9_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_9 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . GPIO_9_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_9 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status . GPIO_9_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config_Status_GPIO_9_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 9 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_9_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config2  VTSS_IOREG(0x1e, 0, 0x012b)

/** 
 * \brief
 * Data selected by GPIO_9_Internal_Node_Sel to be transmitted from the pin
 * is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config2 . GPIO_9_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config2_GPIO_9_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_9 when
 * GPIO_9_Config_Status.GPIO_9_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[9]
 * 0xFC: ch0_debug_data[9]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: ch1_one_pps
 * 0xF8: ch1_tosi_frm_pulse
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: ch1_msec_ip1588_igr_sop
 * 0xD8: ch0_msec_ip1588_igr_sop
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: ch1_msec_ip1588_igr_eop
 * 0xD4: ch0_msec_ip1588_igr_eop
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_msec_ip1588_igr_abort
 * 0xD0: ch0_msec_ip1588_igr_abort
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: ch1_line_pcs1g_char_pos[3]
 * 0xC6: ch1_line_pcs1g_char_pos[2]
 * 0xC5: ch1_line_pcs1g_char_pos[1]
 * 0xC4: ch1_line_pcs1g_char_pos[0]
 * 0xC3: ch0_line_pcs1g_char_pos[3]
 * 0xC2: ch0_line_pcs1g_char_pos[2]
 * 0xC1: ch0_line_pcs1g_char_pos[1]
 * 0xC0: ch0_line_pcs1g_char_pos[0]
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: ch1_client_pcs1g_char_pos[3]
 * 0xB6: ch1_client_pcs1g_char_pos[2]
 * 0xB5: ch1_client_pcs1g_char_pos[1]
 * 0xB4: ch1_client_pcs1g_char_pos[0]
 * 0xB3: ch0_client_pcs1g_char_pos[3]
 * 0xB2: ch0_client_pcs1g_char_pos[2]
 * 0xB1: ch0_client_pcs1g_char_pos[1]
 * 0xB0: ch0_client_pcs1g_char_pos[0]
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: Reserved
 * 0xAC: Reserved
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_link_HCD[2]
 * 0xA8: ch1_link_HCD[1]
 * 0xA7: ch1_link_HCD[0]
 * 0xA6: ch0_link_HCD[2]
 * 0xA5: ch0_link_HCD[1]
 * 0xA4: ch0_link_HCD[0]
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: Reserved
 * 0xA0: Reserved
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: Reserved
 * 0x9C: Reserved
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_exe_last[4]
 * 0x98: ch1_exe_last[3]
 * 0x97: ch1_exe_last[2]
 * 0x96: ch1_exe_last[1]
 * 0x95: ch1_exe_last[0]
 * 0x94: ch0_exe_last[4]
 * 0x93: ch0_exe_last[3]
 * 0x92: ch0_exe_last[2]
 * 0x91: ch0_exe_last[1]
 * 0x90: ch0_exe_last[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: sd6g1_ana_status_3_ib_sig_det
 * 0x86: sd6g1_ana_status_2_ib_sig_det
 * 0x85: sd6g1_ana_status_1_ib_sig_det
 * 0x84: sd6g1_ana_status_0_ib_sig_det
 * 0x83: sd6g0_ana_status_3_ib_sig_det
 * 0x82: sd6g0_ana_status_2_ib_sig_det
 * 0x81: sd6g0_ana_status_1_ib_sig_det
 * 0x80: sd6g0_ana_status_0_ib_sig_det
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config2 . GPIO_9_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config2_GPIO_9_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config2_GPIO_9_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_9_Config2_GPIO_9_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 10 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_10_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status  VTSS_IOREG(0x1e, 0, 0x012c)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_10.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . Trad_GPIO_10_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_Trad_GPIO_10_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_10.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . Trad_GPIO_10_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_Trad_GPIO_10_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_Trad_GPIO_10_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_Trad_GPIO_10_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_10.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . Trad_GPIO_10_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_Trad_GPIO_10_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_10.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . GPI_Intr_Pend10
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPI_Intr_Pend10  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status10.
 * Indicates the present value of the GPIO_10 pin.
 *
 * \details 
 * 0: Present Value of GPIO_10 pin is 0
 * 1: Present Value of GPIO_10 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . GPI_Status10
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPI_Status10  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_10 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt B from channel 0
 * 001: WIS interrupt B from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt B from both channels
 * 101: Logical OR of WIS interrupt B from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . GPIO_10_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_10 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . GPIO_10_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_10 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: SDA for TWS(master) bus #1
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status . GPIO_10_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config_Status_GPIO_10_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 10 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_10_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config2  VTSS_IOREG(0x1e, 0, 0x012d)

/** 
 * \brief
 * Data selected by GPIO_10_Internal_Node_Sel to be transmitted from the
 * pin is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config2 . GPIO_10_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config2_GPIO_10_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_10 when
 * GPIO_10_Config_Status.GPIO_10_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[10]
 * 0xFC: ch0_debug_data[10]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: ch1_tosi_sclk
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: ch1_msec_ip1588_igr_sop
 * 0xD8: ch0_msec_ip1588_igr_sop
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: ch1_msec_ip1588_igr_eop
 * 0xD4: ch0_msec_ip1588_igr_eop
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_msec_ip1588_igr_abort
 * 0xD0: ch0_msec_ip1588_igr_abort
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: ch1_line_pcs1g_char_pos[3]
 * 0xC6: ch1_line_pcs1g_char_pos[2]
 * 0xC5: ch1_line_pcs1g_char_pos[1]
 * 0xC4: ch1_line_pcs1g_char_pos[0]
 * 0xC3: ch0_line_pcs1g_char_pos[3]
 * 0xC2: ch0_line_pcs1g_char_pos[2]
 * 0xC1: ch0_line_pcs1g_char_pos[1]
 * 0xC0: ch0_line_pcs1g_char_pos[0]
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: ch1_client_pcs1g_char_pos[3]
 * 0xB6: ch1_client_pcs1g_char_pos[2]
 * 0xB5: ch1_client_pcs1g_char_pos[1]
 * 0xB4: ch1_client_pcs1g_char_pos[0]
 * 0xB3: ch0_client_pcs1g_char_pos[3]
 * 0xB2: ch0_client_pcs1g_char_pos[2]
 * 0xB1: ch0_client_pcs1g_char_pos[1]
 * 0xB0: ch0_client_pcs1g_char_pos[0]
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: Reserved
 * 0xAC: Reserved
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_link_HCD[2]
 * 0xA8: ch1_link_HCD[1]
 * 0xA7: ch1_link_HCD[0]
 * 0xA6: ch0_link_HCD[2]
 * 0xA5: ch0_link_HCD[1]
 * 0xA4: ch0_link_HCD[0]
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: Reserved
 * 0xA0: Reserved
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: Reserved
 * 0x9C: Reserved
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_exe_last[4]
 * 0x98: ch1_exe_last[3]
 * 0x97: ch1_exe_last[2]
 * 0x96: ch1_exe_last[1]
 * 0x95: ch1_exe_last[0]
 * 0x94: ch0_exe_last[4]
 * 0x93: ch0_exe_last[3]
 * 0x92: ch0_exe_last[2]
 * 0x91: ch0_exe_last[1]
 * 0x90: ch0_exe_last[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: sd6g1_ana_status_3_ib_sig_det
 * 0x86: sd6g1_ana_status_2_ib_sig_det
 * 0x85: sd6g1_ana_status_1_ib_sig_det
 * 0x84: sd6g1_ana_status_0_ib_sig_det
 * 0x83: sd6g0_ana_status_3_ib_sig_det
 * 0x82: sd6g0_ana_status_2_ib_sig_det
 * 0x81: sd6g0_ana_status_1_ib_sig_det
 * 0x80: sd6g0_ana_status_0_ib_sig_det
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config2 . GPIO_10_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config2_GPIO_10_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config2_GPIO_10_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_10_Config2_GPIO_10_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 11 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_11_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status  VTSS_IOREG(0x1e, 0, 0x012e)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_11.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . Trad_GPIO_11_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_Trad_GPIO_11_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_11.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . Trad_GPIO_11_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_Trad_GPIO_11_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_Trad_GPIO_11_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_Trad_GPIO_11_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_11.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . Trad_GPIO_11_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_Trad_GPIO_11_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_11.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . GPI_Intr_Pend11
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPI_Intr_Pend11  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status11.
 * Indicates the present value of the GPIO_11 pin.
 *
 * \details 
 * 0: Present Value of GPIO_11 pin is 0
 * 1: Present Value of GPIO_11 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . GPI_Status11
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPI_Status11  VTSS_BIT(10)

/** 
 * \brief
 * Channel 1 TOSI Data Input Enable.
 * Enables use of this pin as the TOSI data input for channel 0.  Bit usage
 * applies when the pin is configured as a general purpose input (bits
 * [2:0]=000 and bit 15=1).
 *
 * \details 
 * Use of this pin as the TOSI data input is:
 * 0: Disabled
 * 1: Enabled
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . Chan1_TOSI_Data_In_En
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_Chan1_TOSI_Data_In_En  VTSS_BIT(8)

/** 
 * \brief
 * GPIO_11 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . GPIO_11_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_11 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . GPIO_11_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_11 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100: SCL for TWS(master) bus #1
 * 101-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status . GPIO_11_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config_Status_GPIO_11_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 11 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_11_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config2  VTSS_IOREG(0x1e, 0, 0x012f)

/** 
 * \brief
 * Data selected by GPIO_11_Internal_Node_Sel to be transmitted from the
 * pin is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config2 . GPIO_11_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config2_GPIO_11_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_11 when
 * GPIO_11_Config_Status.GPIO_11_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: ch1_debug_data[11]
 * 0xFC: ch0_debug_data[11]
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: ch1_one_pps
 * 0xF8: Reserved
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: ch1_msec_ip1588_igr_sop
 * 0xD8: ch0_msec_ip1588_igr_sop
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: ch1_msec_ip1588_igr_eop
 * 0xD4: ch0_msec_ip1588_igr_eop
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: ch1_msec_ip1588_igr_abort
 * 0xD0: ch0_msec_ip1588_igr_abort
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: ch1_line_pcs1g_char_pos[3]
 * 0xC6: ch1_line_pcs1g_char_pos[2]
 * 0xC5: ch1_line_pcs1g_char_pos[1]
 * 0xC4: ch1_line_pcs1g_char_pos[0]
 * 0xC3: ch0_line_pcs1g_char_pos[3]
 * 0xC2: ch0_line_pcs1g_char_pos[2]
 * 0xC1: ch0_line_pcs1g_char_pos[1]
 * 0xC0: ch0_line_pcs1g_char_pos[0]
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: ch1_client_pcs1g_char_pos[3]
 * 0xB6: ch1_client_pcs1g_char_pos[2]
 * 0xB5: ch1_client_pcs1g_char_pos[1]
 * 0xB4: ch1_client_pcs1g_char_pos[0]
 * 0xB3: ch0_client_pcs1g_char_pos[3]
 * 0xB2: ch0_client_pcs1g_char_pos[2]
 * 0xB1: ch0_client_pcs1g_char_pos[1]
 * 0xB0: ch0_client_pcs1g_char_pos[0]
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: Reserved
 * 0xAC: Reserved
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_link_HCD[2]
 * 0xA8: ch1_link_HCD[1]
 * 0xA7: ch1_link_HCD[0]
 * 0xA6: ch0_link_HCD[2]
 * 0xA5: ch0_link_HCD[1]
 * 0xA4: ch0_link_HCD[0]
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: Reserved
 * 0xA0: Reserved
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: Reserved
 * 0x9C: Reserved
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_exe_last[4]
 * 0x98: ch1_exe_last[3]
 * 0x97: ch1_exe_last[2]
 * 0x96: ch1_exe_last[1]
 * 0x95: ch1_exe_last[0]
 * 0x94: ch0_exe_last[4]
 * 0x93: ch0_exe_last[3]
 * 0x92: ch0_exe_last[2]
 * 0x91: ch0_exe_last[1]
 * 0x90: ch0_exe_last[0]
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: Reserved
 * 0x88: Reserved
 * 0x87: sd6g1_ana_status_3_ib_sig_det
 * 0x86: sd6g1_ana_status_2_ib_sig_det
 * 0x85: sd6g1_ana_status_1_ib_sig_det
 * 0x84: sd6g1_ana_status_0_ib_sig_det
 * 0x83: sd6g0_ana_status_3_ib_sig_det
 * 0x82: sd6g0_ana_status_2_ib_sig_det
 * 0x81: sd6g0_ana_status_1_ib_sig_det
 * 0x80: sd6g0_ana_status_0_ib_sig_det
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config2 . GPIO_11_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config2_GPIO_11_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config2_GPIO_11_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_11_Config2_GPIO_11_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 12 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_12_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status  VTSS_IOREG(0x1e, 0, 0x0130)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_12.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . Trad_GPIO_12_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_Trad_GPIO_12_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_12.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . Trad_GPIO_12_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_Trad_GPIO_12_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_Trad_GPIO_12_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_Trad_GPIO_12_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_12.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . Trad_GPIO_12_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_Trad_GPIO_12_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_12.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . GPI_Intr_Pend12
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPI_Intr_Pend12  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status12.
 * Indicates the present value of the GPIO_12 pin.
 *
 * \details 
 * 0: Present Value of GPIO_12 pin is 0
 * 1: Present Value of GPIO_12 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . GPI_Status12
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPI_Status12  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_12 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . GPIO_12_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_12 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . GPIO_12_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_12 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status . GPIO_12_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config_Status_GPIO_12_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 12 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_12_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config2  VTSS_IOREG(0x1e, 0, 0x0131)

/** 
 * \brief
 * Data selected by GPIO_12_Internal_Node_Sel to be transmitted from the
 * pin is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config2 . GPIO_12_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config2_GPIO_12_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_12 when
 * GPIO_12_Config_Status.GPIO_12_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: Reserved
 * 0xFC: Reserved
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: Reserved
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: Reserved
 * 0xD8: Reserved
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: Reserved
 * 0xD0: Reserved
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: Reserved
 * 0xC4: Reserved
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: Reserved
 * 0xC0: Reserved
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: Reserved
 * 0xB4: Reserved
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: Reserved
 * 0xB0: Reserved
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_sd6g_init_done
 * 0xAC: ch0_sd6g_init_done
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_line_pcs1g_spd_rx
 * 0xA8: ch0_line_pcs1g_spd_rx
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: Reserved
 * 0xA4: Reserved
 * 0xA3: ch1_tx_sync_ctrl_wr_data[1]
 * 0xA2: ch1_tx_sync_ctrl_wr_data[0]
 * 0xA1: ch0_tx_sync_ctrl_wr_data[1]
 * 0xA0: ch0_tx_sync_ctrl_wr_data[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_client_pcs1g_spd_rx
 * 0x9C: ch0_client_pcs1g_spd_rx
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_line_pcs1g_spd_tx
 * 0x98: ch0_line_pcs1g_spd_tx
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_client_pcs1g_spd_tx
 * 0x94: ch0_client_pcs1g_spd_tx
 * 0x93: Reserved
 * 0x92: Reserved
 * 0x91: ch1_rx_link_up
 * 0x90: ch0_rx_link_up
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_tx_link_up
 * 0x8C: ch0_tx_link_up
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: ch1_data_activity_rx
 * 0x88: ch0_data_activity_rx
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_data_activity_tx
 * 0x84: ch0_data_activity_tx
 * 0x83: Reserved
 * 0x82: Reserved
 * 0x81: ch1_s_rx_block_lock
 * 0x80: ch0_s_rx_block_lock
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config2 . GPIO_12_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config2_GPIO_12_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config2_GPIO_12_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_12_Config2_GPIO_12_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 13 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_13_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status  VTSS_IOREG(0x1e, 0, 0x0132)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_13.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . Trad_GPIO_13_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_Trad_GPIO_13_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_13.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . Trad_GPIO_13_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_Trad_GPIO_13_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_Trad_GPIO_13_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_Trad_GPIO_13_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_13.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . Trad_GPIO_13_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_Trad_GPIO_13_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_13.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . GPI_Intr_Pend13
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPI_Intr_Pend13  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status13.
 * Indicates the present value of the GPIO_13 pin.
 *
 * \details 
 * 0: Present Value of GPIO_13 pin is 0
 * 1: Present Value of GPIO_13 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . GPI_Status13
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPI_Status13  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_13 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . GPIO_13_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_13 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . GPIO_13_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_13 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status . GPIO_13_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config_Status_GPIO_13_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 13 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_13_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config2  VTSS_IOREG(0x1e, 0, 0x0133)

/** 
 * \brief
 * Data selected by GPIO_13_Internal_Node_Sel to be transmitted from the
 * pin is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config2 . GPIO_13_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config2_GPIO_13_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_13 when
 * GPIO_13_Config_Status.GPIO_13_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: Reserved
 * 0xFC: Reserved
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: Reserved
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: Reserved
 * 0xD8: Reserved
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: Reserved
 * 0xD0: Reserved
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: Reserved
 * 0xC4: Reserved
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: Reserved
 * 0xC0: Reserved
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: Reserved
 * 0xB4: Reserved
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: Reserved
 * 0xB0: Reserved
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_sd6g_init_done
 * 0xAC: ch0_sd6g_init_done
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_line_pcs1g_spd_rx
 * 0xA8: ch0_line_pcs1g_spd_rx
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: Reserved
 * 0xA4: Reserved
 * 0xA3: ch1_tx_sync_ctrl_wr_data[1]
 * 0xA2: ch1_tx_sync_ctrl_wr_data[0]
 * 0xA1: ch0_tx_sync_ctrl_wr_data[1]
 * 0xA0: ch0_tx_sync_ctrl_wr_data[0]
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_client_pcs1g_spd_rx
 * 0x9C: ch0_client_pcs1g_spd_rx
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_line_pcs1g_spd_tx
 * 0x98: ch0_line_pcs1g_spd_tx
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_client_pcs1g_spd_tx
 * 0x94: ch0_client_pcs1g_spd_tx
 * 0x93: Reserved
 * 0x92: Reserved
 * 0x91: ch1_rx_link_up
 * 0x90: ch0_rx_link_up
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: ch1_tx_link_up
 * 0x8C: ch0_tx_link_up
 * 0x8B: Reserved
 * 0x8A: Reserved
 * 0x89: ch1_data_activity_rx
 * 0x88: ch0_data_activity_rx
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: ch1_data_activity_tx
 * 0x84: ch0_data_activity_tx
 * 0x83: Reserved
 * 0x82: Reserved
 * 0x81: ch1_s_rx_block_lock
 * 0x80: ch0_s_rx_block_lock
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config2 . GPIO_13_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config2_GPIO_13_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config2_GPIO_13_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_13_Config2_GPIO_13_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 14 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_14_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status  VTSS_IOREG(0x1e, 0, 0x0134)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_14.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . Trad_GPIO_14_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_Trad_GPIO_14_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_14.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . Trad_GPIO_14_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_Trad_GPIO_14_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_Trad_GPIO_14_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_Trad_GPIO_14_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_14.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . Trad_GPIO_14_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_Trad_GPIO_14_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_14.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . GPI_Intr_Pend14
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPI_Intr_Pend14  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status14.
 * Indicates the present value of the GPIO_14 pin.
 *
 * \details 
 * 0: Present Value of GPIO_14 pin is 0
 * 1: Present Value of GPIO_14 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . GPI_Status14
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPI_Status14  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_14 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . GPIO_14_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_14 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: TX Link Activity from channel 0
 * 01: TX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . GPIO_14_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_14 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status . GPIO_14_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config_Status_GPIO_14_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 14 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_14_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config2  VTSS_IOREG(0x1e, 0, 0x0135)

/** 
 * \brief
 * Data selected by GPIO_14_Internal_Node_Sel to be transmitted from the
 * pin is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config2 . GPIO_14_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config2_GPIO_14_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_14 when
 * GPIO_14_Config_Status.GPIO_14_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: Reserved
 * 0xFC: Reserved
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: Reserved
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: Reserved
 * 0xD8: Reserved
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: Reserved
 * 0xD0: Reserved
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: Reserved
 * 0xC4: Reserved
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: Reserved
 * 0xC0: Reserved
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: Reserved
 * 0xB4: Reserved
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: Reserved
 * 0xB0: Reserved
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_sd6g_init_done
 * 0xAC: ch0_sd6g_init_done
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_xgxs_intr
 * 0xA8: ch0_xgxs_intr
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_found_schar_rx
 * 0xA4: ch0_found_schar_rx
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: ch1_found_schar_tx
 * 0xA0: ch0_found_schar_tx
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pll_lock_rx
 * 0x9C: ch0_pll_lock_rx
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_pll_lock_tx
 * 0x98: ch0_pll_lock_tx
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_line_pcs1g_intr
 * 0x94: ch0_line_pcs1g_intr
 * 0x93: Reserved
 * 0x92: Reserved
 * 0x91: ch1_client_pcs1g_intr
 * 0x90: ch0_client_pcs1g_intr
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: ch1_line_pcs1g_ass_latency[1]
 * 0x8A: ch1_line_pcs1g_ass_latency[0]
 * 0x89: ch0_line_pcs1g_ass_latency[1]
 * 0x88: ch0_line_pcs1g_ass_latency[0]
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: Reserved
 * 0x84: Reserved
 * 0x83: ch1_client_pcs1g_ass_latency[1]
 * 0x82: ch1_client_pcs1g_ass_latency[0]
 * 0x81: ch0_client_pcs1g_ass_latency[1]
 * 0x80: ch0_client_pcs1g_ass_latency[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config2 . GPIO_14_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config2_GPIO_14_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config2_GPIO_14_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_14_Config2_GPIO_14_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief GPIO 15 Config / Status
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_15_Config_Status
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status  VTSS_IOREG(0x1e, 0, 0x0136)

/** 
 * \brief
 * Traditional GPIO Output Tri-state Control for pin GPIO_15.
 * Controls whether the pin is in input or output mode.  Bit usage applies
 * only when the pin is configured as a traditional GPIO pin (bits [2:0] in
 * this register are 000).
 *
 * \details 
 * 0: Output mode
 * 1: Input mode
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . Trad_GPIO_15_TriState_Ctrl
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_Trad_GPIO_15_TriState_Ctrl  VTSS_BIT(15)

/** 
 * \brief
 * Traditional GPIO Pin Function Selection for pin GPIO_15.
 * Bit usage applies only when the pin is configured as a traditional GPIO
 * pin (bits [2:0] in this register are 000).
 *
 * \details 
 * When the pin is in output mode (bit 15=0):
 * 00: Bit 12 setting is driven out the pin.
 * 01: Drive repeating LOW/Hi-Z pattern at 2Hz.
 * 10: Drive repeating LOW/Hi-Z pattern at 4Hz.
 * 11: Drive repeating LOW/Hi-Z pattern at 10Hz.
 * 
 * When the pin is in input mode (bit 15=1):
 * 00: Assertion of the interrupt pending in bit 11 is disabled.
 * 01: Interrupt pending in bit 11 is asserted on the rising edge of the
 * GPIO pin.
 * 10: Interrupt pending in bit 11 is asserted on the falling edge of the
 * GPIO pin.
 * 11: Interrupt pending in bit 11 is asserted on both the rising and
 * falling edge of the GPIO pin.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . Trad_GPIO_15_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_Trad_GPIO_15_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,13,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_Trad_GPIO_15_Pin_Func_Sel     VTSS_ENCODE_BITMASK(13,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_Trad_GPIO_15_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,13,2)

/** 
 * \brief
 * Traditional GPIO Output Data for pin GPIO_15.
 * Logic value transmitted from the pin when configured as a traditional
 * general purpose output (bits [2:0]=000, bit 15=0 and bits [14:13]=00)
 *
 * \details 
 * 0: Output data = 0
 * 1: Output data = 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . Trad_GPIO_15_Output_Data
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_Trad_GPIO_15_Output_Data  VTSS_BIT(12)

/** 
 * \brief
 * General Purpose Input Interrupt Pending register for pin GPIO_15.
 * Bit usage applies when the pin is configured as a general purpose input
 * (bits [2:0]=000 and bit 15=1) and interrupt generation is enabled (bits
 * [14:13]).  This sticky bit is cleared when the register is read.
 *
 * \details 
 * 0: No interrupt event occurred since the last time the register was read
 * 1: Interrupt event has occurred
 * 
 * Note:  This bit reflects the interrupt status of the GPIO pin.  No INTR
 * signal is sent off from the PHY.  If INTR needs to be sent off from the
 * the device, please use the WIS_INTR through bits [7:5] and configure
 * btis [2:0] to 010.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . GPI_Intr_Pend15
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPI_Intr_Pend15  VTSS_BIT(11)

/** 
 * \brief
 * General_Purpose_Input_Status15.
 * Indicates the present value of the GPIO_15 pin.
 *
 * \details 
 * 0: Present Value of GPIO_15 pin is 0
 * 1: Present Value of GPIO_15 pin is 1
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . GPI_Status15
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPI_Status15  VTSS_BIT(10)

/** 
 * \brief
 * GPIO_15 WIS Interrupt Selection.
 * Determines what WIS interrupt status is transmitted from the pin when
 * bits [2:0] in this register are 010.
 *
 * \details 
 * 000: WIS interrupt A from channel 0
 * 001: WIS interrupt A from channel 1
 * 010: Reserved
 * 011: Reserved
 * 100: Logical AND of WIS interrupt A from both channels
 * 101: Logical OR of WIS interrupt A from both channels
 * 110: Reserved
 * 111: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . GPIO_15_WIS_Intr_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_WIS_Intr_Sel(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_WIS_Intr_Sel     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_WIS_Intr_Sel(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * GPIO_15 Link Activity Selection.
 * Determines what link activity is transmitted from the pin when bits
 * [2:0] in this register are 001.
 *
 * \details 
 * 00: RX Link Activity from channel 0
 * 01: RX Link Activity from channel 1
 * 10: Reserved
 * 11: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . GPIO_15_Link_Activ_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_Link_Activ_Sel(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_Link_Activ_Sel     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_Link_Activ_Sel(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * GPIO_15 Pin Function Selection.
 * Selects the GPIO pin's functionality.
 *
 * \details 
 * 000: Traditional GPIO behavior
 * 001: Activity LED output
 * 010: WIS Interrupt Output
 * 011: Transmit internal signals
 * 100-111: Reserved for future use.
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status . GPIO_15_Pin_Func_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_Pin_Func_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_Pin_Func_Sel     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config_Status_GPIO_15_Pin_Func_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief GPIO 15 Config2
 *
 * \details
 * Register: \a VENICE_GLOBAL:GPIO_Cfg_Stat2:GPIO_15_Config2
 */
#define VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config2  VTSS_IOREG(0x1e, 0, 0x0137)

/** 
 * \brief
 * Data selected by GPIO_15_Internal_Node_Sel to be transmitted from the
 * pin is inverted when this bit is asserted.
 *
 * \details 
 * 0: Normal output
 * 1: Inverted output
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config2 . GPIO_15_Data_Inversion
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config2_GPIO_15_Data_Inversion  VTSS_BIT(15)

/** 
 * \brief
 * Selects the internal signal transmitted from pin GPIO_15 when
 * GPIO_15_Config_Status.GPIO_15_Pin_Func_Sel=3.
 *
 * \details 
 * Selection:
 * 0xFF: Reserved
 * 0xFE: Reserved
 * 0xFD: Reserved
 * 0xFC: Reserved
 * 0xFB: Reserved
 * 0xFA: Reserved
 * 0xF9: Reserved
 * 0xF8: Reserved
 * 0xF7: Reserved
 * 0xF6: Reserved
 * 0xF5: Reserved
 * 0xF4: Reserved
 * 0xF3: Reserved
 * 0xF2: Reserved
 * 0xF1: Reserved
 * 0xF0: Reserved
 * 0xEF: Reserved
 * 0xEE: Reserved
 * 0xED: Reserved
 * 0xEC: Reserved
 * 0xEB: Reserved
 * 0xEA: Reserved
 * 0xE9: Reserved
 * 0xE8: Reserved
 * 0xE7: Reserved
 * 0xE6: Reserved
 * 0xE5: Reserved
 * 0xE4: Reserved
 * 0xE3: Reserved
 * 0xE2: Reserved
 * 0xE1: Reserved
 * 0xE0: Reserved
 * 0xDF: Reserved
 * 0xDE: Reserved
 * 0xDD: Reserved
 * 0xDC: Reserved
 * 0xDB: Reserved
 * 0xDA: Reserved
 * 0xD9: Reserved
 * 0xD8: Reserved
 * 0xD7: Reserved
 * 0xD6: Reserved
 * 0xD5: Reserved
 * 0xD4: Reserved
 * 0xD3: Reserved
 * 0xD2: Reserved
 * 0xD1: Reserved
 * 0xD0: Reserved
 * 0xCF: Reserved
 * 0xCE: Reserved
 * 0xCD: Reserved
 * 0xCC: Reserved
 * 0xCB: Reserved
 * 0xCA: Reserved
 * 0xC9: Reserved
 * 0xC8: Reserved
 * 0xC7: Reserved
 * 0xC6: Reserved
 * 0xC5: Reserved
 * 0xC4: Reserved
 * 0xC3: Reserved
 * 0xC2: Reserved
 * 0xC1: Reserved
 * 0xC0: Reserved
 * 0xBF: Reserved
 * 0xBE: Reserved
 * 0xBD: Reserved
 * 0xBC: Reserved
 * 0xBB: Reserved
 * 0xBA: Reserved
 * 0xB9: Reserved
 * 0xB8: Reserved
 * 0xB7: Reserved
 * 0xB6: Reserved
 * 0xB5: Reserved
 * 0xB4: Reserved
 * 0xB3: Reserved
 * 0xB2: Reserved
 * 0xB1: Reserved
 * 0xB0: Reserved
 * 0xAF: Reserved
 * 0xAE: Reserved
 * 0xAD: ch1_sd6g_init_done
 * 0xAC: ch0_sd6g_init_done
 * 0xAB: Reserved
 * 0xAA: Reserved
 * 0xA9: ch1_xgxs_intr
 * 0xA8: ch0_xgxs_intr
 * 0xA7: Reserved
 * 0xA6: Reserved
 * 0xA5: ch1_found_schar_rx
 * 0xA4: ch0_found_schar_rx
 * 0xA3: Reserved
 * 0xA2: Reserved
 * 0xA1: ch1_found_schar_tx
 * 0xA0: ch0_found_schar_tx
 * 0x9F: Reserved
 * 0x9E: Reserved
 * 0x9D: ch1_pll_lock_rx
 * 0x9C: ch0_pll_lock_rx
 * 0x9B: Reserved
 * 0x9A: Reserved
 * 0x99: ch1_pll_lock_tx
 * 0x98: ch0_pll_lock_tx
 * 0x97: Reserved
 * 0x96: Reserved
 * 0x95: ch1_line_pcs1g_intr
 * 0x94: ch0_line_pcs1g_intr
 * 0x93: Reserved
 * 0x92: Reserved
 * 0x91: ch1_client_pcs1g_intr
 * 0x90: ch0_client_pcs1g_intr
 * 0x8F: Reserved
 * 0x8E: Reserved
 * 0x8D: Reserved
 * 0x8C: Reserved
 * 0x8B: ch1_line_pcs1g_ass_latency[1]
 * 0x8A: ch1_line_pcs1g_ass_latency[0]
 * 0x89: ch0_line_pcs1g_ass_latency[1]
 * 0x88: ch0_line_pcs1g_ass_latency[0]
 * 0x87: Reserved
 * 0x86: Reserved
 * 0x85: Reserved
 * 0x84: Reserved
 * 0x83: ch1_client_pcs1g_ass_latency[1]
 * 0x82: ch1_client_pcs1g_ass_latency[0]
 * 0x81: ch0_client_pcs1g_ass_latency[1]
 * 0x80: ch0_client_pcs1g_ass_latency[0]
 * 0x7F: Reserved
 * 0x7E: Reserved
 * 0x7D: Reserved
 * 0x7C: Reserved
 * 0x7B: Reserved
 * 0x7A: Reserved
 * 0x79: Reserved
 * 0x78: Reserved
 * 0x77: Reserved
 * 0x76: Reserved
 * 0x75: Reserved
 * 0x74: Reserved
 * 0x73: Reserved
 * 0x72: Reserved
 * 0x71: Reserved
 * 0x70: Reserved
 * 0x6F: Reserved
 * 0x6E: Reserved
 * 0x6D: Reserved
 * 0x6C: Reserved
 * 0x6B: Reserved
 * 0x6A: Reserved
 * 0x69: Reserved
 * 0x68: Reserved
 * 0x67: Reserved
 * 0x66: Reserved
 * 0x65: Reserved
 * 0x64: Reserved
 * 0x63: Reserved
 * 0x62: Reserved
 * 0x61: Reserved
 * 0x60: Reserved
 * 0x5F: Reserved
 * 0x5E: Reserved
 * 0x5D: Reserved
 * 0x5C: Reserved
 * 0x5B: Reserved
 * 0x5A: Reserved
 * 0x59: Reserved
 * 0x58: Reserved
 * 0x57: Reserved
 * 0x56: Reserved
 * 0x55: Reserved
 * 0x54: Reserved
 * 0x53: Reserved
 * 0x52: Reserved
 * 0x51: Reserved
 * 0x50: Reserved
 * 0x4F: l_pll5g_status_lock_status
 * 0x4E: h_pll5g_status_lock_status
 * 0x4D: Reserved
 * 0x4C: egr_ts_fifo_empty_all
 * 0x4B: Reserved
 * 0x4A: Reserved
 * 0x49: egr_ts_fifo_empty[1]
 * 0x48: egr_ts_fifo_empty[0]
 * 0x47: Reserved
 * 0x46: Reserved
 * 0x45: ch1_rx_wis_signal_ok
 * 0x44: ch0_rx_wis_signal_ok
 * 0x43: Reserved
 * 0x42: Reserved
 * 0x41: ch1_pcs_rx_status
 * 0x40: ch0_pcs_rx_status
 * 0x3F: Reserved
 * 0x3E: Reserved
 * 0x3D: Reserved
 * 0x3C: Reserved
 * 0x3B: Reserved
 * 0x3A: Reserved
 * 0x39: Reserved
 * 0x38: Reserved
 * 0x37: ch1_lane_sync_status[3]
 * 0x36: ch1_lane_sync_status[2]
 * 0x35: ch1_lane_sync_status[1]
 * 0x34: ch1_lane_sync_status[0]
 * 0x33: ch0_lane_sync_status[3]
 * 0x32: ch0_lane_sync_status[2]
 * 0x31: ch0_lane_sync_status[1]
 * 0x30: ch0_lane_sync_status[0]
 * 0x2F: Reserved
 * 0x2E: Reserved
 * 0x2D: ch1_txen
 * 0x2C: ch0_txen
 * 0x2B: Reserved
 * 0x2A: Reserved
 * 0x29: ch1_pcs_xaui_align
 * 0x28: ch0_pcs_xaui_align
 * 0x27: Reserved
 * 0x26: Reserved
 * 0x25: ch1_line_pcs1g_link_status
 * 0x24: ch0_line_pcs1g_link_status
 * 0x23: Reserved
 * 0x22: Reserved
 * 0x21: ch1_client_pcs1g_link_status
 * 0x20: ch0_client_pcs1g_link_status
 * 0x1F: Reserved
 * 0x1E: Reserved
 * 0x1D: ch1_signal_detect_line
 * 0x1C: ch0_signal_detect_line
 * 0x1B: Reserved
 * 0x1A: Reserved
 * 0x19: ch1_signal_detect_client
 * 0x18: ch0_signal_detect_client
 * 0x17: Reserved
 * 0x16: Reserved
 * 0x15: ch1_s_tx_fault
 * 0x14: ch0_s_tx_fault
 * 0x13: Reserved
 * 0x12: Reserved
 * 0x11: ch1_signal_detect
 * 0x10: ch0_signal_detect
 * 0x0F: Reserved
 * 0x0E: Reserved
 * 0x0D: ch1_sync10g
 * 0x0C: ch0_sync10g
 * 0x0B: Reserved
 * 0x0A: Reserved
 * 0x09: ch1_sync8b10b
 * 0x08: ch0_sync8b10b
 * 0x07: Reserved
 * 0x06: Reserved
 * 0x05: ch1_rxalarm
 * 0x04: ch0_rxalarm
 * 0x03: Reserved
 * 0x02: Reserved
 * 0x01: ch1_txalarm
 * 0x00: ch0_txalarm
 *
 * Field: VTSS_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config2 . GPIO_15_Internal_Node_Sel
 */
#define  VTSS_F_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config2_GPIO_15_Internal_Node_Sel(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config2_GPIO_15_Internal_Node_Sel     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_GPIO_Cfg_Stat2_GPIO_15_Config2_GPIO_15_Internal_Node_Sel(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a VENICE_GLOBAL:Temp_Monitor
 *
 * Temperature Monitor
 */


/** 
 * \brief Temperature Monitor Threshold Settings
 *
 * \details
 * Temperature Monitor Threshold Settings
 *
 * Register: \a VENICE_GLOBAL:Temp_Monitor:Temp_Mon_Threshold
 */
#define VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold  VTSS_IOREG(0x1e, 0, 0x01c0)

/** 
 * \brief
 * Determines trigger for high temp alarm
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold . High_Temp_Threshold_Setting
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_High_Temp_Threshold_Setting(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_High_Temp_Threshold_Setting     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_High_Temp_Threshold_Setting(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Determines trigger for low temp alarm

 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold . Low_Temp_Threshold_Setting
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_Low_Temp_Threshold_Setting(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_Low_Temp_Threshold_Setting     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_Low_Temp_Threshold_Setting(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Temperature Monitor Registers
 *
 * \details
 * Temperature Monitor Registers

 *
 * Register: \a VENICE_GLOBAL:Temp_Monitor:Temp_Mon_Regs
 */
#define VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs  VTSS_IOREG(0x1e, 0, 0x01c1)

/** 
 * \brief
 * Enables the temperature monitor block

 *
 * \details 
 * 0: Temperature Monitor Disable
 * 1: Temperature Monitor Enable

 *
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Enable_Digital_Temp_Monitor
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Enable_Digital_Temp_Monitor  VTSS_BIT(12)

/** 
 * \brief
 * Initiates the temperature sampling process

 *
 * \details 
 * 0: Temperature Monitor idles
 * 1: Temperature Monitor starts sampling
 *
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Temp_Monitor_Run
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Run  VTSS_BIT(11)

/** 
 * \brief
 * Temp Monitor Done Status

 *
 * \details 
 * 0: Temperature Monitor is not done sampling
 * 1: Temperature Monitor is done sampling, data in Temp_Monitor_Reading is
 * ready
 *
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Temp_Monitor_Done_Status
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Done_Status  VTSS_BIT(10)

/** 
 * \brief
 * High Temperature Alarm
 * Sets when the Temp_Monitor_Reading is lower than the value set in
 * High_Temp_Threshold_Setting. 
 * Temp_Monitor_Reading[7:0] value is inversly proportional to Termperature

 *
 * \details 
 * 0: Alarm is not set
 * 1: Alarm is set

 *
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs . High_Temp_Alarm
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_High_Temp_Alarm  VTSS_BIT(9)

/** 
 * \brief
 * Low Temperature  Alarm
 * Sets when the Temp_Monitor_Reading is higher than the value set in
 * Low_Temp_Threshold_Setting. 
 * Temp_Monitor_Reading[7:0] value is inversly proportional to Termperature

 *
 * \details 
 * 0: Alarm is not set
 * 1: Alarm is set
 *
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Low_Temp_Alarm
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Low_Temp_Alarm  VTSS_BIT(8)

/** 
 * \brief
 * Temperature Monitor Reading
 * This is the digital reading of the temperature monitor.  
 * Value is not valid unless Temp_Monitor_Done_Status = 1

 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Temp_Monitor_Reading
 */
#define  VTSS_F_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Reading(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Reading     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Reading(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a VENICE_GLOBAL:POR_STATUS
 *
 * Power On Status
 */


/** 
 * \brief Power On Done
 *
 * \details
 * Power On Done
 *
 * Register: \a VENICE_GLOBAL:POR_STATUS:POR_DONE
 */
#define VTSS_VENICE_GLOBAL_POR_STATUS_POR_DONE  VTSS_IOREG(0x1e, 0, 0x0200)

/** 
 * \brief
 * Indicates the power on sequence are done and both LC PLLs are stable
 * This register is written by API to enable the autoconfiguration on the
 * host side serdes
 *
 * \details 
 * 0: Power On Sequence is not done, LC PLLs are not stable
 * 1: Power On Sequence is done, LC PLLs are stable
 *
 * Field: VTSS_VENICE_GLOBAL_POR_STATUS_POR_DONE . POR_DONE
 */
#define  VTSS_F_VENICE_GLOBAL_POR_STATUS_POR_DONE_POR_DONE  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:LINE_REFCK_SRC
 *
 * Select Line Side Reference Clock Source
 */


/** 
 * \brief Select Line Side Reference Clock Source
 *
 * \details
 * Select Line Side Reference Clock Source
 *
 * Register: \a VENICE_GLOBAL:LINE_REFCK_SRC:LINE_PLL_REFCK_SRC
 */
#define VTSS_VENICE_GLOBAL_LINE_REFCK_SRC_LINE_PLL_REFCK_SRC  VTSS_IOREG(0x1e, 0, 0x0210)

/** 
 * \brief
 * Select Line Side Reference Clock Source
 *
 * \details 
 * 0: Reference Clock from XREFCK
 * 1: Reference Clock from WREFCK
 *
 * Field: VTSS_VENICE_GLOBAL_LINE_REFCK_SRC_LINE_PLL_REFCK_SRC . LINE_PLL_REFCK_SRC
 */
#define  VTSS_F_VENICE_GLOBAL_LINE_REFCK_SRC_LINE_PLL_REFCK_SRC_LINE_PLL_REFCK_SRC  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:MISC_1588_GPIO
 *
 * Misc 1588 GPIO control
 */


/** 
 * \brief Select 1588 PPS to go to GPIO
 *
 * \details
 * Select 1588 PPS to go to GPIO
 *
 * Register: \a VENICE_GLOBAL:MISC_1588_GPIO:SELECT_1588_PPS
 */
#define VTSS_VENICE_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS  VTSS_IOREG(0x1e, 0, 0x0220)

/** 
 * \brief
 * Select 1588 PPS_0 or PPS_1 goes to GPIO (4, 9, and 11)
 *
 * \details 
 * 0: PPS_0 is routed to GPIO
 * 1: PPS_1 is routed to GPIO
 *
 * Field: VTSS_VENICE_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS . SELECT_1588_PPS_1
 */
#define  VTSS_F_VENICE_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS_SELECT_1588_PPS_1  VTSS_BIT(1)

/** 
 * \brief
 * Select 1588 PPS_0 or PPS_1 goes to GPIO 0

 *
 * \details 
 * 0: PPS_0 is routed to GPIO
 * 1: PPS_1 is routed to GPIO
 *
 * Field: VTSS_VENICE_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS . SELECT_1588_PPS_0
 */
#define  VTSS_F_VENICE_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS_SELECT_1588_PPS_0  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:CLK1588_IB_CFG
 *
 * Configuration Registers for 1588 Clock Input Buffer
 */


/** 
 * \brief Configuration Registers 1 for 1588 Clock Input Buffer
 *
 * \details
 * Configuration Registers 1 for 1588 Clock Input Buffer
 *
 * Register: \a VENICE_GLOBAL:CLK1588_IB_CFG:CLK1588_IB_CFG1
 */
#define VTSS_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1  VTSS_IOREG(0x1e, 0, 0x0230)

/** 
 * \brief
 * settings for1588 clock input buffer BIAS
 * 
 * [0] = enable single rail input from P branch, 1: enable, 0: disable
 * [1] = enable single rail input from N branch, 1: enable, 0: disable
 * [2] = reserved
 * [3] = enable input termination, 1: enable, 0: disable
 * [7:4] = reserved

 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1 . CLK1588_IB_BIAS_CTRL
 */
#define  VTSS_F_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * enable BIAS for clk1588 input buffer, default disable

 *
 * \details 
 * 0: Input Buffer Disable
 * 1: Input Buffer Enable
 *
 * Field: VTSS_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1 . CLK1588_IB_ENA_BIAS
 */
#define  VTSS_F_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_ENA_BIAS  VTSS_BIT(15)


/** 
 * \brief Configuration Registers 2 for 1588 Clock Input Buffer
 *
 * \details
 * Configuration Registers 2 for 1588 Clock Input Buffer
 *
 * Register: \a VENICE_GLOBAL:CLK1588_IB_CFG:CLK1588_IB_CFG2
 */
#define VTSS_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2  VTSS_IOREG(0x1e, 0, 0x0231)

/** 
 * \brief
 * settings for 1588 clock input buffer,
 * 
 * 
 * [1:0]  = select value for adjustable reference voltage from bandgap
 * voltage, 0: 490mV, 1: 508mV, 2: 487mV, 3: 478mV
 * [8:2] = reserved
 * [9] = enable common mode voltage termination to VDD, 1: enable, 0:
 * disable
 * [15:10] = value for resistor calibration (RCOMP), 15: lowest value 0:
 * highest value

 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2 . CLK1588_IB_CTRL
 */
#define  VTSS_F_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2_CLK1588_IB_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2_CLK1588_IB_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2_CLK1588_IB_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VENICE_GLOBAL:F2DF_DFT
 *
 * F2DF DFT Configuration and Status Register set
 */


/** 
 * \brief F2DF DFT Main configuration register 1
 *
 * \details
 * Main configuration register 1 for F2DF DFT.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTRX_CFG_1
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1  VTSS_IOREG(0x1e, 0, 0x0250)

/** 
 * \brief
 * Disables error generation based on stuck_at_par errors,
 *
 * \details 
 * 0: stuck_at_par error generates 63 errors per clock cycle (in PRBS mode
 * only)
 * 1: stuck_at_par error does not generate errors
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . STUCK_AT_PAR_MASK_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_STUCK_AT_PAR_MASK_CFG  VTSS_BIT(12)

/** 
 * \brief
 * Disables error generation based on stuck_at_01 errors,
 *
 * \details 
 * 0: stuck_at_01 error generates 63 errors per clock cycle (in PRBS mode
 * only)
 * 1: stuck_at_01 error does not generate errors
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . STUCK_AT_01_MASK_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_STUCK_AT_01_MASK_CFG  VTSS_BIT(11)

/** 
 * \brief
 * Enables data through from gearbox to gearbox
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . DIRECT_THROUGH_ENA_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_DIRECT_THROUGH_ENA_CFG  VTSS_BIT(10)

/** 
 * \brief
 * Captures data from error counter to allow reading of stable data
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . ERR_CNT_CAPT_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_ERR_CNT_CAPT_CFG  VTSS_BIT(9)

/** 
 * \brief
 * States in which error counting is enabled
 *
 * \details 
 * 3:all but IDLE; 2:check 1:stable+check
 * 0:wait_stable+stable+check
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . BIST_CNT_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_BIST_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,5,2)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_BIST_CNT_CFG     VTSS_ENCODE_BITMASK(5,2)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_BIST_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,5,2)

/** 
 * \brief
 * Disable change of stored patterns (e.g. to avoid changes during
 * read-out)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . FREEZE_PATTERN_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_FREEZE_PATTERN_CFG  VTSS_BIT(4)

/** 
 * \brief
 * Selects pattern to check
 *
 * \details 
 * 0: PRBS pattern
 * 1: constant pattern
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . CHK_MODE_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_CHK_MODE_CFG  VTSS_BIT(3)

/** 
 * \brief
 * Selects DES interface width
 *
 * \details 
 * 0:8
 * 1:10
 * 2:16
 * 3:20
 * 4:32
 * 5:40 (default)
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1 . RX_WID_SEL_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_RX_WID_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_RX_WID_SEL_CFG     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_1_RX_WID_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/** 
 * \brief F2DF DFT Main configuration register 2
 *
 * \details
 * Main configuration register 2 for F2DF DFT.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTRX_CFG_2
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2  VTSS_IOREG(0x1e, 0, 0x0251)

/** 
 * \brief
 * Pattern generator: 0:bytes mode; 1:10-bits word mode
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . RX_WORD_MODE_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_RX_WORD_MODE_CFG  VTSS_BIT(14)

/** 
 * \brief
 * Selects PRBS check
 *
 * \details 
 * 0: prbs7
 * 1: prbs15
 * 2: prbs23
 * 3: prbs11
 * 4: prbs31 (default)
 * 5: prbs9
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . RX_PRBS_SEL_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_RX_PRBS_SEL_CFG(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_RX_PRBS_SEL_CFG     VTSS_ENCODE_BITMASK(11,3)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_RX_PRBS_SEL_CFG(x)  VTSS_EXTRACT_BITFIELD(x,11,3)

/** 
 * \brief
 * Enables PRBS checker input inversion
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . INV_ENA_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_INV_ENA_CFG  VTSS_BIT(10)

/** 
 * \brief
 * Selects compare mode
 *
 * \details 
 * 0: compare mode possible
 * 1 learn mode is forced
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . CMP_MODE_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_CMP_MODE_CFG  VTSS_BIT(9)

/** 
 * \brief
 * Number of consecutive errors/non-errors before transitioning to
 * respective state
 *
 * \details 
 * value = num-40-bits-words + 1
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . LRN_CNT_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_LRN_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_LRN_CNT_CFG     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_LRN_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/** 
 * \brief
 * SW reset of error counter; rising edge activates reset
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . CNT_RST
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_CNT_RST  VTSS_BIT(5)

/** 
 * \brief
 * Selects modes in which error counter is active
 *
 * \details 
 * 0:learn and compare mode
 * 1:transition between modes
 * 2:learn mode
 * 3:compare mode
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . CNT_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_CNT_CFG(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_CNT_CFG     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_CNT_CFG(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/** 
 * \brief
 * BIST mode
 *
 * \details 
 * 0: off
 * 1: BIST
 * 2: BER
 * 3:CONT (infinite mode)
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . BIST_MODE_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_BIST_MODE_CFG(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_BIST_MODE_CFG     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_BIST_MODE_CFG(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/** 
 * \brief
 * Enable RX DFT capability
 *
 * \details 
 * 0: Disable DFT
 * 1: Enable DFT
 *
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2 . F2DF_DFTRX_ENA
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_CFG_2_F2DF_DFTRX_ENA  VTSS_BIT(0)


/** 
 * \brief F2DF DFT pattern mask configuration register 1 
 *
 * \details
 * Configuration register 1 for F2DF DFT to mask data bits preventing error
 * counting for these bits.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTRX_MASK_CFG_1
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_1  VTSS_IOREG(0x1e, 0, 0x0252)

/** 
 * \brief
 * Mask out (active high) errors in 16 bit MSB data bits [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_1 . LSB_MASK_CFG_1
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_1_LSB_MASK_CFG_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_1_LSB_MASK_CFG_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_1_LSB_MASK_CFG_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT pattern mask configuration register 2
 *
 * \details
 * Configuration register 2 for F2DF DFT to mask data bits preventing error
 * counting for these bits.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTRX_MASK_CFG_2
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_2  VTSS_IOREG(0x1e, 0, 0x0253)

/** 
 * \brief
 * Mask out (active high) errors in 16 LSB data bits [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_2 . LSB_MASK_CFG_2
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_2_LSB_MASK_CFG_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_2_LSB_MASK_CFG_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_MASK_CFG_2_LSB_MASK_CFG_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT Pattern checker configuration register 1
 *
 * \details
 * Pattern checker configuration register 1 for F2DF DFT.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTRX_PAT_CFG_1
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_1  VTSS_IOREG(0x1e, 0, 0x0254)

/** 
 * \brief
 * Mask out (active high) errors in 8 MSB data bits
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_1 . MSB_MASK_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_1_MSB_MASK_CFG(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_1_MSB_MASK_CFG     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_1_MSB_MASK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Pattern read enable
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_1 . PAT_READ_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_1_PAT_READ_CFG  VTSS_BIT(0)


/** 
 * \brief F2DF DFT Pattern checker configuration register 2
 *
 * \details
 * Pattern checker configuration register 2 for F2DF DFT.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTRX_PAT_CFG_2
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2  VTSS_IOREG(0x1e, 0, 0x0255)

/** 
 * \brief
 * Maximum address in Checker (before continuing with address 0)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2 . MAX_ADDR_CHK_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2_MAX_ADDR_CHK_CFG(x)  VTSS_ENCODE_BITFIELD(x,8,4)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2_MAX_ADDR_CHK_CFG     VTSS_ENCODE_BITMASK(8,4)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2_MAX_ADDR_CHK_CFG(x)  VTSS_EXTRACT_BITFIELD(x,8,4)

/** 
 * \brief
 * Address to read patterns from used by SW
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2 . READ_ADDR_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2_READ_ADDR_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2_READ_ADDR_CFG     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTRX_PAT_CFG_2_READ_ADDR_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


/** 
 * \brief F2DF DFT BIST configuration register A
 *
 * \details
 * BIST configuration register A for F2DF DFT controlling 'check and
 * wait-stable' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG0A
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0A  VTSS_IOREG(0x1e, 0, 0x0256)

/** 
 * \brief
 * BIST FSM: threshold to leave DOZE state
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0A . WAKEUP_DLY_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0A_WAKEUP_DLY_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0A_WAKEUP_DLY_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0A_WAKEUP_DLY_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for F2DF DFT controlling 'check and
 * wait-stable' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG0B
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0B  VTSS_IOREG(0x1e, 0, 0x0257)

/** 
 * \brief
 * BIST FSM: threshold to enter FINISHED state
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0B . MAX_BIST_FRAMES_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0B_MAX_BIST_FRAMES_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0B_MAX_BIST_FRAMES_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG0B_MAX_BIST_FRAMES_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT BIST configuration register A
 *
 * \details
 * BIST configuration register A for F2DF DFT  controlling 'stable' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG1A
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1A  VTSS_IOREG(0x1e, 0, 0x0258)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_stable_attempts
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1A . MAX_UNSTABLE_CYC_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1A_MAX_UNSTABLE_CYC_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1A_MAX_UNSTABLE_CYC_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1A_MAX_UNSTABLE_CYC_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for F2DF DFT  controlling 'stable' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG1B
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1B  VTSS_IOREG(0x1e, 0, 0x0259)

/** 
 * \brief
 * BIST FSM: threshold to enter CHECK state
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1B . STABLE_THRES_CFG
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1B_STABLE_THRES_CFG(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1B_STABLE_THRES_CFG     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG1B_STABLE_THRES_CFG(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT BIST configuration register A
 *
 * \details
 * BIST configuration register B for F2DF DFT controlling frame length in
 * 'check' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG2A
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2A  VTSS_IOREG(0x1e, 0, 0x025a)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_bist_frames [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2A . FRAME_LEN_CFG_MSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2A_FRAME_LEN_CFG_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2A_FRAME_LEN_CFG_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2A_FRAME_LEN_CFG_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for F2DF DFT controlling frame length in
 * 'check' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG2B
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2B  VTSS_IOREG(0x1e, 0, 0x025b)

/** 
 * \brief
 * BIST FSM: threshold to iterate counter for max_bist_frames [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2B . FRAME_LEN_CFG_LSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2B_FRAME_LEN_CFG_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2B_FRAME_LEN_CFG_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG2B_FRAME_LEN_CFG_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT BIST configuration register A
 *
 * \details
 * BIST configuration register A for F2DF DFT controlling stable attempts
 * in ' wait-stable' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG3A
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3A  VTSS_IOREG(0x1e, 0, 0x025c)

/** 
 * \brief
 * BIST FSM: threshold to enter SYNC_ERR state [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3A . MAX_STABLE_ATTEMPTS_CFG_MSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3A_MAX_STABLE_ATTEMPTS_CFG_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3A_MAX_STABLE_ATTEMPTS_CFG_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3A_MAX_STABLE_ATTEMPTS_CFG_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT BIST configuration register B
 *
 * \details
 * BIST configuration register B for F2DF DFT controlling stable attempts
 * in ' wait-stable' mode.
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTBIST_CFG3B
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3B  VTSS_IOREG(0x1e, 0, 0x025d)

/** 
 * \brief
 * BIST FSM: threshold to enter SYNC_ERR state [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3B . MAX_STABLE_ATTEMPTS_CFG_LSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3B_MAX_STABLE_ATTEMPTS_CFG_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3B_MAX_STABLE_ATTEMPTS_CFG_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTBIST_CFG3B_MAX_STABLE_ATTEMPTS_CFG_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT error status register 1
 *
 * \details
 * Status register 1 for F2DF DFT containing the error counter value
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTERR_STAT_1
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_1  VTSS_IOREG(0x1e, 0, 0x025e)

/** 
 * \brief
 * Counter output depending on cnt_cfg_i [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_1 . ERR_CNT_MSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_1_ERR_CNT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_1_ERR_CNT_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_1_ERR_CNT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT error status register 2
 *
 * \details
 * Status register B2 for F2DF DFT containing the error counter value
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTERR_STAT_2
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_2  VTSS_IOREG(0x1e, 0, 0x025f)

/** 
 * \brief
 * Counter output depending on cnt_cfg_i [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_2 . ERR_CNT_LSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_2_ERR_CNT_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_2_ERR_CNT_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTERR_STAT_2_ERR_CNT_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT PRBS status register 1
 *
 * \details
 * Status register 1 for F2DF DFT containing the PRBS data related to 1st
 * sync lost event
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTPRBS_STAT_1
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_1  VTSS_IOREG(0x1e, 0, 0x0260)

/** 
 * \brief
 * PRBS data after first sync lost [31:16]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_1 . PRBS_DATA_STAT_MSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_1_PRBS_DATA_STAT_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_1_PRBS_DATA_STAT_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_1_PRBS_DATA_STAT_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT PRBS status register 2
 *
 * \details
 * Status register 2 for F2DF DFT containing the PRBS data related to 1st
 * sync lost event
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTPRBS_STAT_2
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_2  VTSS_IOREG(0x1e, 0, 0x0261)

/** 
 * \brief
 * PRBS data after first sync lost [15:0]
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_2 . PRBS_DATA_STAT_LSB
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_2_PRBS_DATA_STAT_LSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_2_PRBS_DATA_STAT_LSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTPRBS_STAT_2_PRBS_DATA_STAT_LSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief F2DF DFT miscellaneous status register 1
 *
 * \details
 * Status register 1 for F2DF DFT
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTMAIN_STAT_1
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_1  VTSS_IOREG(0x1e, 0, 0x0262)

/** 
 * \brief
 * 10 bits data word at address 'read_addr_cfg' used for further
 * observation by SW
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_1 . CMP_DATA_STAT
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_1_CMP_DATA_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,10)
#define  VTSS_M_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_1_CMP_DATA_STAT     VTSS_ENCODE_BITMASK(0,10)
#define  VTSS_X_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_1_CMP_DATA_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,10)


/** 
 * \brief F2DF DFT miscellaneous status register 2
 *
 * \details
 * Status register 2 for F2DF DFT
 *
 * Register: \a VENICE_GLOBAL:F2DF_DFT:F2DF_DFTMAIN_STAT_2
 */
#define VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2  VTSS_IOREG(0x1e, 0, 0x0263)

/** 
 * \brief
 * Data input is unchanged for all 40 parallel bits for at least 7 clock
 * cycles (defined by c_STCK_CNT_THRES)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2 . STUCK_AT_PAR
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2_STUCK_AT_PAR  VTSS_BIT(5)

/** 
 * \brief
 * Data input is constantly 0 or constantly 1 for all 40 parallel bits for
 * at least 7 clock cycles (defined by c_STCK_CNT_THRES)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2 . STUCK_AT_01
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2_STUCK_AT_01  VTSS_BIT(4)

/** 
 * \brief
 * BIST: no sync found since BIST enabled
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2 . NO_SYNC
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2_NO_SYNC  VTSS_BIT(3)

/** 
 * \brief
 * BIST: input data not stable
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2 . INSTABLE
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2_INSTABLE  VTSS_BIT(2)

/** 
 * \brief
 * BIST not complete (i.e. not reached stable state or following)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2 . INCOMPLETE
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2_INCOMPLETE  VTSS_BIT(1)

/** 
 * \brief
 * BIST is active (i.e. left DOZE but did not enter a final state)
 *
 * \details 
 * Field: VTSS_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2 . ACTIVE
 */
#define  VTSS_F_VENICE_GLOBAL_F2DF_DFT_F2DF_DFTMAIN_STAT_2_ACTIVE  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:FEATURE_STAT
 *
 * Registers for Device Feature Status
 */


/** 
 * \brief Device Feature Status
 *
 * \details
 * Device Feature Status
 *
 * Register: \a VENICE_GLOBAL:FEATURE_STAT:FEATURE_STAT
 */
#define VTSS_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT  VTSS_IOREG(0x1e, 0, 0x02a0)

/** 
 * \brief
 * Indicates the number of active line side port 
 *
 * \details 
 * 0: 2 ports
 * 1: 1 port
 *
 * Field: VTSS_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT . LINE_ACTIVE_STAT
 */
#define  VTSS_F_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT_LINE_ACTIVE_STAT  VTSS_BIT(3)

/** 
 * \brief
 * Indicates the status of MACsec availability on the device
 *
 * \details 
 * 0: MACsec block may be used
 * 1: MACsec block is disabled
 *
 * Field: VTSS_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT . MACSEC_STAT
 */
#define  VTSS_F_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT_MACSEC_STAT  VTSS_BIT(2)

/** 
 * \brief
 * Indicates the 1588 timestamp accuracy 
 *
 * \details 
 * 0: 4ns
 * 1: 8ns
 *
 * Field: VTSS_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT . TIMESTAMP_ACC_STAT
 */
#define  VTSS_F_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT_TIMESTAMP_ACC_STAT  VTSS_BIT(1)

/** 
 * \brief
 * Indicates the MACsec encryption key capability
 *
 * \details 
 * 0: 128/256-bit 
 * 1: 128-bit
 *
 * Field: VTSS_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT . MACSEC_KEY_STAT
 */
#define  VTSS_F_VENICE_GLOBAL_FEATURE_STAT_FEATURE_STAT_MACSEC_KEY_STAT  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:SPI_CTRL
 *
 * SPI mode control register
 */


/** 
 * \brief SPI mode control register
 *
 * \details
 * SPI mode control register
 *
 * Register: \a VENICE_GLOBAL:SPI_CTRL:SPI_CTRL
 */
#define VTSS_VENICE_GLOBAL_SPI_CTRL_SPI_CTRL  VTSS_IOREG(0x1e, 0, 0x02b0)

/** 
 * \brief
 * Set the SPI interface mode
 *
 * \details 
 * 0: Normal mode
 * 1: Fast mode
 *
 * Field: VTSS_VENICE_GLOBAL_SPI_CTRL_SPI_CTRL . FAST_MODE
 */
#define  VTSS_F_VENICE_GLOBAL_SPI_CTRL_SPI_CTRL_FAST_MODE  VTSS_BIT(0)

/**
 * Register Group: \a VENICE_GLOBAL:RCOMP_CFG
 *
 * RCOMP Configuration Registers
 */

/**
 * Register Group: \a VENICE_GLOBAL:RCOMP_STATUS
 *
 * RCOMP Status Registers
 */


/** 
 * \brief RCOMP Status
 *
 * \details
 * Status register bits for the RCOMP
 *
 * Register: \a VENICE_GLOBAL:RCOMP_STATUS:RCOMP_STATUS
 */
#define VTSS_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS  VTSS_IOREG(0x1e, 0, 0x7010)

/** 
 * \brief
 * Resistor comparison activity
 *
 * \details 
 * 0: resistor measurement finished or inactive
 * 1: resistor measurement in progress
 *
 * Field: VTSS_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS . BUSY
 */
#define  VTSS_F_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_BUSY  VTSS_BIT(12)

/** 
 * \brief
 * Alarm signal if rcomp isn't best choice anymore
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: VTSS_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS . DELTA_ALERT
 */
#define  VTSS_F_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_DELTA_ALERT  VTSS_BIT(7)

/** 
 * \brief
 * Measured resistor value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: VTSS_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS . RCOMP
 */
#define  VTSS_F_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_RCOMP     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_VENICE_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a VENICE_GLOBAL:SYNC_ETH_CFG
 *
 * SYNC_ETH Configuration Registers
 */


/** 
 * \brief SYNC ETH Configuration 0
 *
 * \details
 * Selection register for SYNC_ETH.
 *
 * Register: \a VENICE_GLOBAL:SYNC_ETH_CFG:SYNC_ETH_CFG
 */
#define VTSS_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG  VTSS_IOREG(0x1e, 0, 0x7100)

/** 
 * \brief
 * Select recovered clock divider B
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG . SEL_RECO_CLK_B
 */
#define  VTSS_F_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_B(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_B     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_B(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/** 
 * \brief
 * Select recovered clock divider A
 *
 * \details 
 * 0: No clock dividing
 * 1: Divide clock by 5
 * 2: Divide clock by 4
 * 3: Reserved
 *
 * Field: VTSS_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG . SEL_RECO_CLK_A
 */
#define  VTSS_F_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_A(x)  VTSS_ENCODE_BITFIELD(x,2,2)
#define  VTSS_M_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_A     VTSS_ENCODE_BITMASK(2,2)
#define  VTSS_X_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_SEL_RECO_CLK_A(x)  VTSS_EXTRACT_BITFIELD(x,2,2)

/** 
 * \brief
 * Enable recovered clock B pad
 *
 * \details 
 * 0: Disable (high-impedance)
 * 1: Enable (output recovered clock)
 *
 * Field: VTSS_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG . RECO_CLK_B_ENA
 */
#define  VTSS_F_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_B_ENA  VTSS_BIT(1)

/** 
 * \brief
 * Enable recovered clock A pad
 *
 * \details 
 * 0: Disable (high-impedance)
 * 1: Enable (output recovered clock)
 *
 * Field: VTSS_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG . RECO_CLK_A_ENA
 */
#define  VTSS_F_VENICE_GLOBAL_SYNC_ETH_CFG_SYNC_ETH_CFG_RECO_CLK_A_ENA  VTSS_BIT(0)


#endif /* _VTSS_VENICE_REGS_VENICE_GLOBAL_H_ */
