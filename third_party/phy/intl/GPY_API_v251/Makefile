#
# Makefile for GPY211 PHY
#

EXTRA_CFLAGS  = -DLOG_SEVERITY_MAX=1
EXTRA_CFLAGS += -DP31G_B0=1 -DSAFE_C_LIB=0
EXTRA_CFLAGS += -DDEBUG_PRINT=1 -DREG_RD_PRINT=0 -DREG_WR_PRINT=0
EXTRA_CFLAGS += -DNO_TARGET_TEST=1 -DENABLE_ON_TARGET=0 -DEN_BACKWARD_COMP_API=0
EXTRA_CFLAGS += -I$(src) -I$(src)/src/inc -I$(src)/src/os/linux
EXTRA_CFLAGS += -I$(src)/ISC-DDK-160-BSD_v2.3/SafeXcel-IP-160_DDK_v2.3/Kit/SABuilder_MACsec/Example_AES/incl

obj-$(CONFIG_INTEL_GPY211_PHY) += gpy211.o
gpy211-objs += src/api/phy/gpy211_phy.o
gpy211-objs += src/api/phy/gpy211_chip.o
gpy211-objs += src/api/gmac/gpy211_gmac.o
gpy211-objs += src/api/macsec/gpy211_macsec.o
gpy211-objs += example/macsec_driver/gpy211_gennl.o
gpy211-objs += example/macsec_driver/gpy211_driver.o
gpy211-objs += ISC-DDK-160-BSD_v2.3/SafeXcel-IP-160_DDK_v2.3/Kit/SABuilder_MACsec/Example_AES/src/aes.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
