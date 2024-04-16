#ifndef wordleBot_h
#define wordleBot_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

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
    void deleteWhenG(char letter, int index);
    void deleteWhenY(char letter, int index);

    string makeNewGuess(string response, string word);

    void deleteWordsfromArray(char letter, const string &response, int currentIndex, const string &word);
    void deleteWordsfromArrayG(char letter);
    void addToArray(string word, int index);
    void refineWordsBasedOnFeedback(const string &response, const string &word);

    string chooseNewWord();

    void printVector();

    int getArrayWordCount() { return arrayWordCount; }
    int getWordArraySize() { return wordArray.size(); }

    void handleRResponse(const string &response, const string &word);

    int getTierValue(char letter, const std::unordered_map<char, int> &tierMap);
    string getLowestValueWord(const std::vector<std::string> &words);

    float chanceRight();
};

#endif