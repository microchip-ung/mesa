#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <gpy211.h>

#include "lantiq_gsw.h"
#include "mac_ops.h"

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

static unsigned int g_mdio_rd_cnt = 0;
static unsigned int g_mdio_wr_cnt = 0;

static struct gpy211_device phy = {
	NULL, // callback func pointer for 'lock'
	NULL, // callback func pointer for 'unlock'
	NULL, // pointer to lock_data
	gpy211_mdio_read, // callback func pointer for 'mdio_read'
	gpy211_mdio_write, // callback func pointer for 'mdio_write'
	&mdio, // pointer to mdio_data
	0x07, // smdio_addr
	0x1F, // phy_addr
	NULL, // pointer to priv_data
	NULL, // pointer to shared_data
	{0},  // PHY ID
	{0},  // Link data
	0x60, // WOL support
	0,
	NULL,
	NULL,
};

static int gpy211_mdio_read(void *busdata, u16 phyaddr, u32 regnum)
{
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;
	GSW_MAC_Cli_t param = {0};
	u16 _reg_num, _dev_id;

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

	g_mdio_rd_cnt++;
	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static int gpy211_mdio_write(void *busdata, u16 phyaddr, u32 regnum, u16 data)
{
	struct gpy2xx_mdio *priv = (struct gpy2xx_mdio *)busdata;
	GSW_MAC_Cli_t param = {0};
	u16 _reg_num, _dev_id;

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

	g_mdio_wr_cnt++;
	return ioctl(priv->fd, GSW_XGMAC_CFG, &param);
}

static void print_ver(struct gpy211_id *pid)
{
	printf("======== Version ========\n");
	printf("OUI:          0x%08x\n", pid->OUI);
	printf("Model No.:    0x%02x\n", pid->model_no);
	printf("Revision:     0x%02x\n", pid->revision );

	printf("Manufacturer: 0x%04x\n", pid->manufacturer_id);
	printf("Part No.:     0x%04x\n", pid->part_no);
	printf("Version:      0x%04x\n", pid->version);

	printf("FW Major No.: %u\n", (u32)pid->fw_major);
	printf("FW Minor No.: %u\n", (u32)pid->fw_minor);
	printf(pid->fw_release ? "Released Version\n" : "Test Version\n");
	printf("=========================\n");
}

static int fw_fast_write(char *fw_path)
{
	int ret;
	FILE *fwin;
	u32 filesize;
	u32 addr;
	u8 buf[256];
	u32 wrsize;

	fwin = fopen(fw_path, "rb");
	if (fwin == NULL) {
		printf("Failed in FW file \"%s\".\n", fw_path);
		return -errno;
	}
	fseek(fwin, 0L, SEEK_END);
	filesize = ftell(fwin);
	printf("FW size: %u\n", filesize);
	rewind(fwin);

	printf("Init GPHY ... ");
	fflush(stdout);
	ret = gpy2xx_init(&phy);
	if (ret < 0) {
		printf("failed\n");
		fclose(fwin);
		return ret;
	}
	printf("done\n");
	print_ver(&phy.id);

	printf("Erasing ... ");
	fflush(stdout);
	ret = gpy2xx_fw_frw_init(&phy, FW_FWR_DEF_TIMEOUT);
	if (ret < 0) {
		printf("failed\n");
		fclose(fwin);
		return ret;
	} else
		printf("done\n");

	printf("Programming ");
	fflush(stdout);
	addr = 0;
	while (filesize > 0) {
		memset(buf, 0, sizeof(buf));
		wrsize = min(filesize, sizeof(buf));
		ret = fread(buf, 1, wrsize, fwin);
		if (ret <= 0) {
			printf("read fail: %d\n", ret);
			fclose(fwin);
			return -errno;
		}
		if (ret != wrsize) {
			printf("read 256 bytes fail: %d\n", ret);
			fclose(fwin);
			return -errno;
		}


		ret = gpy2xx_fw_fwr_page(&phy, buf, FW_FWR_DEF_TIMEOUT);
		if (ret < 0) {
			printf("page program fail: %d\n", ret);
			fclose(fwin);
			return ret;
		}
		printf(".");
		fflush(stdout);

		filesize -= wrsize;
		addr += wrsize;
	}
	printf(" done\n");

	printf("Reset PHY ... ");
	fflush(stdout);
	ret = gpy2xx_fw_frw_uninit(&phy);
	if (ret < 0) {
		printf("failed\n");
		fclose(fwin);
		return ret;
	}
	printf("done\n");

	fclose(fwin);
	return 0;
}

int main(int argc, char **argv)
{
	const char *gsw_dev = "/dev/switch_api/0";
	char *fw_path = NULL;
	int i, j;
	int ret;

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
		}
	}

	if (fw_path == NULL) {
		printf("gpy2xx_fw_dl [fw] <fw binary> [XGMAC (2)] [phy address (0x1F)]\n");
		return -1;
	} else if (mdio.xgmac_id < 2 || mdio.xgmac_id > 3) {
		printf("Falcon-Mx support MDIO on XGMAC 2 and 3 only\n");
		return -1;
	} else if (phy.phy_addr > 0x1f) {
		printf("Invalid PHY address %u (range 0~31)\n", (u32)phy.phy_addr);
		return -1;
	}

	mdio.fd = open(gsw_dev, O_RDONLY);
	if (mdio.fd < 0) {
		printf("Can't open GSW API device node \"%s\"\n", gsw_dev);
		return -1;
	}

	ret = fw_fast_write(fw_path);
	printf("g_mdio_rd_cnt = %d\n", g_mdio_rd_cnt);
	printf("g_mdio_wr_cnt = %d\n", g_mdio_wr_cnt);

	close(mdio.fd);
	return ret;
}
