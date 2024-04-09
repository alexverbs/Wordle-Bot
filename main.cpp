#include <iostream>
#include <fstream>
#include "stdio.h"

#include "wordleBot.h"

using namespace std;

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
    cout << "We will start with the word: Adieu" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "what is the output from this word?" << endl;
    cout << " g: correct spot \n y: correct letter and wrong spot\n r: wrong letter" << endl;

    string startWord = "adieu";

    string wordResponse;
    cin >> wordResponse;

    cout << "Is this the correct output?" << endl;

    int k = 0;

    for (int i = 0; i < startWord.length(); i++)
    {

        if (wordResponse[i] == 'g')
        {
            cout << "\033[32m" << startWord.at(k);
        }
        else if (wordResponse[i] == 'y')
        {
            cout << "\033[33m" << startWord.at(k);
        }
        else if (wordResponse[i] == 'r')
        {
            cout << "\033[31m" << startWord.at(k);
        }
        k++;
        cout << "\033[0m";
    }

    cout << endl;

    cout << "y: yes" << endl;
    cout << "n: no" << endl;

    char response;

    cin >> response;

    if (response == 'y')
    {
        bot.makeNewGuess(wordResponse, startWord);
        cout << "The number of words in the array after removals is: " << bot.getArrayWordCount() << endl;
    }
    else
    {
        cout << "Input not correct, to be dealt with later" << endl;
    }

    cout << "The number of words in the array is: " << bot.getArrayWordCount() << endl;

    file.close();

    return 0;
}

// printf("\033[31mred text\n");
// printf("\033[32mgreen text\n");
// printf("\033[33myellow text\n");