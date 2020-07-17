// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h> 
#include <sys/stat.h>
#include<sys/mman.h>
#include <linux/i2c-dev.h>  /* I2C support */
#include <errno.h> 
#include <mscc/ethernet/board/api.h>
#include "../meba_aux.h"
#include "../meba_generic.h"

#define VTSS_MSLEEP(m) usleep((m)*1000)

// Section 4.1. in PD69200 user guide - key definitions
#define COMMAND_KEY                     0x00
#define PROGRAM_KEY                     0x01
#define REQUEST_KEY                     0x02
#define TELEMETRY_KEY                   0x03
#define CHANNEL_KEY                     0x05
#define E2_KEY                          0x06
#define TOTAL_POWER_KEY                 0x60
#define GLBL_KEY                        0x07
#define PRIORITY_KEY                    0x0A
#define SUPPLY_KEY                      0x0B
#define ENABLE_DISABLE_KEY              0x0C
#define PORT_STATUS_KEY                 0x0E
#define TEMPORARY_SUPPLY_KEY            0xA2
#define LLDP_PSE_KEY                    0xA8
#define SAVE_CONFIG_KEY                 0x0F
#define MAIN_KEY                        0x17
#define VERSIONZ_KEY                    0x1E
#define SW_VERSION_KEY                  0x21
#define SET_SYSTEM_MASKS                0x2B
#define RESTORE_FACT_KEY                0x2D
#define TMP_MATRIX_KEY                  0x43
#define BT_LLDP_PD_KEY                  0x50
#define BT_LLDP_PSE_KEY                 0x51
#define REPORT_KEY                      0x52
#define RESET_KEY                       0x55
#define INDIV_MASK_KEY                  0x56
#define POWER_BUDGET_KEY                0x57
#define TOTAL_POWER_KEY                 0x60
#define ACTUAL_SYSTEM_DATA_KEY          0xAD
#define BT_PORT_CONFIG1_KEY             0xC0
#define BT_PORT_STATUS_KEY              0xC1
#define BT_PORT_CLASS_KEY               0xC4
#define BT_PORT_MEASE_KEY               0xC5
#define BT_SYSTEM_STATUS_KEY            0xD0
#define BT_CLASS_PWR_KEY                0xD2

#define PD_BUFFER_SIZE                    15    // All microSemi's access are 15 bytes

// The sequence number is updated by the transmit function, but we have to insert a dummy seq number when building the data structure.
#define DUMMY_SEQ_NUM                   0x00
#define SEQ_NUM_TELEMETRY_AFTER_RESET   0xFF
#define SEQ_NUM_DO_NOT_CHK              0xFF
#define DUMMY_BYTE                      0x4E

#define IGNORE_HIGH_PRIORITY               0
#define CAPACITOR_LEGACY_DETECTION      0x02
#define SUPPORT_HIGH_RES_DETECTION      0x10
#define I2C_RESTART_ENABLE              0x1B
#define LED_STREAM_TYPE                 0x20


#define LINE_SIZE_MAX 100 // PoE firmware file line max size in bytes
#define POE_FIRMWARE_SIZE_MAX 2000000 // Maximum size of the PoE firmware in bytes (file mscc_firmware.txt)

#define MESA_RC(EXPR) { mesa_rc rc = EXPR; if (rc != MESA_RC_OK) { return rc; } }

enum BT_PORT_STATUS_e
{
    //---------------------------------------------------------------------------------------------------------------
    //                                        #  --------- SNMP COUNTERS ---------- #  SNMP Port       #
    //                                        # Absnt # Inv  # Pwr   # Over # Short #  Detection       #
    //                                        # (UDL) # Sig  # Dnied # Load #       #  Status          #
    //---------------------------------------------------------------------------------------------------------------

    //--- Port off ---//
    e0x06_Port_is_off_Main_supply_voltage_is_high     = 0x06,
    e0x07_Port_is_off_Main_supply_voltage_is_low      = 0x07,
    e0x08_Port_is_off_Disable_all_ports_pin_is_active = 0x08,
    e0x0C_Port_is_off_Non_existing_port_number        = 0x0C,
    e0x11_Port_is_yet_undefined                       = 0x11,
    e0x12_Port_is_off_Internal_hardware_fault         = 0x12,
    e0x1A_Port_is_off_User_setting                    = 0x1A,
    e0x1B_ePort_is_off_Detection_is_in_process        = 0x1B,
    e0x1c_Port_is_off_Non_802_3AF_AT_powered_device   = 0x1C,
    e0x1E_Port_is_off_Underload_state                 = 0x1E,
    e0x1F_Port_is_off_Overload_state                  = 0x1F,
    e0x20_Port_is_off_Power_budget_exceeded           = 0x20,
    e0x22_Port_is_off_Configuration_change            = 0x22,
    e0x24_Port_is_off_Voltage_injection_into_the_port = 0x24,
    e0x25_Port_is_off_Improper_Cap_Det_results_or_Det_val_indicating_short = 0x25,
    e0x26_Port_is_off_Discharged_load                 = 0x26,
    e0x34_Port_is_off_Short_condition                 = 0x34,
    e0x35_Port_is_off_Over_temperature_at_the_port    = 0x35,
    e0x36_Port_is_off_Device_is_too_hot               = 0x36,
    e0x37_Unknown_device_port_status                  = 0x37,
    e0x3C_Power_Mng_Static_calc_pwr_exceed_pwr_limit  = 0x3C,
    e0x3D_Power_Management_Static_ovl                 = 0x3D,
    e0x41_Port_is_off_Power_denied_Hardware_power_limit = 0x41,
    e0x43_Port_is_off_Class_Error                      = 0x43,

    e0x44_Port_turn_off_during_host_crash             = 0x44,
    e0x45_Delivering_power_forced_off_during_host_crash = 0x45,
    e0x46_Enabled_port_forced_off_during_host_crash   = 0x46,
    e0x47_Forced_power_crash_error                    = 0x47,
    e0x48_Port_is_off_recovery_UDL                    = 0x48,
    e0x49_Port_is_off_recovery_PG                     = 0x49,
    e0x4A_Port_is_off_recovery_OVL                    = 0x4A,
    e0x4B_Port_is_off_recovery_SC                     = 0x4B,
    e0x4C_Port_is_off_recovery_voltage_injection      = 0x4C,

    //--- Port delivering ---//
    e0x80_2P_Port_delivering_non_IEEE                 = 0x80,
    e0x81_2P_Port_delivering_IEEE                     = 0x81,
    e0x82_4P_Port_that_deliver_only_2_Pair_non_IEEE   = 0x82,
    e0x83_4P_Port_delivering_2P_non_IEEE              = 0x83,
    e0x84_4P_Port_delivering_4P_non_IEEE              = 0x84,
    e0x85_4P_Port_delivering_2P_IEEE_SSPD             = 0x85,
    e0x86_4P_Port_delivering_4P_IEEE_SSPD             = 0x86,
    e0x87_4P_Port_delivering_4P_IEEE_DSPD_1st_phase   = 0x87,
    e0x88_4P_Port_delivering_2P_IEEE_DSPD             = 0x88,
    e0x89_4P_Port_delivering_4P_IEEE_DSPD             = 0x89,
    e0x90_Force_Power_BT_2P                           = 0x90,
    e0x91_Force_Power_BT_4P                           = 0x91,

    //--- Port error ---//
    e0xA0_Force_Power_BT_Error                        = 0xA0,

    //--- Port noral searching ---//
    e0xA7_Connection_Check_error                      = 0xA7,  // normal Ethernet none PD device is connected
    e0xA8_Open_Port_is_not_connected                  = 0xA8,  // Nopthing is conencted to teh Etehrnet port

    eBT_PORT_STATUS_ONKNOWN  = 255 // EZRA - internal NMS soft state which mark that port status was never read and updated
};


int pd69200_wait_time = 50; // Wait 400 ms according to the synchonization descriped in section 7, but from e-mail from Shmulik this can be set to 50 ms.

typedef struct poe_private_cfg_data {
    meba_poe_cfg_t       global;
    meba_poe_port_cfg_t *ports;
} poe_private_cfg_data_t;

typedef struct meba_poe_port_private_status_t {
    mesa_poe_milliwatt_t        requested_power_mode_a;
    mesa_poe_milliwatt_t        requested_power_mode_b;
} meba_poe_port_private_status_t;

typedef struct poe_private_status_data {
    meba_poe_status_t               global;
    meba_poe_port_private_status_t *ports;
} poe_private_status_data_t;

typedef struct poe_driver_private_t {
    poe_private_status_data_t status;
    poe_private_cfg_data_t    cfg;
    meba_debug_t              debug;  /**< Board debug output */
    const char               *builtin_firmware; /**< Path to file with builtin firmware */
} poe_driver_private_t;

#define DEBUG(_inst, _lvl, _fmt, ...) do { ((poe_driver_private_t *)((_inst)->private_data))->debug(_lvl, __FILE__, __LINE__, "(%s) " _fmt, _inst->adapter_name, ##__VA_ARGS__); } while (0)

/*********************
   Local Functions
**********************/
static char *print_as_hex_string(uint8_t *in, int in_size, char *out, int out_size)
{
    int i, s, size_old = out_size;
    char *tmp = out;

    for (i = 0; i < in_size; ++i) {
        s = snprintf(tmp, out_size, "%02hhX ", in[i]);
        tmp += s;
        out_size -= s;

        if (out_size <= 0)
            goto OUT;
    }

OUT:
    out[size_old - 1] = 0;

    return out;
}

int meba_pd69200_i2c_adapter_open(const char *filename, uint8_t i2c_addr)
{
    int file;
    if ((file = open(filename, O_RDWR)) >= 0) {
        if (ioctl(file, I2C_SLAVE, i2c_addr) < 0) {
            printf("cannot specify i2c slave at 0x%02x! [%s]\n", i2c_addr, strerror(errno));
        }
    } else {
        printf("cannot open %s! [%s]\n", filename, strerror(errno));
    }
    return file;
}

// Function for reading data from the MicroSemi micro-controller.
// IN/OUT : Data - Pointer to where to put the read data
// IN     : Size - Number of bytes to read.
static
mesa_rc pd69200_rd(const meba_poe_ctrl_inst_t *const inst,
                   uint8_t *data,
                   char size)
{
    char buf[size * 3 + 1];
    VTSS_MSLEEP(50); // Wait 50ms
    memset(data, 0, size);
    int cnt = read(inst->adapter_fd, data, size);
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Read(%d/%d)  %s ",
          inst->adapter_name, size, cnt,
          print_as_hex_string(data, size, buf, sizeof(buf)));
    return (cnt == size) ? MESA_RC_OK : MESA_RC_ERROR;
}

// Function for writing data from the MicroSemi micro-controller.
// IN  : Data - Pointer to data to write
//     : Size - Number of bytes to write.
static
mesa_rc pd69200_wr(const meba_poe_ctrl_inst_t *const inst,
                   uint8_t *data,
                   char size)
{
    char buf[size * 3 + 1];
    int cnt = write(inst->adapter_fd, data, size);
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Wrote %s ",
          inst->adapter_name,
          print_as_hex_string(data, size, buf, sizeof(buf)));
    return (cnt == size) ? MESA_RC_OK : MESA_RC_ERROR;
}


// Function for reading data from the MicroSemi micro-controller.
// IN/OUT : Data - Pointer to where to put the read data
// IN     : Size - Number of bytes to read.
mesa_rc pd69200_firm_update_rd(const meba_poe_ctrl_inst_t *const inst, uint8_t *data, char size)
{
    mesa_rc rc = MESA_RC_OK;
    int loop_number = 0;
    do
    {
        rc = read(inst->adapter_fd, data, 1);

        if (rc == MESA_RC_ERROR)
        {
            printf("return error1:%d\n\r", rc);
            return rc;
        }

        if (data[0] == 0)
        {
            VTSS_MSLEEP(5);
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "read again:%d", loop_number);
        }
        loop_number++;
    }
    while ((data[0] == 0) && (loop_number < 40));

    if (data[0] == 0)
        return rc;

    rc = read(inst->adapter_fd, &(data[1]), size-1);

    if (rc == MESA_RC_ERROR)
    {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "error2:%d", rc);
    }

    return rc;
}


static
void meba_poe_pd69200_set_chipset(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_chip_state_t  chip_state)
{
    meba_poe_status_t *current_status = 
            &(((poe_driver_private_t *)(inst->private_data))->status.global);

    current_status->chip_state = chip_state;
}

