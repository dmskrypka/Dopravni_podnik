#include "Map.h"

Map::Map(const Map & m) { mC = m.mC; }

Map& Map::operator=(const Map & m) {
	this->mC.clear();
	this->mC = m.mC;
	return *this;
}

void Map::AddCityOnMap(City newC, int n) {
	this->mC.insert({ n, newC });
}

City Map::find(int id) {
	auto res = mC.find(id);
	return res->second;
}

void Map::Print() {
	auto iMap = mC.begin();
	for (; iMap != mC.end(); iMap++) {
		std::cout << iMap->first << ": " << (iMap->second).getName() << std::endl;
	}
}

int Map::getLength() {
	return this->mC.size();
}
