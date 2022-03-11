/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

//-----------------------------------------------------------------------------
// LSD Generator
//-----------------------------------------------------------------------------
// Perl Package        : LSD::generator::targetC (v1.1)
// LSD Source          : /home/p31g/p31g_ip/v_reddydev.priv.p31g_ip.vp_model/ipg_lsd/lsd_sys/source_mdio/xml/reg_files/phy_def.xml
// Register File Name  : PHY
// Register File Title : GPY-specific Management Registers
// Register Width      : 16
// Note                : Doxygen compliant comments
//-----------------------------------------------------------------------------

#ifndef _PHY_H
#define _PHY_H

//! \defgroup PHY Register File PHY - GPY-specific Management Registers
//! @{

//! Base Address of PHY
#define PHY_MODULE_BASE 0x00000020u

//! \defgroup PHY_PERF Register PHY_PERF - Physical Layer Performance Status (Register 0.16)
//! @{

//! Register Offset (relative)
#define PHY_PERF 0x20
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_PERF 0x00000020u

//! Register Reset Value
#define PHY_PERF_RST 0x800Fu

//! Field LEN - Estimated Loop Length (Valid During Link-Up)
#define PHY_PERF_LEN_POS 0
//! Field LEN - Estimated Loop Length (Valid During Link-Up)
#define PHY_PERF_LEN_MASK 0xFu

//! Field FREQ - Frequency Offset of Link-Partner [ppm]
#define PHY_PERF_FREQ_POS 8
//! Field FREQ - Frequency Offset of Link-Partner [ppm]
#define PHY_PERF_FREQ_MASK 0xFF00u

//! @}

//! \defgroup PHY_STAT1 Register PHY_STAT1 - Physical Layer Status 1 (Register 0.17)
//! @{

//! Register Offset (relative)
#define PHY_STAT1 0x22
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_STAT1 0x00000022u

//! Register Reset Value
#define PHY_STAT1_RST 0x0000u

//! Field RES1 - Reserved
#define PHY_STAT1_RES1_POS 0
//! Field RES1 - Reserved
#define PHY_STAT1_RES1_MASK 0x3u

//! Field FW_MEM - Firmware Memory Location
#define PHY_STAT1_FW_MEM_POS 2
//! Field FW_MEM - Firmware Memory Location
#define PHY_STAT1_FW_MEM_MASK 0xCu
//! Constant ROM - Firmware is executed from ROM
#define CONST_PHY_STAT1_FW_MEM_ROM 0x0
//! Constant OTP - Firmware is executed from OTP
#define CONST_PHY_STAT1_FW_MEM_OTP 0x1
//! Constant FLASH - Firmware is executed from FLASH
#define CONST_PHY_STAT1_FW_MEM_FLASH 0x2
//! Constant RAM - Firmware is executed from SRAM
#define CONST_PHY_STAT1_FW_MEM_RAM 0x3

//! Field LSADS - Link Speed Auto-Downspeed Status
#define PHY_STAT1_LSADS_POS 8
//! Field LSADS - Link Speed Auto-Downspeed Status
#define PHY_STAT1_LSADS_MASK 0x100u
//! Constant NORMAL - Did not perform any link speed auto-downspeed
#define CONST_PHY_STAT1_LSADS_NORMAL 0x0
//! Constant DETECTED - Detected an auto-downspeed
#define CONST_PHY_STAT1_LSADS_DETECTED 0x1

//! Field RES2 - Reserved
#define PHY_STAT1_RES2_POS 9
//! Field RES2 - Reserved
#define PHY_STAT1_RES2_MASK 0xFE00u

//! @}

//! \defgroup PHY_RES Register PHY_RES - Reserved
//! @{

//! Register Offset (relative)
#define PHY_RES 0x4
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_RES 0x00000024u

//! Register Reset Value
#define PHY_RES_RST 0x0000u

//! Field RES - Reserved
#define PHY_RES_RES_POS 0
//! Field RES - Reserved
#define PHY_RES_RES_MASK 0xFFFFu

//! @}

//! \defgroup PHY_CTL1 Register PHY_CTL1 - Physical Layer Control 1 (Register 0.19)
//! @{

//! Register Offset (relative)
#define PHY_CTL1 0x26
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_CTL1 0x00000026u

//! Register Reset Value
#define PHY_CTL1_RST 0x0001u

//! Field AMDIX - PHY Performs Auto-MDI/MDI-X or Uses Manual MDI/MDI-X
#define PHY_CTL1_AMDIX_POS 0
//! Field AMDIX - PHY Performs Auto-MDI/MDI-X or Uses Manual MDI/MDI-X
#define PHY_CTL1_AMDIX_MASK 0x1u
//! Constant MANUAL - PHY uses manual MDI/MDI-X
#define CONST_PHY_CTL1_AMDIX_MANUAL 0x0
//! Constant AUTO - PHY performs Auto-MDI/MDI-X
#define CONST_PHY_CTL1_AMDIX_AUTO 0x1

//! Field RES - Reserved
#define PHY_CTL1_RES_POS 1
//! Field RES - Reserved
#define PHY_CTL1_RES_MASK 0x2u

//! Field MDIAB - Mapping of MDI Ports A and B
#define PHY_CTL1_MDIAB_POS 2
//! Field MDIAB - Mapping of MDI Ports A and B
#define PHY_CTL1_MDIAB_MASK 0x4u
//! Constant MDI - Normal MDI mode
#define CONST_PHY_CTL1_MDIAB_MDI 0x0
//! Constant MDIX - Crossover MDI-X mode
#define CONST_PHY_CTL1_MDIAB_MDIX 0x1

//! Field MDICD - Mapping of MDI Ports C and D
#define PHY_CTL1_MDICD_POS 3
//! Field MDICD - Mapping of MDI Ports C and D
#define PHY_CTL1_MDICD_MASK 0x8u
//! Constant MDI - Normal MDI mode
#define CONST_PHY_CTL1_MDICD_MDI 0x0
//! Constant MDIX - Crossover MDI-X mode
#define CONST_PHY_CTL1_MDICD_MDIX 0x1

