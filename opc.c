/* opc.c: MIPR OpCodes          */
/* Copyright (c) 2017 Ryan Kerr */

#include <stdio.h>
#include "opc.h"
#include "reg.h"

#define OVERFLOW 2
#define NEGATIVE 4

void nop() {
    ;;
}

void opr() {
    int hi = HI(r[8])%8,
        lo = LO(r[8])%8;
    
    switch(r[0xA]) {
        case 1:
            if(0xFF<r[hi]+r[lo])
                r[0xF] |= OVERFLOW;
            else
                r[0xF] &= ~OVERFLOW;
            r[hi] += r[lo];
            //printf("%02X + %02X", hi, lo);
            break;
        case 2:
            if(0xFF<r[hi]*r[lo])
                r[0xF] |= OVERFLOW;
            else
                r[0xF] &= ~OVERFLOW;
            r[hi] *= r[lo];
            break;
        case 3:
            if(r[hi]-r[lo]<0) {
                r[0xF] |= NEGATIVE;
                r[hi] = -1*(r[hi] - r[lo]);
            }
            else {
                r[0xF] &= ~NEGATIVE;
                r[hi] -= r[lo];
            }
            break;
        case 4:
            if(r[hi])
                r[hi] /= r[lo];
            break;
        case 5:
            r[hi] &= r[lo];
            break;
        case 6:
            r[hi] |= r[lo];
            break;
        case 7:
            r[hi] = (r[hi]|r[lo])&~(r[hi]&r[lo]);
            break;
        case 8:
            r[hi] = ~r[hi];
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
    if(!r[0xA]||r[0xF]&r[0xA])
        *pc = LONG(r[8],r[9])-1;
}

void jpc() {
    int hi = HI(r[8]), lo = LO(r[8]);
    
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
    
    *pc+=3;
}

void pnc() {
    printf("\nPANIC: ");
    for(int x=0; x<16; x++)
        printf("%02X ", r[x]);
}

void swr() {
    if(!r[0xA] && *pc>0x1000 && r[0xA]<4) {
        r[0xF] = 0xFF;
        return;
    }
    r  = rs[r[0xA]];
    sp = (sppc*)&r[0xB];
    pc = (sppc*)&r[0xD];
}

void mme() {
    if(*pc<0x1000) {
        
    }
    else {
        // Unprivileged Kernel Request Information
    }
}

void tra() {
    if(*pc<0x1000) {
        
    }
    else {
        // Unprivileged Kernel Request Information
    }
}
