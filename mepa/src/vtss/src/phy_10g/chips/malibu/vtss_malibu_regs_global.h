// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_MALIBU_REGS_GLOBAL_H_
#define _VTSS_MALIBU_REGS_GLOBAL_H_


#include "vtss_malibu_regs_common.h"

/*********************************************************************** 
 *
 * Target: \a GLOBAL
 *
 * 
 *
 ***********************************************************************/

/**
 * Register Group: \a GLOBAL:Device_Info
 *
 * Device ID and Revision
 */


/** 
 * \brief Device ID
 *
 * \details
 * Device ID
 *
 * Register: \a GLOBAL:Device_Info:Device_ID
 */
#define VTSS_GLOBAL_Device_Info_Device_ID    VTSS_IOREG(0x1e, 0, 0x0000)

/** 
 * \brief
 * This is the device ID register.
 * The die design is used in multiple product SKUs.  It is impossible to
 * assign a default part number here to support all SKUs simultaneously.
 *
 * \details 
 * Field: VTSS_GLOBAL_Device_Info_Device_ID . Device_ID
 */
#define  VTSS_F_GLOBAL_Device_Info_Device_ID_Device_ID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Device_Info_Device_ID_Device_ID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Device_Info_Device_ID_Device_ID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Device Revision
 *
 * \details
 * Device Revision
 *
 * Register: \a GLOBAL:Device_Info:Device_Revision
 */
#define VTSS_GLOBAL_Device_Info_Device_Revision  VTSS_IOREG(0x1e, 0, 0x0001)

/** 
 * \brief
 * This is the revision number register.
 *
 * \details 
 * Field: VTSS_GLOBAL_Device_Info_Device_Revision . Device_Revision
 */
#define  VTSS_F_GLOBAL_Device_Info_Device_Revision_Device_Revision(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_GLOBAL_Device_Info_Device_Revision_Device_Revision     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_GLOBAL_Device_Info_Device_Revision_Device_Revision(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a GLOBAL:Block_Level_Software_Reset
 *
 * Not documented
 */


/** 
 * \brief Block Level Software Reset
 *
 * \details
 * Register: \a GLOBAL:Block_Level_Software_Reset:Block_Level_Software_Reset
 */
#define VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset  VTSS_IOREG(0x1e, 0, 0x0002)

/** 
 * \brief
 * Reset the datapath and configuration registers in channel 3.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Channel_3
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Channel_3  VTSS_BIT(11)

/** 
 * \brief
 * Reset the datapath and configuration registers in channel 2.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Channel_2
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Channel_2  VTSS_BIT(10)

/** 
 * \brief
 * Reset the datapath and configuration registers in channel 1.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Channel_1
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Channel_1  VTSS_BIT(9)

/** 
 * \brief
 * Reset the datapath and configuration registers in channel 0.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Channel_0
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Channel_0  VTSS_BIT(8)

/** 
 * \brief
 * Reset the F2DF logic.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_DF2F
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_DF2F  VTSS_BIT(7)

/** 
 * \brief
 * Reset the F2DF logic.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_F2DF
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_F2DF  VTSS_BIT(6)

/** 
 * \brief
 * Reset the TWS-slave interface.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_TWS_Slave
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_TWS_Slave  VTSS_BIT(5)

/** 
 * \brief
 * Reset the MDIO interface.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_MDIO
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_MDIO  VTSS_BIT(3)

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
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_SPI
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_SPI  VTSS_BIT(2)

/** 
 * \brief
 * Reset the datapath in all channels and all configuration registers
 * except the GPIO configuration registers (1ExF200-1ExF27F) and global
 * configuration registers (1Ex0000-1Ex71FF).  GPIO functions are not
 * modified when using this software reset since the GPIO configuration
 * registers are not reset to default settings.  The global configuration
 * registers are used to program RCOMP, host side PLL and line side PLL
 * logic blocks.
 *
 * \details 
 * 0: Normal Operation
 * 1: Reset
 *
 * Field: VTSS_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset . Software_Reset_Chip
 */
#define  VTSS_F_GLOBAL_Block_Level_Software_Reset_Block_Level_Software_Reset_Software_Reset_Chip  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:Pin_Status
 *
 * Not documented
 */


/** 
 * \brief Pin Status
 *
 * \details
 * Register: \a GLOBAL:Pin_Status:Pin_Status
 */
#define VTSS_GLOBAL_Pin_Status_Pin_Status    VTSS_IOREG(0x1e, 0, 0x0004)

/** 
 * \brief
 * State of MODE3 pin
 *
 * \details 
 * 0: Logic low
 * 1: Logic high
 *
 * Field: VTSS_GLOBAL_Pin_Status_Pin_Status . MODE3_Pin_State
 */
#define  VTSS_F_GLOBAL_Pin_Status_Pin_Status_MODE3_Pin_State  VTSS_BIT(3)

/** 
 * \brief
 * State of MODE2 pin
 *
 * \details 
 * 0: Logic low
 * 1: Logic high
 *
 * Field: VTSS_GLOBAL_Pin_Status_Pin_Status . MODE2_Pin_State
 */
