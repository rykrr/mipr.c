/* rx.h: Micro Registers        */
/* Copyright (c) 2017 Ryan Kerr */

#ifndef _MICRO_RX_
#define _MICRO_RX_

#define LONG(a,b) ((a<<8)|b)
#define HI(a) ((a&0xF0)>>4)
#define LO(a) (a&0x0F)

typedef unsigned char  _1;
typedef unsigned short _2;

extern _1 m[0x10000];
extern _1 rs[4][16];
extern _1 *r;
extern _2 *sp, *pc;
extern _2 *re;

void clear_registers();

void ldc();
void ldn();
void ldm();
void ldx();
void jmp();
void jpc();
void med(); // Memory Edit
void map(); // Memory Append

#endif
