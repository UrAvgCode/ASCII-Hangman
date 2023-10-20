#include <ncurses.h>
#include <string.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "hangman.h"
#include "game.h"

#define MAX_WORD   100
#define NUM_WORDS  1

#define LENGTH 20

int mistakes = 0;
bool hasWon = false;

char guessWord[LENGTH];
char hintWord[LENGTH];

char usedLetters[6];
int usedLettersCounter = 0;

void pickGuessWord(bool lang) {
    /* Open words file */
    FILE *fp = fopen("wordlist-en", "r");

    if (fp == NULL) {
        perror("Unable to locate word list");
        exit(EXIT_FAILURE);
    }

    /* Count words in file */
    char word[MAX_WORD];
    long wc = 0;
    while (fgets(word, sizeof word, fp) != NULL) {
        ++wc;
    }

    /* Choose random word */
    char randwords[MAX_WORD];
    srand((unsigned) time(NULL));

    rewind(fp);
    int sel = rand() % wc + 1;
    for (int j = 0; j < sel; j++) {
        if (fgets(word, sizeof word, fp) == NULL) {
            perror("Error in fgets()");
        }
    }
    strcpy(randwords, word);

    if (fclose(fp) != 0) {
        perror("Unable to close file");
    }

    strcpy(guessWord, randwords);
}

void createHintWord() {
    for(int i = 0; i < LENGTH; i++)
        if(isLetter(guessWord[i]))
            hintWord[i] = '-';
}

void updateHintWord(char chr) {
    if(!isLetter(chr))
        return;

    for(int i = 0; i <= usedLettersCounter; i++){
        if(equalsLetter(usedLetters[i], chr)){
            return;
        }
    }

    bool contains = false;
    for(int i = 0; i < LENGTH; i++){
        if(equalsLetter(guessWord[i], chr)){
            hintWord[i] = guessWord[i];
            contains = true;
        }
    }

    if(!contains) {
        mistakes += 1;
        usedLetters[usedLettersCounter] = toUppercase(chr);
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

    for(int i=0; i < 6; i++)
        usedLetters[i]='\0';
}

bool isLetter(char chr) {
    if((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
        return true;
    return false;
}

bool equalsLetter(char l1, char l2) {
    if(l1 == l2 || l1 - 32 == l2 || l1 + 32 == l2)
        return true;
    return false;
}

char toUppercase(char c) {
    if(c > 90)
        return c - 32;
    return c;
}

int getMistakes() {
    return mistakes;
}

bool getHasWon() {
    return hasWon;
}