#define  VTSS_F_GLOBAL_Pin_Status_Pin_Status_MODE2_Pin_State  VTSS_BIT(2)

/** 
 * \brief
 * State of MODE1 pin
 *
 * \details 
 * 0: Logic low
 * 1: Logic high
 *
 * Field: VTSS_GLOBAL_Pin_Status_Pin_Status . MODE1_Pin_State
 */
#define  VTSS_F_GLOBAL_Pin_Status_Pin_Status_MODE1_Pin_State  VTSS_BIT(1)

/** 
 * \brief
 * State of MODE0 pin
 *
 * \details 
 * 0: Logic low
 * 1: Logic high
 *
 * Field: VTSS_GLOBAL_Pin_Status_Pin_Status . MODE0_Pin_State
 */
#define  VTSS_F_GLOBAL_Pin_Status_Pin_Status_MODE0_Pin_State  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:Secret_Rev_Num
 *
 * Not documented
 */


/** 
 * \brief Super Secret Revision Number
 *
 * \details
 * Register: \a GLOBAL:Secret_Rev_Num:Secret_Rev_Num
 */
#define VTSS_GLOBAL_Secret_Rev_Num_Secret_Rev_Num  VTSS_IOREG(0x1e, 0, 0x0011)

/** 
 * \brief
 * This is the super secret revision number register.  It is put in place
 * for API to distinguish between hardware revisions for cases where the
 * part's revision number advertised to customers is not incremented....for
 * what ever reason.
 *
 * \details 
 * Field: VTSS_GLOBAL_Secret_Rev_Num_Secret_Rev_Num . SuperSecret_Rev_Num
 */
#define  VTSS_F_GLOBAL_Secret_Rev_Num_Secret_Rev_Num_SuperSecret_Rev_Num(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_GLOBAL_Secret_Rev_Num_Secret_Rev_Num_SuperSecret_Rev_Num     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_GLOBAL_Secret_Rev_Num_Secret_Rev_Num_SuperSecret_Rev_Num(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a GLOBAL:Temp_Monitor
 *
 * Temperature Monitor
 */


/** 
 * \brief Temperature Monitor Threshold Settings
 *
 * \details
 * Temperature Monitor Threshold Settings
 *
 * Register: \a GLOBAL:Temp_Monitor:Temp_Mon_Threshold
 */
#define VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Threshold  VTSS_IOREG(0x1e, 0, 0x01c0)

/** 
 * \brief
 * Determines trigger for high temp alarm
 *
 * \details 
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Threshold . High_Temp_Threshold_Setting
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_High_Temp_Threshold_Setting(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_High_Temp_Threshold_Setting     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_High_Temp_Threshold_Setting(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/** 
 * \brief
 * Determines trigger for low temp alarm

 *
 * \details 
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Threshold . Low_Temp_Threshold_Setting
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_Low_Temp_Threshold_Setting(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_Low_Temp_Threshold_Setting     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GLOBAL_Temp_Monitor_Temp_Mon_Threshold_Low_Temp_Threshold_Setting(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/** 
 * \brief Temperature Monitor Registers
 *
 * \details
 * Temperature Monitor Registers

 *
 * Register: \a GLOBAL:Temp_Monitor:Temp_Mon_Regs
 */
#define VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Regs  VTSS_IOREG(0x1e, 0, 0x01c1)

/** 
 * \brief
 * Enables the temperature monitor block

 *
 * \details 
 * 0: Temperature Monitor Disable
 * 1: Temperature Monitor Enable

 *
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Enable_Digital_Temp_Monitor
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Enable_Digital_Temp_Monitor  VTSS_BIT(12)

/** 
 * \brief
 * Initiates the temperature sampling process

 *
 * \details 
 * 0: Temperature Monitor idles
 * 1: Temperature Monitor starts sampling
 *
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Temp_Monitor_Run
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Run  VTSS_BIT(11)

/** 
 * \brief
 * Temp Monitor Done Status

 *
 * \details 
 * 0: Temperature Monitor is not done sampling
 * 1: Temperature Monitor is done sampling, data in Temp_Monitor_Reading is
 * ready
 *
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Temp_Monitor_Done_Status
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Done_Status  VTSS_BIT(10)

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
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Regs . High_Temp_Alarm
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Regs_High_Temp_Alarm  VTSS_BIT(9)

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
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Low_Temp_Alarm
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Low_Temp_Alarm  VTSS_BIT(8)

/** 
 * \brief
 * Temperature Monitor Reading
 * This is the digital reading of the temperature monitor.  
 * Value is not valid unless Temp_Monitor_Done_Status = 1

 *
 * \details 
 * Field: VTSS_GLOBAL_Temp_Monitor_Temp_Mon_Regs . Temp_Monitor_Reading
 */
#define  VTSS_F_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Reading(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Reading     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GLOBAL_Temp_Monitor_Temp_Mon_Regs_Temp_Monitor_Reading(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * Register Group: \a GLOBAL:Global_Spare_CFG_STAT
 *
 * Not documented
 */