//! Field POLA - Polarity Inversion Control on Port A
#define PHY_CTL1_POLA_POS 4
//! Field POLA - Polarity Inversion Control on Port A
#define PHY_CTL1_POLA_MASK 0x10u
//! Constant NORMAL - Polarity normal
#define CONST_PHY_CTL1_POLA_NORMAL 0x0
//! Constant INVERTED - Polarity inversion
#define CONST_PHY_CTL1_POLA_INVERTED 0x1

//! Field POLB - Polarity Inversion Control on Port B
#define PHY_CTL1_POLB_POS 5
//! Field POLB - Polarity Inversion Control on Port B
#define PHY_CTL1_POLB_MASK 0x20u
//! Constant NORMAL - Polarity normal
#define CONST_PHY_CTL1_POLB_NORMAL 0x0
//! Constant INVERTED - Polarity inversion
#define CONST_PHY_CTL1_POLB_INVERTED 0x1

//! Field POLC - Polarity Inversion Control on Port C
#define PHY_CTL1_POLC_POS 6
//! Field POLC - Polarity Inversion Control on Port C
#define PHY_CTL1_POLC_MASK 0x40u
//! Constant NORMAL - Polarity normal
#define CONST_PHY_CTL1_POLC_NORMAL 0x0
//! Constant INVERTED - Polarity inversion
#define CONST_PHY_CTL1_POLC_INVERTED 0x1

//! Field POLD - Polarity Inversion Control on Port D
#define PHY_CTL1_POLD_POS 7
//! Field POLD - Polarity Inversion Control on Port D
#define PHY_CTL1_POLD_MASK 0x80u
//! Constant NORMAL - Polarity normal
#define CONST_PHY_CTL1_POLD_NORMAL 0x0
//! Constant INVERTED - Polarity inversion
#define CONST_PHY_CTL1_POLD_INVERTED 0x1

//! Field TXADJ - Transmit Level Adjustment
#define PHY_CTL1_TXADJ_POS 8
//! Field TXADJ - Transmit Level Adjustment
#define PHY_CTL1_TXADJ_MASK 0xF00u

//! Field TXOFF - Transmitter Off
#define PHY_CTL1_TXOFF_POS 12
//! Field TXOFF - Transmitter Off
#define PHY_CTL1_TXOFF_MASK 0x1000u
//! Constant ON - Transmitter is on
#define CONST_PHY_CTL1_TXOFF_ON 0x0
//! Constant OFF - Transmitter is off
#define CONST_PHY_CTL1_TXOFF_OFF 0x1

//! Field TLOOP - Test Loop
#define PHY_CTL1_TLOOP_POS 13
//! Field TLOOP - Test Loop
#define PHY_CTL1_TLOOP_MASK 0xE000u
//! Constant OFF - Test loops are switched off - normal operation.
#define CONST_PHY_CTL1_TLOOP_OFF 0x0
//! Constant NETL - Near-end test loop
#define CONST_PHY_CTL1_TLOOP_NETL 0x1
//! Constant FETL - Far-end test loop
#define CONST_PHY_CTL1_TLOOP_FETL 0x2
//! Constant ECHO - Echo test loop
#define CONST_PHY_CTL1_TLOOP_ECHO 0x3
//! Constant RJTL - RL45 connector test loop
#define CONST_PHY_CTL1_TLOOP_RJTL 0x4
//! Constant FETLS - Standalone Far-end test loop. No dependency on GMII_TX_CLK and GMII_RX_CLK
#define CONST_PHY_CTL1_TLOOP_FETLS 0x5

//! @}

//! \defgroup PHY_CTL2 Register PHY_CTL2 - Physical Layer Control 2 (Register 0.20)
//! @{

//! Register Offset (relative)
#define PHY_CTL2 0x28
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_CTL2 0x00000028u

//! Register Reset Value
#define PHY_CTL2_RST 0x0006u

//! Field LPI - Assert LPI via MDIO
#define PHY_CTL2_LPI_POS 0
//! Field LPI - Assert LPI via MDIO
#define PHY_CTL2_LPI_MASK 0x1u
//! Constant DEASSERT - LPI is de-asserted TPI
#define CONST_PHY_CTL2_LPI_DEASSERT 0x0
//! Constant ASSERT - LPI is asserted on TPI
#define CONST_PHY_CTL2_LPI_ASSERT 0x1

//! Field ANPD - Auto-Negotiation Power Down
#define PHY_CTL2_ANPD_POS 1
//! Field ANPD - Auto-Negotiation Power Down
#define PHY_CTL2_ANPD_MASK 0x2u
//! Constant OFF - ANPD is disabled
#define CONST_PHY_CTL2_ANPD_OFF 0x0
//! Constant ON - ANPD is enabled
#define CONST_PHY_CTL2_ANPD_ON 0x1

//! Field PSCL - Power Consumption Scaling Depending on Link Quality
#define PHY_CTL2_PSCL_POS 2
//! Field PSCL - Power Consumption Scaling Depending on Link Quality
#define PHY_CTL2_PSCL_MASK 0x4u
//! Constant OFF - PSCL is disabled
#define CONST_PHY_CTL2_PSCL_OFF 0x0
//! Constant ON - PSCL is enabled
#define CONST_PHY_CTL2_PSCL_ON 0x1

//! Field ULP - Ultra Low Power Mode
#define PHY_CTL2_ULP_POS 3
//! Field ULP - Ultra Low Power Mode
#define PHY_CTL2_ULP_MASK 0x8u
//! Constant OFF - ULP is Disabled
#define CONST_PHY_CTL2_ULP_OFF 0x0
//! Constant ON - ULP is Enabled
#define CONST_PHY_CTL2_ULP_ON 0x1

//! Field ULP_STA_BLOCK - Ultra Low Power Mode entry block by acknowledgment from STA
#define PHY_CTL2_ULP_STA_BLOCK_POS 4
//! Field ULP_STA_BLOCK - Ultra Low Power Mode entry block by acknowledgment from STA
#define PHY_CTL2_ULP_STA_BLOCK_MASK 0x10u
//! Constant OFF - ULP Entry without the role of STA
#define CONST_PHY_CTL2_ULP_STA_BLOCK_OFF 0x0
//! Constant ON - ULP Entry Blocked by STA
#define CONST_PHY_CTL2_ULP_STA_BLOCK_ON 0x1

