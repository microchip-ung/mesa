/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <string.h>
#include <dirent.h>
#include <errno.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "meba_aux.h"

#define SPI_SET_ADDRESS      0x00
#define SPI_WRITE            0x40
#define SPI_READ             0x80

mesa_rc meba_synce_spi_if_spi_transfer(meba_inst_t inst, uint32_t buflen, const uint8_t *tx_data, uint8_t *rx_data)
{
    struct spi_ioc_transfer spi_xfer;
    int timeout_count = 0;

    // Check if SyncE SPI interface is available. If not, find and open the spidev device that corresponds to the SyncE DPLL chip
    if (inst->synce_spi_if_fd < 0) {
        return MESA_RC_ERROR;
    }

    memset(&spi_xfer, 0, sizeof(spi_xfer));
    spi_xfer.delay_usecs = 1;
    spi_xfer.tx_buf = (uintptr_t) tx_data;
    spi_xfer.rx_buf = (uintptr_t) rx_data;
    spi_xfer.len = buflen;
    while (ioctl(inst->synce_spi_if_fd, SPI_IOC_MESSAGE(1), &spi_xfer) == -1) {
        int errsv = errno;
        if (errsv == EBUSY) {
            usleep(10 * 1000);
            if (++timeout_count % 100 == 0) {
                T_E(inst, "Has been waiting %d second(s) for access to SPI IF.", (timeout_count / 100));
            }
            if (timeout_count == 1000) {
                T_E(inst, "Timeout while waiting for access to SPI IF (giving up now after waiting 10 seconds).");
            }
        } else {
            T_E(inst, "Got unexpected error code (errno = %d) from SPI ioctl call.", errsv);
//            T_E(inst, "buflen = %u, tx_data = %u, rx_data = %u", buflen, (uintptr_t) tx_data, (uintptr_t) rx_data);
            break;
        }
    }
    return MESA_RC_OK;
}

static meba_synce_clock_hw_id_t known_dpll_type;

