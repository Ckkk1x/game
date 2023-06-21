#pragma once
#include "events.h"
#include <windows.h>

void menu();
void gameprocess();
void setSizeOfWindow();
void printText(string str);
void characteristics();
void showEvent(Events event);
void handleInput(Events event);
void impactOnHero(Options option);
int findLineOfEventsById(vector<vector<string>> idsOfEvents, string firstIdOfNextEvents);