static
meba_poe_chip_state_t meba_poe_pd69200_get_chipset(
    const meba_poe_ctrl_inst_t     *const inst)
{
    if (inst == NULL || inst->private_data == NULL) {
        return MEBA_POE_NO_CHIPSET_FOUND;
    }

    meba_poe_status_t *current_status = 
            &(((poe_driver_private_t *)(inst->private_data))->status.global);

    return current_status->chip_state;
}

// Something went wrong, we should do synchronization. We do not do as described in section 7 in the userguide. Instead
// microSemi has suggested that we simply wait more than 10 sec. After 10 sec. the I2C buffer is flushed, and we do not have
// to do a reset of the PoE chip, which microSemi didn't like. We only do the wait once.
// The above suggestion from microsemi didn't work, so the workaround below is used instead.
static mesa_rc meba_poe_pd69200_sync(const meba_poe_ctrl_inst_t *const inst)
{
    uint8_t buf[PD_BUFFER_SIZE];
    uint8_t timeout;
    char charbuf[PD_BUFFER_SIZE*4];

    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Driver instance %s not found", inst->adapter_name);
        return MESA_RC_OK;
    }
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Syncing driver instance: %s", inst->adapter_name);

    VTSS_MSLEEP(10000); // Wait at least 10 sec in order to reset i2c system. See Section 8.2 MASK Registers list in "PD69200 Serial Communication Protocol User Guide"

    // Do dummy reads to insure that the i2c is in fact empty now.
    for (timeout = PD_BUFFER_SIZE * 4; timeout > 0; timeout --) {
        if (pd69200_rd(inst, buf, PD_BUFFER_SIZE) == MESA_RC_OK) {
            uint8_t zero_buf[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            if (memcmp(zero_buf, buf, PD_BUFFER_SIZE) == 0) {
                // Empty I2C buffer in controller, just continue
                return MESA_RC_OK;
            }
        }
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
              "No sync found: %s", print_as_hex_string(buf, PD_BUFFER_SIZE, charbuf, sizeof(charbuf)));
        VTSS_MSLEEP(1000);
    }
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,
                  "Did not find and Report or Telemetry Key");
    return MESA_RC_ERROR;
}

// The sequence number is also named ECHO in the user guide. Two consecutive
// messages must not contain the same sequunce number. See section 4.1 - ECHO
// in the user guide.
// In : reset_seq_num - Set to TRUE in order to reset the sequence number to 0.
static char get_seq_num(mesa_bool_t reset_seq_num)
{
    static uint8_t seq_num = 0;

    if (reset_seq_num) {
        seq_num = 0;
    } else if (seq_num == SEQ_NUM_DO_NOT_CHK) {
        seq_num = 0;
    } else {
        seq_num++;
    }
    return seq_num;
}

// Updates the check sum for the command. See section 4.1-CHECKSUM in the user guide
// In : buf - pointer to the I2C data
static void pd69200_update_check_sum (uint8_t *buf)
{
    int buf_index = 0;
    unsigned int sum = 0;

    // Find the check for the data (skip the last 2 bytes - They are the check sum bytes going to be replaced.
    for (buf_index = 0 ; buf_index < PD_BUFFER_SIZE - 2; buf_index++) {
        sum += buf[buf_index]; // Sum up the checksum
    }

    // Convert from integer to 2 bytes.
    buf[13] = sum >> 8;
    buf[14] = sum & 0xFF;
}

// Do the real I2C transmitting. Returns FALSE is the trasmit went wrong.
static mesa_bool_t is_tx_ok(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t                    *buf)
{
    buf[1] = get_seq_num(false);

    // Update the checksum
    pd69200_update_check_sum(buf);

    return MESA_RC_OK == pd69200_wr(inst, buf, PD_BUFFER_SIZE);
}

// Check if the check sum is correct. See Section 4.1 - CHECKSUM in the user guide
// In : buf - pointer to the I2C data
static mesa_bool_t pd69200_check_sum_ok(uint8_t *buf)
{
    int buf_index = 0;
    unsigned int sum = 0;

    // -2 because the Sum bytes shall not be part of the checksum
    for (buf_index = 0 ; buf_index < PD_BUFFER_SIZE - 2; buf_index++) {
        sum += buf[buf_index]; // Sum up the checksum
    }


    // Do the check of the checksum
    if (( buf[13] != (sum >> 8 & 0xFF)) && (buf[14] != (sum & 0xFF)) ) {
        return false;
    } else {
        return true;
    }
}

// Report key - See section 4.6 in the user guide
// expected_seq_num - The expected sequence number for the report
static mesa_bool_t report_key_ok(
    const meba_poe_ctrl_inst_t     *const inst,
    uint8_t expected_seq_num)
{
    mesa_rc rc;
    mesa_bool_t report_key_ok_v = true;

    uint8_t buf[PD_BUFFER_SIZE];

    rc = pd69200_rd(inst, buf, PD_BUFFER_SIZE);
    if (rc != MESA_RC_OK) {
        DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Failed to read: rc=%d\n", rc);
        return false;
    }

    // First make sure that the checksum is correct
    if (pd69200_check_sum_ok(&buf[0])) {
        if (buf[0] != REPORT_KEY) {
            report_key_ok_v = false;
        } else if (buf[2] == 0x00 && buf[3] == 0x00) {
            // Command received/correctly executed
            report_key_ok_v = true;
        } else if  (buf[2] == 0xFF && buf[3] == 0xFF && buf[4] == 0xFF && buf[5] == 0xFF) {
            report_key_ok_v = false;
        } else if  (buf[2] > 0x0  && buf[2] < 0x80) {
            report_key_ok_v = false;
        } else if  (buf[2] > 0x80  && buf[2] < 0x90) {
            report_key_ok_v = false;
        } else if  (buf[2] == 0xFF  && buf[3] == 0xFF) {
            report_key_ok_v = false;
        } else {
            report_key_ok_v = true;
        }
    } else {
        report_key_ok_v = false;
    }

    return report_key_ok_v;
}


// Function that reads controller response ( reponds upon request ), and check the key and checksum.
// Returns false in case of error else true.
static mesa_rc get_controller_response (
    const meba_poe_ctrl_inst_t     *const inst,
    uint8_t *buf,
    uint8_t expected_seq_num)
{
    mesa_rc rc;

    // Try and read the data (Step A)
    rc = pd69200_rd(inst, buf, PD_BUFFER_SIZE);
    if (rc != MESA_RC_OK) {
        char dbg_txt[PD_BUFFER_SIZE*4];
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed, Got: %s\n",  __FUNCTION__,
               print_as_hex_string(buf, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));
        memset(buf, 0x0, PD_BUFFER_SIZE);
        return rc;
    }

    // Check checksum
    if (!pd69200_check_sum_ok(buf)) {
        char dbg_txt[PD_BUFFER_SIZE*4];
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Invalid checksum: %s\n",  __FUNCTION__,
               print_as_hex_string(buf, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));
        return MESA_RC_ERROR;
    }

    if  (buf[0] != TELEMETRY_KEY) {
        char dbg_txt[PD_BUFFER_SIZE*4];
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed, Invalid key (%d): %s\n",
                    __FUNCTION__, buf[0],
                    print_as_hex_string(buf, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));
        return MESA_RC_ERROR;
    }

    return MESA_RC_OK;
}


// Transmit the command
// Return true in case that everything went well
// If the transmitted data is a request key the data is return in the buf pointer.
static mesa_rc pd69200_tx(
    const meba_poe_ctrl_inst_t     *const inst,
    const char *file,
    int line,
    uint8_t *buf)
{
    uint8_t buf_copy[PD_BUFFER_SIZE];
    memcpy(&buf_copy[0], buf, PD_BUFFER_SIZE);

    mesa_rc rc = MESA_RC_ERROR; 

    // Do the I2C transmission and check report key.
    if (is_tx_ok(inst, &buf_copy[0])) {
        // Section 4.6 in PD69200/G user guide - check report in case of command or program
        if ((buf_copy[0] == COMMAND_KEY || buf_copy[0] == PROGRAM_KEY)) {
            if (report_key_ok(inst, buf_copy[1])) {
                rc = MESA_RC_OK;
            } else {
                DEBUG(inst, MEBA_TRACE_LVL_WARNING, "%s called from %s(%d) failed\n",  __FUNCTION__, file, line);
            }
        } else if (buf_copy[0] == REQUEST_KEY) {
            rc = get_controller_response(inst, &buf[0], buf_copy[1]);
        } else {
            rc = MESA_RC_OK;
        }
    } else {
        char dbg_txt[sizeof(buf_copy)*4];
        DEBUG(inst, MEBA_TRACE_LVL_WARNING,
              "%s called from %s(%d), Invalid response: %s\n",  __FUNCTION__, file, line,
              print_as_hex_string(buf, PD_BUFFER_SIZE, dbg_txt, sizeof(dbg_txt)));
    }

    return rc;
}


static 
mesa_rc meba_poe_pd69200_individual_mask_set(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t mask,
    uint8_t val)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        INDIV_MASK_KEY,
        mask,
        val,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf))

    return MESA_RC_OK;
}

static 
mesa_rc meba_poe_pd69200_set_pm_method(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t pm1,
    uint8_t pm2,
    uint8_t pm3)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SUPPLY_KEY,
        0x5F,
        pm1,
        pm2,
        pm3,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf))

    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_set_power_banks(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t bank,
    uint16_t power_limit,
    uint16_t max_shutdown_voltage,
    uint16_t min_shutdown_voltage,
    uint8_t guard_band)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        0x07,
        0x0B,
        0x57,
        bank,
        power_limit >> 8 & 0xFF,
        power_limit & 0xFF,
        max_shutdown_voltage >> 8 & 0xFF,
        max_shutdown_voltage & 0xFF,
        min_shutdown_voltage >> 8 & 0xFF,
        min_shutdown_voltage & 0xFF,
        guard_band,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));
    return MESA_RC_OK;
}

// Section 4.7.7
static mesa_rc pd69200_get_power_supply_parameters(
    const meba_poe_ctrl_inst_t    *const inst,
    uint16_t                      *power_consumption,
    uint16_t                      *max_shutdown_voltage,
    uint16_t                      *min_shutdown_voltage,
    uint8_t                       *bank,
    uint16_t                      *power_limit)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        0x07,
        0x0B,
        0x17,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    *power_consumption = (buf[2]<<8) + buf[3];
    *max_shutdown_voltage = (buf[4]<<8) + buf[5];
    *min_shutdown_voltage = (buf[6]<<8) + buf[7];
    *bank = buf[9];
    *power_limit = (buf[10]<<8) + buf[11];
    return MESA_RC_OK;
}

/* static mesa_rc meba_poe_pd69200_ctrl_set_power_limit_for_channels( */
/*     const meba_poe_ctrl_inst_t  *const inst, */
/*     uint8_t                      channel, */
/*     uint16_t                     power) */
/* { */
/*     uint8_t buf[PD_BUFFER_SIZE] = { */
/*         COMMAND_KEY, */
/*         DUMMY_SEQ_NUM, */
/*         CHANNEL_KEY, */
/*         SUPPLY_KEY, */
/*         channel, */
/*         power >> 8 & 0xFF, */
/*         power & 0xFF, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE */
/*     }; */

/*     MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf)); */

/*     return MESA_RC_OK; */
/* } */

/* static mesa_rc meba_poe_pd69200_ctrl_set_temporary_power_limit_for_channels( */
/*     const meba_poe_ctrl_inst_t  *const inst, */
/*     uint8_t                      channel, */
/*     uint16_t                     power) */
/* { */
/*     uint8_t  buf[PD_BUFFER_SIZE] = { */
/*         COMMAND_KEY, */
/*         DUMMY_SEQ_NUM, */
/*         CHANNEL_KEY, */
/*         TEMPORARY_SUPPLY_KEY, */
/*         channel, */
/*         power >> 8 & 0xFF, */
/*         power & 0xFF, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE, */
/*         DUMMY_BYTE */
/*     }; */

/*     MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf)); */

/*     return MESA_RC_OK; */
/* } */

