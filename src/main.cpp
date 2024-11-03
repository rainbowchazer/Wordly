#include "Game.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "Russian");
    std::locale::global(std::locale(""));
    Game game;
    int action = 0;

    while (true) {
        cout << "Выберите действие: \n"
            "1. Слова из 6 букв. \n"
            "2. Слова из 7 букв. \n"
            "3. Выйти из игры. \n"
            "Ваш выбор - ";

        if (!(cin >> action)) {
            cin.clear();
            while (cin.get() != '\n') {}
            cout << "Ошибка ввода. Пожалуйста, введите целое число." << endl;
            continue;
        }

        switch (action) {
        case 1:
            system("cls");
            WORD_LENGTH = 6;
            filename = "words6.txt";
            game.Play();
            break;

        case 2:
            system("cls");
            WORD_LENGTH = 7;
            filename = "words7.txt";
            game.Play();
            break;

        case 3:
            return 0;

        default:
            system("cls");
            cout << "Некорректный ввод, попробуйте снова." << endl;
            break;
        }
    }

    return 0;
}