/* Do DPLL type detection*/
mesa_rc meba_synce_spi_if_do_dpll_type_detection(meba_inst_t inst, const char *dpll_id)
{
    mesa_rc rc = MESA_RC_OK;
    char synce_spi_file[32];

    uint8_t partnum[3];

    if (meba_synce_spi_if_find_spidev(inst, dpll_id, synce_spi_file, MEBA_ARRSZ(synce_spi_file)) != MESA_RC_OK) {
        return MESA_RC_ERROR;
    }

    inst->synce_spi_if_fd = open(synce_spi_file, O_RDWR);
    if (inst->synce_spi_if_fd < 0) {
        inst->synce_spi_if_fd = -1;
        T_D(inst, "Could not open SPI device file %s", synce_spi_file);
        return MESA_RC_ERROR;
    }

    T_D(inst, "Opened SPI device file %s.", synce_spi_file);

    // Initially assume that no DPLL is present
    known_dpll_type = MEBA_SYNCE_CLOCK_HW_NONE;

    // Write a 0 to the page register (Zarlink 30363) to make sure the page with the Chip-ID register is selected.
    // We do this in all cases, also when support for this DPLL is not compiled in. This is to make sure that a
    // 30363 device cannot be mistaken for a 30343 or for a Silabs 5326/5328
    {
        uint8_t tx_data[2] = {0x7F, 0};
        uint8_t rx_data[2];
        if (meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data) != MESA_RC_OK) {
            T_I(inst, "Could not do SPI transfer to DPLL. Most likely the board does not support a SyncE DPLL.");
            return MESA_RC_ERROR;
        }
    }

    // First try to read the chip ID of a Silabs 5326/5328.
    //
    // If the device is actually a Zarlink 30343 or 30363 this will be seen twice as a write to the Chip-ID register (which will have no effect as this register is read-only) then
    // followed by a read from the chip ID register. That is, if the device is a Zarlink, the chip ID of 30343 is in partnum[0], 30363 in partnum[1], 3077x in partnum[1] & partnum[2].
    //

    // Assuming DPLL is a Silabs 5326/5328, set the address to 134
    {
        uint8_t tx_data[2] = {SPI_SET_ADDRESS, 134};
        uint8_t rx_data[2];
        meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data);
        tx_data[0] = SPI_READ;
        tx_data[1] = 0;
        meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data);  /* Try if Silabs 5326 is on SPI */
        partnum[0] = rx_data[1];
    }

    // Assuming DPLL is a Silabs 5326/5328, set the address to 135
    {
        uint8_t tx_data[2] = {SPI_SET_ADDRESS, 135};
        uint8_t rx_data[2];
        meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data);
        tx_data[0] = SPI_READ;
        tx_data[1] = 0;
        meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data);  /* Read part number to detect if this is a Silabs 5326 or 5328 */
        partnum[1] = rx_data[1];
    }
    mesa_bool_t si5326 = ((partnum[0] == 0x01) && (((partnum[1] & 0xF0) == 0xA0) || ((partnum[1] & 0xF0) == 0xC0)));
    mesa_bool_t si5328 = ((partnum[0] == 0x01) && ((partnum[1] & 0xF0) == 0xC0));

    // If the DPLL chip was not detected as a Silabs 5326/5328 then test if it is a Zarlink 30343 or 30363.
    if (!si5326) {
        // We need to wait 25 ms to be sure that we can read the chip ID from the 30363. This is because the probe for the si5326 above has written to address 0x01 and if the
        // device indeed is a 30363 then it will take up to 25 ms before this address again contains the correct chip ID.
        usleep(25000);
        // Assuming DPLL is a zls30343 or zls30363, read address 0
        {
            uint8_t tx_data[2] = {0x80, 0};
            uint8_t rx_data[2];
            meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data);
            partnum[0] = rx_data[1];
        }
        // Assuming DPLL is a zls30343 or zls30363, read address 1
        {
            uint8_t tx_data[2] = {0x81, 0};
            uint8_t rx_data[2];
            meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data);
            partnum[1] = rx_data[1];
        }
        if ((partnum[0] & 0x1F) == 0x0C || (partnum[0] & 0x1F) == 0x0D) {
            // Device is a 30343
            T_I(inst, "Zarlink 30343 detected.");
            if (MESA_CAP(MESA_CAP_MISC_CHIP_FAMILY) == MESA_CHIP_FAMILY_SERVALT) {
                T_E(inst, "ZLS30343 DPLL detected, but only ZLS30363 is supported on this board.");
                known_dpll_type = MEBA_SYNCE_CLOCK_HW_NONE;
                rc = MESA_RC_ERROR;
            } else {
                known_dpll_type = MEBA_SYNCE_CLOCK_HW_ZL_30343;
            }
        } else if (partnum[1] == 0x3F) {
            // Device is a 30363
            T_I(inst, "Zarlink 30363 detected.");
            known_dpll_type = MEBA_SYNCE_CLOCK_HW_ZL_30363;
        } else if (partnum[1] == 0x0E) {
            uint8_t tx_data[2] = {0x82, 0};
            uint8_t rx_data[2];
            meba_synce_spi_if_spi_transfer(inst, 2, tx_data, rx_data);
            partnum[2] = rx_data[1];
            if (partnum[2] == 0xBB) {
                known_dpll_type = MEBA_SYNCE_CLOCK_HW_ZL_30771;
            } else if (partnum[2] == 0xBC) {
                known_dpll_type = MEBA_SYNCE_CLOCK_HW_ZL_30772;
            } else if (partnum[2] == 0xBD) {
                known_dpll_type = MEBA_SYNCE_CLOCK_HW_ZL_30773;
            } else {
                T_I(inst, "No SyncE DPLL detected. with partnum 0X%x%x", partnum[1], partnum[2]);
                rc = MESA_RC_ERROR;
            }
            if (rc != MESA_RC_ERROR) {
                T_I(inst, "Zarlink 30377X detected with partnum 0X%x%x", partnum[1], partnum[2]);
            }
        } else {
            T_I(inst, "No SyncE DPLL detected. partnum 0X%x%x", partnum[0], partnum[1]);
            rc = MESA_RC_ERROR;
        }
    } else {
        T_I(inst, "Silabs 5326/5328 detected.");
        if (si5328) {
            known_dpll_type = MEBA_SYNCE_CLOCK_HW_SI_5328;
        } else {
            known_dpll_type = MEBA_SYNCE_CLOCK_HW_SI_5326;
        }
    }

    return rc;
}

