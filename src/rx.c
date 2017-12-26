#include "rx.h"
#include <stdio.h>

_1 rs[4][16];
_1 *r;
_1 m[0x10000];
_2 *sp, *pc, *re;
_2 *ab, *cd;

void clear_registers() {
    for(int x=0; x<4; x++)
        for(int y=0; y<16; y++)
            rs[x][y] = 0;
    r  = rs[0];
    sp = (_2*)&r[0xB];
    pc = (_2*)&r[0xD];
    ab = (_2*)&r[0x0];
    cd = (_2*)&r[0x2];
    re = (_2*)&r[0x8];
    *sp = 0x5000;
}

void ldc() {
    r[HI(r[8])] = r[LO(r[8])];
}

/* 0x10 - 0x17 */
void ldn() {
    printf("[ldn] r[%X], %02X\n", r[0xA], r[8]);
    r[r[0xA]] = r[8];
}

/* 0x18-0x1F */
void ldm() {
    printf("[ldm] r[%X], (%02X)@(%04X)\n", r[0xA], m[*ab], *ab);
    r[r[0xA]] = m[*ab];
}

/* 0x01 */
void ldx() {
    printf("[ldx] %04X (%02X & %02X)\n", *re, r[8], r[9]);
    *ab = *re;
}

void jmp() {
    printf("[jmp] %04X -> %04X\n", *pc, *ab-1);
    *pc = *ab-1;
}

void jpc() {
    printf("[jpc] %02X -> %02X\n", *pc, *ab-1);
    int hi = HI(r[8]), lo = LO(r[8]);
    printf("[jpc] %02X (<=>) %02X\n", r[hi], r[lo]);
    
    switch(r[0xA]) {
        case 0:
            if(r[hi]<r[lo])
                break;
            return;
        case 1:
            if(r[hi]>r[lo])
                break;
            return;
        case 2:
            if(r[hi]==r[lo])
                break;
            return;
    };
    printf("[jpc] -> \n");
    *pc=*ab-1;
}

void med() {
    printf("[mov] (%04X), (%02X)@r[%X]\n", *ab, r[r[0xA]], r[0xA]);
    m[*ab] = r[r[0xA]];
}

void map() {
    printf("[map] (%04X) ", *re);
    for(int i=0; m[*pc]; i++) {
        printf("%02X ", m[*pc]);
        m[*re+i] = m[++(*pc)];
    }
    puts("");
}
