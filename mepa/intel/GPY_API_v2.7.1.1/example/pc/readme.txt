Project
===============================================================================
The GPY211 is a Gigabit Ethernet (GbE) Ethernet Network Connection device
with one Ethernet PHY, supporting speeds of 10, 100, 1000 and 2500 Mbps.
It also supports a four-speed (10/100/1000/2500 Mbps) SGMII interface for
connecting with an external chip.

Starting
===============================================================================
These instructions will get you a copy of the project files,
compile and running on your local machine for development and testing purposes.

Prerequisites
===============================================================================
Windows PC, with FTDI's D2XX driver installed to control DUT via UART interface.
The FTDI's D2XX drivers allow direct access to the USB device through a DLL.
Please see 'Installing' below for downloading driver and steps to install them.

Installing
===============================================================================
1.Goto URL http://www.ftdichip.com/Drivers/D2XX.htm
2.Look for 'setup executable' and click on 'setup executable' hyper link under
  section 'Currently Supported D2XX Drivers:' to download the driver.
3.Extract .zip, double-click on .exe file, finish install with correct options.
4.Reboot the windows PC once D2XX drivers installation completed.
5.Now you are ready to control P31G DUT via UART from windows PC.
6.Connect a serial cable from PC's USB port to DUT's microUSB port, note down
  the four new ports that appeared under PC's Device Manager -> Ports as shown
  'USB Serial Port (COMxx)' and each of them are used for:
  USB Serial Port (COMxx) -> HW Reset of P31G
  USB Serial Port (COMxx + 1) -> F24S's UART Data Output/Input
  USB Serial Port (COMxx + 2) -> P31G's UART Data Output/Input
  USB Serial Port (COMxx + 3) -> Firmware UART Data Output
7.Please see 'Running' below for code pulling, compiling and running tests.

Running
===============================================================================
1.Pull the branch:
  git clone ssh://git@gts-chd.intel.com:29418/sw_tcbootrom/gpy_api.git
  cd gpy_api
  git checkout P31G_B0_Step
2.Compile code
  Goto directory 'gpy_api/GPY211/utility' and double-click on 'build_p31g.bat'
3.Successful compilation should result in generating an executable file
  'p31g_util.exe' in the current directory.
4.Run the generated PC tool as below:
  p31g_util.exe -p <comport> -b <baudrate> -a <phyaddr> -d <dutid> -u <ucdis>
  where:
  comport -> comports of DUTs (F24S or P31G) found at step 6 in 'Installing'.
  baudrate -> baudrate of supported (4800, 9600, 19200, 38400, 57600,
                                     115200, 230400, 460800, 921600)
  phyaddr (optional) -> DUT's PHY address to get/set. <0x0 - 0x1F (default)>
  dutid (optional) -> DUT ID (0 for F24S or 1 for P31G). <0 (default) - 1>
  ucdis (optional) -> Disable bypassing uC8051 if in F24S. <0 (default) - 1>

  Ex:
  p31g_util.exe -p com5 -b 115200 -a 0x00 -d 0
5.Please refer 'GPY211_API_UMPG_Rev1.0.pdf' for detailed API usage test.
  MACsec basic commands to test are given in 'macsec_test_commands.txt'
  These are located at 'gpy_api/GPY211/doc' directory.

Versioning
===============================================================================
For version info, please look for 'TOOL_VERSION' in switch_utility.h file.

Authors
===============================================================================
Govindaiah Mudepalli

License
===============================================================================
This project is licensed under the INTEL License - see the file for details.