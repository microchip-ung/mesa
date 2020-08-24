#!/bin/bash

if [[ "clean" = "$1" ]]; then
	rm -f *.o libgpy2xx_api.a
	rm -f p31g_fwdl
	exit 0
fi

if [[ "lib" = "$1" ]]; then
	LOG_CFLAGS="-DLOG_SEVERITY_MAX=0 -DLOGM_IN_FILE=0 -DEN_GMAC_DEBUG_ACCESS=0 -DEN_MSEC_DEBUG_ACCESS=0"
fi

export STAGING_DIR=/local/liangxu1/ugw/ugw_fmx/ugw_sw/openwrt/staging_dir
COMPILER_PREFIX=${STAGING_DIR}/toolchain-mips_24kc+nomips16_gcc-5.5.0_musl/bin/mips-openwrt-linux-
#COMPILER_PREFIX=/home/xul/workspace/buildroot/gpy2xx_fmx/output/host/bin/mips-linux-
GCC="${COMPILER_PREFIX}gcc"
AR="${COMPILER_PREFIX}ar"

#UART_FLAG="-DP31G_UART=1 -DRAPID_UART=1 -DPC_UTILITY=1"
OPTINAL_TFLAGS="${LOG_CFLAGS} -DP31G_OPT_SPEED=0 -DEN_SMDIO_RW=0 -DP31G_B0=1 -DSAFE_C_LIB=0 -DREG_RD_PRINT=0 -DREG_WR_PRINT=0 -DEN_BACKWARD_COMP_API=0"

CUR_DIR=`pwd`
PC_TOOL=`pwd`/../..
GPY211_INC=${PC_TOOL}/src/inc
PHY_SRC=${PC_TOOL}/src/api/phy
GMAC_SRC=${PC_TOOL}/src/api/gmac
MACSEC_SRC=${PC_TOOL}/src/api/macsec
DDKAES_SRC=${PC_TOOL}/ISC-DDK-160-BSD_v2.3/SafeXcel-IP-160_DDK_v2.3/Kit/SABuilder_MACsec/Example_AES/src
DDKAES_INC=${PC_TOOL}/ISC-DDK-160-BSD_v2.3/SafeXcel-IP-160_DDK_v2.3/Kit/SABuilder_MACsec/Example_AES/incl

ALL_INC="-I../../src/os/linux -I${GPY211_INC}"

#echo ${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c "${PHY_SRC}/gpy211_phy.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c "${PHY_SRC}/gpy211_phy.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c "${PHY_SRC}/gpy211_chip.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c "${GMAC_SRC}/gpy211_gmac.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} -c "${MACSEC_SRC}/gpy211_macsec.c"
${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all -I${DDKAES_INC} ${ALL_INC} -c "${DDKAES_SRC}/aes.c"
${AR} rcs libgpy2xx_api.a gpy211_phy.o gpy211_chip.o gpy211_gmac.o gpy211_macsec.o aes.o

if [[ "lib" != "$1" ]]; then
	#${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} user_uart_interface.c gpy2xx_utility.c -L. -lgpy2xx_api -o p31g_util
	${GCC} ${UART_FLAG} ${OPTINAL_TFLAGS} -Wall -fstack-protector-all ${ALL_INC} gpy2xx_fw_dl.c -L. -lgpy2xx_api -o p31g_fwdl
fi
