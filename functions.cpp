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
    for (int i = 0; i < event.options.size()-1; i++) {
        cout << i + 1 << ") " << event.options[i].text << endl;
    }
    cout << R"(
    ----------------------------------------------------------
    )";
   
}