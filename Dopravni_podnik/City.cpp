#include "City.h"

City::City(char *newName, int count, int ar, int id) {
	this->name = newName;
	this->people = count;
	this->area = ar;
	this->id = id;
}

City::City(const City & c) { setUp(c); }

City& City::operator =(const City & c) {
	setUp(c);
	return *this;
}

string City::getName() {
	return this->name;
}

int City::getKm() {
	return this->area;
}

int City::getID() {
	return this->id;
}

int City::getPeople(int count) {
	return this->people;
}

void City::setUp(const City & c) {
	id = c.id;
	name = c.name;
	area = c.area;
	people = c.people;
}