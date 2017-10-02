#pragma once
#include <string.h>
#include <vector>
#include <string>

using namespace std;

class City {
private:
	int id;
	string name;
	int area;
	int people;
	//std::vector<char*> roadsFromTo;

public:
	City() {};
	City(char *newName, int count, int ar, int id);
	City(const City&);

	void setUp(const City&);
	City& operator=(const City&);
	friend bool operator < (const City &l, const City &r) { return l.id < r.id; }
	string getName();
	int getID();
	int getKm();
	int getPeople(int count);

	~City() {}
};