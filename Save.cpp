#include "Save.h"
#include "MainHero.h"
#include <fstream>
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

// TODO - �� ������ ��������� ����� ������ ����������� ��������� ������ ������.
Save::Save() {
	MainHero temp;
	temp.setupStats();

	this->eventsGroupIndex = 0;
	this->currentEventIndex = 0;
	this->mainhero = temp;
}
//Name of file with savings
string Save::filename = "MySave.txt";
 Save* Save::save = NULL;

 // ����� ���������� ��� �� ��������� �������
void Save::CreateNewSave() {
	if (Save::save == NULL) {
		Save::save = new Save;
	}
	MainHero temp;
	temp.setupStats();

	(*Save::save).eventsGroupIndex = 0;
	(*Save::save).currentEventIndex = 0;
	(*Save::save).mainhero = temp;
}

void Save::SaveCurrentProgress(int eventsGroupIndex, int currentEventIndex, MainHero mainhero) {
	(*Save::save).setEventsGroupIndex(eventsGroupIndex);
	(*Save::save).setCurrentEventIndex(currentEventIndex);
	(*Save::save).setMainhero(mainhero);
	Save::save->SaveToFile();
}

void Save::SaveToFile() {
	fstream file;
	file.open(Save::filename, ios::out);
	if (!file) {
		throw exception("������ �������� �����");
	}
	file << this->eventsGroupIndex << '\n';
	file << this->currentEventIndex << '\n';
	file.write((char*)&(this->mainhero), sizeof(MainHero));
	file.close();
}

void Save::TakeFromFile() {
	fstream file;
	file.open(Save::filename, ios::in);
	if (!file) {
		setlocale(LC_ALL, "rus");
		system("cls");
		cout << "�� ������ ���� ����������. ������� ����� �������, ��� ������� ����� ����...";
		_getch();
		setlocale(LC_ALL, "ru_RU.UTF-8");
	}
	else {
		string temp;
		file >> temp;
		this->eventsGroupIndex = stoi(temp);
		file >> temp;
		this->currentEventIndex = stoi(temp);
		file.read((char*)&(this->mainhero), sizeof(MainHero));
	}
	file.close();
}

int Save::getEventsGroupIndex() {
	return this->eventsGroupIndex;
}
int Save::getCurrentEventIndex() {
	return this->currentEventIndex;
}
MainHero Save::getMainhero() {
	return this->mainhero;
}
void Save::setEventsGroupIndex(int eventsGroupIndex) {
	this->eventsGroupIndex = eventsGroupIndex;
}
void Save::setCurrentEventIndex(int currentEventIndex) {
	this->currentEventIndex = currentEventIndex;
}
void Save::setMainhero(MainHero mainhero) {
	this->mainhero = mainhero;
}