/* Detect DPLL type */
mesa_rc meba_synce_spi_if_get_dpll_type(meba_inst_t inst, meba_synce_clock_hw_id_t *dpll_type)
{
    static mesa_bool_t already_known = false;
    mesa_rc rc = MESA_RC_OK;
    if (!already_known) {

        if ((MESA_CAP(MESA_CAP_MISC_CHIP_FAMILY) == MESA_CHIP_FAMILY_SERVALT) && MESA_CAP(MESA_CAP_CLOCK)) {
            T_I(inst, "Using ServalT's builtin DPLL for SyncE.");
            known_dpll_type = MEBA_SYNCE_CLOCK_HW_OMEGA;
            goto known_dpll;
        } else {
            // Check for presence of external dpll
            if ((rc = meba_synce_spi_if_do_dpll_type_detection(inst, "synce_dpll")) == MESA_RC_OK) {
                goto known_dpll;
            }
            close(inst->synce_spi_if_fd);

            // Check for presence of builtin dpll
            if ((rc = meba_synce_spi_if_do_dpll_type_detection(inst, "synce_builtin")) == MESA_RC_OK) {
                goto known_dpll;
            }
            close(inst->synce_spi_if_fd);
            known_dpll_type = MEBA_SYNCE_CLOCK_HW_NONE;
            rc = MESA_RC_OK;
        }
    }
known_dpll:
    already_known = true;
    *dpll_type = known_dpll_type;

    return rc;
}

mesa_rc meba_synce_spi_if_find_spidev(meba_inst_t inst, const char *id, char *spi_file, size_t max_size)
{
    // Find the spidev device that corresponds to the CPLD
    DIR *dp;
    struct dirent *ep;
    int match = 0;

    dp = opendir ("/sys/bus/spi/devices/");
    if (dp == NULL) {
        T_E(inst, "Could not read the /dev directory");
        return MESA_RC_ERROR;
    }

    while (!match && (ep = readdir(dp))) {
        // Open "function" file in sysfs filesystem to determine if this SPI device has function given by id parameter
        char filename[300];
        char function[32];

        snprintf(filename, sizeof(filename), "/sys/bus/spi/devices/%s/function", ep->d_name);
        int function_fd = open(filename, O_RDONLY);
        if (function_fd < 0) {
            snprintf(filename, sizeof(filename), "/sys/bus/spi/devices/%s/modalias", ep->d_name);
            function_fd = open(filename, O_RDONLY);
            if (function_fd < 0) {
                continue;
            }
        }

        int num_read;
        if ((num_read = read(function_fd, function, MEBA_ARRSZ(function) - 1)) <= 0) {
            goto CLOSE;
        } else {
            function[num_read] = 0;  // String needs to be zero-terminated.
        }

        if (strstr(function, id) != 0) {
            match = 1;
        }

CLOSE:
        close(function_fd);
    }
    (void) closedir (dp);

    if (!match) {
        T_I(inst, "Could not locate the SPI device with function %s", id);
        return MESA_RC_ERROR;
    }

    if (strnlen(ep->d_name, sizeof(ep->d_name)) < 4) {
        T_E(inst, "Unexpected SPI device number: %s", ep->d_name);
        return MESA_RC_ERROR;
    }

    snprintf(spi_file, max_size, "/dev/spidev%s", &ep->d_name[3]);
    spi_file[max_size - 1] = 0;

    return MESA_RC_OK;
}
