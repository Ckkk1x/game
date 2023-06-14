#include "stdafx.h"
using namespace std;

int main() {
	try {
		// Default filename - "Events.txt"
		Events::setUpEvents("TEST.txt");
		setSizeOfWindow();
		while (true)
		{
			menu();
		}
	}
	catch(const exception& ex) {
		setlocale(LC_ALL, "rus");
		system("cls");
		cout << ex.what() << endl;
	}

	return 0;
}