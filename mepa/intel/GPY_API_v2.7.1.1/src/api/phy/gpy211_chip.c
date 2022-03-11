/******************************************************************************

         Copyright 2020 - 2021 MaxLinear Inc.
         Copyright 2016 - 2020 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#include "gpy211_common.h"
#include "gpy211_chip.h"
#include "gpy211_regs.h"
#include "gpy211_phy.h"

#if defined(SAFE_C_LIB) && SAFE_C_LIB
errno_t memcpy_s(void *restrict dest, rsize_t dmax, const void *restrict src,
		 rsize_t smax);
#endif

static int __is_rw_done(struct gpy211_device *phy, u32 reg, u32 bit)
{
	int retCode = 0;

	do {
		u32 value = 0;
		u32 busyRetry = MAX_RW_RETRY;

		do {
			value = SMDIO_READ(phy, reg);
			value = (value >> bit) & 1;
		} while ((value) && (--busyRetry));

		if ((!value && !busyRetry)) {
			LOG_CRIT("\nERROR: RW action not finished for too long @ ");
			LOG_CRIT("%s %d\n", __func__, __LINE__);

			retCode = -1;
		}
	} while (0);

	return retCode;
}

int __gpy211_chip_init(struct gpy211_device *phy)
{
	struct gpy211_device *data =
			phy->shared_data == NULL ? phy : phy->shared_data;
	int wd1, wd2;
	LOG_INFO("Entering func name :- %s\n", __func__);

	/* Double check SMDIO Address */
	wd1 = SMDIO_READ(phy,
			 SMDIO_PDI_SMDIO_REGISTERS_SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG);

	if (wd1 < 0) {
		LOG_CRIT("ERROR: SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG read fails\n");
		return wd1;
	}

	if (phy->smdio_addr !=
	    FIELD_GET(wd1, SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_ADDR)) {
		LOG_CRIT("ERROR: given & set SMDIO addr mismatch %d != %d\n",
			 phy->smdio_addr,
			 FIELD_GET(wd1, SMDIO_PDI_SMDIO_REGISTERS_SMDIO_CFG_ADDR));
		return -ENXIO;
	}

	/* Get Chip ID (Vendor Specific) */
	wd1 = SMDIO_READ(phy, CHIPID_CHIPID_MPS_CHIPID_L);

	if (wd1 < 0) {
		LOG_CRIT("ERROR: CHIPID_MPS_CHIPID_L read fails\n");
		return wd1;
	}

	wd2 = SMDIO_READ(phy, CHIPID_CHIPID_MPS_CHIPID_M);

	if (wd2 < 0) {
		LOG_CRIT("ERROR: CHIPID_MPS_CHIPID_M read fails\n");
		return wd2;
	}

	data->id.manufacturer_id = FIELD_GET(wd1, CHIPID_MPS_CHIPID_L_MANID);
	data->id.part_no =  FIELD_GET(wd1, CHIPID_MPS_CHIPID_L_PNUML)
			    | (FIELD_GET(wd2, CHIPID_MPS_CHIPID_M_PNUMM) << 4);
	data->id.version = FIELD_GET(wd2, CHIPID_MPS_CHIPID_M_VERSION);

	if (data->id.manufacturer_id != 0x089) {
		LOG_CRIT("ERROR: manufacturer id is != 0x089\n");
		return -ENXIO;
	}

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return 0;
}

int gpy2xx_gpio_cfg(struct gpy211_device *phy, struct gpy211_gpio *gpio)
{
	int ret;
	u16 port;
	u16 pin;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gpio == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	pin = gpio->pin;

	/* Validate input params */
	//if (port >= ARRAY_SIZE(gpio_reg) || pin > GPIO_PINS_MAX) {
	if (pin > GPIO_PINS_MAX) {
		LOG_WARN("WARN: Invalid input pinId\n");
		return -EINVAL;
	}

	port = pin >> 4;
	pin = pin % 16;

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Input/Output */
	if ((gpio->flags & GPIOF_DIR_IN))
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].dir, pin);
	else {
		if ((gpio->flags & GPIOF_OUTPUT_HIGH))
			ret = SMDIO_SET_BIT(phy, gpio_reg[port].output, pin);
		else
			ret = SMDIO_CLR_BIT(phy, gpio_reg[port].output, pin);

		if (ret == 0)
			ret = SMDIO_SET_BIT(phy, gpio_reg[port].dir, pin);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_DIR/GPIO_OUT modify fails\n");
		goto END;
	}

	/* Open Drain */
//	if (gpio->flags & GPIOF_DIR_OUT) {
	if (gpio->flags & GPIOF_OPEN_DRAIN)
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].od, pin);
	else
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].od, pin);

//	}

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_OD (Open Drain) modify fails\n");
		goto END;
	}

	/* Pull Up/Down Enable/Selection */
//	if (gpio->flags & GPIOF_DIR_IN) {
	switch (gpio->flags & GPIOF_PULL_DOWN) {
	case 0:
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].pull_en, pin);
		break;

	case GPIOF_PULL_UP:
	case GPIOF_PULL_DOWN:
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].pull_en, pin);

		if (ret < 0) {
			LOG_CRIT("ERROR: GPIO_PUDEN (Pull-Up/Pull-Down) enable fails\n");
			goto END;
		}

		if ((gpio->flags & GPIOF_PULL_DOWN) == GPIOF_PULL_UP) {
			ret = SMDIO_SET_BIT(phy, gpio_reg[port].pull_up, pin);
		} else {
			ret = SMDIO_CLR_BIT(phy, gpio_reg[port].pull_up, pin);
		}

		break;

	default:
		ret = -EINVAL;
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_PUDSEL (Pull-Up/Pull-Down) select fails\n");
		goto END;
	}

//	}

	/* Fast/Slow Slew */
	if ((gpio->flags & GPIOF_FAST_SLEW))
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].fast_slew, pin);
	else
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].fast_slew, pin);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_SLEW (GPIO PAD Slew Control) modify fails\n");
		goto END;
	}

	/* Alternative Function */
	if ((gpio->flags & GPIOF_FUNC(1)))
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].alt0, pin);
	else
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].alt0, pin);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL0 (Alternate Function Select 0) modify fails\n");
		goto END;
	}

	if ((gpio->flags & GPIOF_FUNC(2)))
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].alt1, pin);
	else
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].alt1, pin);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL1 (Alternate Function Select 1) modify fails\n");
		goto END;
	}

	/* Pad Strength */
	if ((gpio->flags & GPIOF_PAD_STR(1)))
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].strength0, pin);
	else
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].strength0, pin);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_DRIVE0 (GPIO PAD Driver Strength 0) modify fails\n");
		goto END;
	}

	if ((gpio->flags & GPIOF_PAD_STR(2)))
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].strength1, pin);
	else
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].strength1, pin);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_DRIVE1 (GPIO PAD Driver Strength 1) modify fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gpio_get(struct gpy211_device *phy, struct gpy211_gpio *gpio)
{
	int ret;
	u16 port;
	u16 pin;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gpio == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	pin = gpio->pin;

	/* Validate input params */
	//if (port >= ARRAY_SIZE(gpio_reg) || pin > GPIO_PINS_MAX) {
	if (pin > GPIO_PINS_MAX) {
		LOG_WARN("WARN: Invalid input pinId\n");
		return -EINVAL;
	}

	port = pin >> 4;
	pin = pin % 16;

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Init flags to zero */
	gpio->flags = 0;

	/* Input/Output */
	ret = SMDIO_READ(phy, gpio_reg[port].dir);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_DIR read fails\n");
		goto END;
	}

	if ((ret & (1 << pin))) {
		gpio->flags |= GPIOF_DIR_OUT;
		ret = SMDIO_READ(phy, gpio_reg[port].output);

		if (ret < 0) {
			LOG_CRIT("ERROR: GPIO_OUT read fails\n");
			goto END;
		}

		if ((ret & (1 << pin)))
			gpio->flags |= GPIOF_OUTPUT_HIGH;
		else
			gpio->flags |= GPIOF_OUTPUT_LOW;
	} else {
		gpio->flags |= GPIOF_DIR_IN;
		ret = SMDIO_READ(phy, gpio_reg[port].input);

		if (ret < 0) {
			LOG_CRIT("ERROR: GPIO_IN read fails\n");
			goto END;
		}

		if ((ret & (1 << pin)))
			gpio->flags |= GPIOF_INPUT_HIGH;
		else
			gpio->flags |= GPIOF_INPUT_LOW;

	}

	/* Open Drain */
	ret = SMDIO_READ(phy, gpio_reg[port].od);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_OD read fails\n");
		goto END;
	}

	if (!(ret & (1 << pin)))
		gpio->flags |= GPIOF_OPEN_DRAIN;

	/* Pull Up/Down Enable/Selection */
	ret = SMDIO_READ(phy, gpio_reg[port].pull_en);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_PUDEN read fails\n");
		goto END;
	}

	if ((ret & (1 << pin))) {
		ret = SMDIO_READ(phy, gpio_reg[port].pull_up);

		if (ret < 0) {
			LOG_CRIT("ERROR: GPIO_SEL read fails\n");
			goto END;
		}

		if ((ret & (1 << pin)))
			gpio->flags |= GPIOF_PULL_UP;
		else
			gpio->flags |= GPIOF_PULL_DOWN;
	}

	/* Fast/Slow Slew */
	ret = SMDIO_READ(phy, gpio_reg[port].fast_slew);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_SLEW read fails\n");
		goto END;
	}

	if ((ret & (1 << pin)))
		gpio->flags |= GPIOF_FAST_SLEW;

	/* Alternative Function */
	ret = SMDIO_READ(phy, gpio_reg[port].alt0);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL0 read fails\n");
		goto END;
	}

	if ((ret & (1 << pin)))
		gpio->flags |= GPIOF_FUNC(1);

	ret = SMDIO_READ(phy, gpio_reg[port].alt1);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL1 read fails\n");
		goto END;
	}

	if ((ret & (1 << pin)))
		gpio->flags |= GPIOF_FUNC(2);

	/* Pad Strength */
	ret = SMDIO_READ(phy, gpio_reg[port].strength0);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_DRIVE0 read fails\n");
		goto END;
	}

	if ((ret & (1 << pin)))
		gpio->flags |= GPIOF_PAD_STR(1);

	ret = SMDIO_READ(phy, gpio_reg[port].strength1);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_DRIVE1 read fails\n");
		goto END;
	}

	if ((ret & (1 << pin)))
		gpio->flags |= GPIOF_PAD_STR(2);

	ret = 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gpio_output(struct gpy211_device *phy,
		       struct gpy211_gpio *gpio)
{
	int ret;
	u16 port;
	u16 pin;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gpio == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	pin = gpio->pin;

	/* Validate input params */
	//if (port >= ARRAY_SIZE(gpio_reg) || pin > GPIO_PINS_MAX) {
	if (pin > GPIO_PINS_MAX) {
		LOG_WARN("WARN: Invalid input pinId\n");
		return -EINVAL;
	}

	port = pin >> 4;
	pin = pin % 16;

	/* Acquire lock */
	phy->lock(phy->lock_data);

