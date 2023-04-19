#include "stdafx.h"
using namespace std;

int main() {
	try {
	Events::setUpEvents("Events.txt");
	//main menu
	gameprocess();

	}
	catch(const exception& ex) {
		system("cls");
		cout << ex.what() << endl;
	}

	return 0;
}