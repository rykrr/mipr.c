#include "ncd.h"
#include <unistd.h>

void ncd() {
    switch(r[0xA]) {
        case 0:
            endwin();
            break;
        case 1:
            initscr();
            break;
        case 2:
            mvprintw(r[HI(r[8])], r[LO(r[8])], "X");
            break;;
        case 3:
            usleep(10000);
            getch();
            break;
        case 0xC:
            for(int i=0; i<64; i++)
                mvprintw(i, 0, "\n");
    }
}
