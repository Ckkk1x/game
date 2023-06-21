#include "stdafx.h"
using namespace std;

int main() {
	try {
	Events::setUpEvents("Events.txt");
	//main menu
	void gameprocess();

	}
	catch(const exception& ex) {
		system("cls");
		cout << ex.what() << endl;
	}
	//gftfdtrfut
	return 0;
}