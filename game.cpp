﻿#include "stdafx.h"
using namespace std;

int main() {
	try {
	Events::setUpEvents("Events.txt");
	setSizeOfWindow();
	//main menu
	gameprocess();

	}
	catch(const exception& ex) {
		system("cls");
		cout << ex.what() << endl;
	}

	return 0;
}