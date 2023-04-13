#pragma once
#include "Options.h"
#include <string>
#include <map>
#include <vector>
using namespace std;


class Events {
private:
	string text;
	string id;
	static map<string, Events> eventsArray;
	vector<Options> options;


public:
	Events();
	static void setUpEvents(string fileName);
	

};