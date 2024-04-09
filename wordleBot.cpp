#include "wordleBot.h"

using namespace std;

wordleBot::wordleBot()
{
    char word1 = '?';
    char word2 = '?';
    char word3 = '?';
    char word4 = '?';
    char word5 = '?';
}

wordleBot::~wordleBot()
{
}

void wordleBot::addToArray(string word, int index)
{
    wordArray.push_back(word);
    arrayWordCount++;
}

void wordleBot::deleteWordsfromArray(char letter)
{

    // cout << "letter: " << letter << " has been passed to the function" << endl;

    for (int i = 0; i < wordArray.size() - 1; i++)
    {
        if (wordArray.at(i).find(letter) != string::npos)
        {
            // cout << "word: " << wordArray.at(i) << " has been removed from the array" << endl;
            wordArray.erase(wordArray.begin() + i);
            arrayWordCount--;
        }
    }
}

void wordleBot::deleteWhenG(char letter)
{
    for (int i = 0; i < wordArray.size() - 1; i++)
    {
    }
}

void wordleBot::makeNewGuess(string response, string word)
{
    for (int i = 0; i < response.length(); i++)
    {
        if (response.at(i) == 'r')
        {
            deleteWordsfromArray(word.at(i));
        }
        if (response.at(i) == 'g')
        {
            if (i == 0)
            {
                letter1 = word.at(i);
            }
            if (i == 1)
            {
                letter2 = word.at(i);
            }
            if (i == 2)
            {
                letter3 = word.at(i);
            }
            if (i == 3)
            {
                letter4 = word.at(i);
            }
            if (i == 4)
            {
                letter5 = word.at(i);
            }
        }
    }
}
