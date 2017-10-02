#include "Transport.h"

Transport& Transport::operator =(const Transport & t) {
	setUp(t);
	return *this;
}

void Transport::setUp(const Transport & t) {
	id = t.id;
	type = t.type;
	kmH = t.kmH;
	capacity = t.capacity;
	depreciation = t.depreciation;
	fix = t.fix;
}

int Transport::getKg() { return this->capacity; }
int Transport::Price() { return this->kmPrice; }

void Transport::crashingTR(int km) {
	this->depreciation -= km;
}

int Transport::getID() {
	return this->id;
}

Transport::Transport() {
	this->fix = 0;
	this->type = setType();
}

Transport::Transport(const Transport & t) { setUp(t); }

Truck::Truck() {
	//this->id = id;
	this->type = setType();
	this->kmH = 80;
	this->capacity = 30;
	this->depreciation = 2000;
}

tr::name Truck::setType() {	return tr::TRUCK; }

Train::Train() {
	//this->id = id;
	this->type = setType();
	this->kmH = 60;
	this->capacity = 300;
	this->depreciation = 5000;
};

tr::name Train::setType() {	return tr::TRAIN; }

Plane::Plane() {
	//this->id = id;
	this->type = setType();
	this->kmH = 800;
	this->capacity = 100;
	this->depreciation = 3000;
}

tr::name Plane::setType() {	return tr::PLANE; }

Ship::Ship() {
	//this->id = id;
	this->type = setType();
	this->kmH = 60;
	this->capacity = 200;
	this->depreciation = 4000;
}

tr::name Ship::setType() { return tr::SHIP; }