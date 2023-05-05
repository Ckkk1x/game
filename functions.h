#pragma once
#include "events.h"
#include <windows.h>

void menu();
void gameprocess();
void setSizeOfWindow();
void showEvent(Events event);
void handleInput(Events event);
void impactOnHero(Options option);