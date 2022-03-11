/******************************************************************************

         Copyright 2020 - 2021 MaxLinear Inc.
         Copyright 2016 - 2020 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <gpy211.h>
#include <gpy211_common.h>
#include <registers/phy/std.h>
#include <registers/p31g/pmu_pdi_registers.h>
#include <registers/p31g/smdio_pdi_smdio_registers.h>

#include "lantiq_gsw.h"
#include "mac_ops.h"

#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && EN_EXEC_TIME_PER_MDIO_FREQ
#include <time.h>
#include <sys/time.h>
#define NUM_ITES_PER_MDIO_FREQ_DIV		01
#else
#define NUM_ITES_PER_MDIO_FREQ_DIV		10
#endif

#define min(a, b)	((a)<(b) ? (a) : (b))

static int gpy211_mdio_read(void *busdata, u16 phyaddr, u32 regnum);
static int gpy211_mdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data);

static struct gpy2xx_mdio {
	int fd;
	int xgmac_id;
} mdio = {
	-1,
	2
};

//static unsigned int g_mdio_rd_cnt = 0;
//static unsigned int g_mdio_wr_cnt = 0;

static struct gpy211_device phy = {
	NULL, // callback func pointer for 'lock'
	NULL, // callback func pointer for 'unlock'
	NULL, // pointer to lock_data
	gpy211_mdio_read, // callback func pointer for 'mdio_read'
	gpy211_mdio_write, // callback func pointer for 'mdio_write'
	&mdio, // pointer to mdio_data
	0x1f, // smdio_addr
	0x03, // phy_addr
	NULL, // pointer to priv_data
	NULL, // pointer to shared_data
	{0},  // PHY ID
	{0},  // Link data
	0x60, // WOL support
	0,     // macsec_supported
	0,
	NULL,
	NULL,
	0x320,
	0xaabbccdd,
};

static int _fmx_reg_read(void *busdata, u32 regnum)
{
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_REG_RD;
	param.get = 1;
	param.mac_idx = priv->xgmac_id;
	param.val[0] = regnum;

	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _fmx_reg_write(void *busdata, u32 regnum, u32 data)
{
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_REG_WR;
	param.mac_idx = priv->xgmac_id;
	param.val[0] = regnum;
	param.val[1] = data;

	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _fmx_get_clause(void *busdata, u32 phyaddr)
{
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_GET_MDIO_CL;
	param.get = 1;
	param.mac_idx = priv->xgmac_id;
	param.argc = 2;
	param.val[0] = 0;
	param.val[1] = phyaddr;

	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _fmx_set_clause(void *busdata, u32 phyaddr, u32 clause)
{
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_SET_MDIO_CL;
	param.argc = 3;
	param.set_all = 1;
	param.mac_idx = priv->xgmac_id;
	param.val[0] = 0;
	param.val[1] = clause;
	param.val[2] = phyaddr;

	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _gpy211_c22mdio_read(void *busdata, u16 phyaddr, u32 regnum)
{
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_SET_MDIO_RD;
	param.argc = 3;
	param.get = 1;
	param.set_all = 0;
	param.mac_idx = priv->xgmac_id;
	param.val[0] = 0;
	param.val[1] = phyaddr;
	param.val[2] = regnum;

	//printf("In read:- Mac id: %u, Dev id: %u, Phy id: %u, Reg num: %u\n", param.mac_idx, param.val[0], param.val[1], param.val[2]);

	//g_mdio_rd_cnt++;
	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _gpy211_c22mdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data)
{
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_SET_MDIO_WR;
	param.argc = 4;
	param.get = 0;
	param.set_all = 0;
	param.mac_idx = priv->xgmac_id;
	param.val[0] = 0;
	param.val[1] = phyaddr;
	param.val[2] = regnum;
	param.val[3] = data;

	//printf("In write:- Mac id: %u, Dev id: %u, Phy id: %u, Reg num: %u, Data: %u\n", param.mac_idx, param.val[0], param.val[1], param.val[2], param.val[3]);

	//g_mdio_wr_cnt++;
	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _gpy211_c45mdio_read(void *busdata, u16 phyaddr, u32 regnum)
{
	u16 _reg_num, _dev_id;
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	_dev_id = (regnum >> 16) & 0x1F;
	_reg_num = regnum & 0xFFFF;

	param.cmdType = MAC_CLI_SET_MDIO_RD;
	param.argc = 3;
	param.get = 1;
	param.set_all = 0;
	param.mac_idx = priv->xgmac_id;
	param.val[0] = _dev_id;
	param.val[1] = phyaddr;
	param.val[2] = _reg_num;

	//printf("In read:- Mac id: %u, Dev id: %u, Phy id: %u, Reg num: %u\n", param.mac_idx, param.val[0], param.val[1], param.val[2]);

	//g_mdio_rd_cnt++;
	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _gpy211_c45mdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data)
{
	u16 _reg_num, _dev_id;
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	_dev_id = (regnum >> 16) & 0x1F;
	_reg_num = regnum & 0xFFFF;

	param.cmdType = MAC_CLI_SET_MDIO_WR;
	param.argc = 4;
	param.get = 0;
	param.set_all = 0;
	param.mac_idx = priv->xgmac_id;
	param.val[0] = _dev_id;
	param.val[1] = phyaddr;
	param.val[2] = _reg_num;
	param.val[3] = data;

	//printf("In write:- Mac id: %u, Dev id: %u, Phy id: %u, Reg num: %u, Data: %u\n", param.mac_idx, param.val[0], param.val[1], param.val[2], param.val[3]);

	//g_mdio_wr_cnt++;
	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int _gpy211_c22extnd_read(void *busdata, u16 phyaddr, u32 regnum)
{
	int ret;
	u16 _reg_num, _dev_id;

	/* CLAUSE 45 type read */
	_dev_id = (regnum >> 16) & 0x1F;
	_reg_num = regnum & 0xFFFF;

	/* Write MMDCTRL address register */
	ret = _gpy211_c22mdio_write(busdata, phyaddr, STD_MMDCTRL / 2, _dev_id);

	if (ret < 0)
		return ret;

	/* Write MMDDATA address register */
	ret = _gpy211_c22mdio_write(busdata, phyaddr, STD_MMDDATA / 2, _reg_num);

	if (ret < 0)
		return ret;

	/* Write MMDCTRL address register */
	ret = _gpy211_c22mdio_write(busdata, phyaddr, STD_MMDCTRL / 2, (0x4000 + _dev_id));

	if (ret < 0)
		return ret;

	/* Read target register */
	return _gpy211_c22mdio_read(busdata, phyaddr, STD_MMDDATA / 2);
}