/** 
 * \brief Spare Status 1
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_Status_1
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_1  VTSS_IOREG(0x1e, 0, 0x01d0)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_1 . Spare_Status_1
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_1_Spare_Status_1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_1_Spare_Status_1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_1_Spare_Status_1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare Status 2
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_Status_2
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_2  VTSS_IOREG(0x1e, 0, 0x01d1)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_2 . Spare_Status_2
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_2_Spare_Status_2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_2_Spare_Status_2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_2_Spare_Status_2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare Status 3
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_Status_3
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_3  VTSS_IOREG(0x1e, 0, 0x01d2)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_3 . Spare_Status_3
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_3_Spare_Status_3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_3_Spare_Status_3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_3_Spare_Status_3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare Status 4
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_Status_4
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_4  VTSS_IOREG(0x1e, 0, 0x01d3)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_4 . Spare_Status_4
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_4_Spare_Status_4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_4_Spare_Status_4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_Status_4_Spare_Status_4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW1
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW1
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW1  VTSS_IOREG(0x1e, 0, 0x01d4)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW1 . Spare1
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW1_Spare1(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW1_Spare1     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW1_Spare1(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW2
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW2
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW2  VTSS_IOREG(0x1e, 0, 0x01d5)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW2 . Spare2
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW2_Spare2(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW2_Spare2     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW2_Spare2(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW3
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW3
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW3  VTSS_IOREG(0x1e, 0, 0x01d6)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW3 . Spare3
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW3_Spare3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW3_Spare3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW3_Spare3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW4
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW4
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW4  VTSS_IOREG(0x1e, 0, 0x01d7)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW4 . Spare4
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW4_Spare4(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW4_Spare4     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW4_Spare4(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW5
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW5
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW5  VTSS_IOREG(0x1e, 0, 0x01d8)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW5 . Spare5
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW5_Spare5(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW5_Spare5     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW5_Spare5(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW6
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW6
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW6  VTSS_IOREG(0x1e, 0, 0x01d9)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW6 . Spare6
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW6_Spare6(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW6_Spare6     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW6_Spare6(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW7
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW7
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW7  VTSS_IOREG(0x1e, 0, 0x01da)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW7 . Spare7
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW7_Spare7(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW7_Spare7     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW7_Spare7(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW8
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW8
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW8  VTSS_IOREG(0x1e, 0, 0x01db)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW8 . Spare8
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW8_Spare8(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW8_Spare8     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW8_Spare8(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW9
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW9
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW9  VTSS_IOREG(0x1e, 0, 0x01dc)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW9 . Spare9
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW9_Spare9(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW9_Spare9     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW9_Spare9(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW10
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW10
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW10  VTSS_IOREG(0x1e, 0, 0x01dd)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW10 . Spare10
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW10_Spare10(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW10_Spare10     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW10_Spare10(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW11
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW11
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW11  VTSS_IOREG(0x1e, 0, 0x01de)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW11 . Spare11
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW11_Spare11(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW11_Spare11     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW11_Spare11(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW12
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW12
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW12  VTSS_IOREG(0x1e, 0, 0x01df)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW12 . Spare12
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW12_Spare12(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW12_Spare12     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW12_Spare12(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW13
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW13
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW13  VTSS_IOREG(0x1e, 0, 0x01e0)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW13 . Spare13
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW13_Spare13(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW13_Spare13     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW13_Spare13(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW14
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW14
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW14  VTSS_IOREG(0x1e, 0, 0x01e1)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW14 . Spare14
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW14_Spare14(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW14_Spare14     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW14_Spare14(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW15
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW15
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW15  VTSS_IOREG(0x1e, 0, 0x01e2)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW15 . Spare15
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW15_Spare15(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW15_Spare15     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW15_Spare15(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW16
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW16
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW16  VTSS_IOREG(0x1e, 0, 0x01e3)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW16 . Spare16
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW16_Spare16(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW16_Spare16     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW16_Spare16(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW17
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW17
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW17  VTSS_IOREG(0x1e, 0, 0x01e4)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW17 . Spare17
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW17_Spare17(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW17_Spare17     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW17_Spare17(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW18
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW18
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW18  VTSS_IOREG(0x1e, 0, 0x01e5)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW18 . Spare18
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW18_Spare18(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW18_Spare18     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW18_Spare18(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW19
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW19
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW19  VTSS_IOREG(0x1e, 0, 0x01e6)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW19 . Spare19
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW19_Spare19(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW19_Spare19     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW19_Spare19(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW20
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW20
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW20  VTSS_IOREG(0x1e, 0, 0x01e7)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW20 . Spare20
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW20_Spare20(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW20_Spare20     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW20_Spare20(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW21
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW21
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW21  VTSS_IOREG(0x1e, 0, 0x01e8)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW21 . Spare21
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW21_Spare21(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW21_Spare21     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW21_Spare21(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW22
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW22
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW22  VTSS_IOREG(0x1e, 0, 0x01e9)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW22 . Spare22
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW22_Spare22(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW22_Spare22     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW22_Spare22(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW23
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW23
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW23  VTSS_IOREG(0x1e, 0, 0x01ea)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW23 . Spare23
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW23_Spare23(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW23_Spare23     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW23_Spare23(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW24
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW24
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW24  VTSS_IOREG(0x1e, 0, 0x01eb)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW24 . Spare24
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW24_Spare24(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW24_Spare24     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW24_Spare24(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW25
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW25
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW25  VTSS_IOREG(0x1e, 0, 0x01ec)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW25 . Spare25
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW25_Spare25(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW25_Spare25     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW25_Spare25(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW26
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW26
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW26  VTSS_IOREG(0x1e, 0, 0x01ed)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW26 . Spare26
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW26_Spare26(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW26_Spare26     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW26_Spare26(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW27
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW27
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW27  VTSS_IOREG(0x1e, 0, 0x01ee)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW27 . Spare27
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW27_Spare27(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW27_Spare27     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW27_Spare27(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW28
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW28
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW28  VTSS_IOREG(0x1e, 0, 0x01ef)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW28 . Spare28
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW28_Spare28(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW28_Spare28     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW28_Spare28(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW29
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW29
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW29  VTSS_IOREG(0x1e, 0, 0x01f0)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW29 . Spare29
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW29_Spare29(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW29_Spare29     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW29_Spare29(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW30
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW30
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW30  VTSS_IOREG(0x1e, 0, 0x01f1)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW30 . Spare30
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW30_Spare30(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW30_Spare30     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW30_Spare30(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW31
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW31
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW31  VTSS_IOREG(0x1e, 0, 0x01f2)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW31 . Spare31
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW31_Spare31(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW31_Spare31     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW31_Spare31(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/** 
 * \brief Spare RW32
 *
 * \details
 * Register: \a GLOBAL:Global_Spare_CFG_STAT:Spare_RW32
 */