	if ((gpio->flags & GPIOF_OUTPUT_HIGH))
		ret = SMDIO_SET_BIT(phy, gpio_reg[port].output, pin);
	else
		ret = SMDIO_CLR_BIT(phy, gpio_reg[port].output, pin);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_OUT modify fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_gpio_input(struct gpy211_device *phy, struct gpy211_gpio *gpio)
{
	int ret;
	u16 port;
	u16 pin;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || gpio == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	pin = gpio->pin;

	/* Validate input params */
	//if (port >= ARRAY_SIZE(gpio_reg) || pin > GPIO_PINS_MAX) {
	if (pin > GPIO_PINS_MAX) {
		LOG_WARN("WARN: Invalid input pinId\n");
		return -EINVAL;
	}

	port = pin >> 4;
	pin = pin % 16;

	/* Acquire lock */
	phy->lock(phy->lock_data);

	gpio->flags = 0;
	/* Input */
	ret = SMDIO_READ(phy, gpio_reg[port].dir);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_DIR read fails\n");
		goto END;
	}

	if (!(ret & (1 << pin))) {
		ret = SMDIO_READ(phy, gpio_reg[port].input);

		if (ret < 0) {
			LOG_CRIT("ERROR: GPIO_IN read fails\n");
			goto END;
		}
	} else
		goto END;

	if ((ret & (1 << pin)))
		gpio->flags |= GPIOF_INPUT_HIGH;
	else
		gpio->flags |= GPIOF_INPUT_LOW;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_led_br_cfg(struct gpy211_device *phy,
		      struct gpy211_led_brlvl_cfg *brtness_cfg)
{
	u16 _brtness_cfg;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || brtness_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate LED brightness level mode */
	if (!(brtness_cfg->mode >= LED_BRLEVEL_MIN &&
	      brtness_cfg->mode <= LED_BRLEVEL_MAX)) {
		LOG_WARN("WARN: Invalid input (brightMode) - LED brightness level mode\n");
		return -EINVAL;
	}

	/* Validate LED min brightness level range */
	if (brtness_cfg->lvl_min < LED_BRIGHT_LVL_MIN ||
	    brtness_cfg->lvl_min > LED_BRIGHT_LVL_MAX) {
		LOG_WARN("WARN: Invalid input (brightLvlMin) - LED min brightness level\n");
		return -EINVAL;
	}

	/* Validate LED max brightness level range */
	if (brtness_cfg->lvl_max < LED_BRIGHT_LVL_MIN ||
	    brtness_cfg->lvl_max > LED_BRIGHT_LVL_MAX) {
		LOG_WARN("WARN: Invalid input (brightLvlMax) - LED max brightness level\n");
		return -EINVAL;
	}