static int _gpy211_c22extnd_write(void *busdata, u16 phyaddr, u32 regnum, u16 data)
{
	int ret;
	u16 _reg_num, _dev_id;

	_dev_id = (regnum >> 16) & 0x1F;
	_reg_num = regnum & 0xFFFF;

	/* write MMDCTRL address register */
	ret = _gpy211_c22mdio_write(busdata, phyaddr, STD_MMDCTRL / 2, _dev_id);

	if (ret < 0)
		return ret;

	/* write MMDDATA address register */
	ret = _gpy211_c22mdio_write(busdata, phyaddr, STD_MMDDATA / 2, _reg_num);

	if (ret < 0)
		return ret;

	/* write MMDCTRL address register */
	ret = _gpy211_c22mdio_write(busdata, phyaddr, STD_MMDCTRL / 2, (0x4000 + _dev_id));

	if (ret < 0)
		return ret;

	/* write target register */
	ret = _gpy211_c22mdio_write(busdata, phyaddr, STD_MMDDATA / 2, data);

	if (ret < 0)
		return ret;

	return 0;
}

static int gpy211_mdio_read(void *busdata, u16 phyaddr, u32 regnum)
{
	u8 _mdio_clause;
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_GET_MDIO_CL;
	param.get = 1;
	param.mac_idx = priv->xgmac_id;
	param.argc = 2;
	param.val[0] = 0;
	param.val[1] = phyaddr;

	_mdio_clause = ioctl(priv->fd, GSW_XGMAC_CFG, &param);
	//printf("Clause: %s\n", _mdio_clause ? "CL22" : "CL45");

	if (_mdio_clause == 0) {
		//printf("Calling C45 read\n");
		/* CLAUSE 45 type read */
		return _gpy211_c45mdio_read(busdata, phyaddr, regnum);
	} else if (regnum & MII_ADDR_C45) {
		//printf("Calling C22 extended read\n");
		/* CLAUSE C22 extended type read */
		return _gpy211_c22extnd_read(busdata, phyaddr, regnum);
	} else {
		//printf("Calling C22 read\n");
		/* CLAUSE C22 extended type read */
		return _gpy211_c22mdio_read(busdata, phyaddr, regnum);
	}
}

static int gpy211_mdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data)
{
	u8 _mdio_clause;
	GSW_MAC_Cli_t param = {0};
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;

	param.cmdType = MAC_CLI_GET_MDIO_CL;
	param.get = 1;
	param.mac_idx = priv->xgmac_id;
	param.argc = 2;
	param.val[0] = 0;
	param.val[1] = phyaddr;

	_mdio_clause = ioctl(priv->fd, GSW_XGMAC_CFG, &param);
	//printf("Clause: %s\n", _mdio_clause ? "CL22" : "CL45");

	if (_mdio_clause == 0) {
		//printf("Calling C45 write\n");
		/* CLAUSE 45 type read */
		return _gpy211_c45mdio_write(busdata, phyaddr, regnum, data);
	} else if (regnum & MII_ADDR_C45) {
		//printf("Calling C22 extended write\n");
		/* CLAUSE 22 extended type read */
		return _gpy211_c22extnd_write(busdata, phyaddr, regnum, data);
	} else {
		//printf("Calling C22 write\n");
		/* CLAUSE 22 extended type read */
		return _gpy211_c22mdio_write(busdata, phyaddr, regnum, data);
	}
}

