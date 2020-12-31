#include <iostream>
#include "Map.h"
#include "Continent.h"
#include <ctime>
Map* Map::gameMap;

//a constructor that creats the head of the linked list that represents the continents
Map::Map() {
	//create the head of the continent list (points to null at the begining)
	this->head = NULL ;
	this->size = 0;
}

Map* Map::getInstance()
{
	if (!gameMap) {
		gameMap = new Map();
		std::cout << "\n\n**********An instance of the map class has been created!*********\n\n";
	}
	else
		std::cout << "\n\n*******One map already created I can't creat multiple instances of the map**********\n\n";
	return gameMap;
}

Map::~Map() {
	delete start;
	Continent* traversal = head;
	Continent* ptr = head;
	while (traversal != NULL) {
		traversal = traversal->getNext();
		delete ptr;
		ptr = traversal;
	}
}

//add a continent node to map (linked list)
Continent* Map::addContinent(std::string name) 
{
	if (this->empty()) {
		Continent* ptr = new Continent(name, NULL);
		this->head = ptr;
		this->size++;
		return this->head;
	}
	else {
		Continent* ptr = new Continent(name, this->head);
		this->head = ptr;
		this->size++;
		return this->head;
	}

}
int Map::getSize() {
	return size;
}

Continent* Map::getHead() {
	return head;
}

Country* Map::findCountry(std::string name)
{
	Continent* temp = this->head;
	Country* tempCountry;
	for (int i = 0; i < this->getSize(); i++) {
		tempCountry = temp->findCountry(name);
		if (tempCountry != NULL) {
			//std::cout << "found a country!";
			return tempCountry;
		}
		temp = temp->getNext();
	}
	return nullptr;
}


bool Map::empty() {
	return (this->getSize())==0;
}

//function to print the map
bool Map::printMap() {
	Continent* temp = this->head;
	//loop over each adjacent list
	for (int i = 0; i < this->size; i++) {
		if (temp != NULL) {
			temp->print();
			std::cout << "\n****************************************************************\n";
			temp = temp->getNext();
		}
	}
	std::cout << "---------------" << this->start->getName()<<"\n";
	temp = NULL;
	return true;
}

bool Map::isValid()
{
	Continent* temp1 = head;
	Country* temp2;
	for (int i = 0; i < this->size; i++) {
		temp2 = temp1->getHead();
		for (int j = 0; j < temp1->noCountries; j++) {
			if(this->isDuplicate(temp2, temp1))
				return false;
			else {
				temp2 = temp2->getNext();
			}
		}
		temp1 = temp1->getNext();
	}
	return true;
}

bool Map::isDuplicate(Country* country,Continent* continent)
{
	Continent* temp1 = this->head;
	for (int i = 0; i < this->size; i++) {
		if (temp1->getName().compare(continent->getName()) != 0) {
			if (temp1->findCountry(country->getName()) != NULL)
				return true;
		}
		temp1 = temp1->getNext();
	}
	return false;
}

void Map::setStart(Country* country)
{
	this->start = country;
}

Country* Map::getStart()
{
	return this->start;
}

void Map::addLandBorder(Continent* Continent, Country* tempCountry, std::string name)
{
	Continent->addBorder(tempCountry, name);
}

void Map::addSeaBorder(Continent* Continent, Country* origin, Country* destin)
{
	if (origin != NULL && destin != NULL) {
		((origin->getSeaBorderList()))->push_back(destin);
		((destin->getSeaBorderList()))->push_back(origin);
	}
}
bool Map::isConnected() {
	Continent* temp1 = head;
	Country* temp2;
	std::vector<Country*> *connected = new std::vector <Country*>;
	connected->push_back(start);
	for (int i = 0; i < this->size; i++) {
		temp2 = temp1->getHead();
		for (int j = 0; j < temp1->noCountries; j++) {
			std::vector<Country*>* checked = new std::vector <Country*>;
			if (inVector(temp2, connected)) {
				temp2 = temp2->getNext();
				continue;
			}
			else if (start->hasPath(temp2,checked))
			{
				temp2->printCountry();
				connected->push_back(temp2);
				temp2 = temp2->getNext();
				continue;
			}
			else {
				temp2->printCountry();
				return false;
			}
		}
		temp1 = temp1->getNext();
	}
	return true;
}

std::string Map::getRandom()
{
	std::srand(std::time(0));
	int iSecret = rand() % this->size;
	Continent* tempContinent = this->head;
	int i = 0;
	int j = 0;
	while (i != iSecret) {
		tempContinent = tempContinent->getNext();
		i++;
	}
	Country* tempCountry = tempContinent->getHead();
	std::srand(std::time(0));
	int jSecret = rand() % tempContinent->noCountries;
	while (j != jSecret) {
		tempCountry = tempCountry->getNext();
		j++;
	}
	return tempCountry->getName();
}

//*******************************************************************************
bool Map::inVector(Country* country, std::vector<Country*>* connected) {

	for (size_t i = 0; i < connected->size(); i++) {
		if (country->getName().compare(connected->at(i)->getName()) == 0)
			return true;
	}
	return false;
}
std::vector<Country*>* Map::possibleEnemies(std::string color)
{
	Continent* temp = this->head;
	Country* tempCountry;
	std::vector<Country*>* someVector = new std::vector<Country*>;
	for (int i = 0; i < this->getSize(); i++) {
		tempCountry = temp->getHead();
		for (int j = 0; j < temp->noCountries ;j++) {
			for (size_t k = 0; k < tempCountry->getArmies()->size(); k++) {
				if (tempCountry->getArmies()->at(k).compare(color) != 0) {
					someVector->push_back(tempCountry);
					break;
				}
			}
			tempCountry = tempCountry->getNext();
		}
		temp = temp->getNext();
	}
	return someVector;
}