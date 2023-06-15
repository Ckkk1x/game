#include "MainHero.h"
#include <iostream>
#include <locale.h>
#include <conio.h>
#include "functions.h"
using namespace std;

MainHero::MainHero() {
	physicalHealth = 100;
	mentalHealth = 100;
	hope = 100;
	resurrection = 0;
}

MainHero* MainHero::mainhero = new MainHero;

void MainHero::setupStats() {
	this->physicalHealth = 100;
	this->mentalHealth = 100;
	this->hope = 100;
	this->resurrection = 0;
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

void MainHero::setPhysicalHealth(int physicalHealth) {
	this->physicalHealth = physicalHealth;
}
void MainHero::setMentalHealth(int mentalHealth) {
	this->mentalHealth = mentalHealth;
}
void MainHero::setHope(int hope) {
	this->hope = hope;
}
void MainHero::setResurrection(int resurrection) {
	this->resurrection = resurrection;
}



bool MainHero::haveDiedOrNot() {
	bool haveDied = false;
	setlocale(LC_ALL, "rus");
	string str;
	if (physicalHealth <= 0) {
		system("cls");
		str = "\n\t����� ���� ��������. ������� ����� ������ ��� �� ����������...";
		haveDied = true;
	}
	else if (mentalHealth <= 0) {
		system("cls");
		//str = "\n\t�������� ����� � ���, ���������� ���� �����������. ������� ����� ������ ��� �� ����������.";
		haveDied = true;
	}
	else if (hope <= 0) {
		system("cls");
		str = "\n\t�������� ������� ���� � �����, ��������� ��������� � ����� �������� �� �����. ������� ����� ������ ��� �� ����������...";
		haveDied = true;
	}
	/*if (physicalHealth <= 0 || mentalHealth <= 0 || hope <= 0) {
		MainHero::mainhero->Reborn();
	}*/
	if (haveDied) {
		printText(str);
		_getch();
	}
	
	setlocale(LC_ALL, "ru_RU.UTF-8");
	return haveDied;
}

//void MainHero::Reborn(){
//	setlocale(LC_ALL, "rus");
//	if (resurrection > 0) {
//		physicalHealth = 100;
//		mentalHealth = 100;
//		hope = 100;
//		resurrection -= 1;
//
//		system("cls");
//		cout << R"(
//		�������� ����������� ������������. ���� �������������.
//		)";
//		cout << "���������� ���������� �����������: " << resurrection << endl;
//		_getch();
//	}
//	else if (resurrection <= 0) {
//		system("cls");
//		cout << R"(
//		� ��������� �� �������� ����� ������������. ������ �� ��������� �������...
//		)";
//		_getch();
//		// TODO ��� ������ ���� ������� � ���������� ����������. ��� ��� ��������.
//		exit(1);
//	}
//
//	setlocale(LC_ALL, "ru_RU.UTF-8");
//}