static int fw_fast_write(char *fw_path, u32 cfw_ver)
{
	int ret, ret2 = 0;
	FILE *fwin;
	u32 filesize;
	u8 buf[256];
	u32 wrsize;

	fwin = fopen(fw_path, "rb");
	if (fwin == NULL) {
		printf("Failed to open FW file \"%s\".\n", fw_path);
		return -errno;
	}
	fseek(fwin, 0L, SEEK_END);
	filesize = ftell(fwin);
#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf("FW size: %u\n", filesize);
#endif
	rewind(fwin);

#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf("Init GPHY ... ");
#endif
	fflush(stdout);
	ret = gpy2xx_init(&phy);
	if (ret < 0) {
		printf("api gpy2xx_init failed: %d\n", ret);
		fclose(fwin);
		return ret;
	}
#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf("done\n");
#endif
	//print_ver(&phy.id);

#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf("Erasing flash ... ");
#endif
	fflush(stdout);

#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && EN_EXEC_TIME_PER_MDIO_FREQ
/*
	struct timeval	tv1, tv2;
	gettimeofday(&tv1, NULL);
*/
	clock_t begin_ffu = clock();
#endif

#if defined(EN_TEST_P34X_FFU) && EN_TEST_P34X_FFU
	ret = gpy2xx_smdio_read(&phy, 0x00D2880C); //RCU_PDI_REGISTERS_RST_REQ
	if (ret < 0) {
		printf("api gpy2xx_smdio_read failed: %d\n", ret);
	}
	printf("The value of reg RCU_PDI_REGISTERS_RST_REQ: %x\n", ret);

	ret = gpy2xx_smdio_write(&phy, 0x00D2880C, 0x1770); //RCU_PDI_REGISTERS_RST_REQ.SLICE0 = 1
	if (ret < 0) {
		printf("api gpy2xx_smdio_write failed: %d\n", ret);
	}
#endif

	ret = gpy2xx_fw_frw_init(&phy, FW_FWR_DEF_TIMEOUT);
	if (ret < 0) {
		printf("api gpy2xx_fw_frw_init failed: %d\n", ret);
		fclose(fwin);
		return ret;
	}

#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf("done\n");

	printf("Programming flash ...");
#endif
	fflush(stdout);
	while (filesize > 0) {
		memset(buf, 0xFF, sizeof(buf));
		wrsize = min(filesize, sizeof(buf));
		ret = fread(buf, 1, wrsize, fwin);
		if (ret <= 0) {
			printf("file read fail: %d\n", ret);
			fclose(fwin);
			return -errno;
		}
		if (ret != wrsize) {
			printf("reading 'wrsize' bytes from file failed: %d != %d\n", ret, wrsize);
			fclose(fwin);
			return -errno;
		}
#if defined(TEST_ALL_ZERO_IMAGE) && TEST_ALL_ZERO_IMAGE
		{
			int loop =0;
			memset(buf, 0x00, sizeof(buf));
			printf("all zero image loop %d\n", loop++);
		}
#endif
		ret = gpy2xx_fw_fwr_page(&phy, buf, FW_FWR_DEF_TIMEOUT);
		if (ret < 0) {
			printf("api gpy2xx_fw_fwr_page failed: %d\n", ret);
			//fclose(fwin);
			//return ret;
			ret2 =ret;
			goto RESET_PHY;
		}
		//printf(".");
		fflush(stdout);

		filesize -= wrsize;
	}
#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf(" done\n");
#endif

RESET_PHY:
#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf("Reset PHY ... ");
#endif
	fflush(stdout);
#if defined(EN_TEST_P34X_FFU) && EN_TEST_P34X_FFU
	ret = gpy2xx_smdio_read(&phy, 0x00D2880C); //TOP_FCR
	if (ret < 0) {
		printf("api gpy2xx_smdio_read failed: %d\n", ret);
	}
	printf("The value of reg TOP_FCR: %x\n", ret);

	ret = gpy2xx_smdio_write(&phy, 0x00D2880C, 0x8000); //TOP_FCR.BOOTSEL = FLASH
	if (ret < 0) {
		printf("api gpy2xx_smdio_write failed: %d\n", ret);
	}

	ret = gpy2xx_smdio_read(&phy, 0x00D28814); //TOP_INDICATOR
	if (ret < 0) {
		printf("api gpy2xx_smdio_read failed: %d\n", ret);
	}
	printf("The value of reg TOP_INDICATOR: %x\n", ret);

	ret = gpy2xx_smdio_write(&phy, 0x00D28814, 0x0020); //TOP_INDICATOR.BOOTROM_EXIT = FLASH
	if (ret < 0) {
		printf("api gpy2xx_smdio_write failed: %d\n", ret);
	}

	ret = gpy2xx_smdio_write(&phy, 0x00D29404, 0x1778); //RCU_PDI_REGISTERS_RST_REQ.SLICE0 = 1
	if (ret < 0) {
		printf("api gpy2xx_smdio_write failed: %d\n", ret);
	}

	ret = gpy2xx_smdio_write(&phy, 0x00D29404, 0x1770); //RCU_PDI_REGISTERS_RST_REQ.SLICE0 = 0
	if (ret < 0) {
		printf("api gpy2xx_smdio_write failed: %d\n", ret);
	}
#else
	ret = gpy2xx_fw_frw_uninit(&phy);
	if (ret < 0) {
		printf("api gpy2xx_fw_frw_uninit failed: %d\n", ret);
		fclose(fwin);
		return ret;
	}
#endif

#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && !EN_EXEC_TIME_PER_MDIO_FREQ
	printf("done\n");
#endif

#if defined(EN_EXEC_TIME_PER_MDIO_FREQ) && EN_EXEC_TIME_PER_MDIO_FREQ
	clock_t end_ffu = clock();
	double time_spent = ((double)(end_ffu - begin_ffu)) / CLOCKS_PER_SEC;
	printf("INFO: FFU execution time = %f seconds\n", time_spent);
/*
	gettimeofday(&tv2, NULL);
	printf("INFO: FFU execution time = %f seconds\n",
			 (((double) (tv2.tv_usec - tv1.tv_usec) / 1000000) + (double) (tv2.tv_sec - tv1.tv_sec)));
*/
	do {
	ret = gpy2xx_read(&phy, 30);
		if (ret < 0) {
			printf("reading fw version failed\n");
			return ret;
		}
	}while(ret != cfw_ver); //TODO: need implement infinite loop breaker.
	clock_t phy_up = clock();
	double phy_spent = ((double)(phy_up - end_ffu)) / CLOCKS_PER_SEC;
	printf("INFO: PHY bring-up time = %f seconds\n", phy_spent);
#endif

	udelay(1000000u);

	fclose(fwin);
	if (ret2 == 0)
		return 0;
	else
		return ret2;
}

