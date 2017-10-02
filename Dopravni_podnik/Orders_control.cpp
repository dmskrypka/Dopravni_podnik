#include "Orders_control.h"

#define ADD_SPEED 1000 // 1 sec

string Orders_control::getPath(int choose) { return (!choose ? this->oldPath : this->newPath); }

void Orders_control::delAllInfo() {
	ofstream doc_out;
	doc_out.open(this->newPath, ios_base::trunc);
	doc_out.close();
	doc_out.open(this->oldPath, ios_base::trunc);
	doc_out.close();
}

void Orders_control::delOrder(int id) {
	std::map<int, Order>::iterator enter,end;
	enter = this->newOrders.begin();
	end = this->newOrders.end();
	while (enter != end) {
		if (enter->second.getID() == id) {
			docDelete(this->newPath, enter->second);
			this->newOrders.erase(enter++);
		}
		else ++enter;
	}
}

void Orders_control::docInsert(string path, Order &or) {
	ofstream doc(path, ios_base::app); //adding string to the file end
	if (!doc.is_open()) {
		cout << "File "<< path <<" couldn't be open\n";
	}
	else doc << or.getInfo();
	doc.close();
}

void Orders_control::docDelete(string path, Order &or ) {
	char line[150];
	string s = or .getInfo();
	int i = 0;
	ifstream doc_in;
	string text;
	doc_in.open(path);
	if (!doc_in.is_open()) {
		cout << "File " << path << " couldn't be open\n";
	}
	else {
		while (line[0]!='\0') {
			memset(line, 0, 150);
			doc_in.getline(line, 150);
			if (!(line[0]==s[0]) && line[0] != '\0') {
				text.insert(text.size(), line);
				text.insert(text.size(), "\n");
			}
			else continue;
		}
	}
	doc_in.close();
	ofstream doc_out;
	doc_out.open(path, ios_base::trunc);
	if (!doc_out.is_open()) {
		cout << "File " << path << " couldn't be open\n";
	}
	else doc_out << text;
	doc_out.close();
}

Order Orders_control::returnOrder(int id) { return this->newOrders.find(id)->second; }

void Orders_control::insertNewOrder(Order newO) {
	this->newOrders[newO.getID()] = newO;
	docInsert(this->newPath, newO);
}

void Orders_control::insertOldOrder(Order oldO) {
	this->oldOrders[oldO.getID()] = oldO;
	docInsert(this->oldPath, oldO);
	docDelete(this->newPath, oldO);
}

Orders_control::Orders_control() {
	this->newPath = "resources\\new_orders.txt";
	this->oldPath = "resources\\old_orders.txt";
	this->delAllInfo();
}

Orders_control& Orders_control::operator =(const Orders_control & oc) {
	newOrders.clear();
	oldOrders.clear();
	setUp(oc);
	return *this;
}

Orders_control::Orders_control(const Orders_control & oc) { setUp(oc); }

void Orders_control::setUp(const Orders_control & oc) {
	newPath = oc.newPath;
	oldPath = oc.oldPath;
	newOrders = oc.newOrders;
	oldOrders = oc.oldOrders;
}