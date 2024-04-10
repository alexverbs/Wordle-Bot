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

void wordleBot::deleteWordsfromArray(char letter, const string &response, int currentIndex, const string &word)
{
    bool isLetterValidElsewhere = false;
    for (int i = 0; i < response.length(); i++)
    {
        if (i != currentIndex && response[i] != 'r' && response[i] != 'g' && word.at(i) == letter)
        {
            isLetterValidElsewhere = true;
            break;
        }
    }

    if (!isLetterValidElsewhere)
    {
        for (int i = wordArray.size() - 1; i >= 0; i--)
        {
            if (wordArray.at(i).find(letter) != string::npos)
            {
                wordArray.erase(wordArray.begin() + i);
            }
        }
    }
}

void wordleBot::deleteWordsfromArrayG(char letter)
{
    for (int i = wordArray.size() - 1; i >= 0; i--)
    {
        if (wordArray.at(i).find(letter) == string::npos)
        {
            // cout << "word: " << wordArray.at(i) << " has been removed from the array" << endl;
            wordArray.erase(wordArray.begin() + i);
            arrayWordCount--;
        }
    }
}

void wordleBot::deleteWhenG(char letter, int index)
{
    for (int i = wordArray.size() - 1; i >= 0; i--)
    {
        if (wordArray.at(i).at(index) != letter)
        {
            wordArray.erase(wordArray.begin() + i);
            arrayWordCount--;
        }
    }
}

void wordleBot::deleteWhenY(char letter, int index)
{
    for (int i = wordArray.size() - 1; i >= 0; i--)
    {
        string currentWord = wordArray.at(i);

        if (currentWord.find(letter) == string::npos || currentWord.at(index) == letter)
        {
            wordArray.erase(wordArray.begin() + i);
        }
    }
}

string wordleBot::makeNewGuess(string response, string word)
{
    for (int i = 0; i < response.length(); i++)
    {
        char letter = word.at(i);

        if (response.at(i) == 'r')
        {
            deleteWordsfromArray(letter, response, i, word);
        }
        else if (response.at(i) == 'g')
        {
            deleteWhenG(letter, i);
        }
        else if (response.at(i) == 'y')
        {
            deleteWordsfromArrayG(letter);
            deleteWhenY(letter, i);
        }
    }

    string newGuess = "";
    if (!wordArray.empty())
    {
        newGuess = wordArray.at(0);
    }

    return newGuess;
}

void wordleBot::printVector()
{
    for (int i = 0; i < wordArray.size(); i++)
    {
        cout << wordArray.at(i) << endl;
    }
}