#if defined(EN_USER_CHOICE) && EN_USER_CHOICE
static void remove_leading_whitespace(char **p, int *len)
{
	while (*len && ((**p == ' ') || (**p == '\r') || (**p == '\r'))) {
		(*p)++;
		(*len)--;
	}
}

static int split_buffer(char *buffer, char *array[], int max_param_num)
{
	int i, set_copy = 0;
	int res = 0;
	int len;

	for (i = 0; i < max_param_num; i++)
		array[i] = NULL;

	if (!buffer)
		return 0;

	len = strlen(buffer);

	for (i = 0; i < max_param_num;) {
		remove_leading_whitespace(&buffer, &len);

		for (;
		     *buffer != ' ' && *buffer != '\0' && *buffer != '\r'
		     && *buffer != '\n' && *buffer != '\t'; buffer++, len--) {
			/*Find first valid charactor */
			set_copy = 1;

			if (!array[i])
				array[i] = buffer;
		}

		if (set_copy == 1) {
			i++;

			if (*buffer == '\0' || *buffer == '\r'
			    || *buffer == '\n') {
				*buffer = 0;
				break;
			}

			*buffer = 0;
			buffer++;
			len--;
			set_copy = 0;

		} else {
			if (*buffer == '\0' || *buffer == '\r'
			    || *buffer == '\n')
				break;

			buffer++;
			len--;
		}
	}

	res = i;

	return res;
}

static unsigned int t_olower(u32 ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return ch + 'a' - 'A';

	return ch;
}

static unsigned int xstrncasecmp(const char *s1, const char *s2, unsigned int n)
{
	int c1, c2;

	if (!s1 || !s2) return 1;

	for (; n > 0; s1++, s2++, --n) {
		c1 = t_olower(*s1);
		c2 = t_olower(*s2);

		if (c1 != c2) {
			return (c1 - c2);
		} else if (c1 == '\0') {
			return 0;
		}
	}

	return 0;
}

static char *findArgParam(int argc, char *argv[], char *name)
{
	int i = 0;
	size_t len;

	len = strlen(name);

	for (i = 0; i < argc; i++) {
		if (xstrncasecmp(name, argv[i], len) == 0) {
			if (strlen(argv[i]) > (len + 1)) {

				if ('=' == argv[i][len]) {
					return argv[i] + len + 1;
				}
			}
		}
	}

	return NULL;
}

int scanParamArg(int argc, char *argv[], char *name, int size, void *param)
{
	unsigned long long int tmp;
	char *endptr;

	char *ptr = findArgParam(argc, argv, name);

	if (ptr == NULL) return 0;

	/* check if the given parameter value are the boolean "LTQ_TRUE" / "LTQ_FALSE" */

	if (0 == xstrncasecmp(ptr, "LTQ_TRUE", strlen(ptr))
	    || 0 == xstrncasecmp(ptr, "TRUE", strlen(ptr))
	    || 0 == xstrncasecmp(ptr, "FULL", strlen(ptr))) {
		tmp = 1;
	} else if (0 == xstrncasecmp(ptr, "LTQ_FALSE", strlen(ptr))
		   || 0 == xstrncasecmp(ptr, "FALSE", strlen(ptr))
		   || 0 == xstrncasecmp(ptr, "HALF", strlen(ptr))) {
		tmp = 0;
	} else {
		/* scan for a number */
		tmp = strtoull(ptr, &endptr, 0);

		/* parameter detection does not work in case there are more character after the provided number */
		if (*endptr != '\0')
			return 0;
	}

	if (size <= 4)
		size *= 8;

	if (size == 8)
		*((char *)param) = (char)tmp;
	else if (size == 16)
		*((short *)param) = (short)tmp;
	else if (size == 32)
		*((int *)param) = (int)tmp;
	else if (size == 64)
		*((long long *)param) = (long long)tmp;

	return 1;
}
#endif

