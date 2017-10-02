#include "Company.h"

Company::Company(char *name) {
	this->name = name;
	this->income = 1000000;
	this->costs = 0;
	this->trBuoght[tr::TRUCK] = 5;
	this->trBuoght[tr::TRAIN] = 0;
	this->trBuoght[tr::PLANE] = 0;
	this->trBuoght[tr::SHIP] = 0;
	this->trRented[tr::TRUCK] = 0;
	this->trRented[tr::TRAIN] = 0;
	this->trRented[tr::PLANE] = 0;
	this->trRented[tr::SHIP] = 0;
}

Company::Company(const Company & c) { setUp(c); }

Company& Company::operator =(const Company& c) {
	setUp(c);
	return *this;
}

int Company::getTrPos(int kg,int km) { //~~~~
	int res = 0;
	int x=0;
	int count[4];
	count[0] = tk.getKg()*trBuoght[tr::TRUCK] + tk.getKg()*trRented[tr::TRUCK];
	if (kg <= count[0]) {
		this->income=income+(km*tk.Price());
		return 1;
	}
	res = kg - count[0];
	count[1] = pn.getKg()*trBuoght[tr::PLANE] + pn.getKg()*trRented[tr::PLANE];
	if (res <= count[1]) {
		x = (count[0] * tk.Price()) + (res * pn.Price());
		this->income = income + x;
		return 1;
	}
	count[2] = tn.getKg()*trBuoght[tr::TRAIN] + tn.getKg()*trRented[tr::TRAIN];
	if (res <= count[2]) {
		x += ((count[0] * tk.Price()) + (count[1] * pn.Price()) + ((kg - count[0] - count[1]) * pn.Price()));
		this->income = income + x;
		return 1;
	}
	res = kg - count[0] - count[1]-count[2];
	count[2] = sp.getKg()*trBuoght[tr::SHIP] + sp.getKg()*trRented[tr::SHIP];
	if (res <= count[3]) {
		x += res*sp.Price();
		this->income = income + x;
		return 1;
	}
	return 0;
}

string Company::getAssets(int rent) {
	std::map<tr::name, int> &m = (!rent ? trBuoght : trRented);
	string res = "";
	if (!rent) {
		res = "BALANCE = " + to_string(this->getMoney()) + "\n";
		res = res + " Income: " + to_string(this->income) + "\n" + " Costs: " + to_string(this->costs) + "\n\n";
		res = res + "Transport:\n";
	}
	res = res + " " + tr::Print(tr::TRUCK) + " = " + to_string(m.find(tr::TRUCK)->second)+'\n';
	res = res + " " + tr::Print(tr::TRAIN) + " = " + to_string(m.find(tr::TRAIN)->second) + '\n';
	res = res + " " + tr::Print(tr::PLANE) + " = " + to_string(m.find(tr::PLANE)->second) + '\n';
	res = res + " " + tr::Print(tr::SHIP) + " = "  + to_string(m.find(tr::SHIP)->second) + '\n';
	return res;
}

void Company::addTransport(tr::name c,int rent) { /*, Transport newTR*/
	if (!rent) trBuoght[c] += 1;
	else trRented[c] += 1;
}

void Company::spendMoney(int count) {
	this->costs += count;
}

int Company::getMoney() {
	int res=(this->income - this->costs);
	return res;
}

void Company::setUp(const Company & c) {
	name = c.name;
	income = c.income;
	costs = c.costs;
	trBuoght[tr::TRUCK] = c.trBuoght.find(tr::TRUCK)->second;
	trBuoght[tr::TRAIN] = c.trBuoght.find(tr::TRAIN)->second;
	trBuoght[tr::PLANE] = c.trBuoght.find(tr::PLANE)->second;
	trBuoght[tr::SHIP] =  c.trBuoght.find(tr::SHIP)->second;
	trRented[tr::TRUCK] = c.trRented.find(tr::TRUCK)->second;
	trRented[tr::TRAIN] = c.trRented.find(tr::TRAIN)->second;
	trRented[tr::PLANE] = c.trRented.find(tr::PLANE)->second;
	trRented[tr::SHIP] = c.trRented.find(tr::SHIP)->second;
}