static mesa_rc meba_poe_pd69200_ctrl_get_port_power_limit(
    const meba_poe_ctrl_inst_t  *const inst,
    uint8_t                      channel,
    uint16_t                     *ppl,
    uint16_t                     *tppl)
{
    // Transmit the command

    uint8_t  buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        SUPPLY_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };


    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    *ppl = (buf[2] << 8) + buf[3];
    *tppl  = (buf[4] << 8) + buf[5];
    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_ctrl_set_enable_disable_channels(
    const meba_poe_ctrl_inst_t  *const inst,
    uint8_t                      channel,
    uint8_t                      cmd,
    uint8_t                      port_type)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        ENABLE_DISABLE_KEY,
        channel,
        cmd,
        port_type,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_ctrl_set_port_priority(
    const meba_poe_ctrl_inst_t  *const inst,
    uint8_t                      channel,
    uint8_t                      priority)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        PRIORITY_KEY,
        channel,
        priority,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t      channel,
    uint8_t                     type,
    uint16_t                    requested_power,  // deciwatt
    uint16_t                    allocated_power,  // deciwatt
    uint8_t                     cable_len,
    uint8_t                     execute_lldp)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        0x05,
        0xA6,
        channel,
        type,
        (uint8_t) ((requested_power >> 8) & 0xFF),
        (uint8_t) (requested_power & 0xFF),
        (uint8_t) ((allocated_power >> 8) & 0xFF),
        (uint8_t) (allocated_power & 0xFF),
        cable_len,
        execute_lldp,
        DUMMY_BYTE
    };
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200_ctrl_get_port_layer2_lldp_pse_data(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t      channel,
    uint16_t                    *pse_allocated_power,
    uint16_t                    *pd_requested_power,
    uint8_t                     *pse_power_type,
    uint8_t                     *power_class,
    uint8_t                     *pse_power_pair,
    uint8_t                     *mdi_power_status,
    uint8_t                     *cable_len,
    uint16_t                    *power_indicator)
{
    // Transmit the command

    uint8_t  buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        LLDP_PSE_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };


    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    *pse_allocated_power = (buf[2] << 8) + buf[3];
    *pd_requested_power  = (buf[4] << 8) + buf[5];
    *pse_power_type      =  buf[6];
    *power_class         =  buf[7];
    *pse_power_pair      =  buf[8];
    *mdi_power_status    =  buf[9];
    *cable_len           =  buf[10];
    *power_indicator     =  (buf[11] << 8) + buf[12];

    return MESA_RC_OK;
}



static
mesa_rc meba_poe_pd69200_ctrl_get_single_port_status(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t                     channel,
    uint8_t                     *enable,
    uint8_t                     *port_status,
    uint8_t                     *force_power_enable,
    uint8_t                     *latch,
    uint8_t                     *class,
    uint8_t                     *af_at_poh,
    uint8_t                     *four_pair_enable)
{
    uint8_t  buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        PORT_STATUS_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));
    *enable = buf[2];
    *port_status = buf[3];
    *force_power_enable = buf[4];
    *latch = buf[5];
    *class = buf[6];
    *af_at_poh = buf[10];
    *four_pair_enable = buf[11];

    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_port_power_consume_get(
        const meba_poe_ctrl_inst_t     *const inst,
        uint8_t                         channel,
        uint16_t                       *main_voltage,
        uint16_t                       *calculated_current,
        uint16_t                       *port_power_consumption,
        uint16_t                       *port_voltage)
{

    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        0x25,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));
    *main_voltage = (buf[2] << 8) + buf[3];
    *calculated_current = (buf[4] << 8) + buf[5];
    *port_power_consumption = (buf[6] << 8) + buf[7];
    *port_voltage = (buf[9] << 8) + buf[10];
    return MESA_RC_OK;
}

static mesa_rc meba_poe_pd69200_ctrl_reset_command(
    const meba_poe_ctrl_inst_t  *const inst)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        0x55,
        0x00,
        0x55,
        0x00,
        0x55,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

static 
mesa_rc meba_poe_pd69200_ctrl_set_system_masks(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t                     mask)
{
    mask |= 1 << 2; // maskbit2 must be 1 according to section 4.5.10.
    // Send the system masks command.
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        SET_SYSTEM_MASKS,
        mask,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

static 
mesa_rc meba_poe_pd69200_ctrl_set_temporary_matrix(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t      handle,
    uint8_t                     phys_numb_a,
    uint8_t                     phys_numb_b)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        TMP_MATRIX_KEY,
        handle,
        phys_numb_a,
        phys_numb_b,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

// Apply the port mapping
static
mesa_rc pd69200_program_global_matrix(
    const meba_poe_ctrl_inst_t *const inst)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        TMP_MATRIX_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200_ctrl_get_system_status(
    const meba_poe_ctrl_inst_t  *const inst,
    uint8_t *cpu_status1,
    uint8_t *cpu_status2,
    uint8_t *factory_default,
    uint8_t *gie,
    uint8_t *private_label,
    uint8_t *user_byte,
    uint8_t *device_fail,
    uint8_t *temp_disconnect,
    uint8_t *temp_alarm,
    uint16_t *interrupt_register)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        0x07,
        0x3D,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    if (cpu_status1) *cpu_status1 = buf[2];
    if (cpu_status2) *cpu_status2 = buf[3];
    if (factory_default) *factory_default = buf[4];
    if (gie) *gie = buf[5];
    if (private_label) *private_label = buf[6];
    if (user_byte) *user_byte = buf[7];
    if (device_fail) *device_fail = buf[8];
    if (temp_disconnect) *temp_disconnect = buf[9];
    if (temp_alarm) *temp_alarm = buf[10];
    if (interrupt_register) *interrupt_register = (buf[11]<<8) + buf[12];

    return MESA_RC_OK;
}


static
mesa_rc meba_poe_pd69200_ctrl_get_software_version(
    const meba_poe_ctrl_inst_t     *const inst,
    uint8_t                         *hw_version,
    uint8_t                         *prod_number,
    uint16_t                        *sw_version,
    uint8_t                         *param_number,
    uint8_t                         *build_number,
    uint16_t                        *internal_sw_version,
    uint16_t                        *asic_patch_number)
{
    // Send request to get sw version
    uint8_t buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        VERSIONZ_KEY,
        SW_VERSION_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    *hw_version = buf[2];
    *prod_number = buf[4];
    *sw_version = (buf[5] << 8) +buf[6];
    *param_number = buf[7];
    *build_number = buf[8];
    *internal_sw_version = (buf[9] << 8) +buf[10];
    *asic_patch_number = (buf[11] << 8) +buf[12];
    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200_ctrl_restore_factory_default(
    const meba_poe_ctrl_inst_t      *const inst)
{
    // "pd69200_restore_factory_default - Section 4.1.2"

    uint8_t buf[PD_BUFFER_SIZE] =  {
        PROGRAM_KEY,
        DUMMY_SEQ_NUM,
        RESTORE_FACT_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    if (!is_tx_ok(inst, buf)) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    VTSS_MSLEEP(150); // Wait 100ms (4.1.2 note 1)

    return MESA_RC_OK;
}

//***************************************************************************************************************
//  Code below is used to update the PoE chipset firmware. It is based upon microSemi TN-140_06-0024-081 document
// **************************************************************************************************************
// Send the enter command as described in sw conf guide section 5.2
static mesa_rc pd69200_sendEnter(const meba_poe_ctrl_inst_t  *const inst)
{
    const uint8_t enter[] = { (uint8_t)'E', (uint8_t)'N', (uint8_t)'T', (uint8_t)'R' };

    //T_IG(VTSS_TRACE_GRP_CUSTOM, "Sending ENTR");

    (void) pd69200_wr(inst, (uint8_t *) &enter[0], 1);
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    (void) pd69200_wr(inst, (uint8_t *) &enter[1], 1);
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    (void) pd69200_wr(inst, (uint8_t *) &enter[2], 1);
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    (void) pd69200_wr(inst, (uint8_t *) &enter[3], 1);
    VTSS_MSLEEP(10); // Section 5.2 - Keep at least 10 ms delay between each transmitted character.

    return MESA_RC_OK;
}

// Checking if PoE firmware is valid (Dor selecting the firmware upgrade process)
static mesa_rc pd69200_is_firmware_valid(const meba_poe_ctrl_inst_t  *const inst)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        GLBL_KEY,
        VERSIONZ_KEY,
        SW_VERSION_KEY,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

// Checking if version of PoE firmware update candidate is identical to the current
static mesa_bool_t is_firmware_version_identical(const meba_poe_ctrl_inst_t  *const inst, const char *microsemi_firmware)
{

 #define MAX_FIRMWARE_HEADER_LEN 300

    uint8_t    hw_version;
    uint8_t    prod_number;
    uint16_t   sw_version;
    uint8_t    param_number;
    uint8_t    build_number;
    uint16_t   internal_sw_version;
    uint16_t   asic_patch_number;

    const char *swNum = "Software Number:";
    const char *param = "Param Number:";
    char *swNum_ptr, *param_ptr;
    uint16_t new_sw_ver = 0;
    uint8_t  new_param = 0;
    size_t   mapped_memory_size = 0;
    char    *mapped_memory = NULL;

    int fd=-1;

    mesa_rc rc = meba_poe_pd69200_ctrl_get_software_version(
        inst,
        &hw_version,
        &prod_number,
        &sw_version,
        &param_number,
        &build_number,
        &internal_sw_version,
        &asic_patch_number);

    if (rc != MESA_RC_OK) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO,"Not able to read firmware version from chip.\n");
        return false;
    }

    if (!microsemi_firmware) {
        struct stat st;
        poe_driver_private_t *private_data =
                (poe_driver_private_t *)(inst->private_data);

        if((fd = open(private_data->builtin_firmware,O_RDONLY)) < 0) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Could not open %s for reading.\n", private_data->builtin_firmware );
            return MESA_RC_ERROR;
        }

        if(fstat(fd,&st) < 0) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Could not determine size of %s.\n",
                  private_data->builtin_firmware );
            close(fd);
            return MESA_RC_ERROR;
        }
        mapped_memory_size = (((st.st_size-1)/getpagesize())+1) * getpagesize(); // Round up

        if((mapped_memory = mmap(NULL,mapped_memory_size,PROT_READ,MAP_PRIVATE,fd,0)) == MAP_FAILED) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Could not map %s.\n", private_data->builtin_firmware );
        }
        microsemi_firmware = mapped_memory;

    }

    swNum_ptr = strstr(microsemi_firmware, swNum);
    if (swNum_ptr && (swNum_ptr - microsemi_firmware) < MAX_FIRMWARE_HEADER_LEN) {
        swNum_ptr += strlen(swNum) + 1;
        new_sw_ver = atoi(swNum_ptr);
    } else {
        DEBUG(inst, MEBA_TRACE_LVL_INFO,"Not able to read %s from upgrade image.\n", swNum );
        if (fd >= 0) {
            if (mapped_memory) {
                munmap(mapped_memory, mapped_memory_size);
            }
            close(fd);
        }
        return false;
    }

    param_ptr = strstr(microsemi_firmware, param);
    if (param_ptr && (param_ptr - microsemi_firmware) < MAX_FIRMWARE_HEADER_LEN) {
        param_ptr += strlen(param) + 1;
        new_param  = atoi(param_ptr);
    } else {
        DEBUG(inst, MEBA_TRACE_LVL_INFO,"Not able to read %s from upgrade image.\n", param );
        if (fd >= 0) {
            if (mapped_memory) {
                munmap(mapped_memory, mapped_memory_size);
            }
            close(fd);
        }
        return false;
    }

    if (fd >= 0) {
        if (mapped_memory) {
            munmap(mapped_memory, mapped_memory_size);
        }
        close(fd);
    }

    if (new_sw_ver == sw_version && new_param == param_number) {
        return true;
    } else {
        DEBUG(inst, MEBA_TRACE_LVL_INFO,
              "Different versions, expecting %d.%d, found %d.%d.\n",
              new_sw_ver, new_param, sw_version, param_number );
        return false;
    }
}

static mesa_rc meba_poe_pd69200_prepare_firmware_upgrade(const meba_poe_ctrl_inst_t  *const inst,
                                                mesa_bool_t version_check,
                                                size_t firmware_size,
                                                const char *microsemi_firmware)
{
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Enter for instance %s state %d",  __FUNCTION__, inst->adapter_name, meba_poe_pd69200_get_chipset(inst));
    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_OK; // No PD69200 chip found, don't do anything
    }
    if (version_check) {
        if (is_firmware_version_identical(inst, microsemi_firmware)) {
            DEBUG(inst, MEBA_TRACE_LVL_WARNING,"%s: Not upgrading firmware - versions identical", inst->adapter_name);
            return MESA_RC_ERR_POE_FIRMWARE_VER_NOT_NEW;
        }
    }
    meba_poe_pd69200_set_chipset(inst, MEBA_POE_FIRMWARE_UPGRADE);
    return MESA_RC_OK;
}

