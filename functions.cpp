#include "functions.h"
#include "events.h"
#include "MainHero.h"
#include <iostream>
#include <locale.h>
#include <conio.h>
using namespace std;

int userChoice = 0;

void gameprocess() {
	Events event = Events::eventsArray["A1"];
	showEvent(event);
    Events event2 = Events::eventsArray["A2"];
    showEvent(event2);

	// �������� ��������� - ����� ���� ������� ������ ������
}

void setSizeOfWindow() {
    // ��������� ������� ����
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = { 0, 0, 119, 39 };        // ���������� �������� ������ ���� � ������� ������� ����
    SetConsoleWindowInfo(console, TRUE, &rect); // ��������� ������ �������

    // ���������� ��������� ������� ���� �����
    HWND hwndConsole = GetConsoleWindow();
    LONG style = GetWindowLong(hwndConsole, GWL_STYLE);
    style &= ~WS_THICKFRAME;                    // ������� ����� ��������� ������� ����
    SetWindowLong(hwndConsole, GWL_STYLE, style);
}

void showEvent(Events event) {
    cout << R"(
    ----------------------------------------------------------
    )";
    cout << event.getText() << endl << endl;
    for (int i = 0; i < event.options.size(); i++) {
        cout << i + 1 << ") " << event.options[i].text << endl;
    }
    cout << R"(
    ----------------------------------------------------------
    )";
    handleInput(event);
    if (userChoice != -1) {
        impactOnHero(event.options[userChoice - 1]);
    }
    (*MainHero::mainhero).haveDiedOrNot();
    system("cls");
}


void handleInput(Events event) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int key;
    bool done = false;
    int sizeOfOptionsArray = event.options.size();
    while (!done) {
        key = _getch();
        if (key == 99 || key == 241 && event.options.size() == 0) {
            // ���� ��� ������� ��� ������, �� ����� ����� ������ �������� "c" ��� �� ����������
            // ��� ����� �������� ��� � default � ������ ������� ������ ������ ������
            done = true;
            userChoice = -1;
        }
        switch (key) {
        case 49: // 1
            // ��������� ������ �������� 1
            if (sizeOfOptionsArray >= 1) {
                done = true;
                userChoice = 1;
            } 
            break;
        case 50: // 2
            // ��������� ������ �������� 2
            if (sizeOfOptionsArray >= 2) {
                done = true;
                userChoice = 2;
            }
            break;
        case 51: // 3
            // ��������� ������ �������� 3
            if (sizeOfOptionsArray >= 3) {
                done = true;
                userChoice = 3;
            }
            break;
        case 52: // 4
            // ��������� ������ �������� 4
            if (sizeOfOptionsArray >= 4) {
                done = true;
                userChoice = 4;
                cout << "4" << endl;
            }
            break;
        case 53: // 5
            // ��������� ������ �������� 5
            if (sizeOfOptionsArray >= 5) {
                done = true;
                userChoice = 5;
                cout << "5" << endl;
            }
            break;
        case 54: // 6
            // ��������� ������ �������� 6
            if (sizeOfOptionsArray >= 6) {
                done = true;
                userChoice = 6;
                cout << "6" << endl;
            }
            break;
        case 55: // 7
            // ��������� ������ �������� 7
            if (sizeOfOptionsArray >= 7) {
                done = true;
                userChoice = 7;
                cout << "7" << endl;
            }
            break;
        case 56: // 8
            // ��������� ������ �������� 8
            if (sizeOfOptionsArray >= 8) {
                done = true;
                userChoice = 8;
                cout << "8" << endl;
            }
            break;
        case 57: // 9
            // ��������� ������ �������� 9
            if (sizeOfOptionsArray >= 9) {
                done = true;
                userChoice = 9;
                cout << "9" << endl;
            }
            break;
        case 48: // 0
            // ��������� ������ �������� 10
            if (sizeOfOptionsArray >= 10) {
                done = true;
                userChoice = 10;
                cout << "10" << endl;
            }
            break;
        case 27: // Escape
            // ��������� ������� ������� Escape
            done = true;
            break;
        case 83: // s
            // ������ ����������
            done = true;
            break;
        default:
            // ����������� �������, ������ ���������� ��
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