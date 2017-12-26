#include "qx.h"

void pnc() {
    printf("\nPANIC: ");
    for(int x=0; x<16; x++)
        printf("%02X ", r[x]);
    for(int i=0; i<0x2000; i++)
        fprintf(stderr, "%02X ", m[i]);
}

void frk() {
    pid_t c = fork(), *d = (pid_t*) &r[3];
    if(!c) *pc = *re-1;
    *d = c;
}

void sig() {
    
}

void sih() {

}

void swr() {
    if(!r[0xA] && *pc>0x1000 && r[0xA]<4) {
        r[0xF] = 0xFF;
        return;
    }
    r  = rs[r[0xA]];
    sp = (_2*)&r[0xB];
    pc = (_2*)&r[0xD];
}

void pri() {
    printf("%s", (char*) &m[*re]);
}
