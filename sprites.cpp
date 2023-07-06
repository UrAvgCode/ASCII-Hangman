#include <ncurses.h> // for ncurses functions

#include "sprites.h"

void intro(int x, int y) {
    drawHangman(x + 14, y, 6);
    drawFloor(x + 10, y + 17, 26);
    mvprintw(y+19, x, " _");
    mvprintw(y+20, x, "| |");
    mvprintw(y+21, x, "| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __");
    mvprintw(y+22, x, "| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\");
    mvprintw(y+23, x, "| | | | (_| | | | | (_| | | | | | | (_| | | | |");
    mvprintw(y+24, x, "|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|");
    mvprintw(y+25, x, "                    __/ |");
    mvprintw(y+26, x, "                   |___/");
}

void drawHangman(int x, int y, int state) {
    mvprintw(y, x, " ______________");
    mvprintw(y+1, x, "|  ________))__|");
    mvprintw(y+2, x, " ||/ /     ||");
    mvprintw(y+3, x, " || /      ||");
    mvprintw(y+4, x, " ||/       ||");
    mvprintw(y+5, x, " ||");
    mvprintw(y+6, x, " ||");
    mvprintw(y+7, x, " ||");
    mvprintw(y+8, x, " ||");
    mvprintw(y+9, x, " ||");
    mvprintw(y+10, x, " ||");
    mvprintw(y+11, x, " ||");
    mvprintw(y+12, x, " ||");
    mvprintw(y+13, x, " ||");
    mvprintw(y+14, x, " ||");
    mvprintw(y+15, x, " ||");
    mvprintw(y+16, x, " ||");
    if(state >= 1) {
        mvprintw(y+2, x+11, "||");
        mvprintw(y+3, x+11, "||.--.");
        mvprintw(y+4, x+11, "|/    \\");
        mvprintw(y+5, x+11, "|     |");
        mvprintw(y+6, x+11, "\\    /");
        mvprintw(y+7, x+11, " `==`");
    }
    if(state >= 2) {
        mvprintw(y+7, x+11, "-`==`");
        mvprintw(y+8, x+11, "|   |");
        mvprintw(y+9, x+11, "|   |");
        mvprintw(y+10, x+11, "|   |");
        mvprintw(y+11, x+11, "|___|");
    }
    if(state >= 3) {
        mvprintw(y+7, x+8, "  .-`==`");
        mvprintw(y+8, x+8, " //\\");
        mvprintw(y+9, x+8, "//");
        mvprintw(y+10, x+8, "||");
        mvprintw(y+11, x+8, "()");
    }
    if(state >= 4) {
        mvprintw(y+7, x+10, ".-`==`.");
        mvprintw(y+8, x+10, "/\\   /\\\\");
        mvprintw(y+9, x+10, " |   | \\\\");
        mvprintw(y+10, x+10, " |   | ||");
        mvprintw(y+11, x+10, " |___| ()");
    }
    if(state >= 5) {
        mvprintw(y+11, x+11, "| __|");
        mvprintw(y+12, x+11, "|/");
        mvprintw(y+13, x+11, "||");
        mvprintw(y+14, x+11, "||");
        mvprintw(y+15, x+11, "/|");
    }
    if(state >= 6) {
        mvprintw(y+11, x+14, " |");
        mvprintw(y+12, x+14, "\\|");
        mvprintw(y+13, x+14, "||");
        mvprintw(y+14, x+14, "||");
        mvprintw(y+15, x+14, "|\\");
    }
}

void drawBird(int x, int y) {
    mvprintw(y, x, "              __");
    mvprintw(y+1, x, "             /'{>");
    mvprintw(y+2, x, "         ____) (____");
    mvprintw(y+3, x, "       //'--;   ;--'\\\\");
    mvprintw(y+4, x, "      ///////\\_/\\\\\\\\\\\\\\");
    mvprintw(y+5, x, "             m m");
}

void drawCactus(int x, int y, int version) {
    switch(version){
    case 0:
        mvprintw(y, x, "      /|\\");
        mvprintw(y+1, x, "     |||||");
        mvprintw(y+2, x, "     |||||");
        mvprintw(y+3, x, " /\\  |||||");
        mvprintw(y+4, x, "|||| |||||");
        mvprintw(y+5, x, "|||| |||||  /\\");
        mvprintw(y+6, x, "|||| ||||| ||||");
        mvprintw(y+7, x, " \\|`-'|||| ||||");
        mvprintw(y+8, x, "  \\__ |||| ||||");
        mvprintw(y+9, x, "     ||||`-'|||");
        mvprintw(y+10, x, "     |||| ___/");
        mvprintw(y+11, x, "     |||||");
        mvprintw(y+12, x, "     |||||");
        break;
    case 1:
        mvprintw(y, x, "  _  _");
        mvprintw(y+1, x, " | || | _");
        mvprintw(y+2, x, "-| || || |");
        mvprintw(y+3, x, " | || || |-");
        mvprintw(y+4, x, "  \\_  || |");
        mvprintw(y+5, x, "    |  _/");
        mvprintw(y+6, x, "   -| | \\");
        mvprintw(y+7, x, "    |_|-");
        break;
    }
}

void drawGameOver(int x, int y, bool won) {
    if(won){
        mvprintw(y, x, "__     ______  _    _  __          ______  _   _");
        mvprintw(y+1, x, "\\ \\   / / __ \\| |  | | \\ \\        / / __ \\| \\ | |");
        mvprintw(y+2, x, " \\ \\_/ / |  | | |  | |  \\ \\  /\\  / / |  | |  \\| |");
        mvprintw(y+3, x, "  \\   /| |  | | |  | |   \\ \\/  \\/ /| |  | | . ` |");
        mvprintw(y+4, x, "   | | | |__| | |__| |    \\  /\\  / | |__| | |\\  |");
        mvprintw(y+5, x, "   |_|  \\____/ \\____/      \\/  \\/   \\____/|_| \\_|");
    } else {
        mvprintw(y, x, "__     ______  _    _   _      ____   _____ _______");
        mvprintw(y+1, x, "\\ \\   / / __ \\| |  | | | |    / __ \\ / ____|__   __|");
        mvprintw(y+2, x, " \\ \\_/ / |  | | |  | | | |   | |  | | (___    | |");
        mvprintw(y+3, x, "  \\   /| |  | | |  | | | |   | |  | |\\___ \\   | |");
        mvprintw(y+4, x, "   | | | |__| | |__| | | |___| |__| |____) |  | |");
        mvprintw(y+5, x, "   |_|  \\____/ \\____/  |______\\____/|_____/   |_|");
    }
}

void drawFloor(int x, int y, int width) {
    for(int i = 0; i < width; i++)
        mvprintw(y, x+i, "-");
}