#define VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW32  VTSS_IOREG(0x1e, 0, 0x01f3)

/** 
 * \details 
 * Field: VTSS_GLOBAL_Global_Spare_CFG_STAT_Spare_RW32 . Spare32
 */
#define  VTSS_F_GLOBAL_Global_Spare_CFG_STAT_Spare_RW32_Spare32(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_Global_Spare_CFG_STAT_Spare_RW32_Spare32     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_Global_Spare_CFG_STAT_Spare_RW32_Spare32(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a GLOBAL:PLL_REFCK_SRC
 *
 * Select Reference Clock Sources
 */


/** 
 * \brief Select Host Side PLL Reference Clock Source
 *
 * \details
 * Select Host Side PLL Reference Clock Source
 *
 * Register: \a GLOBAL:PLL_REFCK_SRC:HOST_PLL_REFCK_SRC
 */
#define VTSS_GLOBAL_PLL_REFCK_SRC_HOST_PLL_REFCK_SRC  VTSS_IOREG(0x1e, 0, 0x0210)

/** 
 * \brief
 * Select Host Side PLL Reference Clock Source
 *
 * \details 
 * 0: Reference Clock from HREFCK pin
 * 1: Reference Clock from LREFCK pin (signal routed across the die)
 *
 * Field: VTSS_GLOBAL_PLL_REFCK_SRC_HOST_PLL_REFCK_SRC . HOST_PLL_REFCK_SRC
 */
#define  VTSS_F_GLOBAL_PLL_REFCK_SRC_HOST_PLL_REFCK_SRC_HOST_PLL_REFCK_SRC  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:MISC_1588_GPIO
 *
 * Misc 1588 GPIO control
 */


/** 
 * \brief Select 1588 PPS to go to GPIO
 *
 * \details
 * Select 1588 PPS to go to GPIO
 *
 * Register: \a GLOBAL:MISC_1588_GPIO:SELECT_1588_PPS
 */
#define VTSS_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS  VTSS_IOREG(0x1e, 0, 0x0220)

/** 
 * \brief
 * Select virtual PPS_0 or PPS_2 (and associated loopback controls and
 * output enables) to route to PPS
 *
 * \details 
 * 0: PPS_0 and associated control selected
 * 1: PPS_2 and associated control selected
 *
 * Field: VTSS_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS . SELECT_1588_PPS
 */
#define  VTSS_F_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS_SELECT_1588_PPS  VTSS_BIT(4)

/** 
 * \brief
 * Select 1588 PPS_2 or PPS_3 goes to virtual GPIO PPS_3
 *
 * \details 
 * 0: PPS_2 is routed to virtual GPIO PPS_3
 * 1: PPS_3 is routed to virtual GPIO PPS_3
 *
 * Field: VTSS_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS . SELECT_1588_PPS_3
 */
#define  VTSS_F_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS_SELECT_1588_PPS_3  VTSS_BIT(3)

/** 
 * \brief
 * Select 1588 PPS_2 or PPS_3 goes to virtual GPIO PPS_2
 *
 * \details 
 * 0: PPS_2 is routed to virtual GPIO PPS_2
 * 1: PPS_3 is routed to virtual GPIO PPS_2
 *
 * Field: VTSS_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS . SELECT_1588_PPS_2
 */
#define  VTSS_F_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS_SELECT_1588_PPS_2  VTSS_BIT(2)

/** 
 * \brief
 * Select 1588 PPS_0 or PPS_1 goes to virtual GPIO PPS_1
 *
 * \details 
 * 0: PPS_0 is routed to virtual GPIO PPS_1
 * 1: PPS_1 is routed to virtual GPIO PPS_1
 *
 * Field: VTSS_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS . SELECT_1588_PPS_1
 */
