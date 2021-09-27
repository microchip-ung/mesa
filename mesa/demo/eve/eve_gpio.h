// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
/**
 *
 */

#ifndef _EVE_GPIO_H_
#define _EVE_GPIO_H_

#define MMAP_OFFSET (0x44C00000)
#define MMAP_SIZE   (0x481AEFFF-MMAP_OFFSET)

/* Clock Module Memory Registers */
#define CM_WKUP (0x44E00400)
#define CM_WKUP_ADC_TSC_CLKCTRL (CM_WKUP+0xBC)
#define CM_WKUP_MODULEMODE_ENABLE (0x02)
#define CM_WKUP_IDLEST_DISABLED (0x03<<16)

#define CM_PER (0x44E00000)
#define CM_PER_EPWMSS1_CLKCTRL (CM_PER+0xCC)
#define CM_PER_EPWMSS0_CLKCTRL (CM_PER+0xD4)
#define CM_PER_EPWMSS2_CLKCTRL (CM_PER+0xD8)

/* GPIO Memory Registers */
#define GPIO_REGISTER_SIZE (4)

#define GPIO0	(0x44E07000)
#define GPIO1	(0x4804C000)
#define GPIO2	(0x481AC000)
#define GPIO3	(0x481AE000)

#define GPIO_CLEARDATAOUT (0x190)
#define GPIO_SETDATAOUT   (0x194)
#define GPIO_OE           (0x134)
#define GPIO_DATAOUT      (0x13C)
#define GPIO_DATAIN       (0x138)

/* Analog Digital Converter Memory Registers */
#define ADC_TSC (0x44E0D000)

#define ADC_CTRL (ADC_TSC+0x40)
#define ADC_STEPCONFIG_WRITE_PROTECT_OFF (0x01<<2)
#define ADC_STEPENABLE (ADC_TSC+0x54)

#define ADCSTEPCONFIG1 (ADC_TSC+0x64)
#define ADCSTEPDELAY1  (ADC_TSC+0x68)
#define ADCSTEPCONFIG2 (ADC_TSC+0x6C)
#define ADCSTEPDELAY2  (ADC_TSC+0x70)
#define ADCSTEPCONFIG3 (ADC_TSC+0x74)
#define ADCSTEPDELAY3  (ADC_TSC+0x78)
#define ADCSTEPCONFIG4 (ADC_TSC+0x7C)
#define ADCSTEPDELAY4  (ADC_TSC+0x80)
#define ADCSTEPCONFIG5 (ADC_TSC+0x84)
#define ADCSTEPDELAY5  (ADC_TSC+0x88)
#define ADCSTEPCONFIG6 (ADC_TSC+0x8C)
#define ADCSTEPDELAY6  (ADC_TSC+0x90)
#define ADCSTEPCONFIG7 (ADC_TSC+0x94)
#define ADCSTEPDELAY7  (ADC_TSC+0x98)
#define ADCSTEPCONFIG8 (ADC_TSC+0x9C)
#define ADCSTEPDELAY8  (ADC_TSC+0xA0)

#define ADC_AVG0  (0x000)
#define ADC_AVG2  (0x001)
#define ADC_AVG4  (0x010)
#define ADC_AVG8  (0x011)
#define ADC_AVG16 (0x100)

#define ADC_FIFO0DATA (ADC_TSC+0x100)
#define ADC_FIFO_MASK (0xFFF)

#define INPUT    ((unsigned char)(1))
#define OUTPUT   ((unsigned char)(0))
#define PULLUP   ((unsigned char)(1))
#define PULLDOWN ((unsigned char)(0))
#define DISABLED ((unsigned char)(2))

