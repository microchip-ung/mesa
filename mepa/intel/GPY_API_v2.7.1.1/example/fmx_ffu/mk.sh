#!/bin/bash

if [[ "clean" = "$1" ]]; then
	rm -f *.o libgpy2xx_static.a libgpy2xx_dynamic.so
	rm -f p31g_fmx_ffu
	exit 0
fi

if [[ "lib" = "$1" ]]; then
	LOG_CFLAGS="-DLOG_SEVERITY_MAX=0 -DLOGM_IN_FILE=0 -DEN_GMAC_DEBUG_ACCESS=0 -DEN_MSEC_DEBUG_ACCESS=0"
fi

export STAGING_DIR=/local/gmudepa/fmx/ugw/ugw_sw/openwrt/staging_dir
COMPILER_PREFIX=${STAGING_DIR}/toolchain-mips_24kc+nomips16_gcc-8.3.0_musl/bin/mips-openwrt-linux-
#COMPILER_PREFIX=/home/xul/workspace/buildroot/gpy2xx_fmx/output/host/bin/mips-linux-
GCC="${COMPILER_PREFIX}gcc"
AR="${COMPILER_PREFIX}ar"

#UART_FLAG="-DP31G_UART=1 -DRAPID_UART=1 -DPC_UTILITY=1"
EN_API_FLAG="-DEN_MSEC_DEPRECATED_API=0 -DSUPPORT_MACSEC_VLAN=0 -DEN_GMAC_DEBUG_ACCESS=1 -DEN_MSEC_DEBUG_ACCESS=1 -DEN_REPROGM_MISSING_4B=0 -DTEST_ALL_ZERO_IMAGE=0 -DEN_EXEC_TIME_PER_MDIO_FREQ=0 -DEN_ERASE_FLASH_ONLY_TEST=0 -DEN_USER_CHOICE=0 -DEN_TEST_REG_READ_WRITE=0 -DEN_ERASE_FLASH_TO_OTP_BOOT=0"
OPTINAL_TFLAGS="${LOG_CFLAGS} ${EN_API_FLAG} -DP31G_OPT_SPEED=0 -DEN_SMDIO_RW=1 -DP31G_B0=1 -DSAFE_C_LIB=0 -DREG_RD_PRINT=0 -DREG_WR_PRINT=0 -DEN_BACKWARD_COMP_API=0 -Wno-format -Wno-format"

CUR_DIR=`pwd`
PC_TOOL=`pwd`/../..
GPY211_INC=${PC_TOOL}/src/inc
PHY_SRC=${PC_TOOL}/src/api/phy
GMAC_SRC=${PC_TOOL}/src/api/gmac
MACSEC_SRC=${PC_TOOL}/src/api/macsec
DDKAES_SRC=${PC_TOOL}/ISC-DDK-160-BSD_v2.3/SafeXcel-IP-160_DDK_v2.3/Kit/SABuilder_MACsec/Example_AES/src
DDKAES_INC=${PC_TOOL}/ISC-DDK-160-BSD_v2.3/SafeXcel-IP-160_DDK_v2.3/Kit/SABuilder_MACsec/Example_AES/incl

ALL_INC="-I../../src/os/linux -I${GPY211_INC}"

#static library creation
#echo ${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c "${PHY_SRC}/gpy211_phy.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c -o gpy211_phy_static.o "${PHY_SRC}/gpy211_phy.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c -o gpy211_chip_static.o "${PHY_SRC}/gpy211_chip.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c -o gpy211_macsec_static.o "${MACSEC_SRC}/gpy211_macsec.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all -I${DDKAES_INC} ${ALL_INC} -c -o aes_static.o "${DDKAES_SRC}/aes.c"
${AR} rcs libgpy2xx_static.a gpy211_phy_static.o gpy211_chip_static.o gpy211_macsec_static.o aes_static.o

#dynamic library creation
#${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c -fPIC -o gpy211_phy.o "${PHY_SRC}/gpy211_phy.c"
#${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c -fPIC -o gpy211_chip.o "${PHY_SRC}/gpy211_chip.c"
#${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c -fPIC -o gpy211_macsec.o "${MACSEC_SRC}/gpy211_macsec.c"
#${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all -I${DDKAES_INC} ${ALL_INC} -c -fPIC -o aes.o "${DDKAES_SRC}/aes.c"
#${AR} rcs libgpy2xx_api.a gpy211_phy.o gpy211_chip.o gpy211_macsec.o aes.o
#${GCC} -shared -o libgpy2xx_dynamic.so gpy211_phy.o gpy211_chip.o gpy211_macsec.o aes.o

if [[ "lib" != "$1" ]]; then
	${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} gpy2xx_fw_dl.c -L. -lgpy2xx_static -o p31g_fmx_ffu
fi

rm -f *.o *.a