//! Field RES1 - Reserved
#define PHY_CTL2_RES1_POS 5
//! Field RES1 - Reserved
#define PHY_CTL2_RES1_MASK 0xE0u

//! Field STICKY - Sticky-Bit Handling
#define PHY_CTL2_STICKY_POS 8
//! Field STICKY - Sticky-Bit Handling
#define PHY_CTL2_STICKY_MASK 0x100u
//! Constant OFF - Sticky-bit handling is disabled
#define CONST_PHY_CTL2_STICKY_OFF 0x0
//! Constant ON - Sticky-bit handling is enabled
#define CONST_PHY_CTL2_STICKY_ON 0x1

//! Field SDETP - Signal Detection Polarity for the 1000BASE-X PHY
#define PHY_CTL2_SDETP_POS 9
//! Field SDETP - Signal Detection Polarity for the 1000BASE-X PHY
#define PHY_CTL2_SDETP_MASK 0x200u
//! Constant LOWACTIVE - SIGDET input is low active
#define CONST_PHY_CTL2_SDETP_LOWACTIVE 0x0
//! Constant HIGHACTIVE - SIGDET input is high active
#define CONST_PHY_CTL2_SDETP_HIGHACTIVE 0x1

//! @}

//! \defgroup PHY_ERRCNT Register PHY_ERRCNT - Error Counter (Register 0.21)
//! @{

//! Register Offset (relative)
#define PHY_ERRCNT 0x2A
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_ERRCNT 0x0000002Au

//! Register Reset Value
#define PHY_ERRCNT_RST 0x0000u

//! Field COUNT - Counter Value
#define PHY_ERRCNT_COUNT_POS 0
//! Field COUNT - Counter Value
#define PHY_ERRCNT_COUNT_MASK 0xFFu

//! Field SEL - Select Error Event
#define PHY_ERRCNT_SEL_POS 8
//! Field SEL - Select Error Event
#define PHY_ERRCNT_SEL_MASK 0xF00u
//! Constant RXERR - Receive errors are counted
#define CONST_PHY_ERRCNT_SEL_RXERR 0x0
//! Constant RXACT - Receive frames are counted
#define CONST_PHY_ERRCNT_SEL_RXACT 0x1
//! Constant ESDERR - ESD errors are counted
#define CONST_PHY_ERRCNT_SEL_ESDERR 0x2
//! Constant SSDERR - SSD errors are counted
#define CONST_PHY_ERRCNT_SEL_SSDERR 0x3
//! Constant TXERR - Transmit errors are counted
#define CONST_PHY_ERRCNT_SEL_TXERR 0x4
//! Constant TXACT - Transmit frames events get counted
#define CONST_PHY_ERRCNT_SEL_TXACT 0x5
//! Constant COL - Collision events get counted
#define CONST_PHY_ERRCNT_SEL_COL 0x6
//! Constant NLD - Number of Link Down events get counted
#define CONST_PHY_ERRCNT_SEL_NLD 0x8
//! Constant NDS - Number of auto-downspeed events get counted
#define CONST_PHY_ERRCNT_SEL_NDS 0x9
//! Constant CRC - CRC counter
#define CONST_PHY_ERRCNT_SEL_CRC 0xA
//! Constant TTL - Time to Link
#define CONST_PHY_ERRCNT_SEL_TTL 0xB

//! Field RES - Reserved
#define PHY_ERRCNT_RES_POS 12
//! Field RES - Reserved
#define PHY_ERRCNT_RES_MASK 0xF000u

//! @}

//! \defgroup PHY_RES1 Register PHY_RES1 - Reserved
//! @{

//! Register Offset (relative)
#define PHY_RES1 0xC
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_RES1 0x0000002Cu

//! Register Reset Value
#define PHY_RES1_RST 0x0000u

//! Field RES - Reserved
#define PHY_RES1_RES_POS 0
//! Field RES - Reserved
#define PHY_RES1_RES_MASK 0xFFFFu

//! @}

//! \defgroup PHY_RES2 Register PHY_RES2 - Reserved
//! @{

//! Register Offset (relative)
#define PHY_RES2 0xE
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_RES2 0x0000002Eu

//! Register Reset Value
#define PHY_RES2_RST 0x0000u

//! Field RES - Reserved
#define PHY_RES2_RES_POS 0
//! Field RES - Reserved
#define PHY_RES2_RES_MASK 0xFFFFu

//! @}

//! \defgroup PHY_MIISTAT Register PHY_MIISTAT - Media-Independent Interface Status (Register 0.24)
//! @{

//! Register Offset (relative)
#define PHY_MIISTAT 0x30
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_MIISTAT 0x00000030u

//! Register Reset Value
#define PHY_MIISTAT_RST 0x0000u

//! Field SPEED - GPY Ethernet PHY Speed
#define PHY_MIISTAT_SPEED_POS 0
//! Field SPEED - GPY Ethernet PHY Speed
#define PHY_MIISTAT_SPEED_MASK 0x7u
//! Constant TEN - 10 Mbit/s
#define CONST_PHY_MIISTAT_SPEED_TEN 0x0
//! Constant FAST - 100 Mbit/s
#define CONST_PHY_MIISTAT_SPEED_FAST 0x1
//! Constant GIGA - 1000 Mbit/s
#define CONST_PHY_MIISTAT_SPEED_GIGA 0x2
//! Constant ANEG - Autonegotiation mode
#define CONST_PHY_MIISTAT_SPEED_ANEG 0x3
//! Constant BZ2G5 - 2.5GBit/s
#define CONST_PHY_MIISTAT_SPEED_BZ2G5 0x4

//! Field DPX - GPY Ethernet PHY Duplex Mode
#define PHY_MIISTAT_DPX_POS 3
//! Field DPX - GPY Ethernet PHY Duplex Mode
#define PHY_MIISTAT_DPX_MASK 0x8u
//! Constant HDX - Half duplex
#define CONST_PHY_MIISTAT_DPX_HDX 0x0
//! Constant FDX - Full duplex
#define CONST_PHY_MIISTAT_DPX_FDX 0x1