mesa_rc pd69200_rd_system_status_ok(const meba_poe_ctrl_inst_t *const inst)

{
    uint8_t buf[PD_BUFFER_SIZE];

    // From section 4.1.1 -
    // As part of rebooting, a System Status Telemetry message will be transmitted back to the
    // Host within *TWAKEUP.  *TWAKEUP = 300msec typical depending on system architecture.
    VTSS_MSLEEP(300);

    // Get response -- Check that response is valid
    if (pd69200_rd(inst, buf, PD_BUFFER_SIZE) == MESA_RC_OK) {
        uint8_t zero_buf[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        if (memcmp(zero_buf, buf, PD_BUFFER_SIZE) == 0) {
            // Empty I2C buffer in controller, just continue
            return MESA_RC_OK;
        }
        uint8_t one_buf[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                              0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        if (memcmp(one_buf, buf, PD_BUFFER_SIZE) == 0) {
            // No I2C response
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Reading all 0xFF", __FUNCTION__);
            return MESA_RC_ERROR;
        }

        char cpu_status1     = buf[3];
        char cpu_status2     = buf[4];
//        char factory_default = buf[5];
//        char gie             = buf[6];
//        char private_label   = buf[7];
//        char device_fail     = buf[9];
//        char temp_disconnect = buf[10];
//        char temp_alarm      = buf[11];
//        int  interrupt       = buf[12] << 8 & buf[13];

        if (cpu_status1 == 0x1) {
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: PoE controller firmware download is required", __FUNCTION__);
        }

        if (cpu_status2 == 0x1) {
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: PoE controller memory error", __FUNCTION__);
        }

        return MESA_RC_OK;

    } 

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: System data read failure", __FUNCTION__);
    return MESA_RC_ERROR;
}

static mesa_rc meba_poe_pd69200_firmware_upgrade(const meba_poe_ctrl_inst_t  *const inst,
                                                mesa_bool_t reset,
                                                size_t firmware_size,
                                                const char *microsemi_firmware)
{
    mesa_rc rc = MESA_RC_ERROR;
    uint8_t      buf[PD_BUFFER_SIZE];
    uint32_t     byte_cnt = 0;
    uint8_t      progress = 0;
    uint8_t      prev_progress = 255;
    const char   *byteArr;
    uint8_t      line[LINE_SIZE_MAX];
    uint8_t      line_index;
    int          fd = -1;
    size_t       mapped_memory_size = 0;
    char         *mapped_memory = NULL;

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Enter %d",  __FUNCTION__, meba_poe_pd69200_get_chipset(inst));

    if (MEBA_POE_FIRMWARE_UPGRADE != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_OK; // No PD69200 chip found, don't do anything
    }

    mesa_rc valid = pd69200_is_firmware_valid(inst);

    if (valid == MESA_RC_OK)   { // Valid firmware exists
        // Section 5.1
        uint8_t download[] = { 0x01, 0x01, 0xFF, 0x99, 0x15, 0x16, 0x16, 0x99, 0x4E, 0x4E, 0x4E, 0x4E, 0x4E, 0x03, 0xFA };
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Valid firmware - start download");
        if (MESA_RC_OK != pd69200_tx(inst,__FUNCTION__, __LINE__, download)) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"TX failed");
            return MESA_RC_ERROR;
        }

    } else { // Invalid or non-existing firmware
        // Section 5.2
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Invalid firmware - start download");
        pd69200_sendEnter(inst);
    }

    VTSS_MSLEEP(100); // read TPE\r\n - Section 5.1 - step 2 - response may take 100 ms
    pd69200_rd(inst, buf, 5); // read TPE\r\n - Section 5.1 - step 2
    if ((buf[0] != 'T') || (buf[1] != 'P') || (buf[2] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_WARNING,"No TPE!");
        // Reset - Section 5.1 - step 9
        //        goto out;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Sending 'E' - erasing memory - Section 5.1 - step 3");
    buf[0] = 'E';
    (void) pd69200_wr(inst, buf, 1);
    VTSS_MSLEEP(100);
    pd69200_rd(inst, buf, 5);// read TOE\r\n - Section 5.1 - step 3;
    if ((buf[0] != 'T') || (buf[1] != 'O') || (buf[2] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO,"No TOE!");
        //        goto out;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Erasure may last up to 5 seconds. - Section 5.1 - step 4");
    VTSS_MSLEEP(5000);

    pd69200_rd(inst, buf, 4); // read TE\r\n - Section 5.1 - step 4
    if ((buf[0] != 'T') || (buf[1] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"No TE!");
        //        goto out;
    }
    VTSS_MSLEEP(100);

    pd69200_rd(inst, buf, 5); // read TPE\r\n - Section 5.1 - step 4
    if ((buf[0] != 'T') || (buf[1] != 'P') || (buf[2] != 'E')) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"No TPE!");
        //        goto out;
    }

    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Sending 'P' - program memory - Section 5.1 - step 5");
    buf[0] = 'P';
    (void) pd69200_wr(inst, buf, 1);
    VTSS_MSLEEP(100);
    pd69200_rd(inst, buf, 5); // read TOP\r\n - Section 5.1 - step 5
    if ((buf[0] != 'T') || (buf[1] != 'O') || (buf[2] != 'P')) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO,"No TOP");
        //        goto out;
    }

    if (!microsemi_firmware) { // Use built-in firmware
        struct stat st;
        poe_driver_private_t *private_data =
                (poe_driver_private_t *)(inst->private_data);

        if((fd = open(private_data->builtin_firmware,O_RDONLY)) < 0) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Could not open %s for reading.\n",
                  private_data->builtin_firmware );
            return MESA_RC_ERROR;
        }

        if(fstat(fd,&st) < 0) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Could not determine size of %s.\n",
                  private_data->builtin_firmware );
            close(fd);
            return MESA_RC_ERROR;
        }
        firmware_size = st.st_size;

        mapped_memory_size = (((st.st_size-1)/getpagesize())+1) * getpagesize(); // Round up

        if((mapped_memory = mmap(NULL,mapped_memory_size,PROT_READ,MAP_PRIVATE,fd,0)) == MAP_FAILED) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR,"Could not map %s.\n",
                  private_data->builtin_firmware );
            close(fd);
            return MESA_RC_ERROR;
        }
        microsemi_firmware = mapped_memory;
    }

    printf("\n\rUpdating PoE firmware...\n\r");

    // If greater than 127 then we have reached end of file
    while ((byte_cnt < firmware_size) && (*microsemi_firmware <= 127)) {

        byteArr = microsemi_firmware;

        // Print out progress
        progress = (byte_cnt * 10) / firmware_size;
        if (progress != prev_progress) {
            printf("PoE Firmware update progress:%d %%\n\r", progress * 10);
            prev_progress = progress;
        }

        if (byteArr[0] == 10) {
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"Skipping LF (Line Feed)");
            microsemi_firmware++;
            byte_cnt++;
            byteArr = microsemi_firmware;
        }

        if (byteArr[0] != 'S') {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Line should start with S byteArr[0]:0x%X", byteArr[0]);
            break;
        }

        if (byteArr[1] == '0') { //skip line that starts with "S0"
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Skipping lines starting with S0");

            // If greater than 127 then we have reached end of file
            while (*microsemi_firmware != '\n' && *microsemi_firmware < 127 && byte_cnt <= firmware_size) {
                byte_cnt++;
                DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Skipping S0 lines microsemi_firmware:0x%X, byte_cnt:%u", *microsemi_firmware, byte_cnt);
                microsemi_firmware++;
            }

            // Lines Starting with S3 or S7
        } else if (byteArr[1] == '3' || byteArr[1] == '7') {
            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Lines Starting with S3 or S7 - Section 5.1 - step 6");

            line_index = 0;
            // If greater than 127 then we have reached end of file
            while (*microsemi_firmware != '\n' && *microsemi_firmware < 127 && byte_cnt <= firmware_size) {
                line[line_index++] = *microsemi_firmware;
                microsemi_firmware++;
                byte_cnt++;
            }
            microsemi_firmware++; // For the "\n"
            byte_cnt++;

            DEBUG(inst, MEBA_TRACE_LVL_NOISE, "Writing new line - byte_cnt:%u", byte_cnt);
            line[line_index++] = '\n';
            line[line_index] = 0;

            (void) pd69200_wr(inst, line, line_index); // Write the line - Section 5.1 - step 6
            //T_NG_HEX(VTSS_TRACE_GRP_CUSTOM, line, line_index);

            pd69200_firm_update_rd(inst, buf, 4); // reading T*\r\n or TP\r\n - Section 5.1 - step 6

            if (buf[0] == 'T' && buf[1] == '*') { // if read T*\r\n
                DEBUG(inst, MEBA_TRACE_LVL_NOISE, "NOT END of File");
            } else if (buf[0] == 'T' && buf[1] == 'P') { // if read TP\r\n
                DEBUG(inst, MEBA_TRACE_LVL_NOISE, "END of File");     // Reset - Section 5.1 - step 7
                printf("PoE Firmware update progress:100 %%\n\r");
                break; //end of file
            } else {
                DEBUG(inst, MEBA_TRACE_LVL_ERROR, "No Ack");
                rc = MESA_RC_ERROR;
                goto error_out;
            }

        } else {
            // Unknown Sx number
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Unknown start value S:%d", byteArr[1]);
            break;
        }
    }

    // Wait 400ms - Section 5.1 - step 8
    VTSS_MSLEEP(400);

    // Reset - Section 5.1 - step 9
    buf[0] = 'R';
    buf[1] = 'S';
    buf[2] = 'T';
    (void) pd69200_wr(inst, buf, 3);

    VTSS_MSLEEP(10000);
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Download succeeded");

    rc = pd69200_rd_system_status_ok(inst); // Download succeeded
    meba_poe_pd69200_set_chipset(inst, MEBA_POE_CHIPSET_FOUND);

error_out:
    if (fd >= 0) {
        if (mapped_memory) {
            munmap(mapped_memory, mapped_memory_size);
         }
        close(fd);
    }

    return rc;
}




/*********************
   Public Functions
**********************/


