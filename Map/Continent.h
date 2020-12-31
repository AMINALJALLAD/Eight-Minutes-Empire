#ifndef CONTINENT_H
#define CONTINENT_H
#include "Country.h"
#include <string>
class Continent {
public:
	Continent(std::string name, Continent* next);
	Continent(); // add by Amin 
	std::string getName();
	Continent* getNext();
	bool print();
	bool empty();
	int noCountries;
	Country* findCountry(std::string name);
	Country* addCountry(std::string name);
	Country* getHead();
	bool addBorder(Country* origin, std::string name);


private:
	Continent* next;
	Country* head;
	std::string *name;
};
#endif // !CONTINENT_H