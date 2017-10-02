#pragma once
#include <thread>
#include <iostream>
#include <ostream>
#include <fstream>
#include "Order.h"

class Orders_control {
private:
	string newPath;
	string oldPath;
	std::map<int, Order> newOrders;
	std::map<int, Order> oldOrders;
	
public:
	Orders_control();
	Orders_control(const Orders_control&);

	void delAllInfo();
	string getPath(int choose);
	void delOrder(int id);
	Order returnOrder(int id);
	void docInsert(string path, Order &or);
	void docDelete(string path, Order &or);
	void setUp(const Orders_control&);
	Orders_control& operator =(const Orders_control&);
	void insertNewOrder(Order newO);
	void insertOldOrder(Order newO);

	~Orders_control() {};
};