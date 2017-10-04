/* opc.c: MIPR OpCodes          */
/* Copyright (c) 2017 Ryan Kerr */

#include <stdio.h>
#include "opc.h"
#include "reg.h"

#define OVERFLOW 2
#define NEGATIVE 4

void nop() {

}

void opr() {
    switch(r[0xA]) {
        case 1:
            if(0xFF<r[HI(r[8])]+r[LO(r[8])])
                r[0xF] |= OVERFLOW;
            else
                r[0xF] &= ~OVERFLOW;
            r[HI(r[8])] += r[LO(r[8])];
            break;
        case 2:
            if(0xFF<r[HI(r[8])]*r[LO(r[8])])
                r[0xF] |= OVERFLOW;
            else
                r[0xF] &= ~OVERFLOW;
            r[HI(r[8])] *= r[LO(r[8])];
            break;
        case 3:
            if(r[HI(r[8])]-r[LO(r[8])]<0) {
                r[0xF] |= NEGATIVE;
                r[HI(r[8])] = -1*(r[HI(r[8])] - r[LO(r[8])]);
            }
            else {
                r[0xF] &= ~NEGATIVE;
                r[HI(r[8])] -= r[LO(r[8])];
            }
            break;
        case 4:
            if(r[HI(r[8])])
                r[HI(r[8])] /= r[LO(r[8])];
            break;
        case 5:
            break;
    }
}

void ldn() {
    r[r[0xA]] = r[8];
}

void ldm() {
    r[r[0xA]] = m[LONG(r[8],r[9])];
}

void jmp() {
    printf("%02X & %02X", r[0xF], r[0xA]);
    if(!r[0xA]||r[0xF]&r[0xA]) {
        *pc = LONG(r[8],r[9])-1;
        printf(" -> %04X", *pc);
    }
}

void pnc() {
    printf("\nPANIC: ");
    for(int x=0; x<16; x++)
        printf("%02X ", r[x]);
}