int main(int argc, char **argv)
{
	char *fw_path = NULL;
	int i, j, ret, k = 0;
	struct gpy211_id phyId;
	const char *gsw_dev = "/dev/switch_api/0";
	u32 fw_ver, cfw_ver, tot_ite = 600, clause = 0xf, mdc_clk_div = 0;
	u32 addr, data, fl_code, br_exit, bl_exit, tot_pt = 0, tot_bc = 0, negate_cl = 0;

#if defined(EN_USER_CHOICE) && EN_USER_CHOICE
	int l = 0;
	int num = 0;
	u32 check_space;
	char *param_list[200], temp_buffer[16], lpBuffer[1000], lpBuffer2[1000];
#endif

	for (i = 1, j = 0; i < argc; i++) {
		switch (j) {
		case 0:
			if (strcasecmp(argv[i], "fw") == 0) {
				j++;
				break;
			}
		case 1:
			fw_path = argv[i];
			j = 2;
			break;
		case 2:
			mdio.xgmac_id = atoi(argv[i]);
			j++;
			break;
		case 3:
			phy.phy_addr = strtoul(argv[i], NULL, 0);
			j++;
			break;
		case 4:
			tot_ite = strtoul(argv[i], NULL, 0);
			j++;
			break;
		case 5:
			clause = strtoul(argv[i], NULL, 0);
			j++;
			break;
		case 6:
			cfw_ver = strtoul(argv[i], NULL, 0);
			j++;
			break;
		case 7:
			mdc_clk_div = strtoul(argv[i], NULL, 0);
			j++;
			break;
		}
	}

	if (fw_path == NULL) {
		printf("<ffu_appl_name> fw <fw_bin_file_name> <mdio_xgmac_id> <p31g_phy_id> <tot_iterations_to_run> <mdio_clause> <fw_version_to_compare> <fmx_mdc_clk_divider>\n");
		printf("example below\n");
		printf("./prqv4_ffu_no_extra_cycles_wowa fw GPY2XXP_FLASH_IMAGE_LTCSS_INPUT_0x3740_unsigned_release.bin 2 3 3600 0x0 0x4743 62\n");
		return -1;
	} else if (mdio.xgmac_id < 2 || mdio.xgmac_id > 3) {
		printf("Falcon-Mx support MDIO on XGMAC 2 and 3 only\n");
		return -1;
	} else if (phy.phy_addr > 0x1f) {
		printf("Invalid PHY address %u (range 0~31)\n", (u32)phy.phy_addr);
		return -1;
	}

	printf("total iterations = %d, fw version to compare = %x, mdc clock devider = %d, mdio clause = %d\n", tot_ite, cfw_ver, mdc_clk_div, clause);

	mdio.fd = open(gsw_dev, O_RDONLY);
	if (mdio.fd < 0) {
		printf("Can't open GSW API device node \"%s\"\n", gsw_dev);
		return -1;
	}

	ret = gpy2xx_read(&phy, 30);
	if (ret < 0) {
		printf("reading fw version failed\n");
		return ret;
	}
	printf("power-up fw version is 0x%x\n", ret);

	ret = gpy2xx_read(&phy, 17);
	if (ret < 0) {
		printf("reading phy status1 failed\n");
		return ret;
	}
	ret = (ret >> 2) & 0x3;
	printf("memory target used for firmware execution at boot-up is %s\n", (ret ? ((ret == 1) ? "OTP": "FLASH") : "ROM"));

#if ((defined(EN_TEST_REG_READ_WRITE) && EN_TEST_REG_READ_WRITE) || (defined(EN_ERASE_FLASH_ONLY_TEST) && EN_ERASE_FLASH_ONLY_TEST))
	_fmx_reg_write(phy.mdiobus_data, 0x220, clause);
	printf("set clause - %x\n", clause);
	printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
	_fmx_reg_write(phy.mdiobus_data, 0x204, mdc_clk_div << 19);
	printf("set mdio clk div - %x\n", mdc_clk_div << 19);
	printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));

	printf("Init GPHY ... ");

	ret = gpy2xx_init(&phy);
	if (ret < 0) {
		printf("api gpy2xx_init failed: %d\n", ret);
		return ret;
	}

	printf("done\n");
#endif

#if defined(EN_ERASE_FLASH_ONLY_TEST) && EN_ERASE_FLASH_ONLY_TEST
	printf("Erasing flash ... ");

	ret = gpy2xx_fw_frw_init(&phy, FW_FWR_DEF_TIMEOUT);
	if (ret < 0) {
		printf("api gpy2xx_fw_frw_init failed: %d\n", ret);
		return ret;
	}

	printf("done\n");
	printf("Reset PHY ... ");

	ret = gpy2xx_fw_frw_uninit(&phy);
	if (ret < 0) {
		printf("api gpy2xx_fw_frw_uninit failed: %d\n", ret);
		return ret;
	}

	printf("done\n");

	udelay(1000000u);

	ret = gpy2xx_read(&phy, 30);
	if (ret < 0) {
		printf("reading fw version failed\n");
		return ret;
	}
	printf("erased fw version is 0x%x\n", ret);
	return 0;
#elif defined(EN_TEST_REG_READ_WRITE) && EN_TEST_REG_READ_WRITE
	goto WAIT_FOR_UC;
