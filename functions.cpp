#include "functions.h"
#include "events.h"
#include "MainHero.h"
#include <iostream>
#include <locale.h>
#include <conio.h>
using namespace std;

int userChoice = -1;
bool leaveToMenu = false;

void menu() {
    setlocale(LC_ALL, "rus");
    cout << R"(
    <--------------- Menu --------------->
    1. Продолжить
    2. Новая игра
    0. Выйти
    )";
    int key;
    bool done = false;
    while (!done) {
        key = _getch();
        switch (key)
        {
        case 49: // 1
            setlocale(LC_ALL, "ru_RU.UTF-8");
            done = true;
            gameprocess();
            break;
        case 50: // 2
            setlocale(LC_ALL, "ru_RU.UTF-8");
            done = true;
            MainHero::mainhero->setupStats();
            gameprocess();
            break;
        case 48: // 0
            exit(0);
            break;
        default:
            break;
        }
        leaveToMenu = false;
    }  
}

void gameprocess() {
    system("cls");
    string idsOfEvents[] = { "A1", "A2", "R1"};
    for(auto id : idsOfEvents) {
	showEvent(Events::eventsArray[id]);
        if (leaveToMenu) {
            // TODO тут должно быть сохранение
            return;
        }
    }
}

void setSizeOfWindow() {
    // Установка размера окна
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = { 0, 0, 119, 39 };        // координаты верхнего левого угла и нижнего правого угла
    SetConsoleWindowInfo(console, TRUE, &rect); // установка нового размера

    // Запрещение изменения размера окна мышью
    HWND hwndConsole = GetConsoleWindow();
    LONG style = GetWindowLong(hwndConsole, GWL_STYLE);
    style &= ~WS_THICKFRAME;                    // Удаляем стиль изменения размера окна
    SetWindowLong(hwndConsole, GWL_STYLE, style);
}

void showEvent(Events event) {
    cout << R"(
    ----------------------------------------------------------
    )";
    cout << event.getText() << endl << endl;
    for (int i = 0; i < event.options.size(); i++) {
        cout << '\t' << i + 1 << ") " << event.options[i].text << endl;
    }
    setlocale(LC_ALL, "rus");
    cout << endl << "\t->esc для выхода в главное меню" << endl;
    cout << R"(
    ----------------------------------------------------------
)";
    cout << "\tPhysical hp: " << (*MainHero::mainhero).getPhysicalHealth() << endl;
    cout << "\tMental hp: " << (*MainHero::mainhero).getMentalHealth() << endl;
    cout << "\tHope: " << (*MainHero::mainhero).getHope() << endl;
    cout << "\tResurrection: " << (*MainHero::mainhero).getResurrection() << endl;
    setlocale(LC_ALL, "ru_RU.UTF-8");
    cout << endl;
    handleInput(event);
    if (leaveToMenu) {
        return;
    }
    if (userChoice != -1) {
        impactOnHero(event.options[userChoice - 1]);
    }
    (*MainHero::mainhero).haveDiedOrNot();
    system("cls");
}

void handleInput(Events event) {
    int key;
    bool done = false;
    int sizeOfOptionsArray = event.options.size();
    while (!done) {
        key = _getch();
        if (key == 99 || key == 241 && event.options.size() == 0) {
            // Если это событие без выбора, то нужно будет просто кликнуть "c" что бы продолжить
            // или можно закинуть это в default и ловить нажатие любоой другой кнопки
            done = true;
            userChoice = -1;
        }
        switch (key) {
        case 49: // 1
            // Обработка выбора варианта 1
            if (sizeOfOptionsArray >= 1) {
                done = true;
                userChoice = 1;
            } 
            break;
        case 50: // 2
            // Обработка выбора варианта 2
            if (sizeOfOptionsArray >= 2) {
                done = true;
                userChoice = 2;
            }
            break;
        case 51: // 3
            // Обработка выбора варианта 3
            if (sizeOfOptionsArray >= 3) {
                done = true;
                userChoice = 3;
            }
            break;
        case 52: // 4
            // Обработка выбора варианта 4
            if (sizeOfOptionsArray >= 4) {
                done = true;
                userChoice = 4;
            }
            break;
        case 53: // 5
            // Обработка выбора варианта 5
            if (sizeOfOptionsArray >= 5) {
                done = true;
                userChoice = 5;
            }
            break;
        case 54: // 6
            // Обработка выбора варианта 6
            if (sizeOfOptionsArray >= 6) {
                done = true;
                userChoice = 6;
            }
            break;
        case 55: // 7
            // Обработка выбора варианта 7
            if (sizeOfOptionsArray >= 7) {
                done = true;
                userChoice = 7;
            }
            break;
        case 56: // 8
            // Обработка выбора варианта 8
            if (sizeOfOptionsArray >= 8) {
                done = true;
                userChoice = 8;
            }
            break;
        case 57: // 9
            // Обработка выбора варианта 9
            if (sizeOfOptionsArray >= 9) {
                done = true;
                userChoice = 9;
            }
            break;
        case 48: // 0
            // Обработка выбора варианта 10
            if (sizeOfOptionsArray >= 10) {
                done = true;
                userChoice = 10;
            }
            break;
        case 27: // Escape
            // Тут должен быть переход в меню
            done = true;
            leaveToMenu = true;
            system("cls");
            break;
        case 83: // s
            // Кнопка Сохранения 
            done = true;
            break;
        default:
            // Неизвестная клавиша, просто игнорируем ее
            break;
        }
    }
}

void impactOnHero(Options option) {
    (*MainHero::mainhero).changePhysicalHealth(option.changePhysical);
    (*MainHero::mainhero).changeMentalHealth(option.changeMental);
    (*MainHero::mainhero).changeHope(option.changeHope);

    (*MainHero::mainhero).changeResurrection(option.changeResurrection);
}