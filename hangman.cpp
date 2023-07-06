#include <ncurses.h> // for ncurses functions
#include <string.h> // for strlen()

#include <time.h> // for time()
#include <stdlib.h> // for rand()
#include <stdio.h>

#include "hangman.h"
#include "game.h"

#define LENGTH 20

int mistakes = 0;
bool hasWon = false;

char guessWord[LENGTH];
char hintWord[LENGTH];

char usedLetters[6];
int usedLettersCounter = 0;

void pickGuessWord(bool lang) {
    srand(time(NULL));

    FILE* fp = NULL;
    char words[LENGTH];
    int i = 0 , ran = 0;
    srand(time(NULL));

    if(getLang()) {
        fp = fopen("wordlist-en.txt" , "r+");
    } else {
        fp = fopen("wordlist-de.txt" , "r+");
    }

    for(; fgets(words , sizeof(words) , fp) ; i++);
    ran = rand() % i;
    rewind(fp);
    for(i = 0 ; i < ran ; i++)
        fgets(words , sizeof(words) , fp);

    for(int i = 0; i < LENGTH; i++)
        if(isLetter(words[i]))
            guessWord[i] = words[i];
}

void createHintWord() {
    for(int i = 0; i < LENGTH; i++)
        if(isLetter(guessWord[i]))
            hintWord[i] = '-';
}

void updateHintWord(char chr) {
    if(!isLetter(chr))
        return;

    bool contains = false;

    for(int i = 0; i < usedLettersCounter + 1; i++){
        if(usedLetters[i] == chr){
            contains = true;
        }
    }

    if(contains)
        return;

    for(int i = 0; i < LENGTH; i++){
        if(guessWord[i] == chr){
            hintWord[i] = guessWord[i];
            contains = true;
        }
    }

    if(!contains) {
        mistakes += 1;
        usedLetters[usedLettersCounter] = chr;
        usedLettersCounter++;
    }
}

void drawHintWord(int x, int y) {
    mvprintw(y, x, "HintWord: %s", hintWord);
}

void drawHintLetters(int x, int y) {
    mvprintw(y, x, "Wrong Letters:");

    for(int i = 0; i < usedLettersCounter; i++){
        mvprintw(y + 1, x + 2*i, "%c", usedLetters[i]);
        if(i != usedLettersCounter - 1)
            mvprintw(y + 1, x + 1 + 2*i, ",");
    }
}

void drawGuessWord(int x, int y) {
    mvprintw(y, x, "GuessWord: %s", guessWord);
}

bool isGameOver() {
    if(mistakes >= 6)
        return true;

    if(strcmp(guessWord, hintWord) == 0) {
        hasWon = true;
        return true;
    }

    return false;
}

void reset() {
    mistakes = 0;
    usedLettersCounter = 0;
    hasWon = false;

    for(int i=0; i<LENGTH; i++) {
        guessWord[i]='\0';
        hintWord[i]='\0';
    }

    for(int i=0; i < 6; i++) {
        usedLetters[i]='\0';
    }
}

bool isLetter(char chr) {
    if(chr >= 'a' && chr <= 'z')
        return true;
    return false;
}

int getMistakes() {
    return mistakes;
}

bool getHasWon() {
    return hasWon;
}