//! Field PS - Pause Status for Flow Control
#define PHY_MIISTAT_PS_POS 4
//! Field PS - Pause Status for Flow Control
#define PHY_MIISTAT_PS_MASK 0x30u
//! Constant NONE - No PAUSE
#define CONST_PHY_MIISTAT_PS_NONE 0x0
//! Constant TX - Transmit PAUSE
#define CONST_PHY_MIISTAT_PS_TX 0x1
//! Constant RX - Receive PAUSE
#define CONST_PHY_MIISTAT_PS_RX 0x2
//! Constant TXRX - Both transmit and receive PAUSE
#define CONST_PHY_MIISTAT_PS_TXRX 0x3

//! Field RES1 - Reserved
#define PHY_MIISTAT_RES1_POS 6
//! Field RES1 - Reserved
#define PHY_MIISTAT_RES1_MASK 0xC0u

//! Field EEE - Energy-Efficient Ethernet Mode
#define PHY_MIISTAT_EEE_POS 8
//! Field EEE - Energy-Efficient Ethernet Mode
#define PHY_MIISTAT_EEE_MASK 0x100u
//! Constant OFF - EEE is disabled after auto-negotiation resolution
#define CONST_PHY_MIISTAT_EEE_OFF 0x0
//! Constant ON - EEE is enabled after auto-negotiation resolution
#define CONST_PHY_MIISTAT_EEE_ON 0x1

//! Field MSRES - Master/Slave Configuration
#define PHY_MIISTAT_MSRES_POS 9
//! Field MSRES - Master/Slave Configuration
#define PHY_MIISTAT_MSRES_MASK 0x200u
//! Constant SLAVE - Local PHY configuration is SLAVE after ANEG
#define CONST_PHY_MIISTAT_MSRES_SLAVE 0x0
//! Constant MASTER - Local PHY configuration is MASTER after ANEG
#define CONST_PHY_MIISTAT_MSRES_MASTER 0x1

//! Field LS - Link Status at which GPY Ethernet PHY Operates
#define PHY_MIISTAT_LS_POS 10
//! Field LS - Link Status at which GPY Ethernet PHY Operates
#define PHY_MIISTAT_LS_MASK 0x400u
//! Constant INACTIVE - The link is down.
#define CONST_PHY_MIISTAT_LS_INACTIVE 0x0
//! Constant ACTIVE - The link is up.
#define CONST_PHY_MIISTAT_LS_ACTIVE 0x1

//! Field RES2 - Reserved
#define PHY_MIISTAT_RES2_POS 11
//! Field RES2 - Reserved
#define PHY_MIISTAT_RES2_MASK 0xF800u

//! @}

//! \defgroup PHY_IMASK Register PHY_IMASK - Interrupt Mask Register (Register 0.25)
//! @{

//! Register Offset (relative)
#define PHY_IMASK 0x32
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_IMASK 0x00000032u

//! Register Reset Value
#define PHY_IMASK_RST 0x0000u

//! Field LSTC - Link State Change Mask
#define PHY_IMASK_LSTC_POS 0
//! Field LSTC - Link State Change Mask
#define PHY_IMASK_LSTC_MASK 0x1u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_LSTC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_LSTC_ACTIVE 0x1

//! Field LSPC - Link Speed Change Mask
#define PHY_IMASK_LSPC_POS 1
//! Field LSPC - Link Speed Change Mask
#define PHY_IMASK_LSPC_MASK 0x2u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_LSPC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_LSPC_ACTIVE 0x1

//! Field DXMC - Duplex Mode Change Mask
#define PHY_IMASK_DXMC_POS 2
//! Field DXMC - Duplex Mode Change Mask
#define PHY_IMASK_DXMC_MASK 0x4u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_DXMC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_DXMC_ACTIVE 0x1

//! Field MDIXC - MDIX Change Detect Mask
#define PHY_IMASK_MDIXC_POS 3
//! Field MDIXC - MDIX Change Detect Mask
#define PHY_IMASK_MDIXC_MASK 0x8u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_MDIXC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_MDIXC_ACTIVE 0x1

//! Field MDIPC - MDI Polarity Change Detect Mask
#define PHY_IMASK_MDIPC_POS 4
//! Field MDIPC - MDI Polarity Change Detect Mask
#define PHY_IMASK_MDIPC_MASK 0x10u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_MDIPC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_MDIPC_ACTIVE 0x1

//! Field ADSC - Link Speed Auto-Downspeed Detect Mask
#define PHY_IMASK_ADSC_POS 5
//! Field ADSC - Link Speed Auto-Downspeed Detect Mask
#define PHY_IMASK_ADSC_MASK 0x20u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_ADSC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_ADSC_ACTIVE 0x1

//! Field TEMP - TEMP
#define PHY_IMASK_TEMP_POS 6
//! Field TEMP - TEMP
#define PHY_IMASK_TEMP_MASK 0x40u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_TEMP_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_TEMP_ACTIVE 0x1

//! Field ULP - ULP Entry Indication Mask
#define PHY_IMASK_ULP_POS 7
//! Field ULP - ULP Entry Indication Mask
#define PHY_IMASK_ULP_MASK 0x80u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_ULP_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_ULP_ACTIVE 0x1

//! Field LOR - SyncE Lost Of Reference
#define PHY_IMASK_LOR_POS 8
//! Field LOR - SyncE Lost Of Reference
#define PHY_IMASK_LOR_MASK 0x100u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_LOR_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_LOR_ACTIVE 0x1

//! Field MBOX - Mailbox in VSPEC1 Interrupt Mask
#define PHY_IMASK_MBOX_POS 9
//! Field MBOX - Mailbox in VSPEC1 Interrupt Mask
#define PHY_IMASK_MBOX_MASK 0x200u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_MBOX_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is enabled
#define CONST_PHY_IMASK_MBOX_ACTIVE 0x1

