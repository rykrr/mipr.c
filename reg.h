/* reg.h: MIPR Registers        */
/* Copyright (c) 2017 Ryan Kerr */

#ifndef _MIPR_REG_
#define _MIPR_REG_

typedef unsigned char byte;
typedef unsigned short sppc;

extern byte m[0x10000];
extern byte rs[4][16];
extern byte *r;
extern sppc *sp, *pc;

#endif