/*      PinName #           PinName        GpioBank   #   Bank#  MuxName            Eeprom PWM */
#define P8_3    (38) // {   "GPIO1_6",     GPIO1,     38, 	6,	 "gpmc_ad6",        26,    FALSE, {0} })
#define P8_4    (39) // {   "GPIO1_7",     GPIO1,     39, 	7,	 "gpmc_ad7",        27,    FALSE, {0} })
#define P8_5    (34) // {   "GPIO1_2",     GPIO1,     34, 	2,	 "gpmc_ad2",        22,    FALSE, {0} })
#define P8_6    (35) // {   "GPIO1_3",     GPIO1,     35, 	3,	 "gpmc_ad3",        23,    FALSE, {0} })
#define P8_7    (66) // {   "TIMER4",      GPIO2,     66, 	2, 	 "gpmc_advn_ale",   41,    FALSE, {0} })
#define P8_8    (67) // {   "TIMER7",      GPIO2,     67, 	3,	 "gpmc_oen_ren",    44,    FALSE, {0} })
#define P8_9    (69) // {   "TIMER5",      GPIO2,     69, 	5,	 "gpmc_ben0_cle",   42,    FALSE, {0} })
#define P8_10   (68) // {   "TIMER6",      GPIO2,     68, 	4,	 "gpmc_wen",        43,    FALSE, {0} })
#define P8_11   (45) // {   "GPIO1_13",    GPIO1,     45, 	13,	 "gpmc_ad13",       29,    FALSE, {0} })
#define P8_12   (44) // {   "GPIO1_12",    GPIO1,     44, 	12,	 "gpmc_ad12",       28,    FALSE, {0} })
#define P8_13   (23) // {   "EHRPWM2B",    GPIO0,     23, 	23,	 "gpmc_ad9",        15,    TRUE,  (PWM){4, "EHRPWM2B", "ehrpwm.2:1"}})
#define P8_14   (26) // {   "GPIO0_26",    GPIO0,     26, 	26,	 "gpmc_ad10",       16,    FALSE, {0} })
#define P8_15   (47) // {   "GPIO1_15",    GPIO1,     47, 	15,	 "gpmc_ad15",       31,    FALSE, {0} })
#define P8_16   (46) // {   "GPIO1_14",    GPIO1,     46, 	14,	 "gpmc_ad14",       30,    FALSE, {0} })
#define P8_17   (27) // {   "GPIO0_27",    GPIO0,     27, 	27,	 "gpmc_ad11",       17,    FALSE, {0} })
#define P8_18   (65) // {   "GPIO2_1",     GPIO2,     65, 	1,	 "gpmc_clk",        40,    FALSE, {0} })
#define P8_19   (22) // {   "EHRPWM2A",    GPIO0,     22, 	22,	 "gpmc_ad8",        14,    TRUE,  (PWM){4, "EHRPWM2A", "ehrpwm.2:0"}})
#define P8_20   (63) // {   "GPIO1_31",    GPIO1,     63, 	31,	 "gpmc_csn2",       39,    FALSE, {0} })
#define P8_21   (62) // {   "GPIO1_30",    GPIO1,     62, 	30,	 "gpmc_csn1",       38,    FALSE, {0} })
#define P8_22   (37) // {   "GPIO1_5",     GPIO1,     37, 	5,	 "gpmc_ad5",        25,    FALSE, {0} })
#define P8_23   (36) // {   "GPIO1_4",     GPIO1,     36, 	4,	 "gpmc_ad4",        24,    FALSE, {0} })
#define P8_24   (33) // {   "GPIO1_1",     GPIO1,     33, 	1,	 "gpmc_ad1",        21,    FALSE, {0} })
#define P8_25   (32) // {   "GPIO1_0",     GPIO1,     32, 	0,	 "gpmc_ad0",        20,    FALSE, {0} })
#define P8_26   (61) // {   "GPIO1_29",    GPIO1,     61, 	29,	 "gpmc_csn0",       37,    FALSE, {0} })
#define P8_27   (86) // {   "GPIO2_22",    GPIO2,     86, 	22,	 "lcd_vsync",       57,    FALSE, {0} })
#define P8_28   (88) // {   "GPIO2_24",    GPIO2,     88, 	24,	 "lcd_pclk",        59,    FALSE, {0} })
#define P8_29   (87) // {   "GPIO2_23",    GPIO2,     87, 	23,	 "lcd_hsync",       58,    FALSE, {0} })
#define P8_30   (89) // {   "GPIO2_25",    GPIO2,     89, 	25,	 "lcd_ac_bias_en",  60,    FALSE, {0} })
#define P8_31   (10) // {   "UART5_CTSN",  GPIO0,     10, 	10,	 "lcd_data14",       7,    FALSE, {0} })
#define P8_32   (11) // {   "UART5_RTSN",  GPIO0,     11, 	11,	 "lcd_data15",       8,    FALSE, {0} })
#define P8_33    (9) // {   "UART4_RTSN",  GPIO0,     9,  	9,	 "lcd_data13",       6,    FALSE, {0} })
#define P8_34   (81) // {   "UART3_RTSN",  GPIO2,     81, 	17,	 "lcd_data11",      56,    TRUE,  (PWM){2, "EHRPWM1B", "ehrpwm.1:1"}})
#define P8_35    (8) // {   "UART4_CTSN",  GPIO0,     8,  	8,	 "lcd_data12",       5,    FALSE, {0} })
#define P8_36   (80) // {   "UART3_CTSN",  GPIO2,     80, 	16,	 "lcd_data10",      55,    TRUE,  (PWM){2, "EHRPWM1A", "ehrpwm.1:0"}})
#define P8_37   (78) // {   "UART5_TXD",   GPIO2,     78, 	14,	 "lcd_data8",       53,    FALSE, {0} })
#define P8_38   (79) // {   "UART5_RXD",   GPIO2,     79, 	15,	 "lcd_data9",       54,    FALSE, {0} })
#define P8_39   (76) // {   "GPIO2_12",    GPIO2,     76, 	12,	 "lcd_data6",       51,    FALSE, {0} })
#define P8_40   (77) // {   "GPIO2_13",    GPIO2,     77, 	13,	 "lcd_data7",       52,    FALSE, {0} })
#define P8_41   (74) // {   "GPIO2_10",    GPIO2,     74, 	10,	 "lcd_data4",       49,    FALSE, {0} })
#define P8_42   (75) // {   "GPIO2_11",    GPIO2,     75, 	11,	 "lcd_data5",       50,    FALSE, {0} })
#define P8_43   (72) // {   "GPIO2_8",     GPIO2,     72, 	8,	 "lcd_data2",       47,    FALSE, {0} })
#define P8_44   (73) // {   "GPIO2_9",     GPIO2,     73, 	9,	 "lcd_data3",       48,    FALSE, {0} })
#define P8_45   (70) // {   "GPIO2_6",     GPIO2,     70, 	6,	 "lcd_data0",       45,    TRUE,  (PWM){3, "EHRPWM2A", "ehrpwm.2:0"}})
#define P8_46   (71) // {   "GPIO2_7",     GPIO2,     71, 	7,	 "lcd_data1",       46,    TRUE,  (PWM){3, "EHRPWM2B", "ehrpwm.2:1"}})

