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
        if (i != currentIndex && (response[i] == 'g' || response[i] == 'y') && word.at(i) == letter)
        {
            isLetterValidElsewhere = true;
            break;
        }
    }

    if (!isLetterValidElsewhere)
    {
        // If the letter is not valid elsewhere, delete words containing this letter anywhere
        for (int i = wordArray.size() - 1; i >= 0; i--)
        {
            if (wordArray.at(i).find(letter) != string::npos)
            {
                wordArray.erase(wordArray.begin() + i);
            }
        }
    }
    else
    {
        // If the letter is valid elsewhere, delete words where the letter is not at its correct indices
        for (int i = wordArray.size() - 1; i >= 0; i--)
        {
            string currentWord = wordArray.at(i);
            bool hasIncorrectPosition = false;

            // Check each instance of the letter in the current word
            for (int j = 0; j < currentWord.length(); j++)
            {
                if (currentWord.at(j) == letter)
                {
                    if (response.at(j) == 'r' || (response.at(j) == 'y' && j == currentIndex))
                    {
                        hasIncorrectPosition = true;
                        break;
                    }
                }
            }

            if (hasIncorrectPosition)
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
        // Word must contain the letter and not at the current index
        if (currentWord.find(letter) == string::npos || currentWord.at(index) == letter)
        {
            wordArray.erase(wordArray.begin() + i);
        }
    }
}

void wordleBot::refineWordsBasedOnFeedback(const string &response, const string &word)
{
    vector<bool> excludeFromPosition(26, false); // Tracks letters that must be excluded from specific positions
    vector<bool> validElsewhere(26, false);      // Tracks if letters are valid in other positions

    // Process responses to set flags
    for (int i = 0; i < response.length(); i++)
    {
        if (response.at(i) == 'g' || response.at(i) == 'y')
        {
            validElsewhere[word.at(i) - 'a'] = true; // Mark letter as valid elsewhere
        }
    }

    // Remove words based on feedback
    for (int j = wordArray.size() - 1; j >= 0; j--)
    {
        bool removeWord = false;
        for (int k = 0; k < response.length(); k++)
        {
            if (response.at(k) == 'r' && !validElsewhere[word.at(k) - 'a'] && wordArray.at(j).find(word.at(k)) != string::npos)
            {
                removeWord = true; // Mark to remove if 'r' and not valid elsewhere
                break;
            }
        }
        if (removeWord)
        {
            wordArray.erase(wordArray.begin() + j);
        }
    }
}

string wordleBot::makeNewGuess(string response, string word)
{
    // Refine word list based on previous feedback
    refineWordsBasedOnFeedback(response, word);

    // Process each type of response
    for (int i = 0; i < response.length(); i++)
    {
        if (response.at(i) == 'g')
        {
            deleteWhenG(word.at(i), i);
        }
        else if (response.at(i) == 'y')
        {
            deleteWhenY(word.at(i), i);
        }
        else if (response.at(i) == 'r')
        {
            deleteWordsfromArray(word.at(i), response, i, word);
        }
    }

    // Determine the new guess based on refined word list
    string newGuess = "";
    if (!wordArray.empty())
    {
        newGuess = getLowestValueWord(wordArray);
    }
    return newGuess;
}

int wordleBot::getTierValue(char letter, const std::unordered_map<char, int> &tierMap)
{
    // Convert to lowercase to ensure that the letter matches the map
    letter = std::tolower(letter);
    auto it = tierMap.find(letter);
    if (it != tierMap.end())
    {
        return it->second;
    }
    return 0; // Return 0 if the letter is not found
}

string wordleBot::getLowestValueWord(const std::vector<std::string> &words)
{
    // Mapping of letters to their tier values
    const std::unordered_map<char, int> tierMap = {
        {'e', 1}, {'a', 1}, {'r', 1}, {'i', 1}, {'o', 1}, {'t', 1}, {'n', 1}, {'s', 1}, {'l', 2}, {'c', 2}, {'u', 2}, {'d', 2}, {'p', 2}, {'m', 2}, {'h', 2}, {'g', 2}, {'b', 3}, {'f', 3}, {'y', 3}, {'w', 3}, {'k', 3}, {'v', 3}, {'x', 4}, {'z', 4}, {'q', 4}, {'j', 4}};

    std::string lowestValueWord;
    int lowestValue = INT_MAX;

    for (const std::string &word : words)
    {
        int currentValue = 0;
        for (char letter : word)
        {
            currentValue += getTierValue(letter, tierMap);
        }

        if (currentValue < lowestValue)
        {
            lowestValue = currentValue;
            lowestValueWord = word;
        }
    }

    return lowestValueWord;
}

void wordleBot::printVector()
{
    for (int i = 0; i < wordArray.size(); i++)
    {
        cout << wordArray.at(i) << endl;
    }
}

float wordleBot::chanceRight()
{
    float percentChance = (1.0f / static_cast<float>(wordArray.size())) * 100.0f;

    return percentChance;
}
