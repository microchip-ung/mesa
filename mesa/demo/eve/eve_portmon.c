/************************************************************-*- mode: C -*-*/
/*                                                                          */
/*           Copyright (C) 2014 Vitesse Semiconductor Corporation           */
/*                           All Rights Reserved.                           */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*                            Copyright Notice:                             */
/*                                                                          */
/*  This document contains confidential and proprietary information.        */
/*  Reproduction or usage of this document, in part or whole, by any means, */
/*  electrical, mechanical, optical, chemical or otherwise is prohibited,   */
/*  without written permission from Vitesse Semiconductor Corporation.      */
/*                                                                          */
/*  The information contained herein is protected by Danish and             */
/*  international copyright laws.                                           */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*  <DESCRIBE FILE CONTENTS HERE>                                           */
/*                                                                          */
/****************************************************************************/
/*  $Id: eve_portmon.c,v 1.2 2014/11/25 11:00:10 jsa Exp $                                                                    */
/****************************************************************************/
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "eve_sio.h"
#include <ctype.h>

#define MAXDB 10000

typedef struct {
        unsigned long cnt_hist[MAXDB]; // table in extended memory
        char cnt_chg[MAXDB];
        char cnt_type[MAXDB];
        int fast_ci,slow_ci;
        unsigned long db[MAXDB];
        int dbmax;
        int cur_view;
        unsigned long view_reg;
} t_portmon_mem;


int  stat_rd(SPI_STATE *spi, unsigned long addr);
void stat_wr(SPI_STATE *spi, unsigned long addr, unsigned long data);

int stats_cmd(const char *cmd_line, char *resbuf, int maxlen, void **portmon_mem, SPI_STATE *spi)
{
   int i;
   int fast_now;

   const char *x;
   char *q;
   unsigned long *p;
   unsigned long parm[4];
   unsigned long address;

   int outcnt,rdcnt;
   char cmd;
   int ci,ci_stop;
   unsigned long cnt_now,cnt_last;

   t_portmon_mem *S=(t_portmon_mem*)(*portmon_mem);

   // Init
   if (S==(t_portmon_mem*)0) {
           S = malloc(sizeof(t_portmon_mem));
           *portmon_mem=(void*)S;
   }

   outcnt=30;

   // commands: +xx: Poll xx targets
   //           -xx: Poll xx targets which has changed last time they were polled
   //           cyy,zz,xx: Register target xx as tgtid yy address zz (delta returned)
   //           vyy,zz,xx: Register target xx as tgtid yy address zz (value returned)
   //           wyy,zz   : Register tgtid yy address zz as the stat view register
   //           rzz: Read chip address zz
   //           !: Reset

   q=resbuf;

   q+=sprintf(q,"[");

   if (cmd_line[0]=='!') {
     for (i=0; i<MAXDB; i++) S->cnt_hist[i]=0,S->cnt_chg[i]=0,S->cnt_type[i]=0;
     S->fast_ci=0; S->slow_ci=0;
     S->dbmax=0;
     q+=sprintf(q,"v11");
   }
   else if (cmd_line[0]>='a') {
     x = cmd_line;
     while (*x) {
       cmd=*x;
       p = parm;

       do {
         *(p++)=strtoul(x+1,0,0);
         do x++; while (*x && *x!=' ' && *x!=',');
       } while (*x==',');
       if (*x==' ') x++;

       address = (parm[0] << 14) | parm[1];

       if (cmd=='r') {
               q+=sprintf(q,"%08X ",stat_rd(spi, address));
       }
       if (cmd=='w') {
               q+=sprintf(q,"ViewReg defined");
               S->view_reg = address;
       }
       if (cmd=='c' || cmd=='v') {
         if (parm[2]>S->dbmax) S->dbmax=(int)parm[2]; // typecast OK?
         S->db[parm[2]] = address;
         S->cnt_type[parm[2]]=1;
         if (cmd=='c') S->cnt_type[parm[2]]=2;
         q+=sprintf(q,"ADDED %ld %d",parm[2],S->dbmax);
       }
     };
   }
   else {
     rdcnt=(int)atol(cmd_line+1);
     fast_now=(cmd_line[0]=='-');
     ci=fast_now?S->fast_ci:S->slow_ci;
     ci_stop=ci;

     while (outcnt>0 && rdcnt>0) {
       ci=(ci+1)%(S->dbmax+1);

       if (ci==0 && !fast_now) q+=sprintf (q,"START ");

       if (S->cnt_type[ci]>0 &&
           (S->cnt_chg[ci] || !fast_now)) {

         // View change ?
         address = S->db[ci];
         if ((address>>22) && (address>>22)!=S->cur_view) {
           stat_wr(spi, S->view_reg, (address>>22)-1);
           S->cur_view = address>>22;
         }

         cnt_now = stat_rd(spi, S->db[ci]&0x3FFFFF);


         cnt_last=S->cnt_hist[ci];
         //cnt_now=cnt_last+1;
         if (cnt_now!=cnt_last) {
           S->cnt_hist[ci] = cnt_now;
           if (S->cnt_type[ci]==2) cnt_now-=cnt_last;
           q+=sprintf (q, "%04X%08lX ",ci,cnt_now);
           outcnt--;
           S->cnt_chg[ci]=1;
         } else {
           S->cnt_chg[ci]=0;
         }
         rdcnt--;
       };
       if (ci==ci_stop) break;
     }
     if (fast_now) S->fast_ci=ci; else S->slow_ci=ci;
     q+=sprintf(q,"OK");
   }

   q+=sprintf(q,"]\r\n");
   return strlen(resbuf);
}

int stat_rd(SPI_STATE *spi, unsigned long addr)
{
        char txbuf[7];
        char rxbuf[8];
        int  rxdata;
        unsigned char *res;

        SPI_STATE old_spi = *spi;

        spi->channel    = 0;
        spi->freq[0]    = 3125000;
        spi->padding[0] = 1;

        txbuf[0]=(unsigned char) (addr>>16);
        txbuf[1]=(unsigned char)((addr>>8)&0xff);
        txbuf[2]=(unsigned char) (addr&0xff);
        res = SPI_brw(spi, (unsigned char*)txbuf, 3, (unsigned char*)rxbuf, 4, 0);

        rxdata = res[3];
        rxdata |= ((unsigned long) res[2]) << 8;
        rxdata |= ((unsigned long) res[1]) << 16;
        rxdata |= ((unsigned long) res[0]) << 24;

        *spi = old_spi;
        return rxdata;
}

void stat_wr(SPI_STATE *spi, unsigned long addr, unsigned long data)
{
        char txbuf[7];

        SPI_STATE old_spi = *spi;

        spi->channel    = 0;
        spi->freq[0]    = 3125000;
        spi->padding[0] = 1;

        txbuf[0]=(unsigned char) (0x80|(addr>>16));
        txbuf[1]=(unsigned char)((addr>>8)&0xff);
        txbuf[2]=(unsigned char) (addr&0xff);
        txbuf[3]=(unsigned char) (data>>24);
        txbuf[4]=(unsigned char) (data>>16)&0xff;
        txbuf[5]=(unsigned char) (data>>8)&0xff;
        txbuf[6]=(unsigned char) (data)&0xff;

        SPI_brw(spi, (unsigned char*)txbuf, 7, 0,0,0);
        *spi = old_spi;
}

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
