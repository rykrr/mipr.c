/* micro.c: Simple Microprocessor */
/* Copyright (c) 2017 Ryan Kerr   */

#include <stdio.h>
#include <stdlib.h>

#include "../includes/ax.h"
#include "../includes/cx.h"
#include "../includes/dx.h"
#include "../includes/qx.h"
#include "../includes/rx.h"

int load_file(const char *p, _1 *b, int n) {
    int read = 0;
    FILE *f = fopen(p, "rb");
    
    if(f) {
        read = fread(b, sizeof(_1), n, f);
        fclose(f);
    }
    return read;
}

int main() {
    clear_registers();
    link_codes();
    
    dxm = 0; // DEBUG SWITCH
    
    int l = load_file("xe", m, 0x150);
    if(!l) return 404;
    
    for(_1 b; *pc<0x150 && m[*pc] != 0x0F; (*pc)++) {
        r[8] = r[9] = 0;
        if((b = m[*pc])) {
            
            code *c = opcode[b];
            if(c) {
                for(int i=0; i<c->args; i++)
                    if(i<2)
                        r[8+i] = m[++(*pc)];
                    else
                        m[--(*sp)] = m[++(*pc)];
                r[0xA] = (b&~c->mask)-c->offs;
                debug(b, c->args-2);
                c->fn();
                if(c->args>2)
                    *sp += (c->args-2);
            }
        }
    }
    puts("end");
}
