/******************************************************************************

         Copyright 2016 - 2017 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPHY211_COMMON_H_
#define _GPHY211_COMMON_H_

#include <gpy211.h>

#include "gpy211_cfg.h"
#include "gpy211_ver.h"
#include "gpy211_log.h"
#include "gpy211_regs.h"


#define MAX_RW_RETRY 100

#define FIELD_GET(val, name) (((val) & (name ## _MASK)) >> (name ## _POS))

#define FIELD_SET(val, name) (((val) << (name ## _POS)) & (name ## _MASK))

#define FIELD_REPLACE(src, val, name) (src = (((src) & (~(name ## _MASK))) | (FIELD_SET(val, name))))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif

static inline void none_lock(void *lock_data)
{
	LOG_INFO("Entering func name :- %s\n", __func__);
	LOG_INFO("Exiting func name :- %s\n", __func__);
}

static inline void none_unlock(void *lock_data)
{
	LOG_INFO("Entering func name :- %s\n", __func__);
	LOG_INFO("Exiting func name :- %s\n", __func__);
}

static inline int SMDIO_READ(struct gpy211_device *phy, u32 regaddr)
{
#if defined(EN_SMDIO_RW) && EN_SMDIO_RW
	return gpy2xx_smdio_read(phy, ((regaddr / 2) & 0xFFFF));
#else
	u32 data;

	if (gpy2xx_mbox_read16(phy, regaddr, &data) < 0)
		return -1;

#if defined(REG_RD_PRINT) && REG_RD_PRINT
	printf("\nReading addr %x, value %8x", regaddr, data);
#endif
	return data;
#endif
}

static inline int SMDIO_WRITE(struct gpy211_device *phy, u32 regaddr, u16 val)
{
#if defined(EN_SMDIO_RW) && EN_SMDIO_RW
	return gpy2xx_smdio_write(phy, ((regaddr / 2) & 0xFFFF), val);
#else
#if defined(REG_WR_PRINT) && REG_WR_PRINT
	printf("\nWriting addr %x, value %8x", regaddr, val);
#endif
	return gpy2xx_mbox_write16(phy, regaddr, val);
#endif
}

static inline int SMDIO_SET_MASK_BITS(struct gpy211_device *phy, u32 regaddr,
				      u16 mask, u16 bits)
{
	int ret;
	u16 val;
	/* Read register */
	ret = SMDIO_READ(phy, regaddr);

	if (ret < 0)
		return ret;

	/* Modify register */
	val = (u16)ret;
	val &= ~mask;
	val |= bits;
	/* Write register */
	return SMDIO_WRITE(phy, regaddr, val);
}

static inline int SMDIO_SET_BIT(struct gpy211_device *phy, u32 regaddr, u32 bit)
{
	return SMDIO_SET_MASK_BITS(phy, regaddr, 0, 1 << bit);
}

static inline int SMDIO_CLR_BIT(struct gpy211_device *phy, u32 regaddr, u32 bit)
{
	return SMDIO_SET_MASK_BITS(phy, regaddr, 1 << bit, 0);
}

static inline int PHY_READ(struct gpy211_device *phy, u32 regaddr)
{
	return gpy2xx_read(phy, regaddr / 2);
}

static inline int PHY_WRITE(struct gpy211_device *phy, u32 regaddr, u16 val)
{
	return gpy2xx_write(phy, regaddr / 2, val);
}

static inline int PHY_SET_MASK_BITS(struct gpy211_device *phy, u32 regaddr,
				    u16 mask, u16 bits)
{
	int ret;
	u16 val;
	/* Read register */
	ret = PHY_READ(phy, regaddr);

	if (ret < 0)
		return ret;

	/* Modify register */
	val = (u16)ret;
	val &= ~mask;
	val |= bits;
	/* Write register */
	return PHY_WRITE(phy, regaddr, val);
}

static inline int PHY_SET_BIT(struct gpy211_device *phy, u32 regaddr, u32 bit)
{
	return PHY_SET_MASK_BITS(phy, regaddr, 0, 1 << bit);
}

static inline int PHY_CLR_BIT(struct gpy211_device *phy, u32 regaddr, u32 bit)
{
	return PHY_SET_MASK_BITS(phy, regaddr, 1 << bit, 0);
}

static inline int PHY_READ_MMD(struct gpy211_device *phy, int devad,
			       u32 regaddr)
{
	return gpy2xx_read_mmd(phy, devad, regaddr / 2);
}

static inline int PHY_WRITE_MMD(struct gpy211_device *phy, int devad,
				u32 regaddr, u16 val)
{
	return gpy2xx_write_mmd(phy, devad, regaddr / 2, val);
}

