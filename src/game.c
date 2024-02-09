#include <ncurses.h>
#include <unistd.h>

#include "game.h"
#include "hangman.h"
#include "sprites.h"
#include "menu.h"

// game constant: frames per second
static float fps = 30;

// game state: actual frame number
static int frame = 0;

// game state: elapsed time
static double elapsed = 0;

// pressed key
char key;

// german = false, english = true
bool lang = true;

// definition of game phases
typedef enum {
    GAME_INTRO,
    GAME_MENU,
    GAME_LOOP,
    GAME_OVER
} GAME_STATES;

// game state: actual game phase
static GAME_STATES state = GAME_INTRO;

GAME_STATES get_state() {
    return (state);
}

// render a single frame
void render_frame() {
    int max_x;
    int max_y;
    getmaxyx(stdscr, max_y, max_x);
    int tx = max_x / 2;
    int ty = max_y / 2;

    // clear the actual frame
    clear();

    // render the actual frame depending on the state
    if (state == GAME_INTRO) {
        intro(tx - 23, ty - 13);

    } else if (state == GAME_MENU) {
        drawMenu(tx - 13, ty - 13);

    } else if (state == GAME_LOOP || state == GAME_OVER) {

        // Draw Graphics
        drawHangman(tx - 9, ty, getMistakes());
        drawCactus(tx - 35, ty + 4, 0);
        drawCactus(tx + 27, ty + 9, 1);
        drawFloor(0, ty + 17, max_x);
        drawHintLetters(10, 7);

        if (state == GAME_LOOP) {
            drawHintWord(10, 5);
            drawBird((frame / 2) % max_x, 12);
            updateHintWord(key);
        } else {
            drawGuessWord(10, 5);
            drawGameOver(tx - 20, 10, getHasWon());
        }
    }

    refresh();
}

// update the game state
// * esc goes back to menu
bool update_state() {
    // state check cascade
    switch (state) {
        case GAME_INTRO:
            if (elapsed > 3)
                state = GAME_MENU;
            break;
        case GAME_MENU:
            switch (updateMenuState(key)) {
                case 0:
                    reset();
                    pickGuessWord(lang);
                    createHintWord();
                    state = GAME_LOOP;
                    break;
                case 1:
                    lang = !lang;
                    break;
                case 2:
                    return (true);
                    break;
            }
            break;
        case GAME_LOOP:
            if (isGameOver())
                state = GAME_OVER;
            break;
        case GAME_OVER:
            break;
    }

    if (key == 27)
        state = GAME_MENU;

    return (false);
}

// the game loop
// * it renders frame after frame
// * updates the state after each frame
// * and sleeps for the remainder of the frame
void game_loop() {
    float dt = 1 / fps; // frame duration
    float ms = dt * 1000; // milli seconds

    // initialize ncurses screen
    initscr(); // initialize the screen to contain a single window
    curs_set(FALSE); // disable text cursor
    timeout(0); // configure getch() to be non-blocking
    keypad(stdscr, TRUE); // configure getch() to return cursor key codes
    noecho(); // do not echo keyboard input

    // the main game loop
    while (true) {

        // keyboard input
        key = getch();

        // render a single frame
        render_frame();

        // update frame counter and elapsed time
        frame++;
        elapsed += dt;

        // update the game state
        bool finish = update_state();

        // sleep for the remainder of the frame
        usleep(ms * 1000);

        // check for game finish
        if (finish) break;
    }
}

// get language
bool getLang() {
    return (lang);
}
