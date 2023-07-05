#include <ncurses.h> // for ncurses functions
#include <string.h> // for strlen()

#include <time.h> // for time()
#include <stdlib.h> // for rand()

#include "hangman.h"


int mistakes = 0;
bool hasWon = false;

char guessWord[] = "helloworld";
char hintWord[] = "          ";

char usedLetters[100];
int usedLettersCounter = 0;

void pickGuessWord(bool lang) {

    if(lang) {
        char wordListEN[10][11] = { "heart", "racecar", "elephant", "house", "horse", "table", "bread", "crocodile", "flower", "cat" };

        srand(time(NULL));
        int choose = rand() % strlen(wordListEN[0]);

        for(int i = 0; i < 11; i++){
            guessWord[i] = wordListEN[choose][i];
        }

    } else {
        char wordListDE[10][11] = { "herz", "rennauto", "elefant", "haus", "pferd", "tisch", "brot", "krokodil", "blume", "katze" };

        srand(time(NULL));
        int choose = rand() % strlen(wordListDE[0]);

        int length = 11;

        for(int i = 0; i < length; i++){
            guessWord[i] = wordListDE[choose][i];
        }
    }
}

void createHintWord() {
    int length = strlen(hintWord);

    for(int i = 0; i < length; i++){
        if(isLetter(guessWord[i])) {
            hintWord[i] = '-';
        }
    }
}

void updateHintWord(char chr) {
    if(!isLetter(chr))
        return;

    int length = strlen(usedLetters);
    bool contains = false;

    for(int i = 0; i < length; i++){
        if(usedLetters[i] == chr){
            contains = true;
        }
    }

    if(contains)
        return;

    length = strlen(guessWord);

    for(int i = 0; i < length; i++){
        if(guessWord[i] == chr){
            hintWord[i] = guessWord[i];
            contains = true;
        }
    }

    if(!contains) {
        mistakes += 1;
        usedLetters[usedLettersCounter] = chr;
        usedLettersCounter++;

        if(mistakes >= 6) {
            for(int i = 0; i < length; i++){
                hintWord[i] = guessWord[i];
            }
        }
    }
}

void drawHintWord(int x, int y) {
    mvprintw(y, x, "HintWord: %s", hintWord);
}

void drawHintLetters(int x, int y) {
    mvprintw(y, x, "Wrong Letters:");

    for(int i = 0; i < usedLettersCounter; i++){
        mvprintw(y + 1, x + 2*i, "%c,", usedLetters[i]);
    }
}

bool isGameOver() {
    if(mistakes >= 6) {
        return true;
    }

    int length = strlen(guessWord);

    bool equals = true;
    for(int i = 0; i < length; i++){
        if(hintWord[i] != guessWord[i]) {
            equals = false;
            break;
        }
    }

    if(equals) {
        hasWon = true;
        return true;
    }

    return false;
}

int getMistakes() {
    return mistakes;
}

void reset() {
    mistakes = 0;
    usedLettersCounter = 0;

    for(int i=0; i<11; i++) {
        guessWord[i]=' ';
    }

    for(int i=0; i<11; i++) {
        hintWord[i]=' ';
    }

    for(int i=0; i<100; i++) {
        usedLetters[i]='\0';
    }
}

bool getHasWon() {
    return hasWon;
}

bool isLetter(char chr) {
    char abc[] = "abcdefghijklmnopqrstuvwxyz";

    int length = strlen(abc);
    for(int i = 0; i < length; i++){
        if(abc[i] == chr){
            return true;
        }
    }

    return false;
}