//! Field ANC - Auto-Negotiation Complete Mask
#define PHY_IMASK_ANC_POS 10
//! Field ANC - Auto-Negotiation Complete Mask
#define PHY_IMASK_ANC_MASK 0x400u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_ANC_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_ANC_ACTIVE 0x1

//! Field ANE - Auto-Negotiation Error Mask
#define PHY_IMASK_ANE_POS 11
//! Field ANE - Auto-Negotiation Error Mask
#define PHY_IMASK_ANE_MASK 0x800u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_ANE_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_ANE_ACTIVE 0x1

//! Field NPTX - Next Page Transmitted Mask
#define PHY_IMASK_NPTX_POS 12
//! Field NPTX - Next Page Transmitted Mask
#define PHY_IMASK_NPTX_MASK 0x1000u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_NPTX_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_NPTX_ACTIVE 0x1

//! Field NPRX - Next Page Received Mask
#define PHY_IMASK_NPRX_POS 13
//! Field NPRX - Next Page Received Mask
#define PHY_IMASK_NPRX_MASK 0x2000u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_NPRX_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_NPRX_ACTIVE 0x1

//! Field MSRE - Master/Slave Resolution Error Mask
#define PHY_IMASK_MSRE_POS 14
//! Field MSRE - Master/Slave Resolution Error Mask
#define PHY_IMASK_MSRE_MASK 0x4000u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_MSRE_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_MSRE_ACTIVE 0x1

//! Field WOL - Wake-on-LAN Event Mask
#define PHY_IMASK_WOL_POS 15
//! Field WOL - Wake-on-LAN Event Mask
#define PHY_IMASK_WOL_MASK 0x8000u
//! Constant INACTIVE - Interrupt is masked out
#define CONST_PHY_IMASK_WOL_INACTIVE 0x0
//! Constant ACTIVE - Interrupt is activated
#define CONST_PHY_IMASK_WOL_ACTIVE 0x1

//! @}

//! \defgroup PHY_ISTAT Register PHY_ISTAT - Interrupt Status Register (Register 0.26)
//! @{

//! Register Offset (relative)
#define PHY_ISTAT 0x34
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_ISTAT 0x00000034u

//! Register Reset Value
#define PHY_ISTAT_RST 0x0000u

//! Field LSTC - Link State Change Interrupt Status
#define PHY_ISTAT_LSTC_POS 0
//! Field LSTC - Link State Change Interrupt Status
#define PHY_ISTAT_LSTC_MASK 0x1u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_LSTC_INACTIVE 0x0
//! Constant ACTIVE - Link State Change event is the source of the interrupt
#define CONST_PHY_ISTAT_LSTC_ACTIVE 0x1

//! Field LSPC - Link Speed Change Interrupt Status
#define PHY_ISTAT_LSPC_POS 1
//! Field LSPC - Link Speed Change Interrupt Status
#define PHY_ISTAT_LSPC_MASK 0x2u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_LSPC_INACTIVE 0x0
//! Constant ACTIVE - Link Speed Change event is the source of the interrupt
#define CONST_PHY_ISTAT_LSPC_ACTIVE 0x1

//! Field DXMC - Duplex Mode Change Interrupt Status
#define PHY_ISTAT_DXMC_POS 2
//! Field DXMC - Duplex Mode Change Interrupt Status
#define PHY_ISTAT_DXMC_MASK 0x4u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_DXMC_INACTIVE 0x0
//! Constant ACTIVE - Duplex Mode Change event is the source of the interrupt
#define CONST_PHY_ISTAT_DXMC_ACTIVE 0x1

//! Field MDIXC - MDIX Change Detect Interrupt Status
#define PHY_ISTAT_MDIXC_POS 3
//! Field MDIXC - MDIX Change Detect Interrupt Status
#define PHY_ISTAT_MDIXC_MASK 0x8u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_MDIXC_INACTIVE 0x0
//! Constant ACTIVE - MDIX Change event is the source of the interrupt
#define CONST_PHY_ISTAT_MDIXC_ACTIVE 0x1

//! Field MDIPC - MDI Polarity Change Detect Interrupt Status
#define PHY_ISTAT_MDIPC_POS 4
//! Field MDIPC - MDI Polarity Change Detect Interrupt Status
#define PHY_ISTAT_MDIPC_MASK 0x10u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_MDIPC_INACTIVE 0x0
//! Constant ACTIVE - MDIPC Change event is the source of the interrupt
#define CONST_PHY_ISTAT_MDIPC_ACTIVE 0x1

//! Field ADSC - Link Speed Auto-Downspeed Detect Interrupt Status
#define PHY_ISTAT_ADSC_POS 5
//! Field ADSC - Link Speed Auto-Downspeed Detect Interrupt Status
#define PHY_ISTAT_ADSC_MASK 0x20u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_ADSC_INACTIVE 0x0
//! Constant ACTIVE - ADSC Change event is the source of the interrupt
#define CONST_PHY_ISTAT_ADSC_ACTIVE 0x1

//! Field TEMP - TEMP
#define PHY_ISTAT_TEMP_POS 6
//! Field TEMP - TEMP
#define PHY_ISTAT_TEMP_MASK 0x40u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_TEMP_INACTIVE 0x0
//! Constant ACTIVE - TEMP Change event is the source of the interrupt
#define CONST_PHY_ISTAT_TEMP_ACTIVE 0x1

//! Field ULP - ULP Entry Indication
#define PHY_ISTAT_ULP_POS 7
//! Field ULP - ULP Entry Indication
#define PHY_ISTAT_ULP_MASK 0x80u
//! Constant INACTIVE - No indication of ULP entry
#define CONST_PHY_ISTAT_ULP_INACTIVE 0x0
//! Constant ACTIVE - Indication of ULP Entry
#define CONST_PHY_ISTAT_ULP_ACTIVE 0x1

//! Field LOR - SyncE Lost Of Reference
#define PHY_ISTAT_LOR_POS 8
//! Field LOR - SyncE Lost Of Reference
#define PHY_ISTAT_LOR_MASK 0x100u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_LOR_INACTIVE 0x0
//! Constant ACTIVE - LOR Change event is the source of the interrupt
#define CONST_PHY_ISTAT_LOR_ACTIVE 0x1

