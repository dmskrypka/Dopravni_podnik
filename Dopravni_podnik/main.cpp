#include <Windows.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <locale.h>
#include <conio.h>
//#include <cstdlib> // Error: "system" is ambiguous

#include "Map.h"
#include "Company.h"

using namespace std;

#define ADD_SPEED 1000 // 1 sec

namespace length {
	int len0 = 60;
	int len1 = 60;
	const int charLen = 50;
	int cityNumber = 100;
	Map m;
}

int rentTransport(tr::name c, Company corp) {
	int corpMoney, price;
	corpMoney = corp.getMoney();
	price = tr::Price(c);
	price /= 100;
	return (corpMoney >= price ? (corp.spendMoney(price), 1) : 0);
}

int buyTransport(tr::name c, Company corp) {
	int corpMoney, price;
	corpMoney = corp.getMoney();
	price = tr::Price(c);
	return (corpMoney >= price ? (corp.spendMoney(price), 1) : 0);
}

void startGame() {
	system("title ItalyHorse45 Database Program");
	system("cls");
	system("color 0F");
	cout << "Start Game\n";
	ifstream info("resources\\info.txt");

	char buff[length::charLen];
	info.getline(buff, length::charLen);
	cout << buff;
	cout << '\n';
	memset(buff, 0, length::charLen);
	info.getline(buff, length::charLen);
	cout << buff << endl;
	info.close();
	system("pause");
}

int testChar(char buff[length::charLen], int i) {
	if (buff[i] == 32 || buff[i] == 9) {
		if (i + 1 < length::charLen && buff[i + 1] == 45) return 1;
	}
	return 0;
}

void charConvert(char buff[length::charLen], int i, int &number) {
	if (!number) number = buff[i] - '0';
	else {
		number *= 10;
		number += buff[i] - '0';
	}
}

void insertCity(char *tmp, int people, int km) {
	City newC(tmp, people, km, length::cityNumber);
	length::m.AddCityOnMap(newC, length::cityNumber);
	length::cityNumber += 1;
}

void Creating() {
	ifstream info("resources\\info.txt");
	char tmp_buff[20];
	int people = 0;
	int km = 0;
	char buff[length::charLen];
	if (!info.is_open()) {
		cout << "File info.txt couldn't be open\n";
	}
	else {
		while (true && !info.eof()) {
			info.getline(buff, length::charLen);
			if (buff[0] == '\0' || buff[0] == -52) break;
			int i = 0;
			for (; i < length::charLen; i++) { //get name
				if (testChar(buff, i) || buff[i] == '\0') break;
				tmp_buff[i] = buff[i];
			}
			tmp_buff[i] = '\0';
			for (i += 3; i < length::charLen; i++) { //get people
				if (testChar(buff, i)) break;
				charConvert(buff, i, people);
			}
			for (i += 3; i < length::charLen; i++) {
				if (testChar(buff, i) || buff[i] == '\0') break;
				charConvert(buff, i, km);
			}
			memset(buff, 0, length::charLen);
			insertCity(tmp_buff, people, km);
			km = people = 0;
		}
	}
}

int getPointerID(string s) {
	int res=0;
	int i = 0;
	while (s[i] != '.') {
		if (!res) res = s[i] - '0';
		else {
			res *= 10;
			res = res + s[i] - '0';
		}
		i++;
	}
	return res;
}

void showOrders(string path, int options, Orders_control &oc, Company &c) {
	ifstream doc;
	char buff[200];
	char s = 62;
	string t = "";
	int pointer = 0, i = 0,test=0;
	doc.open(path);
	if (!doc.is_open()) {
		cout << "File " << path << " couldn't be open\n";
	}
	else {
		while (true) {
			while (true) {
				doc.getline(buff, 200);
				while (buff[0] != '\0') {
					if (pointer == i && options) {
						cout << " " << s;
						t = buff;
					}
					else cout << "  ";
					cout << buff << '\n';
					memset(buff, 0, 200);
					doc.getline(buff, 200);
					i++;
				}
				memset(buff, 0, 200);
				cout << '\n';
				system("pause");
				if (!options) break;
				while (true) {
					if (GetAsyncKeyState(VK_DOWN)) {
						(pointer < i - 1 ? pointer++ : pointer = 0);
						break;
					}
					else if (GetAsyncKeyState(VK_UP)) {
						(pointer > 0 ? pointer-- : pointer = i - 1);
						break;
					}
					else if (GetAsyncKeyState(VK_RETURN)) {
						test = 1;
						break;
					}
					else {
						test = 2;
						break;
					}
				}
				i = 0;
				system("cls");
				cout << "NEW ORDERS:\n\n";
				doc.close();
				if (test == 1 || test == 2) break;
				doc.open(path);
			}
			if (test == 2) break;
			if (test == 1) {
				int id = getPointerID(t);
				Order &o = oc.returnOrder(id);
				int kg = o.returnKG();
				int km = o.returnKM();
				if(c.getTrPos(kg,km)!=0) oc.delOrder(id);
				break;
			}

		}
	}
	doc.close();
}