	/* Validate Detect Edge range */
	if (!(brtness_cfg->sw_edge >= LED_EDGE_DET_MIN &&
	      brtness_cfg->sw_edge <= LED_EDGE_DET_MAX)) {
		LOG_WARN("WARN: Invalid input (swEdgeDetect) - Detect Edge\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Read LED Brightness configuration */
	ret = SMDIO_READ(phy, LED_BCTRL_PDI_REGISTERS_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: LED_BRT_CTRL read fails\n");
		goto END;
	}

	_brtness_cfg = (u16)ret;

	/* Modify LED configuration */
	/* Set LED Brightness 2 Level Switch Disable */
	FIELD_REPLACE(_brtness_cfg, 0, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_TWOSWEN);

	/* Set LED Brightness Control Enable */
	if (brtness_cfg->mode != LED_BRLVL_MAX) {
		FIELD_REPLACE(_brtness_cfg, 1, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN);
	} else {
		FIELD_REPLACE(_brtness_cfg, 0, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN);
	}

	/* Set LED Switch edge detect */
	if (brtness_cfg->sw_edge == LED_EDGE_DETECT_RISING) {
		FIELD_REPLACE(_brtness_cfg, 1, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EDGE_DET);
	} else {
		FIELD_REPLACE(_brtness_cfg, 0, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EDGE_DET);
	}

	/* Set Minimum LED Brightness Value */
	FIELD_REPLACE(_brtness_cfg, brtness_cfg->lvl_min,
		      LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MINLEVEL);
	/* Set Miximum LED Brightness Value */
	FIELD_REPLACE(_brtness_cfg, brtness_cfg->lvl_max,
		      LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MAXLEVEL);

	/* Write LED Brightness configuration */
	ret = SMDIO_WRITE(phy, LED_BCTRL_PDI_REGISTERS_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL,
			  _brtness_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: LED_BRT_CTRL write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_led_br_get(struct gpy211_device *phy,
		      struct gpy211_led_brlvl_cfg *brtness_cfg)
{
	u16 _brtness_cfg;
	u16 _brt_ctrl_en, _brt_ctrl_twosen;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || brtness_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Read LED Brightness configuration */
	ret = SMDIO_READ(phy, LED_BCTRL_PDI_REGISTERS_LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL);

	if (ret < 0) {
		LOG_CRIT("ERROR: LED_BRT_CTRL read fails\n");
		goto END;
	}

	_brtness_cfg = (u16)ret;

	/* Get LED configuration */
	/* Get LED Brightness Control Enable */
	_brt_ctrl_en =	FIELD_GET(_brtness_cfg, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN);
	/* Get LED Brightness 2 Level Switch Enable */
	_brt_ctrl_twosen =	FIELD_GET(_brtness_cfg, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_TWOSWEN);

	/* Get LED Brightness Control Enable */
	// brtness_cfg-> = FIELD_GET(_brtness_cfg, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EN);
	/* Get LED Switch edge detect */
	brtness_cfg->sw_edge = FIELD_GET(_brtness_cfg, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_EDGE_DET);
	/* Get Minimum LED Brightness Value */
	brtness_cfg->lvl_min = FIELD_GET(_brtness_cfg, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MINLEVEL);
	/* Get Miximum LED Brightness Value */
	brtness_cfg->lvl_max = FIELD_GET(_brtness_cfg, LED_BCTRL_PDI_REGISTERS_LED_BRT_CTRL_MAXLEVEL);

	if ((_brt_ctrl_twosen == 1) && (_brt_ctrl_en == 1)) {
		LOG_CRIT("ERROR: 2 brightness level mode is not supported\n");
		ret = -EIO;
	} else if ((_brt_ctrl_twosen == 0) && (_brt_ctrl_en == 1))
		brtness_cfg->mode = LED_BRLVL_CONSTANT;
	else
		brtness_cfg->mode = LED_BRLVL_MAX;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

#if defined(EN_SUPPORT_TOP_INT) && EN_SUPPORT_TOP_INT
int gpy2xx_topin_cfg(struct gpy211_device *phy,
		     struct gpy211_extin *extin)
{
	u8 i;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || extin == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Interrupt ID range */
	if (extin->id < EXT_INT_ID_0 || extin->id > EXT_INT_ID_1) {
		LOG_WARN("WARN: Invalid input (intId) - Interrupt ID\n");
		return -EINVAL;
	}

	/* Validate Interrupt Trigger range */
	if (!(extin->ip_char >= EXTIN_IR_DISABLE && extin->ip_char <= EXTIN_IR_LOW)) {
		LOG_WARN("WARN: Invalid input (intTrigger) - Interrupt Trigger\n");
		return -EINVAL;
	}

	/* Validate Interrupt Module-0 range */
	if (!(extin->im0 >= EXTIN_IM0_MIN && extin->im0 <= EXTIN_IM0_MAX)) {
		LOG_WARN("WARN: Invalid input (intMod0) - Interrupt Module-0\n");
		return -EINVAL;
	}

	/* Validate Interrupt Module-1 range */
	if (!(extin->im1 >= EXTIN_IM1_MIN && extin->im1 <= EXTIN_IM1_MAX)) {
		LOG_WARN("WARN: Invalid input (intMod1) - Interrupt Module-1\n");
		return -EINVAL;
	}

	/* Validate Interrupt Module -2 range */
	if (!(extin->im2 >= EXTIN_IM2_MIN && extin->im2 <= EXTIN_IM2_MAX)) {
		LOG_WARN("WARN: Invalid input (intMod2) - Interrupt Module-2\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* ICU_PDI_REGISTERS_IM0_IER_0/1/2/3,
	   ICU_PDI_REGISTERS_IM1_IER,
	   ICU_PDI_REGISTERS_IM2_IER */
	for (i = 0; i < 4; i++) {
		ret = SMDIO_SET_MASK_BITS(phy,
					  (ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_IER_0 + (i * 2)),
					  extin->im0,  extin->im0);

		if (ret < 0) {
			LOG_CRIT("ERROR: IM0_IER_x write fails for IER = %d\n", i);
			goto END;
		}
	}

	/* Enable Interrupt Event of EXINT pin 0/1 */
	if (extin->id == EXT_INT_ID_0) {
		ret = SMDIO_SET_MASK_BITS(phy,
					  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_EINT0_IER,
					  extin->im0,  extin->im0);
	} else {
		ret = SMDIO_SET_MASK_BITS(phy,
					  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_EINT1_IER,
					  extin->im0,  extin->im0);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: IM0_EINTx_IER write fails for Interrupt ID = %d\n", extin->id);
		goto END;
	}

	ret = SMDIO_SET_MASK_BITS(phy,
				  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM1_IER,
				  extin->im1,  extin->im1);

	if (ret < 0) {
		LOG_CRIT("ERROR: IM1_IER write fails\n");
		goto END;
	}

	ret = SMDIO_SET_MASK_BITS(phy,
				  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM2_IER,
				  extin->im2,  extin->im2);

	if (ret < 0) {
		LOG_CRIT("ERROR: IM2_IER write fails\n");
		goto END;
	}

	/* Check if EXINT is configured as Input or Output */
	// TODO
	//2.Input
	/* Configure the edge 'level' of EXINT input pin */
	if (extin->id == EXT_INT_ID_0) {
		ret = SMDIO_SET_MASK_BITS(phy,
					  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_EIU_EXIN_CONF,
					  ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0_MASK,
					  FIELD_SET(extin->ip_char, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0));
	} else {
		ret = SMDIO_SET_MASK_BITS(phy,
					  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_EIU_EXIN_CONF,
					  ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1_MASK,
					  FIELD_SET(extin->ip_char, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1));
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: %s write fails\n", (extin->id == EXT_INT_ID_0) ? "EXIN_EIN0" : "EXIN_EIN1");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_topin_get(struct gpy211_device *phy,
		     struct gpy211_extin *extin)
{
	u16 val;
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || extin == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Interrupt ID range */
	if (extin->id < EXT_INT_ID_0 || extin->id > EXT_INT_ID_1) {
		LOG_WARN("WARN: Invalid input (intId) - Interrupt ID\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Check if EXINT is configured as Input or Output */
	// TODO
	//1.Input
	/* Get IM0's Interrupt Event of EXINT pin 0 */
	if (extin->id == EXT_INT_ID_0) {
		ret = SMDIO_READ(phy, ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_EINT0_IER);
	} else {
		ret = SMDIO_READ(phy, ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_EINT1_IER);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: IM0_EINTx_IER read fails for Interrupt ID = %d\n", extin->id);
		goto END;
	}

	extin->im0 = (u16)ret;

	/* Get IM1's Interrupt Events */
	ret = SMDIO_READ(phy, ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM1_IER);

	if (ret < 0) {
		LOG_CRIT("ERROR: IM1_IER read fails\n");
		goto END;
	}

	extin->im1 = (u16)ret;

	/* Get IM2's Interrupt Events */
	ret = SMDIO_READ(phy, ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM2_IER);

	if (ret < 0) {
		LOG_CRIT("ERROR: IM2_IER read fails\n");
		goto END;
	}

	extin->im2 = (u16)ret;

	ret = SMDIO_READ(phy, ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_EIU_EXIN_CONF);

	if (ret < 0) {
		LOG_CRIT("ERROR: EIU_EXIN_CONF read fails\n");
		goto END;
	}

	val = (u16)ret;

	/* Get the Edge detection of EXINT input pin */
	if (extin->id == EXT_INT_ID_0) {
		extin->ip_char = FIELD_GET(val, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN0);
	} else {
		extin->ip_char = FIELD_GET(val, ICU_PDI_REGISTERS_EIU_EXIN_CONF_EIN1);
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_topin_clr(struct gpy211_device *phy,
		     struct gpy211_extin *extin)
{
	int ret = -EINVAL;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || extin == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Validate Interrupt ID range */
	if (extin->id < EXT_INT_ID_0 || extin->id > EXT_INT_ID_1) {
		LOG_WARN("WARN: Invalid input (intId) - Interrupt ID\n");
		return -EINVAL;
	}

	/* Validate Interrupt Trigger range */
	if (!(extin->ip_char >= EXTIN_IR_DISABLE && extin->ip_char <= EXTIN_IR_LOW)) {
		LOG_WARN("WARN: Invalid input (intTrigger) - Interrupt Trigger\n");
		return -EINVAL;
	}

	/* Validate Interrupt Module-0 range */
	if (!(extin->im0 >= EXTIN_IM0_MIN && extin->im0 <= EXTIN_IM0_MAX)) {
		LOG_WARN("WARN: Invalid input (intMod0) - Interrupt Module-0\n");
		return -EINVAL;
	}

	/* Validate Interrupt Module-1 range */
	if (!(extin->im1 >= EXTIN_IM1_MIN && extin->im1 <= EXTIN_IM1_MAX)) {
		LOG_WARN("WARN: Invalid input (intMod1) - Interrupt Module-1\n");
		return -EINVAL;
	}

	/* Validate Interrupt Module -2 range */
	if (!(extin->im2 >= EXTIN_IM2_MIN && extin->im2 <= EXTIN_IM2_MAX)) {
		LOG_WARN("WARN: Invalid input (intMod2) - Interrupt Module-2\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	/* Clear Interrupt Event of IM0_ISR */
	ret = SMDIO_SET_MASK_BITS(phy,
				  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM0_ISR,
				  extin->im0,  extin->im0);

	if (ret < 0) {
		LOG_CRIT("ERROR: IM0_ISR write fails\n");
		goto END;
	}

	/* Clear Interrupt Event of IM1_ISR */
	ret = SMDIO_SET_MASK_BITS(phy,
				  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM1_ISR,
				  extin->im1,  extin->im1);

	if (ret < 0) {
		LOG_CRIT("ERROR: IM1_ISR write fails\n");
		goto END;
	}

	/* Clear Interrupt Event of IM2_ISR */
	ret = SMDIO_SET_MASK_BITS(phy,
				  ICU_PDI_REGISTERS_ICU_PDI_REGISTERS_IM2_ISR,
				  extin->im1,  extin->im1);

	if (ret < 0) {
		LOG_CRIT("ERROR: IM2_ISR write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#endif /* EN_SUPPORT_TOP_INT */

#ifndef __KERNEL__
static u32 div_u64_rem(u64 dividend, u32 divisor, u32 *remainder)
{
	u64 rem = dividend;
	u64 b = divisor;
	u64 res, d = 1;
	u32 high = rem >> 32;

	/* Reduce the thing a bit first */
	res = 0;

	if (high >= divisor) {
		high /= divisor;
		res = (u64) high << 32;
		rem -= (u64)(high * divisor) << 32;
	}

	while ((s64)b > 0 && b < rem) {
		b = b + b;
		d = d + d;
	}

	do {
		if (rem >= b) {
			rem -= b;
			res += d;
		}

		b >>= 1;
		d >>= 1;
	} while (d);

	if (remainder != NULL) {
		rem = res * divisor;
		*remainder = dividend - rem;
	}

	return res;
}
#endif

static int _gpy2xx_ptp_set_osctime(struct gpy211_device *phy,
				   time64_t ost_ctime)
{
	int ret = -EINVAL;
	u16 _ost_time;
	u32 _pm_base_addr;
	/* Populate Part of the 64-bit Tx OST Correction Timestamp */
	_ost_time = ((ost_ctime >> 0) & 0xFFFF);

	_pm_base_addr = phy->pm_base_addr;
	/* Write Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_0, _ost_time);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_0 write fails\n");
		return ret;
	}

	/* Populate Part of the 64-bit Tx OST Correction Timestamp */
	_ost_time = ((ost_ctime >> 16) & 0xFFFF);
	/* Write Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_1, _ost_time);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_1 write fails\n");
		return ret;
	}

	/* Populate Part of the 64-bit Tx OST Correction Timestamp */
	_ost_time = ((((long long)ost_ctime) >> 32) & 0xFFFF);
	/* Write Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_2, _ost_time);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_2 write fails\n");
		return ret;
	}

	/* Populate Part of the 64-bit Tx OST Correction Timestamp */
	_ost_time = ((((long long)ost_ctime) >> 48) & 0xFFFF);
	/* Write Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_3, _ost_time);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_3 write fails\n");
		return ret;
	}

	return 0;
}

static int _gpy2xx_ptp_get_osctime(struct gpy211_device *phy,
				   time64_t *ost_ctime)
{
	int ret = -EINVAL;
	u32 _pm_base_addr;

	/* Reset to zero */
	*ost_ctime = 0;
	_pm_base_addr = phy->pm_base_addr;

	/* Get Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_0);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_0 read fails\n");
		return ret;
	}

	/* Store Part of the 64-bit Tx OST Correction Timestamp */
	*ost_ctime = ret;

	/* Get Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_1);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_1 read fails\n");
		return ret;
	}

	/* Store Part of the 64-bit Tx OST Correction Timestamp */
	*ost_ctime |= ((long long)ret << 16);

	/* Get Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_2);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_2 read fails\n");
		return ret;
	}

	/* Store Part of the 64-bit Tx OST Correction Timestamp */
	*ost_ctime |= ((long long)ret << 32);

	/* Get Part of the 64-bit Tx OST Correction Timestamp */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_TX_OST_CFG_3);

	if (ret < 0) {
		LOG_CRIT("ERROR: OST_CFG_3 read fails\n");
		return ret;
	}

	/* Store Part of the 64-bit Tx OST Correction Timestamp */
	*ost_ctime |= ((long long)ret << 48);

	return 0;
}

static int _gpy2xx_ptp_set_ssecinc(struct gpy211_device *phy)
{
	int ret = -EINVAL;
	u8 _sub_sec, _sub_nsec;
	u64 _rem_nsec;
	struct gpy211_tsc_low _tsc_low;
	u32 _gmacf_base_addr;
	u32 _update_freq_hz;

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Get Timestamp Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L read fails\n");
		return ret;
	}

	_tsc_low.raw_ts_ctrl_low = ret;
	_update_freq_hz = (SEC_TO_NANOSEC(1) / 4);

	if (_tsc_low.ts_updt) {
		_sub_sec = SEC_TO_NANOSEC(1) / _update_freq_hz;
		_rem_nsec = SEC_TO_NANOSEC(1) % _update_freq_hz;
		_rem_nsec = _rem_nsec * 0x64;
		_sub_nsec = _rem_nsec / _update_freq_hz;
	} else if (0 != phy->ptp_clock) {
		_sub_sec = SEC_TO_NANOSEC(1) / phy->ptp_clock;
		_rem_nsec = SEC_TO_NANOSEC(1) % phy->ptp_clock;
		_rem_nsec = _rem_nsec * 0x64;
		_sub_nsec = _rem_nsec / phy->ptp_clock;
	} else {
		LOG_CRIT("ERROR: Neither PTP clock nor TS update bit is set\n");
		return -1;
	}

	/* Write Sub-second Increment Value */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SUB_SECOND_INCREMENT_H, _sub_sec);

	if (ret < 0) {
		LOG_CRIT("ERROR: SUB_SECOND_INCREMENT_H write fails\n");
		return ret;
	}

	/* The sub-nanosecond increment value, represented in nanoseconds multiplied
	 * by 2 pow 8. When user passes 5.3ns, then pass 5 as sub_sec, 3 as sub_nsec.
	 */
	_sub_nsec = (_sub_nsec * 256) / 100;
	/* Write Sub-nonosecond Increment Value */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SUB_SECOND_INCREMENT_L, (_sub_nsec << 8));

	if (ret < 0) {
		LOG_CRIT("ERROR: SUB_SECOND_INCREMENT_L write fails\n");
		return ret;
	}

	return 0;
}

static int _gpy2xx_ptp_init_systime(struct gpy211_device *phy, u32 sec,
				    u32 nsec)
{
	int ret = -EINVAL;
	u16 _sec_low, _sec_high, _nsec_low, _nsec_high;
	u32 _gmacf_base_addr;


	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (nsec > MAX_NSEC_IN_SEC) {
		LOG_WARN("WARN: Invalid nano-sec input\n");
		return -EINVAL;
	}

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Make sure 'TSINIT' is in reset state before init'ing SysTime */
	ret = __is_rw_done(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			   GMACF_MAC_TIMESTAMP_CONTROL_L_TSINIT_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _is_rw_done fails\n");
		return ret;
	}

	/* Write low-part of 'System Time Second' */
	_sec_low = sec & GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_TSS_MASK;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L, _sec_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_SECONDS_UPDATE_L write fails\n");
		return ret;
	}

	/* Write high-part of 'System Time Second' */
	_sec_high = sec >> 16;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H, _sec_high);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_SECONDS_UPDATE_H write fails\n");
		return ret;
	}

	/* Write low-part of 'System Time Nanoseconds' */
	_nsec_low = nsec & GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_TSSS_MASK;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L, _nsec_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_NANOSECONDS_UPDATE_L write fails\n");
		return ret;
	}

	/* Write high-part of 'System Time Nanoseconds' */
	_nsec_high = nsec >> 16;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H, _nsec_high);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_NANOSECONDS_UPDATE_H write fails\n");
		return ret;
	}

	/* Set 'TSINIT' after init'ing SysTime */
	ret = SMDIO_SET_BIT(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			    GMACF_MAC_TIMESTAMP_CONTROL_L_TSINIT_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: TSINIT_POS set fails\n");
		return ret;
	}

	/* Wait for SysTime init to complete */
	ret = __is_rw_done(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			   GMACF_MAC_TIMESTAMP_CONTROL_L_TSINIT_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _is_rw_done fails\n");
		return ret;
	}

	return 0;
}

static int _gpy2xx_ptp_updt_systime(struct gpy211_device *phy,
				    u8 add_sub, u32 sec, u32 nsec)
{
	int ret = -EINVAL;
	u32 _sec_updt, _nsec_updt;
	u16 _sec_low, _sec_high, _nsec_low, _nsec_high;
	u32 _gmacf_base_addr;

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (nsec > MAX_NSEC_IN_SEC) {
		LOG_WARN("WARN: Invalid nano-sec input\n");
		return -EINVAL;
	}

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Make sure 'TSUPDT' is in reset state before updating SysTime */
	ret = __is_rw_done(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			   GMACF_MAC_TIMESTAMP_CONTROL_L_TSUPDT_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _is_rw_done fails\n");
		return ret;
	}

	/* When ADDSUB is set, then these fields 'TSS, TSSS' must be
	 * programmed with the complement of these update values as below.
	 */
	if (add_sub) {
		/* If the 'TSS' update value needs to be subtracted with SysTime,
		 * then TSS field should be programmed with 2 pow 32 - <value_in_sec>,
		 * represented in binary.
		 */
		_sec_updt = 0x100000000ull - sec;

		/* The 'TSSS' update value derivation logic as below */
		/* If the System Time Nanoseconds register has an accuracy of 1 ns,
		 * then the programmed TSSS value must be 10 pow 9 - <sub-second value>.
		 */
		_nsec_updt = (0x3B9ACA00 - nsec);
	} else {
		/* When ADDSUB is reset, this fields 'TSS, TSSS' must be
		 * programmed with the update values.
		 */
		_sec_updt = sec;
		_nsec_updt = nsec;
	}

	/* Write low-part of 'System Time Second' */
	_sec_low = _sec_updt & GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L_TSS_MASK;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_L, _sec_low);


	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_SECONDS_UPDATE_L write fails\n");
		return ret;
	}

	/* Write high-part of 'System Time Second' */
	_sec_high = _sec_updt >> 16;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_SECONDS_UPDATE_H, _sec_high);


	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_SECONDS_UPDATE_H write fails\n");
		return ret;
	}

	/* Write low-part of 'System Time Nanoseconds' */
	_nsec_low = _nsec_updt & GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L_TSSS_MASK;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_L, _nsec_low);


	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_NANOSECONDS_UPDATE_L write fails\n");
		return ret;
	}

	/* Write high-part of 'System Time Nanoseconds' */
	_nsec_high = _nsec_updt >> 16;
	FIELD_REPLACE(_nsec_high, add_sub, GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H_ADDSUB);
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_H, _nsec_high);


	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_NANOSECONDS_UPDATE_H write fails\n");
		return ret;
	}