//! Field RES - Reserved
#define PHY_ISTAT_RES_POS 9
//! Field RES - Reserved
#define PHY_ISTAT_RES_MASK 0x200u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_RES_INACTIVE 0x0
//! Constant ACTIVE - MBOX Change event is the source of the interrupt
#define CONST_PHY_ISTAT_RES_ACTIVE 0x1

//! Field ANC - Auto-Negotiation Complete Interrupt Status
#define PHY_ISTAT_ANC_POS 10
//! Field ANC - Auto-Negotiation Complete Interrupt Status
#define PHY_ISTAT_ANC_MASK 0x400u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_ANC_INACTIVE 0x0
//! Constant ACTIVE - ANEG complete event is the source of the interrupt
#define CONST_PHY_ISTAT_ANC_ACTIVE 0x1

//! Field ANE - Auto-Negotiation Error Interrupt Status
#define PHY_ISTAT_ANE_POS 11
//! Field ANE - Auto-Negotiation Error Interrupt Status
#define PHY_ISTAT_ANE_MASK 0x800u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_ANE_INACTIVE 0x0
//! Constant ACTIVE - ANEG error event is the source of the interrupt
#define CONST_PHY_ISTAT_ANE_ACTIVE 0x1

//! Field NPTX - Next Page Transmitted Interrupt Status
#define PHY_ISTAT_NPTX_POS 12
//! Field NPTX - Next Page Transmitted Interrupt Status
#define PHY_ISTAT_NPTX_MASK 0x1000u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_NPTX_INACTIVE 0x0
//! Constant ACTIVE - NPTX event is the source of the interrupt
#define CONST_PHY_ISTAT_NPTX_ACTIVE 0x1

//! Field NPRX - Next Page Received Interrupt Status
#define PHY_ISTAT_NPRX_POS 13
//! Field NPRX - Next Page Received Interrupt Status
#define PHY_ISTAT_NPRX_MASK 0x2000u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_NPRX_INACTIVE 0x0
//! Constant ACTIVE - NPTX event is the source of the interrupt
#define CONST_PHY_ISTAT_NPRX_ACTIVE 0x1

//! Field MSRE - Master/Slave Resolution Error Interrupt Status
#define PHY_ISTAT_MSRE_POS 14
//! Field MSRE - Master/Slave Resolution Error Interrupt Status
#define PHY_ISTAT_MSRE_MASK 0x4000u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_MSRE_INACTIVE 0x0
//! Constant ACTIVE - MSRE event is the source of the interrupt
#define CONST_PHY_ISTAT_MSRE_ACTIVE 0x1

//! Field WOL - Wake-on-LAN Interrupt Status
#define PHY_ISTAT_WOL_POS 15
//! Field WOL - Wake-on-LAN Interrupt Status
#define PHY_ISTAT_WOL_MASK 0x8000u
//! Constant INACTIVE - This event is not the interrupt source
#define CONST_PHY_ISTAT_WOL_INACTIVE 0x0
//! Constant ACTIVE - WoL event is the source of the interrupt
#define CONST_PHY_ISTAT_WOL_ACTIVE 0x1

//! @}

//! \defgroup PHY_LED Register PHY_LED - LED Control Register (Register 0.27)
//! @{

//! Register Offset (relative)
#define PHY_LED 0x36
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_LED 0x00000036u

//! Register Reset Value
#define PHY_LED_RST 0xFF00u

//! Field LED0DA - Direct Access to LED0
#define PHY_LED_LED0DA_POS 0
//! Field LED0DA - Direct Access to LED0
#define PHY_LED_LED0DA_MASK 0x1u
//! Constant OFF - Switch off the LED
#define CONST_PHY_LED_LED0DA_OFF 0x0
//! Constant ON - Switch on the LED
#define CONST_PHY_LED_LED0DA_ON 0x1

//! Field LED1DA - Direct Access to LED1
#define PHY_LED_LED1DA_POS 1
//! Field LED1DA - Direct Access to LED1
#define PHY_LED_LED1DA_MASK 0x2u
//! Constant OFF - Switch off the LED
#define CONST_PHY_LED_LED1DA_OFF 0x0
//! Constant ON - Switch on the LED
#define CONST_PHY_LED_LED1DA_ON 0x1

//! Field LED2DA - Direct Access to LED2
#define PHY_LED_LED2DA_POS 2
//! Field LED2DA - Direct Access to LED2
#define PHY_LED_LED2DA_MASK 0x4u
//! Constant OFF - Switch off the LED
#define CONST_PHY_LED_LED2DA_OFF 0x0
//! Constant ON - Switch on the LED
#define CONST_PHY_LED_LED2DA_ON 0x1

//! Field LED3DA - Direct Access to LED3
#define PHY_LED_LED3DA_POS 3
//! Field LED3DA - Direct Access to LED3
#define PHY_LED_LED3DA_MASK 0x8u
//! Constant OFF - Switch off the LED
#define CONST_PHY_LED_LED3DA_OFF 0x0
//! Constant ON - Switch on the LED
#define CONST_PHY_LED_LED3DA_ON 0x1

//! Field RES1 - Reserved
#define PHY_LED_RES1_POS 4
//! Field RES1 - Reserved
#define PHY_LED_RES1_MASK 0xF0u

//! Field LED0EN - Enable Integrated Function of LED0
#define PHY_LED_LED0EN_POS 8
//! Field LED0EN - Enable Integrated Function of LED0
#define PHY_LED_LED0EN_MASK 0x100u
//! Constant DISABLE - Disables the integrated LED function
#define CONST_PHY_LED_LED0EN_DISABLE 0x0
//! Constant ENABLE - Enables the integrated LED function
#define CONST_PHY_LED_LED0EN_ENABLE 0x1

//! Field LED1EN - Enable Integrated Function of LED1
#define PHY_LED_LED1EN_POS 9
//! Field LED1EN - Enable Integrated Function of LED1
#define PHY_LED_LED1EN_MASK 0x200u
//! Constant DISABLE - Disables the integrated LED function
#define CONST_PHY_LED_LED1EN_DISABLE 0x0
//! Constant ENABLE - Enables the integrated LED function
#define CONST_PHY_LED_LED1EN_ENABLE 0x1

