#include "MainHero.h"
#include <iostream>
#include <locale.h>
#include <conio.h>
using namespace std;

//short int physicalHealth;
//short int mentalHealth;
//short int hope;
//short int resurrection;
//static MainHero mainhero;

MainHero::MainHero() {
	physicalHealth = 100;
	mentalHealth = 100;
	hope = 100;
	resurrection = 3;
}

MainHero* MainHero::mainhero = new MainHero;

short int MainHero::getPhysicalHealth() {
	return physicalHealth;
}
void MainHero::changePhysicalHealth(int change) {
	physicalHealth += change;
}
short int MainHero::getMentalHealth() {
	return mentalHealth;
}
void MainHero::changeMentalHealth(int change) {
	mentalHealth += change;
}
short int MainHero::getHope() {
	return hope;
}
void MainHero::changeHope(int change) {
	hope += change;
}
short int MainHero::getResurrection() {
	return resurrection;
}
void MainHero::changeResurrection(int change) {
	resurrection += change;
}
void MainHero::haveDiedOrNot() {
	setlocale(LC_ALL, "rus");
	if (physicalHealth <= 0) {
		system("cls");
		cout <<  R"(
		Персонаж умер от недостатка физ сил. Нажмите любую кнопку что бы продолжить.
		)";
		_getch();
		
	}


	setlocale(LC_ALL, "ru_RU.UTF-8");
}