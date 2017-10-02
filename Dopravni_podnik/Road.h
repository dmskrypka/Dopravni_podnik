#pragma once
#include <vector>
#include <string>
#include "City.h"

class Road {
private:
	std::string name;
	int length;
	std::vector<City> r;

public:
	Road() {}
	Road(std::string n, int len);
	Road(const Road&);

	Road& operator =(const Road&);
	void setUp(const Road&);
	~Road() {};
};