mesa_rc meba_poe_pd69200_ctrl_cfg_set(
    const meba_poe_ctrl_inst_t  *const inst,
    meba_poe_cfg_t              *cfg)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    meba_poe_cfg_t *current_cfg = 
            &(((poe_driver_private_t *)(inst->private_data))->cfg.global);

    if (cfg->primary_max_power != 0 &&
        current_cfg->primary_max_power == cfg->primary_max_power &&
        current_cfg->backup_max_power == cfg->backup_max_power &&
        current_cfg->legacy_detect == cfg->legacy_detect) {
        return MESA_RC_OK;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Update configuration for controller");

    uint8_t mask = cfg->legacy_detect?CAPACITOR_LEGACY_DETECTION:0x0;
    MESA_RC(meba_poe_pd69200_ctrl_set_system_masks(inst,mask));

    // See table in section 4.5.9 in PD69200 user guide
    MESA_RC(meba_poe_pd69200_individual_mask_set(inst, 0x2E, 1)); // Enable LLDP mode.
    MESA_RC(meba_poe_pd69200_individual_mask_set(inst, 0x2F, 1)); // Allow the priority to be fetched from lldp
    MESA_RC(meba_poe_pd69200_set_pm_method(inst, 0x05, 0x01, 0x00));

    uint16_t  power_consumption;
    uint16_t  max_shutdown_voltage;
    uint16_t  min_shutdown_voltage;
    uint8_t   bank;
    uint16_t  power_limit;
    MESA_RC(pd69200_get_power_supply_parameters(
        inst, 
        &power_consumption,
        &max_shutdown_voltage,
        &min_shutdown_voltage,
        &bank,
        &power_limit));

    power_limit = cfg->primary_max_power; 
    uint8_t guard_band = 0x2; // We set guard to 2W in order to get priority to take over as soon as possible.

    MESA_RC(meba_poe_pd69200_set_power_banks(
        inst,
        bank,
        power_limit,
        max_shutdown_voltage,
        min_shutdown_voltage,
        guard_band));

    *current_cfg = *cfg;
    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_port_cfg_set(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_cfg_t            *port_cfg)
{
    uint8_t channel = handle;
 
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }
    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    meba_poe_port_cfg_t *current_port_cfg = 
            &(((poe_driver_private_t *)(inst->private_data))->cfg.ports[handle]);

    if (current_port_cfg->enable == port_cfg->enable &&
        current_port_cfg->priority == port_cfg->priority &&
        current_port_cfg->legacy_support == port_cfg->legacy_support) {
        return MESA_RC_OK;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Update configuration for controller port %d",  handle);
    DEBUG(inst,
          MEBA_TRACE_LVL_INFO, "%s, priority: %s, legacy support: %s",
          port_cfg->enable ? "Enabled" : "Disabled",
          port_cfg->priority == MEBA_POE_PORT_PRIO_CRITICAL
                             ? "crit"
          : port_cfg->priority == MEBA_POE_PORT_PRIO_HIGH ? "high" : "low",
          port_cfg->legacy_support ?  "Enabled" : "Disabled");

    /* mesa_poe_milliwatt_t power_pd69200  = port_cfg->max_power; */

    /* // Section 4.5.14 in user guide */
    /* uint max_port_power = pd69200_get_port_power_max(handle); */

    /* if (power_pd69200 > max_port_power) { */
    /*     power_pd69200 = max_port_power; */
    /* } */

    /* if (power_pd69200 > 0) { */
    /*     MESA_RC(meba_poe_pd69200_ctrl_set_power_limit_for_channels( */
    /*         inst, handle, power_pd69200)); */
    /* } */

    /* // Section 4.5.15 in user guide */
    /* MESA_RC(meba_poe_pd69200_ctrl_set_temporary_power_limit_for_channels( */
    /*     inst, handle, power_pd69200)); */

    uint8_t enable;
    if (port_cfg->enable == 0) {
        enable = 0; // Disable
    } else {
        enable = 1; // Disable
    }

    // port type:
    // 1 - IEEE802.3AF/AT operation
    // 2 - POH operation
    uint8_t port_type = (port_cfg->legacy_support ? 2 : 1);

    MESA_RC(meba_poe_pd69200_ctrl_set_enable_disable_channels(inst, channel, enable, port_type));

    uint8_t pd69200_prio = 3; // Default to low priority

    // Type conversion -- See section 4.5.16 in PD69200 user guide
    switch (port_cfg->priority) {
        case MEBA_POE_PORT_PRIO_LOW :
            pd69200_prio = 3;
            break;
        case MEBA_POE_PORT_PRIO_HIGH:
            pd69200_prio = 2;
            break;
        case MEBA_POE_PORT_PRIO_CRITICAL:
            pd69200_prio = 1;
            break;
        default:
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Unknown priority: %d\n",  __FUNCTION__, port_cfg->priority);
    }

    MESA_RC(meba_poe_pd69200_ctrl_set_port_priority(inst, channel, pd69200_prio));

    *current_port_cfg = *port_cfg;
    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_do_reset(
    const meba_poe_ctrl_inst_t     *const inst)
{
    // Empty i2c buffer.
    uint8_t dummy;
    int i = 20;
    while (i--) {
        pd69200_rd(inst, &dummy, 1);
    }

    MESA_RC(meba_poe_pd69200_ctrl_reset_command(inst));


    uint8_t buf[PD_BUFFER_SIZE];
    // After reset we look for the REPORT KEY to show up
    mesa_bool_t found = false;
    i = 50; // We do read maximum 50 bytes before giving up.
    while (i--) {
        if (pd69200_rd(inst, buf, 1) != MESA_RC_OK) {
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s: Read Failed", __FUNCTION__);
            found = false;
            break;
        }

        if (buf[0] == REPORT_KEY) {
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Found REPORT_KEY", __FUNCTION__);
            found = true;
            break;
        }

        VTSS_MSLEEP(100); // OK, not an expected byte, give PoE controller a little more time to come up, before checking again.
    }

    if (found) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Found PD69200", __FUNCTION__);
        // Read rest of the response in order to clear buffer
        if (pd69200_rd(inst, &buf[1], PD_BUFFER_SIZE - 1) != MESA_RC_OK) {
            found = false;
        }
    } else {
        char dbg_txt[PD_BUFFER_SIZE*4];
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s: Invalid response: %s", __FUNCTION__,
               print_as_hex_string(buf, sizeof(buf), dbg_txt, sizeof(dbg_txt)));
    }

    (void) get_seq_num(true); // Reset the sequence number
    return (found ? MESA_RC_OK : MESA_RC_ERROR);
}

mesa_rc meba_poe_pd69200_ctrl_version_get(
    const meba_poe_ctrl_inst_t     *const inst,
    uint32_t                        max_size,
    char                           *value)
{
    uint8_t   hw_version;
    uint8_t   prod_number;
    uint16_t  sw_version;
    uint8_t   param_number;
    uint8_t   build_number;
    uint16_t  internal_sw_version;
    uint16_t  asic_patch_number;

    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    MESA_RC(meba_poe_pd69200_ctrl_get_software_version(
        inst,
        &hw_version,
        &prod_number,
        &sw_version,
        &param_number,
        &build_number,
        &internal_sw_version,
        &asic_patch_number));

    snprintf(value, max_size,
             "HW Ver.:%d, Prod:%d, sw ver:%d, param:%d, build:%d, internal sw ver:%d, Asic Patch Num:%d",
             hw_version, prod_number, sw_version, param_number, build_number, internal_sw_version, asic_patch_number);

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200_ctrl_status_get(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_status_t              *status)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    meba_poe_status_t *current_status = 
            &(((poe_driver_private_t *)(inst->private_data))->status.global);

    current_status->source = MEBA_POE_POWER_SOURCE_PRIMARY;
    *status = *current_status;
    return MESA_RC_OK;
}


// If we end up mapping two channels to the same port the "pd69200_program_global_matrix"
// will not be executed (no errors will indicate this). To avoid this we start be mapping all channels
// to a non-existing port (Ports above  48)
static mesa_rc pd69200_temp_matrix_init(
    const meba_poe_ctrl_inst_t     *const inst)
{
    for (uint8_t i = 0; i < inst->port_map_length; i++) {
        if (inst->port_map[i].capabilities & MEBA_POE_PORT_CAP_POE) {
            MESA_RC(meba_poe_pd69200_ctrl_set_temporary_matrix(inst, i, i+49, 255));
        }
    }

    return MESA_RC_OK;
}

// Setup port mapping
static mesa_rc pd69200_temp_matrix_set(
    const meba_poe_ctrl_inst_t *const inst)
{

    for (uint8_t i = 0; i < inst->port_map_length; i++) {
        if (inst->port_map[i].capabilities & MEBA_POE_PORT_CAP_POE) {
            MESA_RC(meba_poe_pd69200_ctrl_set_temporary_matrix(
                inst, i, inst->port_map[i].phys_port_a, inst->port_map[i].phys_port_b));
        }
    }
    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200_do_detection(
    const meba_poe_ctrl_inst_t     *const inst)
{
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s(%s)", __FUNCTION__, inst->adapter_name);
    meba_poe_pd69200_set_chipset(inst, MEBA_POE_NO_CHIPSET_FOUND);
    uint8_t cpu_status1;
    uint8_t cpu_status2;
    uint8_t factory_default;
    mesa_rc rc;

    if ((rc = pd69200_rd_system_status_ok(inst)) != MESA_RC_OK) {
        // This is where we end if there are no PoE board detected.
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 No PoE chipset detected. Reason: rc: %d", rc);
        return rc;
    }

    meba_poe_pd69200_set_chipset(inst, MEBA_POE_CHIPSET_FOUND);
    rc = meba_poe_pd69200_ctrl_get_system_status(
        inst, &cpu_status1, &cpu_status2, &factory_default,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    if (rc != MESA_RC_OK) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 Firmware update required");
        return MESA_RC_OK;
    }
    if ((cpu_status1 & 0x01) || (cpu_status2 & 0x01)) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "PD69200 Firmware update required");
    } else {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s(%s): STATUS OK", __FUNCTION__, inst->adapter_name);
        meba_poe_status_t *current_status =
                &(((poe_driver_private_t *)(inst->private_data))->status.global);
        MESA_RC(meba_poe_pd69200_ctrl_version_get(inst, MEBA_POE_VERSION_STRING_SIZE, current_status->version));
    }

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200_chip_initialization(
    const meba_poe_ctrl_inst_t     *const inst)
{
    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_OK;
    }
    // Disable i2c ready interrupt
    MESA_RC(meba_poe_pd69200_individual_mask_set(inst, 0x1E, 0));

    // Turn off lowest priority port, when a higher priority has a PD connected,
    // see section 4.5.10
    MESA_RC(meba_poe_pd69200_ctrl_set_system_masks(inst, 0x0));

    for (uint8_t i = 0; i < inst->port_map_length; i++) {
        if (inst->port_map[i].capabilities & MEBA_POE_PORT_CAP_POE) {
            MESA_RC(meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(inst, i, 0, 0, 0, 0, 0));
        }
    }
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s(%s): PROGRAM MATRIX", __FUNCTION__, inst->adapter_name);

    MESA_RC(pd69200_temp_matrix_init(inst));
    MESA_RC(pd69200_temp_matrix_set(inst));
    MESA_RC(pd69200_program_global_matrix(inst));
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s(%s): PROGRAM MATRIX DONE", __FUNCTION__, inst->adapter_name);
    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200_ctrl_port_status_get(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_port_status_t         *const port_status)
{
    if (port_status == NULL)  {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s port_status is NULL pointer", __FUNCTION__);
        return MESA_RC_ERROR;
    }
    port_status->chip_state = meba_poe_pd69200_get_chipset(inst);

    if (port_status->chip_state == MEBA_POE_FIRMWARE_UPGRADE) {
        DEBUG(inst, MEBA_TRACE_LVL_NOISE, "%s Firmware upgrading", __FUNCTION__);
        port_status->assigned_pd_class_a = -1;
        port_status->assigned_pd_class_b = -1;
        port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_NOT_PERFORMED;
        port_status->state = MEBA_POE_PORT_STATE_DISABLED;
        port_status->power = 0;
        port_status->current = 0;
        port_status->voltage = 0;
        port_status->requested_power = 0;
        return MESA_RC_OK;
    }

    if (port_status->chip_state != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Device not ready for reading", __FUNCTION__);
        return MESA_RC_ERROR;
    }

    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid handle: %d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }


    meba_poe_port_handle_t channel = handle;
    uint8_t enable;
    uint8_t port_state;
    uint8_t force_power_enable;
    uint8_t latch;
    uint8_t pd_class;
    uint8_t af_at_poh;
    uint8_t four_pair_enable;

    MESA_RC(meba_poe_pd69200_ctrl_get_single_port_status(
        inst,
        channel,
        &enable,
        &port_state,
        &force_power_enable,
        &latch,
        &pd_class,
        &af_at_poh,
        &four_pair_enable));

    port_status->assigned_pd_class_a = pd_class;
    port_status->assigned_pd_class_b = -1;
    // See table 4 in the user guide for understanding the conversion - we do not support all status values.
    port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_NOT_PERFORMED;
    switch (port_state) {
        case 0x0:
            port_status->state = MEBA_POE_PORT_STATE_DELIVERING_POWER;
            port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_2P_LEGACY;
            break;
        case 0x1:
            port_status->state = MEBA_POE_PORT_STATE_DELIVERING_POWER;
            port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_2P_IEEE;
            break;

        case 0x1A:
            port_status->state = MEBA_POE_PORT_STATE_DISABLED;
            break;

        case 0x1B: // Interim state, detection going on
            port_status->state = MEBA_POE_PORT_STATE_SEARCHING;
            break;

        case 0x1C: // We have seen "False Positives" when conencted to another switch.
        case 0x1E: // We heen seen "False Positives" when conencted to another switch.
            port_status->state = MEBA_POE_PORT_STATE_OTHER_FAULT;
            break;

        case 0x1F:
            port_status->state = MEBA_POE_PORT_STATE_FAULT;
            break;

        case 0x20:
        case 0x3C:
            port_status->state = MEBA_POE_PORT_STATE_FAULT;
            break;

        case 0x02:
        case 0x03:
        case 0x04:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x0C:
        case 0x11:
        case 0x12:
        case 0x1D:
        case 0x21:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3D:
        case 0x3E:
        case 0x3F:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
            DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "Port %d: Unexpected port state: 0x%X",
                  inst->port_map[handle].port_no, port_state);
            port_status->state = MEBA_POE_PORT_STATE_OTHER_FAULT;
            break;

        default:
            // This shall never happen all states should be covered.
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Port %d: Unknown port state: 0x%X",
                  inst->port_map[handle].port_no, port_state);
            port_status->state = MEBA_POE_PORT_STATE_OTHER_FAULT;
            break;

    }

    uint16_t ppl = 0;
    uint16_t tppl = 0;
    meba_poe_pd69200_ctrl_get_port_power_limit(inst, handle, &ppl, &tppl);
    port_status->requested_power = tppl;


    uint16_t main_voltage = 0;
    uint16_t calculated_current = 0;
    uint16_t port_power_consumption = 0;
    uint16_t port_voltage = 0;

    if (port_status->state == MEBA_POE_PORT_STATE_DELIVERING_POWER) {
        meba_poe_pd69200_ctrl_port_power_consume_get(
            inst,
            channel,
            &main_voltage,
            &calculated_current,
            &port_power_consumption,
            &port_voltage);
    }

    uint16_t pse_allocated_power;
    uint16_t pd_requested_power;
    uint8_t pse_power_type;
    uint8_t power_class;
    uint8_t pse_power_pair;
    uint8_t mdi_power_status;
    uint8_t cable_len;
    uint16_t power_indicator;

    MESA_RC(meba_poe_pd69200_ctrl_get_port_layer2_lldp_pse_data(
        inst,
        handle,
        &pse_allocated_power,
        &pd_requested_power,
        &pse_power_type,
        &power_class,
        &pse_power_pair,
        &mdi_power_status,
        &cable_len,
        &power_indicator));

    port_status->pse_data.pse_allocated_power   = pse_allocated_power;
    port_status->pse_data.pd_requested_power    = pd_requested_power;
    port_status->pse_data.pse_power_type        = pse_power_type;
    port_status->pse_data.power_class           = power_class;
    port_status->pse_data.cable_len             = cable_len;
    port_status->pse_data.pse_power_pair        = pse_power_pair;

    port_status->power = port_power_consumption;
    port_status->current = calculated_current;
    port_status->voltage = port_voltage *100;

    if (power_indicator & 0x2000) {
        port_status->reserved_power = port_status->requested_power; 
    } else {
        port_status->reserved_power = port_status->power;
    }

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200_ctrl_debug(
    const meba_poe_ctrl_inst_t    *const inst,
    uint8_t                       *buf,
    int                            buf_size)
{
    if (buf_size != PD_BUFFER_SIZE) {
        return MESA_RC_ERROR;
    }

    // Get response -- Check that response is valid
    return pd69200_tx(inst, __FILE__, __LINE__, buf);
}

