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

#ifndef _MSCC_APPL_CLI_H_
#define _MSCC_APPL_CLI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "mscc/ethernet/board/api.h"

/* Initialize CLI */
void mscc_appl_cli_init(mscc_appl_init_t *init);

/* CLI request block */
typedef struct {
    /* Parameter parser input */
    const char *cmd;
    const char *stx;
    const char *cmd_org;
    int   parm_parsed;
    uint32_t cmd_flags;

    mesa_bool_t set;
    mesa_bool_t port_list[128 + 1];
    mesa_port_no_t port_no;

    mesa_vid_t  vid;

    // Keywords
    mesa_bool_t enable;
    mesa_bool_t disable;

    // MEBA instance
    meba_inst_t inst;

    // Module specific parser data
    uint8_t module_data[10240];
    void    *module_req;
} cli_req_t;

#define CLI_CMD_FLAG_NONE      0x00000000
#define CLI_CMD_FLAG_ALL_PORTS 0x00000001

/* CLI command entry */
typedef struct cli_cmd_t {
    const char         *syntax;    /* Syntax string */
    const char         *descr;     /* Description string */
    void (* func)(cli_req_t *req); /* Command function */
    uint32_t           flags;      /* Optional command flags */
    int (* func2)(int argc, const char **argv); /* Command function */

    /* Internal fields */
    struct cli_cmd_t *next;       /* Next in registration list */
    struct cli_cmd_t *match_next; /* Next in match list */
} cli_cmd_t;

void mscc_appl_cli_cmd_reg(cli_cmd_t *cmd);

#define CLI_PARM_FLAG_NONE   0x00000000 /* No flags */
#define CLI_PARM_FLAG_NO_TXT 0x00000001 /* Suppress identification text */
#define CLI_PARM_FLAG_SET    0x00000002 /* Set operation parameter */
#define CLI_PARM_FLAG_DUAL   0x00000004 /* Dual parameter */

/* CLI parameter entry */
typedef struct cli_parm_t {
    const char            *txt;    /* Identification text */
    const char            *help;   /* Help text */
    const uint32_t        flags;   /* Miscellaneous flags */
    int  (* parse_func)(cli_req_t *req); /* Parser function */
    void (* cmd_func)(cli_req_t *req);   /* Optional command function */

    /* Internal fields */
    struct cli_parm_t     *next;   /* Next in registration list */
    mesa_bool_t           done;    /* Temporary flag */
} cli_parm_t;

void mscc_appl_cli_parm_reg(cli_parm_t *parm);

const char *cli_bool_txt(mesa_bool_t enabled);
char *cli_mac_txt(const uint8_t *mac, char *buf);
mesa_port_no_t iport2uport(mesa_port_no_t iport);
mesa_port_no_t uport2iport(mesa_port_no_t uport);
void cli_table_header(const char *txt);
int cli_parm_u8(cli_req_t *req, uint8_t *val, uint32_t min, uint32_t max);
int cli_parm_u16(cli_req_t *req, uint16_t *val, uint32_t min, uint32_t max);
int cli_parm_u32(cli_req_t *req, uint32_t *val, uint32_t min, uint32_t max);
const char *cli_parse_find(const char *cmd, const char *stx);
int cli_parse_list(const char *buf, mesa_bool_t *list, uint32_t min, uint32_t max, mesa_bool_t def);
int cli_parse_values(const char *buf, uint32_t *arr, uint32_t *val_cnt, uint32_t min, uint32_t max, uint32_t max_num);
char *cli_port_list_txt(mesa_port_list_t *port_list, char *buf);
mesa_bool_t cli_port_list_member(mesa_port_list_t *port_list, mesa_port_no_t iport);
int cli_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* _MSCC_APPL_CLI_H_ */
