#pragma once
#include "Options.h"
#include <string>
#include <map>
#include <vector>
using namespace std;


class Events {
private:
	string text;

public:
	Events();
	static void setUpEvents(string fileName);
	static map<string, Events> eventsArray;
	vector<Options> options;

	map<int, string> nextEventLine;
	
	string getText();
};