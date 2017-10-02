#pragma once
#include <map>
#include <string>
#include "Transport.h"
#include "Orders_control.h"

class Company {
private:
	char *name;
	//int id;
	int income;
	int costs;
	std::map<tr::name, int> trBuoght;
	std::map<tr::name, int> trRented;

	Plane pn;
	Truck tk;
	Train tn;
	Ship sp;

public:
	Company() {}
	Company(char *name);
	Company(const Company&);

	void setUp(const Company&);
	Company& operator =(const Company&);
	string getAssets(int rent);
	void spendMoney(int count);
	int getMoney();
	int getTrPos(int kg,int km);
	void addTransport(tr::name c, int rent); /*, Transport newTR*/

	~Company() { delete[] name; };
};