	/* Set 'TSUPDT' after updating SysTime */
	ret = SMDIO_SET_BIT(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			    GMACF_MAC_TIMESTAMP_CONTROL_L_TSUPDT_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: TSUPDT_POS set fails\n");
		return ret;
	}

	/* Wait for SysTime update to complete */
	ret = __is_rw_done(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			   GMACF_MAC_TIMESTAMP_CONTROL_L_TSUPDT_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _is_rw_done fails\n");
		return ret;
	}

	return 0;
}

static int _gpy2xx_ptp_set_addend(struct gpy211_device *phy, u32 addend)
{
	int ret = -EINVAL;
	u16 _addend_low, _addend_high;
	struct gpy211_tsc_low _tsc_low;
	u32 _gmacf_base_addr;

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Get Timestamp Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L read fails\n");
		return ret;
	}

	_tsc_low.raw_ts_ctrl_low = ret;

	if ((1 != _tsc_low.foc_updt) || (!addend)) {
		LOG_CRIT("ERROR: NULL input: Either TIMESTAMP_CONTROL.TSCFUPDT or addend\n");
		return ret;
	}

	/* Make sure 'TSADDREG' is in reset state before updating Addend reg */
	ret = __is_rw_done(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			   GMACF_MAC_TIMESTAMP_CONTROL_L_TSADDREG_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _is_rw_done fails\n");
		return ret;
	}

	/* Write low-part of 'Addend' */
	_addend_low = addend & GMACF_MAC_TIMESTAMP_ADDEND_L_TSAR_MASK;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_ADDEND_L, _addend_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_ADDEND_L write fails\n");
		return ret;
	}

	/* Write high-part of 'Addend' */
	_addend_high = addend >> 16;
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_ADDEND_H, _addend_high);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_ADDEND_H write fails\n");
		return ret;
	}

	/* Set 'TSADDREG' to tell device write Addend */
	ret = SMDIO_SET_BIT(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			    GMACF_MAC_TIMESTAMP_CONTROL_L_TSADDREG_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: TSUPDT_POS set fails\n");
		return ret;
	}

	/* Wait for Addend update to complete */
	ret = __is_rw_done(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L,
			   GMACF_MAC_TIMESTAMP_CONTROL_L_TSADDREG_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _is_rw_done fails\n");
		return ret;
	}

	return 0;
}

int gpy2xx_ptp_enable(struct gpy211_device *phy,
		      struct gpy211_ptp_ctrl *ptp_cfg)
{
	int ret = -EINVAL, ret2 = -EINVAL;
	struct gpy211_pmts_cfg _ptp_cfg;
	struct gpy211_tsc_low _tsc_low;
	struct bm_cfg _bm_cfg;
	struct gpy2xx_ts_ctrl _ts_cfg;
	u32 _gmacf_base_addr, _gmacl_base_addr;
	u32 _pm_base_addr, _offset;
	u32 _update_freq_hz;
	u64 temp = 0, _def_addend;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ptp_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Is 1-step TS enabled */
	if (ptp_cfg->ts_ostc_en) {
		/* Validate PTP Transport Protocol ID range */
		if (!(ptp_cfg->tx_ptp_tpt >= PTP_TRANSPORT_OVER_ETH &&
		      ptp_cfg->tx_ptp_tpt <= PTP_TRANSPORT_OVER_IPv6)) {
			LOG_WARN("WARN: Invalid input (ptpTxProtocol) - Transport Protocol ID\n");
			return -EINVAL;
		}
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;
	_gmacl_base_addr = phy->gmacl_base_addr;
	_pm_base_addr = phy->pm_base_addr;

	/* Enable PTP Packet detection */
	ret = SMDIO_SET_BIT(phy, _pm_base_addr + PM_PDI_GMAC_CFG, PM_PDI_GMAC_CFG_GMAC_PTP_DET_POS);
	ret2 = SMDIO_SET_BIT(phy, _pm_base_addr + PM_PDI_GMACL_CFG, PM_PDI_GMACL_CFG_GMACL_PTP_DET_POS);

	if (ret < 0 || ret2 < 0) {
		LOG_CRIT("ERROR: GMAC_CFG or GMACL_CFG modify fails\n");

		if (ret2 < 0)
			ret = ret2;

		goto END;
	}

	/* Enable Timestamp Interrupt */
	ret = SMDIO_SET_BIT(phy, _gmacf_base_addr + GMACF_MAC_INTERRUPT_ENABLE_L, GMACF_MAC_INTERRUPT_ENABLE_L_TSIE_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_CFG or GMACL_CFG modify fails\n");
		goto END;
	}

	_ptp_cfg.ts_refclk_rst = 1;
	_ptp_cfg.tsl_refclk_rst = 1;
	_ptp_cfg.tx_fifo_en = 1;
	_ptp_cfg.rx_fifo_en = 1;
	_ptp_cfg.tx_fifo_rst = 1;
	_ptp_cfg.rx_fifo_rst = 1;

	_ptp_cfg.ts_ostc_en = ptp_cfg->ts_ostc_en;
	_ptp_cfg.tx_ts_phy = ptp_cfg->tx_ts_phy;
	_ptp_cfg.rx_ts_phy = ptp_cfg->rx_ts_phy;

	/* Set Timestamp config */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TS_CFG, _ptp_cfg.raw_ts_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_CFG write fails\n");
		goto END;
	}

