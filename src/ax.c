/* ax.c: Micro ALU              */
/* Copyright (c) 2017 Ryan Kerr */

#include "ax.h"

#define OVERFLOW 2
#define NEGATIVE 4

void nop() {
    ;;
}

void opr() {
    int hi = HI(r[8])%8,
        lo = LO(r[8])%8;
    
    switch(r[0xA]) {
        case 0:
            if(0xFF<r[hi]+r[lo])
                r[0xF] |= OVERFLOW;
            else
                r[0xF] &= ~OVERFLOW;
            r[hi] += r[lo];
            break;
        case 1:
            if(0xFF<r[hi]*r[lo])
                r[0xF] |= OVERFLOW;
            else
                r[0xF] &= ~OVERFLOW;
            r[hi] *= r[lo];
            break;
        case 2:
            if(r[hi]-r[lo]<0) {
                r[0xF] |= NEGATIVE;
                r[hi] = -1*(r[hi] - r[lo]);
            }
            else {
                r[0xF] &= ~NEGATIVE;
                r[hi] -= r[lo];
            }
            break;
        case 3:
            if(r[hi])
                r[hi] /= r[lo];
            break;
        case 4:
            r[hi] &= r[lo];
            break;
        case 5:
            r[hi] |= r[lo];
            break;
        case 6:
            r[hi] ^= r[lo];
            break;
        case 7:
            r[hi] = ~r[hi];
            break;
    }
}