#endif

        _fmx_reg_write(phy.mdiobus_data, 0x220, clause);
        printf("set clause - %x\n", clause);
        printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
        _fmx_reg_write(phy.mdiobus_data, 0x204, mdc_clk_div << 19);
        printf("set mdio clk div - %x\n", mdc_clk_div << 19);
        printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));

	_fmx_set_clause(phy.mdiobus_data, phy.phy_addr, clause);
	clause = _fmx_get_clause(phy.mdiobus_data, phy.phy_addr);
	printf("get mdio clause - %x n %x\n", clause, _fmx_get_clause(phy.mdiobus_data, phy.phy_addr));

	while (k < tot_ite) {
		k++;
		printf("\n\n\nrunning iteration = %d\n", k);
		ret = fw_fast_write(fw_path, cfw_ver);
		if (ret < 0) {
			printf("Hi!!!!!!!!!!!!!!!!! ... it's api fw_fast_write failed ... key in 'cont' to conitnue or 'exit' to exit\n");
			tot_pt++; //tatol page time-out failures

			ret = gpy2xx_read(&phy, 30);
			if (ret < 0) {
				printf("reading fw version failed\n");
				return ret;
			}
			printf("fail fw version is 0x%x\n", ret);

#if defined(EN_USER_CHOICE) && EN_USER_CHOICE
			goto READ_BOOTSTAT;
#else
			goto CHANGE_MDIO_FREQ;
#endif
		}

		ret = gpy2xx_read(&phy, 30);
		if (ret < 0) {
			printf("reading fw version failed\n");
			return ret;
		}
		fw_ver = ret;
		printf("boot fw version is 0x%x\n", fw_ver);

		if ((fw_ver & 0xFFFF) != cfw_ver) {
			printf("Hellooooooooooooooo ... it's failed to boot from flash ... key in 'cont' to conitnue or 'exit' to exit\n");
			tot_bc++; //tatol byte corruption failures

#if defined(EN_USER_CHOICE) && EN_USER_CHOICE
READ_BOOTSTAT:
#endif
			addr = PMU_PDI_REGISTERS_PMU_PDI_REGISTERS_BOOTSTAT;
			ret = gpy2xx_mbox_read16(&phy, addr, &data);
			if (ret < 0) {
				printf("reading boot status failed\n");
#if defined(EN_USER_CHOICE) && EN_USER_CHOICE
				goto WAIT_FOR_UC;
#else
				goto CHANGE_MDIO_FREQ;
#endif
			}

			fl_code = FIELD_GET(data, PMU_PDI_REGISTERS_BOOTSTAT_FAILCODE);
			br_exit = FIELD_GET(data, PMU_PDI_REGISTERS_BOOTSTAT_BOOTROM_EXIT);
			bl_exit = FIELD_GET(data, PMU_PDI_REGISTERS_BOOTSTAT_BOOTLOADER_EXIT);
			printf("boot status fail-code 0x%x, boot rom-exit 0x%x, boot loader-exit 0x%x\n", fl_code, br_exit, bl_exit);

#if ((defined(EN_USER_CHOICE) && EN_USER_CHOICE) || (defined(EN_TEST_REG_READ_WRITE) && EN_TEST_REG_READ_WRITE))
WAIT_FOR_UC:
			while (1) {
				memset(lpBuffer, 0, 1000);
				memset(temp_buffer, 0, 15);

				fgets(lpBuffer, sizeof(lpBuffer), stdin);

				memcpy(temp_buffer, lpBuffer, 15);
				memcpy(lpBuffer2, lpBuffer, 1000);

				num = 0;
				check_space = 1;

				for (l = 0; l < 15; l++) {
					if (temp_buffer[l] != ' ' && temp_buffer[l] != 0 && temp_buffer[l] != '\n') {
						check_space = 0;
					}
				}

				if (temp_buffer[0] != '\n' || check_space == 0) {
					num = split_buffer(lpBuffer, param_list, 200);
				}

				if (temp_buffer[0] == '\n' || check_space == 1) {
					continue;
				} else if (xstrncasecmp(param_list[0], "exit", 4) == 0) {
					return -1;
				} else if (xstrncasecmp(param_list[0], "cont", 4) == 0) {
					break;
				} else if (xstrncasecmp(param_list[0], "gpy2xx_read_mmd", strlen("gpy2xx_read_mmd")) == 0) {
					int cnt = 0;
					int dev_id;
					u32 reg_off;

					cnt += scanParamArg(num, &param_list[1], "devtype", sizeof(dev_id), &dev_id);
					cnt += scanParamArg(num, &param_list[1], "regaddr", sizeof(reg_off), &reg_off);

					ret = gpy2xx_read_mmd(&phy, dev_id, reg_off);

					if (ret < 0) {
						printf("\nERROR: MMD read failed.\n");
					} else {
						printf("\nMmd rd vale = 0x%x\n", ret);
					}
				} else if (xstrncasecmp(param_list[0], "gpy2xx_write_mmd", strlen("gpy2xx_write_mmd")) == 0) {
					int cnt = 0;
					int dev_id;
					u32 reg_off;
					u16 data_val;

					cnt += scanParamArg(num, &param_list[1], "devtype", sizeof(dev_id), &dev_id);
					cnt += scanParamArg(num, &param_list[1], "regaddr", sizeof(reg_off), &reg_off);
					cnt += scanParamArg(num, &param_list[1], "data", sizeof(data_val), &data_val);

					ret = gpy2xx_write_mmd(&phy, dev_id, reg_off, data_val);

					if (ret < 0) {
						printf("\nERROR: MMD write failed.\n");
					}
				} else if (xstrncasecmp(param_list[0], "gpy2xx_read", strlen("gpy2xx_read")) == 0) {
					int cnt = 0;
					u32 reg_off;

					cnt += scanParamArg(num, &param_list[1], "regaddr", sizeof(reg_off), &reg_off);

					ret = gpy2xx_read(&phy, reg_off);

					if (ret < 0) {
						printf("\nERROR: MDIO read failed.\n");
					} else {
						printf("\nMdio rd vale = 0x%x\n", ret);
					}
				} else if (xstrncasecmp(param_list[0], "gpy2xx_write", strlen("gpy2xx_write")) == 0) {
					int cnt = 0;
					u32 reg_off;
					u16 data_val;

					cnt += scanParamArg(num, &param_list[1], "regaddr", sizeof(reg_off), &reg_off);
					cnt += scanParamArg(num, &param_list[1], "data", sizeof(data_val), &data_val);

					ret = gpy2xx_write(&phy, reg_off, data_val);

					if (ret < 0) {
						printf("\nERROR: MDIO write failed.\n");
					}
				} else if (xstrncasecmp(param_list[0], "gpy2xx_mbox_read16", strlen("gpy2xx_mbox_read16")) == 0) {
					int cnt = 0;
					u32 reg_off, data_val;

					cnt += scanParamArg(num,  &param_list[1], "regaddr", sizeof(reg_off), &reg_off);

					ret = gpy2xx_mbox_read16(&phy, reg_off, &data_val);

					if (ret < 0) {
						printf("\nERROR: MBOX read failed.\n");
					} else {
						printf("\nMBOX rd vale = 0x%x\n", data_val);
					}
				} else if (xstrncasecmp(param_list[0], "gpy2xx_mbox_write16", strlen("gpy2xx_mbox_write16")) == 0) {
					int cnt = 0;
					u32 reg_off, data_val;

					cnt += scanParamArg(num,  &param_list[1], "regaddr", sizeof(reg_off), &reg_off);
					cnt += scanParamArg(num,  &param_list[1], "data", sizeof(data_val), &data_val);

					ret = gpy2xx_mbox_write16(&phy, reg_off, data_val);

					if (ret < 0) {
						printf("\nERROR: MBOX write failed.\n");
					}
				} else if (xstrncasecmp(param_list[0], "gpy2xx_mbox_read32", strlen("gpy2xx_mbox_read32")) == 0) {
					int cnt = 0;
					u32 reg_off, data_val;

					cnt += scanParamArg(num,  &param_list[1], "regaddr", sizeof(reg_off), &reg_off);

					ret = gpy2xx_mbox_read32(&phy, reg_off, &data_val);

					if (ret < 0) {
						printf("\nERROR: MBOX read failed.\n");
					} else {
						printf("\nMBOX rd vale = 0x%x\n", data_val);
					}
				} else if (xstrncasecmp(param_list[0], "gpy2xx_mbox_write32", strlen("gpy2xx_mbox_write32")) == 0) {
					int cnt = 0;
					u32 reg_off, data_val;

					cnt += scanParamArg(num,  &param_list[1], "regaddr", sizeof(reg_off), &reg_off);
					cnt += scanParamArg(num,  &param_list[1], "data", sizeof(data_val), &data_val);

					ret = gpy2xx_mbox_write32(&phy, reg_off, data_val);

					if (ret < 0) {
						printf("\nERROR: MBOX write failed.\n");
					}
				}  else {
					printf("invalid key input ....  key in 'cont' to conitnue or 'exit' to exit\n");
				}
			}
#endif
		}

#if defined(EN_USER_CHOICE) && !EN_USER_CHOICE
CHANGE_MDIO_FREQ:
#endif
		if (tot_pt)
			printf("total page time out fails so far = %d\n", tot_pt);
		if (tot_bc)
			printf("total byte corruption fails so far = %d\n", tot_bc);

		ret = gpy2xx_read(&phy, 17);
		if (ret < 0) {
			printf("reading phy status1 failed\n");
			return ret;
		}
		ret = (ret >> 2) & 0x3;
		printf("memory target used for firmware execution post reset is %s\n", (ret ? ((ret == 1) ? "OTP": ((ret == 2) ? "FLASH" : "SRAM")) : "ROM"));

		if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 0) && (negate_cl == 0)) {
			mdc_clk_div = 1;
			printf("set clause - given\n", _fmx_reg_write(phy.mdiobus_data, 0x220, clause));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 102\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x080000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 1) && (negate_cl == 0)) {
			mdc_clk_div = 2;
			printf("set clause - given\n", _fmx_reg_write(phy.mdiobus_data, 0x220, clause));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 122\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x100000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 2) && (negate_cl == 0)) {
			mdc_clk_div = 3;
			printf("set clause - given\n", _fmx_reg_write(phy.mdiobus_data, 0x220, clause));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 142\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x180000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 3)&& (negate_cl == 0)) {
			mdc_clk_div = 4;
			printf("set clause - given\n", _fmx_reg_write(phy.mdiobus_data, 0x220, clause));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 162\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x200000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 4)&& (negate_cl == 0)) {
			mdc_clk_div = 5;
			printf("set clause - given\n", _fmx_reg_write(phy.mdiobus_data, 0x220, clause));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 202\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x280000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 5) && (negate_cl == 1)) {
			negate_cl = 1;
			mdc_clk_div = 0;
			printf("set clause - negate\n", _fmx_reg_write(phy.mdiobus_data, 0x220, ((~clause) & 0xf)));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 62\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x0));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 0) && (negate_cl == 1)) {
			mdc_clk_div = 1;
			printf("set clause - negate\n", _fmx_reg_write(phy.mdiobus_data, 0x220, ((~clause) & 0xf)));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 102\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x080000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 1) && (negate_cl == 1)) {
			mdc_clk_div = 2;
			printf("set clause - negate\n", _fmx_reg_write(phy.mdiobus_data, 0x220, ((~clause) & 0xf)));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 122\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x100000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 2) && (negate_cl == 1)) {
			mdc_clk_div = 3;
			printf("set clause - negate\n", _fmx_reg_write(phy.mdiobus_data, 0x220, ((~clause) & 0xf)));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 142\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x180000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		}  else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 3) && (negate_cl == 1)) {
			mdc_clk_div = 4;
			printf("set clause - negate\n", _fmx_reg_write(phy.mdiobus_data, 0x220, ((~clause) & 0xf)));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 162\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x200000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		}  else if ((k % NUM_ITES_PER_MDIO_FREQ_DIV == 0) && (mdc_clk_div == 4) && (negate_cl == 1)) {
			mdc_clk_div = 5;
			printf("set clause - negate\n", _fmx_reg_write(phy.mdiobus_data, 0x220, ((~clause) & 0xf)));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 202\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x280000));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
		} else if (k == tot_ite) {
			printf("ffu execution done\n");
			//Reset Clause to 45 and MDIO frequecy divider to 62.
			printf("set clause - given\n", _fmx_reg_write(phy.mdiobus_data, 0x220, 0x0));
			printf("get clause - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x220));
			printf("set mdio clk div - 62\n", _fmx_reg_write(phy.mdiobus_data, 0x204, 0x0));
			printf("get mdio clk div - %x\n", _fmx_reg_read(phy.mdiobus_data, 0x204));
			//return 0;
		}

//Erase FLASH and make sure it booted from OTP before each iteration.
#if defined(EN_ERASE_FLASH_TO_OTP_BOOT) && EN_ERASE_FLASH_TO_OTP_BOOT
		ret = gpy2xx_read_fw_info(&phy);
		if (ret < 0)
			printf("\nERROR: Reading FW info failed.\n");

		phyId = phy.id;
		if (phyId.fw_memory == FW_EXECUTED_FROM_FLASH
			|| phyId.fw_memory == FW_EXECUTED_FROM_SRAM) {
			printf("Erasing flash ... ");

			ret = gpy2xx_fw_frw_init(&phy, FW_FWR_DEF_TIMEOUT);
			if (ret < 0) {
				printf("api gpy2xx_fw_frw_init failed: %d\n", ret);
				return ret;
			}

			printf("done\n");
			printf("Reset PHY ... ");

			ret = gpy2xx_fw_frw_uninit(&phy);
			if (ret < 0) {
				printf("api gpy2xx_fw_frw_uninit failed: %d\n", ret);
				return ret;
			}

			printf("done\n");
			udelay(1000000u);

			ret = gpy2xx_read(&phy, 30);
			if (ret < 0) {
				printf("reading fw version failed\n");
				return ret;
			}
			printf("erased fw version is 0x%x\n", ret);

			ret = gpy2xx_read(&phy, 17);
			if (ret < 0) {
				printf("reading phy status1 failed\n");
				return ret;
			}
			ret = (ret >> 2) & 0x3;
			printf("memory target used for firmware execution post flash erase is %s\n", (ret ? ((ret == 1) ? "OTP": ((ret == 2) ? "FLASH" : "SRAM")) : "ROM"));
		}
#endif
	}

#if 1 //Test P31GSYS-1670
	ret = gpy2xx_read_fw_info(&phy);
	if (ret < 0)
		printf("\nERROR: Reading FW info failed.\n");

	phyId = phy.id;

	printf("\t%40s:\t0x%x\n", "Firmware Version", ((phyId.fw_release << 15) | (phyId.fw_major << 8) | (phyId.fw_minor)));
	printf("\t%40s:\t0x%x\n", "Firmware Major Version Number", phyId.fw_major);
	printf("\t%40s:\t0x%x\n", "Firmware Minor Version Number", phyId.fw_minor);
	printf("\t%40s:\t0x%x\n", "Firmware Release Indication", phyId.fw_release);
	printf("\t%40s:\t%s\n", "The memory target used for firmware execution", (phyId.fw_memory ? ((phyId.fw_memory == 1) ? "OTP": ((phyId.fw_memory == 2) ? "FLASH" : "SRAM")) : "ROM"));
#endif

	close(mdio.fd);
	return ret;
}
