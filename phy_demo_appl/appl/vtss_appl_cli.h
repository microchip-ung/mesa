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

#ifndef _VTSS_APPL_CLI_H_
#define _VTSS_APPL_CLI_H_

/* How to add a new CLI command:

   1. Determine the appropriate CLI file for the command:
      - General commands: vtss_appl_cli.c
      - Switch commands : vtss_appl_switch_cli.c
      - OTN commands    : vtss_appl_otn_cli.c

   2. Add command entry to cli_cmd_table[]

   3. Add command function cli_cmd_xxx()

   For each new parameter:

   4. Add parameter entry to cli_parm_table[]

   5. Add parameter function cli_parm_xxx()

   6. If needed, add parameter field to the 'cli_req_t' struct below.

 */

/* Initialize CLI */
void vtss_appl_cli_init(void);

/* CLI task */
void vtss_appl_cli_task(void);

/* Initialize switch commands */
void vtss_appl_cli_l2_init(void);

/* Initialize OTN commands */
void vtss_appl_cli_otn_init(void);

typedef unsigned char uchar;

#define CLI_TGT_MAX  64
#define CLI_ADDR_MAX (1<<8)  /* 8-bit address space */
#define CLI_PHY_MAX 32

/* CLI request block */
typedef struct {
    /* Parameter parser input */
    char *cmd;
    char *cmd2;
    char *stx;
    char *cmd_org;

    vtss_inst_t      api_inst;  /* API instance */
    vtss_appl_inst_t appl_inst; /* Application instance */
    vtss_appl_board_t *board;   /* Board */

    int   parm_parsed;

#if defined(VTSS_GPIOS)
    BOOL         gpio_list[VTSS_GPIO_NO_END];
#endif /* VTSS_GPIOS */
    BOOL  set;

  
    BOOL  port_list[VTSS_PORTS+1];

    BOOL  tgt_list[CLI_TGT_MAX];
    BOOL  addr_list[CLI_ADDR_MAX];
    BOOL  mmd_list[CLI_ADDR_MAX];
    u32   value;
    u32   page;
    u32   gpio_no;
    u32   clk_freq;
    BOOL  modify_frm;
    u32   port;
    u32   port_no;
    u16   mmd_addr;
    u32   addr;
    u8    miim_addr;
    char  pattern[129];

    vtss_port_speed_t speed;
    BOOL              fdx;
    u32               max_length;

    vtss_vid_t vid;
    uchar      mac[6];

#if defined(VTSS_FEATURE_LAYER2)
    vtss_vlan_port_type_t port_type;
    vtss_vlan_frame_t     frame_type;
#endif /* VTSS_FEATURE_LAYER2 */

    vtss_debug_layer_t api_layer;
    vtss_debug_group_t api_group;

    vtss_trace_layer_t trace_layer;
    vtss_trace_group_t group;
    vtss_trace_level_t level;
    BOOL egress;
    BOOL ingress;
    BOOL auto_keyword;
    BOOL binary;
    BOOL bytes;
    BOOL clear;
    BOOL discards;
    BOOL decimal;
    BOOL enable;
    BOOL errors;
    BOOL disable;
    BOOL equipment;
    BOOL facility;
    BOOL far_end;
    BOOL full;
    BOOL near_end;
    BOOL packets;
    BOOL warm;
    u32  etype;
    u32  mmd_address;
#if defined(VTSS_CHIP_10G_PHY)     
    vtss_phy_10g_loopback_t lb;
#endif /* VTSS_CHIP_10G_PHY */
#if defined(VTSS_FEATURE_WIS)
    u8      wis_overhead;
    u8      wis_tti_mode;
    u8      wis_gen_mode;
    u8      wis_ana_mode;
    u8      wis_tti[64];
    u16     wis_aisl;
    u16     wis_rdil;
    u16     wis_fault;
    u8      wis_oh_id;
    u8      wis_oh_val[26];
    u8      wis_err_inj;
    u32     sl;
    u32     wis_passthru;
    BOOL    wis_gen_mode_set;
    BOOL    wis_ana_mode_set;
    BOOL    wis_tti_mode_set;
    BOOL    wis_overhead_set;
    BOOL    wis_tti_set;
    BOOL    wis_loopback;
    BOOL    wis_err_inj_set;
    BOOL    wis_loopback_set;
    BOOL    ais_on_los;
    BOOL    ais_on_lof;
    BOOL    rdil_on_los;
    BOOL    rdil_on_lof;
    BOOL    rdil_on_ais;
    BOOL    wis_rx_force;
    BOOL    wis_tx_force;
    BOOL    wis_forced_ais_l;
    BOOL    wis_forced_rdi_l;
    BOOL    wis_pn_ebc_mode_s;
    BOOL    wis_pn_ebc_mode_l;
    BOOL    wis_pf_ebc_mode_l;
    BOOL    wis_pn_ebc_mode_p;
    BOOL    wis_pf_ebc_mode_p;
    BOOL    wis_perf_mode;
    BOOL    wis_perf_mode_bit;
#endif /* VTSS_FEATURE_WIS */
#ifdef VTSS_OPT_PHY_TIMESTAMP
    u8          eng_id;
    u8          clkfreq;
    BOOL        clk_freq_spec;
    u8          clk_src;
    BOOL        clk_src_spec;
    u8          rx_ts_pos;
    BOOL        rx_ts_pos_spec;
    u8          tx_fifo_mode;
    BOOL        tx_fifo_mode_spec;
    u8          encap_type;
    u8          flow_st_index;
    u8          flow_end_index;
    u8          flow_match_mode;
    u8          channel_map;
    BOOL        flow_id_spec;
    u8          flow_id;
    BOOL        pbb_spec;
    BOOL        pbb_en;
    u16         tpid;
    BOOL        mac_match_mode_spec;
    u8          mac_match_mode;
    BOOL        ptp_mac_spec;
    u8          ptp_mac[6];
    BOOL        vlan_chk_spec;
    BOOL        vlan_chk;
    BOOL        num_tag_spec;
    u8          num_tag;
    BOOL        tag_rng_mode_spec;
    u8          tag_rng_mode;
    u8          tag1_type;
    u8          tag2_type;
    u16         tag1_lower;
    u16         tag1_upper;
    u16         tag2_lower;
    u16         tag2_upper;
    BOOL        ip_mode_spec;
    u8          ip_mode;
    BOOL        sport_spec;
    u16         sport_val;
    u16         sport_mask;
    BOOL        dport_spec;
    u16         dport_val;
    u16         dport_mask;
    BOOL        addr_match_select_spec;
    u8          addr_match_select;
    BOOL        ipv4_addr_spec;
    vtss_ipv4_t ipv4_addr;
    BOOL        ipv4_mask_spec;
    vtss_ipv4_t ipv4_mask;
    u32         ipv6_addr[4];
    u32         ipv6_mask[4];
    BOOL        stk_depth_spec;
    u8          stk_depth;
    BOOL        stk_ref_point_spec;
    u8          stk_ref_point;
    BOOL        stk_lvl_0;
    u32         stk_lvl_0_lower;
    u32         stk_lvl_0_upper;
    BOOL        stk_lvl_1;
    u32         stk_lvl_1_lower;
    u32         stk_lvl_1_upper;
    BOOL        stk_lvl_2;
    u32         stk_lvl_2_lower;
    u32         stk_lvl_2_upper;
    BOOL        stk_lvl_3;
    u32         stk_lvl_3_lower;
    u32         stk_lvl_3_upper;
    BOOL        cw_en;
    BOOL        ach_ver_spec;
    u8          ach_ver;
    BOOL        channel_type_spec;
    u16         channel_type;
    BOOL        proto_id_spec;
    u16         proto_id;
    u8          action_id;
    BOOL        ptp_spec;
    u8          clk_mode;
    u8          delaym;
    u8          domain_meg_lower;
    u8          domain_meg_upper;
    BOOL        y1731_oam_spec;
    BOOL        ietf_oam_spec;
    u8          ietf_tf;
    u8          ietf_ds;
    u8          sig_mask;
    u8          version;
    u8          time_sec;
    vtss_timeinterval_t  latency_val;
    vtss_timeinterval_t  delay_val; 
    vtss_timeinterval_t  asym_val;
    BOOL    phy_mmd_access; // Indicate if a phy access is a MMD access.
    u32     blk_id_1588;         /* 1588 internal block Id's */
    u32     csr_reg_offset_1588; /* 1588 Internal block's CSR register offset*/
#endif /* VTSS_OPT_PHY_TIMESTAMP */
} cli_req_t;

