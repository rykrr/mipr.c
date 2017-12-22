/* ax.h: Micro ALU              */
/* Copyright (c) 2017 Ryan Kerr */

#ifndef _MICRO_AX_
#define _MICRO_AX_
#include <stdio.h>

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "rx.h"

void nop();
void opr();
void ldn();
void ldm();
void jmp();
void jpc();
void frk();
void sig();
void sih();
void pnc();

#endif
