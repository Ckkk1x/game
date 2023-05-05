#pragma once
using namespace std;


class MainHero {
private:
	short int physicalHealth;
	short int mentalHealth;
	short int hope;
	short int resurrection;

public:
	static MainHero* mainhero;

	MainHero();
	void setupStats();
	short int getPhysicalHealth();
	void changePhysicalHealth(int change);
	short int getMentalHealth();
	void changeMentalHealth(int change);
	short int getHope();
	void changeHope(int change);
	short int getResurrection();
	void changeResurrection(int change);
	
	void haveDiedOrNot();
	void Reborn();

};