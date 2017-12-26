#include "cx.h"

code *opcode[0xFF];
code config[0xFF] = {
    /*     lo    hi  mask  offs  a  f  fnc      */
    { 1, 0x00, 0x00, 0xFF, 0x00, 0, 0, nop },   // No Operation
    
    { 1, 0x01, 0x01, 0xFF, 0x00, 2, 0, ldx },   // Load Extended (16)
    { 1, 0x02, 0x02, 0xFF, 0x00, 0, 0, jmp },   // Jump Unconditional
    
    { 1, 0x10, 0x17, 0xF0, 0x00, 1, 0, ldn },
    { 1, 0x18, 0x1F, 0xF0, 0x08, 1, 0, ldm },
    { 1, 0x20, 0x22, 0xF0, 0x00, 1, 0, jpc },
    { 1, 0x30, 0x37, 0xF0, 0x00, 1, 0, med },
    { 1, 0x3A, 0x3A, 0xFF, 0x00, 2, 0, map },
    
    { 1, 0xE1, 0xE1, 0xFF, 0x00, 2, 0, pri },
    
    { 1, 0xA0, 0xA7, 0xF0, 0x00, 1, 0, opr },   // ALU Calls
    { 1, 0xFF, 0xFF, 0xFF, 0x00, 0, 0, pnc },   // PANIC
    { 0 }                                       // NULL TERMINATOR
};

void link_codes() {
    for(int i=0; i<0xFF; i++)
        opcode[i] = NULL;
    for(int x=0; config[x].on; x++)
        for(int y=config[x].lo; y<=config[x].hi; y++)
            opcode[y] = &config[x];
}
