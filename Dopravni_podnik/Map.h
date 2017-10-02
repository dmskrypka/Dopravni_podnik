#pragma once
#include <map>
#include <iostream>
#include "City.h"
#include "Road.h"

class Map {
private:
	std::map<int,City> mC;
public:
	Map() {}
	Map(const Map&);

	Map& operator=(const Map&);
	void AddCityOnMap(City newC, int n);
	City find(int id);
	void Print();
	int getLength();

	~Map() {}
};