#pragma once
#include <string>
namespace tr {
	enum name { TRUCK, TRAIN, PLANE, SHIP, DEFAULT };

	int Price(name c);
	std::string Print(name c);

	inline std::string Print(name c) {
		std::string res="";
		switch (c) {
		case PLANE:
			res = "PLANE";
			break;
		case SHIP:
			res = "SHIP ";
			break;
		case TRAIN:
			res = "TRAIN";
			break;
		case TRUCK:
			res = "TRUCK";
			break;
		}
		return res;
	}
	inline int Price(name c) {
		int res = 0;
		switch (c) {
		case PLANE:
			res = 100000;
			break;
		case SHIP:
			res = 150000;
			break;
		case TRAIN:
			res = 80000;
			break;
		case TRUCK:
			res = 10000;
			break;
		}
		return res;
	}
}

class Transport {
protected:
	int id;
	tr::name type;
	int kmH;
	int kmPrice;
	int capacity;
	int depreciation; // while > 0
	int fix; // while != 5

public:
	Transport();
	Transport(const Transport&);

	Transport& operator=(const Transport&);
	void setUp(const Transport&);
	virtual tr::name setType() { return tr::DEFAULT; }
	void crashingTR(int km);
	int getID();
	int getKg();
	int Price();
	friend bool operator < (const Transport &l, const Transport &r) { return l.id < r.id; }


	virtual ~Transport() {};
};

class Truck : public Transport {
public:
	Truck();
	~Truck() {};

	tr::name setType();
};

class Train : public Transport {
public:
	Train();
	~Train() {};

	tr::name setType();
};

class Plane : public Transport {
public:
	Plane();
	~Plane() {};

	tr::name setType();
};

class Ship : public Transport {
public:
	Ship();
	~Ship() {};

	tr::name setType();
};