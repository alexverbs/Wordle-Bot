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
    // The flag to check if the letter is valid somewhere else other than currentIndex
    bool isLetterValidElsewhere = false;
    for (int i = 0; i < response.length(); i++)
    {
        if (i != currentIndex && response[i] != 'r' && word.at(i) == letter) // Typo here, it should check for 'y' or 'g' as well.
        {
            isLetterValidElsewhere = true;
            break;
        }
    }

    // If the letter is not valid elsewhere, delete words containing this letter
    if (!isLetterValidElsewhere)
    {
        for (int i = wordArray.size() - 1; i >= 0; i--)
        {
            if (wordArray.at(i).find(letter) != string::npos && wordArray.at(i).at(currentIndex) != letter)
            {
                wordArray.erase(wordArray.begin() + i);
            }
        }
    }
    // If the letter is valid elsewhere, only delete words where the letter is at currentIndex
    else
    {
        for (int i = wordArray.size() - 1; i >= 0; i--)
        {
            if (wordArray.at(i).at(currentIndex) == letter)
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

string wordleBot::makeNewGuess(string response, string word)
{
    // Handle green responses ('g') - letter is correct and in the correct position
    for (int i = 0; i < response.length(); i++)
    {
        if (response.at(i) == 'g')
        {
            deleteWhenG(word.at(i), i);
        }
    }

    // Handle yellow responses ('y') - letter is correct but in the wrong position
    for (int i = 0; i < response.length(); i++)
    {
        if (response.at(i) == 'y')
        {
            // Delete the word if it doesn't contain the yellow letter at all
            // or if it contains the yellow letter in the position where it shouldn't be
            deleteWhenY(word.at(i), i);

            // If a letter appears as yellow and is not in any green positions,
            // make sure it is present in the remaining words but not at the 'y' index
            bool isLetterGreenSomewhere = false;
            for (int j = 0; j < response.length(); j++)
            {
                if (response.at(j) == 'g' && word.at(j) == word.at(i))
                {
                    isLetterGreenSomewhere = true;
                    break;
                }
            }
            if (!isLetterGreenSomewhere)
            {
                for (int j = wordArray.size() - 1; j >= 0; j--)
                {
                    string currentWord = wordArray.at(j);
                    if (currentWord.find(word.at(i)) == string::npos ||
                        currentWord.at(i) == word.at(i))
                    {
                        wordArray.erase(wordArray.begin() + j);
                    }
                }
            }
        }
    }

    // Handle red responses ('r') - letter is not in the word at this position
    for (int i = 0; i < response.length(); i++)
    {
        if (response.at(i) == 'r')
        {
            bool isLetterValidElsewhere = false;
            // Check if the 'r' letter appears as 'g' or 'y' anywhere else in the response
            for (int j = 0; j < response.length(); j++)
            {
                if (i != j && (response.at(j) == 'g' || response.at(j) == 'y') && word.at(j) == word.at(i))
                {
                    isLetterValidElsewhere = true;
                    break;
                }
            }
            // If the 'r' letter does not appear as 'g' or 'y' anywhere else,
            // remove all words that contain this letter
            if (!isLetterValidElsewhere)
            {
                for (int j = wordArray.size() - 1; j >= 0; j--)
                {
                    if (wordArray.at(j).find(word.at(i)) != string::npos)
                    {
                        wordArray.erase(wordArray.begin() + j);
                    }
                }
            }
            // If the 'r' letter appears as 'g' or 'y' somewhere else,
            // only remove words that have the letter in the current position
            else
            {
                for (int j = wordArray.size() - 1; j >= 0; j--)
                {
                    if (wordArray.at(j).at(i) == word.at(i))
                    {
                        wordArray.erase(wordArray.begin() + j);
                    }
                }
            }
        }
    }

    // Select the new guess
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
