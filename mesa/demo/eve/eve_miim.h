/*
 * eve_miim.h
 *
 *  Created on: Oct 30, 2014
 *      Author: jsa
 */

#ifndef _EVE_MIIM_H_
#define _EVE_MIIM_H_

void MIIM_set_debug(int on);
int  miim_setgpio(int pin, int val);
long miim_read(void *handle, int phynum, int regnum);
int  miim_write(void *handle, int phynum, int regnum, unsigned long value);
int  miim_cmd_microcmd(void *handle, const char *cmd_line, char *resbuf, int maxlen);
int  miim_cmd_microsetup(void *handle, const char *cmd, const char *param, char *resbuf);

#endif /* _EVE_MIIM_H_ */