	_ptp_cfg.tx_ptp_off = ptp_cfg->tx_ptp_off;
	_ptp_cfg.tx_ptp_tpt = ptp_cfg->tx_ptp_tpt;
	/* Set PTP config */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_GMAC_PTP_CFG, _ptp_cfg.raw_ptp_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_PTP_CFG write fails\n");
		goto END;
	}

	if (ptp_cfg->ts_ostc_en == 1) {
		ret = _gpy2xx_ptp_set_osctime(phy, ptp_cfg->tx_ost_corr);

		if (ret < 0) {
			LOG_CRIT("ERROR: api _gpy2xx_ptp_set_osctime fails\n");
			goto END;
		}
	}

	_tsc_low.raw_ts_ctrl_low = 0;
	_tsc_low.ts_en = 1;
	_tsc_low.foc_updt = 1;
	_tsc_low.dob_ro_ctrl = 1;
	_tsc_low.ts_ver2_en = 1;
	_tsc_low.ts_eth_en = 1;
	_tsc_low.ts_ipv6_en = 1;
	_tsc_low.ts_ipv4_en = 1;

	/* Set Timestamp Control low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L, _tsc_low.raw_ts_ctrl_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: Full MAC_TIMESTAMP_CONTROL_L write fails\n");
		goto END;
	}

	if (phy->id.family == ID_P34X) {
		_offset = XGMAC_MAC_TIMESTAMP_CONTROL_L;
	} else {
		_offset = GMACL_MAC_TIMESTAMP_CONTROL_L;
	}

	ret = SMDIO_WRITE(phy, _gmacl_base_addr + _offset, 0x3C01);

	if (ret < 0) {
		LOG_CRIT("ERROR: Xgmac/Lite MAC_TIMESTAMP_CONTROL_L write fails\n");
		goto END;
	}

	ret = _gpy2xx_ptp_set_ssecinc(phy);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_set_ssecinc fails\n");
		goto END;
	}

	_update_freq_hz = (SEC_TO_NANOSEC(1) / 4);
	temp = (u64)((_update_freq_hz * 1000000ULL) << 32);
	_def_addend = div_u64_rem(temp, phy->ptp_clock, NULL);

	ret = _gpy2xx_ptp_set_addend(phy, _def_addend);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_set_addend fails\n");
		goto END;
	}

	_ts_cfg.snap_type = 1;
	_ts_cfg.ts_evtmsg_en = _ts_cfg.ts_master_en = 0;
	_ts_cfg.gpc_sel = 2;
	ret = gpy2xx_ptp_set_tsctrl(phy, &_ts_cfg);

	if (ret < 0) {
		printf("\nERROR: TS control set failed.\n");
		return -1;
	}

	ret = gpy2xx_gmacx_bm_get(phy, &_bm_cfg);

	if (ret < 0) {
		printf("\nERROR: PM's Buffer info get failed.\n");
		return -1;
	}

	_bm_cfg.sb0_pkt_thresh = _bm_cfg.sb1_pkt_thresh = 0x100;

	ret = gpy2xx_gmacx_bm_cfg(phy, &_bm_cfg);

	if (ret < 0) {
		printf("\nERROR: PM's Buffer info set failed.\n");
		return -1;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_disable(struct gpy211_device *phy)
{
	int ret = -EINVAL, ret2 = -EINVAL;
	u16 _ptp_cfg, _ts_cfg;
	struct gpy211_tsc_low _tsc_low;
	u32 _gmacf_base_addr, _gmacl_base_addr;
	u32 _pm_base_addr, _offset;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;
	_gmacl_base_addr = phy->gmacl_base_addr;
	_pm_base_addr = phy->pm_base_addr;

	/* Disable PTP Packet detection */
	ret = SMDIO_CLR_BIT(phy, _pm_base_addr + PM_PDI_GMAC_CFG, PM_PDI_GMAC_CFG_GMAC_PTP_DET_POS);
	ret2 = SMDIO_CLR_BIT(phy, _pm_base_addr + PM_PDI_GMACL_CFG, PM_PDI_GMACL_CFG_GMACL_PTP_DET_POS);

	if (ret < 0 || ret2 < 0) {
		LOG_CRIT("ERROR: GMAC_CFG or GMACL_CFG modify fails\n");

		if (ret2 < 0)
			ret = ret2;

		goto END;
	}

	/* Disable Timestamp Interrupt */
	ret = SMDIO_CLR_BIT(phy, _gmacf_base_addr + GMACF_MAC_INTERRUPT_ENABLE_L, GMACF_MAC_INTERRUPT_ENABLE_L_TSIE_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_CFG or GMACL_CFG modify fails\n");
		goto END;
	}

	_ptp_cfg = 0;
	/* Clear PTP config */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_GMAC_PTP_CFG, _ptp_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_PTP_CFG write fails\n");
		goto END;
	}

	ret = _gpy2xx_ptp_set_osctime(phy, 0x0);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_set_osctime fails\n");
		goto END;
	}

	_ts_cfg = 0;
	/* Clear Timestamp config */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TS_CFG, _ts_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_CFG write fails\n");
		goto END;
	}

	_tsc_low.raw_ts_ctrl_low = 0;
	_tsc_low.ts_ipv4_en = 1;

	/* Set Timestamp Control low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L, _tsc_low.raw_ts_ctrl_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L write fails\n");
		goto END;
	}

	if (phy->id.family == ID_P34X) {
		_offset = XGMAC_MAC_TIMESTAMP_CONTROL_L;
	} else {
		_offset = GMACL_MAC_TIMESTAMP_CONTROL_L;
	}

	ret = SMDIO_WRITE(phy, _gmacl_base_addr + _offset, 0x0);

	if (ret < 0) {
		LOG_CRIT("ERROR: Xgmac/Lite MAC_TIMESTAMP_CONTROL_L write fails\n");
		goto END;
	}

	/* Set Timestamp Control high word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_H, 0x0);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_H write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}


int gpy2xx_ptp_set_tsctrl(struct gpy211_device *phy,
			  struct gpy2xx_ts_ctrl *ts_cfg)
{
	int ret = -EINVAL;
	struct gpy211_tsc_low _ts_ctrl_low;
	struct gpy211_tsc_high _ts_ctrl_high;
	u32 _gmacf_base_addr, _gpc_sel, _alt0_sel, _alt1_sel;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ts_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	_ts_ctrl_low.raw_ts_ctrl_low = 0;
	_ts_ctrl_high.raw_ts_ctrl_high = 0;

	/* Get Timestamp Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L read fails\n");
		goto END;
	}

	_ts_ctrl_low.raw_ts_ctrl_low = ret;
	_ts_ctrl_low.ts_evtmsg_en = ts_cfg->ts_evtmsg_en;
	_ts_ctrl_low.ts_master_en = ts_cfg->ts_master_en;

	/* Set Timestamp Control low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L, _ts_ctrl_low.raw_ts_ctrl_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L write fails\n");
		goto END;
	}

	/* Get Timestamp Control high word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_H write fails\n");
		goto END;
	}

	_ts_ctrl_high.raw_ts_ctrl_high = ret;
	_ts_ctrl_high.snap_type = ts_cfg->snap_type;
	_ts_ctrl_high.ts_stat_mode = 1;

	/* Set Timestamp Control high word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_H, _ts_ctrl_high.raw_ts_ctrl_high);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_H write fails\n");
		goto END;
	}

	ret = PHY_MBOX_HWRD(phy, CGU_PDI_MODULE_BASE + CGU_PDI_SYNCE_CONF, &_gpc_sel);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPC1_OUT_CONF read fails\n");
		goto END;
	}

	_gpc_sel |= ts_cfg->gpc_sel << 4;

	ret = PHY_MBOX_HWWR(phy, CGU_PDI_MODULE_BASE + CGU_PDI_SYNCE_CONF, _gpc_sel);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPC1_OUT_CONF write fails\n");
		goto END;
	}

	ret = PHY_MBOX_HWRD(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL0, &_alt0_sel);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL0 read fails\n");
		goto END;
	}

	_alt0_sel |= 1 << 4;

	ret = PHY_MBOX_HWWR(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL0, _alt0_sel);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL0 write fails\n");
		goto END;
	}

	ret = PHY_MBOX_HWRD(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL1, &_alt1_sel);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL1 read fails\n");
		goto END;
	}

	_alt1_sel |= 1 << 11;

	ret = PHY_MBOX_HWWR(phy, GPIO_PDI_REGISTERS_MODULE_BASE + GPIO_PDI_REGISTERS_GPIO_ALTSEL1, _alt1_sel);

	if (ret < 0) {
		LOG_CRIT("ERROR: GPIO_ALTSEL1 write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_ptp_get_tsctrl(struct gpy211_device *phy,
				  struct gpy2xx_ts_ctrl *ts_cfg)
{
	int ret = -EINVAL;
	struct gpy211_tsc_low _ts_ctrl_low;
	struct gpy211_tsc_high _ts_ctrl_high;
	u32 _gmacf_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ts_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	_ts_ctrl_low.raw_ts_ctrl_low = 0;
	_ts_ctrl_high.raw_ts_ctrl_high = 0;

	/* Get Timestamp Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L read fails\n");
		goto END;
	}

	_ts_ctrl_low.raw_ts_ctrl_low = ret;
	ts_cfg->ts_evtmsg_en = _ts_ctrl_low.ts_evtmsg_en;
	ts_cfg->ts_master_en = _ts_ctrl_low.ts_master_en;

	/* Get Timestamp Control high word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_H write fails\n");
		goto END;
	}

	_ts_ctrl_high.raw_ts_ctrl_high = ret;
	ts_cfg->snap_type = _ts_ctrl_high.snap_type;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_set_ppsctrl(struct gpy211_device *phy,
			   struct gpy2xx_pps_ctrl *pps_ctrl)
{
	int ret = -EINVAL;
	u32 _ttime_nsec, _sub_sec_inc, _num_of_units;
	u16 _pps_ctrl_low;
	u16 _nsec_tt_low, _nsec_tt_hi, _sec_tt_low, _sec_tt_hi;
	u16 _units_int_low, _units_int_hi, _units_wid_low, _units_wid_hi;
	struct gpy211_tsc_low _tsc_low;
	u32 _gmacf_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pps_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	if ((pps_ctrl->nsec_tgttime > MAX_NSEC_IN_SEC) ||
	    (pps_ctrl->pps0_interal > MAX_NSEC_IN_SEC) ||
	    (pps_ctrl->pps0_width > MAX_NSEC_IN_SEC)) {
		LOG_WARN("WARN: Invalid nano-sec input\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	_pps_ctrl_low = pps_ctrl->ppsctrl_low.raw_pps_ctrl_low;
	/* Set PPS Control low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS_CONTROL_L, _pps_ctrl_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_PPS_CONTROL_L write fails\n");
		goto END;
	}

	/* Check if 'PPS0 Target Time Register' setting is busy */
	ret = __is_rw_done(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H,
			   GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H_TRGTBUSY0_POS);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _is_rw_done fails\n");
		return ret;
	}

	_sec_tt_low = pps_ctrl->sec_tgttime & GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L_TSTRH0_MASK;
	/* Set PPS Target Time Seconds - low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L, _sec_tt_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_SECONDS_L write fails\n");
		goto END;
	}

	_sec_tt_hi = pps_ctrl->sec_tgttime >> 16;
	/* Set PPS Target Time Seconds - high word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H, _sec_tt_hi);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_SECONDS_H write fails\n");
		goto END;
	}

	/* Get Timestamp Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L read fails\n");
		return ret;
	}

	_tsc_low.raw_ts_ctrl_low = ret;

	/* If the System Time Nanoseconds register has an accuracy of 1 ns */
	/* So no change */
	_ttime_nsec = pps_ctrl->nsec_tgttime;

	_nsec_tt_low = _ttime_nsec & GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L_TTSL0_MASK;
	/* Set PPS Target Time Nano-Seconds - low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L, _nsec_tt_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_NANOSECONDS_L write fails\n");
		goto END;
	}

	_nsec_tt_hi = _ttime_nsec >> 16;
	/* Set PPS Target Time Nano-Seconds - high word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H, _nsec_tt_hi);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_NANOSECONDS_H write fails\n");
		goto END;
	}

	/* The interval is stored in terms of number of units of sub-second
	 * increment value. You need to program one value less than the required
	 * interval.
	 */

	/* Get Sub-second Increment Value */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_SUB_SECOND_INCREMENT_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: SUB_SECOND_INCREMENT_H write fails\n");
		return ret;
	}

	_sub_sec_inc = FIELD_GET(ret, GMACF_MAC_SUB_SECOND_INCREMENT_H_SSINC);

	if (1 == _tsc_low.dob_ro_ctrl) {
		/* If the System Time Nanoseconds register has an accuracy of 1 ns */
		/* So no change */
	} else {
		/* If the System Time Nanoseconds register has a resolution of ~0.465 ns */
		_sub_sec_inc = ((465 * _sub_sec_inc) / 1000);
	}

	if (_sub_sec_inc == 0 || pps_ctrl->pps0_interal < _sub_sec_inc) {
		LOG_CRIT("ERROR: pps_ctrl->pps0_interal (%u) / _sub_sec_inc (%u) < 1\n",
			 pps_ctrl->pps0_interal, _sub_sec_inc);
		ret = -EINVAL;
		goto END;
	}

	_num_of_units = (pps_ctrl->pps0_interal / _sub_sec_inc) - 1;

	_units_int_low = _num_of_units & GMACF_MAC_PPS0_INTERVAL_L_PPSINT0_MASK;
	/* Set PPS Interval - low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_INTERVAL_L, _units_int_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_INTERVAL_L write fails\n");
		goto END;
	}

	_units_int_hi = _num_of_units >> 16;
	/* Set PPS Interval - high word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_INTERVAL_H, _units_int_hi);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_INTERVAL_H write fails\n");
		goto END;
	}

	_num_of_units = (pps_ctrl->pps0_width / _sub_sec_inc) - 1;

	_units_wid_low = _num_of_units & GMACF_MAC_PPS0_INTERVAL_L_PPSINT0_MASK;
	/* Set PPS Width - low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_WIDTH_L, _units_wid_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_WIDTH_L write fails\n");
		goto END;
	}

	_units_wid_hi = _num_of_units >> 16;
	/* Set PPS Interval - high word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PPS0_WIDTH_H, _units_wid_hi);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_WIDTH_H write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_ptp_get_ppsctrl(struct gpy211_device *phy,
				   struct gpy2xx_pps_ctrl *pps_ctrl)
{
	int ret = -EINVAL;
	u32 _ttime_nsec, _sub_sec_inc, _num_of_units;
	u16 _nsec_tt_low, _nsec_tt_hi, _sec_tt_low, _sec_tt_hi;
	u16 _units_int_low, _units_int_hi, _units_wid_low, _units_wid_hi;
	struct gpy211_tsc_low _tsc_low;
	u32 _gmacf_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pps_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Get PPS Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_PPS_CONTROL_L write fails\n");
		goto END;
	}

	pps_ctrl->ppsctrl_low.raw_pps_ctrl_low = ret;

	/* Get PPS Target Time Seconds - low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_SECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_SECONDS_L write fails\n");
		goto END;
	}

	_sec_tt_low = ret;

	/* Get PPS Target Time Seconds - high word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_SECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_SECONDS_H write fails\n");
		goto END;
	}

	_sec_tt_hi = ret;
	pps_ctrl->sec_tgttime = (_sec_tt_hi << 16) | _sec_tt_low;

	/* Get PPS Target Time Nano-Seconds - low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_NANOSECONDS_L write fails\n");
		goto END;
	}

	_nsec_tt_low = ret;

	/* Get PPS Target Time Nano-Seconds - high word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_TARGET_TIME_NANOSECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_TARGET_TIME_NANOSECONDS_H write fails\n");
		goto END;
	}

	_nsec_tt_hi = ret;
	_ttime_nsec = (_nsec_tt_hi << 16) | _nsec_tt_low;

	/* Get Timestamp Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_CONTROL_L read fails\n");
		return ret;
	}

	_tsc_low.raw_ts_ctrl_low = ret;

	/* If the System Time Nanoseconds register has an accuracy of 1 ns */
	pps_ctrl->nsec_tgttime = _ttime_nsec;

	/* Get PPS Interval - low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_INTERVAL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_INTERVAL_L write fails\n");
		goto END;
	}

	_units_int_low = ret;

	/* Get PPS Interval - high word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_INTERVAL_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_INTERVAL_H write fails\n");
		goto END;
	}

	_units_int_hi = ret;
	_num_of_units = (_units_int_hi << 16) | _units_int_low;

	/* The interval is stored in terms of number of units of sub-second
	 * increment value. You need to program one value less than the required
	 * interval.
	 */

	/* Get Sub-second Increment Value */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_SUB_SECOND_INCREMENT_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: SUB_SECOND_INCREMENT_H write fails\n");
		return ret;
	}

	_sub_sec_inc = FIELD_GET(ret, GMACF_MAC_SUB_SECOND_INCREMENT_H_SSINC);

	if (1 == _tsc_low.dob_ro_ctrl) {
		/* If the System Time Nanoseconds register has an accuracy of 1 ns */
		/* So no change */
	} else {
		/* If the System Time Nanoseconds register has a resolution of ~0.465 ns */
		_sub_sec_inc = ((465 * _sub_sec_inc) / 1000);
	}

	if (_num_of_units)
		pps_ctrl->pps0_interal = (_num_of_units + 1) * _sub_sec_inc;
	else
		pps_ctrl->pps0_interal = 0;

	/* Get PPS Width - low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_WIDTH_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_WIDTH_L write fails\n");
		goto END;
	}

	_units_wid_low = ret;

	/* Get PPS Interval - high word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PPS0_WIDTH_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: PPS0_WIDTH_H write fails\n");
		goto END;
	}

	_units_wid_hi = ret;
	_num_of_units = (_units_wid_hi << 16) | _units_wid_low;

	if (_num_of_units)
		pps_ctrl->pps0_width = (_num_of_units + 1) * _sub_sec_inc;
	else
		pps_ctrl->pps0_width = 0;

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_set_ptoctrl(struct gpy211_device *phy,
			   struct gpy2xx_pto_ctrl *pto_ctrl)
{
	int ret = -EINVAL;
	u16 i, _sport_id[PTP_SPORT_ID_LEN_HWORD];
	u32 _gmacf_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pto_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	if ((pto_ctrl->logmsg_lvl.log_sync_interval < PTP_LOG_SYNC_INTVL_MIN) ||
	    (pto_ctrl->logmsg_lvl.log_sync_interval > PTP_LOG_SYNC_INTVL_MAX) ||
	    (pto_ctrl->logmsg_lvl.dr_to_sync_ratio > PTP_DR_TO_SYNC_RATIO_MAX) ||
	    (pto_ctrl->logmsg_lvl.log_min_pdr_interval < PTP_LOG_MIN_PDR_INTVL_MIN) ||
	    (pto_ctrl->logmsg_lvl.log_min_pdr_interval > PTP_LOG_MIN_PDR_INTVL_MAX)) {
		LOG_WARN("WARN: Invalid inpult range\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Set PTO Control low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_PTO_CONTROL_L, pto_ctrl->ptoctrl_low.raw_pto_ctrl_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_PTO_CONTROL_L write fails\n");
		goto END;
	}

#if defined(SAFE_C_LIB) && SAFE_C_LIB
	memcpy_s((u8 *)_sport_id, PTP_SPORT_ID_LEN_BYTE, pto_ctrl->sport_id, PTP_SPORT_ID_LEN_BYTE);
#else
	memcpy((u8 *)_sport_id, pto_ctrl->sport_id, PTP_SPORT_ID_LEN_BYTE);
#endif

	for (i = 0; i < PTP_SPORT_ID_LEN_HWORD; i++) {
		/* Set Source Port Identity 0 */
		ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_SOURCE_PORT_IDENTITY0_L + (i * 4), _sport_id[i]);

		if (ret < 0) {
			LOG_CRIT("ERROR: MAC_SOURCE_PORT_IDENTITYx_L write fails for ieration %d\n", i);
			goto END;
		}
	}

	/* Negative value must be represented in 2's-complement form */
	if (pto_ctrl->logmsg_lvl.log_sync_interval < 0) {
		pto_ctrl->logmsg_lvl.log_sync_interval = (~(-pto_ctrl->logmsg_lvl.log_sync_interval)) + 1;
	}

	/* Set Log Message Interval - low word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_LOG_MESSAGE_INTERVAL_L, pto_ctrl->logmsg_lvl.raw_logm_lvl_low);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_LOG_MESSAGE_INTERVAL_L write fails\n");
		goto END;
	}

	/* Negative value must be represented in 2's-complement form */
	if (pto_ctrl->logmsg_lvl.log_min_pdr_interval < 0) {
		pto_ctrl->logmsg_lvl.log_min_pdr_interval = (~(-pto_ctrl->logmsg_lvl.log_min_pdr_interval)) + 1;
	}

	/* Set Log Message Interval - high word */
	ret = SMDIO_WRITE(phy, _gmacf_base_addr + GMACF_MAC_LOG_MESSAGE_INTERVAL_H, pto_ctrl->logmsg_lvl.raw_logm_lvl_hi);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_LOG_MESSAGE_INTERVAL_H write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