//! Field LED2EN - Enable Integrated Function of LED2
#define PHY_LED_LED2EN_POS 10
//! Field LED2EN - Enable Integrated Function of LED2
#define PHY_LED_LED2EN_MASK 0x400u
//! Constant DISABLE - Disables the integrated LED function
#define CONST_PHY_LED_LED2EN_DISABLE 0x0
//! Constant ENABLE - Enables the integrated LED function
#define CONST_PHY_LED_LED2EN_ENABLE 0x1

//! Field LED3EN - Enable Integrated Function of LED3
#define PHY_LED_LED3EN_POS 11
//! Field LED3EN - Enable Integrated Function of LED3
#define PHY_LED_LED3EN_MASK 0x800u
//! Constant DISABLE - Disables the integrated LED function
#define CONST_PHY_LED_LED3EN_DISABLE 0x0
//! Constant ENABLE - Enables the integrated LED function
#define CONST_PHY_LED_LED3EN_ENABLE 0x1

//! Field INV - Invert LED Output
#define PHY_LED_INV_POS 12
//! Field INV - Invert LED Output
#define PHY_LED_INV_MASK 0xF000u

//! @}

//! \defgroup PHY_TPGCTRL Register PHY_TPGCTRL - Test-Packet Generator Control (Register 0.28)
//! @{

//! Register Offset (relative)
#define PHY_TPGCTRL 0x38
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_TPGCTRL 0x00000038u

//! Register Reset Value
#define PHY_TPGCTRL_RST 0x0000u

//! Field EN - Enable the TPG
#define PHY_TPGCTRL_EN_POS 0
//! Field EN - Enable the TPG
#define PHY_TPGCTRL_EN_MASK 0x1u
//! Constant DISABLE - Disables the TPG
#define CONST_PHY_TPGCTRL_EN_DISABLE 0x0
//! Constant ENABLE - Enables the TPG
#define CONST_PHY_TPGCTRL_EN_ENABLE 0x1

//! Field START - Start or Stop TPG Data Generation.
#define PHY_TPGCTRL_START_POS 1
//! Field START - Start or Stop TPG Data Generation.
#define PHY_TPGCTRL_START_MASK 0x2u
//! Constant STOP - Stops the TPG data generation
#define CONST_PHY_TPGCTRL_START_STOP 0x0
//! Constant START - Starts the TPG data generation
#define CONST_PHY_TPGCTRL_START_START 0x1

//! Field RES1 - Reserved
#define PHY_TPGCTRL_RES1_POS 2
//! Field RES1 - Reserved
#define PHY_TPGCTRL_RES1_MASK 0xCu

//! Field SIZE - Packet Size
#define PHY_TPGCTRL_SIZE_POS 4
//! Field SIZE - Packet Size
#define PHY_TPGCTRL_SIZE_MASK 0x70u
//! Constant B64 - Packet length is 64 bytes
#define CONST_PHY_TPGCTRL_SIZE_B64 0x0
//! Constant B128 - Packet length is 128 bytes
#define CONST_PHY_TPGCTRL_SIZE_B128 0x1
//! Constant B256 - Packet length is 256 bytes
#define CONST_PHY_TPGCTRL_SIZE_B256 0x2
//! Constant B512 - Packet length is 512 bytes
#define CONST_PHY_TPGCTRL_SIZE_B512 0x3
//! Constant B1024 - Packet length is 1024 bytes
#define CONST_PHY_TPGCTRL_SIZE_B1024 0x4
//! Constant B1518 - Packet length is 1518 bytes
#define CONST_PHY_TPGCTRL_SIZE_B1518 0x5
//! Constant B9600 - Packet length is 9600 bytes
#define CONST_PHY_TPGCTRL_SIZE_B9600 0x6

//! Field RES2 - Reserved.
#define PHY_TPGCTRL_RES2_POS 7
//! Field RES2 - Reserved.
#define PHY_TPGCTRL_RES2_MASK 0x80u

//! Field TYPE - Packet Data Type
#define PHY_TPGCTRL_TYPE_POS 8
//! Field TYPE - Packet Data Type
#define PHY_TPGCTRL_TYPE_MASK 0x300u
//! Constant RANDOM - Use random data as the packet content
#define CONST_PHY_TPGCTRL_TYPE_RANDOM 0x0
//! Constant BYTEINC - Use byte increment as the packet content
#define CONST_PHY_TPGCTRL_TYPE_BYTEINC 0x1
//! Constant PREDEF - Use pre-defined content of the register TPGDATA
#define CONST_PHY_TPGCTRL_TYPE_PREDEF 0x2
//! Constant DBGDATA - Use Dbg data as packet content
#define CONST_PHY_TPGCTRL_TYPE_DBGDATA 0x3

//! Field IPGL - Inter-Packet Gap Length
#define PHY_TPGCTRL_IPGL_POS 10
//! Field IPGL - Inter-Packet Gap Length
#define PHY_TPGCTRL_IPGL_MASK 0xC00u
//! Constant BT48 - Length is 48 bit times
#define CONST_PHY_TPGCTRL_IPGL_BT48 0x0
//! Constant BT96 - Length is 96 bit times
#define CONST_PHY_TPGCTRL_IPGL_BT96 0x1
//! Constant BT960 - Length is 960 bit times
#define CONST_PHY_TPGCTRL_IPGL_BT960 0x2
//! Constant BT9600 - Length is 9600 bit times
#define CONST_PHY_TPGCTRL_IPGL_BT9600 0x3

//! Field RES3 - Reserved
#define PHY_TPGCTRL_RES3_POS 12
//! Field RES3 - Reserved
#define PHY_TPGCTRL_RES3_MASK 0x1000u

//! Field MODE - Mode of the TPG
#define PHY_TPGCTRL_MODE_POS 13
//! Field MODE - Mode of the TPG
#define PHY_TPGCTRL_MODE_MASK 0x2000u
//! Constant CONTINUOUS - Send packets continuously
#define CONST_PHY_TPGCTRL_MODE_CONTINUOUS 0x0
//! Constant SINGLE - Send a single packet.
#define CONST_PHY_TPGCTRL_MODE_SINGLE 0x1

