#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
#include <vector>
class Country
{
public:
	Country(std::string name, Country* next);
	Country(); 
	Country* getNext();
	void setNext(Country* next);
	std::string getName();
	std::string getColor();
	void setColor(std::string color);
	bool printCountry();

	std::vector<Country*>* getLandBorderList();
	std::vector<Country*>* getSeaBorderList();
	bool hasLandBorder(std::string name);
	bool hasSeaBorder(std::string name);
	bool hasBorder(std::string name);
	bool hasPath(Country* other, std::vector<Country*>* checked);
	bool inVector(Country* country, std::vector<Country*>* connected);

	bool hasArmy(std::string color);


	std::vector<std::string>* getCastles();
	std::vector<std::string>* getArmies();
	//void buildCastle(std::string color);
	bool destroyCastle(std::string color);


private:
	std::string* name;
	Country* next;
	std::vector<Country*> *landBorderList;
	std::vector<Country*> *seaBorderList;
	std::string* color;
	std::vector<std::string> *castles;
	std::vector<std::string> *armies;

};
#endif // !COUNTRY_H
