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
    1. ����������
    2. ����� ����
    0. �����
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
    bool hasChanged = false; 
    vector<vector<string>> idsOfEvents = {{"A4"}, {"B1"}};
    for (int eventsGroupIndex = 0; eventsGroupIndex < idsOfEvents.size(); eventsGroupIndex++) {
        hasChanged = false;
        for (int currentEventIndex = 0; currentEventIndex < idsOfEvents[eventsGroupIndex].size(); currentEventIndex++) {
            string currentId = idsOfEvents[eventsGroupIndex][currentEventIndex];
            Events currentEvent = Events::eventsArray[currentId];
	        showEvent(currentEvent);
            if (leaveToMenu) {
                // TODO ��� ������ ���� ����������
                return;
            }
            if (currentEvent.nextEventLine.size() > 0) {
                // ����� ��������� ����� �������
                eventsGroupIndex = findLineOfEventsById(idsOfEvents, currentEvent.nextEventLine[userChoice]);
                hasChanged = true;
                break;
            }
        }
        if (!hasChanged) { 
            // ���� ������ ����� �������, �� �� �������� �� ���������, 
            // ����� �������� ��������, ��� �� �� ������ ��������������� ���������� �����
            break;
        }
    }
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
        cout << '\t' << i + 1 << ") " << event.options[i].text << endl;
    }
    setlocale(LC_ALL, "rus");
    cout << endl << "\t->esc ��� ������ � ������� ����" << endl;
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
    if (userChoice != -1 && userChoice != -2 && userChoice != 0) {
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
        if (key == 32 && event.options.size() == 0) {
            // ���� ��� ������� ��� ������, �� ����� ����� ������ �������� ������ ��� �� ����������
            // ��� ����� �������� ��� � default � ������ ������� ������ ������ ������
            done = true;
            userChoice = 0;
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
            }
            break;
        case 53: // 5
            // ��������� ������ �������� 5
            if (sizeOfOptionsArray >= 5) {
                done = true;
                userChoice = 5;
            }
            break;
        case 54: // 6
            // ��������� ������ �������� 6
            if (sizeOfOptionsArray >= 6) {
                done = true;
                userChoice = 6;
            }
            break;
        case 55: // 7
            // ��������� ������ �������� 7
            if (sizeOfOptionsArray >= 7) {
                done = true;
                userChoice = 7;
            }
            break;
        case 56: // 8
            // ��������� ������ �������� 8
            if (sizeOfOptionsArray >= 8) {
                done = true;
                userChoice = 8;
            }
            break;
        case 57: // 9
            // ��������� ������ �������� 9
            if (sizeOfOptionsArray >= 9) {
                done = true;
                userChoice = 9;
            }
            break;
        case 48: // 0
            // ��������� ������ �������� 10
            if (sizeOfOptionsArray >= 10) {
                done = true;
                userChoice = 10;
            }
            break;
        case 27: // Escape
            // ��� ������ ���� ������� � ����
            done = true;
            leaveToMenu = true;
            system("cls");
            break;
        //case 83: // s
        //    // ������ ���������� 
        //    done = true;
        //    break;
        default:
            // ����������� �������, ������ ���������� ��
            break;
        }
    }
}

void impactOnHero(Options option) {
    if (option.changePhysical + (*MainHero::mainhero).getPhysicalHealth() <= 100) {
        (*MainHero::mainhero).changePhysicalHealth(option.changePhysical);
    }
    else {
        int over = (option.changePhysical + (*MainHero::mainhero).getPhysicalHealth()) - 100;
        (*MainHero::mainhero).changePhysicalHealth(option.changePhysical - over); 
    }

    if (option.changeMental + (*MainHero::mainhero).getMentalHealth() <= 100) {
        (*MainHero::mainhero).changeMentalHealth(option.changeMental);
    }
    else {
        int over = (option.changeMental + (*MainHero::mainhero).getMentalHealth()) - 100;
        (*MainHero::mainhero).changeMentalHealth(option.changeMental - over);
    }

    if (option.changeHope + (*MainHero::mainhero).getHope() <= 100) {
        (*MainHero::mainhero).changeHope(option.changeHope);
    }
    else {
        int over = (option.changeHope + (*MainHero::mainhero).getHope()) - 100;
        (*MainHero::mainhero).changeHope(option.changeHope - over);
    }


    int changeResurr = 0;
    // ���� �� ����� ������������ ���-�� ������ 
    if (option.changeResurrection == 3) {
        changeResurr = option.changeResurrection - (*MainHero::mainhero).getResurrection();
    }
    // ���� �� ����� ������ ��������� �����-�� ���������� ������
    else {
        changeResurr = option.changeResurrection;
    }
    (*MainHero::mainhero).changeResurrection(changeResurr);
}

int findLineOfEventsById(vector<vector<string>> idsOfEvents, string firstIdOfNextEvents) {
    for (int i = 0; i < idsOfEvents.size(); i++) {
        if (firstIdOfNextEvents == idsOfEvents[i][0]) {
            //���� ��������� ����� �������, �� ������� �������
            // -1 ������ ��� ����� ����������� ��������, ��� ��� ���������������� ������ for 
            return i-1; 
        }
    }
    // ���� �� �� ����� �������
    throw exception("�� ������� ��������� ������� �������!");
}