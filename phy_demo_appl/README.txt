
The 1G PHY has several flavors, all are supported by the Unified PHY API,
However, in order to reduce the API footprint, there are options to omit
features which some of the PHY's do not support.

To include 1588, define: VTSS_OPT_PHY_TIMESTAMP 
  - Includes the files in the "ts" directory
To include MACSEC, define: VTSS_FEATURE_MACSEC 
  - Includes the files in the "macsec" directory

To Build a library for the 1G PHY:
make -f Makefile_1g

To Build a library for the 10G PHY:
make -f Makefile_10g

To exercise the Standalone PHY and the PHY API,
The following PHY Evaluation board description files exist for this program:
vtss_api/appl/vtss_appl_board_tesla_eval.c
vtss_api/appl/vtss_appl_board_atom12_eval.c
vtss_api/appl/vtss_appl_board_elise_eval.c
vtss_api/appl/vtss_appl_board_nano_eval.c
vtss_api/appl/vtss_appl_board_viper_eval.c

The Demo Application, vtss_appl_cu_phy.c, must be compiled for only one of these boards at any one time.
There are a number of #defines in each build file.
These defines are used to configure the software appropriately for the given Hardware and the Application capabilities.
An example is MACSEC and 1588.
The VSC8574 and VSC8584 families support 1588.  VSC8574 supports generation_1 and VSC8584 supports generation_2.
Both of these families could have the -DVTSS_OPT_PHY_TIMESTAMP enabled if the application supports it.
The VSC8584 family supports MACSEC, therefore this family could have -DVTSS_FEATURE_MACSEC enabled.

## Available Defines:
##  -DVTSS_OPSYS_LINUX=1
##  -DVTSS_OPT_PORT_COUNT=4
##  -DVTSS_CHIP_CU_PHY
##  -DVIPER_EVAL_BOARD
##  -DVTSS_OPT_PHY_TIMESTAMP
##  -DVTSS_FEATURE_MACSEC
##  -DVTSS_FEATURE_EEE
##  -DVTSS_SW_OPTION_EEE
##  -D_INCLUDE_DEBUG_FILE_PRINT_
##  -D_INCLUDE_DEBUG_TERM_PRINT_
##  -DVTSS_SW_OPTION_DEBUG
##  -DVTSS_PHY_OPT_CAP_FE_ONLY
##  -DVTSS_PHY_OPT_CAP_GE_ONLY
##  -DVTSS_FEATURE_SERDES_MACRO_SETTINGS


The General Description of the steps are:

./build_aaaaaa_vscxxxxev       (where aaaaaa = family name, xxxx = model)
./vtss_api_aaaaaa_vscxxxxev  www.xxx.yyy.zzz    (where www.xxx.yyy.zzz is the ip_addr for the eval board)


To compile the Demo Application, perform the following steps for the appropriate evaluation platform:

for Atom12 family (VSC8522, etc):
./build_atom12_vsc8522ev.sh
This will create a vtss_api_atom12_vsc8522ev executable file, which takes 1 argument as input, the ip_addr of the evalutaion board.
To execute: ./vtss_api_atom12_vsc8522ev www.xxx.yyy.zzz  (where: www.xxx.yyy.zzz is the ip_addr for the eval board)

for Tesla family (VSC8574, etc):
./build_tesla_vsc8574ev.sh
This will create a vtss_api_tesla_vsc8574ev executable file, which takes 1 argument as input, the ip_addr of the evalutaion board.
To execute: ./vtss_api_tesla_vsc8574ev www.xxx.yyy.zzz  (where: www.xxx.yyy.zzz is the ip_addr for the eval board)

for Elise family (VSC8514, etc):
./build_elise_vsc8514ev.sh
This will create a vtss_api_elise_vsc8514ev executable file, which takes 1 argument as input, the ip_addr of the evalutaion board.
To execute: ./vtss_api_elise_vsc8514ev www.xxx.yyy.zzz  (where: www.xxx.yyy.zzz is the ip_addr for the eval board)

for Nano family (VSC8502, etc):
./build_nano_vsc8502ev.sh
This will create a vtss_api_nano_vsc8502ev executable file, which takes 1 argument as input, the ip_addr of the evalutaion board.
To execute: ./vtss_api_nano_vsc8502ev www.xxx.yyy.zzz  (where: www.xxx.yyy.zzz is the ip_addr for the eval board)

for Viper family (VSC8584, etc):
./build_viper_vsc8584ev.sh
This will create a vtss_api_viper_vsc8584ev table file, which takes 1 argument as input, the ip_addr of the evalutaion board.
To execute: ./vtss_api_viper_vsc8584ev www.xxx.yyy.zzz  (where: www.xxx.yyy.zzz is the ip_addr for the eval board)