mesa_rc meba_poe_pd69200_ctrl_port_capabilities_get(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_cap_t            *capabilities)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Device not ready for reading", __FUNCTION__);
        return MESA_RC_ERROR;
    }

    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid handle: %d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }

    *capabilities = inst->port_map[handle].capabilities;
    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200_ctrl_firmware_upgrade(
        const meba_poe_ctrl_inst_t     *const inst,
        mesa_bool_t                     reset,
        uint32_t                        size,
        const char                     *data)
{
    return meba_poe_pd69200_firmware_upgrade(inst, reset, size, data);
}

mesa_rc meba_poe_pd69200_ctrl_prepare_firmware_upgrade(
        const meba_poe_ctrl_inst_t     *const inst,
        mesa_bool_t                     version_check,
        uint32_t                        size,
        const char                     *data)
{
    return meba_poe_pd69200_prepare_firmware_upgrade(inst, version_check, size, data);
}

mesa_rc meba_poe_pd69200_ctrl_port_pd_data_set(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_data_t             *pd_data)
{
    uint8_t type = 0, source = 0, prio = 0;
    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_ERROR;
    }

    switch(pd_data->type) {
        case MEBA_POE_PORT_PD_POWER_TYPE2_PSE:
            type = 0;
            break;
        case MEBA_POE_PORT_PD_POWER_TYPE2_PD:
            type = 1;
            break;
        case MEBA_POE_PORT_PD_POWER_TYPE1_PSE:
            type = 2;
            break;
        case MEBA_POE_PORT_PD_POWER_TYPE1_PD:
            type = 3;
            break;
        default:
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid type parameter %d", __FUNCTION__, pd_data->type);
        return MESA_RC_ERR_PARM;
    }

    switch(pd_data->source) {
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_UNKNOWN:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_UNKNOWN:
            source = 0;
            break;
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_PSE:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_PRIMARY:
            source = 1;
            break;
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_RESERVED:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_BACKUP:
            source = 2;
            break;
        case MEBA_POE_PORT_PD_PD_POWER_SOURCE_PSE_LOCAL:
        case MEBA_POE_PORT_PD_PSE_POWER_SOURCE_RESERVED:
            source = 3;
            break;
        default:
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid source parameter %d", __FUNCTION__, pd_data->source);
        return MESA_RC_ERR_PARM;
    }

    switch(pd_data->prio) {
        case MEBA_POE_PORT_PD_POWER_PRIORITY_UNKNOWN:
            prio = 0;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_CRITICAL:
            prio = 1;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_HIGH:
            prio = 2;
            break;
        case MEBA_POE_PORT_PD_POWER_PRIORITY_LOW:
            prio = 3;
            break;
        default:
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid prio parameter %d", __FUNCTION__, pd_data->prio);
        return MESA_RC_ERR_PARM;
    }

    return meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(
        inst,
        handle,
        type << 6 | source << 4 | prio,
        pd_data->pd_requested_power  / 100, // convert from milliwatt to deciwatt
        pd_data->pse_allocated_power / 100, // convert from milliwatt to deciwatt
        100,                                // always set to 100 meters
        1);
}

mesa_rc meba_poe_pd69200_ctrl_port_pd_data_clear(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle)
{
    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_ERROR;
    }

    meba_poe_port_cfg_t *port_cfg = 
            &(((poe_driver_private_t *)(inst->private_data))->cfg.ports[handle]);

    uint8_t pd69200_prio = 3; // Default to low priority

    // Type conversion -- See section 4.5.16 in PD69200 user guide
    switch (port_cfg->priority) {
        case MEBA_POE_PORT_PRIO_LOW :
            pd69200_prio = 3;
            break;
        case MEBA_POE_PORT_PRIO_HIGH:
            pd69200_prio = 2;
            break;
        case MEBA_POE_PORT_PRIO_CRITICAL:
            pd69200_prio = 1;
            break;
        default:
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Unknown priority: %d\n",  __FUNCTION__, port_cfg->priority);
    }

    return meba_poe_pd69200_ctrl_set_port_layer2_lldp_pd_data(
        inst, handle, pd69200_prio, 0, 0, 0, 3);
}

mesa_rc meba_poe_pd69200_ctrl_port_pd_bt_data_set(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_bt_data_t          *pd_data)
{
    return MESA_RC_OK;
}

void meba_pd69200_driver_init(
    meba_poe_ctrl_inst_t       *inst,
    char const                 *adapter_name, 
    int                         adapter_fd, 
    meba_poe_ctrl_cap_t         capabilities, 
    meba_poe_port_properties_t *port_map,
    uint32_t                    port_map_length,
    meba_poe_psu_input_prob_t   *psu_map,
    uint32_t                    psu_map_length,
    meba_debug_t                debug)        /**< Board debug output */
{
    int i;
    if (adapter_fd <=0) {

        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s: Invalid file handle (%d)",
              adapter_name,
              adapter_fd);
    }
    static meba_poe_ctrl_api_t meba_pd69200_api = {
        .meba_poe_ctrl_do_detection = meba_poe_pd69200_do_detection,
        .meba_poe_ctrl_chip_initialization = meba_poe_pd69200_chip_initialization,
        .meba_poe_ctrl_sync = meba_poe_pd69200_sync,
        .meba_poe_ctrl_reset_command = meba_poe_pd69200_ctrl_reset_command,
        .meba_poe_ctrl_version_get = meba_poe_pd69200_ctrl_version_get,
        .meba_poe_ctrl_port_cfg_set = meba_poe_pd69200_ctrl_port_cfg_set,
        .meba_poe_ctrl_port_status_get = meba_poe_pd69200_ctrl_port_status_get,
        .meba_poe_ctrl_cfg_set = meba_poe_pd69200_ctrl_cfg_set,
        .meba_poe_ctrl_status_get = meba_poe_pd69200_ctrl_status_get,
        .meba_poe_ctrl_debug = meba_poe_pd69200_ctrl_debug,
        .meba_poe_ctrl_firmware_upgrade = meba_poe_pd69200_ctrl_firmware_upgrade,
        .meba_poe_ctrl_prepare_firmware_upgrade = meba_poe_pd69200_ctrl_prepare_firmware_upgrade,
        .meba_poe_ctrl_port_capabilities_get = meba_poe_pd69200_ctrl_port_capabilities_get,
        .meba_poe_ctrl_port_pd_bt_data_set = meba_poe_pd69200_ctrl_port_pd_bt_data_set,
        .meba_poe_ctrl_port_pd_data_set = meba_poe_pd69200_ctrl_port_pd_data_set,
        .meba_poe_ctrl_port_pd_data_clear = meba_poe_pd69200_ctrl_port_pd_data_clear,
    };

    poe_driver_private_t *private_data = malloc(sizeof(poe_driver_private_t));
    private_data->debug = debug;
    private_data->cfg.ports = malloc(sizeof(meba_poe_port_cfg_t)*port_map_length);
    private_data->status.ports = malloc(sizeof(meba_poe_port_private_status_t)*port_map_length);
    for (i=0; i<port_map_length; ++i) {
        private_data->status.global.chip_state = MEBA_POE_CHIPSET_DETECTION;
    }
    private_data->builtin_firmware = "/etc/mscc/poe/firmware/mscc_firmware.txt";
    inst->api = &meba_pd69200_api;
    inst->private_data = private_data;
    inst->adapter_name = adapter_name;
    inst->adapter_fd = adapter_fd;
    inst->capabilities = capabilities;
    inst->port_map = port_map;
    inst->port_map_length = port_map_length;
    inst->psu_map = psu_map;
    inst->psu_map_length = psu_map_length;
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"%s Done", __FUNCTION__);
    return;
}



// PoE BT driver


mesa_rc meba_poe_pd69200_ctrl_port_dummy_method(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pse_data_t            *pse_data)
{
    return MESA_RC_OK;
}


static
mesa_rc meba_poe_pd69200bt_ctrl_set_BT_port_parameters(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t                     channel,
    uint8_t                     port_mode_cfg1,
    uint8_t                     port_mode_cfg2,
    uint8_t                     port_operation_mode,
    uint8_t                     add_power_for_port_mode,
    uint8_t                     priority)
{
    // Transmit the command
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_CONFIG1_KEY,
        channel,
        port_mode_cfg1,
        port_mode_cfg2,
        port_operation_mode,
        add_power_for_port_mode,
        priority,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;

}

static
mesa_rc meba_poe_pd69200bt_ctrl_get_BT_port_status(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t                     channel,
    uint8_t                     *port_status,
    uint8_t                     *enable,
    uint8_t                     *assigned_class,
    uint16_t                    *measured_port_power,
    uint8_t                     *last_shutdown_error_status,
    uint8_t                     *port_event)
{
    uint8_t  buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_STATUS_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));
    *port_status = buf[2];
    *enable = buf[3];
    *assigned_class = buf[4];
    *measured_port_power = (buf[5]<<8) + buf[6];
    *last_shutdown_error_status = buf[9];
    *port_event = buf[10];

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200bt_ctrl_get_BT_port_class(
    const meba_poe_ctrl_inst_t *const inst,
    uint8_t                     channel,
    uint8_t                     *port_status,
    uint8_t                     *port_phy_info,
    uint8_t                     *measured_class,
    uint8_t                     *requested_class,
    uint16_t                    *requested_power,
    uint8_t                     *assigned_class,
    uint16_t                    *assigned_power,
    uint8_t                     *auto_class_support,
    uint16_t                    *auto_class_measurement)
{
    uint8_t  buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_CLASS_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));
    *port_status = buf[2];
    *port_phy_info = buf[3];
    *measured_class = buf[4];
    *requested_class = buf[5];
    *requested_power = (buf[6]<<8) + buf[7];
    *assigned_class = buf[8];
    *assigned_power = (buf[9]<<8) + buf[10];
    *auto_class_support = (buf[11] & 0xF0)>>4;
    *auto_class_measurement = ((buf[11] & 0xF)<<8) + buf[12];

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200bt_get_BT_port_measurements(
        const meba_poe_ctrl_inst_t     *const inst,
        uint8_t                         channel,
        uint16_t                       *main_voltage,
        uint16_t                       *calculated_current,
        uint16_t                       *port_power_consumption,
        uint16_t                       *port_voltage)
{

    // Send request to get status
    unsigned char buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_PORT_MEASE_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));
    *main_voltage = (buf[2] << 8) + buf[3];
    *calculated_current = (buf[4] << 8) + buf[5];
    *port_power_consumption = (buf[6] << 8) + buf[7];
    *port_voltage = (buf[9] << 8) + buf[10];
    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200bt_ctrl_port_cfg_set(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_port_cfg_t            *port_cfg)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }
    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    meba_poe_port_cfg_t *current_port_cfg = 
            &(((poe_driver_private_t *)(inst->private_data))->cfg.ports[handle]);

    if (current_port_cfg->enable == port_cfg->enable &&
        current_port_cfg->priority == port_cfg->priority &&
        current_port_cfg->legacy_support == port_cfg->legacy_support) {
        return MESA_RC_OK;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Update configuration for controller port %d",  handle);
    DEBUG(inst,
          MEBA_TRACE_LVL_INFO, "%s, priority: %s legacy_support %s",
          port_cfg->enable ? "Enabled" : "Disabled",
          port_cfg->priority == MEBA_POE_PORT_PRIO_CRITICAL ? "crit" : port_cfg->priority == MEBA_POE_PORT_PRIO_HIGH ? "high" : "low",
          port_cfg->legacy_support ? "Enabled" : "Disabled"
          );


    uint8_t port_mode_cfg1 = port_cfg->enable;

    // The port power that will be used for power management purposes is
    //dynamic for non LLDP/CDP/Autoclass ports and TPPL_BT for LLDP/CDP/Autoclass
    //ports.
    uint8_t port_mode_cfg2 = 2; 
    uint8_t port_operation_mode = 0;
    uint8_t add_power_for_port_mode =0;
    uint8_t priority = port_cfg->priority;

    if (port_cfg->legacy_support) {
        port_operation_mode += 0x10;  // Value copied from Ezra's version TODO decide on righ choise for value
    }

    MESA_RC(meba_poe_pd69200bt_ctrl_set_BT_port_parameters(
        inst,
        handle,
        port_mode_cfg1,
        port_mode_cfg2,
        port_operation_mode,
        add_power_for_port_mode,
        priority));


    *current_port_cfg = *port_cfg;
    return MESA_RC_OK;
}


