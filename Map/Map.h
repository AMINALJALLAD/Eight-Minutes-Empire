#ifndef MAP_H
#define MAP_H
#include "Continent.h"
class Map {
public:

	//singleton stuff
	static Map* getInstance(); 
	//end

	~Map();
	Continent* addContinent(std::string name);
	bool empty();
	bool printMap();
	int getSize();
	int size;
	Country* findCountry(std::string name);
	bool isValid();
	bool isDuplicate(Country* country, Continent* continent);
	void setStart(Country* country);
	Country* getStart();
	void addLandBorder(Continent* Continent, Country* tempCountry, std::string name);
	void addSeaBorder(Continent* Continent, Country* tempCountry, Country* destin);
	Continent* getHead();
	bool isConnected();
	std::string getRandom();
	bool inVector(Country* country, std::vector<Country*>* connected);

	std::vector<Country*>* possibleEnemies(std::string name);

private:
	//singleton stuff
	Map();
	static Map* gameMap;
	//end
	Continent* head;
	Country* start;
};

#endif