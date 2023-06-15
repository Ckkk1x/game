#include "functions.h"
#include "events.h"
#include "MainHero.h"
#include "Save.h"
#include <iostream>
#include <locale.h>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;

int userChoice = -1;
bool leaveToMenu = false;

void menu() {
    setlocale(LC_ALL, "rus"); 
    cout << R"(
     >    ~~~~~~~ Заварушка в Велеграде ~~~~~~~    <
     |                                             |
     |                  Меню                       |
     |              1. Продолжить                  |
     |              2. Новая игра                  |
     |              0. Выйти                       |
     |                                             |
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
            Save::CreateNewSave();
            Save::save->TakeFromFile();
            (*MainHero::mainhero) = Save::save->mainhero;
            gameprocess();
            break;
        case 50: // 2
            setlocale(LC_ALL, "ru_RU.UTF-8");
            done = true;
            MainHero::mainhero->setupStats();
            Save::CreateNewSave();
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
    int eventsGroupIndex;
    int currentEventIndex;
    // {{"A1"}, {"B1"}, {"B2"}, {"B3"}, {"C1", "C2", "C3"}, {"F1"}}
    vector<vector<string>> idsOfEvents = { {"A1"}, {"B1"}, {"B2"}, {"B3"}, {"C1", "C2", "C3"}, {"F1"} };
    // Сохранение
    eventsGroupIndex = Save::save->getEventsGroupIndex();
    currentEventIndex = Save::save->getCurrentEventIndex();
    //---------
    for (; eventsGroupIndex < idsOfEvents.size(); eventsGroupIndex++) {
        hasChanged = false;
        while (currentEventIndex < idsOfEvents[eventsGroupIndex].size()) {
            string currentId = idsOfEvents[eventsGroupIndex][currentEventIndex];
            Events currentEvent = Events::eventsArray[currentId];
	        showEvent(currentEvent);
            if (leaveToMenu) {
                Save::save->SaveCurrentProgress(eventsGroupIndex, currentEventIndex, (*MainHero::mainhero));
                return;
            }
            if (currentEvent.nextEventLine.size() > 0) {
                // Поиск следующей ветки событий
                eventsGroupIndex = findLineOfEventsById(idsOfEvents, currentEvent.nextEventLine[userChoice]);
                hasChanged = true;
                break;
            }
            currentEventIndex++;
        }
        currentEventIndex = 0;
        if (!hasChanged) { 
            // Если вконце линии событий, мы не перейдем на следующие, 
            // нужно оборвать итерацию, что бы не начать последовательно перебирать линии
            break;
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

void printText(string str)
{
    for (int i = 0; i < str.length(); i++) {
        this_thread::sleep_for(0.04s);
        cout << str[i];
    }
}

void characteristics()
{
    int physHp = (*MainHero::mainhero).getPhysicalHealth() / 10;
    int mentalHp = (*MainHero::mainhero).getMentalHealth() / 10;
    int hopeHp = (*MainHero::mainhero).getHope() / 10;
    //cout << "\tResurrection: " << (*MainHero::mainhero).getResurrection() << endl;
    
    char symbol = 22;
    char heart = 3;
    cout << '\t' << "[" << heart << "]";
    for (int i = 0; i < physHp; i++) {
        cout << symbol;
    }
    cout << endl;
    char diamond = 4;
    cout << '\t' << "[" << diamond << "]";
    for (int i = 0; i < mentalHp; i++) {
        cout << symbol;
    }
    cout << endl;
    char clubs = 6;
    cout << '\t' << "[" << clubs << "]";
    for (int i = 0; i < hopeHp; i++) {
        cout << symbol;
    }
    cout << endl;

}

void showEvent(Events event) {
    cout << R"(
    ----------------------------------------------------------
    )";
    string str = event.getText();
    printText(str);
    cout << endl << endl;
    for (int i = 0; i < event.options.size(); i++) {
        cout << '\t' << i + 1 << ") " << event.options[i].text << endl;
    }
    setlocale(LC_ALL, "rus");
    cout << endl << "\t->esc для выхода в главное меню" << endl;
    if(event.options.size() == 0)
        cout << "\t->space для перехода к следующему событию" << endl;
    cout << R"(
    ----------------------------------------------------------
)";
    setlocale(LC_ALL, "ru_RU.UTF-8");
    characteristics();
    cout << endl;
    handleInput(event);
    if (leaveToMenu) {
        system("cls");
        return;
    }
    if (userChoice != -1 && userChoice != -2 && userChoice != 0) {
        impactOnHero(event.options[userChoice - 1]);
    }
    if (userChoice == 0) {
        impactOnHero(event.zeroOption);
    }
    if ((*MainHero::mainhero).haveDiedOrNot())
    {
        Save::save->CreateNewSave();
        system("cls");
        return;
    }
    system("cls");
}

void handleInput(Events event) {
    int key;
    bool done = false;
    int sizeOfOptionsArray = event.options.size();
    while (!done) {
        key = _getch();
        if (key == 32 && event.options.size() == 0) {
            // Если это событие без выбора, то нужно будет просто кликнуть пробел что бы продолжить
            // или можно закинуть это в default и ловить нажатие любоой другой кнопки
            done = true;
            userChoice = 0;
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
        //case 83: // s
        //    // Кнопка Сохранения 
        //    done = true;
        //    break;
        default:
            // Неизвестная клавиша, просто игнорируем ее
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
    
    //int changeResurr = 0;
    //// Если мы хотим восстановить кол-во жизней 
    //if (option.changeResurrection == 3) {
    //    changeResurr = option.changeResurrection - (*MainHero::mainhero).getResurrection();
    //}
    //// Если мы хотим просто прибавить какое-то количество жизней
    //else {
    //    changeResurr = option.changeResurrection;
    //}
    //(*MainHero::mainhero).changeResurrection(changeResurr);
}

int findLineOfEventsById(vector<vector<string>> idsOfEvents, string firstIdOfNextEvents) {
    for (int i = 0; i < idsOfEvents.size(); i++) {
        if (firstIdOfNextEvents == idsOfEvents[i][0]) {
            //Ищем следующую линию событий, по первому индексу
            // -1 потому что после возвращения значения, оно еще инкрементируется циклом for 
            return i-1; 
        }
    }
    // Если мы не нашли елемент
    throw exception("Не найдена следующая цепочка событий!");
}