#define  VTSS_F_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS_SELECT_1588_PPS_1  VTSS_BIT(1)

/** 
 * \brief
 * Select 1588 PPS_0 or PPS_1 goes to virtual GPIO PPS_0

 *
 * \details 
 * 0: PPS_0 is routed to virtual GPIO PPS_0
 * 1: PPS_1 is routed to virtual GPIO PPS_0
 *
 * Field: VTSS_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS . SELECT_1588_PPS_0
 */
#define  VTSS_F_GLOBAL_MISC_1588_GPIO_SELECT_1588_PPS_SELECT_1588_PPS_0  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:CLK1588_IB_CFG
 *
 * Configuration Registers for 1588 Clock Input Buffer
 */


/** 
 * \brief Configuration Registers 1 for 1588 Clock Input Buffer
 *
 * \details
 * Configuration Registers 1 for 1588 Clock Input Buffer
 *
 * Register: \a GLOBAL:CLK1588_IB_CFG:CLK1588_IB_CFG1
 */
#define VTSS_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1  VTSS_IOREG(0x1e, 0, 0x0230)

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
 * Field: VTSS_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1 . CLK1588_IB_BIAS_CTRL
 */
#define  VTSS_F_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_BIAS_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_BIAS_CTRL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_BIAS_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/** 
 * \brief
 * enable BIAS for clk1588 input buffer, default disable

 *
 * \details 
 * 0: Input Buffer Disable
 * 1: Input Buffer Enable
 *
 * Field: VTSS_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1 . CLK1588_IB_ENA_BIAS
 */
#define  VTSS_F_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG1_CLK1588_IB_ENA_BIAS  VTSS_BIT(15)


/** 
 * \brief Configuration Registers 2 for 1588 Clock Input Buffer
 *
 * \details
 * Configuration Registers 2 for 1588 Clock Input Buffer
 *
 * Register: \a GLOBAL:CLK1588_IB_CFG:CLK1588_IB_CFG2
 */
#define VTSS_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2  VTSS_IOREG(0x1e, 0, 0x0231)

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
 * Field: VTSS_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2 . CLK1588_IB_CTRL
 */
#define  VTSS_F_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2_CLK1588_IB_CTRL(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2_CLK1588_IB_CTRL     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_CLK1588_IB_CFG_CLK1588_IB_CFG2_CLK1588_IB_CTRL(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a GLOBAL:RING_OSC
 *
 * Control and Status Register for Ring Oscilator Test Circuit
 */


/** 
 * \brief Control Register for Ring Oscilator Test Circuit
 *
 * \details
 * Control Register for Ring Oscilator Test Circuit
 *
 * Register: \a GLOBAL:RING_OSC:RING_OSC_CTRL
 */
#define VTSS_GLOBAL_RING_OSC_RING_OSC_CTRL   VTSS_IOREG(0x1e, 0, 0x0240)

/** 
 * \brief
 * Enable Ring Oscilator
 *
 * \details 
 * 0: Ring Oscilator Disable
 * 1: Ring Oscilator Enable

 *
 * Field: VTSS_GLOBAL_RING_OSC_RING_OSC_CTRL . RING_OSC_ENA
 */
#define  VTSS_F_GLOBAL_RING_OSC_RING_OSC_CTRL_RING_OSC_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Enable Ring Oscilator
 *
 * \details 
 * 0: Select Ring Oscilator 0
 * 1: Select Ring Oscilator 1
 * 2: Select Ring Oscilator 2
 * 3: Select Ring Oscilator 3
 *
 * Field: VTSS_GLOBAL_RING_OSC_RING_OSC_CTRL . RING_OSC_SEL
 */
#define  VTSS_F_GLOBAL_RING_OSC_RING_OSC_CTRL_RING_OSC_SEL(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_GLOBAL_RING_OSC_RING_OSC_CTRL_RING_OSC_SEL     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_GLOBAL_RING_OSC_RING_OSC_CTRL_RING_OSC_SEL(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a GLOBAL:IP1588_CSR_CLK_DEBUG
 *
 * Clock enable override for 1588 CSR clock
 */


/** 
 * \brief IP1588 CSR Clock Enable Override
 *
 * \details
 * Manually force CSR clock on 100% of the time
 *
 * Register: \a GLOBAL:IP1588_CSR_CLK_DEBUG:IP1588_CSR_CLK_DBG
 */
#define VTSS_GLOBAL_IP1588_CSR_CLK_DEBUG_IP1588_CSR_CLK_DBG  VTSS_IOREG(0x1e, 0, 0x0270)

/** 
 * \brief
 * Force IP1588 CSR clock on at all times.
 *
 * \details 
 * 0: Clock automatically turned on when registers are accessed
 * 1: Clock toggles continuously
 *
 * Field: VTSS_GLOBAL_IP1588_CSR_CLK_DEBUG_IP1588_CSR_CLK_DBG . FRC_1588_CSR_CLK_ON
 */
#define  VTSS_F_GLOBAL_IP1588_CSR_CLK_DEBUG_IP1588_CSR_CLK_DBG_FRC_1588_CSR_CLK_ON  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:FRC_DIS
 *
 * Force Feature Disable
 */