static int _gpy2xx_ptp_get_ptoctrl(struct gpy211_device *phy,
				   struct gpy2xx_pto_ctrl *pto_ctrl)
{
	int ret = -EINVAL;
	u16 i, _sport_id[PTP_SPORT_ID_LEN_HWORD];
	u32 _gmacf_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || pto_ctrl == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Set PTO Control low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_PTO_CONTROL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_PTO_CONTROL_L write fails\n");
		goto END;
	}

	pto_ctrl->ptoctrl_low.raw_pto_ctrl_low = ret;

	for (i = 0; i < PTP_SPORT_ID_LEN_HWORD; i++) {
		/* Set Source Port Identity 0 */
		ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_SOURCE_PORT_IDENTITY0_L + (i * 4));

		if (ret < 0) {
			LOG_CRIT("ERROR: MAC_SOURCE_PORT_IDENTITYx_L write fails for ieration %d\n", i);
			goto END;
		}

		_sport_id[i] = ret;
	}

#if defined(SAFE_C_LIB) && SAFE_C_LIB
	memcpy_s(pto_ctrl->sport_id, PTP_SPORT_ID_LEN_BYTE, (u8 *)_sport_id, PTP_SPORT_ID_LEN_BYTE);
#else
	memcpy(pto_ctrl->sport_id, (u8 *)_sport_id, PTP_SPORT_ID_LEN_BYTE);
