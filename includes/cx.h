/* ax.h: Micro ALU              */
/* Copyright (c) 2017 Ryan Kerr */

#ifndef _MICRO_CX_
#define _MICRO_CX_

#include "rx.h"

#include "ax.h"
#include "dx.h"
#include "qx.h"

typedef struct cx {
    const _1 on, lo, hi;
    const _1 mask,
             offs,
             args,
             flag;
    void (*fn)();
} code;

extern code  config[0xFF];
extern code *opcode[0xFF];

void link_codes();
#endif
