#include "dx.h"

_1 dxm;

int debug(_1 b, _1 c) {
    if(dxm) {
        printf("< %02X > ", b);
        
        for(int i=0; i<16; i++)
            printf("[ %X | %02X ] ", i, r[i]);
        
        char c = fgetc(stdin);
        if(c == 's')
            sdb();
        return 1;
    }
    return 0;
}
void sdb() {
    printf("\nStack Dump\n");
    for(int i=0; i<5; i++)
        printf("%02X ", m[*sp+i]);
    printf("\n");
}
