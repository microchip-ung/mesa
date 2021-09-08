/*
 * eve_jtag.h
 *
 *  Created on: Aug 4, 2014
 *      Author: jsa
 */

#ifndef _EVE_JTAG_H_
#define _EVE_JTAG_H_

typedef enum {
  P_JTAG_TCK,
  P_JTAG_TDO,
  P_JTAG_TMS,
  P_JTAG_RST,
  P_JTAG_TDI,
  P_JTAG_DBG,
  P_JTAG_END
  } jtagConfig_t;

int  jtag_MicroCmd(const char *cmd_line, char *resbuf, int maxlen);
int  jtag_SetConfig(jtagConfig_t param, int val);
void JTAG_set_debug(int on);
int  jtag_Vector(const char *vector, int rpt, int num);

#endif /* _EVE_JTAG_H_ */
