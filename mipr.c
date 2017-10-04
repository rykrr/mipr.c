/* mipr.c: Simple Microprocessor */
/* Copyright (c) 2017 Ryan Kerr  */

#include <stdio.h>
#include <stdlib.h>
#include "opc.h"
#include "reg.h"

byte rs[4][16];
byte *r;
byte m[0x10000];
sppc *sp, *pc;

typedef struct code {
    const byte on, lo, hi;
    const byte mask,
               offs,
               args,
               flag;
    void (*fn)();
} CODE;

CODE nosort_codes[0xFF] = {
    { 1, 0x00, 0x00, 0xFF, 0x00, 0, 0, nop },   // No Operation
    { 1, 0x01, 0x09, 0xF0, 0x00, 1, 0, opr },   // MISC Operation
    { 1, 0x10, 0x17, 0xF0, 0x00, 1, 0, ldn },   // Load 8 from Next
    { 1, 0x18, 0x1F, 0xF0, 0x0A, 2, 0, ldm },   // Load 8 from Memory
    { 1, 0x20, 0x24, 0xF0, 0x00, 2, 0, jmp },   // Jump to MemAddr
    { 1, 0xFF, 0xFF, 0xFF, 0x00, 0, 0, pnc },   // PANIC
    { 0 }                                       // NULL TERMINATOR
};

CODE *opcode[0xFF];

void link_codes() {
    for(int i=0; i<0xFF; i++)
        opcode[i] = NULL;
    
    for(int x=0; nosort_codes[x].on; x++)
        for(int y=nosort_codes[x].lo; y<=nosort_codes[x].hi; y++)
            opcode[y] = &nosort_codes[x];
}

void clear_registers() {
    for(int x=0; x<4; x++)
        for(int y=0; y<16; y++)
            rs[x][y] = 0;
    r  = rs[0];
    sp = (sppc*)&r[0xB];
    pc = (sppc*)&r[0xD];
}

int load_file(const char *p, byte *b, int n) {
    int read = 0;
    FILE *f = fopen(p, "rb");
    
    if(f) {
        read = fread(b, sizeof(byte), n, f);
        fclose(f);
    }
    return read;
}

int main() {
    clear_registers();
    link_codes();
    
    int l = load_file("xe", m, 0xFF);
    
    if(!l)
        return 404;
    
    for(byte b; *pc<0xFF && m[*pc] != 0x0F; (*pc)++) {
        r[8] = r[9] = 0;
        if(b = m[*pc]) {
            printf("[%02X][%02X] ", *pc, b);
            
            CODE *c = opcode[b];
            if(c) {
                for(int i=0; i<c->args && i<2; i++)
                    r[8+i] = m[++(*pc)];
                r[0xA] = (b&~c->mask);//-c->offs;
                printf("(%01X: %02X %02X) ", r[0xA], r[8], r[9]);
                c->fn();
            }
            printf("\n");
        }
    }
    pnc();
    printf("\n");
}
