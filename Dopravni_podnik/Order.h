#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <fstream>

#include "Map.h"

using namespace std;

class Order {
private:
	int id;
	string name;
	City from;
	City to;
	int kg;
	int timeH;
	
public:
	Order() {};
	Order(Map m);
	Order(const Order&);

	void setUp(const Order&);
	Order& operator =(const Order&);
	void setNewOrder(Map m);
	int getID();
	int returnKG();
	int returnKM();
	string getInfo();
	friend bool operator ==(const Order &l, const Order &r) { return l.id == r.id; }
	friend bool operator < (const Order &l, const Order &r) { return l.id < r.id; }

	~Order() {};
};