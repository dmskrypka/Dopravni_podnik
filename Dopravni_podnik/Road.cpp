#include "Road.h"

Road::Road(std::string n, int len) {
	this->name = n;
	this->length = len;
};

Road::Road(const Road & r) { setUp(r); }

Road& Road::operator =(const Road& r) {
	setUp(r);
	return *this;
}

void Road::setUp(const Road & r) {
	name = r.name;
	length = r.length;
}