static inline int PHY_SET_MASK_MMD_BITS(struct gpy211_device *phy, int devad,
					u32 regaddr, u16 mask, u16 bits)
{
	int ret;
	u16 val;
	/* Read register */
	ret = PHY_READ_MMD(phy, devad, regaddr);

	if (ret < 0)
		return ret;

	/* Modify register */
	val = (u16)ret;
	val &= ~mask;
	val |= bits;
	/* Write register */
	return PHY_WRITE_MMD(phy, devad, regaddr, val);
}

static inline int PHY_SET_MMD_BIT(struct gpy211_device *phy, int devad,
				  u32 regaddr, u32 bit)
{
	return PHY_SET_MASK_MMD_BITS(phy, devad, regaddr, 0, 1 << bit);
}

static inline int PHY_CLR_MMD_BIT(struct gpy211_device *phy, int devad,
				  u32 regaddr, u32 bit)
{
	return PHY_SET_MASK_MMD_BITS(phy, devad, regaddr, 1 << bit, 0);
}

/* IP_MDIO half-word (16 bit) read */
static inline int PHY_MBOX_HWRD(struct gpy211_device *phy, u32 regaddr, u32 *regdata)
{
	int ret;

	ret = gpy2xx_mbox_read16(phy, regaddr, regdata);
#if defined(REG_RD_PRINT) && REG_RD_PRINT
	printf("\nReading addr %x, value %8x", regaddr, *regdata);
#endif
	return ret;
}

/* IP_MDIO half-word (16 bit) write */
static inline int PHY_MBOX_HWWR(struct gpy211_device *phy, u32 regaddr, u32 regdata)
{
	int ret;
	ret = gpy2xx_mbox_write16(phy, regaddr, regdata);
#if defined(REG_WR_PRINT) && REG_WR_PRINT
	printf("\nWriting addr %x, value %8x", regaddr, regdata);
#endif
	return ret;
}

/* IP_MDIO full-word (32 bit)read */
static inline int PHY_MBOX_READ(struct gpy211_device *phy, u32 regaddr, u32 *regdata)
{
	int ret;
	ret = gpy2xx_mbox_read32(phy, regaddr, regdata);
#if defined(REG_RD_PRINT) && REG_RD_PRINT
	printf("\nReading addr %x, value %8x", regaddr, *regdata);
#endif
	return ret;
}

/* IP_MDIO full-word (32 bit)write */
static inline int PHY_MBOX_WRITE(struct gpy211_device *phy, u32 regaddr, u32 regdata)
{
	int ret;
	ret = gpy2xx_mbox_write32(phy, regaddr, regdata);
#if defined(REG_WR_PRINT) && REG_WR_PRINT
	printf("\nWriting addr %x, value %8x", regaddr, regdata);
#endif
	return ret;
}


/* IP_XPCS half-word (16 bit) read */
static inline int PHY_XPCS_HWRD(struct gpy211_device *phy, u32 regaddr, u32 *regdata)
{
	int ret;
	u32 _base, _offset;


	_base = (regaddr >> 10);
	ret = gpy2xx_mbox_write32(phy, (USXGMII_PDI_REGISTERS_USXGMII_PDI_BASEADRR), _base);
#if defined(REG_RD_PRINT) && REG_RD_PRINT
	printf("\nReading addr %x, value %8x", USXGMII_PDI_REGISTERS_USXGMII_PDI_BASEADRR, _base);
#endif

	if (ret < 0) {
		return ret;
	}

	_offset = ((regaddr) & 0x3FF);

	ret = gpy2xx_mbox_read16(phy, (USXGMII_PDI_REGISTERS_MODULE_BASE + _offset), regdata);
#if defined(REG_RD_PRINT) && REG_RD_PRINT
	printf("\nReading addr %x, value %8x", USXGMII_PDI_REGISTERS_MODULE_BASE + _offset, *regdata);
#endif
	return ret;
}


/* IP_XPCS half-word (16 bit) write */
static inline int PHY_XPCS_HWWR(struct gpy211_device *phy, u32 regaddr, u32 regdata)
{
	int ret;
	u32 _base, _offset;


	_base = (regaddr >> 10);
	ret = gpy2xx_mbox_write32(phy, (USXGMII_PDI_REGISTERS_USXGMII_PDI_BASEADRR), _base);
#if defined(REG_RD_PRINT) && REG_RD_PRINT
	printf("\nReading addr %x, value %8x", USXGMII_PDI_REGISTERS_USXGMII_PDI_BASEADRR, _base);
#endif

	if (ret < 0) {
		return ret;
	}

	_offset = ((regaddr) & 0x3FF);

	ret = gpy2xx_mbox_write16(phy, (USXGMII_PDI_REGISTERS_MODULE_BASE + _offset), regdata);
#if defined(REG_RD_PRINT) && REG_RD_PRINT
	printf("\nReading addr %x, value %8x", USXGMII_PDI_REGISTERS_MODULE_BASE + _offset, regdata);
#endif
	return ret;
}
#endif /* _GPHY211_COMMON_H_ */
