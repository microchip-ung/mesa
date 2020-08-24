/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

//#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <gpy211.h>
#include <registers/phy/std.h>
#include <registers/p31g/p31g_mdio_pdi.h>
#include "gpy211_utility.h"

#if defined(UART_INTERFACE) && UART_INTERFACE
extern unsigned char device_uart;
extern int pc_uart_dataread(u32 Offset, u32 *value);
extern int pc_uart_datawrite(u32 Offset, u32 value);
#endif /* UART_INTERFACE */

#if !DEBUG_P31G_UART
#undef LOG_INFO
#define LOG_INFO(fmt, ...)
#endif

#if P31G_UART
static int smdio_flag = 0;
static u32 smdio_regnum = 0;
#endif

#if LOGM_IN_FILE
extern FILE *mdio_fp;
#endif
static inline int __gp211_reg_rd(u32 regaddr, u32 *data)
{
	pc_uart_dataread(regaddr, data);
	return 0;
}

static inline int __gp211_reg_wr(u32 regaddr, u32 data)
{
	pc_uart_datawrite(regaddr, data);
	return 0;
}

/**
	\brief API for chacking if device is busy on read/write.
	User application uses this API to device busy status.

	\param reg This is 32-bit control register number.

	\param mask This is 16-bit mask to specify busy bit.

	\param action This is action to return from func or continue.

	\return Return value as follows:
	- >=0: register value
	- <0: error code
*/
static inline int __is_device_busy(u32 reg, u16 mask, u8 action)
{
	int retCode = 0;

	do {
		u32 value = 0;
		u32 busyRetry = MAX_BUSY_RETRY;

		do {
			__gp211_reg_rd(reg, &value);
			value = value & mask;
		} while (value && --busyRetry);

		if (value && !busyRetry) {
			printf("ERROR: MDIO busy for too long\n");
			printf("%s %s %d (register=0x%x)\n", __FILE__, __func__, __LINE__, reg);

			if (RETURN_FROM_FUNC == action)
				return -1;

			retCode = -1;
		}
	} while (0);

	return retCode;
}

static int __gpy211_mmdio_read(void *busdata, u16 phyaddr, u32 regnum)
{
	u32 _mdio_ctrl = 0, _mdio_data = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

#ifdef __KERNEL__
	spin_lock_bh(&gswdev->lock_mdio);
#endif

	/* Check if device busy in read/write */
	__is_device_busy((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_CTRL / 2),
			 P31G_MDIO_PDI_MDIO_CTRL_MBUSY_MASK, RETURN_FROM_FUNC);
	_mdio_ctrl = ((CONST_P31G_MDIO_PDI_MDIO_CTRL_OP_RD << P31G_MDIO_PDI_MDIO_CTRL_OP_POS) |
		      ((phyaddr & 0x1F) << P31G_MDIO_PDI_MDIO_CTRL_PHYAD_POS) |
		      (regnum & 0x1F));
	LOG_INFO("MDIO read ctrl data :- 0x%x\n", _mdio_ctrl);
	/* Write MDIO Control Register */
	__gp211_reg_wr((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_CTRL / 2), _mdio_ctrl);
	/* Wait for device write to coplete */
	__is_device_busy((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_CTRL / 2),
			 P31G_MDIO_PDI_MDIO_CTRL_MBUSY_MASK, RETURN_FROM_FUNC);
	/* Read MDIO Data Register */
	__gp211_reg_rd((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_READ / 2), &_mdio_data);
	LOG_INFO("MDIO read data :- 0x%x\n", _mdio_data);
	_mdio_data = _mdio_data & 0xFFFF;
#if LOGM_IN_FILE
	//LOG_CRIT("MDIO read : PHY-add = %2x REG-addr = %4x\n", phyaddr, regnum); //Del later
	fprintf(mdio_fp, "MDIO read : PHY-add = %2x REG-addr = %4x\n", phyaddr, regnum); //Del later
#endif
#ifdef __KERNEL__
	spin_unlock_bh(&gswdev->lock_mdio);
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return _mdio_data;
}

