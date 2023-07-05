#include <ncurses.h> // for ncurses functions

#include "menu.h"
#include "game.h"

// definition of menu phases
typedef enum {
    START_GAME,
    QUIT_GAME,
    CHANGE_LANGUAGE
} MENU_STATES;

// game state: actual game phase
static MENU_STATES state = START_GAME;

void drawMenu(int x, int y) {
    mvprintw(y+0, x, "   _____ _             _   ");
    mvprintw(y+1, x, "  / ____| |           | |  ");
    mvprintw(y+2, x, " | (___ | |_ __ _ _ __| |_");
    mvprintw(y+3, x, "  \\___ \\| __/ _` | '__| __|");
    mvprintw(y+4, x, "  ____) | || (_| | |  | |_");
    mvprintw(y+5, x, " |_____/ \\__\\__,_|_|   \\__|");

    mvprintw(y+8, x, "  _");
    mvprintw(y+9, x, " | |");
    mvprintw(y+10, x, " | |     __ _ _ __   __ _");
    mvprintw(y+11, x, " | |    / _` | '_ \\ / _` |");
    mvprintw(y+12, x, " | |___| (_| | | | | (_| |_");
    mvprintw(y+13, x, " |______\\__,_|_| |_|\\__, (_)");
    mvprintw(y+14, x, "                     __/ |");
    mvprintw(y+15, x, "                    |___/");

    mvprintw(y+18, x, "   ____        _ _");
    mvprintw(y+19, x, "  / __ \\      (_) |");
    mvprintw(y+20, x, " | |  | |_   _ _| |_");
    mvprintw(y+21, x, " | |  | | | | | | __|");
    mvprintw(y+22, x, " | |__| | |_| | | |_");
    mvprintw(y+23, x, "  \\___\\_\\\\__,_|_|\\__|");

    if(getLang()) {
        mvprintw(y+8, x + 30, "  ______ _   _");
        mvprintw(y+9, x + 30, " |  ____| \\ | |");
        mvprintw(y+10, x + 30, " | |__  |  \\| |");
        mvprintw(y+11, x + 30, " |  __| | . ` |");
        mvprintw(y+12, x + 30, " | |____| |\\  |");
        mvprintw(y+13, x + 30, " |______|_| \\_|");
    } else {
        mvprintw(y+8, x + 30, "  _____  ______ ");
        mvprintw(y+9, x + 30, " |  __ \\|  ____|");
        mvprintw(y+10, x + 30, " | |  | | |__");
        mvprintw(y+11, x + 30, " | |  | |  __|");
        mvprintw(y+12, x + 30, " | |__| | |____");
        mvprintw(y+13, x + 30, " |_____/|______|");
    }

    switch(state) {
    case START_GAME:
        mvprintw(y+0, x - 6, " __");
        mvprintw(y+1, x - 6, " \\ \\");
        mvprintw(y+2, x - 6, "  \\ \\");
        mvprintw(y+3, x - 6, "   > >");
        mvprintw(y+4, x - 6, "  / /");
        mvprintw(y+5, x - 6, " /_/");
        break;
    case CHANGE_LANGUAGE:
        mvprintw(y+8, x - 6, " __");
        mvprintw(y+9, x - 6, " \\ \\");
        mvprintw(y+10, x - 6, "  \\ \\");
        mvprintw(y+11, x - 6, "   > >");
        mvprintw(y+12, x - 6, "  / /");
        mvprintw(y+13, x - 6, " /_/");
        break;
    case QUIT_GAME:
        mvprintw(y+18, x - 6, " __");
        mvprintw(y+19, x - 6, " \\ \\");
        mvprintw(y+20, x - 6, "  \\ \\");
        mvprintw(y+21, x - 6, "   > >");
        mvprintw(y+22, x - 6, "  / /");
        mvprintw(y+23, x - 6, " /_/");
        break;
    }
}

int updateMenuState(char key) {

    switch(state) {
    case START_GAME:
        if (key == 3) {
            state = QUIT_GAME;
        } else if (key == 2) {
            state = CHANGE_LANGUAGE;
        } else if (key == 10) {
            return 1;
        }
        break;
    case CHANGE_LANGUAGE:
        if (key == 3) {
            state = START_GAME;
        } else if (key == 2) {
            state = QUIT_GAME;
        } else if (key == 10) {
            return 2;
        }
        break;
    case QUIT_GAME:
        if (key == 3) {
            state = CHANGE_LANGUAGE;
        } else if (key == 2) {
            state = START_GAME;
        }  else if (key == 10) {
            return 3;
        }
        break;
    }
    return 0;
}
