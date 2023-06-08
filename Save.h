#include "MainHero.h"
#include <string>
using namespace std;

class Save {
private:
	int eventsGroupIndex;
	int currentEventIndex;
public:
	MainHero mainhero;
	static Save* save;
	static string filename;

	static void CreateNewSave();

	Save();
	void SaveCurrentProgress(int eventsGroupIndex, int currentEventIndex, MainHero mainhero);
	void SaveToFile();
	void TakeFromFile();
	int getEventsGroupIndex();
	int getCurrentEventIndex();
	MainHero getMainhero();
	void setEventsGroupIndex(int eventsGroupIndex);
	void setCurrentEventIndex(int currentEventIndex);
	void setMainhero(MainHero mainhero);
};