static
mesa_rc meba_poe_pd69200bt_ctrl_set_port_layer2_lldp_pd_data(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t      channel,
    uint16_t                    requested_power_single,  // deciwatt
    uint16_t                    requested_power_dual_a,  // deciwatt
    uint16_t                    requested_power_dual_b,  // deciwatt
    uint8_t                     cable_len,
    uint8_t                     autoclass)
{
    uint8_t buf[PD_BUFFER_SIZE] = {
        COMMAND_KEY,
        DUMMY_SEQ_NUM,
        0x05,
        BT_LLDP_PD_KEY,
        channel,
        ((requested_power_single >> 8) & 0xFF),
        (requested_power_single & 0xFF),
        ((requested_power_dual_a >> 8) & 0xFF),
        (requested_power_dual_a & 0xFF),
        ((requested_power_dual_b >> 8) & 0xFF),
        (requested_power_dual_b & 0xFF),
        (autoclass<<4) + cable_len,
        DUMMY_BYTE
    };
    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    return MESA_RC_OK;
}

static
mesa_rc meba_poe_pd69200bt_ctrl_get_port_layer2_lldp_pse_data(
    const meba_poe_ctrl_inst_t *const inst,
    meba_poe_port_handle_t      channel,
    uint16_t                   *pse_allocated_power_a_or_single,
    uint16_t                   *pse_allocated_power_b,
    uint16_t                   *pse_max_power,
    uint8_t                    *assigned_class,
    uint8_t                    *status,
    uint8_t                    *power_bits)
{
    uint8_t  buf[PD_BUFFER_SIZE]  = {
        REQUEST_KEY,
        DUMMY_SEQ_NUM,
        CHANNEL_KEY,
        BT_LLDP_PSE_KEY,
        channel,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE,
        DUMMY_BYTE
    };

    MESA_RC(pd69200_tx(inst, __FUNCTION__, __LINE__, buf));

    *pse_allocated_power_a_or_single = (buf[2] << 8) + buf[3];
    *pse_allocated_power_b           = (buf[4] << 8) + buf[5];
    *pse_max_power                   = (buf[6] << 8) + buf[7];
    *assigned_class                  =  buf[8];
    *status                          =  buf[9];
    *power_bits                      =  buf[10];

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200bt_ctrl_cfg_set(
    const meba_poe_ctrl_inst_t  *const inst,
    meba_poe_cfg_t              *cfg)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_INFO, "%s Failed\n",  __FUNCTION__);
        return MESA_RC_ERROR;
    }

    meba_poe_cfg_t *current_cfg =
            &(((poe_driver_private_t *)(inst->private_data))->cfg.global);

    if (current_cfg->primary_max_power == cfg->primary_max_power &&
        current_cfg->backup_max_power == cfg->backup_max_power ) {
        return MESA_RC_OK;
    }

    DEBUG(inst, MEBA_TRACE_LVL_INFO, "Update configuration for controller");

    uint16_t  power_consumption;
    uint16_t  max_shutdown_voltage;
    uint16_t  min_shutdown_voltage;
    uint8_t   bank;
    uint16_t  power_limit;
    MESA_RC(pd69200_get_power_supply_parameters(
        inst,
        &power_consumption,
        &max_shutdown_voltage,
        &min_shutdown_voltage,
        &bank,
        &power_limit));

    power_limit = cfg->primary_max_power;
    uint8_t guard_band = 0x2; // We set guard to 2W in order to get priority to take over as soon as possible.

    MESA_RC(meba_poe_pd69200_set_power_banks(
        inst,
        bank,
        power_limit,
        max_shutdown_voltage,
        min_shutdown_voltage,
        guard_band));

    *current_cfg = *cfg;
    return MESA_RC_OK;
}


mesa_rc meba_poe_pd69200bt_ctrl_port_status_get(
        const meba_poe_ctrl_inst_t     *const inst,
        meba_poe_port_handle_t          handle,
        meba_poe_port_status_t         *const port_status)
{
    if (port_status == NULL)  {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s port_status is NULL pointer", __FUNCTION__);
        return MESA_RC_ERROR;
    }
    port_status->chip_state = meba_poe_pd69200_get_chipset(inst);

    if (port_status->chip_state == MEBA_POE_FIRMWARE_UPGRADE) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Firmware upgrading", __FUNCTION__);
        port_status->assigned_pd_class_a = -1;
        port_status->assigned_pd_class_b = -1;
        port_status->pd_structure = MEBA_POE_PORT_PD_STRUCTURE_NOT_PERFORMED;
        port_status->state = MEBA_POE_PORT_STATE_DISABLED;
        port_status->power = 0;
        port_status->current = 0;
        port_status->voltage = 0;
        port_status->requested_power = 0;
        return MESA_RC_OK;
    }

    if (port_status->chip_state != MEBA_POE_CHIPSET_FOUND) {
        DEBUG(inst, MEBA_TRACE_LVL_DEBUG, "%s Device not ready for reading", __FUNCTION__);
        return MESA_RC_ERROR;
    }

    if (handle >= inst->port_map_length) {
        DEBUG(inst, MEBA_TRACE_LVL_ERROR, "%s Invalid handle: %d", __FUNCTION__, handle);
        return MESA_RC_ERR_PARM;
    }


    meba_poe_port_handle_t channel = handle;
    uint8_t  port_state;
    uint8_t  enable;
    uint8_t  assigned_class;
    uint16_t measured_port_power;
    uint8_t  last_shutdown_error_status;
    uint8_t  port_event;

    MESA_RC(meba_poe_pd69200bt_ctrl_get_BT_port_status(
        inst,
        channel,
        &port_state,
        &enable,
        &assigned_class,
        &measured_port_power,
        &last_shutdown_error_status,
        &port_event));
    port_status->assigned_pd_class_a = (assigned_class & 0xF0) >> 4;
    port_status->assigned_pd_class_b = assigned_class & 0xF;
    if (port_status->assigned_pd_class_a == 0xC) {
        port_status->assigned_pd_class_a = -1;
    }
    if (port_status->assigned_pd_class_b == 0xC) {
        port_status->assigned_pd_class_b = -1;
    }
    port_status->power = measured_port_power * 100;
    // See table 4 in the user guide for understanding the conversion - we do not support all status values.
    switch (port_state) {
        case  e0x80_2P_Port_delivering_non_IEEE:
        case  e0x81_2P_Port_delivering_IEEE:
        case  e0x82_4P_Port_that_deliver_only_2_Pair_non_IEEE:
        case  e0x83_4P_Port_delivering_2P_non_IEEE:
        case  e0x84_4P_Port_delivering_4P_non_IEEE:
        case  e0x85_4P_Port_delivering_2P_IEEE_SSPD:
        case  e0x86_4P_Port_delivering_4P_IEEE_SSPD:
        case  e0x87_4P_Port_delivering_4P_IEEE_DSPD_1st_phase:
        case  e0x88_4P_Port_delivering_2P_IEEE_DSPD:
        case  e0x89_4P_Port_delivering_4P_IEEE_DSPD:
            port_status->state = MEBA_POE_PORT_STATE_DELIVERING_POWER;
            break;

        case e0x08_Port_is_off_Disable_all_ports_pin_is_active:
        case e0x1A_Port_is_off_User_setting:
        case e0x22_Port_is_off_Configuration_change:
            port_status->state = MEBA_POE_PORT_STATE_DISABLED;
            break;

        // Interim state, detection going on  -     ePort_is_off_Detection_is_in_process
        case e0x1B_ePort_is_off_Detection_is_in_process:
        case e0xA8_Open_Port_is_not_connected:  // typical value when nothing is connected to the port
            port_status->state = MEBA_POE_PORT_STATE_SEARCHING;
            break;

        // Port is off due to miselenious reasones
        case e0x06_Port_is_off_Main_supply_voltage_is_high:
        case e0x07_Port_is_off_Main_supply_voltage_is_low:
        case e0x12_Port_is_off_Internal_hardware_fault:
        case e0x1F_Port_is_off_Overload_state:
        case e0x34_Port_is_off_Short_condition:
            port_status->state = MEBA_POE_PORT_STATE_FAULT;
            break;

        case e0x1E_Port_is_off_Underload_state:
        case e0x20_Port_is_off_Power_budget_exceeded:
        case e0x24_Port_is_off_Voltage_injection_into_the_port:
        case e0x25_Port_is_off_Improper_Cap_Det_results_or_Det_val_indicating_short:
        case e0x26_Port_is_off_Discharged_load:
        case e0x35_Port_is_off_Over_temperature_at_the_port:
        case e0x36_Port_is_off_Device_is_too_hot:
        case e0x3C_Power_Mng_Static_calc_pwr_exceed_pwr_limit:
        case e0x3D_Power_Management_Static_ovl:
        case e0x41_Port_is_off_Power_denied_Hardware_power_limit:
        case e0x43_Port_is_off_Class_Error:
        case e0xA0_Force_Power_BT_Error:
        case e0x1c_Port_is_off_Non_802_3AF_AT_powered_device: // Non-standart PD connected
        case e0xA7_Connection_Check_error:      // normal status when Ethernet link as laptop is conencted to this port

        case e0x11_Port_is_yet_undefined:
        case e0x44_Port_turn_off_during_host_crash:
        case e0x45_Delivering_power_forced_off_during_host_crash:
        case e0x46_Enabled_port_forced_off_during_host_crash:
        case e0x47_Forced_power_crash_error:
        case e0x48_Port_is_off_recovery_UDL:
        case e0x49_Port_is_off_recovery_PG:
        case e0x4A_Port_is_off_recovery_OVL:
        case e0x4B_Port_is_off_recovery_SC:
        case e0x4C_Port_is_off_recovery_voltage_injection:
        case eBT_PORT_STATUS_ONKNOWN:

            port_status->state = MEBA_POE_PORT_STATE_OTHER_FAULT;
            break;
        default:
            // This shall never happen all states should be covered.
            DEBUG(inst, MEBA_TRACE_LVL_ERROR, "Port %d: Unknown port state: 0x%X",
                  inst->port_map[handle].port_no, port_state);
            port_status->state = MEBA_POE_PORT_STATE_OTHER_FAULT;
            break;

    }

    port_status->requested_power = 0;
    port_status->auto_class = 1 << 2; // We do support auto class
    if (port_status->state == MEBA_POE_PORT_STATE_DELIVERING_POWER) {
        uint8_t  port_phy_info;
        uint8_t  measured_class;
        uint8_t  requested_class;
        uint16_t requested_power;
        uint16_t assigned_power = 0;
        uint8_t  auto_class_support;
        uint16_t auto_class_measurement;
        MESA_RC(meba_poe_pd69200bt_ctrl_get_BT_port_class(
            inst,
            channel,
            &port_state,
            &port_phy_info,
            &measured_class,
            &requested_class,
            &requested_power,
            &assigned_class,
            &assigned_power,
            &auto_class_support,
            &auto_class_measurement));

        port_status->requested_power = assigned_power * 100; // Convert from deciwatt to milliWatts
        port_status->pd_structure = port_phy_info & 0x0F;

        port_status->measured_pd_class_a = (measured_class & 0xF0) >> 4;
        if ( port_status->measured_pd_class_a == 0xC ) {
            port_status->measured_pd_class_a = -1;
        }

        port_status->measured_pd_class_b = measured_class & 0xF;
        if ( port_status->measured_pd_class_b == 0xC ) {
            port_status->measured_pd_class_b = -1;
        }

        port_status->requested_pd_class_a = (requested_class & 0xF0) >> 4;
        if ( port_status->requested_pd_class_a == 0xC ) {
            port_status->requested_pd_class_a = -1;
        }

        port_status->requested_pd_class_b = requested_class & 0xF;
        if ( port_status->requested_pd_class_b == 0xC ) {
            port_status->requested_pd_class_b = -1;
        }

        port_status->autoclass_support = auto_class_support;
        if (port_status->autoclass_support == 0x2) {
            port_status->measured_autoclass_power = auto_class_measurement * 100; // Convert from deciwatt to milliWatts
        } else {
            port_status->measured_autoclass_power = 0;
        }

        // auto_class_support = 0 : autoclass detection not performed.
        port_status->auto_class |= auto_class_support ? 2 : 0;
    }

    uint16_t main_voltage = 0;
    uint16_t calculated_current = 0;
    uint16_t port_power_consumption = 0;
    uint16_t port_voltage = 0;

    if (port_status->state == MEBA_POE_PORT_STATE_DELIVERING_POWER) {
        meba_poe_pd69200bt_get_BT_port_measurements(
            inst,
            channel,
            &main_voltage,
            &calculated_current,
            &port_power_consumption,
            &port_voltage);
    }
    port_status->power = port_power_consumption * 100;
    port_status->current = calculated_current;
    port_status->voltage = port_voltage * 100;

    uint16_t pse_allocated_power_a_or_single;
    uint16_t pse_allocated_power_b;
    uint16_t pse_max_power;
    uint8_t  layer2_status;
    uint8_t  power_bits;

    MESA_RC(meba_poe_pd69200bt_ctrl_get_port_layer2_lldp_pse_data(
        inst,
        channel,
        &pse_allocated_power_a_or_single,
        &pse_allocated_power_b,
        &pse_max_power,
        &assigned_class,
        &layer2_status,
        &power_bits));

    port_status->power_pairs_control_ability = false;  // TODO assign real value
    port_status->pse_alloc_power_alt_a = pse_allocated_power_a_or_single * 100;
    port_status->pse_alloc_power_alt_b = pse_allocated_power_b * 100;
    port_status->pse_max_avail_power   = pse_max_power * 100;
    port_status->power_status          = (power_bits & 0x3) << 10 | (power_bits & 0xC) << 12;

    meba_poe_port_cfg_t *port_cfg =
        &(((poe_driver_private_t *)(inst->private_data))->cfg.ports[handle]);

    meba_poe_port_private_status_t *current_port_status =
        &(((poe_driver_private_t *)(inst->private_data))->status.ports[handle]);

    port_status->requested_power_mode_a = current_port_status->requested_power_mode_a;
    port_status->requested_power_mode_b = current_port_status->requested_power_mode_b;

    // These values are used to fill basic fields of LLDP frame
    switch (power_bits & 0x3) {
        case 0: // Undefined
            port_status->pse_data.pse_power_pair = 1;
        break;
        case 1: // Alternative A
            port_status->pse_data.pse_power_pair = 1;
        break;
        case 2: // Alternative B
            port_status->pse_data.pse_power_pair = 2;
        break;
        case 3: // Both alternatives
            port_status->pse_data.pse_power_pair = 1;
        break;
    }

    if ( port_status->assigned_pd_class_a >= 4 ) {
        port_status->pse_data.power_class = 5; // Note: value 1:class=0. value 2:class=1, etc. 5 = Class 4 and above
    } else if ( port_status->assigned_pd_class_a  < 0 ) {
        port_status->pse_data.power_class = 1;
    }

    // these values are used to fill DLL classification fields of LLDP frame

    // type << 6 | source << 4 | prio
    uint8_t type = 1; // alvays a PSE
    uint8_t source = 1; // Primary Power Souce

    port_status->pse_data.pse_power_type        =  type << 6 | source << 4 | port_cfg->priority;

    // I am not sure what to put here, so we use the sum
    port_status->pse_data.pse_allocated_power   = port_status->pse_alloc_power_alt_a + port_status->pse_alloc_power_alt_b;
    port_status->pse_data.pd_requested_power    = current_port_status->requested_power_mode_a + current_port_status->requested_power_mode_b;

    // Proprietary parameter. Cable len in meters
    port_status->pse_data.cable_len             = 100;


    if ((layer2_status & 0xF) >= 3) {
        port_status->reserved_power = port_status->requested_power; 
    } else {
        port_status->reserved_power = port_status->power;
    }

    port_status->system_setup = 2; // This value is specificed in Table 79-6f IEEE 803.2bt/D3.7  Type 3 PSE = 0. Type 4 PSE = 2.

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200bt_ctrl_port_pd_data_set(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_data_t             *pd_data)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    return meba_poe_pd69200bt_ctrl_set_port_layer2_lldp_pd_data(
        inst,
        handle,
        pd_data->pd_requested_power/100, // convert from milliwatt to deciwatt 
        0,
        0,
        10, // corresponds to 100m
        0);
}

