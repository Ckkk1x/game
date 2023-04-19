#include "functions.h"
#include "events.h"
#include <iostream>
#include <locale.h>
using namespace std;

void gameprocess() {
	Events event = Events::eventsArray["A1"];
    setSizeOfWindow();
	showEvent(event);
	//void catchChoice();
	//void impactOnHero();
	// Проверка персонажа - может быть методом самого класса
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
    for (int i = 0; i < event.options.size()-1; i++) {
        cout << i + 1 << ") " << event.options[i].text << endl;
    }
    cout << R"(
    ----------------------------------------------------------
    )";
   
}