//! Field CHSEL - Channel Selection
#define PHY_TPGCTRL_CHSEL_POS 14
//! Field CHSEL - Channel Selection
#define PHY_TPGCTRL_CHSEL_MASK 0xC000u
//! Constant CHA - Channel A is selected
#define CONST_PHY_TPGCTRL_CHSEL_CHA 0x0
//! Constant CHB - Channel B is selected
#define CONST_PHY_TPGCTRL_CHSEL_CHB 0x1
//! Constant CHC - Channel C is selected
#define CONST_PHY_TPGCTRL_CHSEL_CHC 0x2
//! Constant CHD - Channel D is selected
#define CONST_PHY_TPGCTRL_CHSEL_CHD 0x3

//! @}

//! \defgroup PHY_TPGDATA Register PHY_TPGDATA - Test-Packet Generator Data (Register 0.29)
//! @{

//! Register Offset (relative)
#define PHY_TPGDATA 0x3A
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_TPGDATA 0x0000003Au

//! Register Reset Value
#define PHY_TPGDATA_RST 0x00AAu

//! Field DATA - Data Byte to be Transmitted
#define PHY_TPGDATA_DATA_POS 0
//! Field DATA - Data Byte to be Transmitted
#define PHY_TPGDATA_DATA_MASK 0xFFu
//! Constant DVC - Select the debug data to be dump
#define CONST_PHY_TPGDATA_DATA_DVC 0x0Fu
//! Constant PREC - select whether to take full precision('1') of reduce precision '0' at bit 7
#define CONST_PHY_TPGDATA_DATA_PREC 0x80u
//! Constant PREC2 - For reduce precision, select the options with bits [6:5]
#define CONST_PHY_TPGDATA_DATA_PREC2 0x60u
//! Constant RESERVED - Reserved
#define CONST_PHY_TPGDATA_DATA_RESERVED 0x10u

//! Field SA - Source Address
#define PHY_TPGDATA_SA_POS 8
//! Field SA - Source Address
#define PHY_TPGDATA_SA_MASK 0xF00u

//! Field DA - Destination Address
#define PHY_TPGDATA_DA_POS 12
//! Field DA - Destination Address
#define PHY_TPGDATA_DA_MASK 0xF000u

//! @}

//! \defgroup PHY_FWV Register PHY_FWV - Firmware Version Register (Register 0.30)
//! @{

//! Register Offset (relative)
#define PHY_FWV 0x3C
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_FWV 0x0000003Cu

//! Register Reset Value
#define PHY_FWV_RST 0x0000u

//! Field MINOR - Minor Version Number
#define PHY_FWV_MINOR_POS 0
//! Field MINOR - Minor Version Number
#define PHY_FWV_MINOR_MASK 0xFFu

//! Field MAJOR - Major Version Number
#define PHY_FWV_MAJOR_POS 8
//! Field MAJOR - Major Version Number
#define PHY_FWV_MAJOR_MASK 0x7F00u

//! Field REL - Release Indication
#define PHY_FWV_REL_POS 15
//! Field REL - Release Indication
#define PHY_FWV_REL_MASK 0x8000u
//! Constant TEST - Indicates a test version
#define CONST_PHY_FWV_REL_TEST 0x0
//! Constant RELEASE - Indicates a released version
#define CONST_PHY_FWV_REL_RELEASE 0x1

//! @}

//! \defgroup PHY_TEST Register PHY_TEST - Internal Test Modes CDIAG and ABIST (Register 0.31)
//! @{

//! Register Offset (relative)
#define PHY_TEST 0x3E
//! Register Offset (absolute) for 1st Instance PHY
#define PHY_PHY_TEST 0x0000003Eu

//! Register Reset Value
#define PHY_TEST_RST 0x0000u

//! Field ABOPT - ABIST Option for DC test
#define PHY_TEST_ABOPT_POS 0
//! Field ABOPT - ABIST Option for DC test
#define PHY_TEST_ABOPT_MASK 0xFu

//! Field ABSEL - ABIST sub-mode selection
#define PHY_TEST_ABSEL_POS 4
//! Field ABSEL - ABIST sub-mode selection
#define PHY_TEST_ABSEL_MASK 0x30u
//! Constant ANALOG - ABIST Analog Tests
#define CONST_PHY_TEST_ABSEL_ANALOG 0x0
//! Constant DC - ABIST DC Tests
#define CONST_PHY_TEST_ABSEL_DC 0x1

//! Field ABRET - ABIST ReTrig
#define PHY_TEST_ABRET_POS 6
//! Field ABRET - ABIST ReTrig
#define PHY_TEST_ABRET_MASK 0x40u
//! Constant NORMAL - Normal Mode
#define CONST_PHY_TEST_ABRET_NORMAL 0x0
//! Constant RETRIG - Restart the current ABIST Test
#define CONST_PHY_TEST_ABRET_RETRIG 0x1

//! Field ABUART - ABIST UART output for debug
#define PHY_TEST_ABUART_POS 7
//! Field ABUART - ABIST UART output for debug
#define PHY_TEST_ABUART_MASK 0x80u
//! Constant NORMAL - ABIST normal output
#define CONST_PHY_TEST_ABUART_NORMAL 0x0
//! Constant UART - ABIST output to UART
#define CONST_PHY_TEST_ABUART_UART 0x1

//! Field RES - Reserved
#define PHY_TEST_RES_POS 8
//! Field RES - Reserved
#define PHY_TEST_RES_MASK 0x1F00u

//! Field TM - Proprietary Test Modes ABIST and CDIAG
#define PHY_TEST_TM_POS 13
//! Field TM - Proprietary Test Modes ABIST and CDIAG
#define PHY_TEST_TM_MASK 0xE000u
//! Constant CDIAG - GPY specific
#define CONST_PHY_TEST_TM_CDIAG 0x6
//! Constant ABIST - GPY specific
#define CONST_PHY_TEST_TM_ABIST 0x7

//! @}

//! @}

#endif