static int __gpy211_mmdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data)
{
	u32 _mdio_ctrl = 0;
	LOG_INFO("Entering func name :- %s\n", __func__);

#ifdef __KERNEL__
	spin_lock_bh(&gswdev->lock_mdio);
#endif

	/* Check if device busy in read/write */
	__is_device_busy((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_CTRL / 2),
			 P31G_MDIO_PDI_MDIO_CTRL_MBUSY_MASK, RETURN_FROM_FUNC);
	/* Write MDIO Data Register */
	__gp211_reg_wr((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_WRITE / 2), data);
	LOG_INFO("MDIO write data :- 0x%x\n", data);
	_mdio_ctrl = ((CONST_P31G_MDIO_PDI_MDIO_CTRL_OP_WR << P31G_MDIO_PDI_MDIO_CTRL_OP_POS) |
		      ((phyaddr & 0x1F) << P31G_MDIO_PDI_MDIO_CTRL_PHYAD_POS) |
		      (regnum & 0x1F));
	LOG_INFO("MDIO write ctrl data :- 0x%x\n", _mdio_ctrl);
	/* Write MDIO Control Register */
	__gp211_reg_wr((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_CTRL / 2), _mdio_ctrl);
	/* Wait for device write to coplete */
	__is_device_busy((P31G_MDIO_PDI_P31G_MDIO_PDI_MDIO_CTRL / 2),
			 P31G_MDIO_PDI_MDIO_CTRL_MBUSY_MASK, RETURN_FROM_FUNC);
#if LOGM_IN_FILE
	//LOG_CRIT("MDIO write: PHY-add = %2x REG-addr = %4x Data-val = %4x\n", phyaddr, regnum, data); //Del later
	fprintf(mdio_fp, "MDIO write: PHY-add = %2x REG-addr = %4x Data-val = %4x\n", phyaddr, regnum, data); //Del later
#endif

#ifdef __KERNEL__
	spin_unlock_bh(&gswdev->lock_mdio);
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int gpy211_mdio_read(void *busdata, u16 phyaddr, u32 regnum)
{
	u32 _mdio_data;
#if defined(EN_UC8051_BP) & EN_UC8051_BP
	u32 _reset_status = 0;
#endif
	u16 _reg_num, _dev_id;
	LOG_INFO("Entering func name :- %s\n", __func__);

#ifdef __KERNEL__
	spin_lock_bh(&gswdev->lock_mdio);
#endif

#if F24S_UART
#if defined(EN_UC8051_BP) & EN_UC8051_BP

	/* Bypass uC8051 code if it's running */
	if ((device_uart & 0x2) == uC8051_BP) {
		__gp211_reg_rd(0xFA00, &_reset_status);
		_reset_status = (_reset_status & ~0x7000) + 0x2000;
		__gp211_reg_wr(0xFA00, _reset_status);
		usleep(1);
	}

#endif
	/* Disable Auto-Polling */
	__gp211_reg_wr((0xF400 + 0xB), 0x0000);
	/* Configure F24S GPIO alternate function to MMDIO */
	pc_uart_datawrite(0xf383, 0x03c3);
	pc_uart_datawrite(0xf384, 0x003f);
#elif P31G_UART

	if (smdio_flag) {
		__gp211_reg_rd(smdio_regnum, &_mdio_data);
		smdio_flag = 0;
		smdio_regnum = 0;
	} else
#endif
	if (regnum & MII_ADDR_C45) {	/* Check if CLAUSE 45 type read */
		/* CLAUSE 45 type read */
		_dev_id = (regnum >> 16) & 0x1F;
		_reg_num = regnum & 0xFFFF;
		LOG_INFO("Clause 45 type read\n");

		/* Write MMDCTRL address register */
		__gpy211_mmdio_write(busdata, phyaddr, STD_MMDCTRL / 2, _dev_id);
		/* Write MMDDATA address register */
		__gpy211_mmdio_write(busdata, phyaddr, STD_MMDDATA / 2, _reg_num);
		/* Write MMDCTRL address register */
		__gpy211_mmdio_write(busdata, phyaddr, STD_MMDCTRL / 2, (0x4000 + _dev_id));
		/* Read target register */
		_mdio_data = __gpy211_mmdio_read(busdata, phyaddr, STD_MMDDATA / 2);
	} else {
		_mdio_data = __gpy211_mmdio_read(busdata, phyaddr, regnum);
	}

#if F24S_UART
	/* Configure F24S GPIO alternate function to default */
	//pc_uart_datawrite(0xf383, 0x03c0);
	//pc_uart_datawrite(0xf384, 0x0000);
	/* Enable Auto-Polling */
	__gp211_reg_wr((0xF400 + 0xB), 0x006F);
#if defined(EN_UC8051_BP) & EN_UC8051_BP

	/* Disable bypassing uC8051 code if it's running */
	if ((device_uart & 0x2) == uC8051_BP) {
		__gp211_reg_rd(0xFA00, &_reset_status);
		_reset_status = _reset_status & ~0x7000;
		__gp211_reg_wr(0xFA00, _reset_status);
	}

#endif
#endif

#ifdef __KERNEL__
	spin_unlock_bh(&gswdev->lock_mdio);
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return _mdio_data;
}

int gpy211_mdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data)
{
	s16 ret = 0;
	u32 _mdio_data;
#if defined(EN_UC8051_BP) & EN_UC8051_BP
	u32 _reset_status = 0;
#endif
	u16 _reg_num, _dev_id;
	LOG_INFO("Entering func name :- %s\n", __func__);
	_mdio_data = (data & 0xFFFF);

#ifdef __KERNEL__
	spin_lock_bh(&gswdev->lock_mdio);
#endif

#if F24S_UART
#if defined(EN_UC8051_BP) & EN_UC8051_BP

	/* Bypass uC8051 code if it's running */
	if ((device_uart & 0x2) == uC8051_BP) {
		__gp211_reg_rd(0xFA00, &_reset_status);
		_reset_status = (_reset_status & ~0x7000) + 0x2000;
		__gp211_reg_wr(0xFA00, _reset_status);
		usleep(1);
	}

#endif
	/* Disable Auto-Polling */
	__gp211_reg_wr((0xF400 + 0xB), 0x0000);
	/* Configure F24S GPIO alternate function to MMDIO */
	pc_uart_datawrite(0xf383, 0x03c3);
	pc_uart_datawrite(0xf384, 0x003f);
#elif P31G_UART

	if (smdio_flag) {
		__gp211_reg_wr(smdio_regnum, _mdio_data);
		smdio_flag = 0;
		smdio_regnum = 0;
	} else if (phyaddr == ((struct gpy211_device *)busdata)->smdio_addr
		   && regnum == SMDIO_BADR) {
		smdio_flag = 1;
		smdio_regnum = _mdio_data;
	} else
#endif
	if (regnum & MII_ADDR_C45) {	/* Check if CLAUSE 45 type write */
		_dev_id = (regnum >> 16) & 0x1F;
		_reg_num = regnum & 0xFFFF;
		LOG_INFO("Clause 45 type write\n");

		/* write MMDCTRL address register */
		__gpy211_mmdio_write(busdata, phyaddr, STD_MMDCTRL / 2, _dev_id);
		/* write MMDDATA address register */
		__gpy211_mmdio_write(busdata, phyaddr, STD_MMDDATA / 2, _reg_num);
		/* write MMDCTRL address register */
		__gpy211_mmdio_write(busdata, phyaddr, STD_MMDCTRL / 2, (0x4000 + _dev_id));
		/* write target register */
		__gpy211_mmdio_write(busdata, phyaddr, STD_MMDDATA / 2, _mdio_data);
	} else {
		/* CLAUSE 22 (, extended) type write */
		ret = __gpy211_mmdio_write(busdata, phyaddr, regnum, data);
	}

#if F24S_UART
	/* Configure F24S GPIO alternate function to default */
	//pc_uart_datawrite(0xf383, 0x03c0);
	//pc_uart_datawrite(0xf384, 0x0000);
	/* Enable Auto-Polling */
	__gp211_reg_wr((0xF400 + 0xB), 0x006F);
#if defined(EN_UC8051_BP) & EN_UC8051_BP

	/* Disable bypassing uC8051 code if it's running */
	if ((device_uart & 0x2) == uC8051_BP) {
		__gp211_reg_rd(0xFA00, &_reset_status);
		_reset_status = _reset_status & ~0x7000;
		__gp211_reg_wr(0xFA00, _reset_status);
	}

#endif
#endif

#ifdef __KERNEL__
	spin_unlock_bh(&gswdev->lock_mdio);
#endif

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

#if defined(P31G_IND_RW) && P31G_IND_RW
/* UART inteface suppot function */
int pm_indirect_read(struct gpy211_device *phy, u32 regaddr, u32 *data)
{
	int ret;
	s32 data_low, data_high;

	u16 addr_high = regaddr >> 16;
	u16 addr_low = regaddr & 0xFFFF;

	u16 pm_pdi_ctrl = ((PM_PDI_PM_PDI_CTRL / 4) & 0xFFFF); //0xE06F
	u16 pm_pdi_addrl = ((PM_PDI_PM_PDI_ADDRL / 4) & 0xFFFF); //0xE070
	u16 pm_pdi_addrh = ((PM_PDI_PM_PDI_ADDRH / 4) & 0xFFFF); //0xE071
	u16 pm_pdi_datal = ((PM_PDI_PM_PDI_DATAL / 4) & 0xFFFF); //0xE072
	u16 pm_pdi_datah = ((PM_PDI_PM_PDI_DATAH / 4) & 0xFFFF); //0xE073

	//Address to read
	ret = smdio_write(phy, pm_pdi_addrl, addr_low);

	if (ret < 0) {
		goto END;
	}

	ret = smdio_write(phy, pm_pdi_addrh, addr_high);

	if (ret < 0) {
		goto END;
	}

	//Read Control
	ret = smdio_write(phy, pm_pdi_ctrl, 0x01);

	if (ret < 0) {
		goto END;
	}

	//Read Data
	data_low = smdio_read(phy, pm_pdi_datal);

	if (data_low < 0) {
		goto END;
	}

	data_high = smdio_read(phy, pm_pdi_datah);

	if (data_high < 0) {
		goto END;
	}

	*data = ((data_high << 16) | data_low);

END:
	return ret;
}

int pm_indirect_write(struct gpy211_device *phy, u32 regaddr, u32 data)
{
	int ret;
	u16 data_low = data & 0xFFFF;
	u16	data_high = data >> 16;;

	u16 addr_high = regaddr >> 16;
	u16 addr_low = regaddr & 0xFFFF;

	u16 pm_pdi_ctrl = ((PM_PDI_PM_PDI_CTRL / 4) & 0xFFFF); //0xE06F
	u16 pm_pdi_addrl = ((PM_PDI_PM_PDI_ADDRL / 4) & 0xFFFF); //0xE070
	u16 pm_pdi_addrh = ((PM_PDI_PM_PDI_ADDRH / 4) & 0xFFFF); //0xE071
	u16 pm_pdi_datal = ((PM_PDI_PM_PDI_DATAL / 4) & 0xFFFF); //0xE072
	u16 pm_pdi_datah = ((PM_PDI_PM_PDI_DATAH / 4) & 0xFFFF); //0xE073

	//Address to write
	ret = smdio_write(phy, pm_pdi_addrl, addr_low);

	if (ret < 0) {
		goto END;
	}

	ret = smdio_write(phy, pm_pdi_addrh, addr_high);

	if (ret < 0) {
		goto END;
	}

	//Write Data
	ret = smdio_write(phy, pm_pdi_datal, data_low);

	if (ret < 0) {
		goto END;
	}

	ret = smdio_write(phy, pm_pdi_datah, data_high);

	if (ret < 0) {
		goto END;
	}

	//Write Control
	ret = smdio_write(phy, pm_pdi_ctrl, 0x02);

	if (ret < 0) {
		goto END;
	}

END:
	return ret;
}
#endif
