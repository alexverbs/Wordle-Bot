#ifndef wordleBot_h
#define wordleBot_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class wordleBot
{
private:
    char letter1, letter2, letter3, letter4, letter5;
    vector<string> wordArray;
    int arrayWordCount = 0;

public:
    wordleBot();
    ~wordleBot();
    void makeNewGuess(string response, string word);
    void deleteWhenG(char letter);

    void deleteWordsfromArray(char letter);
    void addToArray(string word, int index);

    int getArrayWordCount() { return arrayWordCount; }
};

#endif