/** 
 * \brief Force Feature Disable
 *
 * \details
 * Force Feature Disable
 *
 * Register: \a GLOBAL:FRC_DIS:FRC_DIS
 */
#define VTSS_GLOBAL_FRC_DIS_FRC_DIS          VTSS_IOREG(0x1e, 0, 0x0280)

/** 
 * \brief
 * Disable 1588's nphase sampler to reduce accuracy in the low-end product
 * variant.
 *
 * \details 
 * 0: nphase sampler circuit enabled
 * 1: nphase sampler circuit disabled
 *
 * Field: VTSS_GLOBAL_FRC_DIS_FRC_DIS . FRC_NPHASE_DIS
 */
#define  VTSS_F_GLOBAL_FRC_DIS_FRC_DIS_FRC_NPHASE_DIS  VTSS_BIT(1)

/** 
 * \brief
 * Disable MACsec's 256-bit encryption key capability in the low-end
 * product variant.
 *
 * \details 
 * 0: 256-bit key capability enabled
 * 1: 256-bit key capability disabled
 *
 * Field: VTSS_GLOBAL_FRC_DIS_FRC_DIS . FRC_256KEY_DIS
 */
#define  VTSS_F_GLOBAL_FRC_DIS_FRC_DIS_FRC_256KEY_DIS  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:EFUSE_STATES
 *
 * State of E-fuses
 */


/** 
 * \brief Efuse Read Status
 *
 * \details
 * Efuse Read Status
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_READ_STAT
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_READ_STAT  VTSS_IOREG(0x1e, 0, 0x028f)


/** 
 * \brief Efuses [15:0]
 *
 * \details
 * Efuses [15:0]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q15_Q0
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q15_Q0  VTSS_IOREG(0x1e, 0, 0x0290)


/** 
 * \brief Efuses [31:16]
 *
 * \details
 * Efuses [31:16]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q31_Q16
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q31_Q16  VTSS_IOREG(0x1e, 0, 0x0291)


/** 
 * \brief Efuses [47:32]
 *
 * \details
 * Efuses [47:32]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q47_Q32
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q47_Q32  VTSS_IOREG(0x1e, 0, 0x0292)


/** 
 * \brief Efuses [63:48]
 *
 * \details
 * Efuses [63:48]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q63_Q48
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q63_Q48  VTSS_IOREG(0x1e, 0, 0x0293)


/** 
 * \brief Efuses [79:64]
 *
 * \details
 * Efuses [79:64]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q79_Q64
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q79_Q64  VTSS_IOREG(0x1e, 0, 0x0294)


/** 
 * \brief Efuses [95:80]
 *
 * \details
 * Efuses [95:80]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q95_Q80
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q95_Q80  VTSS_IOREG(0x1e, 0, 0x0295)


/** 
 * \brief Efuses [111:96]
 *
 * \details
 * Efuses [111:96]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q111_Q96
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q111_Q96  VTSS_IOREG(0x1e, 0, 0x0296)


/** 
 * \brief Efuses [127:112]
 *
 * \details
 * Efuses [127:112]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q127_Q112
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q127_Q112  VTSS_IOREG(0x1e, 0, 0x0297)


/** 
 * \brief Efuses [143:128]
 *
 * \details
 * Efuses [143:128]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q143_Q128
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q143_Q128  VTSS_IOREG(0x1e, 0, 0x0298)


/** 
 * \brief Efuses [159:144]
 *
 * \details
 * Efuses [159:144]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q159_Q144
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q159_Q144  VTSS_IOREG(0x1e, 0, 0x0299)


/** 
 * \brief Efuses [175:160]
 *
 * \details
 * Efuses [175:160]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q175_Q160
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q175_Q160  VTSS_IOREG(0x1e, 0, 0x029a)


/** 
 * \brief Efuses [191:176]
 *
 * \details
 * Efuses [191:176]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q191_Q176
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q191_Q176  VTSS_IOREG(0x1e, 0, 0x029b)


/** 
 * \brief Efuses [207:192]
 *
 * \details
 * Efuses [207:192]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q207_Q192
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q207_Q192  VTSS_IOREG(0x1e, 0, 0x029c)


/** 
 * \brief Efuses [223:208]
 *
 * \details
 * Efuses [223:208]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q223_Q208
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q223_Q208  VTSS_IOREG(0x1e, 0, 0x029d)


/** 
 * \brief Efuses [239:224]
 *
 * \details
 * Efuses [239:224]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q239_Q224
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q239_Q224  VTSS_IOREG(0x1e, 0, 0x029e)


/** 
 * \brief Efuses [255:240]
 *
 * \details
 * Efuses [255:240]
 *
 * Register: \a GLOBAL:EFUSE_STATES:EFUSE_Q255_Q240
 */
#define VTSS_GLOBAL_EFUSE_STATES_EFUSE_Q255_Q240  VTSS_IOREG(0x1e, 0, 0x029f)

/**
 * Register Group: \a GLOBAL:FEATURE_STAT
 *
 * Registers for Device Feature Status
 */


/** 
 * \brief Device Feature Status
 *
 * \details
 * Device Feature Status
 *
 * Register: \a GLOBAL:FEATURE_STAT:FEATURE_STAT
 */
