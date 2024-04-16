#include <iostream>
#include <fstream>
#include "stdio.h"

#include "wordleBot.h"

using namespace std;

void printColoredWord(const string &response, const string &word)
{
    for (size_t i = 0; i < word.length(); i++)
    {
        switch (response[i])
        {
        case 'g':
            cout << "\033[32m" << word[i];
            break;
        case 'y':
            cout << "\033[33m" << word[i];
            break;
        case 'r':
            cout << "\033[31m" << word[i];
            break;
        }
        cout << "\033[0m";
    }
    cout << endl;
}

int main()
{

    ifstream file;
    file.open("wordleWords.txt");

    string word;
    int wordCount = 0;
    wordleBot bot;

    while (file >> word)
    {
        bot.addToArray(word, wordCount);
        wordCount++;
    }

    cout << "Welcome to Alex Verbesey's Wordle Bot!" << endl;
    cout << "This bot will help you win the game Wordle!" << endl;
    cout << "Enter this as your frist word: Adieu" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "what is the output from this word?" << endl;
    cout << " g: correct spot \n y: correct letter and wrong spot\n r: wrong letter" << endl;

    string currentGuess = "adieu";
    string wordResponse;
    int tries = 0;

    while (tries < 6)
    {
        cout << "Guess [" << tries + 1 << "] Enter this: " << currentGuess << endl;
        cout << "Enter the response (g, y, r for each letter): ";
        cin >> wordResponse;

        printColoredWord(wordResponse, currentGuess);

        if (wordResponse == "ggggg")
        {
            cout << "Correct! You've guessed the word!" << endl;
            break;
        }

        currentGuess = bot.makeNewGuess(wordResponse, currentGuess);
        cout << "Number of possible words left: " << bot.getWordArraySize() << endl;
        cout << "There is a " << bot.chanceRight() << "% chance that this word is correct!" << endl;
        tries++;
    }

    if (tries == 5)
    {
        cout << "You've reached the maximum number of tries." << endl;
    }

    file.close();

    return 0;
}

// printf("\033[31mred text\n");
// printf("\033[32mgreen text\n");
// printf("\033[33myellow text\n");