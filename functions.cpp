#include "header.h"

//compressed way to draw gameboard and hangman from NVitanovic on youtube (was printing it all manually before)
void printMessage(string message, bool printTop = true, bool printBottom = true) {
    if (printTop) {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++) { //33 because 33 characters in line above ^  "+-----+"
        if (front) { //center message
            message = " " + message; //add space at the front
        }
        else {
            message = message + " "; //add space at the back
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBottom) {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    }
    else {
        cout << "|" << endl;
    }
}

void drawHangman(int guessCount = 0) {
    if (guessCount >= 1)
        printMessage("|", false, false); // top and bottom borders are false so it won't print (it will center and print "|")
    else
        printMessage("", false, false);

    if (guessCount >= 2)
        printMessage("|", false, false);
    else
        printMessage("", false, false);

    if (guessCount >= 3)
        printMessage("O", false, false);
    else
        printMessage("", false, false);

    if (guessCount == 4)
        printMessage("/  ", false, false);

    if (guessCount == 5)
        printMessage("/| ", false, false);

    if (guessCount >= 6)
        printMessage("/|\\", false, false); // escape the escape character
    else
        printMessage("", false, false);

    if (guessCount >= 7)
        printMessage("|", false, false);
    else
        printMessage("", false, false);

    if (guessCount == 8)
        printMessage("/", false, false);

    if (guessCount >= 9)
        printMessage("/ \\", false, false);
    else
        printMessage("", false, false);
}

void printLetters(string input, char from, char to) //from a-m to n-z 
{
    string s;
    for (char i = from; i <= to; i++) {
        if (input.find(i) == string::npos) { //if input doesn't contain character (npos basically means end of string)
            s += i; //add character guessed to the guessed string being displayed
            s += " "; //removes from guessing list
        }
        else
            s += "  "; //if guess correct then take out character from guessing list
    }
    printMessage(s, false, false);
}

void availableLetters(string taken) {
    printMessage("Available letters"); //prints availiable letters to guess
    printLetters(taken, 'a', 'm');
    printLetters(taken, 'n', 'z');
}

bool checkWin(string word, string guessed) {
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++) {
        if (guessed.find(word[i]) == string::npos) { //if guess does not contain character
            won = false;
            s += "_ "; //blank character of actual word since guess was wrong
        }
        else {
            s += word[i];
            s += " "; //show actual character if guess contained character
        }
    }
    printMessage(s, false); //will print bottom border
    return won;
}

string randomWord(string path) {
    int lineCount = 0;
    string word;
    vector<string> v; //longer or shorter depending on the word randomly selected
    ifstream reader(path);
    if (reader.is_open()) {
        while (std::getline(reader, word)) //getline from reader and store in word
            v.push_back(word); //adds element to end of vector

        int randomLine = rand() % v.size();

        word = v.at(randomLine); //word = what the vector is at our random line in the file
        reader.close();
    }
    return word;
}

int triesLeft(string word, string guessed) {
    int error = 0;
    for (int i = 0; i < guessed.length(); i++) { //loops through guessed characters
        if (word.find(guessed[i]) == string::npos) //increment errors if guessed character isn't cfound in word string
            error++;
    }
    return error;
}

void runApp() {
  
    srand(time(NULL));
    string guesses;
    string wordToGuess;
    wordToGuess = randomWord("words.txt"); //file containing words to guess
    int tries = 0;
    bool win = false;
    do
    {
        system("cls");
        printMessage("HANGMAN");
        drawHangman(tries);
        availableLetters(guesses);
        printMessage("Guess the word");
        win = checkWin(wordToGuess, guesses);

        if (win)
            break;

        char x;
        cout << "Guess a letter: "; cin >> x;

        if (guesses.find(x) == string::npos)
            guesses += x;

        tries = triesLeft(wordToGuess, guesses);

    } while (tries < 10); //10 tries corresponds to hangman image

    if (win)
        printMessage("YOU WON!");
    else
        printMessage("YOU LOST :(");
    printMessage(wordToGuess.c_str());

    system("pause");
    getchar();
  
}
