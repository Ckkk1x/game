#include "stdafx.h"
using namespace std;

int main() {
	try {
		Events::setUpEvents("Events.txt");
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