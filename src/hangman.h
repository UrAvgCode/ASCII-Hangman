#include <stdbool.h>

void intro(int x, int y);

int getMistakes();
bool getHasWon();
bool isGameOver();

void pickGuessWord(bool lang);

void createHintWord();
void updateHintWord(char chr);

void drawHintWord(int x, int y);
void drawHintLetters(int x, int y);
void drawGuessWord(int x, int y);

bool isLetter(char chr);
bool equalsLetter(char l1, char l2);
char toUppercase(char c);

void reset();
