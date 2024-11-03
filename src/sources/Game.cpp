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
        cerr << "Ошибка открытия файла словаря!" << endl;
        return;
    }

    string word;
    srand(time(nullptr));
    int count = 0;
    while (file >> word) {
        if (word.length() == WORD_LENGTH) { // Проверка на длину слова
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
        cout << "Введите слово: ";
        for (int i = 0; i < WORD_LENGTH; i++) {
            cin >> userWord[i];
        }

        // Проверяем, есть ли введенное слово в файле словаря
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
            cout << "Введенное слово не найдено в словаре. Пожалуйста, введите другое слово." << endl;
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
    return guessWordStr; // Возвращает вектор guessWordStr
}

vector<char> Game::getExampleWord() {
    return exampleWord; // Возвращает вектор exampleWord
}

vector<vector<char>> Game::getField() {
    return field; // Возвращает двумерный вектор field
}

vector<char> Game::getUserWordChar() {
    return userWordChar; // Возвращает вектор userWordChar
}

int Game::getAttempt() {
    return attempt; // Возвращает значение attempt
}

int Game::getWin() {
    return win; // Возвращает значение win
}

void Game::makeFieldTest() {
    makeField(); // Вызывает makeField() игры
}

void Game::guessWordTest() {
    guessWord(); // Вызывает guessWord() игры
}

bool Game::validityTest(const vector<char>& word) {
    userWordChar = word; // Устанавливает userWordChar в тестируемое слово
    return validity(); // Вызывает validity() игры и возвращает результат
}

void Game::checkBoxTest() {
    checkBox(); // Вызывает checkBox() игры
}

void Game::Play() {
    attempt = 0;
    field.clear();
    guessWord();

    string ex = "";
    for (int h = 0; h < WORD_LENGTH; h++) {
        ex += exampleWord[h];
    }
    cout << "Игра \"" << WORD_LENGTH << " букв\"" << endl; // Изменение заголовка игры

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
            cout << "Ты победил!" << endl;
            break;
        }

        attempt++;
    }

    if (attempt == 6) {
        cout << "Ты проиграл. Загаданное слово было: " << ex << endl; // Изменение заголовка игры
    }

    attempt = 0;
    guessWordStr.clear();
    exampleWord.clear();
    userWordChar.clear();
    partial = 0;
    perfect = 0;
}