#endif

	/* Set Log Message Interval - low word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_LOG_MESSAGE_INTERVAL_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_LOG_MESSAGE_INTERVAL_L write fails\n");
		goto END;
	}

	pto_ctrl->logmsg_lvl.raw_logm_lvl_low = ret;

	/* Negative value must be represented in 2's-complement form */
	if (pto_ctrl->logmsg_lvl.log_sync_interval < 0) {
		pto_ctrl->logmsg_lvl.log_sync_interval = (~(-pto_ctrl->logmsg_lvl.log_sync_interval)) + 1;
	}

	/* Set Log Message Interval - high word */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_LOG_MESSAGE_INTERVAL_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_LOG_MESSAGE_INTERVAL_H write fails\n");
		goto END;
	}

	pto_ctrl->logmsg_lvl.raw_logm_lvl_hi = ret;

	/* Negative value must be represented in 2's-complement form */
	if (pto_ctrl->logmsg_lvl.log_min_pdr_interval < 0) {
		pto_ctrl->logmsg_lvl.log_min_pdr_interval = (~(-pto_ctrl->logmsg_lvl.log_min_pdr_interval)) + 1;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_adjfreq(struct gpy211_device *phy, s32 ppb)
{
	int ret = -EINVAL;
	u64 adj, diff;
	u32 _update_freq_hz;
	u64 temp = 0, _def_addend;

	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	if (ppb >= SEC_TO_NANOSEC(1) || ppb <= NEG_SEC_TO_NANOSEC(1)) {
		LOG_CRIT("Error: ppb (%u) is not within +/- SEC_TO_NANOSEC(1)\n", ppb);
		return -EINVAL;
	}

	/* Validate input params */
	//None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_update_freq_hz = (SEC_TO_NANOSEC(1) / 4);
	temp = (u64)((_update_freq_hz * 1000000ULL) << 32);
	_def_addend = div_u64_rem(temp, phy->ptp_clock, NULL);

	/* Actual addend in integer arithmetic becomes
	 * addend = (def_addend * 1000000000) / (1000000000 - ppb)
	 */
	adj = (_def_addend * SEC_TO_NANOSEC(1));
	diff = (SEC_TO_NANOSEC(1) - ppb);

	_def_addend = div_u64_rem(adj, diff, NULL);

	ret = _gpy2xx_ptp_set_addend(phy, _def_addend);

	if (ret < 0) {
		LOG_CRIT("ERROR: api_ _gpy2xx_ptp_set_addend fails\n");
		goto END;
	}

END:

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_settime(struct gpy211_device *phy,       struct timespec64 *ts)
{
	int ret = -EINVAL;

	if (phy == NULL || ts == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	//None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	ret = _gpy2xx_ptp_init_systime(phy, ts->tv_sec, ts->tv_nsec);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_init_systime fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_adjtime(struct gpy211_device *phy, s64 delta)
{
	int ret = -EINVAL;
	u8 add_sub = 0; // 0 for add, 1 for subtract
	u32 sec, nsec;
	u32 quotient, remainder;

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	//None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	if (delta < 0) {
		add_sub = 1;
		delta = -delta;
	}

	if (delta > MAX_NANOSEC_IN_DAY) {
		LOG_WARN("WARN: Invalid input delta parameter)\n");
		return -EINVAL;
	}

	quotient = div_u64_rem(delta, SEC_TO_NANOSEC(1), &remainder);
	sec = quotient;
	nsec = remainder;

	ret = _gpy2xx_ptp_updt_systime(phy, add_sub, sec, nsec);

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_updt_systime fails\n");
		goto END;
	}

END:

	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_gettime(struct gpy211_device *phy, struct timespec64 *ts)
{
	time64_t _ref_ts;
	int ret = -EINVAL;
	u32 _gmacf_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ts == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Reset to zero */
	ts->tv_sec = 0;
	/* Get Seconds Part of the System Time */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_SECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_SECONDS_L read fails\n");
		goto END;
	}

	_ref_ts = (u16)ret;
	/* Store Part of the System Timestamp */
	ts->tv_sec = _ref_ts;

	/* Get Seconds Part of the System Time */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_SECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_SECONDS_H read fails\n");
		goto END;
	}

	_ref_ts = (u16)ret;
	/* Store Part of the System Timestamp */
	ts->tv_sec |= (_ref_ts << 16);

	/* Get NanoSeconds Part of System Timestamp */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_NANOSECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_NANOSECONDS_L read fails\n");
		goto END;
	}

	_ref_ts = (u16)ret;
	/* Store Part of the System Timestamp */
	ts->tv_nsec = _ref_ts;

	/* Get NanoSeconds Part of the System Timestamp */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: SYSTEM_TIME_NANOSECONDS_H read fails\n");
		goto END;
	}

	_ref_ts = (u16)ret & GMACF_MAC_SYSTEM_TIME_NANOSECONDS_H_TSSS_MASK;
	/* Store Part of the Ref Timestamp */
	ts->tv_nsec |= (_ref_ts << 16);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_fifostat(struct gpy211_device *phy,
			struct gpy211_ts_fifo_stat *fifo_status)
{
	u16 _fifo_status;
	int ret = -EINVAL;
	u32 _pm_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || fifo_status == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);
	_pm_base_addr = phy->pm_base_addr;

	/* Read FIFO statu */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_TS_FIFO_STAT);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_FIFO_STAT read fails\n");
		goto END;
	}

	_fifo_status = ret;
	fifo_status->raw_fifo_stat = _fifo_status;

	/* Clear TS status by writing 1 to clear */
	_fifo_status = 0;
	FIELD_REPLACE(_fifo_status, 1, PM_PDI_TS_FIFO_STAT_RX_UDF);
	FIELD_REPLACE(_fifo_status, 1, PM_PDI_TS_FIFO_STAT_RX_OVF);
	FIELD_REPLACE(_fifo_status, 1, PM_PDI_TS_FIFO_STAT_TX_UDF);
	FIELD_REPLACE(_fifo_status, 1, PM_PDI_TS_FIFO_STAT_TX_OVF);
	/* Write 1 to clear */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TS_FIFO_STAT, _fifo_status);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_FIFO_STAT write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_resetfifo(struct gpy211_device *phy)
{
	int ret = -EINVAL;
	struct gpy211_pmts_cfg _ptp_cfg;
	u32 _pm_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_pm_base_addr = phy->pm_base_addr;

	/* Read PTP configuration */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_TS_CFG);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_CFG read fails\n");
		goto END;
	}

	_ptp_cfg.raw_ts_cfg = ret;
	_ptp_cfg.tx_fifo_rst = 0;
	_ptp_cfg.rx_fifo_rst = 0;

	/* Reset the TS FIFO status */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TS_CFG, _ptp_cfg.raw_ts_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_CFG write fails\n");
		goto END;
	}

	_ptp_cfg.tx_fifo_rst = 1;
	_ptp_cfg.rx_fifo_rst = 1;

	/* Release the TS FIFO status */
	ret = SMDIO_WRITE(phy, _pm_base_addr + PM_PDI_TS_CFG, _ptp_cfg.raw_ts_cfg);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_CFG write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

#if defined(EN_GMAC_DEBUG_ACCESS) && EN_GMAC_DEBUG_ACCESS
int gpy2xx_ptp_txtsstat(struct gpy211_device *phy,
			struct gpy211_ts_stat *ts_status)
{
	int ret = -EINVAL;
	u32 _gmacf_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ts_status == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Read MAC_TIMESTAMP_STATUS_L */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_STATUS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_STATUS_L read fails\n");
		goto END;
	}

	ts_status->tss_low.raw_ts_stat_low = ret;

	/* Read MAC_TIMESTAMP_STATUS_H */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_STATUS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: MAC_TIMESTAMP_STATUS_H read fails\n");
		goto END;
	}

	ts_status->tss_high.raw_ts_stat_hi = ret;

	/* Read TX_TIMESTAMP_STATUS_NANOSECONDS_L */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_TIMESTAMP_STATUS_NANOSECONDS_L read fails\n");
		goto END;
	}

	ts_status->txts_stat.txtss_nsec = ret;

	/* Read TX_TIMESTAMP_STATUS_NANOSECONDS_H */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_TIMESTAMP_STATUS_NANOSECONDS_H read fails\n");
		goto END;
	}

	ts_status->txts_stat.txtss_mis = FIELD_GET(ret, GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H_TXTSSMIS);
	ts_status->txts_stat.txtss_nsec |= (FIELD_GET(ret, GMACF_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_H_TXTSSLO) << 16);

	/* Read TX_TIMESTAMP_STATUS_SECONDS_L */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_TIMESTAMP_STATUS_SECONDS_L read fails\n");
		goto END;
	}

	ts_status->txts_stat.txtss_sec = ret;

	/* Read TX_TIMESTAMP_STATUS_SECONDS_H */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_TX_TIMESTAMP_STATUS_SECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: TX_TIMESTAMP_STATUS_SECONDS_H read fails\n");
		goto END;
	}

	ts_status->txts_stat.txtss_sec |= (ret << 16);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
#endif

int gpy2xx_ptp_getrxts(struct gpy211_device *phy,
		       struct gpy211_rx_ts *rx_ts)
{
	s32 _rx_ts, _rx_crc;
	u32 _ts_sec, _ts_nsec;
	time64_t _sec_to_nsec;
	u32 _pm_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || rx_ts == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_pm_base_addr = phy->pm_base_addr;

	/* Reset to zero */
	rx_ts->rx_ts_stat = 0;
	/* Get Part of the 64-bit Rx Timestamp */
	_rx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_RX_TS_STAT_0);

	if (_rx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_RX_TS_STAT_0 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Rx Timestamp */
	_ts_nsec = (u16)_rx_ts;

	/* Get Part of the 64-bit Rx Timestamp */
	_rx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_RX_TS_STAT_1);

	if (_rx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_RX_TS_STAT_1 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Rx Timestamp */
	_ts_nsec |= (_rx_ts << 16);

	//printf("\nNano-sec %x", _ts_nsec);
	/* Get Part of the 64-bit Rx Timestamp */
	_rx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_RX_TS_STAT_2);

	if (_rx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_RX_TS_STAT_2 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Rx Timestamp */
	_ts_sec = (u16)_rx_ts;

	/* Get Part of the 64-bit Rx Timestamp */
	_rx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_RX_TS_STAT_3);

	if (_rx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_RX_TS_STAT_3 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Rx Timestamp */
	_ts_sec |= ((u16)_rx_ts << 16);
	_sec_to_nsec = SEC_TO_NANOSEC(_ts_sec);
	rx_ts->rx_ts_stat = _sec_to_nsec + _ts_nsec;
	//printf("\nSec %x, Sec-to-Nsec %I64x, Total Nsec %I64x", _ts_sec, _sec_to_nsec, rx_ts->rx_ts_stat);

	/* Reset to zero */
	rx_ts->rx_crc_stat = 0;
	/* Get Part of the 32-bit Tx Frame CRC */
	_rx_crc = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_RX_CRC_STAT_0);

	if (_rx_crc < 0) {
		LOG_CRIT("ERROR: GMAC_TX_CRC_STAT_0 read fails\n");
		_rx_ts = _rx_crc;
		goto END;
	}

	/* Store Part of the 32-bit Tx Frame CRC */
	rx_ts->rx_crc_stat = (u16)_rx_crc;

	/* Get Part of the 32-bit Tx Frame CRC */
	_rx_crc = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_RX_CRC_STAT_1);

	if (_rx_crc < 0) {
		LOG_CRIT("ERROR: GMAC_TX_CRC_STAT_1 read fails\n");
		_rx_ts = _rx_crc;
		goto END;
	}

	/* Store Part of the 32-bit Tx Frame CRC */
	rx_ts->rx_crc_stat |= ((u16)_rx_crc << 16);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return _rx_ts;
}

int gpy2xx_ptp_gettxts(struct gpy211_device *phy,
		       struct gpy211_tx_ts *tx_ts)
{
	s32 _tx_ts, _tx_crc;
	u32 _ts_sec, _ts_nsec;
	time64_t _sec_to_nsec;
	u32 _pm_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || tx_ts == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_pm_base_addr = phy->pm_base_addr;

