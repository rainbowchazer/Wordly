#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

extern const int FIELD_ROWS;
extern int WORD_LENGTH;
extern string filename;

class Game {
private:
    vector<char> guessWordStr;
    vector<char> exampleWord;
    vector<vector<char>> field;
    vector<char> userWordChar;
    int attempt = 0;
    int win = 0;

    void makeField();
    void guessWord();
    void checkBox();
    bool validity();

public:
    int perfect = 0;
    int partial = 0;
    vector<char> getGuessWordStr();
    vector<char> getExampleWord();
    vector<vector<char>> getField();
    vector<char> getUserWordChar();
    void setGuessWordStr(const vector<char>& newGuessWordStr);
    void setUserWordChar(const vector<char>& newUserWordChar);
    void setExampleWord(const vector<char>& newExampleWord);
    int getAttempt();
    int getWin();
    void makeFieldTest();
    void guessWordTest();
    bool validityTest(const vector<char>& word);
    void checkBoxTest();
    void Play();
};