#define P9_11   (30) // {   "UART4_RXD",   GPIO0,     30,  30,   "gpmc_wait0",       18,   FALSE, {0} })
#define P9_12   (60) // {   "GPIO1_28",    GPIO1,     60,  28,   "gpmc_ben1",        36,   FALSE, {0} })
#define P9_13   (31) // {   "UART4_TXD",   GPIO0,     31,  31,   "gpmc_wpn",         19,   FALSE, {0} })
#define P9_14   (50) // {   "EHRPWM1A",    GPIO1,     50,  18,   "gpmc_a2",          34,   TRUE, (PWM){6, "EHRPWM1A", "ehrpwm.1:0"}})
#define P9_15   (48) // {   "GPIO1_16",    GPIO1,     48,  16,   "mii1_rxd3",        32,   FALSE, {0} })
#define P9_16   (51) // {   "EHRPWM1B",    GPIO1,     51,  19,   "gpmc_a3",          35,   TRUE, (PWM){6, "EHRPWM1B", "ehrpwm.1:1"}})
#define P9_17    (5) // {   "I2C1_SCL",    GPIO0,      5,   5,   "spi0_cs0",          3,   FALSE, {0} })
#define P9_18    (4) // {   "I2C1_SDA",    GPIO0,      4,   4,   "spi0_d1",           2,   FALSE, {0} })
#define P9_19   (13) // {   "I2C2_SCL",    GPIO0,     13,  13,   "uart1_rtsn",        9,   FALSE, {0} })
#define P9_20   (12) // {   "I2C2_SDA",    GPIO0,     12,  12,   "uart1_ctsn",       10,   FALSE, {0} })
#define P9_21    (3) // {   "UART2_TXD",   GPIO0,      3,   3,   "spi0_d0",           1,   TRUE, (PWM){3, "EHRPWM0B", "ehrpwm.0:1"}})
#define P9_22    (2) // {   "UART2_RXD",   GPIO0,      2,   2,   "spi0_sclk",         0,   TRUE, (PWM){3, "EHRPWM0A", "ehrpwm.0:0"}})
#define P9_23   (49) // {   "GPIO1_17",    GPIO1,     49,  17,   "gpmc_a1",          33,   FALSE, {0} })
#define P9_24   (15) // {   "UART1_TXD",   GPIO0,     15,  15,   "uart1_txd",        12,   FALSE, {0} })
#define P9_25  (117) // {   "GPIO3_21",    GPIO3,    117,  21,   "mcasp0_ahclkx",    66,   FALSE, {0} })
#define P9_26   (14) // {   "UART1_RXD",   GPIO0,     14,  14,   "uart1_rxd",        11,   FALSE, {0} })
#define P9_27  (115) // {   "GPIO3_19",    GPIO3,    115,  19,   "mcasp0_fsr",       64,   FALSE, {0} })
#define P9_28  (113) // {   "SPI1_CS0",    GPIO3,    113,  17,   "mcasp0_ahclkr",    63,   TRUE, (PWM){4, "ECAPPWM2", "ecap.2"}})
#define P9_29  (111) // {   "SPI1_D0",     GPIO3,    111,  15,   "mcasp0_fsx",       61,   TRUE, (PWM){1, "EHRPWM0B", "ehrpwm.0:1"}})
#define P9_30  (112) // {   "SPI1_D1",     GPIO3,    112,  16,   "mcasp0_axr0",      62,   FALSE, {0} })
#define P9_31  (110) // {   "SPI1_SCLK",   GPIO3,    110,  14,   "mcasp0_aclkx",     65,   TRUE, (PWM){1, "EHRPWM0A", "ehrpwm.0:0"}})
#define P9_33    (4) // {   "AIN4",        0,          4,   4,   "",                 71,   FALSE, {0} })
#define P9_35    (6) // {   "AIN6",        0,          6,   6,   "",                 73,   FALSE, {0} })
#define P9_36    (5) // {   "AIN5",        0,          5,   5,   "",                 72,   FALSE, {0} })
#define P9_37    (2) // {   "AIN2",        0,          2,   2,   "",                 69,   FALSE, {0} })
#define P9_38    (3) // {   "AIN3",        0,          3,   3,   "",                 70,   FALSE, {0} })
#define P9_39    (0) // {   "AIN0",        0,          0,   0,   "",                 67,   FALSE, {0} })
#define P9_40    (1) // {   "AIN1",        0,          1,   1,   "",                 68,   FALSE, {0} })
#define P9_41   (20) // {   "CLKOUT2",     GPIO0,     20,  20,   "xdma_event_intr1", 13,   FALSE, {0} })
#define P9_42    (7) // {   "GPIO0_7",     GPIO0,      7,   7,   "ecap0_in_pwm0_out", 4,   TRUE, (PWM){0, "ECAPPWM0", "ecap.0"}})


#define CONFIG_MUX_PATH "/sys/kernel/debug/omap_mux"
#define SYSFS_GPIO_DIR  "/sys/class/gpio"

#define MAX_BUF 64

int  gpio_export(unsigned int gpio);
int  gpio_unexport(unsigned int gpio);
int  gpio_set_dir(unsigned int gpio, int set_output);
int  gpio_set_value(unsigned int gpio, int value);
int  gpio_get_value(unsigned int gpio);
int  gpio_set_edge(unsigned int gpio, char *edge);
int  gpio_fd_open(unsigned int gpio);
int  gpio_fd_close(int fd);
int  gpio_mm_init(void);
int  gpio_mm_set(unsigned int gpio, int value);
int  gpio_mm_get(unsigned int gpio);
int  gpio_mm_dir(unsigned int gpio, int dir);
int  gpio_mmdo_set(unsigned int gpio, int value);
int  gpio_mmdo_dir(unsigned int gpio, int dir);
void GPIO_set_debug(int on);

// Put this here, until we have a better place for it
void log2stderr(char *msg, ...);

#endif
