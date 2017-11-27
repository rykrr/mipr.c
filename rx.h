/* rx.h: Micro Registers        */
/* Copyright (c) 2017 Ryan Kerr */

#ifndef _MICRO_RX_
#define _MICRO_RX_

#define LONG(a,b) ((a<<8)|b)
#define HI(a) ((a&0xF0)>>4)
#define LO(a) (a&0x0F)

typedef unsigned char byte;
typedef unsigned short sppc;

extern byte m[0x10000];
extern byte rs[4][16];
extern byte *r;
extern sppc *sp, *pc;

#endif
