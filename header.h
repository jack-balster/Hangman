#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

//prints gmaeboard and text (got this function from NVitanovic on youtube) was doing everything manually before
void printMessage(string message, bool printTop, bool printBottom);

//draws the hangman as wrong guesses occur
void drawHangman(int guessCount);

//prints the incorrect letters that the user has guessed
void printLetters(string input, char from, char to);

//prints the available letters you can still guess
void availableLetters(string taken);

//checks if they have won and prints the correct letters of the word if the guess is correct
bool checkWin(string word, string guessed);

//keeps track of how many guesses you have left (10)
int triesLeft(string word, string guessed);

//runs application utilizing all of the previous functions
void runApp();