#define VTSS_GLOBAL_FEATURE_STAT_FEATURE_STAT  VTSS_IOREG(0x1e, 0, 0x02a0)

/** 
 * \brief
 * Indicates the status of 1588 availability on the device
 *
 * \details 
 * 0: 1588 may be used
 * 1: 1588 is permanently disabled
 *
 * Field: VTSS_GLOBAL_FEATURE_STAT_FEATURE_STAT . IP1588_STAT
 */
#define  VTSS_F_GLOBAL_FEATURE_STAT_FEATURE_STAT_IP1588_STAT  VTSS_BIT(3)

/** 
 * \brief
 * Indicates the status of MACsec availability on the device
 *
 * \details 
 * 0: MACsec block may be used
 * 1: MACsec block is permanently disabled
 *
 * Field: VTSS_GLOBAL_FEATURE_STAT_FEATURE_STAT . MACSEC_STAT
 */
#define  VTSS_F_GLOBAL_FEATURE_STAT_FEATURE_STAT_MACSEC_STAT  VTSS_BIT(2)

/** 
 * \brief
 * Indicates the 1588 timestamp accuracy 
 *
 * \details 
 * 0: 4ns
 * 1: 8ns
 *
 * Field: VTSS_GLOBAL_FEATURE_STAT_FEATURE_STAT . TIMESTAMP_ACC_STAT
 */
#define  VTSS_F_GLOBAL_FEATURE_STAT_FEATURE_STAT_TIMESTAMP_ACC_STAT  VTSS_BIT(1)

/** 
 * \brief
 * Indicates the MACsec encryption key capability
 *
 * \details 
 * 0: 128/256-bit 
 * 1: 128-bit
 *
 * Field: VTSS_GLOBAL_FEATURE_STAT_FEATURE_STAT . MACSEC_KEY_STAT
 */
#define  VTSS_F_GLOBAL_FEATURE_STAT_FEATURE_STAT_MACSEC_KEY_STAT  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:SPI_CTRL
 *
 * SPI mode control register
 */


/** 
 * \brief SPI mode control register
 *
 * \details
 * SPI mode control register
 *
 * Register: \a GLOBAL:SPI_CTRL:SPI_CTRL
 */
#define VTSS_GLOBAL_SPI_CTRL_SPI_CTRL        VTSS_IOREG(0x1e, 0, 0x02b0)

/** 
 * \brief
 * Set the SPI interface mode
 *
 * \details 
 * 0: Normal mode
 * 1: Fast mode
 *
 * Field: VTSS_GLOBAL_SPI_CTRL_SPI_CTRL . FAST_MODE
 */
#define  VTSS_F_GLOBAL_SPI_CTRL_SPI_CTRL_FAST_MODE  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:ANATEST_CFG
 *
 * Control Regiser for ANATEST pin
 */


/** 
 * \brief Control Regiser for ANATEST pin
 *
 * \details
 * Control Regiser for ANATEST pin
 *
 * Register: \a GLOBAL:ANATEST_CFG:ANATEST_CFG
 */
#define VTSS_GLOBAL_ANATEST_CFG_ANATEST_CFG  VTSS_IOREG(0x1e, 0, 0x02c0)

/** 
 * \brief
 * Enable ANATEST pin
 *
 * \details 
 * 0: ANATEST pin disable
 * 1: ANATEST pin enable
 *
 * Field: VTSS_GLOBAL_ANATEST_CFG_ANATEST_CFG . ANATEST_ENA
 */
#define  VTSS_F_GLOBAL_ANATEST_CFG_ANATEST_CFG_ANATEST_ENA  VTSS_BIT(0)

/**
 * Register Group: \a GLOBAL:CFG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a GLOBAL:CFG:CONFIG
 */
#define VTSS_GLOBAL_CFG_CONFIG               VTSS_IOREG(0x1e, 0, 0x02d0)

/**
 * Register Group: \a GLOBAL:RNG
 *
 * Not documented
 */


/** 
 * \details
 * Register: \a GLOBAL:RNG:RNG_REG
 */
#define VTSS_GLOBAL_RNG_RNG_REG              VTSS_IOREG(0x1e, 0, 0x02d1)

/** 
 * \brief
 * Random number
 *
 * \details 
 * Field: VTSS_GLOBAL_RNG_RNG_REG . RNDNUM
 */
#define  VTSS_F_GLOBAL_RNG_RNG_REG_RNDNUM(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_GLOBAL_RNG_RNG_REG_RNDNUM     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_GLOBAL_RNG_RNG_REG_RNDNUM(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a GLOBAL:RCOMP_CFG
 *
 * RCOMP Configuration Registers
 */


/** 
 * \brief RCOMP Configuration 0
 *
 * \details
 * Configuration register 0 for RCOMP
 *
 * Register: \a GLOBAL:RCOMP_CFG:RCOMP_CFG0
 */
#define VTSS_GLOBAL_RCOMP_CFG_RCOMP_CFG0     VTSS_IOREG(0x1e, 0, 0x7000)

