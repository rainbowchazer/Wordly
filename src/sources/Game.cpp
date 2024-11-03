#include "Game.h"

const int FIELD_ROWS = 6;
int WORD_LENGTH = 6;
string filename = "";

void Game::makeField() {
    for (int i = 0; i < FIELD_ROWS; i++) {
        vector<char> row;
        for (int j = 0; j < WORD_LENGTH; j++) {
            row.push_back('*');
            cout << " " << row[j] << " ";
        }
        field.push_back(row);
        cout << endl;
    }
}

void Game::guessWord() {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "������ �������� ����� �������!" << endl;
        return;
    }

    string word;
    srand(time(nullptr));
    int count = 0;
    while (file >> word) {
        if (word.length() == WORD_LENGTH) { // �������� �� ����� �����
            count++;
            if (rand() % count == 0) {
                guessWordStr = vector<char>(word.begin(), word.end());
            }
        }
    }
    file.close();

    exampleWord = guessWordStr;
}

void Game::checkBox() {
    for (int i = 0; i < FIELD_ROWS; i++) {
        vector<char> between(exampleWord.begin(), exampleWord.end());
        for (int j = 0; j < WORD_LENGTH; j++) {
            field[attempt][j] = userWordChar[j];

            if (field[i][j] == exampleWord[j]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
                cout << " " << field[i][j] << " ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                Game::perfect++;
            }
            else if (find(between.begin(), between.end(), field[i][j]) != between.end()) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN);
                cout << " " << field[i][j] << " ";
                int index = distance(between.begin(), find(between.begin(), between.end(), field[i][j]));


                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                Game::partial++;
            }
            else {
                cout << " " << field[i][j] << " ";
            }
        }
        cout << endl;
    }
}

bool Game::validity() {
    bool isValidInput = false;
    vector<char> userWord(WORD_LENGTH);

    do {
        isValidInput = true;
        cout << "������� �����: ";
        for (int i = 0; i < WORD_LENGTH; i++) {
            cin >> userWord[i];
        }

        // ���������, ���� �� ��������� ����� � ����� �������
        ifstream file(filename);
        string word;
        bool wordFound = false;
        while (file >> word) {
            vector<char> wordVec(word.begin(), word.end());
            if (wordVec == userWord) {
                wordFound = true;
                break;
            }
        }
        file.close();

        if (!wordFound) {
            isValidInput = false;
            cout << "��������� ����� �� ������� � �������. ����������, ������� ������ �����." << endl;
        }
    } while (!isValidInput);

    userWordChar = userWord;
    return true;
}

void Game::setGuessWordStr(const vector<char>& newGuessWordStr) {
    guessWordStr = newGuessWordStr;
}

void Game::setUserWordChar(const vector<char>& newUserWordChar) {
    userWordChar = newUserWordChar;
}

void Game::setExampleWord(const vector<char>& newExampleWord) {
    exampleWord = newExampleWord;
}

vector<char> Game::getGuessWordStr() {
    return guessWordStr; // ���������� ������ guessWordStr
}

vector<char> Game::getExampleWord() {
    return exampleWord; // ���������� ������ exampleWord
}

vector<vector<char>> Game::getField() {
    return field; // ���������� ��������� ������ field
}

vector<char> Game::getUserWordChar() {
    return userWordChar; // ���������� ������ userWordChar
}

int Game::getAttempt() {
    return attempt; // ���������� �������� attempt
}

int Game::getWin() {
    return win; // ���������� �������� win
}

void Game::makeFieldTest() {
    makeField(); // �������� makeField() ����
}

void Game::guessWordTest() {
    guessWord(); // �������� guessWord() ����
}

bool Game::validityTest(const vector<char>& word) {
    userWordChar = word; // ������������� userWordChar � ����������� �����
    return validity(); // �������� validity() ���� � ���������� ���������
}

void Game::checkBoxTest() {
    checkBox(); // �������� checkBox() ����
}

void Game::Play() {
    attempt = 0;
    field.clear();
    guessWord();

    string ex = "";
    for (int h = 0; h < WORD_LENGTH; h++) {
        ex += exampleWord[h];
    }
    cout << "���� \"" << WORD_LENGTH << " ����\"" << endl; // ��������� ��������� ����

    makeField();

    while (attempt < 6) {
        if (!validity()) {
            break;
        }

        system("cls");

        checkBox();

        win = 0;
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (exampleWord[i] == userWordChar[i]) {
                win++;
            }
        }

        if (win >= WORD_LENGTH) {
            cout << "�� �������!" << endl;
            break;
        }

        attempt++;
    }

    if (attempt == 6) {
        cout << "�� ��������. ���������� ����� ����: " << ex << endl; // ��������� ��������� ����
    }

    attempt = 0;
    guessWordStr.clear();
    exampleWord.clear();
    userWordChar.clear();
    partial = 0;
    perfect = 0;
}