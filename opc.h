/* opc.h: MIPR OpCodes          */
/* Copyright (c) 2017 Ryan Kerr */

#ifndef _MIPR_OPC_
#define _MIPR_OPC_
#include "reg.h"

#define LONG(a,b) (a<<8)|b
#define HI(a) (a&0xF0)>>4
#define LO(a) (a&0x0F)

void nop();
void opr();
void ldn();
void ldm();
void jmp();
void pnc();

#endif