/** 
 * \brief
 * Enable power-down after calibration was done
 *
 * \details 
 * 0: disable power-down
 * 1: enable power-down
 *
 * Field: VTSS_GLOBAL_RCOMP_CFG_RCOMP_CFG0 . PWD_ENA
 */
#define  VTSS_F_GLOBAL_RCOMP_CFG_RCOMP_CFG0_PWD_ENA  VTSS_BIT(13)

/** 
 * \brief
 * Start calibration
 *
 * \details 
 * 0: idle/inactive
 * 1: start (activate)
 *
 * Field: VTSS_GLOBAL_RCOMP_CFG_RCOMP_CFG0 . RUN_CAL
 */
#define  VTSS_F_GLOBAL_RCOMP_CFG_RCOMP_CFG0_RUN_CAL  VTSS_BIT(12)

/** 
 * \brief
 * Speed selection. Setting time for analog circuit after changing resistor
 * settings.
 *
 * \details 
 * 0: max period
 * 1: max period/2
 * 2: max period/4
 * 3: max period/8
 *
 * Field: VTSS_GLOBAL_RCOMP_CFG_RCOMP_CFG0 . SPEED_SEL
 */
#define  VTSS_F_GLOBAL_RCOMP_CFG_RCOMP_CFG0_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,10,2)
#define  VTSS_M_GLOBAL_RCOMP_CFG_RCOMP_CFG0_SPEED_SEL     VTSS_ENCODE_BITMASK(10,2)
#define  VTSS_X_GLOBAL_RCOMP_CFG_RCOMP_CFG0_SPEED_SEL(x)  VTSS_EXTRACT_BITFIELD(x,10,2)

/** 
 * \brief
 * RCOMP operation mode
 *
 * \details 
 * 0: inactive
 * 1: perform calibration permanently
 * 2: perform calibration once
 * 3: perform calibration once and generate alarm if necessary
 *
 * Field: VTSS_GLOBAL_RCOMP_CFG_RCOMP_CFG0 . MODE_SEL
 */
#define  VTSS_F_GLOBAL_RCOMP_CFG_RCOMP_CFG0_MODE_SEL(x)  VTSS_ENCODE_BITFIELD(x,8,2)
#define  VTSS_M_GLOBAL_RCOMP_CFG_RCOMP_CFG0_MODE_SEL     VTSS_ENCODE_BITMASK(8,2)
#define  VTSS_X_GLOBAL_RCOMP_CFG_RCOMP_CFG0_MODE_SEL(x)  VTSS_EXTRACT_BITFIELD(x,8,2)

/** 
 * \brief
 * Overwrite measured resistor value with value programmed in rcomp_val
 *
 * \details 
 * 0: normal mode
 * 1: overwrite mode
 *
 * Field: VTSS_GLOBAL_RCOMP_CFG_RCOMP_CFG0 . FORCE_ENA
 */
#define  VTSS_F_GLOBAL_RCOMP_CFG_RCOMP_CFG0_FORCE_ENA  VTSS_BIT(4)

/** 
 * \brief
 * Resistor comparator value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: VTSS_GLOBAL_RCOMP_CFG_RCOMP_CFG0 . RCOMP_VAL
 */
#define  VTSS_F_GLOBAL_RCOMP_CFG_RCOMP_CFG0_RCOMP_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_GLOBAL_RCOMP_CFG_RCOMP_CFG0_RCOMP_VAL     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_GLOBAL_RCOMP_CFG_RCOMP_CFG0_RCOMP_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * Register Group: \a GLOBAL:RCOMP_STATUS
 *
 * RCOMP Status Registers
 */


/** 
 * \brief RCOMP Status
 *
 * \details
 * Status register bits for the RCOMP
 *
 * Register: \a GLOBAL:RCOMP_STATUS:RCOMP_STATUS
 */
#define VTSS_GLOBAL_RCOMP_STATUS_RCOMP_STATUS  VTSS_IOREG(0x1e, 0, 0x7010)

/** 
 * \brief
 * Resistor comparison activity
 *
 * \details 
 * 0: resistor measurement finished or inactive
 * 1: resistor measurement in progress
 *
 * Field: VTSS_GLOBAL_RCOMP_STATUS_RCOMP_STATUS . BUSY
 */
#define  VTSS_F_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_BUSY  VTSS_BIT(12)

/** 
 * \brief
 * Alarm signal if rcomp isn't best choice anymore
 *
 * \details 
 * 0: inactive
 * 1: active
 *
 * Field: VTSS_GLOBAL_RCOMP_STATUS_RCOMP_STATUS . DELTA_ALERT
 */
#define  VTSS_F_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_DELTA_ALERT  VTSS_BIT(7)

/** 
 * \brief
 * Measured resistor value
 *
 * \details 
 * 0: maximum resistance value
 * 15: minimum resistance value
 *
 * Field: VTSS_GLOBAL_RCOMP_STATUS_RCOMP_STATUS . RCOMP
 */
#define  VTSS_F_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_RCOMP     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_GLOBAL_RCOMP_STATUS_RCOMP_STATUS_RCOMP(x)  VTSS_EXTRACT_BITFIELD(x,0,4)


#endif /* _VTSS_MALIBU_REGS_GLOBAL_H_ */