void manageTransport(Company &c) {
	char s = ' ',ch='*';
	tr::name tr[4] = { tr::TRUCK, tr::TRAIN, tr::PLANE, tr::SHIP };
	int p = 0;
	int i = 0, j = 0;
	int test = 0;
	while(true){
		cout << "MANAGE TRANSPORT:\n";
		cout << "\nYou have:\n";
		cout << c.getAssets(0);
		cout << "Rented:\n";
		cout << c.getAssets(1);
		cout << "\n\n";
		cout << " BUY\t\t\t";
		cout << "  RENT\n\n";
		while (true && j < 4) {
			if (!i && p == j) cout << ch;
			else cout << s;
			cout << tr::Print(tr[j]) + ": " + to_string(tr::Price(tr[j])) + "\t\t";
			if (i && p == j) cout << ch;
			else cout << s;
			cout << tr::Print(tr[j]) + ": " + to_string(tr::Price(tr[j])) + "\n";
			if (j == 3) cout << '\n';
			j++;
		}
		system("pause");
		system("cls");
		while (true) {
			if (GetAsyncKeyState(VK_DOWN)) {
				(p < 3 ? p++ : p = 0);
				break;
			}
			else if (GetAsyncKeyState(VK_UP)) {
				(p > 0 ? p-- : p = 3);
				break;
			}
			else if (GetAsyncKeyState(VK_RIGHT)) {
				(i ? i = 0 : i = 1);
				break;
			}
			else if (GetAsyncKeyState(VK_LEFT)) {
				(i ? i = 0 : i = 1);
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN)) {
				test = 1;
				break;
			}
			else { 
				test = 2;
				break;
			}
		}
		if (test == 1){
			int money = c.getMoney();
			int price = (i ? tr::Price(tr[p]) / 1000 : tr::Price(tr[p]));
			if (price > money) {
				system("cls");
				cout << "\n\n\n\n\n\n";
				cout << "\n\t\t\t\tNot enough money.\n";
				cout << "\n\n\n\n\n\n";
				system("pause");
				system("cls");
			}
			else {
				c.spendMoney(price);
				c.addTransport(tr[p],i);
			}
			test = 0;
		}
		if (test==2) break;
		j = 0;
	}
	
}

void startMenu(Orders_control &oc,Company &c) {
	int test = 0;
	int choose = 0;
	while (true) {
		if (!test) {
			cout << "\nIt's your little Transport Corp.";
			cout << "\n\n\t1. Show assets.";
			cout << "\n\t2. Show new orders.";
			cout << "\n\t3. Add 4 new orders.";
			cout << "\n\t4. Show old orders.";
			cout << "\n\t5. Manage transport.\n";
			cout << "\n\t0. Exit\n";
			cout << "\n\n Enter your choose: ";
			cin >> choose;
			cout << '\n';
			switch (choose) {
			case 1:
				cout << c.getAssets(0);
				cout << "Rented:\n";
				cout << c.getAssets(1);
				system("pause");
				break;
			case 2:
				system("cls");
				cout << "NEW ORDERS:\n\n";
				showOrders(oc.getPath(1), 1, oc,c);
				break;
			case 3:
				for (int i = 0; i < 4; i++) {
					Order ord(length::m);
					oc.insertNewOrder(ord);
				}
				system("cls");
				cout << "Successfully added.";
				Sleep(ADD_SPEED);
				break;
			case 4:
				system("cls");
				cout << "OLD ORDERS:\n\n";
				showOrders(oc.getPath(0), 0, oc,c);
				break;
			case 5:
				system("cls");
				manageTransport(c);
				break;
			case 0:
				exit(0);
				break;
			default:
				system("cls");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t ";
				cout << "Please enter correct choose. Thank you!";
				cout << "\n\n\n\n\n\n\n\n\n\n\n";
				system("pause");
				break;
			}
		}
		cout << "\n\n\n\n\n\n\n\n\n\n\n";
		system("cls");
	}
}

int main() {
	//setlocale(LC_ALL, "cs_CZ");
	//setlocale(LC_CTYPE, "Czech");
	Creating();
	Orders_control OC;
	Company c("MyFirstComp");
	for (int i = 0; i < 4; i++) {
		Order ord(length::m);
		OC.insertNewOrder(ord);
		//OC.insertOldOrder(ord);
	}
	startMenu(OC,c);
	system("pause");
	return 0;
}

//SUM: 1839
//this - 1102
//game - 737