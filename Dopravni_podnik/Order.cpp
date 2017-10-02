#include "Order.h"

int id_m = 1;

char *randCompany(char *buff) {
	char num[10];
	int maxCount=0;
	const int len = 50;
	ifstream comp("resources\\comp.txt");
	if (!comp.is_open()) {
		cout << "File comp.txt couldn't be open\n";
	}
	else {
		comp.getline(num, 10);
		for (int i = 0; num[i] != '\0'; i++) {
			if (!maxCount) maxCount = num[i] - '0';
			else {
				maxCount *= 10;
				maxCount+= num[i] - '0';
			}
		}
		int x = rand() % maxCount + 1;
		while (!comp.eof()) {
			comp.getline(buff, len);
			x--;
			if (!x) break;
			memset(buff, 0, len);
		}
	}
	return buff;
}

string getName(char *buff) { // '-'=45 
	string res = "";
	char tmp=0;
	do {
		if (*buff == 45) tmp = '\0';
		else tmp = *buff;
		res += tmp;
		buff++;
	} while (*buff != 45);
	return res;
}

City getCityFrom(Map m,char *buff) {
	int res = 0;
	while(*buff != '\0') {
		if (*buff==45 || res) {
			if (!res) {
				buff++;
				res = *buff - '0';
			}
			else {
				res *= 10;
				res += *buff - '0';
			}
		}
		buff++;
	}
	return m.find(res);
}

City getCityTo(Map m, int id) {
	while (true) {
		int newID = rand() % m.getLength();
		newID += 100;
		if (newID != id) return m.find(newID);
	}
}

int getKG() {
	int res = rand() % 900;
	return res + 100;
}

int Order::returnKG() { return this->kg; }
int Order::returnKM() { return this->from.getKm() + this->to.getKm(); }

void Order::setNewOrder(Map m) {
	char *buff = new char[50];
	buff = randCompany(buff);
	this->id = id_m;
	this->name = getName(buff);
	this->from = getCityFrom(m,buff);
	this->to = getCityTo(m, this->from.getID());
	this->kg = getKG();

	delete[] buff;
	id_m += 1;
}

string Order::getInfo() {
	string res,tmp;
	res = this->id + '0';
	res = res + ". " + this->name + " {from: " + this->from.getName() + " | to: " + this->to.getName() + "} with ";
	res = res + to_string(this->kg) + "kg"+ "\n";
	return res;
}

Order::Order(Map m) { 
	this->setNewOrder(m); 
}

Order::Order(const Order & o) { setUp(o); }

int Order::getID() { 
	return this->id; 
}

Order& Order::operator=(const Order & o) {
	setUp(o);
	return *this;
}

void Order::setUp(const Order & o) {
	id = o.id;
	name = o.name;
	from = o.from;
	to = o.to;
	kg = o.kg;
}