	/* Reset to zero */
	tx_ts->tx_ts_stat = 0;
	/* Get Part of the 64-bit Tx Timestamp */
	_tx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_TX_TS_STAT_0);

	if (_tx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_TX_TS_STAT_0 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Tx Timestamp */
	_ts_nsec = (u16)_tx_ts;

	/* Get Part of the 64-bit Tx Timestamp */
	_tx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_TX_TS_STAT_1);

	if (_tx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_TX_TS_STAT_1 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Tx Timestamp */
	_ts_nsec |= (_tx_ts << 16);
	//printf("\nNano-sec %x", _ts_nsec);

	/* Get Part of the 64-bit Tx Timestamp */
	_tx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_TX_TS_STAT_2);

	if (_tx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_TX_TS_STAT_2 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Tx Timestamp */
	_ts_sec = (u16)_tx_ts;

	/* Get Part of the 64-bit Tx Timestamp */
	_tx_ts = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_TX_TS_STAT_3);

	if (_tx_ts < 0) {
		LOG_CRIT("ERROR: GMAC_TX_TS_STAT_3 read fails\n");
		goto END;
	}

	/* Store Part of the 64-bit Tx Timestamp */
	_ts_sec |= ((u16)_tx_ts << 16);
	_sec_to_nsec = SEC_TO_NANOSEC(_ts_sec);
	tx_ts->tx_ts_stat = _sec_to_nsec + _ts_nsec;
	//printf("\nSec %x, Sec-to-Nsec %I64x, Total Nsec %I64x", _ts_sec, _sec_to_nsec, tx_ts->tx_ts_stat);

	/* Reset to zero */
	tx_ts->tx_crc_stat = 0;
	/* Get Part of the 32-bit Tx Frame CRC */
	_tx_crc = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_TX_CRC_STAT_0);

	if (_tx_crc < 0) {
		LOG_CRIT("ERROR: GMAC_TX_CRC_STAT_0 read fails\n");
		_tx_ts = _tx_crc;
		goto END;
	}

	/* Store Part of the 32-bit Tx Frame CRC */
	tx_ts->tx_crc_stat = (u16)_tx_crc;

	/* Get Part of the 32-bit Tx Frame CRC */
	_tx_crc = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_TX_CRC_STAT_1);

	if (_tx_crc < 0) {
		LOG_CRIT("ERROR: GMAC_TX_CRC_STAT_1 read fails\n");
		goto END;
	}

	/* Store Part of the 32-bit Tx Frame CRC */
	tx_ts->tx_crc_stat |= ((u16)_tx_crc << 16);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return _tx_ts;
}

int gpy2xx_ptp_getcfg(struct gpy211_device *phy,
		      struct gpy211_ptp_cfg *ptp_cfg)
{
	int ret = -EINVAL;
	struct gpy211_pmts_cfg _ptp_cfg;
	u32 _pm_base_addr;
	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || ptp_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);
	_pm_base_addr = phy->pm_base_addr;

	/* Get Transmit PTP Transport Protocol Type */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_GMAC_PTP_CFG);

	if (ret < 0) {
		LOG_CRIT("ERROR: GMAC_PTP_CFG read fails\n");
		goto END;
	}

	_ptp_cfg.raw_ptp_cfg = ret;
	ptp_cfg->ptp_ctrl.tx_ptp_off = _ptp_cfg.tx_ptp_off;
	ptp_cfg->ptp_ctrl.tx_ptp_tpt = _ptp_cfg.tx_ptp_tpt;

	/* Get PM configuration of GMAC Timestamp */
	ret = SMDIO_READ(phy, _pm_base_addr + PM_PDI_TS_CFG);

	if (ret < 0) {
		LOG_CRIT("ERROR: TS_CFG read fails\n");
		goto END;
	}

	_ptp_cfg.raw_ts_cfg = ret;
	ptp_cfg->ptp_ctrl.ts_ostc_en = _ptp_cfg.ts_ostc_en;
	ptp_cfg->ptp_ctrl.tx_ts_phy = _ptp_cfg.tx_ts_phy;
	ptp_cfg->ptp_ctrl.rx_ts_phy = _ptp_cfg.rx_ts_phy;
	ptp_cfg->ptp_ctrl.ts_ostc_en = _ptp_cfg.ts_ostc_en;

	if (ptp_cfg->ptp_ctrl.ts_ostc_en == 1) {
		ret = _gpy2xx_ptp_get_osctime(phy, &(ptp_cfg->ptp_ctrl.tx_ost_corr));

		if (ret < 0) {
			LOG_CRIT("ERROR: api _gpy2xx_ptp_get_osctime fails\n");
			goto END;
		}
	}

	ret = _gpy2xx_ptp_get_tsctrl(phy, &(ptp_cfg->ts_ctrl));

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_get_tsctrl fails\n");
		goto END;
	}

	ret = _gpy2xx_ptp_get_ppsctrl(phy, &(ptp_cfg->pps_ctrl));

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_get_ppsctrl fails\n");
		goto END;
	}

	ret = _gpy2xx_ptp_get_ptoctrl(phy, &(ptp_cfg->pto_ctrl));

	if (ret < 0) {
		LOG_CRIT("ERROR: api _gpy2xx_ptp_get_ptoctrl fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_aux_cfg(struct gpy211_device *phy, struct gpy211_aux_cfg *aux_cfg)
{

	int ret = -EINVAL;
	u32 _aux_ctrl;
	u32 _gmacf_base_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL || aux_cfg == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Check chip ID for register selection */
	if (phy->id.family != ID_P31G && phy->id.family != ID_P34X) {
		LOG_WARN("PTP auxiliary TS is not supported on this PHY familiy.\n");
		return -EINVAL;
	}

	/* Validate input params */
	if (aux_cfg->aux_enable > 1) {
		LOG_WARN("WARN: Wrong Enable parameter.\n");
		return -EINVAL;
	}

	if (aux_cfg->aux_trigger_port > 3) {
		LOG_WARN("WARN: Wrong trigger source.\n");
		return -EINVAL;
	}

	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;


	/* enable/disable auxiliary snapshot */
	_aux_ctrl = 0;
	FIELD_REPLACE(_aux_ctrl, aux_cfg->aux_enable, GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN0);
	ret = PHY_MBOX_HWWR(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_CONTROL_L, _aux_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_CONTROL_L write fails\n");
		goto END;
	}

	if (phy->id.family == ID_P34X) {
		ret = PHY_MBOX_HWRD(phy, SLICE_CGU_PDI_REGISTERS_MODULE_BASE + SLICE_CGU_PDI_SYNCE_CONF, &_aux_ctrl);
	} else {
		ret = PHY_MBOX_HWRD(phy, CGU_PDI_MODULE_BASE + CGU_PDI_SYNCE_CONF, &_aux_ctrl);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: CGU_PDI_SYNCE_CONF read fails\n");
		goto END;
	}

	if (phy->id.family == ID_P34X) {
		FIELD_REPLACE(_aux_ctrl, aux_cfg->aux_trigger_port, SLICE_CGU_PDI_SYNCE_CONF_INTIMER_SEL);
		ret = PHY_MBOX_HWWR(phy, SLICE_CGU_PDI_REGISTERS_MODULE_BASE + SLICE_CGU_PDI_SYNCE_CONF, _aux_ctrl);
	} else {
		FIELD_REPLACE(_aux_ctrl, aux_cfg->aux_trigger_port, CGU_PDI_SYNCE_CONF_INTIMER_SEL);
		ret = PHY_MBOX_HWWR(phy, CGU_PDI_MODULE_BASE + CGU_PDI_SYNCE_CONF, _aux_ctrl);
	}

	if (ret < 0) {
		LOG_CRIT("ERROR: CGU_PDI_SYNCE_CONF write fails\n");
		goto END;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_getauxts(struct gpy211_device *phy, struct timespec64 *ts)
{
	int ret = -EINVAL;
	time64_t _ref_ts;
	u32 _timestamp_ctrl;
	u32 _gmacf_base_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	/* Get auxlilary timestamp enent */
	ret = PHY_MBOX_HWRD(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_STATUS_L, &_timestamp_ctrl);

	if (ret < 0) {
		LOG_CRIT("ERROR: TIMESTAMP_STATUS_L read fails\n");
		goto END;
	}

	/* Get Seconds Part of the Auxiliary Time */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_TIMESTAMP_SECONDS_L read fails\n");
		goto END;
	}

	_ref_ts = (u16) ret;
	/* Store Part of the Auxiliary Timestamp */
	ts->tv_sec = _ref_ts;

	/* Get Seconds Part of the Auxiliary Time */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_TIMESTAMP_SECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_TIMESTAMP_SECONDS_H read fails\n");
		goto END;
	}

	_ref_ts = (u16)ret;
	/* Store Part of the Auxiliary Timestamp */
	ts->tv_sec |= (_ref_ts << 16);


	/* Get NanoSeconds Part of Auxiliary Timestamp */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_L);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_TIMESTAMP_NANOSECONDS_L read fails\n");
		goto END;
	}

	_ref_ts = (u16)ret;
	/* Store Part of the Auxiliary Timestamp */
	ts->tv_nsec = _ref_ts;

	/* Get NanoSeconds Part of the Auxiliary Timestamp */
	ret = SMDIO_READ(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_TIMESTAMP_NANOSECONDS_H read fails\n");
		goto END;
	}

	_ref_ts = (u16)ret & GMACF_MAC_AUXILIARY_TIMESTAMP_NANOSECONDS_H_AUXTSLO_MASK;
	/* Store Part of the Ref Timestamp */
	ts->tv_nsec |= (_ref_ts << 16);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_auxfifostat(struct gpy211_device *phy, struct gpy211_aux_fifo_stat *fifo_status)
{
	int ret = -EINVAL;
	u32 _data0, _data1;
	u32 _gmacf_base_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	ret = PHY_MBOX_HWRD(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_STATUS_L, &_data0);

	if (ret < 0) {
		LOG_CRIT("ERROR: TIMESTAMP_STATUS_L read fails\n");
		goto END;
	}

	ret = PHY_MBOX_HWRD(phy, _gmacf_base_addr + GMACF_MAC_TIMESTAMP_STATUS_H, &_data1);

	if (ret < 0) {
		LOG_CRIT("ERROR: TIMESTAMP_STATUS_H read fails\n");
		goto END;
	}

	fifo_status->ovfl = FIELD_GET(_data0, GMACF_MAC_TIMESTAMP_STATUS_L_TSSOVF);
	fifo_status->fill_lvl = FIELD_GET(_data1, GMACF_MAC_TIMESTAMP_STATUS_H_ATSNS);

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}

int gpy2xx_ptp_resetauxfifo(struct gpy211_device *phy)
{

	int ret = -EINVAL;
	u32 _data0;
	u32 _gmacf_base_addr;

	LOG_INFO("Entering func name :- %s\n", __func__);

	if (phy == NULL) {
		LOG_WARN("WARN: NULL input pointer(s)\n");
		return -EINVAL;
	}

	/* Validate input params */
	// None
	/* Acquire lock */
	phy->lock(phy->lock_data);

	_gmacf_base_addr = phy->gmacf_base_addr;

	ret = PHY_MBOX_HWRD(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_CONTROL_L, &_data0);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_CONTROL_L read fails\n");
		goto END;
	}

	_data0 = (_data0 || GMACF_MAC_AUXILIARY_CONTROL_L_ATSFC_MASK);

	ret = PHY_MBOX_HWWR(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_CONTROL_L, _data0);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_CONTROL_L write fails\n");
		goto END;
	}

	/* after reset, re-enable auxiliary snapshot */
	_data0 = (_data0 && ~GMACF_MAC_AUXILIARY_CONTROL_L_ATSFC_MASK);
	FIELD_REPLACE(_data0, 1, GMACF_MAC_AUXILIARY_CONTROL_L_ATSEN0);
	ret = PHY_MBOX_HWWR(phy, _gmacf_base_addr + GMACF_MAC_AUXILIARY_CONTROL_L, _data0);

	if (ret < 0) {
		LOG_CRIT("ERROR: AUXILIARY_CONTROL_L write fails\n");
		return ret;
	}

END:
	phy->unlock(phy->lock_data);

	LOG_INFO("Exiting func name :- %s\n", __func__);
	return ret;
}
