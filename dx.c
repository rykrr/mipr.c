#include "dx.h"

byte dxm;

int debug(byte b, byte c) {
    if(dxm) {
        printf("< %02X > ", b);
        
        for(int i=0; i<16; i++)
            printf("[ %X | %02X ] ", i, r[i]);
        
        fgetc(stdin);
        return 1;
    }
    return 0;
}