#define CLI_CMD_FLAG_NONE     0x00000000
#define CLI_CMD_FLAG_NO_STORE 0x00000001

/* CLI command entry */
typedef struct cli_cmd_t {
    const char         *syntax;      /* Syntax string */
    const char         *descr;       /* Description string */
    void (* func)(cli_req_t *req);   /* Command function */
    u32                flags;        /* Optional command flags */
    void (* func2)(int argc, const char **argv); /* Command function */

    /* Internal fields */
    struct cli_cmd_t   *next;        /* Next in registration list */
    struct cli_cmd_t   *match_next;  /* Next in match list */
} cli_cmd_t;

void vtss_appl_cli_cmd_reg(cli_cmd_t *cmd);

#define CLI_PARM_FLAG_NONE   0x00000000 /* No flags */
#define CLI_PARM_FLAG_NO_TXT 0x00000001 /* Suppress identification text */
#define CLI_PARM_FLAG_SET    0x00000002 /* Set operation parameter */
#define CLI_PARM_FLAG_DUAL   0x00000004 /* Dual parameter */

/* CLI parameter entry */
typedef struct cli_parm_t {
    const char            *txt;    /* Identification text */
    const char            *help;   /* Help text */
    const u32             flags;   /* Miscellaneous flags */
    int  (* parse_func)(cli_req_t *req); /* Parser function */
    void (* cmd_func)(cli_req_t *req);   /* Optional command function */

    /* Internal fields */
    struct cli_parm_t     *next;   /* Next in registration list */
    BOOL                  done;    /* Temporary flag */
} cli_parm_t;

void vtss_appl_cli_parm_reg(cli_parm_t *parm);

char *cli_mac_txt(const uchar *mac, char *buf);
void cli_table_header(const char *txt);
int cli_parm_u8(cli_req_t *req, u8 *val, u32 min, u32 max);
int cli_parm_u16(cli_req_t *req, u16 *val, u32 min, u32 max);
int cli_parm_u32(cli_req_t *req, u32 *val, u32 min, u32 max);
char *cli_parse_find(char *cmd, char *stx);
int cli_parse_list(char *buf, BOOL *list, u32 min, u32 max, BOOL def);
int cli_parse_mac(char *cmd, uchar *mac_addr);

typedef enum {
    SYMREG_READ,
    SYMREG_WRITE,
    SYMREG_QUERY
} symreg_func_t;

void symreg_cli_regs_print(symreg_func_t func, char *pattern, u32 value);
void symreg_init(void);

#endif /* _VTSS_APPL_CLI_H_ */
