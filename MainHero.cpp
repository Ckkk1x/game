#include "MainHero.h"
#include <iostream>
#include <locale.h>
#include <conio.h>
using namespace std;



MainHero::MainHero() {
	physicalHealth = 100;
	mentalHealth = 100;
	hope = 100;
	resurrection = 1;
}

MainHero* MainHero::mainhero = new MainHero;

void MainHero::setupStats() {
	physicalHealth = 100;
	mentalHealth = 100;
	hope = 100;
	resurrection = 1;
}
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
	else if (mentalHealth <= 0) {
		system("cls");
		cout << R"(
		Персонаж сошел с ума, ментальные силы закончились. Теперь он идет спасать украинцев. Нажмите любую кнопку что бы продолжить.
		)";
		_getch();
	}
	else if (hope <= 0) {
		system("cls");
		cout << R"(
		Персонаж потерял веру...Теперь он вишня. Нажмите любую кнопку что бы продолжить.
		)";
		_getch();
	}
	if (physicalHealth <= 0 || mentalHealth <= 0 || hope <= 0) {
		MainHero::mainhero->Reborn();
	}
	
	setlocale(LC_ALL, "ru_RU.UTF-8");
}

void MainHero::Reborn(){
	setlocale(LC_ALL, "rus");
	if (resurrection > 0) {
		physicalHealth = 100;
		mentalHealth = 100;
		hope = 100;
		resurrection -= 1;

		system("cls");
		cout << R"(
		Персонаж использовал перерождение. Силы восстановлены.
		)";
		cout << "Количество оставшихся возрождений: " << resurrection << endl;
		_getch();
	}
	else if (resurrection <= 0) {
		system("cls");
		cout << R"(
		У персонажа не осталось более перерождений. Теперь он упокоится навечно...
		)";
		_getch();
		// TODO Тут должен быть переход к последнему сохранению. Или его загрузка.
		exit(1);
	}

	setlocale(LC_ALL, "ru_RU.UTF-8");
}