mesa_rc meba_poe_pd69200bt_ctrl_port_pd_bt_data_set(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle,
    meba_poe_pd_bt_data_t          *pd_data)
{
    if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    MESA_RC(meba_poe_pd69200bt_ctrl_set_port_layer2_lldp_pd_data(
        inst,
        handle,
        pd_data->pd_requested_power_single/100, // convert from milliwatt to deciwatt 
        pd_data->pd_requested_power_alt_a/100, // convert from milliwatt to deciwatt 
        pd_data->pd_requested_power_alt_b/100, // convert from milliwatt to deciwatt 
        10, // corresponds to 100m
        0));

    meba_poe_port_private_status_t *current_port_status =
        &(((poe_driver_private_t *)(inst->private_data))->status.ports[handle]);

    // Save requested power values in driver private data.
    // The request values are needed to construct LLDP to be sent to PD.
    current_port_status->requested_power_mode_a = pd_data->pd_requested_power_alt_a;
    current_port_status->requested_power_mode_b = pd_data->pd_requested_power_alt_b;

    return MESA_RC_OK;

}

mesa_rc meba_poe_pd69200bt_ctrl_port_pd_data_clear(
    const meba_poe_ctrl_inst_t     *const inst,
    meba_poe_port_handle_t          handle)
{
     if (meba_poe_pd69200_get_chipset(inst) != MEBA_POE_CHIPSET_FOUND) {
        return MESA_RC_ERROR;
    }

    // Only way to disable LLDP is to disable PoE and then re-enable
    MESA_RC(meba_poe_pd69200bt_ctrl_set_BT_port_parameters(
        inst, handle, 0, 0xFF, 0xFF, 0xFF, 0xFF));
    
    MESA_RC(meba_poe_pd69200bt_ctrl_set_BT_port_parameters(
        inst, handle, 1, 0xFF, 0xFF, 0xFF, 0xFF));

    meba_poe_port_private_status_t *current_port_status =
        &(((poe_driver_private_t *)(inst->private_data))->status.ports[handle]);

    current_port_status->requested_power_mode_a = 0;
    current_port_status->requested_power_mode_b = 0;

    return MESA_RC_OK;
}

mesa_rc meba_poe_pd69200bt_chip_initialization(
    const meba_poe_ctrl_inst_t     *const inst)
{
    if (MEBA_POE_CHIPSET_FOUND != meba_poe_pd69200_get_chipset(inst)) {
        return MESA_RC_OK;
    }

    // I2C restart enable - Initializes the I2C module system after 10 seconds of inactivity.
    MESA_RC(meba_poe_pd69200_individual_mask_set(inst, I2C_RESTART_ENABLE, 1));
    // Turn off lowest priority port, when a higher priority has a PD connected.
    MESA_RC(meba_poe_pd69200_individual_mask_set(inst, IGNORE_HIGH_PRIORITY, 0));
    // Support High res detection.
    MESA_RC(meba_poe_pd69200_individual_mask_set(inst, SUPPORT_HIGH_RES_DETECTION, 1));
    // Enable port poe led.
    MESA_RC(meba_poe_pd69200_individual_mask_set(inst, LED_STREAM_TYPE, 2));
    MESA_RC(pd69200_temp_matrix_init(inst));
    MESA_RC(pd69200_temp_matrix_set(inst));
    MESA_RC(pd69200_program_global_matrix(inst));

    return MESA_RC_OK;
}

void meba_pd69200bt_driver_init(
    meba_poe_ctrl_inst_t       *inst,
    char const                 *adapter_name, 
    int                         adapter_fd, 
    meba_poe_ctrl_cap_t         capabilities,
    meba_poe_port_properties_t *port_map,
    uint32_t                    port_map_length,
    meba_poe_psu_input_prob_t   *psu_map,
    uint32_t                    psu_map_length,
    meba_debug_t                debug)        /**< Board debug output */
{
    int i;

    static meba_poe_ctrl_api_t meba_pd69200bt_api = {
        .meba_poe_ctrl_do_detection = meba_poe_pd69200_do_detection,
        .meba_poe_ctrl_chip_initialization = meba_poe_pd69200bt_chip_initialization,
        .meba_poe_ctrl_sync = meba_poe_pd69200_sync,
        .meba_poe_ctrl_reset_command = meba_poe_pd69200_ctrl_reset_command,
        .meba_poe_ctrl_version_get = meba_poe_pd69200_ctrl_version_get,
        .meba_poe_ctrl_port_cfg_set = meba_poe_pd69200bt_ctrl_port_cfg_set,
        .meba_poe_ctrl_port_status_get = meba_poe_pd69200bt_ctrl_port_status_get,
        .meba_poe_ctrl_cfg_set = meba_poe_pd69200bt_ctrl_cfg_set,
        .meba_poe_ctrl_status_get = meba_poe_pd69200_ctrl_status_get,
        .meba_poe_ctrl_debug = meba_poe_pd69200_ctrl_debug,
        .meba_poe_ctrl_firmware_upgrade = meba_poe_pd69200_ctrl_firmware_upgrade,
        .meba_poe_ctrl_prepare_firmware_upgrade = meba_poe_pd69200_ctrl_prepare_firmware_upgrade,
        .meba_poe_ctrl_port_capabilities_get = meba_poe_pd69200_ctrl_port_capabilities_get,
        .meba_poe_ctrl_port_pd_data_set = meba_poe_pd69200bt_ctrl_port_pd_data_set,
        .meba_poe_ctrl_port_pd_bt_data_set = meba_poe_pd69200bt_ctrl_port_pd_bt_data_set,
        .meba_poe_ctrl_port_pd_data_clear = meba_poe_pd69200bt_ctrl_port_pd_data_clear,
    };

    poe_driver_private_t *private_data = malloc(sizeof(poe_driver_private_t));
    private_data->debug = debug;
    private_data->cfg.ports = malloc(sizeof(meba_poe_port_cfg_t)*port_map_length);
    private_data->status.ports = malloc(sizeof(meba_poe_port_private_status_t)*port_map_length);
    for (i=0; i<port_map_length; ++i) {
        private_data->status.global.chip_state = MEBA_POE_CHIPSET_DETECTION;
    }
    private_data->builtin_firmware = "/etc/mscc/poe/firmware/mscc_firmware_bt.txt";
    inst->api = &meba_pd69200bt_api;
    inst->private_data = private_data;
    inst->adapter_fd = adapter_fd;
    inst->adapter_name = adapter_name;
    inst->capabilities = capabilities;
    inst->port_map = port_map;
    inst->port_map_length = port_map_length;
    inst->psu_map = psu_map;
    inst->psu_map_length = psu_map_length;
    DEBUG(inst, MEBA_TRACE_LVL_DEBUG,"%s Done", __FUNCTION__);
    return;
}
 

